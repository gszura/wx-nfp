/*******************************************************************************
//
// Name:        wxHttpThread.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "wxHttpThread.h"
#include "wx-nfpAppInfo.h"
#include "wx-nfpAppVersion.h"

#include <wx/sstream.h>
#include <wx/datetime.h>
#include <wx/filename.h>
#include <wx/utils.h>
#include "wx/tokenzr.h"
#include "wx/uri.h"


const wxEventType wxEVT_NEW_APP_AVAILABLE_EVENT = wxNewEventType();
const wxEventType wxEVT_NEW_APP_DOWNLOADED_EVENT = wxNewEventType();
const wxEventType wxEVT_SYNC_OPERATION_DONE_EVENT = wxNewEventType();


/**
 *
 */
wxHttpThread::~wxHttpThread() {}

/**
 * thread execution starts here
 */
wxThread::ExitCode wxHttpThread::Entry()
{
    ExitCode exitCode = (wxThread::ExitCode)-1;

    switch (m_actionType) {
    case ACTION_CHECK_FOR_UPDATE: {
        exitCode = checkUpdateAvailability();
        if ( (size_t)exitCode == (size_t)-1 ) {
            sendEventAvailable( EVENT_STATUS_ERROR, m_response );
        }
        break;
    }
    case ACTION_DOWNLOAD_UPDATE: {
        exitCode = downloadUpdate();
        if ( (size_t)exitCode == (size_t)-1 ) {
            sendEventDownload( EVENT_STATUS_ERROR, m_response );
        }
        break;
    }
    case ACTION_IS_SERVER_ALIVE: {
        exitCode = checkIsServerAlive();
        sendEventSyncOperationDone(exitCode, m_response);
        break;
    }
    case ACTION_CHECK_USER_DATA_FILE: {
        exitCode = checkUserDataFile();
        sendEventSyncOperationDone(exitCode, m_response);
        break;
    }
    case ACTION_DOWNLOAD_USER_DATA_FILE: {
        exitCode = downloadUserDataFile();
        sendEventSyncOperationDone(exitCode, m_response);
        break;
    }
    case ACTION_UPLOAD_USER_DATA_FILE: {
        exitCode = uploadUserDataFile();
        sendEventSyncOperationDone(exitCode, m_response);
        break;
    }
    case ACTION_REMOVE_USER_DATA_FILE: {
        exitCode = removeUserDataFile();
        sendEventSyncOperationDone(exitCode, m_response);
        break;
    }
    default: {
        // unknown operation.. just exit
        wxLogDebug( wxString::Format( _T("[wxHttpThread] unknown operation!!: '%i'"), m_actionType ) );
    }
    }

    return exitCode;
}

/**
 * called when the thread exits - whether it terminates normally or is
 * stopped with Delete() (but not when it is Kill()ed!)
 */
void wxHttpThread::OnExit()
{
    //wxSocketBase::Shutdown();
}

/******************************************************************************
 ******************************************************************************
 ******************************************************************************/

/**
 * Check if there is a new version of application available.
 */
