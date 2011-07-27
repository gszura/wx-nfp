/***************************************************************
 * Name:      dayFrame.cpp
 * Purpose:   Dialog for editing day's data
 * Author:    Grzegorz Szura (grzegorz@szura.net)
 * Created:   2010-03-02
 * Copyright: Grzegorz Szura (http://www.szura.net)
 * License:
 **************************************************************/

#include "dayFrame.h"
#include "../data/xpm/wx-nfp.xpm"
#include "cyclesData_declarations.h"

//(*InternalHeaders(dayFrame)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

/******************************************************************************/

//(*IdInit(dayFrame)
const long dayFrame::ID_staticCardNo = wxNewId();
const long dayFrame::ID_textCardNo = wxNewId();
const long dayFrame::ID_space1 = wxNewId();
const long dayFrame::ID_space2 = wxNewId();
const long dayFrame::ID_staticCycleDay = wxNewId();
const long dayFrame::ID_textCycleDay = wxNewId();
const long dayFrame::ID_buttonPreviousDay = wxNewId();
const long dayFrame::ID_buttonNextDay = wxNewId();
const long dayFrame::ID_staticDate = wxNewId();
const long dayFrame::ID_textDate = wxNewId();
const long dayFrame::ID_buttonAddNewDay = wxNewId();
const long dayFrame::ID_staticCardLocked = wxNewId();
const long dayFrame::ID_staticMenstruation = wxNewId();
const long dayFrame::ID_checkBoxMenstruation1 = wxNewId();
const long dayFrame::ID_checkBoxMenstruation2 = wxNewId();
const long dayFrame::ID_textCoitusRecordCounter = wxNewId();
const long dayFrame::ID_changesMenstruation = wxNewId();
const long dayFrame::ID_staticCoitusRecord = wxNewId();
const long dayFrame::ID_textCoitusRecord = wxNewId();
const long dayFrame::ID_buttonCoitusRecordMinus = wxNewId();
const long dayFrame::ID_buttonCoitusRecordPlus = wxNewId();
const long dayFrame::ID_changesCoitusRecord = wxNewId();
const long dayFrame::ID_checkBoxOtherDisturbances = wxNewId();
const long dayFrame::ID_changesOtherDisturbances = wxNewId();
const long dayFrame::ID_staticMucusFeeling = wxNewId();
const long dayFrame::ID_comboBoxMucusFeeling = wxNewId();
const long dayFrame::ID_changesMucusFeeling = wxNewId();
const long dayFrame::ID_staticMucusAppearance = wxNewId();
const long dayFrame::ID_textMucusAppearance = wxNewId();
const long dayFrame::ID_changesMucusAppearance = wxNewId();
const long dayFrame::ID_checkBoxMucusAppearanceOpaque = wxNewId();
const long dayFrame::ID_checkBoxMucusAppearanceWhite = wxNewId();
const long dayFrame::ID_checkBoxMucusAppearanceYellowish = wxNewId();
const long dayFrame::ID_checkBoxMucusAppearanceTacky = wxNewId();
const long dayFrame::ID_checkBoxMucusAppearanceClear = wxNewId();
const long dayFrame::ID_checkBoxMucusAppearanceStretchy = wxNewId();
const long dayFrame::ID_checkBoxMucusAppearanceSeminalResidue = wxNewId();
const long dayFrame::ID_staticMucusAmount = wxNewId();
const long dayFrame::ID_checkBoxMucusAmount1 = wxNewId();
const long dayFrame::ID_checkBoxMucusAmount2 = wxNewId();
const long dayFrame::ID_checkBoxMucusAmount3 = wxNewId();
const long dayFrame::ID_staticLengthOfStretch = wxNewId();
const long dayFrame::ID_checkBoxLengthOfStretch1 = wxNewId();
const long dayFrame::ID_checkBoxLengthOfStretch2 = wxNewId();
const long dayFrame::ID_checkBoxLengthOfStretch3 = wxNewId();
const long dayFrame::ID_staticMeasuredTemperature = wxNewId();
const long dayFrame::ID_comboBoxMeasuredTemperature = wxNewId();
const long dayFrame::ID_changesMeasuredTemperature = wxNewId();
const long dayFrame::ID_staticMeasurementTime = wxNewId();
const long dayFrame::ID_comboBoxMeasurementTimeHour = wxNewId();
const long dayFrame::ID_comboBoxMeasurementTimeMinute = wxNewId();
const long dayFrame::ID_changesMeasuredTime = wxNewId();
const long dayFrame::ID_staticMeasurementPlace = wxNewId();
const long dayFrame::ID_comboBoxMeasurementPlace = wxNewId();
const long dayFrame::ID_changesMeasuredPlace = wxNewId();
const long dayFrame::ID_checkBoxTemperatureDisturbances = wxNewId();
const long dayFrame::ID_changesTemperatureDisturbances = wxNewId();
const long dayFrame::ID_staticAdditionalTemperatureCorrection = wxNewId();
const long dayFrame::ID_comboBoxAdditionalTemperatureCorrection = wxNewId();
const long dayFrame::ID_changesAdditionalTemperatureCorrection = wxNewId();
const long dayFrame::ID_staticTemperatureAfterCorections = wxNewId();
const long dayFrame::ID_textTemperatureAfterCorections = wxNewId();
const long dayFrame::ID_space3 = wxNewId();
const long dayFrame::ID_staticCervixPosition = wxNewId();
const long dayFrame::ID_comboBoxCervixPosition = wxNewId();
const long dayFrame::ID_changesCervixPosition = wxNewId();
const long dayFrame::ID_staticCervixDilation = wxNewId();
const long dayFrame::ID_comboBoxCervixDilation = wxNewId();
const long dayFrame::ID_changesCervixDilation = wxNewId();
const long dayFrame::ID_staticCervixHardness = wxNewId();
const long dayFrame::ID_comboBoxCervixHardness = wxNewId();
const long dayFrame::ID_changesCervixHardness = wxNewId();
const long dayFrame::ID_staticOvulationPain = wxNewId();
const long dayFrame::ID_checkBoxOvulationPain1 = wxNewId();
const long dayFrame::ID_checkBoxOvulationPain2 = wxNewId();
const long dayFrame::ID_changesOvulationPain = wxNewId();
const long dayFrame::ID_staticBreastsTension = wxNewId();
const long dayFrame::ID_checkBoxBreastsTension1 = wxNewId();
const long dayFrame::ID_checkBoxBreastsTension2 = wxNewId();
const long dayFrame::ID_changesBreastsTension = wxNewId();
const long dayFrame::ID_staticSpotting = wxNewId();
const long dayFrame::ID_checkBoxSpotting1 = wxNewId();
const long dayFrame::ID_checkBoxSpotting2 = wxNewId();
const long dayFrame::ID_changesSpotting = wxNewId();
const long dayFrame::ID_staticAdditionalNotes = wxNewId();
const long dayFrame::ID_changesAdditionalNotes = wxNewId();
const long dayFrame::ID_textAdditionalNotes = wxNewId();
const long dayFrame::ID_buttonSave = wxNewId();
const long dayFrame::ID_buttonCancel = wxNewId();
const long dayFrame::ID_staticSpace7 = wxNewId();
const long dayFrame::ID_buttonClose = wxNewId();
const long dayFrame::ID_panelMain = wxNewId();
//*)

BEGIN_EVENT_TABLE(dayFrame,wxDialog)
     //(*EventTable(dayFrame)
     //*)
END_EVENT_TABLE()

/******************************************************************************/

const wxEventType wxEVT_DAY_DATA_MODIFIED_EVENT = wxNewEventType();

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
dayFrame::dayFrame(wxWindow* parent, configClass *config, cycleDataClass *cycleData, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
     m_parent = parent;
     m_config = config;
     m_cycleData = cycleData;

     m_textAdditionalNotesEventProcessing = false;
     m_none = _T( "----" );
     m_temperatureAfterCorections = -1;

     buildGui(parent);
}

/**
 * Build GUI
 */
