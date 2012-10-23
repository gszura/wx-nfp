/*******************************************************************************
//
// Name:        printFrame.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "../data/xpm/wx_nfp.xpm"
#include "printFrame.h"

/******************************************************************************/
BEGIN_EVENT_TABLE( printFrame, wxDialog )
     EVT_CLOSE( printFrame::OnClose )
     EVT_BUTTON( ID_BUTTONOK, printFrame::buttonOkClick )
     EVT_BUTTON( ID_BUTTONCANCEL, printFrame::buttonCancelClick )

     EVT_CHECKBOX( ID_CHECKBOXPRINTCARDS, printFrame::checkBoxPrintCardsClick )
     EVT_RADIOBUTTON( ID_RADIOBUTTONPRINTCURRENTCARD, printFrame::radioButtonPrintCurrentCardClick )
     EVT_RADIOBUTTON( ID_RADIOBUTTONPRINTALLCARDS, printFrame::radioButtonPrintAllCardsClick )
     EVT_RADIOBUTTON( ID_RADIOBUTTONPRINTSELECTEDCARDS, printFrame::radioButtonPrintSelectedCardsClick )
     EVT_TEXT( ID_SPINFIRSTCARD, printFrame::spinFirstCardTextUpdated )
     EVT_TEXT( ID_SPINLASTCARD, printFrame::spinLastCardTextUpdated )
     EVT_CHECKBOX( ID_CHECKBOXPRINTLEGEND, printFrame::checkBoxPrintLegendClick )
END_EVENT_TABLE()


/******************************************************************************/

/**
 *
 */
printFrame::printFrame( wxWindow *parent, configClass *config, int firstCard, int lastCard, int activeCard, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style )
     : wxDialog( parent, id, title, position, size, style )
{
     m_config = config;
     m_activeCard = activeCard;

     CreateGUIControls();

     checkBoxPrintCards->SetValue( true );
     checkBoxPrintLegend->SetValue( false );
     spinFirstCard->SetRange( firstCard, lastCard );
     spinFirstCard->SetValue( activeCard );
     spinLastCard->SetRange( firstCard, lastCard );
     spinLastCard->SetValue( activeCard );
     radioButtonPrintCurrentCard->SetValue( true );
     radioButtonPrintAllCards->SetValue( false );
     radioButtonPrintSelectedCards->SetValue( false );
     radioButtonClicked = false;
}

/**
 *
 */
printFrame::~printFrame()
{
}

/**
 *
 */