wxThread::ExitCode wxHttpThread::checkUpdateAvailability()
{
    m_address = wxString::Format( _T( "%s%s" ), m_serverName.c_str(), UPDATES_PATH );
#if defined(__UNIX__)
    m_address << _T( "?os=deb" ) << (wxIsPlatform64Bit() ? _T( "64" ) : _T( "32" ));
#else
    m_address << _T( "?os=win" ); //  << wxIsPlatform64Bit() ? _T( "64" ) : _T( "32" );
#endif

    // open connection
    if ( !openConnection() ) {
        return (wxThread::ExitCode)-1;
    }

    // send request
    if ( !getInputStream() ) {
        return (wxThread::ExitCode)-1;
    }

    // get response
    wxString content = get();

    // close connection
    closeConnection();

    if ( content.StartsWith( _( "Error" ) ) ) {
        m_response = wxString::Format( _( "Incorrect data received from Web Server: '%s'" ), content.c_str() );
        return (wxThread::ExitCode)-1;
    }

    // expected output:
    // 0.9.1444;download/wx-nfp_setup_0.9.1444.exe
    // 0.9.1;download/wx-nfp_0.9.1_i386.deb

    wxStringTokenizer tkz(content, wxT(";"));
    if (tkz.CountTokens() != 2) {
        m_response = wxString::Format( _( "Incorrect data received from server -there should be exactly one ';' character in the string: '%s'" ), content.c_str() );
        return (wxThread::ExitCode)-1;
    }

    wxLogDebug( wxString::Format( _T("[wxHttpThread] checkUpdateAvailability response: %s"), content.c_str() ) );

    wxString availableVersionStr = tkz.GetNextToken();
    wxString setupFilePath = tkz.GetNextToken();

    int installedVersion = m_util.strToInt( wxString::Format( _T( "%d" ), AutoVersion::_MAJOR) ) * 1000000;
    installedVersion += m_util.strToInt( wxString::Format( _T( "%d" ), AutoVersion::_MINOR) ) * 100000;
    installedVersion += m_util.strToInt( wxString::Format( _T( "%d" ), AutoVersion::_BUILD) );
    int availableVersion = 0;
    wxString tmp;

    wxStringTokenizer tkz2(availableVersionStr, wxT("."));
    if (tkz2.CountTokens() < 2) {
        m_response = wxString::Format( _( "Incorrect data received from server -couldn't find the '.' character in the 'availableVersion' string '%s'" ), availableVersionStr.c_str() );
        return (wxThread::ExitCode)-1;
    }

    availableVersion = m_util.strToInt(tkz2.GetNextToken()) * 1000000;
    if ( tkz2.HasMoreTokens() )
        availableVersion += m_util.strToInt(tkz2.GetNextToken()) * 100000;
    if ( tkz2.HasMoreTokens() )
        availableVersion += m_util.strToInt(tkz2.GetNextToken());

    wxLogDebug( wxString::Format( _T("[wxHttpThread] installed version of application: %i, available: %i"), installedVersion, availableVersion ) );
    if ( installedVersion < availableVersion ) {

        wxString newAppSetupFileUrl = m_address.BeforeLast( _T('/') ) + _T('/') + setupFilePath;
        sendEventAvailable( EVENT_STATUS_UPDATE_AVAILABLE, newAppSetupFileUrl );
    } else {
        sendEventAvailable( EVENT_STATUS_UPDATE_NOT_AVAILABLE, wxEmptyString );
    }

    return 0;
}

/******************************************************************************/

/**
 * Download new version of application.
 */
wxThread::ExitCode wxHttpThread::downloadUpdate()
{
    // Preparing value of the 'Host' header
    m_address = m_serverName;

    // open connection
    if ( !openConnection() ) {
        return (wxThread::ExitCode)-1;
    }

    // send request
    if ( !getInputStream() ) {
        return (wxThread::ExitCode)-1;
    }

    setCurrentAction( _("receiving data") );

    // opening file to store downloaded file
    wxString tempFilePath = wxFileName::CreateTempFileName( _T( "nfp" ) ) + _T( ".exe" );

    m_fileOutputStream = new wxFileOutputStream( tempFilePath );
    if ( !m_fileOutputStream->Ok() ) {
        closeConnection();
        m_response = wxString::Format( _( "Cannot save file to disk: '%s'" ), tempFilePath.c_str() );
        return (wxThread::ExitCode)-1;
    }

    // reading and storing downloaded file
    m_inputStream->Read( *m_fileOutputStream );

    // close connection
    m_fileOutputStream->Close();
    closeConnection();


    sendEventDownload( EVENT_STATUS_UPDATE_DOWNLOADED, tempFilePath );
    return 0;
}

/******************************************************************************/

/**
 * Check if server is alive
 * - request 'ping.php' page
 * - expected return is string 'I am alive'
 */
wxThread::ExitCode wxHttpThread::checkIsServerAlive()
{
    m_address = wxString::Format( _T( "%s%s" ), m_serverName.c_str(), SERVER_PING_PATH );

    // open connection
    if ( !openConnection() ) {
        return (wxThread::ExitCode)-1;
    }

    // send request
    if ( !getInputStream() ) {
        return (wxThread::ExitCode)-1;
    }

    // get response
    wxString content = get();

    // close connection
    closeConnection();

    if ( content.IsEmpty() || !content.IsSameAs( PING_RESPONSE ) ) {
        m_response = wxString::Format( _( "Error: Wrong response from server. Expected: '%s', received: '%s'"), PING_RESPONSE, content.c_str() );
        return (wxThread::ExitCode)-1;
    }

    // server is alive
    return 0;
}


