/***************************************************************
 * Name:      cardFrame.cpp
 * Purpose:   Dialog for editing card's data
 * Author:    Grzegorz Szura (grzegorz@szura.net)
 * Created:   2010-03-02
 * Copyright: Grzegorz Szura (http://www.szura.net)
 * License:
 **************************************************************/

#include "cardFrame.h"
#include "../data/xpm/wx-nfp.xpm"
#include "cyclesData_declarations.h"

//(*InternalHeaders(cardFrame)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

/******************************************************************************/

//(*IdInit(cardFrame)
const long cardFrame::ID_staticCardNo = wxNewId();
const long cardFrame::ID_textCardNo = wxNewId();
const long cardFrame::ID_changesCardNo = wxNewId();
const long cardFrame::ID_static1stDayOfCycle = wxNewId();
const long cardFrame::ID_datePicker1stDayOfCycle = wxNewId();
const long cardFrame::ID_changes1stDayOfCycle = wxNewId();
const long cardFrame::ID_staticTemp = wxNewId();
const long cardFrame::ID_staticSpace1 = wxNewId();
const long cardFrame::ID_staticTempTime = wxNewId();
const long cardFrame::ID_comboBoxTempTimeHour = wxNewId();
const long cardFrame::ID_comboBoxTempTimeMinute = wxNewId();
const long cardFrame::ID_changesTempTime = wxNewId();
const long cardFrame::ID_staticSpace2 = wxNewId();
const long cardFrame::ID_staticTempPlace = wxNewId();
const long cardFrame::ID_comboBoxTempPlace = wxNewId();
const long cardFrame::ID_changesTempPlace = wxNewId();
const long cardFrame::ID_staticTempCorrection = wxNewId();
const long cardFrame::ID_staticSpace3 = wxNewId();
const long cardFrame::ID_staticTempCorrectionMouth = wxNewId();
const long cardFrame::ID_comboBoxTempCorrectionMouth = wxNewId();
const long cardFrame::ID_changesTempCorrectionMouth = wxNewId();
const long cardFrame::ID_staticSpace4 = wxNewId();
const long cardFrame::ID_staticTempCorrectionVagina = wxNewId();
const long cardFrame::ID_comboBoxTempCorrectionVagina = wxNewId();
const long cardFrame::ID_changesTempCorrectionVagina = wxNewId();
const long cardFrame::ID_staticSpace5 = wxNewId();
const long cardFrame::ID_staticTempCorrectionRectum = wxNewId();
const long cardFrame::ID_comboBoxTempCorrectionRectum = wxNewId();
const long cardFrame::ID_changesTempCorrectionRectum = wxNewId();
const long cardFrame::ID_staticSpace6 = wxNewId();
const long cardFrame::ID_staticTempCorrectionTime = wxNewId();
const long cardFrame::ID_comboBoxTempCorrectionTime = wxNewId();
const long cardFrame::ID_changesTempCorrectionTime = wxNewId();
const long cardFrame::ID_staticNotes = wxNewId();
const long cardFrame::ID_changesNotes = wxNewId();
const long cardFrame::ID_textNotes = wxNewId();
const long cardFrame::ID_staticName = wxNewId();
const long cardFrame::ID_textName = wxNewId();
const long cardFrame::ID_changesName = wxNewId();
const long cardFrame::ID_staticBirthdayDay = wxNewId();
const long cardFrame::ID_datePickerBirthdayDay = wxNewId();
const long cardFrame::ID_changesBirthdayDay = wxNewId();
const long cardFrame::ID_buttonSave = wxNewId();
const long cardFrame::ID_buttonCancel = wxNewId();
const long cardFrame::ID_staticSpace7 = wxNewId();
const long cardFrame::ID_buttonClose = wxNewId();
const long cardFrame::ID_panelMain = wxNewId();
//*)

BEGIN_EVENT_TABLE(cardFrame,wxDialog)
    //(*EventTable(cardFrame)
    //*)
END_EVENT_TABLE()

/******************************************************************************/

const wxEventType wxEVT_CARD_DATA_MODIFIED_EVENT = wxNewEventType();

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
cardFrame::cardFrame(wxWindow* parent, configClass *config, cycleDataClass *cycleData, wxWindowID id) {
    m_parent = parent;
    m_config = config;
    m_cycleData = cycleData;
    m_notesEventProcessing = false;

    buildGui(parent);

}

/**
 * Build GUI
 */