void dayFrame::buildGui(wxWindow* parent)
{
     //(*Initialize(dayFrame)
     wxBoxSizer* sizerMucus4;
     wxBoxSizer* sizerMain2;
     wxFlexGridSizer* sizerHeader3;
     wxBoxSizer* sizerMucus3;
     wxBoxSizer* sizerHeader4;
     wxFlexGridSizer* sizerOther1;
     wxFlexGridSizer* sizerTemperature1;
     wxFlexGridSizer* sizerTemperature3;
     wxFlexGridSizer* sizerMucus5;
     wxBoxSizer* sizerMain1;
     wxBoxSizer* sizerDataRight;
     wxBoxSizer* sizerMeasurementTime;
     wxBoxSizer* sizerTemperature2;
     wxFlexGridSizer* sizerMucus1;
     wxFlexGridSizer* sizerCervix1;
     wxBoxSizer* sizerMucus2;
     wxStaticBoxSizer* sizerTemperature;
     wxBoxSizer* sizerMenstruation;
     wxStaticBoxSizer* sizerBasic;
     wxBoxSizer* sizerDate;
     wxBoxSizer* sizerDataLeft;
     wxBoxSizer* sizerButtons;
     wxBoxSizer* sizerHeader1;
     wxStaticBoxSizer* sizerHeader;
     wxBoxSizer* sizerAdditionalNotes;
     wxBoxSizer* BoxSizer1;
     wxFlexGridSizer* sizerGeneral1;
     wxBoxSizer* sizerHeader2;
     wxStaticBoxSizer* sizerOther;
     wxBoxSizer* sizerCoitusRecord;
     wxStaticBoxSizer* sizerMucus;
     wxStaticBoxSizer* sizerCervix;
     wxBoxSizer* sizerData;
     
     Create(parent, wxID_ANY, _("NFP - edit day\'s data"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
     SetClientSize(wxSize(479,510));
     sizerMain1 = new wxBoxSizer(wxHORIZONTAL);
     panelMain = new wxPanel(this, ID_panelMain, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_panelMain"));
     sizerMain2 = new wxBoxSizer(wxVERTICAL);
     sizerHeader = new wxStaticBoxSizer(wxHORIZONTAL, panelMain, wxEmptyString);
     sizerHeader1 = new wxBoxSizer(wxHORIZONTAL);
     sizerHeader2 = new wxBoxSizer(wxVERTICAL);
     sizerHeader3 = new wxFlexGridSizer(0, 4, 0, 0);
     sizerHeader3->AddGrowableCol(1);
     staticCardNo = new wxStaticText(panelMain, ID_staticCardNo, _("card number"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticCardNo"));
     sizerHeader3->Add(staticCardNo, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     textCardNo = new wxStaticText(panelMain, ID_textCardNo, _("999"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_textCardNo"));
     textCardNo->SetForegroundColour(wxColour(0,0,128));
     wxFont textCardNoFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
     if ( !textCardNoFont.Ok() ) textCardNoFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
     textCardNoFont.SetPointSize((int)(textCardNoFont.GetPointSize() * 1.000000));
     textCardNoFont.SetWeight(wxBOLD);
     textCardNo->SetFont(textCardNoFont);
     sizerHeader3->Add(textCardNo, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
     space1 = new wxStaticText(panelMain, ID_space1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_space1"));
     sizerHeader3->Add(space1, 0, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     space2 = new wxStaticText(panelMain, ID_space2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_space2"));
     sizerHeader3->Add(space2, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     staticCycleDay = new wxStaticText(panelMain, ID_staticCycleDay, _("day of cycle"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticCycleDay"));
     sizerHeader3->Add(staticCycleDay, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     textCycleDay = new wxStaticText(panelMain, ID_textCycleDay, _("999"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_textCycleDay"));
     textCycleDay->SetMinSize(wxSize(-1,-1));
     textCycleDay->SetForegroundColour(wxColour(0,0,128));
     wxFont textCycleDayFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
     if ( !textCycleDayFont.Ok() ) textCycleDayFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
     textCycleDayFont.SetPointSize((int)(textCycleDayFont.GetPointSize() * 1.000000));
     textCycleDayFont.SetWeight(wxBOLD);
     textCycleDay->SetFont(textCycleDayFont);
     sizerHeader3->Add(textCycleDay, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
     buttonPreviousDay = new wxButton(panelMain, ID_buttonPreviousDay, _("<"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_buttonPreviousDay"));
     buttonPreviousDay->SetToolTip(_("Go to previous day of the card"));
     sizerHeader3->Add(buttonPreviousDay, 0, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     buttonNextDay = new wxButton(panelMain, ID_buttonNextDay, _(">"), wxDefaultPosition, wxSize(40,-1), 0, wxDefaultValidator, _T("ID_buttonNextDay"));
     buttonNextDay->SetToolTip(_("Go to next day of the card"));
     sizerHeader3->Add(buttonNextDay, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerHeader2->Add(sizerHeader3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     sizerDate = new wxBoxSizer(wxHORIZONTAL);
     staticDate = new wxStaticText(panelMain, ID_staticDate, _("date"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticDate"));
     sizerDate->Add(staticDate, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     textDate = new wxStaticText(panelMain, ID_textDate, _("999"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_textDate"));
     textDate->SetForegroundColour(wxColour(0,0,128));
     wxFont textDateFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
     if ( !textDateFont.Ok() ) textDateFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
     textDateFont.SetPointSize((int)(textDateFont.GetPointSize() * 1.000000));
     textDateFont.SetWeight(wxBOLD);
     textDate->SetFont(textDateFont);
     sizerDate->Add(textDate, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
     sizerHeader2->Add(sizerDate, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     sizerHeader1->Add(sizerHeader2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerHeader4 = new wxBoxSizer(wxVERTICAL);
     buttonAddNewDay = new wxButton(panelMain, ID_buttonAddNewDay, _("add new day"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_buttonAddNewDay"));
     sizerHeader4->Add(buttonAddNewDay, 0, wxALL|wxALIGN_RIGHT|wxALIGN_TOP, 5);
     staticCardLocked = new wxStaticText(panelMain, ID_staticCardLocked, _("Card is locked!\nData are protected against any changes."), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE, _T("ID_staticCardLocked"));
     staticCardLocked->SetForegroundColour(wxColour(255,0,0));
     wxFont staticCardLockedFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
     if ( !staticCardLockedFont.Ok() ) staticCardLockedFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
     staticCardLockedFont.SetPointSize((int)(staticCardLockedFont.GetPointSize() * 1.000000));
     staticCardLockedFont.SetWeight(wxBOLD);
     staticCardLocked->SetFont(staticCardLockedFont);
     sizerHeader4->Add(staticCardLocked, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
     sizerHeader1->Add(sizerHeader4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerHeader->Add(sizerHeader1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     sizerMain2->Add(sizerHeader, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerData = new wxBoxSizer(wxHORIZONTAL);
     sizerDataLeft = new wxBoxSizer(wxVERTICAL);
     sizerBasic = new wxStaticBoxSizer(wxVERTICAL, panelMain, wxEmptyString);
     sizerGeneral1 = new wxFlexGridSizer(0, 3, 0, 0);
     sizerGeneral1->AddGrowableCol(0);
     staticMenstruation = new wxStaticText(panelMain, ID_staticMenstruation, _("menstruation"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticMenstruation"));
     sizerGeneral1->Add(staticMenstruation, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     sizerMenstruation = new wxBoxSizer(wxHORIZONTAL);
     checkBoxMenstruation1 = new wxCheckBox(panelMain, ID_checkBoxMenstruation1, _("/"), wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_checkBoxMenstruation1"));
     checkBoxMenstruation1->SetValue(false);
     checkBoxMenstruation1->SetToolTip(_("Small bleeding"));
     sizerMenstruation->Add(checkBoxMenstruation1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxMenstruation2 = new wxCheckBox(panelMain, ID_checkBoxMenstruation2, _("X"), wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_checkBoxMenstruation2"));
     checkBoxMenstruation2->SetValue(false);
     checkBoxMenstruation2->SetToolTip(_("Heavy bleeding"));
     sizerMenstruation->Add(checkBoxMenstruation2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     textCoitusRecordCounter = new wxStaticText(panelMain, ID_textCoitusRecordCounter, wxEmptyString, wxDefaultPosition, wxSize(25,-1), wxALIGN_RIGHT, _T("ID_textCoitusRecordCounter"));
     textCoitusRecordCounter->SetForegroundColour(wxColour(64,128,128));
     sizerMenstruation->Add(textCoitusRecordCounter, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
     sizerGeneral1->Add(sizerMenstruation, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     changesMenstruation = new wxStaticText(panelMain, ID_changesMenstruation, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesMenstruation"));
     changesMenstruation->SetForegroundColour(wxColour(255,0,0));
     sizerGeneral1->Add(changesMenstruation, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     staticCoitusRecord = new wxStaticText(panelMain, ID_staticCoitusRecord, _("coitus record"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticCoitusRecord"));
     sizerGeneral1->Add(staticCoitusRecord, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     sizerCoitusRecord = new wxBoxSizer(wxHORIZONTAL);
     textCoitusRecord = new wxTextCtrl(panelMain, ID_textCoitusRecord, wxEmptyString, wxDefaultPosition, wxSize(80,-1), wxTE_READONLY|wxTE_CENTRE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_textCoitusRecord"));
     sizerCoitusRecord->Add(textCoitusRecord, 1, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     buttonCoitusRecordMinus = new wxButton(panelMain, ID_buttonCoitusRecordMinus, _("-"), wxDefaultPosition, wxSize(25,-1), 0, wxDefaultValidator, _T("ID_buttonCoitusRecordMinus"));
     sizerCoitusRecord->Add(buttonCoitusRecordMinus, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     buttonCoitusRecordPlus = new wxButton(panelMain, ID_buttonCoitusRecordPlus, _("+"), wxDefaultPosition, wxSize(25,-1), 0, wxDefaultValidator, _T("ID_buttonCoitusRecordPlus"));
     sizerCoitusRecord->Add(buttonCoitusRecordPlus, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerGeneral1->Add(sizerCoitusRecord, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     changesCoitusRecord = new wxStaticText(panelMain, ID_changesCoitusRecord, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesCoitusRecord"));
     changesCoitusRecord->SetForegroundColour(wxColour(255,0,0));
     sizerGeneral1->Add(changesCoitusRecord, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerBasic->Add(sizerGeneral1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
     checkBoxOtherDisturbances = new wxCheckBox(panelMain, ID_checkBoxOtherDisturbances, _("disturbances (other than temperature)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxOtherDisturbances"));
     checkBoxOtherDisturbances->SetValue(false);
     BoxSizer1->Add(checkBoxOtherDisturbances, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesOtherDisturbances = new wxStaticText(panelMain, ID_changesOtherDisturbances, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesOtherDisturbances"));
     changesOtherDisturbances->SetForegroundColour(wxColour(255,0,0));
     BoxSizer1->Add(changesOtherDisturbances, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerBasic->Add(BoxSizer1, 0, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerDataLeft->Add(sizerBasic, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerMucus = new wxStaticBoxSizer(wxVERTICAL, panelMain, _("mucus observation"));
     sizerMucus1 = new wxFlexGridSizer(0, 3, 0, 0);
     sizerMucus1->AddGrowableCol(0);
     staticMucusFeeling = new wxStaticText(panelMain, ID_staticMucusFeeling, _("feeling, experience"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticMucusFeeling"));
     staticMucusFeeling->SetToolTip(_("External observation"));
     sizerMucus1->Add(staticMucusFeeling, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     comboBoxMucusFeeling = new wxComboBox(panelMain, ID_comboBoxMucusFeeling, wxEmptyString, wxDefaultPosition, wxSize(100,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxMucusFeeling"));
     comboBoxMucusFeeling->SetToolTip(_("External observation"));
     sizerMucus1->Add(comboBoxMucusFeeling, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesMucusFeeling = new wxStaticText(panelMain, ID_changesMucusFeeling, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesMucusFeeling"));
     changesMucusFeeling->SetForegroundColour(wxColour(255,0,0));
     sizerMucus1->Add(changesMucusFeeling, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     staticMucusAppearance = new wxStaticText(panelMain, ID_staticMucusAppearance, _("appearance"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticMucusAppearance"));
     staticMucusAppearance->SetToolTip(_("Internal observation"));
     sizerMucus1->Add(staticMucusAppearance, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     textMucusAppearance = new wxTextCtrl(panelMain, ID_textMucusAppearance, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_CENTRE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_textMucusAppearance"));
     textMucusAppearance->SetToolTip(_("Internal observation"));
     sizerMucus1->Add(textMucusAppearance, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesMucusAppearance = new wxStaticText(panelMain, ID_changesMucusAppearance, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesMucusAppearance"));
     changesMucusAppearance->SetForegroundColour(wxColour(255,0,0));
     sizerMucus1->Add(changesMucusAppearance, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerMucus->Add(sizerMucus1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     sizerMucus2 = new wxBoxSizer(wxVERTICAL);
     checkBoxMucusAppearanceOpaque = new wxCheckBox(panelMain, ID_checkBoxMucusAppearanceOpaque, _("o - opaque (the opposite of clear)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxMucusAppearanceOpaque"));
     checkBoxMucusAppearanceOpaque->SetValue(false);
     sizerMucus2->Add(checkBoxMucusAppearanceOpaque, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxMucusAppearanceWhite = new wxCheckBox(panelMain, ID_checkBoxMucusAppearanceWhite, _("w - white"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxMucusAppearanceWhite"));
     checkBoxMucusAppearanceWhite->SetValue(false);
     sizerMucus2->Add(checkBoxMucusAppearanceWhite, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxMucusAppearanceYellowish = new wxCheckBox(panelMain, ID_checkBoxMucusAppearanceYellowish, _("y - yellowish"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxMucusAppearanceYellowish"));
     checkBoxMucusAppearanceYellowish->SetValue(false);
     sizerMucus2->Add(checkBoxMucusAppearanceYellowish, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxMucusAppearanceTacky = new wxCheckBox(panelMain, ID_checkBoxMucusAppearanceTacky, _("t - tacky (stretches up to 1 cm)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxMucusAppearanceTacky"));
     checkBoxMucusAppearanceTacky->SetValue(false);
     sizerMucus2->Add(checkBoxMucusAppearanceTacky, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerMucus->Add(sizerMucus2, 0, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerMucus3 = new wxBoxSizer(wxVERTICAL);
     checkBoxMucusAppearanceClear = new wxCheckBox(panelMain, ID_checkBoxMucusAppearanceClear, _("c - clear (a more-fertile mucus)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxMucusAppearanceClear"));
     checkBoxMucusAppearanceClear->SetValue(false);
     sizerMucus3->Add(checkBoxMucusAppearanceClear, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxMucusAppearanceStretchy = new wxCheckBox(panelMain, ID_checkBoxMucusAppearanceStretchy, _("s - stretchy (stretches more than 1 cm)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxMucusAppearanceStretchy"));
     checkBoxMucusAppearanceStretchy->SetValue(false);
     sizerMucus3->Add(checkBoxMucusAppearanceStretchy, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerMucus->Add(sizerMucus3, 0, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerMucus4 = new wxBoxSizer(wxHORIZONTAL);
     checkBoxMucusAppearanceSeminalResidue = new wxCheckBox(panelMain, ID_checkBoxMucusAppearanceSeminalResidue, _("SR - seminal residue from marital relations"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxMucusAppearanceSeminalResidue"));
     checkBoxMucusAppearanceSeminalResidue->SetValue(false);
     sizerMucus4->Add(checkBoxMucusAppearanceSeminalResidue, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerMucus->Add(sizerMucus4, 0, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerMucus5 = new wxFlexGridSizer(0, 4, 0, 0);
     sizerMucus5->AddGrowableCol(0);
     staticMucusAmount = new wxStaticText(panelMain, ID_staticMucusAmount, _("amount of mucus"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticMucusAmount"));
     sizerMucus5->Add(staticMucusAmount, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxMucusAmount1 = new wxCheckBox(panelMain, ID_checkBoxMucusAmount1, _("+"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxMucusAmount1"));
     checkBoxMucusAmount1->SetValue(false);
     checkBoxMucusAmount1->SetToolTip(_("Trace amount"));
     sizerMucus5->Add(checkBoxMucusAmount1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxMucusAmount2 = new wxCheckBox(panelMain, ID_checkBoxMucusAmount2, _("++"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxMucusAmount2"));
     checkBoxMucusAmount2->SetValue(false);
     checkBoxMucusAmount2->SetToolTip(_("Typical amount"));
     sizerMucus5->Add(checkBoxMucusAmount2, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxMucusAmount3 = new wxCheckBox(panelMain, ID_checkBoxMucusAmount3, _("+++"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxMucusAmount3"));
     checkBoxMucusAmount3->SetValue(false);
     checkBoxMucusAmount3->SetToolTip(_("Huge amount"));
     sizerMucus5->Add(checkBoxMucusAmount3, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     staticLengthOfStretch = new wxStaticText(panelMain, ID_staticLengthOfStretch, _("length of stretch in cm"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticLengthOfStretch"));
     sizerMucus5->Add(staticLengthOfStretch, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxLengthOfStretch1 = new wxCheckBox(panelMain, ID_checkBoxLengthOfStretch1, _("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxLengthOfStretch1"));
     checkBoxLengthOfStretch1->SetValue(false);
     sizerMucus5->Add(checkBoxLengthOfStretch1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxLengthOfStretch2 = new wxCheckBox(panelMain, ID_checkBoxLengthOfStretch2, _("2"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxLengthOfStretch2"));
     checkBoxLengthOfStretch2->SetValue(false);
     sizerMucus5->Add(checkBoxLengthOfStretch2, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxLengthOfStretch3 = new wxCheckBox(panelMain, ID_checkBoxLengthOfStretch3, _("3 .."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxLengthOfStretch3"));
     checkBoxLengthOfStretch3->SetValue(false);
     sizerMucus5->Add(checkBoxLengthOfStretch3, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerMucus->Add(sizerMucus5, 1, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerDataLeft->Add(sizerMucus, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerData->Add(sizerDataLeft, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     sizerDataRight = new wxBoxSizer(wxVERTICAL);
     sizerTemperature = new wxStaticBoxSizer(wxVERTICAL, panelMain, _("temperature measurement"));
     sizerTemperature1 = new wxFlexGridSizer(0, 3, 0, 0);
     sizerTemperature1->AddGrowableCol(0);
     staticMeasuredTemperature = new wxStaticText(panelMain, ID_staticMeasuredTemperature, _("temperature"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticMeasuredTemperature"));
     sizerTemperature1->Add(staticMeasuredTemperature, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     comboBoxMeasuredTemperature = new wxComboBox(panelMain, ID_comboBoxMeasuredTemperature, wxEmptyString, wxDefaultPosition, wxSize(120,-1), 0, 0, 0, wxDefaultValidator, _T("ID_comboBoxMeasuredTemperature"));
     sizerTemperature1->Add(comboBoxMeasuredTemperature, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesMeasuredTemperature = new wxStaticText(panelMain, ID_changesMeasuredTemperature, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesMeasuredTemperature"));
     changesMeasuredTemperature->SetForegroundColour(wxColour(255,0,0));
     sizerTemperature1->Add(changesMeasuredTemperature, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     staticMeasurementTime = new wxStaticText(panelMain, ID_staticMeasurementTime, _("measurement time"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticMeasurementTime"));
     sizerTemperature1->Add(staticMeasurementTime, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     sizerMeasurementTime = new wxBoxSizer(wxHORIZONTAL);
     comboBoxMeasurementTimeHour = new wxComboBox(panelMain, ID_comboBoxMeasurementTimeHour, wxEmptyString, wxDefaultPosition, wxSize(60,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxMeasurementTimeHour"));
     sizerMeasurementTime->Add(comboBoxMeasurementTimeHour, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     comboBoxMeasurementTimeMinute = new wxComboBox(panelMain, ID_comboBoxMeasurementTimeMinute, wxEmptyString, wxDefaultPosition, wxSize(60,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxMeasurementTimeMinute"));
     sizerMeasurementTime->Add(comboBoxMeasurementTimeMinute, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     sizerTemperature1->Add(sizerMeasurementTime, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesMeasuredTime = new wxStaticText(panelMain, ID_changesMeasuredTime, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesMeasuredTime"));
     changesMeasuredTime->SetForegroundColour(wxColour(255,0,0));
     sizerTemperature1->Add(changesMeasuredTime, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     staticMeasurementPlace = new wxStaticText(panelMain, ID_staticMeasurementPlace, _("measurement place"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticMeasurementPlace"));
     sizerTemperature1->Add(staticMeasurementPlace, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     comboBoxMeasurementPlace = new wxComboBox(panelMain, ID_comboBoxMeasurementPlace, wxEmptyString, wxDefaultPosition, wxSize(120,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxMeasurementPlace"));
     sizerTemperature1->Add(comboBoxMeasurementPlace, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesMeasuredPlace = new wxStaticText(panelMain, ID_changesMeasuredPlace, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesMeasuredPlace"));
     changesMeasuredPlace->SetForegroundColour(wxColour(255,0,0));
     sizerTemperature1->Add(changesMeasuredPlace, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerTemperature->Add(sizerTemperature1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     sizerTemperature2 = new wxBoxSizer(wxHORIZONTAL);
     checkBoxTemperatureDisturbances = new wxCheckBox(panelMain, ID_checkBoxTemperatureDisturbances, _("temperature measurement disturbances"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxTemperatureDisturbances"));
     checkBoxTemperatureDisturbances->SetValue(false);
     checkBoxTemperatureDisturbances->SetToolTip(_("Disturbed temperature measurement is ignored on the temperature graph and during calculating peak values"));
     sizerTemperature2->Add(checkBoxTemperatureDisturbances, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesTemperatureDisturbances = new wxStaticText(panelMain, ID_changesTemperatureDisturbances, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesTemperatureDisturbances"));
     changesTemperatureDisturbances->SetForegroundColour(wxColour(255,0,0));
     sizerTemperature2->Add(changesTemperatureDisturbances, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerTemperature->Add(sizerTemperature2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     sizerTemperature3 = new wxFlexGridSizer(0, 3, 0, 0);
     sizerTemperature3->AddGrowableCol(0);
     staticAdditionalTemperatureCorrection = new wxStaticText(panelMain, ID_staticAdditionalTemperatureCorrection, _("additional correction"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticAdditionalTemperatureCorrection"));
     sizerTemperature3->Add(staticAdditionalTemperatureCorrection, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     comboBoxAdditionalTemperatureCorrection = new wxComboBox(panelMain, ID_comboBoxAdditionalTemperatureCorrection, wxEmptyString, wxDefaultPosition, wxSize(100,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxAdditionalTemperatureCorrection"));
     sizerTemperature3->Add(comboBoxAdditionalTemperatureCorrection, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesAdditionalTemperatureCorrection = new wxStaticText(panelMain, ID_changesAdditionalTemperatureCorrection, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesAdditionalTemperatureCorrection"));
     changesAdditionalTemperatureCorrection->SetForegroundColour(wxColour(255,0,0));
     sizerTemperature3->Add(changesAdditionalTemperatureCorrection, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     staticTemperatureAfterCorections = new wxStaticText(panelMain, ID_staticTemperatureAfterCorections, _("temperature after corrections"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticTemperatureAfterCorections"));
     sizerTemperature3->Add(staticTemperatureAfterCorections, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     textTemperatureAfterCorections = new wxStaticText(panelMain, ID_textTemperatureAfterCorections, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_textTemperatureAfterCorections"));
     wxFont textTemperatureAfterCorectionsFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
     if ( !textTemperatureAfterCorectionsFont.Ok() ) textTemperatureAfterCorectionsFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
     textTemperatureAfterCorectionsFont.SetPointSize((int)(textTemperatureAfterCorectionsFont.GetPointSize() * 1.000000));
     textTemperatureAfterCorectionsFont.SetWeight(wxBOLD);
     textTemperatureAfterCorections->SetFont(textTemperatureAfterCorectionsFont);
     sizerTemperature3->Add(textTemperatureAfterCorections, 0, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     space3 = new wxStaticText(panelMain, ID_space3, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_space3"));
     space3->SetForegroundColour(wxColour(255,0,0));
     sizerTemperature3->Add(space3, 0, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerTemperature->Add(sizerTemperature3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     sizerDataRight->Add(sizerTemperature, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerCervix = new wxStaticBoxSizer(wxVERTICAL, panelMain, _("cervix observation"));
     sizerCervix1 = new wxFlexGridSizer(0, 3, 0, 0);
     sizerCervix1->AddGrowableCol(0);
     staticCervixPosition = new wxStaticText(panelMain, ID_staticCervixPosition, _("position"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticCervixPosition"));
     staticCervixPosition->SetToolTip(_("If you set the position of the cervix, please set also dilation"));
     sizerCervix1->Add(staticCervixPosition, 1, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     comboBoxCervixPosition = new wxComboBox(panelMain, ID_comboBoxCervixPosition, wxEmptyString, wxDefaultPosition, wxSize(120,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxCervixPosition"));
     comboBoxCervixPosition->SetToolTip(_("If you set the position of the cervix, please set also dilation"));
     sizerCervix1->Add(comboBoxCervixPosition, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesCervixPosition = new wxStaticText(panelMain, ID_changesCervixPosition, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesCervixPosition"));
     changesCervixPosition->SetForegroundColour(wxColour(255,0,0));
     sizerCervix1->Add(changesCervixPosition, 0, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     staticCervixDilation = new wxStaticText(panelMain, ID_staticCervixDilation, _("dilation"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticCervixDilation"));
     staticCervixDilation->SetToolTip(_("If you set the dilation of the cervix, please set also position"));
     sizerCervix1->Add(staticCervixDilation, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     comboBoxCervixDilation = new wxComboBox(panelMain, ID_comboBoxCervixDilation, wxEmptyString, wxDefaultPosition, wxSize(120,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxCervixDilation"));
     comboBoxCervixDilation->SetToolTip(_("If you set the dilation of the cervix, please set also position"));
     sizerCervix1->Add(comboBoxCervixDilation, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesCervixDilation = new wxStaticText(panelMain, ID_changesCervixDilation, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesCervixDilation"));
     changesCervixDilation->SetForegroundColour(wxColour(255,0,0));
     sizerCervix1->Add(changesCervixDilation, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     staticCervixHardness = new wxStaticText(panelMain, ID_staticCervixHardness, _("hardness"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticCervixHardness"));
     sizerCervix1->Add(staticCervixHardness, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     comboBoxCervixHardness = new wxComboBox(panelMain, ID_comboBoxCervixHardness, wxEmptyString, wxDefaultPosition, wxSize(120,-1), 0, 0, wxCB_READONLY, wxDefaultValidator, _T("ID_comboBoxCervixHardness"));
     sizerCervix1->Add(comboBoxCervixHardness, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesCervixHardness = new wxStaticText(panelMain, ID_changesCervixHardness, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesCervixHardness"));
     changesCervixHardness->SetForegroundColour(wxColour(255,0,0));
     sizerCervix1->Add(changesCervixHardness, 0, wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerCervix->Add(sizerCervix1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     sizerDataRight->Add(sizerCervix, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerOther = new wxStaticBoxSizer(wxVERTICAL, panelMain, wxEmptyString);
     sizerOther1 = new wxFlexGridSizer(0, 4, 0, 0);
     sizerOther1->AddGrowableCol(0);
     staticOvulationPain = new wxStaticText(panelMain, ID_staticOvulationPain, _("ovulation pain"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticOvulationPain"));
     sizerOther1->Add(staticOvulationPain, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxOvulationPain1 = new wxCheckBox(panelMain, ID_checkBoxOvulationPain1, _("v"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxOvulationPain1"));
     checkBoxOvulationPain1->SetValue(false);
     sizerOther1->Add(checkBoxOvulationPain1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxOvulationPain2 = new wxCheckBox(panelMain, ID_checkBoxOvulationPain2, _("vv"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxOvulationPain2"));
     checkBoxOvulationPain2->SetValue(false);
     sizerOther1->Add(checkBoxOvulationPain2, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesOvulationPain = new wxStaticText(panelMain, ID_changesOvulationPain, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesOvulationPain"));
     changesOvulationPain->SetForegroundColour(wxColour(255,0,0));
     sizerOther1->Add(changesOvulationPain, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     staticBreastsTension = new wxStaticText(panelMain, ID_staticBreastsTension, _("breasts tension"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticBreastsTension"));
     sizerOther1->Add(staticBreastsTension, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxBreastsTension1 = new wxCheckBox(panelMain, ID_checkBoxBreastsTension1, _("v"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxBreastsTension1"));
     checkBoxBreastsTension1->SetValue(false);
     sizerOther1->Add(checkBoxBreastsTension1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxBreastsTension2 = new wxCheckBox(panelMain, ID_checkBoxBreastsTension2, _("vv"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxBreastsTension2"));
     checkBoxBreastsTension2->SetValue(false);
     sizerOther1->Add(checkBoxBreastsTension2, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesBreastsTension = new wxStaticText(panelMain, ID_changesBreastsTension, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesBreastsTension"));
     changesBreastsTension->SetForegroundColour(wxColour(255,0,0));
     sizerOther1->Add(changesBreastsTension, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     staticSpotting = new wxStaticText(panelMain, ID_staticSpotting, _("spotting"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticSpotting"));
     sizerOther1->Add(staticSpotting, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxSpotting1 = new wxCheckBox(panelMain, ID_checkBoxSpotting1, _("v"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxSpotting1"));
     checkBoxSpotting1->SetValue(false);
     sizerOther1->Add(checkBoxSpotting1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     checkBoxSpotting2 = new wxCheckBox(panelMain, ID_checkBoxSpotting2, _("vv"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxSpotting2"));
     checkBoxSpotting2->SetValue(false);
     sizerOther1->Add(checkBoxSpotting2, 0, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     changesSpotting = new wxStaticText(panelMain, ID_changesSpotting, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesSpotting"));
     changesSpotting->SetForegroundColour(wxColour(255,0,0));
     sizerOther1->Add(changesSpotting, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerOther->Add(sizerOther1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     sizerAdditionalNotes = new wxBoxSizer(wxHORIZONTAL);
     staticAdditionalNotes = new wxStaticText(panelMain, ID_staticAdditionalNotes, _("additional notes"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticAdditionalNotes"));
     sizerAdditionalNotes->Add(staticAdditionalNotes, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
     changesAdditionalNotes = new wxStaticText(panelMain, ID_changesAdditionalNotes, wxEmptyString, wxDefaultPosition, wxSize(15,-1), wxALIGN_CENTRE, _T("ID_changesAdditionalNotes"));
     changesAdditionalNotes->SetForegroundColour(wxColour(255,0,0));
     sizerAdditionalNotes->Add(changesAdditionalNotes, 0, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerOther->Add(sizerAdditionalNotes, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     textAdditionalNotes = new wxTextCtrl(panelMain, ID_textAdditionalNotes, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxSIMPLE_BORDER, wxDefaultValidator, _T("ID_textAdditionalNotes"));
     textAdditionalNotes->SetMinSize(wxSize(200,40));
     textAdditionalNotes->SetMaxSize(wxSize(400,60));
     sizerOther->Add(textAdditionalNotes, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerDataRight->Add(sizerOther, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
     sizerData->Add(sizerDataRight, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
     sizerMain2->Add(sizerData, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
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
     sizerMain1->SetSizeHints(this);
     
     Connect(ID_buttonPreviousDay,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dayFrame::buttonPreviousDayClick);
     Connect(ID_buttonNextDay,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dayFrame::buttonNextDayClick);
     Connect(ID_buttonAddNewDay,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dayFrame::buttonAddNewDayClick);
     Connect(ID_checkBoxMenstruation1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxMenstruation1Click);
     Connect(ID_checkBoxMenstruation2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxMenstruation2Click);
     Connect(ID_buttonCoitusRecordMinus,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dayFrame::buttonCoitusRecordMinusClick);
     Connect(ID_buttonCoitusRecordPlus,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dayFrame::buttonCoitusRecordPlusClick);
     Connect(ID_checkBoxOtherDisturbances,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxOtherDisturbancesClick);
     Connect(ID_comboBoxMucusFeeling,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dayFrame::comboBoxMucusFeelingUpdated);
     Connect(ID_checkBoxMucusAppearanceOpaque,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxMucusAppearanceClick);
     Connect(ID_checkBoxMucusAppearanceWhite,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxMucusAppearanceClick);
     Connect(ID_checkBoxMucusAppearanceYellowish,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxMucusAppearanceClick);
     Connect(ID_checkBoxMucusAppearanceTacky,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxMucusAppearanceClick);
     Connect(ID_checkBoxMucusAppearanceClear,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxMucusAppearanceClick);
     Connect(ID_checkBoxMucusAppearanceStretchy,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxMucusAppearanceClick);
     Connect(ID_checkBoxMucusAppearanceSeminalResidue,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxMucusAppearanceClick);
     Connect(ID_checkBoxMucusAmount1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxMucusAmount1Click);
     Connect(ID_checkBoxMucusAmount2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxMucusAmount2Click);
     Connect(ID_checkBoxMucusAmount3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxMucusAmount3Click);
     Connect(ID_checkBoxLengthOfStretch1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxLengthOfStretch1Click);
     Connect(ID_checkBoxLengthOfStretch2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxLengthOfStretch2Click);
     Connect(ID_checkBoxLengthOfStretch3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxLengthOfStretch3Click);
     Connect(ID_comboBoxMeasuredTemperature,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dayFrame::comboBoxMeasuredTemperatureUpdated);
     Connect(ID_comboBoxMeasurementTimeHour,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dayFrame::comboBoxMeasurementTimeUpdated);
     Connect(ID_comboBoxMeasurementTimeMinute,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dayFrame::comboBoxMeasurementTimeUpdated);
     Connect(ID_comboBoxMeasurementPlace,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dayFrame::comboBoxMeasurementPlaceUpdated);
     Connect(ID_checkBoxTemperatureDisturbances,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxTemperatureDisturbancesClick);
     Connect(ID_comboBoxAdditionalTemperatureCorrection,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dayFrame::comboBoxAdditionalTemperatureCorrectionUpdated);
     Connect(ID_comboBoxCervixPosition,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dayFrame::comboBoxCervixPositionUpdated);
     Connect(ID_comboBoxCervixDilation,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dayFrame::comboBoxCervixDilationUpdated);
     Connect(ID_comboBoxCervixHardness,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dayFrame::comboBoxCervixHardnessUpdated);
     Connect(ID_checkBoxOvulationPain1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxOvulationPain1Click);
     Connect(ID_checkBoxOvulationPain2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxOvulationPain2Click);
     Connect(ID_checkBoxBreastsTension1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxBreastsTension1Click);
     Connect(ID_checkBoxBreastsTension2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxBreastsTension2Click);
     Connect(ID_checkBoxSpotting1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxSpotting1Click);
     Connect(ID_checkBoxSpotting2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&dayFrame::checkBoxSpotting2Click);
     Connect(ID_textAdditionalNotes,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&dayFrame::textAdditionalNotesUpdated);
     Connect(ID_buttonSave,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dayFrame::buttonSaveClick);
     Connect(ID_buttonCancel,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dayFrame::buttonCancelClick);
     Connect(ID_buttonClose,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&dayFrame::buttonCloseClick);
     Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&dayFrame::dayFrameClose);
     //*)

     /****************************************************/
     /** comboBoxes' data */
     comboBoxMucusFeeling->SetSelection( comboBoxMucusFeeling->Append(m_none) );
     comboBoxMucusFeeling->Append(string_mucusDry_long);
     comboBoxMucusFeeling->Append(string_mucusMoist_long);
     comboBoxMucusFeeling->Append(string_mucusWet_long);
     comboBoxMucusFeeling->Append(string_mucusSlippery_long);
     comboBoxMeasurementTimeHour->Append(_T("0"));
     comboBoxMeasurementTimeHour->Append(_T("1"));
     comboBoxMeasurementTimeHour->Append(_T("2"));
     comboBoxMeasurementTimeHour->Append(_T("3"));
     comboBoxMeasurementTimeHour->Append(_T("4"));
     comboBoxMeasurementTimeHour->Append(_T("5"));
     comboBoxMeasurementTimeHour->Append(_T("6"));
     comboBoxMeasurementTimeHour->SetSelection( comboBoxMeasurementTimeHour->Append(_T("7")) );
     comboBoxMeasurementTimeHour->Append(_T("8"));
     comboBoxMeasurementTimeHour->Append(_T("9"));
     comboBoxMeasurementTimeHour->Append(_T("10"));
     comboBoxMeasurementTimeHour->Append(_T("11"));
     comboBoxMeasurementTimeHour->Append(_T("12"));
     comboBoxMeasurementTimeHour->Append(_T("13"));
     comboBoxMeasurementTimeHour->Append(_T("14"));
     comboBoxMeasurementTimeHour->Append(_T("15"));
     comboBoxMeasurementTimeHour->Append(_T("16"));
     comboBoxMeasurementTimeHour->Append(_T("17"));
     comboBoxMeasurementTimeHour->Append(_T("18"));
     comboBoxMeasurementTimeHour->Append(_T("19"));
     comboBoxMeasurementTimeHour->Append(_T("20"));
     comboBoxMeasurementTimeHour->Append(_T("21"));
     comboBoxMeasurementTimeHour->Append(_T("22"));
     comboBoxMeasurementTimeHour->Append(_T("23"));
     comboBoxMeasurementTimeMinute->SetSelection( comboBoxMeasurementTimeMinute->Append(_T("00")) );
     comboBoxMeasurementTimeMinute->Append(_T("05"));
     comboBoxMeasurementTimeMinute->Append(_T("10"));
     comboBoxMeasurementTimeMinute->Append(_T("15"));
     comboBoxMeasurementTimeMinute->Append(_T("20"));
     comboBoxMeasurementTimeMinute->Append(_T("25"));
     comboBoxMeasurementTimeMinute->Append(_T("30"));
     comboBoxMeasurementTimeMinute->Append(_T("35"));
     comboBoxMeasurementTimeMinute->Append(_T("40"));
     comboBoxMeasurementTimeMinute->Append(_T("45"));
     comboBoxMeasurementTimeMinute->Append(_T("50"));
     comboBoxMeasurementTimeMinute->Append(_T("55"));
     comboBoxMeasurementPlace->Append(string_placeMouth);
     comboBoxMeasurementPlace->SetSelection( comboBoxMeasurementPlace->Append(string_placeVagina) );
     comboBoxMeasurementPlace->Append(string_placeRectum);
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,7"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,65"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,6"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,55"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,5"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,45"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,4"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,35"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,3"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,25"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,2"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,15"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,1"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("-0,05"));
     comboBoxAdditionalTemperatureCorrection->SetSelection( comboBoxAdditionalTemperatureCorrection->Append(_T("0")) );
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,05"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,1"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,15"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,2"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,25"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,3"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,35"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,4"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,45"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,5"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,55"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,6"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,65"));
     comboBoxAdditionalTemperatureCorrection->Append(_T("+0,7"));
     comboBoxCervixPosition->SetSelection( comboBoxCervixPosition->Append(m_none) );
     comboBoxCervixPosition->Append( string_cervixHigh_long );
     comboBoxCervixPosition->Append( string_cervixAboveMiddle_long );
     comboBoxCervixPosition->Append( string_cervixInMiddle_long );
     comboBoxCervixPosition->Append( string_cervixBelowMiddle_long );
     comboBoxCervixPosition->Append( string_cervixLow_long );
     comboBoxCervixDilation->SetSelection( comboBoxCervixDilation->Append(m_none) );
     comboBoxCervixDilation->Append( string_cervixOpen_long );
     comboBoxCervixDilation->Append( string_cervixHalfOpen_long );
     comboBoxCervixDilation->Append( string_cervixClosed_long );
     comboBoxCervixHardness->SetSelection( comboBoxCervixHardness->Append(m_none) );
     comboBoxCervixHardness->Append( string_cervixSoft_long );
     comboBoxCervixHardness->Append( string_cervixRatherFirm_long );
     comboBoxCervixHardness->Append( string_cervixFirm_long );

     updateMeasuredTemperatureList();

     /****************************************************/
     setButtonsStyle();
     SetSize( m_config->formDayLeft, m_config->formDayTop, -1, -1 );
     //GetSizer()->Fit( this );
     //GetSizer()->SetSizeHints( this );

     wxIcon wx_nfp_ICON( wx_nfp_xpm );
     SetIcon( wx_nfp_ICON );

     SetAffirmativeId( ID_buttonSave );
     SetEscapeId( ID_buttonClose );
     buttonSave->SetDefault();
}

/**
 *
 */
dayFrame::~dayFrame()
{
     //(*Destroy(dayFrame)
     //*)
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * dayFrameClose
 */
void dayFrame::dayFrameClose( wxCloseEvent& event )
{
     if (m_config->useCoitusRecordCounter) {
          wxString input = textCoitusRecord->GetValue();
          input = input.Trim( true );
          input = input.Trim( false );
          if ( input.Length() > 0 )
               m_cycleData->increaseCoitusRecordCounter( -1 * input.Length() );
     }

     if ( m_cycleData->getCard()->getCardLocked() || checkIfDataHasBeenChanged( true ) ) {
          Hide();
          m_parent->SetFocus();
     }
}

/**
 * buttonSaveClick
 */
void dayFrame::buttonSaveClick( wxCommandEvent& event )
{
     save();
     update();
     updateButtonsState();
}

/**
 * buttonCancelClick
 */
void dayFrame::buttonCancelClick( wxCommandEvent& event )
{
     update();
     updateButtonsState();
}

/**
 * buttonCloseClick
 */
void dayFrame::buttonCloseClick( wxCommandEvent& event )
{
     if (m_config->useCoitusRecordCounter) {
          wxString input = textCoitusRecord->GetValue();
          input = input.Trim( true );
          input = input.Trim( false );
          if ( input.Length() > 0 )
               m_cycleData->increaseCoitusRecordCounter( -1 * input.Length() );
     }

     if ( m_cycleData->getCard()->getCardLocked() || checkIfDataHasBeenChanged( true ) ) {
          Hide();
          m_parent->SetFocus();
     }
}

/**
 * buttonPreviousDayClick
 */
void dayFrame::buttonPreviousDayClick( wxCommandEvent& event )
{
     if ( m_cycleData->getCard()->getCardLocked() || checkIfDataHasBeenChanged( true ) ) {
          if ( m_cycleData->getActiveDay() > 1 ) {
               m_cycleData->setActiveDay( m_cycleData->getActiveDay() - 1 );
          }
          update();
          m_config->checkCurrentDayVisibility = true;

          sendDataUpdateEvent( ACTIVE_DAY_CHANGED, _T( "'prev day' click - refresh previously and currently active days only" ) );
     }
}

/**
 * buttonNextDayClick
 */
void dayFrame::buttonNextDayClick( wxCommandEvent& event )
{
     if ( m_cycleData->getCard()->getCardLocked() || checkIfDataHasBeenChanged( true ) ) {
          if ( m_cycleData->getActiveDay() < m_cycleData->getDaysCount() ) {
               m_cycleData->setActiveDay( m_cycleData->getActiveDay() + 1 );
          }
          update();
          m_config->checkCurrentDayVisibility = true;

          sendDataUpdateEvent( ACTIVE_DAY_CHANGED, _T( "'next day' click - refresh previously and currently active days only" ) );
     }
}

/**
 * buttonAddNewDayClick
 */
void dayFrame::buttonAddNewDayClick( wxCommandEvent& event )
{
     if ( m_cycleData->getCard()->getCardLocked() || checkIfDataHasBeenChanged( true ) ) {
          if ( m_cycleData->addNewDay() > -1 ) {
               m_cycleData->setActiveDay( m_cycleData->getDaysCount() );
               m_cycleData->setCardModified( true );
               m_config->checkCurrentDayVisibility = true;

               sendDataUpdateEvent( ACTIVE_DAY_CHANGED, _T( "'add new day' click - refresh previously and currently active days only" ) );
               update();
          } else {
               wxMessageBox( _( "Error occured while adding new day" ), _( "Error" ), wxOK | wxICON_ERROR );
          }
     }
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * checkBoxMenstruation1Click
 */
void dayFrame::checkBoxMenstruation1Click( wxCommandEvent& event )
{
     int val = -1;
     if ( checkBoxMenstruation1->GetValue() ) {
          checkBoxMenstruation2->SetValue( false );
          val = 1;
     }
     if ( m_cycleData->getDay()->getMenstruation() == val ) {
          if ( changesMenstruation->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesMenstruation->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesMenstruation->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesMenstruation->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * checkBoxMenstruation2Click
 */
void dayFrame::checkBoxMenstruation2Click( wxCommandEvent& event )
{
     int val = -1;
     if ( checkBoxMenstruation2->GetValue() ) {
          checkBoxMenstruation1->SetValue( false );
          val = 2;
     }
     if ( m_cycleData->getDay()->getMenstruation() == val ) {
          if ( changesMenstruation->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesMenstruation->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesMenstruation->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesMenstruation->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}


/**
 * buttonCoitusRecordMinusClick
 */
void dayFrame::buttonCoitusRecordMinusClick( wxCommandEvent& event )
{
     wxString input = textCoitusRecord->GetValue();
     input = input.Trim( true );
     input = input.Trim( false );

     if ( input.Length() > 0 ) {
          wxString output = _T( " " );
          for ( int i = 0; i < ( int )input.Length() - 1; i++ ) {
               output += m_config->coitusRecordCharacter;
          }
          m_cycleData->increaseCoitusRecordCounter( -1 );
          textCoitusRecord->SetValue( output );
          if (m_config->useCoitusRecordCounter)
               textCoitusRecordCounter->SetLabel( m_util.intToStr( m_cycleData->getCoitusRecordCounter() ) );

          if ( m_cycleData->getDay()->getCoitusRecord() == ( int )input.Length() - 1 ) {
               if ( changesCoitusRecord->GetLabel().IsSameAs( _T( "*" ) ) ) {
                    m_changes--;
                    changesCoitusRecord->SetLabel( wxEmptyString );
               }
          } else if ( m_cycleData->getDay()->getCoitusRecord() < 1 && input.Length() - 1 == 0 ) {
               if ( changesCoitusRecord->GetLabel().IsSameAs( _T( "*" ) ) ) {
                    m_changes--;
                    changesCoitusRecord->SetLabel( wxEmptyString );
               }
          } else {
               if ( !changesCoitusRecord->GetLabel().IsSameAs( _T( "*" ) ) ) {
                    m_changes++;
                    changesCoitusRecord->SetLabel( _T( "*" ) );
               }
          }
          updateButtonsState();
     }
}

/**
 * buttonCoitusRecordPlusClick
 */
void dayFrame::buttonCoitusRecordPlusClick( wxCommandEvent& event )
{
     wxString input = textCoitusRecord->GetValue();
     input = input.Trim( true );
     input = input.Trim( false );

     wxString output = _T( " " );
     for ( int i = 0; i < ( int )input.Length() + 1; i++ ) {
          output += m_config->coitusRecordCharacter;
     }
     m_cycleData->increaseCoitusRecordCounter( 1 );
     textCoitusRecord->SetValue( output );
     if (m_config->useCoitusRecordCounter)
          textCoitusRecordCounter->SetLabel( m_util.intToStr( m_cycleData->getCoitusRecordCounter() ) );

     if ( m_cycleData->getDay()->getCoitusRecord() == ( int )input.Length() + 1 ) {
          if ( changesCoitusRecord->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesCoitusRecord->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesCoitusRecord->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesCoitusRecord->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * checkBoxOtherDisturbancesClick
 */
void dayFrame::checkBoxOtherDisturbancesClick( wxCommandEvent& event )
{
     if ( m_cycleData->getDay()->getOtherDisturbances() == checkBoxOtherDisturbances->GetValue() ) {
          if ( changesOtherDisturbances->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesOtherDisturbances->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesOtherDisturbances->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesOtherDisturbances->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * comboBoxMucusFeelingUpdated
 */
void dayFrame::comboBoxMucusFeelingUpdated( wxCommandEvent& event )
{
     int val = -1;
     if ( comboBoxMucusFeeling->GetValue().IsSameAs( string_mucusDry_long ) ) {
          val = MUCUS_DRY;
     } else if ( comboBoxMucusFeeling->GetValue().IsSameAs( string_mucusMoist_long ) ) {
          val = MUCUS_MOIST;
     } else if ( comboBoxMucusFeeling->GetValue().IsSameAs( string_mucusWet_long ) ) {
          val = MUCUS_WET;
     } else if ( comboBoxMucusFeeling->GetValue().IsSameAs( string_mucusSlippery_long ) ) {
          val = MUCUS_SLIPPERY;
     }
     if ( m_cycleData->getDay()->getMucusFeelingExperience() == val ) {
          if ( changesMucusFeeling->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesMucusFeeling->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesMucusFeeling->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesMucusFeeling->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * checkBoxMucusAppearanceClick
 */
void dayFrame::checkBoxMucusAppearanceClick( wxCommandEvent& event )
{
     int val = calculateMucusAppearance();
     textMucusAppearance->SetValue( _T( " " ) + m_cycleData->getDay()->convertMucusAppearance( val ) );

     if ( m_cycleData->getDay()->getMucusAppearance() == val ) {
          if ( changesMucusAppearance->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesMucusAppearance->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesMucusAppearance->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesMucusAppearance->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * checkBoxLengthOfStretch1Click
 */
void dayFrame::checkBoxLengthOfStretch1Click( wxCommandEvent& event )
{
     if ( checkBoxLengthOfStretch1->GetValue() ) {
          checkBoxLengthOfStretch2->SetValue( false );
          checkBoxLengthOfStretch3->SetValue( false );
     }
     checkBoxMucusAppearanceClick( event );
}

/**
 * checkBoxLengthOfStretch2Click
 */
void dayFrame::checkBoxLengthOfStretch2Click( wxCommandEvent& event )
{
     if ( checkBoxLengthOfStretch2->GetValue() ) {
          checkBoxLengthOfStretch1->SetValue( false );
          checkBoxLengthOfStretch3->SetValue( false );
     }
     checkBoxMucusAppearanceClick( event );
}

/**
 * checkBoxLengthOfStretch3Click
 */
void dayFrame::checkBoxLengthOfStretch3Click( wxCommandEvent& event )
{
     if ( checkBoxLengthOfStretch3->GetValue() ) {
          checkBoxLengthOfStretch1->SetValue( false );
          checkBoxLengthOfStretch2->SetValue( false );
     }
     checkBoxMucusAppearanceClick( event );
}

/**
 * checkBoxMucusAmount1Click
 */
void dayFrame::checkBoxMucusAmount1Click( wxCommandEvent& event )
{
     if ( checkBoxMucusAmount1->GetValue() ) {
          checkBoxMucusAmount2->SetValue( false );
          checkBoxMucusAmount3->SetValue( false );
     }
     checkBoxMucusAppearanceClick( event );
}

/**
 * checkBoxMucusAmount2Click
 */
void dayFrame::checkBoxMucusAmount2Click( wxCommandEvent& event )
{
     if ( checkBoxMucusAmount2->GetValue() ) {
          checkBoxMucusAmount1->SetValue( false );
          checkBoxMucusAmount3->SetValue( false );
     }
     checkBoxMucusAppearanceClick( event );
}

/**
 * checkBoxMucusAmount3Click
 */
void dayFrame::checkBoxMucusAmount3Click( wxCommandEvent& event )
{
     if ( checkBoxMucusAmount3->GetValue() ) {
          checkBoxMucusAmount1->SetValue( false );
          checkBoxMucusAmount2->SetValue( false );
     }
     checkBoxMucusAppearanceClick( event );
}

/**
 * comboBoxMeasuredTemperatureUpdated
 */
void dayFrame::comboBoxMeasuredTemperatureUpdated( wxCommandEvent& event )
{
     int val = -1;
     if ( ! comboBoxMeasuredTemperature->GetValue().IsSameAs( m_none ) )
          val = m_util.strToTemperature( comboBoxMeasuredTemperature->GetValue() );

     if ( m_cycleData->getDay()->getTemperatureMeasuredValue() == val ) {
          if ( changesMeasuredTemperature->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesMeasuredTemperature->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesMeasuredTemperature->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesMeasuredTemperature->SetLabel( _T( "*" ) );
          }
     }
     updateTemperatureAfterCorectionsValue();
     updateButtonsState();
}

/**
 * comboBoxMeasurementTimeUpdated
 */
void dayFrame::comboBoxMeasurementTimeUpdated( wxCommandEvent& event )
{
     wxString tH = m_cycleData->getDay()->getTemperatureMeasurementTime().Format( _T( "%H" ) );
     wxString tM = m_cycleData->getDay()->getTemperatureMeasurementTime().Format( _T( "%M" ) );
     if ( m_cycleData->getDay()->getTemperatureMeasurementTime().GetHour() == 0 && m_cycleData->getDay()->getTemperatureMeasurementTime().GetMinute() == 0 ) {
          tH = m_cycleData->getCard()->getTemperatureUsualMeasurementTime().Format( _T( "%H" ) );
          tM = m_cycleData->getCard()->getTemperatureUsualMeasurementTime().Format( _T( "%M" ) );
     }
     if ( tH.StartsWith( _T( "0" ) ) )
          tH = tH.Mid( 1 );

     if ( comboBoxMeasurementTimeHour->GetValue().IsSameAs( tH ) && comboBoxMeasurementTimeMinute->GetValue().IsSameAs( tM ) ) {
          if ( changesMeasuredTime->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesMeasuredTime->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesMeasuredTime->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesMeasuredTime->SetLabel( _T( "*" ) );
          }
     }
     updateTemperatureAfterCorectionsValue();
     updateButtonsState();
}

/**
 * comboBoxMeasurementPlaceUpdated
 */
void dayFrame::comboBoxMeasurementPlaceUpdated( wxCommandEvent& event )
{
     wxString mp = string_placeVagina;
     if ( m_cycleData->getDay()->getTemperatureMeasurementPlace() == PLACE_MOUTH ) {
          mp = string_placeMouth;
     } else if ( m_cycleData->getDay()->getTemperatureMeasurementPlace() == PLACE_VAGINA ) {
          mp = string_placeVagina;
     } else if ( m_cycleData->getDay()->getTemperatureMeasurementPlace() == PLACE_RECTUM ) {
          mp = string_placeRectum;
     } else if ( m_cycleData->getCard()->getTemperatureUsualMeasurementPlace() == PLACE_MOUTH ) {
          mp = string_placeMouth;
     } else if ( m_cycleData->getCard()->getTemperatureUsualMeasurementPlace() == PLACE_RECTUM ) {
          mp = string_placeRectum;
     }

     if ( comboBoxMeasurementPlace->GetValue().IsSameAs( mp ) ) {
          if ( changesMeasuredPlace->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesMeasuredPlace->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesMeasuredPlace->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesMeasuredPlace->SetLabel( _T( "*" ) );
          }
     }
     updateTemperatureAfterCorectionsValue();
     updateButtonsState();
}

/**
 * checkBoxTemperatureDisturbancesClick
 */
void dayFrame::checkBoxTemperatureDisturbancesClick( wxCommandEvent& event )
{
     if ( m_cycleData->getDay()->getTemperatureDisturbances() == checkBoxTemperatureDisturbances->GetValue() ) {
          if ( changesTemperatureDisturbances->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesTemperatureDisturbances->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesTemperatureDisturbances->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesTemperatureDisturbances->SetLabel( _T( "*" ) );
          }
     }
     updateTemperatureAfterCorectionsValue();
     updateButtonsState();
}

/**
 * comboBoxAdditionalTemperatureCorrectionUpdated
 */
void dayFrame::comboBoxAdditionalTemperatureCorrectionUpdated( wxCommandEvent& event )
{
     int val = m_util.strToTemperature( comboBoxAdditionalTemperatureCorrection->GetValue() );
     if ( m_cycleData->getDay()->getTemperatureAdditionalCorrection() == val ) {
          if ( changesAdditionalTemperatureCorrection->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesAdditionalTemperatureCorrection->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesAdditionalTemperatureCorrection->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesAdditionalTemperatureCorrection->SetLabel( _T( "*" ) );
          }
     }
     updateTemperatureAfterCorectionsValue();
     updateButtonsState();
}

/**
 * comboBoxCervixPositionUpdated
 */
void dayFrame::comboBoxCervixPositionUpdated( wxCommandEvent& event )
{
     int val = -1;
     // cervix - position
     if ( comboBoxCervixPosition->GetValue().IsSameAs( string_cervixHigh_long ) ) {
          val = CERVIX_HIGH;
     } else if ( comboBoxCervixPosition->GetValue().IsSameAs( string_cervixAboveMiddle_long ) ) {
          val = CERVIX_ABOVE_MIDDLE;
     } else if ( comboBoxCervixPosition->GetValue().IsSameAs( string_cervixInMiddle_long ) ) {
          val = CERVIX_IN_MIDDLE;
     } else if ( comboBoxCervixPosition->GetValue().IsSameAs( string_cervixBelowMiddle_long ) ) {
          val = CERVIX_BELOW_MEDDLE;
     } else if ( comboBoxCervixPosition->GetValue().IsSameAs( string_cervixLow_long ) ) {
          val = CERVIX_LOW;
     }
     if ( m_cycleData->getDay()->getCervixPosition() == val ) {
          if ( changesCervixPosition->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesCervixPosition->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesCervixPosition->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesCervixPosition->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * comboBoxCervixDilationUpdated
 */
void dayFrame::comboBoxCervixDilationUpdated( wxCommandEvent& event )
{
     int val = -1;
     //cervix - dilation
     if ( comboBoxCervixDilation->GetValue().IsSameAs( string_cervixOpen_long ) ) {
          val = CERVIX_OPEN;
     } else if ( comboBoxCervixDilation->GetValue().IsSameAs( string_cervixHalfOpen_long ) ) {
          val = CERVIX_HALF_OPEN;
     } else if ( comboBoxCervixDilation->GetValue().IsSameAs( string_cervixClosed_long ) ) {
          val = CERVIX_CLOSED;
     }
     if ( m_cycleData->getDay()->getCervixDilation() == val ) {
          if ( changesCervixDilation->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesCervixDilation->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesCervixDilation->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesCervixDilation->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * comboBoxCervixHardnessUpdated
 */
void dayFrame::comboBoxCervixHardnessUpdated( wxCommandEvent& event )
{
     int val = -1;
     // cervix - hardness
     if ( comboBoxCervixHardness->GetValue().IsSameAs( string_cervixSoft_long ) ) {
          val = CERVIX_SOFT;
     } else if ( comboBoxCervixHardness->GetValue().IsSameAs( string_cervixRatherFirm_long ) ) {
          val = CERVIX_RATHER_FIRM;
     } else if ( comboBoxCervixHardness->GetValue().IsSameAs( string_cervixFirm_long ) ) {
          val = CERVIX_FIRM;
     }
     if ( m_cycleData->getDay()->getCervixHardness() == val ) {
          if ( changesCervixHardness->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesCervixHardness->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesCervixHardness->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesCervixHardness->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * checkBoxOvulationPain1Click
 */
void dayFrame::checkBoxOvulationPain1Click( wxCommandEvent& event )
{
     int val = -1;
     if ( checkBoxOvulationPain1->GetValue() ) {
          checkBoxOvulationPain2->SetValue( false );
          val = 1;
     }
     if ( m_cycleData->getDay()->getOvulationPain() == val ) {
          if ( changesOvulationPain->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesOvulationPain->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesOvulationPain->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesOvulationPain->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * checkBoxOvulationPain2Click
 */
void dayFrame::checkBoxOvulationPain2Click( wxCommandEvent& event )
{
     int val = -1;
     if ( checkBoxOvulationPain2->GetValue() ) {
          checkBoxOvulationPain1->SetValue( false );
          val = 2;
     }
     if ( m_cycleData->getDay()->getOvulationPain() == val ) {
          if ( changesOvulationPain->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesOvulationPain->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesOvulationPain->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesOvulationPain->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * checkBoxBreastsTension1Click
 */
void dayFrame::checkBoxBreastsTension1Click( wxCommandEvent& event )
{
     int val = -1;
     if ( checkBoxBreastsTension1->GetValue() ) {
          checkBoxBreastsTension2->SetValue( false );
          val = 1;
     }
     if ( m_cycleData->getDay()->getBreastsTension() == val ) {
          if ( changesBreastsTension->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesBreastsTension->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesBreastsTension->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesBreastsTension->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * checkBoxBreastsTension2Click
 */
void dayFrame::checkBoxBreastsTension2Click( wxCommandEvent& event )
{
     int val = -1;
     if ( checkBoxBreastsTension2->GetValue() ) {
          checkBoxBreastsTension1->SetValue( false );
          val = 2;
     }
     if ( m_cycleData->getDay()->getBreastsTension() == val ) {
          if ( changesBreastsTension->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesBreastsTension->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesBreastsTension->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesBreastsTension->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * checkBoxSpotting1Click
 */
void dayFrame::checkBoxSpotting1Click( wxCommandEvent& event )
{
     int val = -1;
     if ( checkBoxSpotting1->GetValue() ) {
          checkBoxSpotting2->SetValue( false );
          val = 1;
     }
     if ( m_cycleData->getDay()->getSpotting() == val ) {
          if ( changesSpotting->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesSpotting->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesSpotting->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesSpotting->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * checkBoxSpotting2Click
 */
void dayFrame::checkBoxSpotting2Click( wxCommandEvent& event )
{
     int val = -1;
     if ( checkBoxSpotting2->GetValue() ) {
          checkBoxSpotting1->SetValue( false );
          val = 2;
     }
     if ( m_cycleData->getDay()->getSpotting() == val ) {
          if ( changesSpotting->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes--;
               changesSpotting->SetLabel( wxEmptyString );
          }
     } else {
          if ( !changesSpotting->GetLabel().IsSameAs( _T( "*" ) ) ) {
               m_changes++;
               changesSpotting->SetLabel( _T( "*" ) );
          }
     }
     updateButtonsState();
}

/**
 * textAdditionalNotesUpdated
 */
void dayFrame::textAdditionalNotesUpdated( wxCommandEvent& event )
{
     if ( !m_textAdditionalNotesEventProcessing ) {
          m_textAdditionalNotesEventProcessing = true;
          wxString value = textAdditionalNotes->GetValue();

          if ( value.Length() > 0 && value[value.Length()-1] == '\n' ) {
               value = value.SubString( 0, value.Length() - 2 );
               textAdditionalNotes->SetValue( value );
               buttonSaveClick( event );
          } else {
               if ( textAdditionalNotes->GetValue().IsSameAs( m_cycleData->getDay()->getAdditionalNotes() ) ) {
                    if ( changesAdditionalNotes->GetLabel().IsSameAs( _T( "*" ) ) ) {
                         m_changes--;
                         changesAdditionalNotes->SetLabel( wxEmptyString );
                    }
               } else {
                    if ( !changesAdditionalNotes->GetLabel().IsSameAs( _T( "*" ) ) ) {
                         m_changes++;
                         changesAdditionalNotes->SetLabel( _T( "*" ) );
                    }
               }
               updateButtonsState();
          }

          m_textAdditionalNotesEventProcessing = false;
     }
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
void dayFrame::updateMeasuredTemperatureList()
{
     comboBoxMeasuredTemperature->Clear();
     comboBoxMeasuredTemperature->SetSelection( comboBoxMeasuredTemperature->Append(m_none) );
     for ( int i = 0; i < m_config->rowsCountTemp; i++ ) {
          int tt = m_config->temperatureRangeHigh - ( 5 * i );
          wxString temp = m_util.intToStr( tt / 100 ) + _T( "," );
          tt = tt % 100;
          if ( tt == 5 )
               temp += _T( "05" );
          else if ( tt % 10 == 0 )
               temp += m_util.intToStr( tt / 10 );
          else
               temp += m_util.intToStr( tt );

          comboBoxMeasuredTemperature->Append(temp);
     }
}

/**
 *
 */
void dayFrame::setButtonsStyle()
{
     int flatButton = 0;
     if ( m_config->useFlatButtons )
          flatButton = wxNO_BORDER;

     buttonSave->SetWindowStyle( flatButton );
     buttonCancel->SetWindowStyle( flatButton );
     buttonClose->SetWindowStyle( flatButton );
     buttonAddNewDay->SetWindowStyle( flatButton );
     buttonCoitusRecordMinus->SetWindowStyle( flatButton );
     buttonCoitusRecordPlus->SetWindowStyle( flatButton );
     buttonNextDay->SetWindowStyle( flatButton );
     buttonPreviousDay->SetWindowStyle( flatButton );

     buttonSave->Refresh();
     buttonCancel->Refresh();
     buttonClose->Refresh();
     buttonAddNewDay->Refresh();
     buttonCoitusRecordMinus->Refresh();
     buttonCoitusRecordPlus->Refresh();
     buttonNextDay->Refresh();
     buttonPreviousDay->Refresh();
}

/**
 * update data displayed in the frame.
 */
void dayFrame::update()
{
     m_changes = 0;
     changesMenstruation->SetLabel( wxEmptyString );
     changesCoitusRecord->SetLabel( wxEmptyString );
     changesOtherDisturbances->SetLabel( wxEmptyString );
     changesMucusFeeling->SetLabel( wxEmptyString );
     changesMucusAppearance->SetLabel( wxEmptyString );
     changesMeasuredTemperature->SetLabel( wxEmptyString );
     changesMeasuredTime->SetLabel( wxEmptyString );
     changesMeasuredPlace->SetLabel( wxEmptyString );
     changesTemperatureDisturbances->SetLabel( wxEmptyString );
     changesAdditionalTemperatureCorrection->SetLabel( wxEmptyString );
     changesCervixPosition->SetLabel( wxEmptyString );
     changesCervixDilation->SetLabel( wxEmptyString );
     changesCervixHardness->SetLabel( wxEmptyString );
     changesOvulationPain->SetLabel( wxEmptyString );
     changesBreastsTension->SetLabel( wxEmptyString );
     changesSpotting->SetLabel( wxEmptyString );
     changesAdditionalNotes->SetLabel( wxEmptyString );

     if ( m_cycleData->getActiveCard() > 0 && m_cycleData->getActiveDay() > 0 ) {
          // top
          textCardNo->SetLabel( m_util.intToStr( m_cycleData->getActiveCard() ) );
          textCycleDay->SetLabel( m_util.intToStr( m_cycleData->getActiveDay() ) );
          wxDateTime date = m_cycleData->getCard()->getFirstDayOfCycle();
          date.Add( wxDateSpan::Days( m_cycleData->getActiveDay() - 1 ) );
          textDate->SetLabel( date.Format( _T( "%A, %d %B %Y" ) ) );

          if ( m_cycleData->getActiveDay() == 1 ) {
               buttonPreviousDay->Enable( false );
          } else {
               buttonPreviousDay->Enable( true );
          }
          if ( m_cycleData->getActiveDay() == m_cycleData->getDaysCount() ) {
               buttonNextDay->Enable( false );
          } else {
               buttonNextDay->Enable( true );
          }

          if ( m_cycleData->getActiveCard() == m_cycleData->getCardsCount() ) {
               buttonAddNewDay->Enable( true );
          } else {
               buttonAddNewDay->Enable( false );
          }

          cardEntry * card = m_cycleData->getCard();
          dayEntry * day = m_cycleData->getDay();

          // box basic
          if ( day->getMenstruation() == 1 ) {
               checkBoxMenstruation1->SetValue( true );
               checkBoxMenstruation2->SetValue( false );
          } else if ( day->getMenstruation() == 2 ) {
               checkBoxMenstruation1->SetValue( false );
               checkBoxMenstruation2->SetValue( true );
          } else {
               checkBoxMenstruation1->SetValue( false );
               checkBoxMenstruation2->SetValue( false );
          }

          wxString output = _T( " " );
          for ( int i = 0; i < day->getCoitusRecord(); i++ ) {
               output += m_config->coitusRecordCharacter;
          }
          textCoitusRecord->SetFont( m_config->fontResultHeart );
          textCoitusRecord->SetValue( output );
          if (m_config->useCoitusRecordCounter)
               textCoitusRecordCounter->SetLabel( m_util.intToStr( m_cycleData->getCoitusRecordCounter() ) );

          if ( day->getOtherDisturbances() ) {
               checkBoxOtherDisturbances->SetValue( true );
          } else {
               checkBoxOtherDisturbances->SetValue( false );
          }

          // box mucus
          if ( day->getMucusFeelingExperience() == MUCUS_DRY ) {
               comboBoxMucusFeeling->SetValue( string_mucusDry_long );
          } else if ( day->getMucusFeelingExperience() == MUCUS_MOIST ) {
               comboBoxMucusFeeling->SetValue( string_mucusMoist_long );
          } else if ( day->getMucusFeelingExperience() == MUCUS_WET ) {
               comboBoxMucusFeeling->SetValue( string_mucusWet_long );
          } else if ( day->getMucusFeelingExperience() == MUCUS_SLIPPERY ) {
               comboBoxMucusFeeling->SetValue( string_mucusSlippery_long );
          } else {
               comboBoxMucusFeeling->SetValue( m_none );
          }

          textMucusAppearance->SetValue( _T( " " ) + m_cycleData->getDay()->convertMucusAppearance( day->getMucusAppearance() ) );

          int v = day->getMucusAppearance();
          if ( v >= MUCUS_LENGHTOFSTRETCH3 ) {
               v -= MUCUS_LENGHTOFSTRETCH3;
               checkBoxLengthOfStretch3->SetValue( true );
          } else {
               checkBoxLengthOfStretch3->SetValue( false );
          }
          if ( v >= MUCUS_LENGHTOFSTRETCH2 ) {
               v -= MUCUS_LENGHTOFSTRETCH2;
               checkBoxLengthOfStretch2->SetValue( true );
          } else {
               checkBoxLengthOfStretch2->SetValue( false );
          }
          if ( v >= MUCUS_LENGHTOFSTRETCH1 ) {
               v -= MUCUS_LENGHTOFSTRETCH1;
               checkBoxLengthOfStretch1->SetValue( true );
          } else {
               checkBoxLengthOfStretch1->SetValue( false );
          }
          if ( v >= MUCUS_AMOUNT3 ) {
               v -= MUCUS_AMOUNT3;
               checkBoxMucusAmount3->SetValue( true );
          } else {
               checkBoxMucusAmount3->SetValue( false );
          }
          if ( v >= MUCUS_AMOUNT2 ) {
               v -= MUCUS_AMOUNT2;
               checkBoxMucusAmount2->SetValue( true );
          } else {
               checkBoxMucusAmount2->SetValue( false );
          }
          if ( v >= MUCUS_AMOUNT1 ) {
               v -= MUCUS_AMOUNT1;
               checkBoxMucusAmount1->SetValue( true );
          } else {
               checkBoxMucusAmount1->SetValue( false );
          }
          if ( v >= MUCUS_SEMINALRESIDUE ) {
               v -= MUCUS_SEMINALRESIDUE;
               checkBoxMucusAppearanceSeminalResidue->SetValue( true );
          } else {
               checkBoxMucusAppearanceSeminalResidue->SetValue( false );
          }
          if ( v >= MUCUS_STRETCHY ) {
               v -= MUCUS_STRETCHY;
               checkBoxMucusAppearanceStretchy->SetValue( true );
          } else {
               checkBoxMucusAppearanceStretchy->SetValue( false );
          }
          if ( v >= MUCUS_CLEAR ) {
               v -= MUCUS_CLEAR;
               checkBoxMucusAppearanceClear->SetValue( true );
          } else {
               checkBoxMucusAppearanceClear->SetValue( false );
          }
          if ( v >= MUCUS_TACKY ) {
               v -= MUCUS_TACKY;
               checkBoxMucusAppearanceTacky->SetValue( true );
          } else {
               checkBoxMucusAppearanceTacky->SetValue( false );
          }
          if ( v >= MUCUS_YELLOWISH ) {
               v -= MUCUS_YELLOWISH;
               checkBoxMucusAppearanceYellowish->SetValue( true );
          } else {
               checkBoxMucusAppearanceYellowish->SetValue( false );
          }
          if ( v >= MUCUS_WHITE ) {
               v -= MUCUS_WHITE;
               checkBoxMucusAppearanceWhite->SetValue( true );
          } else {
               checkBoxMucusAppearanceWhite->SetValue( false );
          }
          if ( v >= MUCUS_OPAQUE ) {
               v -= MUCUS_OPAQUE;
               checkBoxMucusAppearanceOpaque->SetValue( true );
          } else {
               checkBoxMucusAppearanceOpaque->SetValue( false );
          }

          // box temperature
          if ( day->getTemperatureMeasuredValue() > 0 ) {
               comboBoxMeasuredTemperature->SetValue( m_util.temperatureToStr( day->getTemperatureMeasuredValue(), false ) );
          } else {
               comboBoxMeasuredTemperature->SetValue( m_none );
          }

          wxString tH = day->getTemperatureMeasurementTime().Format( _T( "%H" ) );
          wxString tM = day->getTemperatureMeasurementTime().Format( _T( "%M" ) );
          if ( day->getTemperatureMeasurementTime().GetHour() == 0 && day->getTemperatureMeasurementTime().GetMinute() == 0 ) {
               tH = card->getTemperatureUsualMeasurementTime().Format( _T( "%H" ) );
               tM = card->getTemperatureUsualMeasurementTime().Format( _T( "%M" ) );
          }
          if ( tH.StartsWith( _T( "0" ) ) )
               tH = tH.Mid( 1 );
          comboBoxMeasurementTimeHour->SetValue( tH );
          comboBoxMeasurementTimeMinute->SetValue( tM );

          if ( day->getTemperatureMeasurementPlace() == PLACE_MOUTH ) {
               comboBoxMeasurementPlace->SetValue( string_placeMouth );
          } else if ( day->getTemperatureMeasurementPlace() == PLACE_VAGINA ) {
               comboBoxMeasurementPlace->SetValue( string_placeVagina );
          } else if ( day->getTemperatureMeasurementPlace() == PLACE_RECTUM ) {
               comboBoxMeasurementPlace->SetValue( string_placeRectum );
          } else if ( card->getTemperatureUsualMeasurementPlace() == PLACE_MOUTH ) {
               comboBoxMeasurementPlace->SetValue( string_placeMouth );
          } else if ( card->getTemperatureUsualMeasurementPlace() == PLACE_RECTUM ) {
               comboBoxMeasurementPlace->SetValue( string_placeRectum );
          } else {
               comboBoxMeasurementPlace->SetValue( string_placeVagina );
          }

          if ( day->getTemperatureDisturbances() ) {
               checkBoxTemperatureDisturbances->SetValue( true );
          } else {
               checkBoxTemperatureDisturbances->SetValue( false );
          }

          wxString t = m_util.temperatureToStr( day->getTemperatureAdditionalCorrection(), true );
          if ( t.IsEmpty() )
               t = _T( "0" );
          comboBoxAdditionalTemperatureCorrection->SetValue( t );

          updateTemperatureAfterCorectionsValue();

          // box cervix
          // cervix - position
          if ( day->getCervixPosition() == CERVIX_HIGH ) {
               comboBoxCervixPosition->SetValue( string_cervixHigh_long );
          } else if ( day->getCervixPosition() == CERVIX_ABOVE_MIDDLE ) {
               comboBoxCervixPosition->SetValue( string_cervixAboveMiddle_long );
          } else if ( day->getCervixPosition() == CERVIX_IN_MIDDLE ) {
               comboBoxCervixPosition->SetValue( string_cervixInMiddle_long );
          } else if ( day->getCervixPosition() == CERVIX_BELOW_MEDDLE ) {
               comboBoxCervixPosition->SetValue( string_cervixBelowMiddle_long );
          } else if ( day->getCervixPosition() == CERVIX_LOW ) {
               comboBoxCervixPosition->SetValue( string_cervixLow_long );
          } else {
               comboBoxCervixPosition->SetValue( m_none );
          }

          //cervix - dilation
          if ( day->getCervixDilation() == CERVIX_OPEN ) {
               comboBoxCervixDilation->SetValue( string_cervixOpen_long );
          } else if ( day->getCervixDilation() == CERVIX_HALF_OPEN ) {
               comboBoxCervixDilation->SetValue( string_cervixHalfOpen_long );
          } else if ( day->getCervixDilation() == CERVIX_CLOSED ) {
               comboBoxCervixDilation->SetValue( string_cervixClosed_long );
          } else {
               comboBoxCervixDilation->SetValue( m_none );
          }

          // cervix - hardness
          if ( day->getCervixHardness() == CERVIX_SOFT ) {
               comboBoxCervixHardness->SetValue( string_cervixSoft_long );
          } else if ( day->getCervixHardness() == CERVIX_RATHER_FIRM ) {
               comboBoxCervixHardness->SetValue( string_cervixRatherFirm_long );
          } else if ( day->getCervixHardness() == CERVIX_FIRM ) {
               comboBoxCervixHardness->SetValue( string_cervixFirm_long );
          } else {
               comboBoxCervixHardness->SetValue( m_none );
          }

          // box other
          if ( day->getOvulationPain() == 1 ) {
               checkBoxOvulationPain1->SetValue( true );
               checkBoxOvulationPain2->SetValue( false );
          } else if ( day->getOvulationPain() == 2 ) {
               checkBoxOvulationPain1->SetValue( false );
               checkBoxOvulationPain2->SetValue( true );
          } else {
               checkBoxOvulationPain1->SetValue( false );
               checkBoxOvulationPain2->SetValue( false );
          }

          if ( day->getBreastsTension() == 1 ) {
               checkBoxBreastsTension1->SetValue( true );
               checkBoxBreastsTension2->SetValue( false );
          } else if ( day->getBreastsTension() == 2 ) {
               checkBoxBreastsTension1->SetValue( false );
               checkBoxBreastsTension2->SetValue( true );
          } else {
               checkBoxBreastsTension1->SetValue( false );
               checkBoxBreastsTension2->SetValue( false );
          }

          if ( day->getSpotting() == 1 ) {
               checkBoxSpotting1->SetValue( true );
               checkBoxSpotting2->SetValue( false );
          } else if ( day->getSpotting() == 2 ) {
               checkBoxSpotting1->SetValue( false );
               checkBoxSpotting2->SetValue( true );
          } else {
               checkBoxSpotting1->SetValue( false );
               checkBoxSpotting2->SetValue( false );
          }

          textAdditionalNotes->SetValue( day->getAdditionalNotes() );
          textAdditionalNotes->SetInsertionPointEnd();
     } else {
          textCardNo->SetLabel( _T( "???" ) );
          textCycleDay->SetLabel( _T( "???" ) );
          textDate->SetLabel( _T( "???" ) );
     }

     if ( m_cycleData->getCard()->getCardLocked() ) {
          // lock everything
          staticCardLocked->Show();
     } else {
          staticCardLocked->Hide();
     }
     updateButtonsState();
}

/**
 * update value of the 'm_temperatureAfterCorections' variable and refresh the field.
 */
void dayFrame::updateTemperatureAfterCorectionsValue()
{
     // reading data from fields
     if ( comboBoxMeasuredTemperature->GetValue().IsSameAs( m_none ) ) {
          m_temperatureAfterCorections = -1;
          textTemperatureAfterCorections->SetLabel( _T( "--" ) );
          return;
     }

     int tempValue = m_util.strToTemperature( comboBoxMeasuredTemperature->GetValue() );
     wxDateTime tempTime = wxDateTime( m_util.strToInt( comboBoxMeasurementTimeHour->GetValue() ), m_util.strToInt( comboBoxMeasurementTimeMinute->GetValue() ), 0, 0 );

     int tempPlace = PLACE_VAGINA;
     if ( comboBoxMeasurementPlace->GetValue().IsSameAs( string_placeMouth ) )
          tempPlace = PLACE_MOUTH;
     else if ( comboBoxMeasurementPlace->GetValue().IsSameAs( string_placeRectum ) )
          tempPlace = PLACE_RECTUM;

     int tempAdditCorrections = m_util.strToTemperature( comboBoxAdditionalTemperatureCorrection->GetValue() );

     // calculating new value of the 'm_temperatureAfterCorections' variable.
     m_temperatureAfterCorections = m_cycleData->calculateCorrectTemperatureValue( tempValue, tempTime, tempPlace, tempAdditCorrections );
     if ( m_temperatureAfterCorections > 0 ) {
          textTemperatureAfterCorections->SetLabel( m_util.temperatureToStr( m_temperatureAfterCorections, false ) );
          //textTemperatureAfterCorections->SetLabel( _T( "--" ) );
     } else {
     }
}

/**
 * update the buttons state (buttonSave, buttonCancel).
 */
void dayFrame::updateButtonsState()
{
     if (m_cycleData->getCard()->getCardLocked() || m_changes == 0) {
          buttonSave->Enable( false );
          buttonCancel->Enable( false );
     } else {
          buttonSave->Enable( true );
          buttonCancel->Enable( true );
     }

     if ( m_cycleData->getActiveDay() > 1 ) {
          buttonPreviousDay->Enable( true );
     } else {
          buttonPreviousDay->Enable( false );
     }
     if ( m_cycleData->getActiveDay() < m_cycleData->getDaysCount() ) {
          buttonNextDay->Enable( true );
     } else {
          buttonNextDay->Enable( false );
     }
}

/**
 * ask to save chages.
 */
bool dayFrame::checkIfDataHasBeenChanged( bool cancelAllowed )
{
     if ( !m_cycleData->getCard()->getCardLocked() && m_changes > 0 ) {
          int answer;
          if ( cancelAllowed ) {
               answer = wxMessageBox( _( "Do you want to save day's data changes? \nNote: Not saved data will be lost!" ), _( "Warning" ), wxYES_NO | wxCANCEL );
          } else {
               answer = wxMessageBox( _( "Do you want to save day's data changes? \nNote: Not saved data will be lost!" ), _( "Warning" ), wxYES_NO );
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
     return true;
}

/**
 *
 */
int dayFrame::calculateMucusAppearance()
{
     int tmp = 0;
     if ( checkBoxMucusAppearanceOpaque->GetValue() ) {
          tmp += MUCUS_OPAQUE;
     }
     if ( checkBoxMucusAppearanceWhite->GetValue() ) {
          tmp += MUCUS_WHITE;
     }
     if ( checkBoxMucusAppearanceYellowish->GetValue() ) {
          tmp += MUCUS_YELLOWISH;
     }
     if ( checkBoxMucusAppearanceTacky->GetValue() ) {
          tmp += MUCUS_TACKY;
     }
     if ( checkBoxMucusAppearanceClear->GetValue() ) {
          tmp += MUCUS_CLEAR;
     }
     if ( checkBoxMucusAppearanceStretchy->GetValue() ) {
          tmp += MUCUS_STRETCHY;
     }
     if ( checkBoxMucusAppearanceSeminalResidue->GetValue() ) {
          tmp += MUCUS_SEMINALRESIDUE;
     }
     if ( checkBoxMucusAmount1->GetValue() ) {
          tmp += MUCUS_AMOUNT1;
     }
     if ( checkBoxMucusAmount2->GetValue() ) {
          tmp += MUCUS_AMOUNT2;
     }
     if ( checkBoxMucusAmount3->GetValue() ) {
          tmp += MUCUS_AMOUNT3;
     }
     if ( checkBoxLengthOfStretch1->GetValue() ) {
          tmp += MUCUS_LENGHTOFSTRETCH1;
     }
     if ( checkBoxLengthOfStretch2->GetValue() ) {
          tmp += MUCUS_LENGHTOFSTRETCH2;
     }
     if ( checkBoxLengthOfStretch3->GetValue() ) {
          tmp += MUCUS_LENGHTOFSTRETCH3;
     }
     //if ( tmp == 0 )
     //    tmp = -1;
     return tmp;
}

/**
 * save updated data to the m_cycleData object and refresh the view.
 */
bool dayFrame::save()
{
     if ( m_changes > 0 ) {
          if ( m_cycleData->getActiveCard() > 0 && m_cycleData->getActiveDay() > 0 ) {
               //cardEntry * card = m_cycleData->getCard();
               dayEntry * day = m_cycleData->getDay();

               // box basic
               if ( checkBoxMenstruation1->GetValue() ) {
                    day->setMenstruation( 1 );
               } else if ( checkBoxMenstruation2->GetValue() ) {
                    day->setMenstruation( 2 );
               } else {
                    day->setMenstruation( -1 );
               }

               wxString output = textCoitusRecord->GetValue();
               output = output.Trim( true );
               output = output.Trim( false );

               if ( !output.IsEmpty() ) {
                    day->setCoitusRecord( output.Length() );
               } else {
                    day->setCoitusRecord( -1 );
               }

               day->setOtherDisturbances( checkBoxOtherDisturbances->GetValue() );

               // box mucus
               if ( comboBoxMucusFeeling->GetValue().IsSameAs( string_mucusDry_long ) ) {
                    day->setMucusFeelingExperience( MUCUS_DRY );
               } else if ( comboBoxMucusFeeling->GetValue().IsSameAs( string_mucusMoist_long ) ) {
                    day->setMucusFeelingExperience( MUCUS_MOIST );
               } else if ( comboBoxMucusFeeling->GetValue().IsSameAs( string_mucusWet_long ) ) {
                    day->setMucusFeelingExperience( MUCUS_WET );
               } else if ( comboBoxMucusFeeling->GetValue().IsSameAs( string_mucusSlippery_long ) ) {
                    day->setMucusFeelingExperience( MUCUS_SLIPPERY );
               } else {
                    day->setMucusFeelingExperience( -1 );
               }

               day->setMucusAppearance( calculateMucusAppearance() );

               // box temperature
               if ( comboBoxMeasuredTemperature->GetValue().IsSameAs( m_none ) ) {
                    day->setTemperatureMeasuredValue( -1 );
               } else {
                    int value = m_util.strToTemperature( comboBoxMeasuredTemperature->GetValue() );
                    day->setTemperatureMeasuredValue( value );
               }

               day->setTemperatureMeasurementTime( wxDateTime( m_util.strToInt( comboBoxMeasurementTimeHour->GetValue() ), m_util.strToInt( comboBoxMeasurementTimeMinute->GetValue() ), 0, 0 ) );

               if ( comboBoxMeasurementPlace->GetValue().IsSameAs( string_placeMouth ) ) {
                    day->setTemperatureMeasurementPlace( PLACE_MOUTH );
               } else if ( comboBoxMeasurementPlace->GetValue().IsSameAs( string_placeRectum ) ) {
                    day->setTemperatureMeasurementPlace( PLACE_RECTUM );
               } else {
                    day->setTemperatureMeasurementPlace( PLACE_VAGINA );
               }

               day->setTemperatureDisturbances( checkBoxTemperatureDisturbances->GetValue() );
               day->setTemperatureAdditionalCorrection( m_util.strToTemperature( comboBoxAdditionalTemperatureCorrection->GetValue() ) );
               day->setTemperatureValueAfterCorrections( m_temperatureAfterCorections );

               // box cervix
               // cervix - position
               if ( comboBoxCervixPosition->GetValue().IsSameAs( string_cervixHigh_long ) ) {
                    day->setCervixPosition( CERVIX_HIGH );
               } else if ( comboBoxCervixPosition->GetValue().IsSameAs( string_cervixAboveMiddle_long ) ) {
                    day->setCervixPosition( CERVIX_ABOVE_MIDDLE );
               } else if ( comboBoxCervixPosition->GetValue().IsSameAs( string_cervixInMiddle_long ) ) {
                    day->setCervixPosition( CERVIX_IN_MIDDLE );
               } else if ( comboBoxCervixPosition->GetValue().IsSameAs( string_cervixBelowMiddle_long ) ) {
                    day->setCervixPosition( CERVIX_BELOW_MEDDLE );
               } else if ( comboBoxCervixPosition->GetValue().IsSameAs( string_cervixLow_long ) ) {
                    day->setCervixPosition( CERVIX_LOW );
               } else {
                    day->setCervixPosition( -1 );
               }

               //cervix - dilation
               if ( comboBoxCervixDilation->GetValue().IsSameAs( string_cervixOpen_long ) ) {
                    day->setCervixDilation( CERVIX_OPEN );
               } else if ( comboBoxCervixDilation->GetValue().IsSameAs( string_cervixHalfOpen_long ) ) {
                    day->setCervixDilation( CERVIX_HALF_OPEN );
               } else if ( comboBoxCervixDilation->GetValue().IsSameAs( string_cervixClosed_long ) ) {
                    day->setCervixDilation( CERVIX_CLOSED );
               } else {
                    day->setCervixDilation( -1 );
               }

               // cervix - hardness
               if ( comboBoxCervixHardness->GetValue().IsSameAs( string_cervixSoft_long ) ) {
                    day->setCervixHardness( CERVIX_SOFT );
               } else if ( comboBoxCervixHardness->GetValue().IsSameAs( string_cervixRatherFirm_long ) ) {
                    day->setCervixHardness( CERVIX_RATHER_FIRM );
               } else if ( comboBoxCervixHardness->GetValue().IsSameAs( string_cervixFirm_long ) ) {
                    day->setCervixHardness( CERVIX_FIRM );
               } else {
                    day->setCervixHardness( -1 );
               }

               // box other
               if ( checkBoxOvulationPain1->GetValue() ) {
                    day->setOvulationPain( 1 );
               } else if ( checkBoxOvulationPain2->GetValue() ) {
                    day->setOvulationPain( 2 );
               } else {
                    day->setOvulationPain( -1 );
               }

               if ( checkBoxBreastsTension1->GetValue() ) {
                    day->setBreastsTension( 1 );
               } else if ( checkBoxBreastsTension2->GetValue() ) {
                    day->setBreastsTension( 2 );
               } else {
                    day->setBreastsTension( -1 );
               }

               if ( checkBoxSpotting1->GetValue() ) {
                    day->setSpotting( 1 );
               } else {
                    if ( checkBoxSpotting2->GetValue() ) {
                         day->setSpotting( 2 );
                    } else {
                         day->setSpotting( -1 );
                    }
                    day->setAdditionalNotes( textAdditionalNotes->GetValue() );
               }
          } else {
          }
          m_cycleData->setCardModified( true );
     }

     m_config->checkCurrentDayVisibility = true;

     if ( changesMeasuredTemperature->GetLabel().IsSameAs( _T( "*" ) ) ||
               changesMeasuredTime->GetLabel().IsSameAs( _T( "*" ) ) ||
               changesMeasuredPlace->GetLabel().IsSameAs( _T( "*" ) ) ||
               changesTemperatureDisturbances->GetLabel().IsSameAs( _T( "*" ) ) ||
               changesAdditionalTemperatureCorrection->GetLabel().IsSameAs( _T( "*" ) )
        ) {
          if ( m_cycleData->getCard()->getResultTemperatureHighLevelStart() > 0 ) {
               m_cycleData->setResultTemperaturesLevels( m_cycleData->getActiveCard() , m_cycleData->getCard()->getResultTemperatureHighLevelStart(), false );
               sendDataUpdateEvent( ACTIVE_DAY_UPDATE_WITH_RESULTS, _T( "refresh current day and following if the row size will change. Also refresh previous and next day where temperature had been measured. Also refresh days with low and high levels of temperatures." ) );
          } else {
               sendDataUpdateEvent( ACTIVE_DAY_UPDATE_WITH_TEMP, _T( "refresh current day and following if the row size will change. Also refresh previous and next day where temperature had been measured." ) );
          }
     } else {
          sendDataUpdateEvent( ACTIVE_DAY_UPDATE, _T( "refresh current day and following if the row size will change" ) );
     }

     return true;
}

/**
 *
 */
void dayFrame::sendDataUpdateEvent( int id, wxString message )
{
     wxCommandEvent event( wxEVT_DAY_DATA_MODIFIED_EVENT, DAY_EVENT );
     event.SetInt( id );
     event.SetString( message );
     wxPostEvent( m_parent, event );
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/