/******************************************************************************/

/**
 * Check if file exists on remote server.
 */
wxThread::ExitCode wxHttpThread::checkUserDataFile()
{
    if ( m_inputData.IsEmpty() ) {
        m_response = wxString::Format( _( "Error: Hash is empty - it seems that data file has never been stored on the server" ) );
        return (wxThread::ExitCode)-1;
    }

    m_address = wxString::Format( _T( "%s%s?f=%s" ), m_serverName.c_str(), CHECK_FILE_PATH, m_inputData.c_str() );

    // open connection
    if ( !openConnection() ) {
        return (wxThread::ExitCode)-1;
    }

    // send request
    if ( !getInputStream() ) {
        return (wxThread::ExitCode)-1;
    }

    // get response
    wxString content = get();

    // close connection
    closeConnection();

    if ( content.Length() != 32 || content.StartsWith( _( "Error" ) ) ) {
        m_response = wxString::Format( _( "Error: Incorrect data received from server: '%s'" ), content.c_str() );
        return (wxThread::ExitCode)-1;
    }

    // expected output: md5sum string (32 characters)
    m_response = content;
    // file exists
    return 0;
}

/******************************************************************************/

/**
* Download latest user data file.
*/
wxThread::ExitCode wxHttpThread::downloadUserDataFile()
{
    if ( m_inputData.IsEmpty() ) {
        m_response = wxString::Format( _( "Error: Hash is empty - it seems that data file has never been stored on the server" ) );
        return (wxThread::ExitCode)-1;
    }

    m_address = wxString::Format( _T( "%s%s?f=%s" ), m_serverName.c_str(), DOWNLOAD_FILE_PATH, m_inputData.c_str() );

    // open connection
    if ( !openConnection() ) {
        return (wxThread::ExitCode)-1;
    }

    // send request
    if ( !getInputStream() ) {
        return (wxThread::ExitCode)-1;
    }

    setCurrentAction( _("receiving data") );

    // opening file to store downloaded file
    wxString tempFilePath = wxFileName::CreateTempFileName( _T( "nfp" ) );

    m_fileOutputStream = new wxFileOutputStream( tempFilePath );
    if ( !m_fileOutputStream->Ok() ) {
        closeConnection();
        m_response = wxString::Format( _( "Error: Cannot save file to disk: '%s'" ), tempFilePath.c_str() );
        return (wxThread::ExitCode)-1;
    }

    // reading and storing downloaded file
    m_inputStream->Read( *m_fileOutputStream );

    // close connection
    m_fileOutputStream->Close();


    if ( m_http->GetResponse() != 200 ) {
        m_response = wxString::Format( _( "Error: incorrect response code: %i (expected 200)" ), m_http->GetResponse() );
    }

    wxString responseContentType = m_http->GetHeader( _T("Content-Type") );
    if ( !responseContentType.IsSameAs(_T("application/octet-stream")) ) {
        closeConnection();
        m_response = wxString::Format( _( "Error: content type of the response: '%s' ((expected 'application/octet-stream')" ), responseContentType.c_str() );
        return (wxThread::ExitCode)-1;
    }

    closeConnection();

    m_response = tempFilePath;

    return 0;
}

/******************************************************************************/

/**
* Upload user data file.
*/
wxThread::ExitCode wxHttpThread::uploadUserDataFile()
{
    if ( m_inputData.IsEmpty() ) {
        m_response = wxString::Format( _( "Error: File parameter is not defined: '%s'" ), m_inputData.c_str() );
        return (wxThread::ExitCode)-1;
    }
    if ( !wxFileExists(m_inputData) ) {
        m_response = wxString::Format( _( "Error: File does not exist: '%s'" ), m_inputData.c_str() );
        return (wxThread::ExitCode)-1;
    }
    if ( m_inputData2.IsEmpty() ) {
        m_response = wxString::Format( _( "Error: File name parameter is not defined: '%s'" ), m_inputData2.c_str() );
        return (wxThread::ExitCode)-1;
    }

    m_address = wxString::Format( _T( "%s%s" ), m_serverName.c_str(), UPLOAD_FILE_PATH );

    if ( !parseServerName() ) {
        return (wxThread::ExitCode)-1;
    }

    wxString content = postFile(m_inputData, m_inputData2);

    if ( content.Length() != 46 || content.StartsWith( _( "Error" ) ) ) {
        m_response = wxString::Format( _( "Error: Incorrect data received from server: '%s'" ), content.c_str() );
        return (wxThread::ExitCode)-1;
    }

    // expected output: md5sum string (32 characters)
    m_response = content;

    return 0;
}