void printFrame::CreateGUIControls()
{
     WxBoxSizerMain = new wxBoxSizer( wxVERTICAL );
     this->SetSizer( WxBoxSizerMain );
     this->SetAutoLayout( true );

     WxBoxSizerPrintCards = new wxBoxSizer( wxHORIZONTAL );
     WxBoxSizerMain->Add( WxBoxSizerPrintCards, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5 );

     checkBoxPrintCards = new wxCheckBox( this, ID_CHECKBOXPRINTCARDS, _( "Print cycles' cards:" ), wxPoint( 5, 5 ), wxSize( 250, 17 ), 0, wxDefaultValidator, _T( "checkBoxPrintCards" ) );
     WxBoxSizerPrintCards->Add( checkBoxPrintCards, 0, wxALIGN_LEFT | wxALL, 5 );

     WxBoxSizerPrintCurrentCard = new wxBoxSizer( wxHORIZONTAL );
     WxBoxSizerMain->Add( WxBoxSizerPrintCurrentCard, 0, wxEXPAND | wxLEFT | wxRIGHT, 5 );

     staticText1 = new wxStaticText( this, ID_STATICTEXT1, _T( "" ), wxPoint( 5, 0 ), wxSize( 20, 17 ), wxST_NO_AUTORESIZE, _T( "staticText1" ) );
     WxBoxSizerPrintCurrentCard->Add( staticText1, 0, wxALIGN_LEFT | wxLEFT | wxBOTTOM, 5 );

     radioButtonPrintCurrentCard = new wxRadioButton( this, ID_RADIOBUTTONPRINTCURRENTCARD, _( "Current card" ), wxPoint( 25, 0 ), wxSize( 200, 17 ), 0, wxDefaultValidator, _T( "radioButtonPrintCurrentCard" ) );
     WxBoxSizerPrintCurrentCard->Add( radioButtonPrintCurrentCard, 0, wxALIGN_LEFT | wxRIGHT | wxBOTTOM, 5 );

     WxBoxSizerPrintAllCards = new wxBoxSizer( wxHORIZONTAL );
     WxBoxSizerMain->Add( WxBoxSizerPrintAllCards, 0, wxEXPAND | wxLEFT | wxRIGHT, 5 );

     staticText2 = new wxStaticText( this, ID_STATICTEXT2, _T( "" ), wxPoint( 5, 0 ), wxSize( 20, 17 ), wxST_NO_AUTORESIZE, _T( "staticText2" ) );
     WxBoxSizerPrintAllCards->Add( staticText2, 0, wxALIGN_LEFT | wxLEFT | wxBOTTOM, 5 );

     radioButtonPrintAllCards = new wxRadioButton( this, ID_RADIOBUTTONPRINTALLCARDS, _( "All cards" ), wxPoint( 25, 0 ), wxSize( 200, 17 ), 0, wxDefaultValidator, _T( "radioButtonPrintAllCards" ) );
     WxBoxSizerPrintAllCards->Add( radioButtonPrintAllCards, 0, wxALIGN_LEFT | wxRIGHT | wxBOTTOM, 5 );

     WxBoxSizerPrintSelectedCards = new wxBoxSizer( wxHORIZONTAL );
     WxBoxSizerMain->Add( WxBoxSizerPrintSelectedCards, 0, wxEXPAND | wxLEFT | wxRIGHT, 5 );

     staticText3 = new wxStaticText( this, ID_STATICTEXT3, _T( "" ), wxPoint( 5, 2 ), wxSize( 20, 17 ), wxST_NO_AUTORESIZE, _T( "staticText3" ) );
     WxBoxSizerPrintSelectedCards->Add( staticText3, 0, wxALIGN_LEFT | wxLEFT | wxBOTTOM, 5 );

     radioButtonPrintSelectedCards = new wxRadioButton( this, ID_RADIOBUTTONPRINTSELECTEDCARDS, _( "Selected cards" ), wxPoint( 25, 2 ), wxSize( 150, 17 ), 0, wxDefaultValidator, _T( "radioButtonPrintSelectedCards" ) );
     WxBoxSizerPrintSelectedCards->Add( radioButtonPrintSelectedCards, 0, wxALIGN_LEFT | wxRIGHT | wxBOTTOM, 5 );

     spinFirstCard = new wxSpinCtrl( this, ID_SPINFIRSTCARD, _T( "999" ), wxPoint( 180, 0 ), wxSize( 50, 22 ), wxSP_ARROW_KEYS, 0, 999, 999 );
     WxBoxSizerPrintSelectedCards->Add( spinFirstCard, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 5 );

     staticText4 = new wxStaticText( this, ID_STATICTEXT4, _T( "-" ), wxPoint( 235, 2 ), wxDefaultSize, wxALIGN_CENTRE, _T( "staticText4" ) );
     WxBoxSizerPrintSelectedCards->Add( staticText4, 0, wxALIGN_LEFT | wxRIGHT | wxBOTTOM, 5 );

     spinLastCard = new wxSpinCtrl( this, ID_SPINLASTCARD, _T( "999" ), wxPoint( 260, 0 ), wxSize( 50, 22 ), wxSP_ARROW_KEYS, 0, 999, 999 );
     WxBoxSizerPrintSelectedCards->Add( spinLastCard, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 5 );

     WxBoxSizerPrintLegend = new wxBoxSizer( wxHORIZONTAL );
     WxBoxSizerMain->Add( WxBoxSizerPrintLegend, 0, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 5 );

     checkBoxPrintLegend = new wxCheckBox( this, ID_CHECKBOXPRINTLEGEND, _( "Print legend (description of abbreviations)" ), wxPoint( 5, 5 ), wxSize( 250, 17 ), 0, wxDefaultValidator, _T( "checkBoxPrintLegend" ) );
     WxBoxSizerPrintLegend->Add( checkBoxPrintLegend, 0, wxALIGN_LEFT | wxALL, 5 );

     WxBoxSizerButtons = new wxBoxSizer( wxHORIZONTAL );
     WxBoxSizerMain->Add( WxBoxSizerButtons, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5 );

     buttonOk = new wxButton( this, ID_BUTTONOK, _( "OK" ), wxPoint( 5, 5 ), wxSize( 75, 25 ), 0, wxDefaultValidator, _T( "buttonOk" ) );
     WxBoxSizerButtons->Add( buttonOk, 0, wxALIGN_CENTER | wxALL, 5 );

     buttonCancel = new wxButton( this, ID_BUTTONCANCEL, _( "Cancel" ), wxPoint( 90, 5 ), wxSize( 75, 25 ), 0, wxDefaultValidator, _T( "buttonCancel" ) );
     WxBoxSizerButtons->Add( buttonCancel, 0, wxALIGN_CENTER | wxALL, 5 );

     /*******************************************************************/

     checkBoxPrintCards->SetToolTip( _( "Select this if you want to print cycles' cards" ) );
     radioButtonPrintCurrentCard->SetToolTip( _( "Print only current card" ) );
     radioButtonPrintAllCards->SetToolTip( _( "Print all cards from the set" ) );
     radioButtonPrintSelectedCards->SetToolTip( _( "Print cards from defined range" ) );
     spinFirstCard->SetToolTip( _( "First card to print" ) );
     spinLastCard->SetToolTip( _( "Last card to print" ) );
     checkBoxPrintLegend->SetToolTip( _( "Select this if you want to print description of abbreviations used on cycles' card.\nLegend will be printed on a separate page." ) );
     buttonOk->SetToolTip( _( "Print choosen cards" ) );
     buttonCancel->SetToolTip( _( "Cancel printing and close this window" ) );

     /*******************************************************************/

     SetTitle( _("NFP - print cards..") );
     wxIcon wx_nfp_ICON( wx_nfp_xpm );
     SetIcon( wx_nfp_ICON );

     GetSizer()->Fit( this );
     GetSizer()->SetSizeHints( this );
     Center();

     SetAffirmativeId( ID_BUTTONOK );
     SetEscapeId( ID_BUTTONCANCEL );
     buttonOk->SetDefault();
}

