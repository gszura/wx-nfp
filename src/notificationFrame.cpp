/*******************************************************************************
//
// Name:        notificationFrame.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "notificationFrame.h"

/******************************************************************************/

BEGIN_EVENT_TABLE( notificationFrame, wxDialog )
    EVT_CLOSE( notificationFrame::OnClose )
    EVT_BUTTON( ID_buttonClose, notificationFrame::buttonCloseClick )
END_EVENT_TABLE()

/******************************************************************************/
/**
 *
 */
notificationFrame::notificationFrame( wxWindow *parent, configClass *config, const wxString& message, int textAlign, const wxPoint& pos, bool hideOnClose, const wxSize& size, wxWindowID id, const wxString &title, long style )
    : wxDialog( parent, id, title, pos, size, style )
{
    m_config = config;
    m_hideOnClose = hideOnClose;
    CreateGUIControls(message, textAlign);
}

/**
 *
 */
notificationFrame::~notificationFrame()
{
}

/**
 *
 */
void notificationFrame::CreateGUIControls(const wxString& message, int textAlign)
{
    sizer1 = new wxBoxSizer( wxHORIZONTAL );
    this->SetSizer( sizer1 );
    this->SetAutoLayout( true );

    panel1 = new wxPanel( this, ID_panel1, wxPoint( 0, 0 ) );
    panel1->SetBackgroundColour( wxColour( m_config->colourBackground ) );
    sizer1->Add( panel1, 1, wxEXPAND | wxALL, 0 );

    sizer2 = new wxBoxSizer( wxVERTICAL );
    panel1->SetSizer( sizer2 );
    panel1->SetAutoLayout( true );

    text1 = new wxStaticText( panel1, ID_text1, message, wxPoint( 5, 5 ), wxDefaultSize, textAlign | wxST_NO_AUTORESIZE, _T( "text1" ) );
    text1->SetForegroundColour( wxColour( 128, 0, 0 ) );
    text1->SetFont( wxFont( 9, wxSWISS, wxNORMAL, wxBOLD, FALSE ) );
    sizer2->Add( text1, 0, wxEXPAND | wxALL, 5 );

    buttonClose = new wxButton( panel1, ID_buttonClose, _( "Close" ), wxPoint( 5, 95 ), wxDefaultSize, wxNO_BORDER, wxDefaultValidator, _T( "buttonClose" ) );
    buttonClose->SetBackgroundColour( wxColour( m_config->colourBackground ) );
    buttonClose->SetForegroundColour( wxColour( 128, 0, 0 ) );
    buttonClose->SetFont( wxFont( 9, wxSWISS, wxNORMAL, wxBOLD, FALSE ) );
    sizer2->Add( buttonClose, 0, wxALIGN_CENTER | wxALL, 5 );

    SetTitle( _( "NFP - notification" ) );
    SetIcon( wxNullIcon );

    GetSizer()->Fit( this );
    GetSizer()->SetSizeHints( this );
    //Center();

    SetAffirmativeId( ID_buttonClose );
    SetEscapeId( ID_buttonClose );
    //buttonClose->SetDefault();
}


/**
 *
 */
void notificationFrame::setMessage( wxString message )
{
    text1->SetLabel(message);
    this->Refresh();
    this->Update();
    this->Show();
}

/**
 *
 */
void notificationFrame::OnClose( wxCloseEvent& /*event*/ )
{
    if (m_hideOnClose)
        Hide();
    else
        Destroy();
}

/**
 * buttonCloseClick
 */
void notificationFrame::buttonCloseClick( wxCommandEvent& event )
{
    if (m_hideOnClose)
        Hide();
    else
        Destroy();
}