/******************************************************************************/

/**
* Remove from server all copies of user data file.
*/
wxThread::ExitCode wxHttpThread::removeUserDataFile()
{
    if ( m_inputData.IsEmpty() ) {
        m_response = wxString::Format( _( "Error: Hash is empty - it seems that data file has never been stored on the server" ) );
        return (wxThread::ExitCode)-1;
    }

    m_address = wxString::Format( _T( "%s%s?f=%s" ), m_serverName.c_str(), REMOVE_FILE_PATH, m_inputData.c_str() );

    // open connection
    if ( !openConnection() ) {
        return (wxThread::ExitCode)-1;
    }

    // send request
    if ( !getInputStream() ) {
        return (wxThread::ExitCode)-1;
    }

    // get response
    wxString content = get();

    // close connection
    closeConnection();

    if ( content.Length() != 2 || content.StartsWith( _( "Error" ) ) ) {
        m_response = wxString::Format( _( "Error: Incorrect data received from server: '%s'" ), content.c_str() );
        return (wxThread::ExitCode)-1;
    }

    // expected output: md5sum string (32 characters)
    m_response = content;
    // file exists
    return 0;
}

/******************************************************************************
 ******************************************************************************
 ******************************************************************************/

/**
 *
 */
void wxHttpThread::sendEventAvailable( int id, wxString message )
{
    wxCommandEvent event( wxEVT_NEW_APP_AVAILABLE_EVENT, THREAD_EVENT );
    event.SetInt( id );
    event.SetString( message );
    wxPostEvent( m_parent, event );
}


/**
 *
 */
void wxHttpThread::sendEventDownload( int id, wxString message )
{
    wxCommandEvent event( wxEVT_NEW_APP_DOWNLOADED_EVENT, THREAD_EVENT );
    event.SetInt( id );
    event.SetString( message );
    wxPostEvent( m_parent, event );
}

/**
 *
 */
void wxHttpThread::sendEventSyncOperationDone( wxThread::ExitCode retCode, wxString message )
{
    wxCommandEvent event( wxEVT_SYNC_OPERATION_DONE_EVENT, THREAD_EVENT );
    event.SetInt( (size_t)retCode );
    event.SetString( message );
    wxPostEvent( m_parent, event );
}


/******************************************************************************
 ******************************************************************************
 ******************************************************************************/

bool wxHttpThread::parseServerName()
{
    wxURI uri(m_address);

    if ( uri.HasScheme() && !uri.GetScheme().IsSameAs( _T("http") )) {
        m_response = wxString::Format( _T("Error: not supported scheme: %s (only 'http' is supported"), uri.GetScheme().c_str() );
        return false;
    }
    if ( !uri.HasServer() ) {
        m_response = wxString::Format( _T("Error: cannot find a server name in given address: %s"), m_address.c_str() );
        return false;
    }
    if ( !uri.HasPath() ) {
        m_response = wxString::Format( _T("Error: cannot find a path in given address: %s"), m_address.c_str() );
        return false;
    }

    m_host = uri.GetServer();
    if ( uri.HasPort() && !uri.GetPort().IsSameAs( _T("80") )) {
        m_host += _T(":") + uri.GetPort();
        m_port = m_util.strToInt(uri.GetPort());
    }
    m_path = uri.GetPath();
    if ( uri.HasQuery() ) {
        m_path += _T("?") + uri.GetQuery();
    }

    wxLogDebug( wxString::Format( _T("[wxHttpThread] host: %s"), m_host.c_str() ) );
    wxLogDebug( wxString::Format( _T("[wxHttpThread] port: %i"), m_port ) );
    wxLogDebug( wxString::Format( _T("[wxHttpThread] path: %s"), m_path.c_str() ) );

    return true;
}

