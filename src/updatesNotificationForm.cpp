/*******************************************************************************
//
// Name:        updatesNotificationForm.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "updatesNotificationForm.h"
#include "../data/xpm/wx_nfp.xpm"

//(*InternalHeaders(updatesNotificationForm)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(updatesNotificationForm)
const long updatesNotificationForm::ID_staticUpdateAvailable = wxNewId();
const long updatesNotificationForm::ID_GAUGE = wxNewId();
const long updatesNotificationForm::ID_buttonInstall = wxNewId();
const long updatesNotificationForm::ID_buttonLater = wxNewId();
const long updatesNotificationForm::ID_TIMER = wxNewId();
//*)

BEGIN_EVENT_TABLE(updatesNotificationForm,wxFrame)
    EVT_COMMAND( THREAD_EVENT, wxEVT_NEW_APP_DOWNLOADED_EVENT, updatesNotificationForm::newAppDownloadedEvent )
    //(*EventTable(updatesNotificationForm)
    //*)
END_EVENT_TABLE()

/**
 *
 */
updatesNotificationForm::updatesNotificationForm(wxWindow* parent, configClass *config, wxString newAppSetupFileUrl,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_parent = parent;
    m_config = config;
    m_newAppSetupFileUrl = newAppSetupFileUrl;
    CreateGUIControls(parent, id);
}

/**
 *
 */
updatesNotificationForm::~updatesNotificationForm() {}

/**
 *
 */
void updatesNotificationForm::CreateGUIControls( wxWindow *parent, wxWindowID id )
{
    //(*Initialize(updatesNotificationForm)
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer1;

    Create(parent, id, _("NFP - new version is available"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    SetClientSize(wxDefaultSize);
    Move(wxDefaultPosition);
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    staticUpdateAvailable = new wxStaticText(this, ID_staticUpdateAvailable, _("New version of the application is available.\n-To download and install it, press \'download and install\' button.\n-If you don\'t want to install it now, press \'remind me later\' button."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticUpdateAvailable"));
    BoxSizer1->Add(staticUpdateAvailable, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    gauge = new wxGauge(this, ID_GAUGE, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAUGE"));
    BoxSizer1->Add(gauge, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    buttonInstall = new wxButton(this, ID_buttonInstall, _("Download and install"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_buttonInstall"));
    BoxSizer2->Add(buttonInstall, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    buttonLater = new wxButton(this, ID_buttonLater, _("Remind me later"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_buttonLater"));
    BoxSizer2->Add(buttonLater, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    timer.SetOwner(this, ID_TIMER);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_buttonInstall,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&updatesNotificationForm::buttonInstallClick);
    Connect(ID_buttonLater,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&updatesNotificationForm::buttonLaterClick);
    Connect(ID_TIMER,wxEVT_TIMER,(wxObjectEventFunction)&updatesNotificationForm::timerTrigger);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&updatesNotificationForm::onClose);
    //*)

    int width, height;
    GetSize(&width, &height);
    SetSize( wxSystemSettings::GetMetric( wxSYS_SCREEN_X ) - width - 10, 10, wxDefaultCoord, wxDefaultCoord );
    wxIcon wx_nfp_ICON( wx_nfp_xpm );
    SetIcon( wx_nfp_ICON );
}

void updatesNotificationForm::onClose(wxCloseEvent& event)
{
    Destroy();
}

void updatesNotificationForm::buttonInstallClick(wxCommandEvent& event)
{
    m_checkUpdatesThread = new wxHttpThread(this, ACTION_DOWNLOAD_UPDATE, m_newAppSetupFileUrl, wxEmptyString, wxEmptyString, m_config, wxTHREAD_DETACHED);

    if ( m_checkUpdatesThread->Create() != wxTHREAD_NO_ERROR ) {
        // ...
    }
    if ( m_checkUpdatesThread->Run() != wxTHREAD_NO_ERROR ) {
        // ...
    }
    buttonInstall->Enable( false );
    staticUpdateAvailable->SetLabel( _("Application installer is downloading.\nDuring that time you can continue your work with the application.") );
    timer.Start( 200 );
}

void updatesNotificationForm::buttonLaterClick(wxCommandEvent& event)
{
    timer.Stop();
    Close();
}

void updatesNotificationForm::timerTrigger(wxTimerEvent& event)
{
    int range = m_checkUpdatesThread->getUploadDownloadSize();
    if (range < 0) {
        gauge->Pulse();
        return;
    }

    int value = m_checkUpdatesThread->getUploadedDownloadedSoFar();
    value = value * 100 / range;
    if (value < 0) value = 0;
    if (value > 100) value = 100;
    gauge->SetValue( value );
}

/**
 *
 */
void updatesNotificationForm::newAppDownloadedEvent( wxCommandEvent& event )
{
    m_checkUpdatesThread->Wait();
    timer.Stop();
    event.Skip();
    Close();
}
