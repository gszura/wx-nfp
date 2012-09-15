/*******************************************************************************
//
// Name:        liveUpdateClass.cpp
// Author:      enkeli
// Description:
//
*******************************************************************************/

#include "liveUpdateClass.h"
#include "wx-nfpAppInfo.h"
#include "wx-nfpAppVersion.h"

#include <wx/protocol/http.h>
#include <wx/sstream.h>
#include <wx/datetime.h>
#include <wx/filename.h>
#include <wx/utils.h>


const wxEventType wxEVT_NEW_APP_AVAILABLE_EVENT = wxNewEventType();
const wxEventType wxEVT_NEW_APP_DOWNLOADED_EVENT = wxNewEventType();

/**
 *
 */
liveUpdateClass::liveUpdateClass( wxWindow *parent, configClass *config, bool checkUpdates, wxString newAppSetupFileUrl ) {
    m_parent = parent;
    m_config = config;
    m_newAppSetupFilePath = wxFileName::CreateTempFileName( _T( "NFP" ) ) + _T( ".exe" );;
    m_checkUpdates = checkUpdates;
    m_newAppSetupFileUrl = newAppSetupFileUrl;
}

/**
 *
 */
liveUpdateClass::~liveUpdateClass() {}

/**
 * thread execution starts here
 */
void *liveUpdateClass::Entry() {
    if ( m_checkUpdates ) {
        checkUpdateAvailability();
    } else {
        downloadUpdate();
    }
    return NULL;
}

/**
 * called when the thread exits - whether it terminates normally or is
 * stopped with Delete() (but not when it is Kill()ed!)
 */
void liveUpdateClass::OnExit() {
    //wxSocketBase::Shutdown();
}

/******************************************************************************/

/**
 * Check if there is a new version of application available.
 */
bool liveUpdateClass::checkUpdateAvailability() {
    wxString urlToFetch = wxString::Format( _T( "%s%s" ), HOME_URL, UPDATES_PATH );
#if defined(__UNIX__)
    urlToFetch << _T( "?os=deb" ) << (wxIsPlatform64Bit() ? _T( "64" ) : _T( "32" ));
#else
    urlToFetch << _T( "?os=win" ); //  << wxIsPlatform64Bit() ? _T( "64" ) : _T( "32" );
#endif

    // Preparing value of the 'Host' header
    wxString host = HOME_URL;
    int t = host.Find( _T( "//" ) );
    host = host.Mid( t + 2 );
    t = host.Find( _T( "/" ) );
    host = host.Mid( 0, t );

    // preparing the host name and port where we are going to connect
    wxString connectHost = host;
    unsigned short connectPort = 80;
    if ( ! m_config->updatesProxy.IsEmpty() ) {
        // connect through the proxy
        t = m_config->updatesProxy.Find( _T( ":" ) );
        if (t < 0) {
            connectHost = m_config->updatesProxy;
            connectPort = 8080;
        } else {
            connectHost = m_config->updatesProxy.Mid(0, t);
            connectPort = m_util.strToInt( m_config->updatesProxy.Mid(t+1));
        }
    }

    // Prepare the wxHTTP object
    wxHTTP wxHttp;
    wxHttp.SetHeader(_T("User-Agent"), _T("wxWidgets 2.x"));
    wxHttp.SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...

    for (int i=10; i>0; i--) {
        if (wxHttp.Connect(connectHost, connectPort))
            break;
        wxSleep(1);
    }

    // Try to get the input stream (connects to the given URL)
    wxHttp.SetHeader(_T("Host"), host);
    wxInputStream *in_stream = wxHttp.GetInputStream( urlToFetch );

    if ( wxHttp.GetError() != wxPROTO_NOERR ) {
        sendEventAvailable( EVENT_STATUS_ERROR, wxString::Format( _( "Problem with reading data from the server '%s'.. error code: %d" ), urlToFetch.c_str(), wxHttp.GetError() ) );
        return false;
    }

    // Get the data
    wxString content;
    wxStringOutputStream out_stream(&content);
    in_stream->Read(out_stream);
    content.Trim( true );
    content.Trim( false );

    wxDELETE(in_stream);
    wxHttp.Close();

    if ( content.StartsWith( _( "Error" ) ) ) {
        sendEventAvailable( EVENT_STATUS_ERROR, wxString::Format( _( "Incorrect data received from Web Server: '%s'" ), content.c_str() ) );
        return false;
    }

    // expected output:
    // X.Y;download/wx-nfp_setup.exe
    // X.Y;download/wx-nfp_setup.tar.gz
    t = content.Find( _T( ";" ) );
    if ( t == -1 ) {
        sendEventAvailable( EVENT_STATUS_ERROR, wxString::Format( _( "Incorrect data received from Web Server -couldn't find the ';' character in the string '%s'" ), content.c_str() ) );
        return false;
    }

    wxString availableVersionStr = content.Mid( 0, t );
    wxString setupFilePath = content.Mid( t + 1 );

    int installedVersion = m_util.strToInt( wxString::Format( _T( "%d" ), AutoVersion::_MAJOR) ) * 100000 + m_util.strToInt( wxString::Format( _T( "%d" ), AutoVersion::_MINOR) ) * 10000 + m_util.strToInt( wxString::Format( _T( "%d" ), AutoVersion::_BUILD) );
    int availableVersion = 0;
    wxString tmp;

    t = availableVersionStr.Find( _T( "." ) );
    if ( t > -1 ) {
        availableVersion = m_util.strToInt( availableVersionStr.Mid( 0, t ) ) * 100000;
        tmp = availableVersionStr.Mid( t + 1 );
    } else {
        sendEventAvailable( EVENT_STATUS_ERROR, wxString::Format( _( "Incorrect data received from Web Server - couldn't find the '.' character in the 'availableVersion' string '%s'" ), availableVersionStr.c_str() ) );
        return false;
    }
    t = tmp.Find( _T( "." ) );
    if ( t > -1 ) {
        availableVersion = m_util.strToInt( tmp.Mid( 0, t ) ) * 10000 + m_util.strToInt( tmp.Mid( t + 1 ) );
    } else {
        availableVersion = m_util.strToInt( tmp ) * 10000;
    }

    if ( installedVersion < availableVersion ) {
        wxString newAppSetupFileUrl = urlToFetch.Mid( 0, urlToFetch.Find( _T( '/' ), true ) + 1 ) + setupFilePath;
        sendEventAvailable( EVENT_STATUS_UPDATE_AVAILABLE, newAppSetupFileUrl );
    } else {
        sendEventAvailable( EVENT_STATUS_UPDATE_NOT_AVAILABLE, _T( "" ) );
    }

    return true;
}

