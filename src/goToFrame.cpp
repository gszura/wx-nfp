/***************************************************************
 * Name:      goToFrame.cpp
 * Purpose:   Dialog for choosing the card to open
 * Author:    Grzegorz Szura (grzegorz@szura.net)
 * Created:   2010-03-09
 * Copyright: Grzegorz Szura (http://www.szura.net)
 * License:
 **************************************************************/

#include "goToFrame.h"
#include "../data/xpm/wx_nfp.xpm"

//(*InternalHeaders(goToFrame)
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

/******************************************************************************/

//(*IdInit(goToFrame)
const long goToFrame::ID_radioButtonCardNumber = wxNewId();
const long goToFrame::ID_spinCardNumber = wxNewId();
const long goToFrame::ID_radioButtonDate = wxNewId();
const long goToFrame::ID_datePickerDate = wxNewId();
const long goToFrame::ID_space1 = wxNewId();
const long goToFrame::ID_staticVaildDates = wxNewId();
const long goToFrame::ID_staticCard = wxNewId();
const long goToFrame::ID_textCard = wxNewId();
const long goToFrame::ID_staticDay = wxNewId();
const long goToFrame::ID_textDay = wxNewId();
const long goToFrame::ID_staticDate = wxNewId();
const long goToFrame::ID_textDate = wxNewId();
const long goToFrame::ID_buttonGoTo = wxNewId();
const long goToFrame::ID_buttonCancel = wxNewId();
const long goToFrame::ID_panel1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(goToFrame,wxDialog)
    //(*EventTable(goToFrame)
    //*)
END_EVENT_TABLE()

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
goToFrame::goToFrame(wxWindow* parent,configClass *config, cycleDataClass *cycleData, int focusIn, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_config = config;
    m_cycleData = cycleData;

    buildGui(parent);

    if ( focusIn == GOTO_CARD ) {
        radioButtonCardNumber->SetValue( true );
        radioButtonDate->SetValue( false );
        spinCardNumber->SetFocus();
        spinCardNumber->SetSelection( -1, -1 );
    } else {
        radioButtonCardNumber->SetValue( false );
        radioButtonDate->SetValue( true );
        datePickerDate->SetFocus();
    }

    spinCardNumber->SetRange( 1, m_cycleData->getCardsCount() );
    spinCardNumber->SetValue( m_cycleData->getActiveCard() );

    wxDateTime firstDay = m_cycleData->getCard( 1 )->getFirstDayOfCycle();
    wxDateTime lastDay = m_cycleData->getCard( m_cycleData->getCardsCount() )->getFirstDayOfCycle();
    lastDay.Add( wxDateSpan::Days( m_cycleData->getCard( m_cycleData->getCardsCount() )->getDaysCount() - 1 ) );
    datePickerDate->SetRange( firstDay, lastDay );

    wxDateTime currentDay = m_cycleData->getCard()->getFirstDayOfCycle();
    if ( m_cycleData->getActiveDay() > 0 ) {
        currentDay.Add( wxDateSpan::Days( m_cycleData->getActiveDay() - 1 ) );
    }
    datePickerDate->SetValue( currentDay );

    staticVaildDates->SetLabel( wxString::Format( _( "Vaild dates: %s - %s" ), firstDay.Format( _T( "%Y-%m-%d" ) ).c_str(), lastDay.Format( _T( "%Y-%m-%d" ) ).c_str() ) );
    textCard->SetLabel( m_util.intToStr( m_cycleData->getActiveCard() ) );
    if ( m_cycleData->getActiveDay() > 0 ) {
        textDay->SetLabel( m_util.intToStr( m_cycleData->getActiveDay() ) );
    } else {
        textDay->SetLabel( _T( "1" ) );
    }
    textDate->SetLabel( currentDay.Format( _T( "%Y-%m-%d" ) ) );
}

/**
 * Build GUI
 */
