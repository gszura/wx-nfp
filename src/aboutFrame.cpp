/*******************************************************************************
//
// Name:        aboutFrame.cpp
// Author:      enkeli
// Description:
//
*******************************************************************************/

#include "aboutFrame.h"
#include "wx-nfpAppInfo.h"
#include "wx-nfpAppVersion.h"
#include "wx-nfpApp.h"
#include "../data/xpm/splash_screen.xpm"

BEGIN_EVENT_TABLE( aboutFrame, wxDialog )
     EVT_CLOSE( aboutFrame::aboutFrameClose )
     EVT_BUTTON( ID_BUTTONCLOSE, aboutFrame::buttonCloseClick )
     EVT_BUTTON( ID_BUTTONUPDATE, aboutFrame::buttonUpdateClick )
     EVT_TIMER( ID_TIMER1, aboutFrame::timer1Timer )
END_EVENT_TABLE()

/*******************************************************************************
********************************************************************************
*******************************************************************************/

aboutFrame::aboutFrame( wxWindow *parent, wxString fileToOpen, configClass *config, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style )
     : wxDialog( parent, id, title, position, size, style )
{
     m_config = config;

     CreateGUIControls();
     buttonUpdate->Enable( false );
     Refresh();

     if ( ! fileToOpen.IsEmpty() ) {
          m_config->dataFileName = fileToOpen;
          m_config->openFileFromParams = true;

     }

     m_timeTics = 0;
     timer1->Start( 200 );
}

/**
 *
 */
aboutFrame::~aboutFrame() {}

/******************************************************************************/

/**
 *
 */
