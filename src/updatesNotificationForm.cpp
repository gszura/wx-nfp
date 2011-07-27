/*******************************************************************************
//
// Name:        updatesNotificationForm.cpp
// Author:      enkeli
// Description:
//
*******************************************************************************/

#include "updatesNotificationForm.h"
#include "../data/xpm/wx-nfp.xpm"

BEGIN_EVENT_TABLE( updatesNotificationForm, wxFrame )
     EVT_CLOSE( updatesNotificationForm::updatesNotificationFormClose )
     EVT_BUTTON( ID_BUTTONLATER, updatesNotificationForm::buttonLaterClick )
     EVT_BUTTON( ID_BUTTONINSTALL, updatesNotificationForm::buttonInstallClick )
     EVT_COMMAND( THREAD_EVENT, wxEVT_NEW_APP_DOWNLOADED_EVENT, updatesNotificationForm::newAppDownloadedEvent )
     EVT_TIMER( ID_TIMERUPDATES, updatesNotificationForm::timerUpdatesTimer )
END_EVENT_TABLE()

/******************************************************************************/

/**
 *
 */
updatesNotificationForm::updatesNotificationForm( wxWindow *parent, configClass *config, wxString newAppSetupFileUrl, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style )
     : wxFrame( parent, id, title, position, size, style )
{
     m_parent = parent;
     m_config = config;
     m_newAppSetupFileUrl = newAppSetupFileUrl;
     CreateGUIControls();
}

/**
 *
 */
updatesNotificationForm::~updatesNotificationForm() {}

/**
 *
 */
void updatesNotificationForm::CreateGUIControls( void )
{
     int flatButton = 0;
     if ( m_config->useFlatButtons ) {
          flatButton = wxNO_BORDER;
     }

     WxBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
     this->SetSizer( WxBoxSizer1 );
     this->SetAutoLayout( true );

     WxPanel1 = new wxPanel( this, ID_WXPANEL1, wxPoint( 0, 0 ), wxSize( 340, 169 ) );
     WxBoxSizer1->Add( WxPanel1, 1, wxEXPAND | wxALL, 0 );

     WxBoxSizer2 = new wxBoxSizer( wxVERTICAL );
     WxPanel1->SetSizer( WxBoxSizer2 );
     WxPanel1->SetAutoLayout( true );

     staticUpdateAvailable = new wxStaticText( WxPanel1, ID_STATICUPDATEAVAILABLE, _( "New version of the application is available.\n-To download and install it, press 'download and install' button.\n-If you don't want to install it now, press 'remind me later' button." ), wxPoint( 15, 5 ), wxSize( 300, 58 ), wxALIGN_LEFT | wxST_NO_AUTORESIZE, _T( "staticUpdateAvailable" ) );
     WxBoxSizer2->Add( staticUpdateAvailable, 1, wxEXPAND | wxALL, 5 );

     gauge = new wxGauge( WxPanel1, ID_GAUGE, 100, wxPoint( 57, 73 ), wxSize( 216, 25 ), wxGA_HORIZONTAL | wxGA_SMOOTH, wxDefaultValidator, _T( "gauge" ) );
     gauge->SetRange( 100 );
     gauge->SetValue( 0 );
     WxBoxSizer2->Add( gauge, 0, wxEXPAND | wxALL, 5 );

     WxBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
     WxBoxSizer2->Add( WxBoxSizer3, 0, wxALIGN_CENTER | wxALL, 5 );

     buttonInstall = new wxButton( WxPanel1, ID_BUTTONINSTALL, _( "Download and install" ), wxPoint( 5, 5 ), wxSize( 150, 22 ), flatButton, wxDefaultValidator, _T( "buttonInstall" ) );
     buttonInstall->SetDefault();
     WxBoxSizer3->Add( buttonInstall, 0, wxALIGN_CENTER | wxALL, 10 );

     buttonLater = new wxButton( WxPanel1, ID_BUTTONLATER, _( "Remind me later" ), wxPoint( 165, 5 ), wxSize( 150, 22 ), flatButton, wxDefaultValidator, _T( "buttonLater" ) );
     WxBoxSizer3->Add( buttonLater, 0, wxALIGN_CENTER | wxALL, 10 );

     timerUpdates = new wxTimer();
     timerUpdates->SetOwner( this, ID_TIMERUPDATES );

     SetTitle( _( "NFP - new version is available" ) );
     SetSize( wxSystemSettings::GetMetric( wxSYS_SCREEN_X ) - 350, 10, -1, -1 );
     wxIcon wx_nfp_ICON( wx_nfp_xpm );
     SetIcon( wx_nfp_ICON );
}

/******************************************************************************/

/**
 *
 */
void updatesNotificationForm::updatesNotificationFormClose( wxCloseEvent& event )
{
     Destroy();
}

/**
 * buttonInstallClick
 */
void updatesNotificationForm::buttonInstallClick( wxCommandEvent& event )
{
     m_checkUpdatesThread = new liveUpdateClass( this, m_config, false, m_newAppSetupFileUrl );
     if ( m_checkUpdatesThread->Create() != wxTHREAD_NO_ERROR ) {
          // ...
     }
     if ( m_checkUpdatesThread->Run() != wxTHREAD_NO_ERROR ) {
          // ...
     }
     buttonInstall->Enable( false );
     staticUpdateAvailable->SetLabel( _("Application installer is downloading.\nDuring that time you can continue your work with the application.") );
     timerUpdates->Start( 300 );
}

/**
 * buttonLaterClick
 */
void updatesNotificationForm::buttonLaterClick( wxCommandEvent& event )
{
     timerUpdates->Stop();
     Close();
}

/**
 *
 */
void updatesNotificationForm::newAppDownloadedEvent( wxCommandEvent& event )
{
     timerUpdates->Stop();
     event.Skip();
     Close();
}

/**
 * timerUpdatesTimer
 */
void updatesNotificationForm::timerUpdatesTimer( wxTimerEvent& event )
{
     if ( m_checkUpdatesThread != NULL ) {
          if ( m_checkUpdatesThread->getInputStream() != NULL ) {
               int s = m_checkUpdatesThread->getInputStream()->GetSize();
               if ( gauge->GetRange() != s ) {
                    gauge->SetRange( s );
               }
          } else {

          }
          if ( m_checkUpdatesThread->getFileOutputStream() != NULL ) {
               int s = m_checkUpdatesThread->getFileOutputStream()->GetSize();
               wxString x = _( "downloaded already: " );
               x << s;

               gauge->SetValue( s );
          } else {

          }
     } else {

     }

}
/******************************************************************************/