void cardFrame::buildGui(wxWindow* parent) {
    //(*Initialize(cardFrame)
    wxBoxSizer* sizerMain2;
    wxFlexGridSizer* sizerTempCorrection;
    wxBoxSizer* sizerCardNotes;
    wxBoxSizer* sizerMain1;
    wxStaticBoxSizer* sizerCard;
    wxFlexGridSizer* sizerTemp;
    wxFlexGridSizer* sizerCardNo;
    wxBoxSizer* sizerButtons;
    wxStaticBoxSizer* sizerCommon;
    wxFlexGridSizer* sizerCommon2;
    wxBoxSizer* sizerTempTime;

    Create(parent, wxID_ANY, _("NFP - edit card\'s data"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    sizerMain1 = new wxBoxSizer(wxHORIZONTAL);
    panelMain = new wxPanel(this, ID_panelMain, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_panelMain"));
    sizerMain2 = new wxBoxSizer(wxVERTICAL);
    sizerCard = new wxStaticBoxSizer(wxVERTICAL, panelMain, _("data specific for current card"));
    sizerCardNo = new wxFlexGridSizer(0, 3, 0, 0);
    sizerCardNo->AddGrowableCol(0);
    staticCardNo = new wxStaticText(panelMain, ID_staticCardNo, _("card number"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticCardNo"));
    staticCardNo->SetToolTip(_("The card number is set automatically"));
    sizerCardNo->Add(staticCardNo, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    textCardNo = new wxStaticText(panelMain, ID_textCardNo, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_textCardNo"));
    wxFont textCardNoFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !textCardNoFont.Ok() ) textCardNoFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    textCardNoFont.SetPointSize((int)(textCardNoFont.GetPointSize() * 1.000000));
    textCardNoFont.SetWeight(wxBOLD);
    textCardNo->SetFont(textCardNoFont);
    textCardNo->SetToolTip(_("The card number is set automatically"));
    sizerCardNo->Add(textCardNo, 1, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    changesCardNo = new wxStaticText(panelMain, ID_changesCardNo, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesCardNo"));
    changesCardNo->SetForegroundColour(wxColour(255,0,0));
    sizerCardNo->Add(changesCardNo, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    static1stDayOfCycle = new wxStaticText(panelMain, ID_static1stDayOfCycle, _("first day of the cycle"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_static1stDayOfCycle"));
    static1stDayOfCycle->SetToolTip(_("First day of the cycle can be set for the first card only and only if there is only one card in the set"));
    sizerCardNo->Add(static1stDayOfCycle, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    datePicker1stDayOfCycle = new wxDatePickerCtrl(panelMain, ID_datePicker1stDayOfCycle, wxDefaultDateTime, wxDefaultPosition, wxSize(120,-1), wxDP_DROPDOWN|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_datePicker1stDayOfCycle"));
    datePicker1stDayOfCycle->SetToolTip(_("First day of the cycle can be set for the first card only and only if there is only one card in the set"));
    sizerCardNo->Add(datePicker1stDayOfCycle, 1, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    changes1stDayOfCycle = new wxStaticText(panelMain, ID_changes1stDayOfCycle, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changes1stDayOfCycle"));
    changes1stDayOfCycle->SetForegroundColour(wxColour(255,0,0));
    sizerCardNo->Add(changes1stDayOfCycle, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizerCard->Add(sizerCardNo, 0, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticTemp = new wxStaticText(panelMain, ID_staticTemp, _("temperature measurement:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticTemp"));
    sizerCard->Add(staticTemp, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    sizerTemp = new wxFlexGridSizer(0, 4, 0, 0);
    sizerTemp->AddGrowableCol(1);
    staticSpace1 = new wxStaticText(panelMain, ID_staticSpace1, wxEmptyString, wxDefaultPosition, wxSize(5,-1), 0, _T("ID_staticSpace1"));
    sizerTemp->Add(staticSpace1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    staticTempTime = new wxStaticText(panelMain, ID_staticTempTime, _("usual time"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticTempTime"));
    staticTempTime->SetToolTip(_("Usual time, when you will measure temperature in this cycle"));
    sizerTemp->Add(staticTempTime, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    sizerTempTime = new wxBoxSizer(wxHORIZONTAL);
    comboBoxTempTimeHour = new wxComboBox(panelMain, ID_comboBoxTempTimeHour, wxEmptyString, wxDefaultPosition, wxSize(60,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxTempTimeHour"));
    comboBoxTempTimeHour->SetToolTip(_("Usual time, when you will measure temperature in this cycle"));
    sizerTempTime->Add(comboBoxTempTimeHour, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    comboBoxTempTimeMinute = new wxComboBox(panelMain, ID_comboBoxTempTimeMinute, wxEmptyString, wxDefaultPosition, wxSize(60,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxTempTimeMinute"));
    comboBoxTempTimeMinute->SetToolTip(_("Usual time, when you will measure temperature in this cycle"));
    sizerTempTime->Add(comboBoxTempTimeMinute, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    sizerTemp->Add(sizerTempTime, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    changesTempTime = new wxStaticText(panelMain, ID_changesTempTime, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesTempTime"));
    changesTempTime->SetForegroundColour(wxColour(255,0,0));
    sizerTemp->Add(changesTempTime, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticSpace2 = new wxStaticText(panelMain, ID_staticSpace2, wxEmptyString, wxDefaultPosition, wxSize(5,-1), 0, _T("ID_staticSpace2"));
    sizerTemp->Add(staticSpace2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    staticTempPlace = new wxStaticText(panelMain, ID_staticTempPlace, _("usual place"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticTempPlace"));
    staticTempPlace->SetToolTip(_("Usual place, when you will measure temperature in this cycle"));
    sizerTemp->Add(staticTempPlace, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    comboBoxTempPlace = new wxComboBox(panelMain, ID_comboBoxTempPlace, wxEmptyString, wxDefaultPosition, wxSize(120,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxTempPlace"));
    comboBoxTempPlace->SetToolTip(_("Usual place, when you will measure temperature in this cycle"));
    sizerTemp->Add(comboBoxTempPlace, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    changesTempPlace = new wxStaticText(panelMain, ID_changesTempPlace, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesTempPlace"));
    changesTempPlace->SetForegroundColour(wxColour(255,0,0));
    sizerTemp->Add(changesTempPlace, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizerCard->Add(sizerTemp, 0, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticTempCorrection = new wxStaticText(panelMain, ID_staticTempCorrection, _("temperature correction when measured:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticTempCorrection"));
    sizerCard->Add(staticTempCorrection, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    sizerTempCorrection = new wxFlexGridSizer(0, 4, 0, 0);
    sizerTempCorrection->AddGrowableCol(1);
    staticSpace3 = new wxStaticText(panelMain, ID_staticSpace3, wxEmptyString, wxDefaultPosition, wxSize(5,-1), 0, _T("ID_staticSpace3"));
    sizerTempCorrection->Add(staticSpace3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    staticTempCorrectionMouth = new wxStaticText(panelMain, ID_staticTempCorrectionMouth, _("in mouth"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticTempCorrectionMouth"));
    staticTempCorrectionMouth->SetToolTip(_("How the temperature should be corected, when it will be measured in mouth"));
    sizerTempCorrection->Add(staticTempCorrectionMouth, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    comboBoxTempCorrectionMouth = new wxComboBox(panelMain, ID_comboBoxTempCorrectionMouth, wxEmptyString, wxDefaultPosition, wxSize(100,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxTempCorrectionMouth"));
    comboBoxTempCorrectionMouth->SetToolTip(_("How the temperature should be corected, when it will be measured in mouth"));
    sizerTempCorrection->Add(comboBoxTempCorrectionMouth, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    changesTempCorrectionMouth = new wxStaticText(panelMain, ID_changesTempCorrectionMouth, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesTempCorrectionMouth"));
    changesTempCorrectionMouth->SetForegroundColour(wxColour(255,0,0));
    sizerTempCorrection->Add(changesTempCorrectionMouth, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticSpace4 = new wxStaticText(panelMain, ID_staticSpace4, wxEmptyString, wxDefaultPosition, wxSize(5,-1), 0, _T("ID_staticSpace4"));
    sizerTempCorrection->Add(staticSpace4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    staticTempCorrectionVagina = new wxStaticText(panelMain, ID_staticTempCorrectionVagina, _("in vagina"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticTempCorrectionVagina"));
    staticTempCorrectionVagina->SetToolTip(_("How the temperature should be corected, when it will be measured in vagina"));
    sizerTempCorrection->Add(staticTempCorrectionVagina, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    comboBoxTempCorrectionVagina = new wxComboBox(panelMain, ID_comboBoxTempCorrectionVagina, wxEmptyString, wxDefaultPosition, wxSize(100,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxTempCorrectionVagina"));
    comboBoxTempCorrectionVagina->SetToolTip(_("How the temperature should be corected, when it will be measured in vagina"));
    sizerTempCorrection->Add(comboBoxTempCorrectionVagina, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    changesTempCorrectionVagina = new wxStaticText(panelMain, ID_changesTempCorrectionVagina, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesTempCorrectionVagina"));
    changesTempCorrectionVagina->SetForegroundColour(wxColour(255,0,0));
    sizerTempCorrection->Add(changesTempCorrectionVagina, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticSpace5 = new wxStaticText(panelMain, ID_staticSpace5, wxEmptyString, wxDefaultPosition, wxSize(5,-1), 0, _T("ID_staticSpace5"));
    sizerTempCorrection->Add(staticSpace5, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    staticTempCorrectionRectum = new wxStaticText(panelMain, ID_staticTempCorrectionRectum, _("in rectum"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticTempCorrectionRectum"));
    staticTempCorrectionRectum->SetToolTip(_("How the temperature should be corected, when it will be measured in rectum"));
    sizerTempCorrection->Add(staticTempCorrectionRectum, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    comboBoxTempCorrectionRectum = new wxComboBox(panelMain, ID_comboBoxTempCorrectionRectum, wxEmptyString, wxDefaultPosition, wxSize(100,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxTempCorrectionRectum"));
    comboBoxTempCorrectionRectum->SetToolTip(_("How the temperature should be corected, when it will be measured in rectum"));
    sizerTempCorrection->Add(comboBoxTempCorrectionRectum, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    changesTempCorrectionRectum = new wxStaticText(panelMain, ID_changesTempCorrectionRectum, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesTempCorrectionRectum"));
    changesTempCorrectionRectum->SetForegroundColour(wxColour(255,0,0));
    sizerTempCorrection->Add(changesTempCorrectionRectum, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticSpace6 = new wxStaticText(panelMain, ID_staticSpace6, wxEmptyString, wxDefaultPosition, wxSize(5,-1), 0, _T("ID_staticSpace6"));
    sizerTempCorrection->Add(staticSpace6, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    staticTempCorrectionTime = new wxStaticText(panelMain, ID_staticTempCorrectionTime, _("at different time as usual"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticTempCorrectionTime"));
    staticTempCorrectionTime->SetToolTip(_("How the temperature should be corected, when it will be measured 60 minutes later than usual"));
    sizerTempCorrection->Add(staticTempCorrectionTime, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    comboBoxTempCorrectionTime = new wxComboBox(panelMain, ID_comboBoxTempCorrectionTime, wxEmptyString, wxDefaultPosition, wxSize(100,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxTempCorrectionTime"));
    comboBoxTempCorrectionTime->SetToolTip(_("How the temperature should be corected, when it will be measured 60 minutes later than usual"));
    sizerTempCorrection->Add(comboBoxTempCorrectionTime, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    changesTempCorrectionTime = new wxStaticText(panelMain, ID_changesTempCorrectionTime, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesTempCorrectionTime"));
    changesTempCorrectionTime->SetForegroundColour(wxColour(255,0,0));
    sizerTempCorrection->Add(changesTempCorrectionTime, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizerCard->Add(sizerTempCorrection, 0, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizerCardNotes = new wxBoxSizer(wxHORIZONTAL);
    staticNotes = new wxStaticText(panelMain, ID_staticNotes, _("notes:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticNotes"));
    staticNotes->SetToolTip(_("Type notes common for this cycle"));
    sizerCardNotes->Add(staticNotes, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    changesNotes = new wxStaticText(panelMain, ID_changesNotes, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesNotes"));
    changesNotes->SetForegroundColour(wxColour(255,0,0));
    sizerCardNotes->Add(changesNotes, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizerCard->Add(sizerCardNotes, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    textNotes = new wxTextCtrl(panelMain, ID_textNotes, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_textNotes"));
    textNotes->SetMinSize(wxSize(180,40));
    textNotes->SetMaxSize(wxSize(400,60));
    textNotes->SetToolTip(_("Type notes common for this cycle"));
    sizerCard->Add(textNotes, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizerMain2->Add(sizerCard, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizerCommon = new wxStaticBoxSizer(wxHORIZONTAL, panelMain, _("data common for all cards"));
    sizerCommon2 = new wxFlexGridSizer(0, 3, 0, 0);
    sizerCommon2->AddGrowableCol(0);
    staticName = new wxStaticText(panelMain, ID_staticName, _("name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticName"));
    staticName->SetToolTip(_("Type your name"));
    sizerCommon2->Add(staticName, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    textName = new wxTextCtrl(panelMain, ID_textName, wxEmptyString, wxDefaultPosition, wxSize(120,-1), wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_textName"));
    textName->SetToolTip(_("Type your name"));
    sizerCommon2->Add(textName, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    changesName = new wxStaticText(panelMain, ID_changesName, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesName"));
    changesName->SetForegroundColour(wxColour(255,0,0));
    sizerCommon2->Add(changesName, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    staticBirthdayDay = new wxStaticText(panelMain, ID_staticBirthdayDay, _("day of birth"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticBirthdayDay"));
    staticBirthdayDay->SetToolTip(_("Provide your birthday day. This information is used to calculate your age displayed on the cycles\' card."));
    sizerCommon2->Add(staticBirthdayDay, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    datePickerBirthdayDay = new wxDatePickerCtrl(panelMain, ID_datePickerBirthdayDay, wxDefaultDateTime, wxDefaultPosition, wxSize(120,-1), wxDP_DROPDOWN|wxDP_SHOWCENTURY, wxDefaultValidator, _T("ID_datePickerBirthdayDay"));
    datePickerBirthdayDay->SetToolTip(_("Provide your birthday day. This information is used to calculate your age displayed on the cycles\' card."));
    sizerCommon2->Add(datePickerBirthdayDay, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    changesBirthdayDay = new wxStaticText(panelMain, ID_changesBirthdayDay, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesBirthdayDay"));
    changesBirthdayDay->SetForegroundColour(wxColour(255,0,0));
    sizerCommon2->Add(changesBirthdayDay, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizerCommon->Add(sizerCommon2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    sizerMain2->Add(sizerCommon, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    sizerButtons = new wxBoxSizer(wxHORIZONTAL);
    buttonSave = new wxButton(panelMain, ID_buttonSave, _("save changes"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_buttonSave"));
    buttonSave->SetToolTip(_("Save changes without closing this window"));
    sizerButtons->Add(buttonSave, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    buttonCancel = new wxButton(panelMain, ID_buttonCancel, _("cancel changes"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_buttonCancel"));
    buttonCancel->SetToolTip(_("Close this window without saving changes"));
    sizerButtons->Add(buttonCancel, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    staticSpace7 = new wxStaticText(panelMain, ID_staticSpace7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticSpace7"));
    sizerButtons->Add(staticSpace7, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    buttonClose = new wxButton(panelMain, ID_buttonClose, _("close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_buttonClose"));
    buttonClose->SetToolTip(_("Close this window (and ask for saving unsaved changes)"));
    sizerButtons->Add(buttonClose, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    sizerMain2->Add(sizerButtons, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    panelMain->SetSizer(sizerMain2);
    sizerMain2->Fit(panelMain);
    sizerMain2->SetSizeHints(panelMain);
    sizerMain1->Add(panelMain, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(sizerMain1);
    sizerMain1->Fit(this);
    sizerMain1->SetSizeHints(this);

    Connect(ID_datePicker1stDayOfCycle,wxEVT_DATE_CHANGED,(wxObjectEventFunction)&cardFrame::datePicker1stDayOfCycleDateChanged);
    Connect(ID_comboBoxTempTimeHour,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cardFrame::comboBoxTempTimeUpdated);
    Connect(ID_comboBoxTempTimeMinute,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cardFrame::comboBoxTempTimeUpdated);
    Connect(ID_comboBoxTempPlace,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cardFrame::comboBoxTempPlaceUpdated);
    Connect(ID_comboBoxTempCorrectionMouth,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cardFrame::comboBoxTempCorrectionMouthUpdated);
    Connect(ID_comboBoxTempCorrectionVagina,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cardFrame::comboBoxTempCorrectionVaginaUpdated);
    Connect(ID_comboBoxTempCorrectionRectum,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cardFrame::comboBoxTempCorrectionRectumUpdated);
    Connect(ID_comboBoxTempCorrectionTime,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cardFrame::comboBoxTempCorrectionTimeUpdated);
    Connect(ID_textNotes,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cardFrame::textNotesUpdated);
    Connect(ID_textName,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cardFrame::textNameUpdated);
    Connect(ID_datePickerBirthdayDay,wxEVT_DATE_CHANGED,(wxObjectEventFunction)&cardFrame::datePickerBirthdayDayDateChanged);
    Connect(ID_buttonSave,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cardFrame::buttonSaveClick);
    Connect(ID_buttonCancel,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cardFrame::buttonCancelClick);
    Connect(ID_buttonClose,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cardFrame::buttonCloseClick);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&cardFrame::cardFrameClose);
    Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&cardFrame::cardFrameKeyDown);
    //*)

    /****************************************************/
    /** comboBoxes' data */
    comboBoxTempTimeHour->Append(_T("0"));
    comboBoxTempTimeHour->Append(_T("1"));
    comboBoxTempTimeHour->Append(_T("2"));
    comboBoxTempTimeHour->Append(_T("3"));
    comboBoxTempTimeHour->Append(_T("4"));
    comboBoxTempTimeHour->Append(_T("5"));
    comboBoxTempTimeHour->Append(_T("6"));
    comboBoxTempTimeHour->SetSelection( comboBoxTempTimeHour->Append(_T("7")) );
    comboBoxTempTimeHour->Append(_T("8"));
    comboBoxTempTimeHour->Append(_T("9"));
    comboBoxTempTimeHour->Append(_T("10"));
    comboBoxTempTimeHour->Append(_T("11"));
    comboBoxTempTimeHour->Append(_T("12"));
    comboBoxTempTimeHour->Append(_T("13"));
    comboBoxTempTimeHour->Append(_T("14"));
    comboBoxTempTimeHour->Append(_T("15"));
    comboBoxTempTimeHour->Append(_T("16"));
    comboBoxTempTimeHour->Append(_T("17"));
    comboBoxTempTimeHour->Append(_T("18"));
    comboBoxTempTimeHour->Append(_T("19"));
    comboBoxTempTimeHour->Append(_T("20"));
    comboBoxTempTimeHour->Append(_T("21"));
    comboBoxTempTimeHour->Append(_T("22"));
    comboBoxTempTimeHour->Append(_T("23"));
    comboBoxTempTimeMinute->SetSelection( comboBoxTempTimeMinute->Append(_T("00")) );
    comboBoxTempTimeMinute->Append(_T("05"));
    comboBoxTempTimeMinute->Append(_T("10"));
    comboBoxTempTimeMinute->Append(_T("15"));
    comboBoxTempTimeMinute->Append(_T("20"));
    comboBoxTempTimeMinute->Append(_T("25"));
    comboBoxTempTimeMinute->Append(_T("30"));
    comboBoxTempTimeMinute->Append(_T("35"));
    comboBoxTempTimeMinute->Append(_T("40"));
    comboBoxTempTimeMinute->Append(_T("45"));
    comboBoxTempTimeMinute->Append(_T("50"));
    comboBoxTempTimeMinute->Append(_T("55"));
    comboBoxTempPlace->Append(string_placeMouth);
    comboBoxTempPlace->SetSelection( comboBoxTempPlace->Append(string_placeVagina) );
    comboBoxTempPlace->Append(string_placeRectum);
    comboBoxTempCorrectionMouth->Append(_T("-0,7"));
    comboBoxTempCorrectionMouth->Append(_T("-0,65"));
    comboBoxTempCorrectionMouth->Append(_T("-0,6"));
    comboBoxTempCorrectionMouth->Append(_T("-0,55"));
    comboBoxTempCorrectionMouth->Append(_T("-0,5"));
    comboBoxTempCorrectionMouth->Append(_T("-0,45"));
    comboBoxTempCorrectionMouth->Append(_T("-0,4"));
    comboBoxTempCorrectionMouth->Append(_T("-0,35"));
    comboBoxTempCorrectionMouth->Append(_T("-0,3"));
    comboBoxTempCorrectionMouth->Append(_T("-0,25"));
    comboBoxTempCorrectionMouth->Append(_T("-0,2"));
    comboBoxTempCorrectionMouth->Append(_T("-0,15"));
    comboBoxTempCorrectionMouth->Append(_T("-0,1"));
    comboBoxTempCorrectionMouth->Append(_T("-0,05"));
    comboBoxTempCorrectionMouth->SetSelection( comboBoxTempCorrectionMouth->Append(_T("0")) );
    comboBoxTempCorrectionMouth->Append(_T("+0,05"));
    comboBoxTempCorrectionMouth->Append(_T("+0,1"));
    comboBoxTempCorrectionMouth->Append(_T("+0,15"));
    comboBoxTempCorrectionMouth->Append(_T("+0,2"));
    comboBoxTempCorrectionMouth->Append(_T("+0,25"));
    comboBoxTempCorrectionMouth->Append(_T("+0,3"));
    comboBoxTempCorrectionMouth->Append(_T("+0,35"));
    comboBoxTempCorrectionMouth->Append(_T("+0,4"));
    comboBoxTempCorrectionMouth->Append(_T("+0,45"));
    comboBoxTempCorrectionMouth->Append(_T("+0,5"));
    comboBoxTempCorrectionMouth->Append(_T("+0,55"));
    comboBoxTempCorrectionMouth->Append(_T("+0,6"));
    comboBoxTempCorrectionMouth->Append(_T("+0,65"));
    comboBoxTempCorrectionMouth->Append(_T("+0,7"));
    comboBoxTempCorrectionVagina->Append(_T("-0,7"));
    comboBoxTempCorrectionVagina->Append(_T("-0,65"));
    comboBoxTempCorrectionVagina->Append(_T("-0,6"));
    comboBoxTempCorrectionVagina->Append(_T("-0,55"));
    comboBoxTempCorrectionVagina->Append(_T("-0,5"));
    comboBoxTempCorrectionVagina->Append(_T("-0,45"));
    comboBoxTempCorrectionVagina->Append(_T("-0,4"));
    comboBoxTempCorrectionVagina->Append(_T("-0,35"));
    comboBoxTempCorrectionVagina->Append(_T("-0,3"));
    comboBoxTempCorrectionVagina->Append(_T("-0,25"));
    comboBoxTempCorrectionVagina->Append(_T("-0,2"));
    comboBoxTempCorrectionVagina->Append(_T("-0,15"));
    comboBoxTempCorrectionVagina->Append(_T("-0,1"));
    comboBoxTempCorrectionVagina->Append(_T("-0,05"));
    comboBoxTempCorrectionVagina->SetSelection( comboBoxTempCorrectionVagina->Append(_T("0")) );
    comboBoxTempCorrectionVagina->Append(_T("+0,05"));
    comboBoxTempCorrectionVagina->Append(_T("+0,1"));
    comboBoxTempCorrectionVagina->Append(_T("+0,15"));
    comboBoxTempCorrectionVagina->Append(_T("+0,2"));
    comboBoxTempCorrectionVagina->Append(_T("+0,25"));
    comboBoxTempCorrectionVagina->Append(_T("+0,3"));
    comboBoxTempCorrectionVagina->Append(_T("+0,35"));
    comboBoxTempCorrectionVagina->Append(_T("+0,4"));
    comboBoxTempCorrectionVagina->Append(_T("+0,45"));
    comboBoxTempCorrectionVagina->Append(_T("+0,5"));
    comboBoxTempCorrectionVagina->Append(_T("+0,55"));
    comboBoxTempCorrectionVagina->Append(_T("+0,6"));
    comboBoxTempCorrectionVagina->Append(_T("+0,65"));
    comboBoxTempCorrectionVagina->Append(_T("+0,7"));
    comboBoxTempCorrectionRectum->Append(_T("-0,7"));
    comboBoxTempCorrectionRectum->Append(_T("-0,65"));
    comboBoxTempCorrectionRectum->Append(_T("-0,6"));
    comboBoxTempCorrectionRectum->Append(_T("-0,55"));
    comboBoxTempCorrectionRectum->Append(_T("-0,5"));
    comboBoxTempCorrectionRectum->Append(_T("-0,45"));
    comboBoxTempCorrectionRectum->Append(_T("-0,4"));
    comboBoxTempCorrectionRectum->Append(_T("-0,35"));
    comboBoxTempCorrectionRectum->Append(_T("-0,3"));
    comboBoxTempCorrectionRectum->Append(_T("-0,25"));
    comboBoxTempCorrectionRectum->Append(_T("-0,2"));
    comboBoxTempCorrectionRectum->Append(_T("-0,15"));
    comboBoxTempCorrectionRectum->SetSelection( comboBoxTempCorrectionRectum->Append(_T("0")) );
    comboBoxTempCorrectionRectum->Append(_T("-0,1"));
    comboBoxTempCorrectionRectum->Append(_T("-0,05"));
    comboBoxTempCorrectionRectum->SetSelection( comboBoxTempCorrectionRectum->Append(_T("0")) );
    comboBoxTempCorrectionRectum->Append(_T("+0,05"));
    comboBoxTempCorrectionRectum->Append(_T("+0,1"));
    comboBoxTempCorrectionRectum->Append(_T("+0,15"));
    comboBoxTempCorrectionRectum->Append(_T("+0,2"));
    comboBoxTempCorrectionRectum->Append(_T("+0,25"));
    comboBoxTempCorrectionRectum->Append(_T("+0,3"));
    comboBoxTempCorrectionRectum->Append(_T("+0,35"));
    comboBoxTempCorrectionRectum->Append(_T("+0,4"));
    comboBoxTempCorrectionRectum->Append(_T("+0,45"));
    comboBoxTempCorrectionRectum->Append(_T("+0,5"));
    comboBoxTempCorrectionRectum->Append(_T("+0,55"));
    comboBoxTempCorrectionRectum->Append(_T("+0,6"));
    comboBoxTempCorrectionRectum->Append(_T("+0,65"));
    comboBoxTempCorrectionRectum->Append(_T("+0,7"));
    comboBoxTempCorrectionTime->Append(_T("-0,7"));
    comboBoxTempCorrectionTime->Append(_T("-0,65"));
    comboBoxTempCorrectionTime->Append(_T("-0,6"));
    comboBoxTempCorrectionTime->Append(_T("-0,55"));
    comboBoxTempCorrectionTime->Append(_T("-0,5"));
    comboBoxTempCorrectionTime->Append(_T("-0,45"));
    comboBoxTempCorrectionTime->Append(_T("-0,4"));
    comboBoxTempCorrectionTime->Append(_T("-0,35"));
    comboBoxTempCorrectionTime->Append(_T("-0,3"));
    comboBoxTempCorrectionTime->Append(_T("-0,25"));
    comboBoxTempCorrectionTime->Append(_T("-0,2"));
    comboBoxTempCorrectionTime->Append(_T("-0,15"));
    comboBoxTempCorrectionTime->SetSelection( comboBoxTempCorrectionTime->Append(_T("-0,1")) );
    comboBoxTempCorrectionTime->Append(_T("-0,05"));
    comboBoxTempCorrectionTime->Append(_T("0"));
    comboBoxTempCorrectionTime->Append(_T("+0,05"));
    comboBoxTempCorrectionTime->Append(_T("+0,1"));
    comboBoxTempCorrectionTime->Append(_T("+0,15"));
    comboBoxTempCorrectionTime->Append(_T("+0,2"));
    comboBoxTempCorrectionTime->Append(_T("+0,25"));
    comboBoxTempCorrectionTime->Append(_T("+0,3"));
    comboBoxTempCorrectionTime->Append(_T("+0,35"));
    comboBoxTempCorrectionTime->Append(_T("+0,4"));
    comboBoxTempCorrectionTime->Append(_T("+0,45"));
    comboBoxTempCorrectionTime->Append(_T("+0,5"));
    comboBoxTempCorrectionTime->Append(_T("+0,55"));
    comboBoxTempCorrectionTime->Append(_T("+0,6"));
    comboBoxTempCorrectionTime->Append(_T("+0,65"));
    comboBoxTempCorrectionTime->Append(_T("+0,7"));

    /****************************************************/
    setButtonsStyle();
    SetSize( m_config->formCardLeft, m_config->formCardTop, -1, -1 );

    wxIcon wx_nfp_ICON( wx_nfp_xpm );
    SetIcon( wx_nfp_ICON );

    SetAffirmativeId( ID_buttonSave );
    SetEscapeId( ID_buttonClose );
    buttonSave->SetDefault();
}

/**
 *
 */
cardFrame::~cardFrame() {
    //(*Destroy(cardFrame)
    //*)
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * cardFrameClose
 */
void cardFrame::cardFrameClose( wxCloseEvent& event ) {
    if ( checkIfCanExit( true ) ) {
        Hide();
        m_parent->SetFocus();
    }
}

/**
 * buttonSaveClick
 */
void cardFrame::buttonSaveClick( wxCommandEvent& event ) {
    save();
    update();
    updateButtonsState();
}

/**
 * buttonCancelClick
 */
void cardFrame::buttonCancelClick( wxCommandEvent& event ) {
    update();
    updateButtonsState();
}

/**
 * buttonCloseClick
 */
void cardFrame::buttonCloseClick( wxCommandEvent& event ) {
    if ( checkIfCanExit( true ) ) {
        Hide();
        m_parent->SetFocus();
    }
}

/**
 * cardFrameKeyDown
 */
void cardFrame::cardFrameKeyDown( wxKeyEvent& event ) {
    if ( event.GetKeyCode() == WXK_ESCAPE ) {
        if ( checkIfCanExit( true ) ) {
            Hide();
        }
    }

    event.Skip();
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * datePicker1stDayOfCycleDateChanged
 */
void cardFrame::datePicker1stDayOfCycleDateChanged( wxDateEvent& event ) {
    if ( datePicker1stDayOfCycle->GetValue().IsSameDate( m_cycleData->getCard()->getFirstDayOfCycle() ) ) {
        if ( changes1stDayOfCycle->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes--;
            changes1stDayOfCycle->SetLabel( wxEmptyString );
        }
    } else {
        if ( !changes1stDayOfCycle->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes++;
            changes1stDayOfCycle->SetLabel( _T( "*" ) );
        }
    }

    updateButtonsState();
}

/**
 * comboBoxTempTimeUpdated
 */
void cardFrame::comboBoxTempTimeUpdated( wxCommandEvent& event ) {
    // insert your code here
    int m = m_cycleData->getCard()->getTemperatureUsualMeasurementTime().GetMinute();
    wxString minute = m_util.intToStr( m );

    if ( m < 10 ) {
        minute = _T( "0" ) + m_util.intToStr( m );
    }

    if ( comboBoxTempTimeHour->GetValue().IsSameAs( m_util.intToStr( m_cycleData->getCard()->getTemperatureUsualMeasurementTime().GetHour() ) ) &&
            comboBoxTempTimeMinute->GetValue().IsSameAs( minute ) ) {
        if ( changesTempTime->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes--;
            changesTempTime->SetLabel( wxEmptyString );
        }
    } else {
        if ( !changesTempTime->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes++;
            changesTempTime->SetLabel( _T( "*" ) );
        }
    }

    updateButtonsState();
}

/**
 * comboBoxTempPlaceUpdated
 */
void cardFrame::comboBoxTempPlaceUpdated( wxCommandEvent& event ) {
    int place;

    if ( comboBoxTempPlace->GetValue().IsSameAs( string_placeMouth ) ) {
        place = PLACE_MOUTH;
        comboBoxTempCorrectionMouth->Enable( false );
        comboBoxTempCorrectionVagina->Enable( true );
        comboBoxTempCorrectionRectum->Enable( true );
    } else if ( comboBoxTempPlace->GetValue().IsSameAs( string_placeRectum ) ) {
        place = PLACE_RECTUM;
        comboBoxTempCorrectionMouth->Enable( true );
        comboBoxTempCorrectionVagina->Enable( true );
        comboBoxTempCorrectionRectum->Enable( false );
    } else {
        place = PLACE_VAGINA;
        comboBoxTempCorrectionMouth->Enable( true );
        comboBoxTempCorrectionVagina->Enable( false );
        comboBoxTempCorrectionRectum->Enable( true );
    }

    if ( place == m_cycleData->getCard()->getTemperatureUsualMeasurementPlace() ) {
        if ( changesTempPlace->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes--;
            changesTempPlace->SetLabel( wxEmptyString );
        }
    } else {
        if ( !changesTempPlace->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes++;
            changesTempPlace->SetLabel( _T( "*" ) );
        }
    }

    updateButtonsState();
}

/**
 * comboBoxTempCorrectionMouthUpdated
 */
void cardFrame::comboBoxTempCorrectionMouthUpdated( wxCommandEvent& event ) {
    if ( comboBoxTempCorrectionMouth->GetValue().IsSameAs( m_util.temperatureToStr( m_cycleData->getCard()->getTemperatureCorrectionWhenMeasuredInMouth(), true, true ) ) ) {
        if ( changesTempCorrectionMouth->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes--;
            changesTempCorrectionMouth->SetLabel( wxEmptyString );
        }
    } else {
        if ( !changesTempCorrectionMouth->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes++;
            changesTempCorrectionMouth->SetLabel( _T( "*" ) );
        }
    }

    updateButtonsState();
}

/**
 * comboBoxTempCorrectionVaginaUpdated
 */
void cardFrame::comboBoxTempCorrectionVaginaUpdated( wxCommandEvent& event ) {
    if ( comboBoxTempCorrectionVagina->GetValue().IsSameAs( m_util.temperatureToStr( m_cycleData->getCard()->getTemperatureCorrectionWhenMeasuredInVagina(), true, true ) ) ) {
        if ( changesTempCorrectionVagina->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes--;
            changesTempCorrectionVagina->SetLabel( wxEmptyString );
        }
    } else {
        if ( !changesTempCorrectionVagina->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes++;
            changesTempCorrectionVagina->SetLabel( _T( "*" ) );
        }
    }

    updateButtonsState();
}

/**
 * comboBoxTempCorrectionRectumUpdated
 */
void cardFrame::comboBoxTempCorrectionRectumUpdated( wxCommandEvent& event ) {
    if ( comboBoxTempCorrectionRectum->GetValue().IsSameAs( m_util.temperatureToStr( m_cycleData->getCard()->getTemperatureCorrectionWhenMeasuredInRectum(), true, true ) ) ) {
        if ( changesTempCorrectionRectum->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes--;
            changesTempCorrectionRectum->SetLabel( wxEmptyString );
        }
    } else {
        if ( !changesTempCorrectionRectum->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes++;
            changesTempCorrectionRectum->SetLabel( _T( "*" ) );
        }
    }

    updateButtonsState();
}

/**
 * comboBoxTempCorrectionTimeUpdated
 */
void cardFrame::comboBoxTempCorrectionTimeUpdated( wxCommandEvent& event ) {
    // TODO
    if ( comboBoxTempCorrectionTime->GetValue().IsSameAs( m_util.temperatureToStr( m_cycleData->getCard()->getTemperatureCorrectionForMeasurementTimeSake(), true, true ) ) ) {
        if ( changesTempCorrectionTime->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes--;
            changesTempCorrectionTime->SetLabel( wxEmptyString );
        }
    } else {
        if ( !changesTempCorrectionTime->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes++;
            changesTempCorrectionTime->SetLabel( _T( "*" ) );
        }
    }

    updateButtonsState();
}

/**
 * textNotesUpdated
 */
void cardFrame::textNotesUpdated( wxCommandEvent& event ) {
    if ( !m_notesEventProcessing ) {
        m_notesEventProcessing = true;

        wxString value = textNotes->GetValue();

        if ( value.Length() > 0 && value[value.Length()-1] == '\n' ) {

            value = value.SubString( 0, value.Length() - 2 );
            textNotes->SetValue( value );
            buttonSaveClick( event );
        } else {
            if ( value.IsSameAs( m_cycleData->getCard()->getNotes() ) ) {
                if ( changesNotes->GetLabel().IsSameAs( _T( "*" ) ) ) {
                    m_changes--;
                    changesNotes->SetLabel( wxEmptyString );
                }
            } else {
                if ( !changesNotes->GetLabel().IsSameAs( _T( "*" ) ) ) {
                    m_changes++;
                    changesNotes->SetLabel( _T( "*" ) );
                }
            }

            updateButtonsState();
        }

        m_notesEventProcessing = false;
    }
}

/**
 * textNameUpdated
 */
void cardFrame::textNameUpdated( wxCommandEvent& event ) {
    if ( textName->GetValue().IsSameAs( m_cycleData->getName() ) ) {
        if ( changesName->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes--;
            changesName->SetLabel( wxEmptyString );
        }
    } else {
        if ( !changesName->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes++;
            changesName->SetLabel( _T( "*" ) );
        }
    }

    updateButtonsState();
}

/**
 * datePickerBirthdayDayDateChanged
 */
void cardFrame::datePickerBirthdayDayDateChanged( wxDateEvent& event ) {
    if ( datePickerBirthdayDay->GetValue().IsSameDate( m_cycleData->getBirthdayDay() ) ) {
        if ( changesBirthdayDay->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes--;
            changesBirthdayDay->SetLabel( wxEmptyString );
        }
    } else {
        if ( !changesBirthdayDay->GetLabel().IsSameAs( _T( "*" ) ) ) {
            m_changes++;
            changesBirthdayDay->SetLabel( _T( "*" ) );
        }
    }

    updateButtonsState();
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
void cardFrame::setButtonsStyle() {
    int flatButton = 0;

    if ( m_config->useFlatButtons )
        flatButton = wxNO_BORDER;

    buttonSave->SetWindowStyle( flatButton );
    buttonCancel->SetWindowStyle( flatButton );
    buttonClose->SetWindowStyle( flatButton );
    buttonSave->Refresh();
    buttonCancel->Refresh();
    buttonClose->Refresh();
}


/**
 * update data displayed in the frame.
 */
void cardFrame::update() {
    // TODO - put ASSERTS here
    if ( m_cycleData->getActiveCard() == 0 ) {

    }

    if ( m_cycleData->getCardsCount() == 0 ) {

    }

    if ( m_cycleData->getCard() == NULL ) {

    }

    if ( m_cycleData->getActiveCard() > 0 && m_cycleData->getCardsCount() > 0 && m_cycleData->getCard() != NULL ) {
        textCardNo->SetLabel( m_util.intToStr( m_cycleData->getActiveCard() ) );
        datePicker1stDayOfCycle->SetValue( m_cycleData->getCard()->getFirstDayOfCycle() );

        if ( m_cycleData->getCardsCount() == 1 && m_cycleData->getDaysCount() == 1 ) {
            datePicker1stDayOfCycle->Enable( true );
        } else {
            datePicker1stDayOfCycle->Enable( false );
        }

        wxString tH = m_cycleData->getCard()->getTemperatureUsualMeasurementTime().Format( _T( "%H" ) );

        if ( tH.StartsWith( _T( "0" ) ) )
            tH = tH.Mid( 1 );

        comboBoxTempTimeHour->SetValue( tH );
        comboBoxTempTimeMinute->SetValue( m_cycleData->getCard()->getTemperatureUsualMeasurementTime().Format( _T( "%M" ) ) );
        comboBoxTempCorrectionMouth->SetValue( m_util.temperatureToStr( m_cycleData->getCard()->getTemperatureCorrectionWhenMeasuredInMouth(), true, true ) );
        comboBoxTempCorrectionVagina->SetValue( m_util.temperatureToStr( m_cycleData->getCard()->getTemperatureCorrectionWhenMeasuredInVagina(), true, true ) );
        comboBoxTempCorrectionRectum->SetValue( m_util.temperatureToStr( m_cycleData->getCard()->getTemperatureCorrectionWhenMeasuredInRectum(), true, true ) );
        comboBoxTempCorrectionTime->SetValue( m_util.temperatureToStr( m_cycleData->getCard()->getTemperatureCorrectionForMeasurementTimeSake(), true, true ) );

        int dataInt = m_cycleData->getCard()->getTemperatureUsualMeasurementPlace();
        switch ( dataInt ) {
        case PLACE_MOUTH: {
            comboBoxTempPlace->SetValue( string_placeMouth );
            comboBoxTempCorrectionMouth->Enable( false );
            comboBoxTempCorrectionVagina->Enable( true );
            comboBoxTempCorrectionRectum->Enable( true );
            break;
        }
        case PLACE_RECTUM: {
            comboBoxTempPlace->SetValue( string_placeRectum );
            comboBoxTempCorrectionMouth->Enable( true );
            comboBoxTempCorrectionVagina->Enable( true );
            comboBoxTempCorrectionRectum->Enable( false );
            break;
        }
        default: {
            comboBoxTempPlace->SetValue( string_placeVagina );
            comboBoxTempCorrectionMouth->Enable( true );
            comboBoxTempCorrectionVagina->Enable( false );
            comboBoxTempCorrectionRectum->Enable( true );
            break;
        }
        }

        textNotes->SetValue( m_cycleData->getCard()->getNotes() ) ;

        textNotes->SetInsertionPointEnd();

        if ( m_cycleData->getCard()->getCardLocked() ) {
            comboBoxTempTimeHour->Enable( false );
            comboBoxTempTimeMinute->Enable( false );
            comboBoxTempPlace->Enable( false );
            comboBoxTempCorrectionMouth->Enable( false );
            comboBoxTempCorrectionVagina->Enable( false );
            comboBoxTempCorrectionRectum->Enable( false );
            comboBoxTempCorrectionTime->Enable( false );
            textNotes->Enable( false );
        } else {
            comboBoxTempTimeHour->Enable( true );
            comboBoxTempTimeMinute->Enable( true );
            comboBoxTempPlace->Enable( true );
            comboBoxTempCorrectionTime->Enable( true );
            textNotes->Enable( true );
        }

    } else {
        textCardNo->SetLabel( _T( "???" ) );
        datePicker1stDayOfCycle->SetValue( wxDateTime::Today() );

        comboBoxTempTimeHour->SetValue( _T( "7" ) );
        comboBoxTempTimeMinute->SetValue( _T( "00" ) );

        comboBoxTempCorrectionMouth->SetValue( _T( "0" ) );
        comboBoxTempCorrectionVagina->SetValue( _T( "0" ) );
        comboBoxTempCorrectionRectum->SetValue( _T( "0" ) );

        comboBoxTempPlace->SetValue( string_placeVagina );
        textNotes->SetValue( wxEmptyString ) ;

        datePicker1stDayOfCycle->Enable( false );
        comboBoxTempTimeHour->Enable( false );
        comboBoxTempTimeMinute->Enable( false );
        comboBoxTempPlace->Enable( false );
        comboBoxTempCorrectionMouth->Enable( false );
        comboBoxTempCorrectionVagina->Enable( false );
        comboBoxTempCorrectionRectum->Enable( false );
        comboBoxTempCorrectionTime->Enable( false );
        textNotes->Enable( false );
    }

    textName->SetValue( m_cycleData->getName() );

    datePickerBirthdayDay->SetValue( m_cycleData->getBirthdayDay() );

    // TODO - put ASSERT here
    if ( m_cycleData->getName().length() == 0 ) {

    }

    m_changes = 0;
    changes1stDayOfCycle->SetLabel( wxEmptyString );
    changesTempTime->SetLabel( wxEmptyString );
    changesTempPlace->SetLabel( wxEmptyString );
    changesTempCorrectionMouth->SetLabel( wxEmptyString );
    changesTempCorrectionVagina->SetLabel( wxEmptyString );
    changesTempCorrectionRectum->SetLabel( wxEmptyString );
    changesTempCorrectionTime->SetLabel( wxEmptyString );
    changesNotes->SetLabel( wxEmptyString );
    changesName->SetLabel( wxEmptyString );
    changesBirthdayDay->SetLabel( wxEmptyString );

    updateButtonsState();
}

/**
 * update values of temperatureCorrectedValue for each day in active card.
 */
void cardFrame::updateTemperatureCorrectedValues() {
    for ( int i = 1; i <= m_cycleData->getDaysCount(); i++ ) {
        m_cycleData->getDay( i )->setTemperatureValueAfterCorrections( m_cycleData->calculateCorrectTemperatureValue( i ) );
    }
}

/**
 * update the buttons state (buttonSave, buttonCancel).
 */
void cardFrame::updateButtonsState() {
    if ( m_changes == 0 ) {
        buttonSave->Enable( false );
        buttonCancel->Enable( false );
    } else {
        buttonSave->Enable( true );
        buttonCancel->Enable( true );
    }
}

/**
 * ask to save chages and next check if value of the 'name' is not
 * empty - if it's empty then do not let to exit the window.
 */
bool cardFrame::checkIfCanExit( bool cancelAllowed ) {
    if ( m_changes > 0 ) {
        if (m_config->autosaveChanges) {
            save();
            return true;
        }

        int answer;

        if ( cancelAllowed ) {
            answer = wxMessageBox( _( "Save card's data changes? \nNote: Not saved data will be lost!" ) , _( "Warning" ), wxYES_NO | wxCANCEL );
        } else {
            answer = wxMessageBox( _( "Save card's data changes? \nNote: Not saved data will be lost!" ) , _( "Warning" ), wxYES_NO );
        }

        if ( answer == wxYES ) {
            save();
        }

        if ( answer == wxCANCEL ) {
            return false;
        } else {
            return true;
        }
    } else {
        return true;
    }


}

/**
 * save updated data to the m_cycleData object and refresh the view.
 */
bool cardFrame::save() {
    if ( m_changes > 0 ) {
        // TODO - put ASSERTS here
        if ( m_cycleData->getActiveCard() == 0 ) {

        }

        if ( m_cycleData->getCardsCount() == 0 ) {

        }

        if ( m_cycleData->getCard() == NULL ) {

        }

        if ( m_cycleData->getActiveCard() > 0 && m_cycleData->getCardsCount() > 0 && m_cycleData->getCard() != NULL ) {
            m_cycleData->getCard()->setFirstDayOfCycle( datePicker1stDayOfCycle->GetValue() );
            m_cycleData->getCard()->setTemperatureUsualMeasurementTime( wxDateTime( m_util.strToInt( comboBoxTempTimeHour->GetValue() ), m_util.strToInt( comboBoxTempTimeMinute->GetValue() ), 0, 0 ) );
            m_cycleData->getCard()->setTemperatureCorrectionWhenMeasuredInMouth( m_util.strToTemperature( comboBoxTempCorrectionMouth->GetValue() ) );
            m_cycleData->getCard()->setTemperatureCorrectionWhenMeasuredInVagina( m_util.strToTemperature( comboBoxTempCorrectionVagina->GetValue() ) );
            m_cycleData->getCard()->setTemperatureCorrectionWhenMeasuredInRectum( m_util.strToTemperature( comboBoxTempCorrectionRectum->GetValue() ) );
            m_cycleData->getCard()->setTemperatureCorrectionForMeasurementTimeSake( m_util.strToTemperature( comboBoxTempCorrectionTime->GetValue() ) );

            if ( comboBoxTempPlace->GetValue().IsSameAs( string_placeMouth ) ) {
                m_cycleData->getCard()->setTemperatureUsualMeasurementPlace( PLACE_MOUTH );
            } else if ( comboBoxTempPlace->GetValue().IsSameAs( string_placeRectum ) ) {
                m_cycleData->getCard()->setTemperatureUsualMeasurementPlace( PLACE_RECTUM );
            } else {
                m_cycleData->getCard()->setTemperatureUsualMeasurementPlace( PLACE_VAGINA );
            }

            m_cycleData->getCard()->setNotes( textNotes->GetValue() );
        }

        m_cycleData->setName( textName->GetValue() );
        m_cycleData->setBirthdayDay( datePickerBirthdayDay->GetValue() );

        // TODO - put ASSERTS here
        if ( m_cycleData->getName().length() == 0 ) {

        }

        m_cycleData->setCardModified( true );
    }

    if ( changes1stDayOfCycle->GetLabel().IsSameAs( _T( "*" ) ) ) {
        sendDataUpdateEvent( ACTIVE_CARD_UPDATE_WITH_1ST_DAY, _T( "refresh current card - 1st day of the cycle has been changed." ) );
    } else if ( changesTempTime->GetLabel().IsSameAs( _T( "*" ) ) ||
                changesTempPlace->GetLabel().IsSameAs( _T( "*" ) ) ||
                changesTempCorrectionTime->GetLabel().IsSameAs( _T( "*" ) )
              ) {
        updateTemperatureCorrectedValues();

        if ( m_cycleData->getCard()->getResultTemperatureHighLevelStart() > 0 ) {
            m_cycleData->setResultTemperaturesLevels( m_cycleData->getActiveCard() , m_cycleData->getCard()->getResultTemperatureHighLevelStart(), false );

        }
        sendDataUpdateEvent( ACTIVE_CARD_UPDATE_WITH_TEMP, _T( "refresh current card - temperature related data have been changed." ) );
    } else if ( changesTempCorrectionMouth->GetLabel().IsSameAs( _T( "*" ) ) ||
                changesTempCorrectionVagina->GetLabel().IsSameAs( _T( "*" ) ) ||
                changesTempCorrectionRectum->GetLabel().IsSameAs( _T( "*" ) )
              ) {
        updateTemperatureCorrectedValues();

        if ( m_cycleData->getCard()->getResultTemperatureHighLevelStart() > 0 ) {
            m_cycleData->setResultTemperaturesLevels( m_cycleData->getActiveCard() , m_cycleData->getCard()->getResultTemperatureHighLevelStart(), false );
        }

        sendDataUpdateEvent( ACTIVE_CARD_UPDATE_WITH_PLACES, _T( "refresh current card - temperature measuring placed data have been changed." ) );
    } else {
        sendDataUpdateEvent( ACTIVE_CARD_UPDATE, _T( "refresh current card - temperature related data have not been changed." ) );
    }

    return true;
}

/**
 *
 */
void cardFrame::sendDataUpdateEvent( int id, wxString message ) {
    wxCommandEvent event( wxEVT_CARD_DATA_MODIFIED_EVENT, CARD_EVENT );
    event.SetInt( id );
    event.SetString( message );
    wxPostEvent( m_parent, event );
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/
