/*******************************************************************************
//
// Name:        liveUpdateClass.h
// Author:      enkeli
// Description:
//
*******************************************************************************/

#ifndef __LIVE_UPDATE_CLASS__
#define __LIVE_UPDATE_CLASS__

#include "configClass.h"
#include "utilClass.h"
#include <wx/wfstream.h>

#define EVENT_STATUS_UPDATE_AVAILABLE     1
#define EVENT_STATUS_UPDATE_NOT_AVAILABLE 2
#define EVENT_STATUS_UPDATE_DOWNLOADED    3
#define EVENT_STATUS_ERROR                10

/******************************************************************************/

extern const wxEventType wxEVT_NEW_APP_AVAILABLE_EVENT;
extern const wxEventType wxEVT_NEW_APP_DOWNLOADED_EVENT;


enum {
     THREAD_EVENT
};

/******************************************************************************/

class liveUpdateClass : public wxThread {
public:
     liveUpdateClass( wxWindow *parent, configClass *config, bool checkUpdates, wxString newAppSetupFileUrl = _T( "" ) );
     ~liveUpdateClass();

     // thread execution starts here
     // connect to the updates page and check if new version of the application is available.
     virtual void *Entry();

     // called when the thread exits - whether it terminates normally or is
     // stopped with Delete() (but not when it is Kill()ed!)
     virtual void OnExit();

     bool checkUpdateAvailability();
     bool downloadUpdate();
     void sendEventAvailable( int, wxString );
     void sendEventDownload( int, wxString );

     wxInputStream *getInputStream();
     wxFileOutputStream *getFileOutputStream();

private:
     wxWindow *m_parent;
     configClass *m_config;
     utilClass m_util;

     bool m_checkUpdates;
     wxString m_newAppSetupFileUrl;
     wxString m_newAppSetupFilePath;
     wxInputStream *m_inputStream;
     wxFileOutputStream *m_fileOutputStream;
};


#endif