/**
 * Download new version of application.
 */
bool liveUpdateClass::downloadUpdate() {
    // Preparing value of the 'Host' header
    wxString host = m_newAppSetupFileUrl;
    int t = host.Find( _T( "//" ) );
    host = host.Mid( t + 2 );
    t = host.Find( _T( "/" ) );
    host = host.Mid( 0, t );

    // preparing the host name and port where we are going to connect
    wxString connectHost = host;
    unsigned short connectPort = 80;
    if ( ! m_config->updatesProxy.IsEmpty() ) {
        // connect through the proxy
        t = m_config->updatesProxy.Find( _T( ":" ) );
        if (t < 0) {
            connectHost = m_config->updatesProxy;
            connectPort = 8080;
        } else {
            connectHost = m_config->updatesProxy.Mid(0, t);
            connectPort = m_util.strToInt( m_config->updatesProxy.Mid(t+1) );
        }
    }

    // Prepare the wxHTTP object
    wxHTTP wxHttp;
    wxHttp.SetHeader(_T("User-Agent"), _T("wxWidgets 2.x"));
    wxHttp.SetTimeout(10); // 10 seconds of timeout instead of 10 minutes ...

    for (int i=10; i>0; i--) {
        if (wxHttp.Connect(connectHost, connectPort))
            break;
        wxSleep(1);
    }

    // Try to get the input stream (connects to the given URL)
    wxHttp.SetHeader(_T("Host"), host);
    m_inputStream = wxHttp.GetInputStream( m_newAppSetupFileUrl );

    if ( wxHttp.GetError() != wxPROTO_NOERR ) {
        sendEventAvailable( EVENT_STATUS_ERROR, wxString::Format( _( "Problem with reading data from the server '%s'.. error code: %d" ), m_newAppSetupFileUrl.c_str(), wxHttp.GetError() ) );
        return false;
    }

    // opening file to store downloaded file
    m_fileOutputStream = new wxFileOutputStream( m_newAppSetupFilePath );
    if ( !m_fileOutputStream->Ok() ) {
        delete m_inputStream;
        sendEventAvailable( EVENT_STATUS_ERROR, wxString::Format( _( "Cannot save file to disk: '%s'" ), m_newAppSetupFilePath.c_str() ) );
        return false;
    }

    // storing downloaded file
    m_inputStream->Read( *m_fileOutputStream );

    wxDELETE(m_inputStream);
    m_fileOutputStream->Close();
    wxHttp.Close();

    sendEventDownload( EVENT_STATUS_UPDATE_DOWNLOADED, m_newAppSetupFilePath );
    return true;
}

/**
 *
 */
void liveUpdateClass::sendEventAvailable( int id, wxString message ) {
    wxCommandEvent event( wxEVT_NEW_APP_AVAILABLE_EVENT, THREAD_EVENT );
    event.SetInt( id );
    event.SetString( message );
    wxPostEvent( m_parent, event );
}

/**
 *
 */
void liveUpdateClass::sendEventDownload( int id, wxString message ) {
    wxCommandEvent event( wxEVT_NEW_APP_DOWNLOADED_EVENT, THREAD_EVENT );
    event.SetInt( id );
    event.SetString( message );
    wxPostEvent( m_parent, event );
}

/**
 *
 */
wxInputStream *liveUpdateClass::getInputStream() {
    if ( m_inputStream != NULL && m_inputStream->IsOk() ) {
        return m_inputStream;
    } else {
        return NULL;
    }
}

/**
 *
 */
wxFileOutputStream *liveUpdateClass::getFileOutputStream() {
    if ( m_fileOutputStream != NULL && m_fileOutputStream->IsOk() ) {
        return m_fileOutputStream;
    } else {
        return NULL;
    }
}

/******************************************************************************/
