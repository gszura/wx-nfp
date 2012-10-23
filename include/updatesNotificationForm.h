/*******************************************************************************
//
// Name:        updatesNotificationForm.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef UPDATESNOTIFICATIONFORM_H
#define UPDATESNOTIFICATIONFORM_H

//(*Headers(updatesNotificationForm)
#include <wx/gauge.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/timer.h>
//*)

#include "configClass.h"
#include "utilClass.h"
#include "wxHttpThread.h"

/******************************************************************************/

class updatesNotificationForm: public wxFrame
{
public:

    updatesNotificationForm(wxWindow* parent,configClass *config, wxString newAppSetupFileUrl, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);

    virtual ~updatesNotificationForm();

    //(*Declarations(updatesNotificationForm)
    wxTimer timer;
    wxStaticText* staticUpdateAvailable;
    wxGauge* gauge;
    wxButton* buttonLater;
    wxButton* buttonInstall;
    //*)

protected:

    //(*Identifiers(updatesNotificationForm)
    static const long ID_staticUpdateAvailable;
    static const long ID_GAUGE;
    static const long ID_buttonInstall;
    static const long ID_buttonLater;
    static const long ID_TIMER;
    //*)

private:
    wxWindow *m_parent;
    configClass *m_config;
    wxString m_newAppSetupFileUrl;
    wxHttpThread *m_checkUpdatesThread;


    void CreateGUIControls( wxWindow *parent, wxWindowID id );

    //(*Handlers(updatesNotificationForm)
    void onClose(wxCloseEvent& event);
    void buttonInstallClick(wxCommandEvent& event);
    void buttonLaterClick(wxCommandEvent& event);
    void timerTrigger(wxTimerEvent& event);
    //*)

    void newAppDownloadedEvent( wxCommandEvent& event);

    DECLARE_EVENT_TABLE()
};

#endif