void goToFrame::buildGui(wxWindow* parent)
{
    //(*Initialize(goToFrame)
    wxBoxSizer* sizer6;
    wxBoxSizer* sizer1;
    wxBoxSizer* sizer5;
    wxBoxSizer* BoxSizer1;
    wxStaticBoxSizer* sizer3;
    wxFlexGridSizer* sizer4;
    wxBoxSizer* sizer2;

    Create(parent, wxID_ANY, _("NFP - go to card.."), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
    sizer1 = new wxBoxSizer(wxHORIZONTAL);
    panel1 = new wxPanel(this, ID_panel1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_panel1"));
    sizer2 = new wxBoxSizer(wxVERTICAL);
    sizer3 = new wxStaticBoxSizer(wxVERTICAL, panel1, wxEmptyString);
    sizer4 = new wxFlexGridSizer(0, 2, 0, 0);
    sizer4->AddGrowableCol(0);
    radioButtonCardNumber = new wxRadioButton(panel1, ID_radioButtonCardNumber, _("Go to card number:"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_radioButtonCardNumber"));
    radioButtonCardNumber->SetToolTip(_("Go to card with choosen number"));
    sizer4->Add(radioButtonCardNumber, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    spinCardNumber = new wxSpinCtrl(panel1, ID_spinCardNumber, _T("0"), wxDefaultPosition, wxSize(120,-1), wxSP_ARROW_KEYS, 0, 100, 0, _T("ID_spinCardNumber"));
    spinCardNumber->SetValue(_T("0"));
    spinCardNumber->SetToolTip(_("Choose the card number"));
    sizer4->Add(spinCardNumber, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    radioButtonDate = new wxRadioButton(panel1, ID_radioButtonDate, _("Go to card with day:"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_radioButtonDate"));
    radioButtonDate->SetToolTip(_("Go to card where there is a day with choosen date"));
    sizer4->Add(radioButtonDate, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    datePickerDate = new wxDatePickerCtrl(panel1, ID_datePickerDate, wxDefaultDateTime, wxDefaultPosition, wxSize(120,-1), wxDP_DROPDOWN|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_datePickerDate"));
    datePickerDate->SetToolTip(_("Choose the date"));
    sizer4->Add(datePickerDate, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer3->Add(sizer4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    space1 = new wxStaticText(panel1, ID_space1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_space1"));
    BoxSizer1->Add(space1, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticVaildDates = new wxStaticText(panel1, ID_staticVaildDates, _("Vaild dates: %s - %s"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_staticVaildDates"));
    BoxSizer1->Add(staticVaildDates, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    sizer3->Add(BoxSizer1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    sizer5 = new wxBoxSizer(wxHORIZONTAL);
    staticCard = new wxStaticText(panel1, ID_staticCard, _("Choosen card:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticCard"));
    sizer5->Add(staticCard, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    textCard = new wxStaticText(panel1, ID_textCard, _("1"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_textCard"));
    textCard->SetForegroundColour(wxColour(0,0,128));
    wxFont textCardFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !textCardFont.Ok() ) textCardFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    textCardFont.SetPointSize((int)(textCardFont.GetPointSize() * 1.000000));
    textCardFont.SetWeight(wxBOLD);
    textCard->SetFont(textCardFont);
    sizer5->Add(textCard, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticDay = new wxStaticText(panel1, ID_staticDay, _("day:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticDay"));
    sizer5->Add(staticDay, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    textDay = new wxStaticText(panel1, ID_textDay, _("1"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_textDay"));
    textDay->SetForegroundColour(wxColour(0,0,128));
    wxFont textDayFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !textDayFont.Ok() ) textDayFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    textDayFont.SetPointSize((int)(textDayFont.GetPointSize() * 1.000000));
    textDayFont.SetWeight(wxBOLD);
    textDay->SetFont(textDayFont);
    sizer5->Add(textDay, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticDate = new wxStaticText(panel1, ID_staticDate, _("date:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticDate"));
    sizer5->Add(staticDate, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    textDate = new wxStaticText(panel1, ID_textDate, _("xxxx-xx-xx"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_textDate"));
    textDate->SetForegroundColour(wxColour(0,0,128));
    wxFont textDateFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !textDateFont.Ok() ) textDateFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    textDateFont.SetPointSize((int)(textDateFont.GetPointSize() * 1.000000));
    textDateFont.SetWeight(wxBOLD);
    textDate->SetFont(textDateFont);
    sizer5->Add(textDate, 1, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer3->Add(sizer5, 1, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    sizer2->Add(sizer3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizer6 = new wxBoxSizer(wxHORIZONTAL);
    buttonGoTo = new wxButton(panel1, ID_buttonGoTo, _("Go to"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_buttonGoTo"));
    buttonGoTo->SetToolTip(_("Switch to choosen card / day"));
    sizer6->Add(buttonGoTo, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    buttonCancel = new wxButton(panel1, ID_buttonCancel, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_buttonCancel"));
    buttonCancel->SetToolTip(_("Cancel operation and close this window"));
    sizer6->Add(buttonCancel, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    sizer2->Add(sizer6, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panel1->SetSizer(sizer2);
    sizer2->Fit(panel1);
    sizer2->SetSizeHints(panel1);
    sizer1->Add(panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(sizer1);
    sizer1->Fit(this);
    sizer1->SetSizeHints(this);

    Connect(ID_radioButtonCardNumber,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&goToFrame::radioButtonCardNumberClick);
    Connect(ID_spinCardNumber,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&goToFrame::spinCardNumberChange);
    Connect(ID_radioButtonDate,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&goToFrame::radioButtonDateClick);
    Connect(ID_datePickerDate,wxEVT_DATE_CHANGED,(wxObjectEventFunction)&goToFrame::datePickerDateDateChanged);
    Connect(ID_buttonGoTo,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&goToFrame::buttonGoToClick);
    Connect(ID_buttonCancel,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&goToFrame::buttonCancelClick);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&goToFrame::goToFrameClose);
    //*)
    Connect(ID_spinCardNumber,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&goToFrame::spinCardNumberChange);

    /****************************************************/
    int flatButton = 0;
    if ( m_config->useFlatButtons )
        flatButton = wxNO_BORDER;
    buttonGoTo->SetWindowStyle( flatButton );
    buttonCancel->SetWindowStyle( flatButton );
    buttonGoTo->Refresh();
    buttonCancel->Refresh();

    wxIcon wx_nfp_ICON( wx_nfp_xpm );
    SetIcon( wx_nfp_ICON );

    GetSizer()->Fit( this );
    GetSizer()->SetSizeHints( this );
    Center();

    SetAffirmativeId( ID_buttonGoTo );
    SetEscapeId( ID_buttonCancel );
    buttonGoTo->SetDefault();
}

/**
 *
 */
goToFrame::~goToFrame()
{
    //(*Destroy(goToFrame)
    //*)
}

/******************************************************************************/

/**
 *
 */
void goToFrame::goToFrameClose( wxCloseEvent& /*event*/ )
{
    this->EndModal( 0 );
    Destroy();
}

/**
 * buttonOkClick
 */
void goToFrame::buttonGoToClick( wxCommandEvent& event )
{
    int card = m_util.strToInt( textCard->GetLabel() );
    int day  = m_util.strToInt( textDay->GetLabel() );

    m_cycleData->setActiveCard( card );
    m_cycleData->setActiveDay( day );

    if ( day == 1 ) {
        m_config->checkFirstDayVisibility = true;
    } else if ( day == m_cycleData->getCard( card )->getDaysCount() ) {
        m_config->checkLastDayVisibility = true;
    } else {
        m_config->checkCurrentDayVisibility = true;
    }

    this->EndModal( 1 );
}

/**
 * buttonCancelClick
 */
void goToFrame::buttonCancelClick( wxCommandEvent& event )
{
    this->EndModal( 0 );
}

/******************************************************************************/

/**
 * radioButtonDateClick
 */
void goToFrame::radioButtonDateClick( wxCommandEvent& event )
{
    updateInfo();
}

/**
 * radioButtonCardNumberClick
 */
void goToFrame::radioButtonCardNumberClick( wxCommandEvent& event )
{
    updateInfo();
}

/******************************************************************************/

/**
 * spinCardNumberChange
 */
void goToFrame::spinCardNumberChange(wxSpinEvent& event)
{
    radioButtonCardNumber->SetValue( true );
    radioButtonDate->SetValue( false );

    updateInfo();
}

/**
 * datePickerDateDateChanged
 */
void goToFrame::datePickerDateDateChanged( wxDateEvent& event )
{
    radioButtonCardNumber->SetValue( false );
    radioButtonDate->SetValue( true );

    updateInfo();
}

/******************************************************************************/

/**
 * Update card number, day number and date in the "info" section of the frame.
 */
void goToFrame::updateInfo()
{
    int card = -1;
    int day  = -1;
    wxDateTime date;

    if ( radioButtonCardNumber->GetValue() ) {
        card = spinCardNumber->GetValue();
        day = 1;
        date = m_cycleData->getCard( card )->getFirstDayOfCycle();
    } else {
        date = datePickerDate->GetValue();
        card = findCard( date );
        day = findDay( date, card );
    }

    textCard->SetLabel( m_util.intToStr( card ) );
    textDay->SetLabel( m_util.intToStr( day ) );
    textDate->SetLabel( date.Format( _T( "%Y-%m-%d" ) ) );


}

/**
 * Find the card number based on the provided date.
 */
int goToFrame::findCard( wxDateTime date )
{
    wxDateTime d;

    if ( m_cycleData->getCardsCount() == 1 ) {
        return 1;
    }

    for ( int c = 2; c <= m_cycleData->getCardsCount(); c++ ) {
        d = m_cycleData->getCard( c )->getFirstDayOfCycle();
        if ( date < d ) {
            return ( c -1 );
        }
    }
    return m_cycleData->getCardsCount();
}

/**
 * Find the day number based on the provided date and card number.
 */
int goToFrame::findDay( wxDateTime date, int card )
{
    if ( card == -1 ) {
        return -1;
    }

    wxDateTime d1 = m_cycleData->getCard( card )->getFirstDayOfCycle();
    wxDateTime d2;
    int daysCount = m_cycleData->getCard( card )->getDaysCount();

    if ( date.IsSameDate( d1 ) ) {
        return 1;
    } else {
        d2 = d1;
        d2.Add( wxDateSpan::Days( daysCount - 1 ) );
        if ( date.IsSameDate( d2 ) ) {
            return daysCount;
        }
    }

    int a1 = 1;
    int a2 = daysCount;
    int a = 0;

    while ( true ) {
        a = a1 + (( a2 - a1 ) / 2 );
        d2 = d1;
        d2.Add( wxDateSpan::Days( a - 1 ) );
        if ( date.IsSameDate( d2 ) ) {
            return a;
        } else if ( date < d2 ) {
            a2 = a;
        } else {
            a1 = a;
        }
    }

    return -1;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/