/******************************************************************************/

bool wxHttpThread::openConnection()
{
    if ( !parseServerName() ) {
        return false;
    }

    setCurrentAction( wxString::Format( _("opening connection to the server: %s:%i"), m_host.c_str(), m_port ) );

    wxString connectHost = m_host;
    unsigned short connectPort = m_port;

    /*
    if ( ! m_config->updatesProxy.IsEmpty() ) {
        // connect through the proxy
        int t = m_config->updatesProxy.Find( _T( ":" ) );
        if (t < 0) {
            connectHost = m_config->updatesProxy;
            connectPort = 8080;
        } else {
            connectHost = m_config->updatesProxy.Mid(0, t);
            connectPort = m_util.strToInt( m_config->updatesProxy.Mid(t+1));
        }
    }
    */

    // Prepare the wxHTTP object
    m_http = new wxHTTP();
    m_http->SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...

    wxLogDebug( wxString::Format( _T("[wxHttpThread] connecting to: %s:%i"), connectHost.c_str(), connectPort ) );

    bool success = m_http->Connect(connectHost, connectPort);
    if ( !success ) {
        wxLogDebug( wxString::Format( _T("[wxHttpThread] NOT connected (error: %i). trying once again.."), m_http->GetError() ) );
        wxSleep(1);
        success = m_http->Connect(connectHost, connectPort);
    }

    if ( !success ) {
        m_response = wxString::Format( _("Error: cannot connect to the server: %s:%i"), connectHost.c_str(), connectPort );
        return false;
    }

    wxLogDebug( _T("[wxHttpThread] connected") );

//if ( m_http->GetError() != wxPROTO_NOERR ) {
//    m_response = wxString::Format( _( "Problem with reading data from the server '%s'.. error code: %d" ), m_address.c_str(), m_http->GetError() );
//    return false;
//}

    m_http->SetHeader(_T("Host"), m_host);
    m_http->SetHeader(_T("User-Agent"), _T("wxWidgets 2.x"));

    return true;
}

/******************************************************************************/

bool wxHttpThread::closeConnection()
{
    wxDELETE(m_inputStream);
    m_http->Close();
    return true;
}

/******************************************************************************/

bool wxHttpThread::getInputStream()
{
    setCurrentAction( _("sending data") );

    m_inputStream = m_http->GetInputStream( m_path );

    if ( m_http->GetError() == wxPROTO_NOERR ) {
        return true;
    } else {
        m_response = wxString::Format( _( "Problem with reading data from: http://%s%i%s.. error code: %d" ), m_host.c_str(), m_port, m_path.c_str(), m_http->GetError() );
        closeConnection();
        return false;
    }
}

/******************************************************************************
 ******************************************************************************
 ******************************************************************************/

wxString wxHttpThread::get()
{
    setCurrentAction( _("receiving data") );

    wxString content;
    wxStringOutputStream out_stream(&content);
    m_inputStream->Read(out_stream);
    content.Trim( true );
    content.Trim( false );

    if ( m_http->GetError() != wxPROTO_NOERR ) {
        m_response = wxString::Format( _("Error: problem with server, error code: %i"), m_http->GetError() );
    }

    return content;
}


/******************************************************************************
 ******************************************************************************
 ******************************************************************************/