/******************************************************************************/

/**
 *
 */
void printFrame::OnClose( wxCloseEvent& /*event*/ )
{
     this->EndModal( 0 );
     Destroy();
}

/**
 * buttonOkClick
 */
void printFrame::buttonOkClick( wxCommandEvent& event )
{



     int ret = 0;

     if ( checkBoxPrintLegend->GetValue() ) {
          ret = 1000000;
     }

     if ( checkBoxPrintCards->GetValue() ) {
          ret += 1000 * spinFirstCard->GetValue();
          ret += spinLastCard->GetValue();
     }

     this->EndModal( ret );
}

/**
 * buttonCancelClick
 */
void printFrame::buttonCancelClick( wxCommandEvent& event )
{
     this->EndModal( 0 );
}

/******************************************************************************/

/**
 * checkBoxPrintCardsClick
 */
void printFrame::checkBoxPrintCardsClick( wxCommandEvent& event )
{
     if ( checkBoxPrintCards->IsChecked() || checkBoxPrintLegend->IsChecked() )
          buttonOk->Enable( true );
     else
          buttonOk->Enable( false );

     if ( checkBoxPrintCards->IsChecked() ) {
          radioButtonPrintCurrentCard->Enable( true );
          radioButtonPrintAllCards->Enable( true );
          radioButtonPrintSelectedCards->Enable( true );
          spinFirstCard->Enable( true );
          spinLastCard->Enable( true );
     } else {
          radioButtonPrintCurrentCard->Enable( false );
          radioButtonPrintAllCards->Enable( false );
          radioButtonPrintSelectedCards->Enable( false );
          spinFirstCard->Enable( false );
          spinLastCard->Enable( false );
     }
}

/**
 * radioButtonPrintCurrentCardClick
 */
void printFrame::radioButtonPrintCurrentCardClick( wxCommandEvent& event )
{
     radioButtonClicked = true;
     spinFirstCard->SetValue( m_activeCard );
     spinLastCard->SetValue( m_activeCard );
     radioButtonClicked = false;
}

/**
 * radioButtonPrintAllCardsClick
 */
void printFrame::radioButtonPrintAllCardsClick( wxCommandEvent& event )
{
     radioButtonClicked = true;
     spinFirstCard->SetValue( spinFirstCard->GetMin() );
     spinLastCard->SetValue( spinLastCard->GetMax() );
     radioButtonClicked = false;
}

/**
 * radioButtonPrintSelectedCardsClick
 */
void printFrame::radioButtonPrintSelectedCardsClick( wxCommandEvent& event )
{
     // nothing to do
}

/**
 * spinFirstCardTextUpdated
 */
void printFrame::spinFirstCardTextUpdated( wxCommandEvent& event )
{
     if ( !radioButtonClicked && !radioButtonPrintSelectedCards->GetValue() ) {
          radioButtonPrintSelectedCards->SetValue( true );

          if ( spinFirstCard->GetValue() > spinLastCard->GetValue() )
               spinLastCard->SetValue( spinFirstCard->GetValue() );
     }
}

/**
 * spinLastCardTextUpdated
 */
void printFrame::spinLastCardTextUpdated( wxCommandEvent& event )
{
     if ( !radioButtonClicked && !radioButtonPrintSelectedCards->GetValue() ) {
          radioButtonPrintSelectedCards->SetValue( true );

          if ( spinFirstCard->GetValue() > spinLastCard->GetValue() )
               spinFirstCard->SetValue( spinLastCard->GetValue() );
     }
}

/**
 * checkBoxPrintLegendClick
 */
void printFrame::checkBoxPrintLegendClick( wxCommandEvent& event )
{
     if ( checkBoxPrintCards->IsChecked() || checkBoxPrintLegend->IsChecked() )
          buttonOk->Enable( true );
     else
          buttonOk->Enable( false );
}

/******************************************************************************/