void aboutFrame::CreateGUIControls( void )
{
     WxBoxSizer1 = new wxBoxSizer( wxVERTICAL );
     this->SetSizer( WxBoxSizer1 );
     this->SetAutoLayout( true );

     WxPanel1 = new wxPanel( this, ID_WXPANEL1, wxPoint( 0, 0 ), wxSize( 400, 406 ) );
     WxPanel1->SetBackgroundColour( wxColour( *wxWHITE ) );
     WxBoxSizer1->Add( WxPanel1, 1, wxALIGN_CENTER | wxALL, 0 );

     WxBoxSizer2 = new wxBoxSizer( wxVERTICAL );
     WxPanel1->SetSizer( WxBoxSizer2 );
     WxPanel1->SetAutoLayout( true );

     wxBitmap WxStaticBitmap1_BITMAP( splash_screen_xpm );
     WxStaticBitmap1 = new wxStaticBitmap( WxPanel1, ID_WXSTATICBITMAP1, WxStaticBitmap1_BITMAP, wxPoint( 0, 0 ), wxSize( 400, 235 ) );
     WxStaticBitmap1->Enable( false );
     WxBoxSizer2->Add( WxStaticBitmap1, 1, wxALIGN_CENTER | wxALL, 0 );

     staticNfp = new wxStaticText( WxPanel1, ID_STATIC_NFP, _( "Natural Family Planing" ), wxPoint( 0, 240 ), wxDefaultSize, wxALIGN_CENTRE, wxT( "staticNfp" ) );
     staticNfp->SetForegroundColour( wxColour( 128, 0, 0 ) );
     staticNfp->SetFont( wxFont( 14, wxSWISS, wxNORMAL, wxNORMAL, FALSE ) );
     WxBoxSizer2->Add( staticNfp, 0, wxALIGN_CENTRE | wxALL, 5 );

     staticCycleObservationCard = new wxStaticText( WxPanel1, ID_STATIC_COC, _( "Cycle observation cards" ), wxPoint( 0, 278 ), wxDefaultSize, wxALIGN_CENTRE, wxT( "staticCycleObservationCard" ) );
     staticCycleObservationCard->SetForegroundColour( wxColour( 128, 0, 0 ) );
     staticCycleObservationCard->SetFont( wxFont( 12, wxSWISS, wxNORMAL, wxBOLD, FALSE ) );
     WxBoxSizer2->Add( staticCycleObservationCard, 0, wxALIGN_CENTRE | wxALL, 0 );

     WxBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
     WxBoxSizer2->Add( WxBoxSizer3, 0, wxEXPAND | wxALL, 5 );

     staticHomeUrl = new wxHyperlinkCtrl( WxPanel1, ID_STATIC_HOME_URL, HOME_URL, wxString::Format( _T( "%s?l=en" ), HOME_URL ), wxPoint( 5, 5 ), wxDefaultSize, wxNO_BORDER | wxHL_ALIGN_LEFT | wxHL_CONTEXTMENU, wxT( "staticHomeUrl" ) );
     staticHomeUrl->SetHoverColour( *wxRED );
     staticHomeUrl->SetNormalColour( *wxBLUE );
     staticHomeUrl->SetVisitedColour( *wxBLUE );
     staticHomeUrl->SetFont( wxFont( 8, wxSWISS, wxNORMAL, wxNORMAL, TRUE ) );
     WxBoxSizer3->Add( staticHomeUrl, 1, wxALIGN_LEFT | wxALL, 0 );

     wxString version = wxString::Format( _( "version: %d.%d (build %d, %s-%s-%s)" ), AutoVersion::MAJOR, AutoVersion::MINOR, AutoVersion::BUILD, wxString(AutoVersion::YEAR, wxConvUTF8).c_str(), wxString(AutoVersion::MONTH, wxConvUTF8).c_str(), wxString(AutoVersion::DATE, wxConvUTF8).c_str() );
     staticAppVersion = new wxStaticText( WxPanel1, ID_STATIC_APP_VERSION, version, wxPoint( 115, 5 ), wxDefaultSize, wxALIGN_RIGHT, wxT( "staticAppVersion" ) );
     staticAppVersion->SetForegroundColour( wxColour( 128, 0, 0 ) );
     WxBoxSizer3->Add( staticAppVersion, 1, wxALIGN_RIGHT | wxALL, 0 );

     WxBoxSizer4 = new wxBoxSizer( wxHORIZONTAL );
     WxBoxSizer2->Add( WxBoxSizer4, 0, wxEXPAND | wxALL, 0 );

     int flatButton = 0;
     if ( m_config->useFlatButtons ) {
          flatButton = wxNO_BORDER;
     }

     buttonUpdate = new wxButton( WxPanel1, ID_BUTTONUPDATE, _( "check for updates..." ), wxPoint( 5, 5 ), wxSize( 90, 22 ), flatButton, wxDefaultValidator, wxT( "buttonUpdate" ) );
     buttonUpdate->SetBackgroundColour( wxColour( *wxWHITE ) );
     WxBoxSizer4->Add( buttonUpdate, 1, wxALIGN_RIGHT | wxALL, 5 );
     buttonUpdate->SetToolTip( _( "Check if there is a new version of the application to download.." ) );

     buttonClose = new wxButton( WxPanel1, ID_BUTTONCLOSE,  _( "close" ), wxPoint( 105, 5 ), wxSize( 90, 22 ), flatButton, wxDefaultValidator, wxT( "buttonClose" ) );
     buttonClose->SetBackgroundColour( wxColour( *wxWHITE ) );
     WxBoxSizer4->Add( buttonClose, 1, wxALIGN_RIGHT | wxALL, 5 );

     timer1 = new wxTimer();
     timer1->SetOwner( this, ID_TIMER1 );

     SetTitle( _( "Natural Family Planing" ) );
     SetIcon( wxNullIcon );

     GetSizer()->Fit( this );
     GetSizer()->SetSizeHints( this );
     Center();

     SetEscapeId( ID_BUTTONCLOSE );
}

/******************************************************************************/

/**
 *
 */
void aboutFrame::aboutFrameClose( wxCloseEvent& event )
{
     Destroy();
}

/******************************************************************************/

/**
 * buttonCloseClick
 */
void aboutFrame::buttonCloseClick( wxCommandEvent& event )
{
     Hide();
}

/**
 * buttonUpdateClick
 */
void aboutFrame::buttonUpdateClick( wxCommandEvent& event )
{
     m_mainFrame->checkForUpdates( true );
     buttonUpdate->Enable( false );
}

/******************************************************************************/

/**
 * timer1Timer
 */
void aboutFrame::timer1Timer( wxTimerEvent& event )
{
     m_timeTics++;
     if ( m_timeTics == 1 ) {

          m_mainFrame = new nfpMainFrame( this, m_config );
          m_mainFrame->Show( true );
          m_mainFrame->setFocusOnCardFrm();
     } else if ( m_timeTics == 12 ) {

          timer1->Stop();
          buttonUpdate->Enable( true );
          Hide();
     }
}

/**
 *
 */
void aboutFrame::setButtonsStyle()
{
     int flatButton = 0;
     if ( m_config->useFlatButtons ) {
          flatButton = wxNO_BORDER;
     }

     buttonUpdate->SetWindowStyle( flatButton );
     buttonClose->SetWindowStyle( flatButton );

     buttonUpdate->Refresh();
     buttonClose->Refresh();
}


/*******************************************************************************
********************************************************************************
*******************************************************************************/