wxString wxHttpThread::postFile(const wxString& fileToUploadPath, const wxString& fileToUploadName)
{
    setCurrentAction( wxString::Format( _("opening connection to the server: %s:%i"), m_host.c_str(), m_port ) );

    setInputStramReady(false);
    m_socket = new wxSocketClient(wxSOCKET_WAITALL);
    wxIPV4address addr;
    addr.Hostname(m_host);
    addr.Service(80);
    if(!m_socket->Connect(addr, true)) {
        return _T("Error: Connection to server failed");
    }
    setInputStramReady(true);

    // prepare the post data
    setCurrentAction( _("preparing data to sent") );

    wxString boundary = _T("--") + fileToUploadName + _T("--");
    wxFileInputStream fileInputStream( fileToUploadPath );
    if( !fileInputStream.IsOk() ) {
        setInputStramReady(false);
        return wxString::Format( _T( "Error: Cannot create input stream for file: '%s'" ), fileToUploadPath.c_str() );
    }

    size_t fileSize = fileInputStream.GetSize();
    wxString postDataHeader;
    wxString postDataFooter;

    postDataHeader << wxString::Format( _T("--%s\r\n"), boundary.c_str() );
    postDataHeader << wxString::Format( _T("Content-Disposition: form-data; name=\"file\"; filename=\"%s\"\r\n"), fileToUploadName.c_str() );
    postDataHeader << _T("Content-Type: application/octet-stream\r\n\r\n");
    postDataFooter << wxString::Format( _T("\r\n--%s--\r\n"), boundary.c_str() );

    m_uploadSize = fileSize + postDataHeader.length() + postDataFooter.length();
    m_uploadedSoFar = 0;

    // preparing http request headers
    wxString postHeader;
    postHeader << wxString::Format( _T("POST %s HTTP/1.0\r\n"), m_path.c_str());
    postHeader << wxString::Format( _T("Host: %s\r\n"), m_host.c_str());
    postHeader << wxString::Format( _T("Content-Length: %i\r\n"), m_uploadSize);
    postHeader << wxString::Format( _T("Content-Type: multipart/form-data; boundary=%s\r\n"), boundary.c_str());
    postHeader << _T("User-Agent: wxWidgets 2.x\r\n\r\n");

    setCurrentAction( _("sending data") );

    // sending post headers
    wxLogDebug( wxString::Format( _T("[wxHttpThread] sending %i bytes of header"), postHeader.length()) );
    m_socket->Write(postHeader.mb_str(), wxStrlen(postHeader));
    wxLogDebug( wxString::Format( _T( "[wxHttpThread] sent %i bytes of headers" ), m_socket->LastCount() ) );

    // sending post data
    wxLogDebug( wxString::Format( _T("[wxHttpThread] sending %i bytes of content"), m_uploadSize) );
    m_socket->Write(postDataHeader.mb_str(), postDataHeader.length());
    m_uploadedSoFar += postDataHeader.length();

    wxByte* tempBuffer = new wxByte[UPLOAD_BUFFER_SIZE];
    while ( !fileInputStream.Eof() ) {
        fileInputStream.Read( tempBuffer, UPLOAD_BUFFER_SIZE );
        int bytesRead = fileInputStream.LastRead();
        m_socket->Write(tempBuffer, bytesRead);
        m_uploadedSoFar += bytesRead;
    }
    wxLogDebug( wxString::Format( _T( "[wxHttpThread] sent %i bytes of content" ), m_uploadedSoFar ) );

    wxLogDebug( wxString::Format( _T("[wxHttpThread] sending %i bytes of footer"), postHeader.length()) );
    m_socket->Write(postDataFooter.mb_str(), postDataFooter.length());
    m_uploadedSoFar += postDataFooter.length();
    wxLogDebug( wxString::Format( _T( "[wxHttpThread] sent %i bytes of footer" ), m_uploadedSoFar ) );

    wxString response = readResponse();

    setInputStramReady(false);
    m_socket->Close();
    delete m_socket;

    return response;
}


wxString wxHttpThread::readResponse()
{
    setCurrentAction( _("receiving data") );

    HeadersHashMap headers = readResponseHeaders();
    int contentSize = m_util.strToInt( headers[ _T("Content-Length") ] );

    return read(contentSize);
}


HeadersHashMap wxHttpThread::readResponseHeaders()
{
    HeadersHashMap headers;
    wxString line;
    wxStringTokenizer tokenzr;

    for ( ;; ) {
        line = readLine();

        if ( line.IsEmpty() ) {
            break;
        }

        wxString headerName = line.BeforeFirst(':');
        wxString headerValue = line.AfterFirst(':').Strip(wxString::both);
        headers[headerName] = headerValue;
        wxLogDebug( wxString::Format( _T("header: %s = %s"), headerName.c_str(), headerValue.c_str() ) );
    }

    wxLogDebug( wxString::Format( _T("found %i headers"), headers.size() ) );
    return headers;
}

