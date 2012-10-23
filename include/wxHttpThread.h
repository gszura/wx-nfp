#ifndef HEADER_C67620A3ED36BBA9
#define HEADER_C67620A3ED36BBA9

/*******************************************************************************
//
// Name:        wxHttpThread.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef __LIVE_UPDATE_CLASS__
#define __LIVE_UPDATE_CLASS__

#include "configClass.h"
#include "cyclesData.h"
#include "utilClass.h"
#include <wx/wfstream.h>
#include <wx/protocol/http.h>
#include <wx/hashmap.h>

/******************************************************************************/

#define ACTION_CHECK_FOR_UPDATE           1
#define ACTION_DOWNLOAD_UPDATE            2
#define ACTION_IS_SERVER_ALIVE            3
#define ACTION_CHECK_USER_DATA_FILE       4
#define ACTION_DOWNLOAD_USER_DATA_FILE    5
#define ACTION_UPLOAD_USER_DATA_FILE      6
#define ACTION_REMOVE_USER_DATA_FILE      7

#define EVENT_STATUS_OK                   0
#define EVENT_STATUS_UPDATE_AVAILABLE     1
#define EVENT_STATUS_UPDATE_NOT_AVAILABLE 2
#define EVENT_STATUS_UPDATE_DOWNLOADED    3
#define EVENT_STATUS_ERROR                99

#define PING_RESPONSE _T( "I am alive" )
#define UPLOAD_BUFFER_SIZE 1024

/******************************************************************************/

extern const wxEventType wxEVT_NEW_APP_AVAILABLE_EVENT;
extern const wxEventType wxEVT_NEW_APP_DOWNLOADED_EVENT;
extern const wxEventType wxEVT_SYNC_OPERATION_DONE_EVENT;

enum {
    THREAD_EVENT
};

WX_DECLARE_STRING_HASH_MAP( wxString, HeadersHashMap );

/******************************************************************************/

class wxHttpThread : public wxThread
{
public:
    wxHttpThread( wxWindow *parent, int actionType, wxString serverName, wxString inputData1, wxString inputData2, configClass *config, wxThreadKind threadKind)
        : wxThread(wxTHREAD_JOINABLE) {
        m_parent = parent;
        m_actionType = actionType;

        m_serverName = serverName;
        m_inputData = inputData1;
        m_inputData2 = inputData2;
        m_response = wxEmptyString;
        m_uploadSize = -1;
        m_uploadedSoFar = -1;
        m_inputStramReady = false;

        m_address = wxEmptyString;
        m_host = wxEmptyString;
        m_port = 80;
        m_path = wxEmptyString;
        m_currentAction = _T("?");

    }

    ~wxHttpThread();

    // thread execution starts here
    // connect to the updates page and check if new version of the application is available.
    virtual ExitCode Entry();

    // called when the thread exits - whether it terminates normally or is
    // stopped with Delete() (but not when it is Kill()ed!)
    virtual void OnExit();

private:
    ExitCode checkUpdateAvailability();
    ExitCode downloadUpdate();
    ExitCode checkIsServerAlive();
    ExitCode checkUserDataFile();
    ExitCode downloadUserDataFile();
    ExitCode uploadUserDataFile();
    ExitCode removeUserDataFile();

    void sendEventAvailable( int, wxString );
    void sendEventDownload( int, wxString );
    void sendEventSyncOperationDone( wxThread::ExitCode, wxString );

    bool parseServerName();
    bool openConnection();
    bool closeConnection();

    bool getInputStream();

    wxString get();

    wxString postFile(const wxString& fileToUploadPath, const wxString& fileToUploadName);
    wxString readResponse();
    HeadersHashMap readResponseHeaders();
    wxString readLine();
    wxString read(int bytestCount);

public:
    int getUploadDownloadSize();
    int getUploadedDownloadedSoFar();
private:
    int getUploadSize();
    int getUploadedSoFar();
    int getDownloadSize();
    int getDownloadedSoFar();

    bool isInputStramReady();
    void setInputStramReady(bool);

public:
    wxString getCurrentAction();
private:
    void setCurrentAction(wxString);


private:
    /** variables */
    wxWindow *m_parent;
    configClass *m_config;
    utilClass m_util;

    wxString m_serverName;
    wxString m_inputData;
    wxString m_inputData2;
    wxString m_response;
    int m_uploadSize;
    int m_uploadedSoFar;

    int m_actionType;
    wxHTTP *m_http;
    wxSocketClient *m_socket;
    wxInputStream *m_inputStream;
    wxFileOutputStream *m_fileOutputStream;

    wxString m_address;
    wxString m_host;
    int m_port;
    wxString m_path;

    wxCriticalSection gs_critSectionLocker1;
    bool m_inputStramReady;
    wxCriticalSection gs_critSectionLocker2;
    wxString m_currentAction;
};


#endif

#endif // header guard