wxString wxHttpThread::readLine()
{
    const int LINE_BUF = 4095;

    wxString result = wxEmptyString;

    wxCharBuffer buf(LINE_BUF);
    char *pBuf = buf.data();
    while ( m_socket->WaitForRead() ) {
        // peek at the socket to see if there is a CRLF
        m_socket->Peek(pBuf, LINE_BUF);

        size_t nRead = m_socket->LastCount();
        if ( !nRead && m_socket->Error() )
            return result;

        // look for "\r\n" paying attention to a special case: "\r\n" could
        // have been split by buffer boundary, so check also for \r at the end
        // of the last chunk and \n at the beginning of this one
        pBuf[nRead] = '\0';
        const char *eol = strchr(pBuf, '\n');

        // if we found '\n', is there a '\r' as well?
        if ( eol ) {
            if ( eol == pBuf ) {
                // check for case of "\r\n" being split
                if ( result.IsEmpty() || result.Last() != wxT('\r') ) {
                    // ignore the stray '\n'
                    eol = NULL;
                }
                //else: ok, got real EOL

                // read just this '\n' and restart
                nRead = 1;
            } else { // '\n' in the middle of the buffer
                // in any case, read everything up to and including '\n'
                nRead = eol - pBuf + 1;

                if ( eol[-1] != '\r' ) {
                    // as above, simply ignore stray '\n'
                    eol = NULL;
                }
            }
        }

        m_socket->Read(pBuf, nRead);
        if ( m_socket->LastCount() != nRead )
            return result;

        pBuf[nRead] = '\0';
        result += wxString::FromAscii(pBuf);

        if ( eol ) {
            // remove trailing "\r\n"
            result.RemoveLast(2);

            return result;
        }
    }

    return result;
}

wxString wxHttpThread::read(int bytestCount)
{
    wxLogDebug( wxString::Format( _T("[wxHttpThread] trying to read %i bytes of content"), bytestCount ) );

    int readSoFar = 0;

    wxString result = wxEmptyString;

    wxCharBuffer buf(bytestCount+1);
    char *pBuf = buf.data();
    while ( m_socket->WaitForRead() ) {
        // peek at the socket to see if there is a CRLF
        m_socket->Read(pBuf, bytestCount);
        readSoFar += (int)m_socket->LastCount();
        wxLogDebug( wxString::Format( _T("[wxHttpThread] read %i bytes so far.."), readSoFar ) );
        pBuf[readSoFar] = '\0';
        result += wxString::FromAscii(pBuf);
        if (readSoFar >= bytestCount)
            break;
    }

    return result;
}



/******************************************************************************
 ******************************************************************************
 ******************************************************************************/

int wxHttpThread::getUploadDownloadSize()
{
    if (m_actionType == ACTION_UPLOAD_USER_DATA_FILE)
        return getUploadSize();
    else
        return getDownloadSize();
}

int wxHttpThread::getUploadedDownloadedSoFar()
{
    if (m_actionType == ACTION_UPLOAD_USER_DATA_FILE)
        return getUploadedSoFar();
    else
        return getDownloadedSoFar();
}

int wxHttpThread::getUploadSize()
{
    return m_uploadSize;
}

int wxHttpThread::getUploadedSoFar()
{
    return m_uploadedSoFar;
}

int wxHttpThread::getDownloadSize()
{
    if ( isInputStramReady() )
        return m_inputStream->GetSize();
    else
        return -1;
}

int wxHttpThread::getDownloadedSoFar()
{
    if ( isInputStramReady() )
        return m_inputStream->GetSize();
    else
        return -1;
}

/******************************************************************************/

bool wxHttpThread::isInputStramReady()
{
    wxCriticalSectionLocker locker(gs_critSectionLocker1);
    return m_inputStramReady;
}

void wxHttpThread::setInputStramReady(bool value)
{
    wxCriticalSectionLocker locker(gs_critSectionLocker1);
    m_inputStramReady = value;
}

/******************************************************************************/

wxString wxHttpThread::getCurrentAction()
{
    wxCriticalSectionLocker locker(gs_critSectionLocker2);
    return m_currentAction;
}

void wxHttpThread::setCurrentAction(wxString currentAction)
{
    wxCriticalSectionLocker locker(gs_critSectionLocker2);
    m_currentAction = currentAction;
}



/******************************************************************************
 ******************************************************************************
 ******************************************************************************/
