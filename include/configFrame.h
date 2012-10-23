/***************************************************************
 * Name:      configFrame.h
 * Purpose:   Dialog for editing configuration data - header file
 * Author:    Grzegorz Szura (grzegorz@szura.net)
 * Created:   2010-03-11
 * Copyright: Grzegorz Szura (http://www.szura.net)
 * License:
 **************************************************************/

#ifndef __CONFIG_FRAME__
#define __CONFIG_FRAME__

//(*Headers(configFrame)
#include <wx/spinctrl.h>
#include <wx/combobox.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/listbox.h>
//*)

#include "configClass.h"
#include "utilClass.h"
#include <wx/fontdlg.h>

/******************************************************************************/

#define CONFIG_CHANGED                 91
#define CONFIG_FONT_CHANGED            92
#define CONFIG_LANGUAGE_CHANGED        93
#define CONFIG_BUTTONS_STYLE_CHANGED   94
#define CONFIG_SYNC_SERVER_CHANGED     95

#define PAGE_ANALYSIS_NO                2

extern const wxEventType wxEVT_CONFIG_DATA_MODIFIED_EVENT;

enum {
    CONFIG_EVENT
};

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
class configFrame: public wxDialog
{
public:
    configFrame(wxWindow* parent,configClass *config, size_t pageNo=0, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~configFrame();

    //(*Declarations(configFrame)
    wxStaticText* changesCheckForMissingDays;
    wxButton* buttonFontResultDefault;
    wxStaticText* changesColourPhaseLine;
    wxStaticText* StaticText1;
    wxStaticText* StaticText23;
    wxComboBox* comboBoxAutoanalyzeCardPreferResult3;
    wxButton* buttonColourCell22;
    wxStaticText* staticCustomServerUri;
    wxStaticText* space1;
    wxButton* buttonColourPointAfter;
    wxStaticText* StaticText13;
    wxStaticText* changesColourBorders;
    wxCheckBox* checkBoxBreastsAutocontrolReminder;
    wxButton* buttonOk;
    wxStaticText* changesFontResultDefault;
    wxComboBox* comboBoxAutoanalyzeCardPreferResult2;
    wxStaticText* changesPassword;
    wxCheckBox* checkBoxAutosaveSet;
    wxButton* buttonColourTemperatureLevelLine;
    wxStaticText* space2;
    wxStaticText* changesFontResultPhases;
    wxStaticText* changesSyncFileAutomatically;
    wxStaticText* changesAutosaveSet;
    wxStaticText* StaticText32;
    wxStaticText* staticTemperatureCorF1;
    wxStaticText* staticTemperatureCorF2;
    wxComboBox* comboBoxAutoanalyzeCardPreferResult1;
    wxStaticText* changesCustomServerUri;
    wxStaticText* StaticText20;
    wxButton* buttonFontResultPhases;
    wxButton* buttonFontHeadTopic;
    wxStaticText* staticBreastsAutocontrolReminderDay1;
    wxStaticText* space3;
    wxStaticText* StaticText6;
    wxButton* buttonColourBorders;
    wxStaticText* changesColourBackground;
    wxPanel* panelGeneral;
    wxStaticText* changesAutoanalyzeCardPreferResult3;
    wxSpinCtrl* spinMaxAllowedNotMesuredLowLevelDays;
    wxStaticText* StaticText18;
    wxStaticText* changesAutoanalyzeCardPreferResult4;
    wxStaticText* StaticText17;
    wxStaticText* StaticText24;
    wxStaticText* staticLengthUnit;
    wxStaticText* space6;
    wxStaticText* StaticText30;
    wxStaticText* StaticText15;
    wxComboBox* comboBoxTemperatureRangeLow;
    wxPanel* panelMain;
    wxSpinCtrl* spinNumberOfHistoricalCyclesToUse;
    wxStaticText* changesTemperatureRangeLow;
    wxStaticText* space5;
    wxComboBox* comboBoxAutoanalyzeCardPreferResult5;
    wxStaticText* changesBreastsAutocontrolReminder;
    wxButton* buttonSetDefaults;
    wxPanel* panelColours;
    wxStaticText* StaticText22;
    wxStaticText* changesColourPointNormal;
    wxStaticText* staticTemperatureUnit;
    wxSpinCtrl* spinMaxAllowedNotMesuredHighLevelDays;
    wxCheckBox* checkBoxCheckForUpdates;
    wxStaticText* StaticText3;
    wxCheckBox* checkBoxShowAutoanalysisDetails;
    wxStaticText* space4;
    wxStaticText* changesBreastAutocontrolInterval;
    wxStaticText* StaticText2;
    wxStaticText* changesFontResultHeader;
    wxTextCtrl* textUpdatesProxy;
    wxCheckBox* checkBoxOpenLastOpenedFile;
    wxStaticText* StaticText27;
    wxCheckBox* checkBoxRememberPosition;
    wxButton* buttonFontResultResults;
    wxButton* buttonColourCell12;
    wxStaticText* changesShowAutoanalysisDetails;
    wxStaticText* changesMaxIncludedNotMesuredHighLevelDays;
    wxStaticText* changesAutoanalyzeCardPreferResult1;
    wxStaticText* changesAutosaveChanges;
    wxTextCtrl* textCustomServerUri;
    wxPanel* panelFonts;
    wxStaticText* staticColourCell;
    wxStaticText* staticLanguage;
    wxStaticText* StaticText16;
    wxStaticText* staticPasswordNote;
    wxStaticText* changesColourCell;
    wxStaticText* changesFlatButtons;
    wxStaticText* changesUpdatesProxy;
    wxTextCtrl* textPassword;
    wxButton* buttonColourCell11;
    wxButton* buttonSave;
    wxStaticText* staticBreastAutocontrolInterval1;
    wxStaticText* changesFontHeadName;
    wxComboBox* comboBoxAutoanalyzeCardPreferResult4;
    wxPanel* panelOther;
    wxStaticText* changesUseCustomServer;
    wxButton* buttonCancel;
    wxStaticText* changesNumberOfHistoricalCyclesToUse;
    wxCheckBox* checkBoxRememberPassword;
    wxStaticText* changesAutoanalyzeCardPreferResult5;
    wxButton* buttonColourCell21;
    wxStaticText* StaticText25;
    wxStaticText* StaticText26;
    wxSpinCtrl* spinMaxIncludedNotMesuredHighLevelDays;
    wxListBox* listBoxLanguage;
    wxComboBox* comboBoxTemperatureRangeHigh;
    wxStaticText* changesColourTemperatureLine;
    wxStaticText* StaticText14;
    wxStaticText* StaticText4;
    wxStaticText* StaticText8;
    wxCheckBox* checkBoxUseCustomServer;
    wxStaticText* changesMaxAllowedNotMesuredHighLevelDays;
    wxCheckBox* checkBoxIncludeNotMesuredDaysIfAfterMucusPeak;
    wxStaticText* changesOpenLastOpenedFile;
    wxButton* buttonFontResultHeader;
    wxStaticText* StaticText9;
    wxStaticText* StaticText21;
    wxStaticText* changesMaxIncludedNotMesuredLowLevelDays;
    wxStaticText* changesCheckForUpdates;
    wxStaticText* changesLanguage;
    wxStaticText* space10;
    wxStaticText* changesFontHeadTopic;
    wxButton* buttonColourPointBefore;
    wxPanel* panelApplication;
    wxStaticText* StaticText29;
    wxPanel* PanelAnalysis;
    wxButton* buttonColourPointNormal;
    wxStaticText* space9;
    wxStaticText* changesIncludeNotMesuredDaysIfAfterMucusPeak;
    wxButton* buttonFontHeadValue;
    wxStaticText* changesLengthUnit;
    wxButton* buttonColourMarkedCell1;
    wxButton* buttonColourTemperatureLine;
    wxStaticText* StaticText19;
    wxCheckBox* checkBoxCheckForMissingDays;
    wxStaticText* staticAnalysis2;
    wxStaticText* staticBreastAutocontrolInterval2;
    wxButton* buttonColourBackground;
    wxComboBox* comboBoxTemperatureUnit;
    wxStaticText* staticTemperatureRangeLow;
    wxStaticText* staticBreastsAutocontrolReminderDay2;
    wxStaticText* changesFontHeadValue;
    wxStaticText* changesAutoanalyzeCardPreferResult2;
    wxStaticText* StaticText28;
    wxCheckBox* checkBoxFlatButtons;
    wxSpinCtrl* spinMaxIncludedNotMesuredLowLevelDays;
    wxStaticText* StaticText33;
    wxStaticText* changesRememberPassword;
    wxStaticText* staticAlalysis1;
    wxStaticText* changesMaxAllowedNotMesuredLowLevelDays;
    wxStaticText* changesColourTemperatureLevelLine;
    wxStaticText* StaticText7;
    wxCheckBox* checkBoxAutoanalyzeCard;
    wxStaticText* StaticText11;
    wxSpinCtrl* spinCtrlBreastsAutocontrolReminderDay;
    wxStaticText* changesRememberPosition;
    wxNotebook* notebook;
    wxSpinCtrl* spinCtrlBreastAutocontrolInterval;
    wxStaticText* StaticText12;
    wxStaticText* staticColours;
    wxStaticText* changesFontResultResults;
    wxButton* buttonColourMarkedCell2;
    wxStaticText* staticFonts;
    wxStaticText* staticPassword;
    wxStaticText* StaticText10;
    wxStaticText* changesTemperatureUnit;
    wxComboBox* comboBoxLengthUnit;
    wxButton* buttonFontHeadName;
    wxStaticText* StaticText5;
    wxStaticText* changesAutoanalyzeCard;
    wxStaticText* changesBreastsAutocontrolReminderDay;
    wxStaticText* changesTemperatureRangeHigh;
    wxStaticText* changesColourPointBefore;
    wxCheckBox* checkBoxAutosaveChanges;
    wxStaticText* staticTemperatureRangeHigh;
    wxStaticText* changesColourPointAfter;
    wxButton* buttonColourPhaseLine;
    wxCheckBox* checkBoxSyncFileAutomatically;
    wxStaticText* staticUpdatesProxy;
    //*)

protected:
    //(*Identifiers(configFrame)
    static const long ID_staticLanguage;
    static const long ID_changesLanguage;
    static const long ID_listBoxLanguage;
    static const long ID_checkBoxOpenLastOpenedFile;
    static const long ID_changesOpenLastOpenedFile;
    static const long ID_checkBoxAutosaveChanges;
    static const long ID_changesAutosaveChanges;
    static const long ID_checkBoxAutosaveSet;
    static const long ID_changesAutosaveSet;
    static const long ID_checkBoxSyncFileAutomatically;
    static const long ID_changesSyncFileAutomatically;
    static const long ID_checkBoxRememberPosition;
    static const long ID_changesRememberPosition;
    static const long ID_checkBoxFlatButtons;
    static const long ID_changesFlatButtons;
    static const long ID_checkBoxCheckForUpdates;
    static const long ID_changesCheckForUpdates;
    static const long ID_space2;
    static const long ID_staticUpdatesProxy;
    static const long ID_space1;
    static const long ID_space3;
    static const long ID_textUpdatesProxy;
    static const long ID_changesUpdatesProxy;
    static const long ID_panelGeneral;
    static const long ID_checkBoxCheckForMissingDays;
    static const long ID_changesCheckForMissingDays;
    static const long ID_checkBoxBreastsAutocontrolReminder;
    static const long ID_changesBreastsAutocontrolReminder;
    static const long ID_space5;
    static const long ID_staticBreastsAutocontrolReminderDay1;
    static const long ID_spinCtrlBreastsAutocontrolReminderDay;
    static const long ID_staticBreastsAutocontrolReminderDay2;
    static const long ID_changesBreastsAutocontrolReminderDay;
    static const long ID_space6;
    static const long ID_staticBreastAutocontrolInterval1;
    static const long ID_spinCtrlBreastAutocontrolInterval;
    static const long ID_staticBreastAutocontrolInterval2;
    static const long ID_changesBreastAutocontrolInterval;
    static const long ID_space9;
    static const long ID_staticTemperatureRangeHigh;
    static const long ID_comboBoxTemperatureRangeHigh;
    static const long ID_staticTemperatureCorF1;
    static const long ID_changesTemperatureRangeHigh;
    static const long ID_space10;
    static const long ID_staticTemperatureRangeLow;
    static const long ID_comboBoxTemperatureRangeLow;
    static const long ID_staticTemperatureCorF2;
    static const long ID_changesTemperatureRangeLow;
    static const long ID_panelApplication;
    static const long ID_checkBoxAutoanalyzeCard;
    static const long ID_changesAutoanalyzeCard;
    static const long ID_STATICTEXT14;
    static const long ID_checkBoxShowAutoanalysisDetails;
    static const long ID_changesShowAutoanalysisDetails;
    static const long ID_STATICTEXT10;
    static const long ID_STATICTEXT17;
    static const long ID_STATICTEXT18;
    static const long ID_spinMaxAllowedNotMesuredLowLevelDays;
    static const long ID_STATICTEXT19;
    static const long ID_STATICTEXT11;
    static const long ID_changesMaxAllowedNotMesuredLowLevelDays;
    static const long ID_STATICTEXT12;
    static const long ID_spinMaxIncludedNotMesuredLowLevelDays;
    static const long ID_STATICTEXT15;
    static const long ID_changesMaxIncludedNotMesuredLowLevelDays;
    static const long ID_STATICTEXT8;
    static const long ID_STATICTEXT9;
    static const long ID_spinMaxAllowedNotMesuredHighLevelDays;
    static const long ID_STATICTEXT21;
    static const long ID_changesMaxAllowedNotMesuredHighLevelDays;
    static const long ID_STATICTEXT23;
    static const long ID_STATICTEXT24;
    static const long ID_spinMaxIncludedNotMesuredHighLevelDays;
    static const long ID_STATICTEXT25;
    static const long ID_changesMaxIncludedNotMesuredHighLevelDays;
    static const long ID_STATICTEXT27;
    static const long ID_checkBoxIncludeNotMesuredDaysIfAfterMucusPeak;
    static const long ID_changesIncludeNotMesuredDaysIfAfterMucusPeak;
    static const long ID_STATICTEXT3;
    static const long ID_STATICTEXT5;
    static const long ID_STATICTEXT2;
    static const long ID_spinNumberOfHistoricalCyclesToUse;
    static const long ID_STATICTEXT4;
    static const long ID_changesNumberOfHistoricalCyclesToUse;
    static const long ID_STATICTEXT1;
    static const long ID_STATICTEXT6;
    static const long ID_STATICTEXT22;
    static const long ID_comboBoxAutoanalyzeCardPreferResult1;
    static const long ID_changesAutoanalyzeCardPreferResult1;
    static const long ID_STATICTEXT26;
    static const long ID_comboBoxAutoanalyzeCardPreferResult2;
    static const long ID_changesAutoanalyzeCardPreferResult2;
    static const long ID_STATICTEXT28;
    static const long ID_comboBoxAutoanalyzeCardPreferResult3;
    static const long ID_changesAutoanalyzeCardPreferResult3;
    static const long ID_STATICTEXT29;
    static const long ID_comboBoxAutoanalyzeCardPreferResult4;
    static const long ID_changesAutoanalyzeCardPreferResult4;
    static const long ID_STATICTEXT30;
    static const long ID_comboBoxAutoanalyzeCardPreferResult5;
    static const long ID_changesAutoanalyzeCardPreferResult5;
    static const long ID_PANEL1;
    static const long ID_staticColours;
    static const long ID_buttonColourBackground;
    static const long ID_changesColourBackground;
    static const long ID_staticColourCell;
    static const long ID_buttonColourCell11;
    static const long ID_buttonColourCell21;
    static const long ID_buttonColourMarkedCell1;
    static const long ID_buttonColourCell12;
    static const long ID_buttonColourCell22;
    static const long ID_buttonColourMarkedCell2;
    static const long ID_changesColourCell;
    static const long ID_buttonColourPointNormal;
    static const long ID_changesColourPointNormal;
    static const long ID_buttonColourPointBefore;
    static const long ID_changesColourPointBefore;
    static const long ID_buttonColourPointAfter;
    static const long ID_changesColourPointAfter;
    static const long ID_buttonColourTemperatureLine;
    static const long ID_changesColourTemperatureLine;
    static const long ID_buttonColourTemperatureLevelLine;
    static const long ID_changesColourTemperatureLevelLine;
    static const long ID_buttonColourPhaseLine;
    static const long ID_changesColourPhaseLine;
    static const long ID_buttonColourBorders;
    static const long ID_changesColourBorders;
    static const long ID_panelColours;
    static const long ID_staticFonts;
    static const long ID_buttonFontHeadTopic;
    static const long ID_changesFontHeadTopic;
    static const long ID_buttonFontHeadName;
    static const long ID_changesFontHeadName;
    static const long ID_buttonFontHeadValue;
    static const long ID_changesFontHeadValue;
    static const long ID_buttonFontResultHeader;
    static const long ID_changesFontResultHeader;
    static const long ID_buttonFontResultDefault;
    static const long ID_changesFontResultDefault;
    static const long ID_buttonFontResultResults;
    static const long ID_changesFontResultResults;
    static const long ID_buttonFontResultPhases;
    static const long ID_changesFontResultPhases;
    static const long ID_panelFonts;
    static const long ID_checkBoxRememberPassword;
    static const long ID_changesRememberPassword;
    static const long ID_STATICTEXT31;
    static const long ID_staticPassword;
    static const long ID_STATICTEXT35;
    static const long ID_STATICTEXT34;
    static const long ID_textPassword;
    static const long ID_STATICTEXT7;
    static const long ID_STATICTEXT32;
    static const long ID_staticPasswordNote;
    static const long ID_changesPassword;
    static const long ID_checkBoxUseCustomServer;
    static const long ID_changesUseCustomServer;
    static const long ID_STATICTEXT13;
    static const long ID_staticCustomServerUri;
    static const long ID_STATICTEXT16;
    static const long ID_STATICTEXT20;
    static const long ID_textCustomServerUri;
    static const long ID_changesCustomServerUri;
    static const long ID_staticLengthUnit;
    static const long ID_comboBoxLengthUnit;
    static const long ID_changesLengthUnit;
    static const long ID_staticTemperatureUnit;
    static const long ID_comboBoxTemperatureUnit;
    static const long ID_changesTemperatureUnit;
    static const long ID_buttonSetDefaults;
    static const long ID_panelOther;
    static const long ID_notebook;
    static const long ID_buttonSave;
    static const long ID_buttonCancel;
    static const long ID_space4;
    static const long ID_buttonOk;
    static const long ID_panelMain;
    //*)

private:
    //(*Handlers(configFrame)
    void configFrameClose (wxCloseEvent& event);
    void buttonOkClick (wxCommandEvent& event);
    void buttonCancelClick (wxCommandEvent& event);
    void buttonSaveClick (wxCommandEvent& event);
    void listBoxLanguageSelected (wxCommandEvent& event);
    void checkBoxRememberPositionClick (wxCommandEvent& event);
    void checkBoxFlatButtonsClick (wxCommandEvent& event);
    void checkBoxCheckForUpdatesClick (wxCommandEvent& event);
    void textUpdatesProxyUpdated (wxCommandEvent& event);
    void checkBoxOpenLastOpenedFileClick (wxCommandEvent& event);
    void checkBoxCheckForMissingDaysClick (wxCommandEvent& event);
    void checkBoxBreastsAutocontrolReminderClick (wxCommandEvent& event);
    void spinCtrlBreastsAutocontrolReminderDayUpdated (wxSpinEvent& event );
    void spinCtrlBreastAutocontrolIntervalUpdated (wxSpinEvent& event );
    void comboBoxLengthUnitUpdated (wxCommandEvent& event );
    void comboBoxTemperatureUnitUpdated (wxCommandEvent& event );
    void comboBoxTemperatureRangeHighUpdated (wxCommandEvent& event );
    void comboBoxTemperatureRangeLowUpdated (wxCommandEvent& event );
    void buttonColourBackgroundClick (wxCommandEvent& event);
    void buttonColourCell11Click (wxCommandEvent& event);
    void buttonColourCell12Click (wxCommandEvent& event);
    void buttonColourCell21Click (wxCommandEvent& event);
    void buttonColourCell22Click (wxCommandEvent& event);
    void buttonColourMarkedCell1Click (wxCommandEvent& event);
    void buttonColourMarkedCell2Click (wxCommandEvent& event);
    void buttonColourPointNormalClick (wxCommandEvent& event);
    void buttonColourPointBeforeClick (wxCommandEvent& event);
    void buttonColourPointAfterClick (wxCommandEvent& event);
    void buttonColourTemperatureLineClick (wxCommandEvent& event);
    void buttonColourTemperatureLevelLineClick (wxCommandEvent& event);
    void buttonColourPhaseLineClick (wxCommandEvent& event);
    void buttonColourBordersClick (wxCommandEvent& event);
    void buttonFontHeadTopicClick (wxCommandEvent& event);
    void buttonFontHeadNameClick (wxCommandEvent& event);
    void buttonFontHeadValueClick (wxCommandEvent& event);
    void buttonFontResultHeaderClick (wxCommandEvent& event);
    void buttonFontResultDefaultClick (wxCommandEvent& event);
    void buttonFontResultResultsClick (wxCommandEvent& event);
    void buttonFontResultPhasesClick (wxCommandEvent& event);
    void buttonSetDefaultsClick (wxCommandEvent& event);
    void checkBoxAutosaveChangesClick(wxCommandEvent& event);
    void checkBoxAutosaveSetClick(wxCommandEvent& event);
    void checkBoxAutoanalyzeCardClick(wxCommandEvent& event);
    void spinMaxAllowedNotMesuredLowLevelDaysChange(wxSpinEvent& event);
    void spinMaxIncludedNotMesuredLowLevelDaysChange(wxSpinEvent& event);
    void spinMaxAllowedNotMesuredHighLevelDaysChange(wxSpinEvent& event);
    void spinMaxIncludedNotMesuredHighLevelDaysChange(wxSpinEvent& event);
    void checkBoxIncludeNotMesuredDaysIfAfterMucusPeakClick(wxCommandEvent& event);
    void spinNumberOfHistoricalCyclesToUseChange(wxSpinEvent& event);
    void comboBoxAutoanalyzeCardPreferResult1TextUpdated(wxCommandEvent& event);
    void comboBoxAutoanalyzeCardPreferResult2TextUpdated(wxCommandEvent& event);
    void comboBoxAutoanalyzeCardPreferResult3TextUpdated(wxCommandEvent& event);
    void comboBoxAutoanalyzeCardPreferResult4TextUpdated(wxCommandEvent& event);
    void comboBoxAutoanalyzeCardPreferResult5TextUpdated(wxCommandEvent& event);
    void checkBoxShowAutoanalysisDetailsClick(wxCommandEvent& event);
    void checkBoxRememberPasswordClick(wxCommandEvent& event);
    void textPasswordText(wxCommandEvent& event);
    void checkBoxUseCustomServerClick(wxCommandEvent& event);
    void textCustomServerUriText(wxCommandEvent& event);
    void checkBoxSyncFileAutomaticallyClick(wxCommandEvent& event);
    //*)

private:
    void buildGui(wxWindow* parent);
    DECLARE_EVENT_TABLE()

    // My methods
public:
    void setButtonsStyle();
    void update();

private:
    void showColourDialog (wxButton*, wxString);
    void setColour (wxButton*, wxColour);
    void checkColourChanges ( wxButton*, wxColour, wxStaticText*);
    void checkCellsColourChanges();
    void showFontDialog (wxButton*, wxFont, wxColour, wxStaticText*, wxString);
    //void setFont (wxButton*, wxString);
    //void checkFontChanges ( wxButton*, wxFont, wxColour, wxStaticText*);
private:
    void updateButtonsState();
    bool save();
    bool areFontsTheSame (wxFont, wxFont, wxColour, wxColour);
    bool areFontsTheSame (wxFont, wxFont);
    void sendDataUpdateEvent (int, wxString);

    // My variables
private:
    wxWindow *m_parent;
    configClass *m_config;
    utilClass m_util;
    wxArrayString m_langAbbr;
    wxFontDialog *m_fontDialog;
    wxFontData m_fontData;
    int m_changes;
    bool m_init;
    wxArrayString m_langNames;
    wxArrayLong m_langIdentifiers;
    bool m_syncServerChanged;
};

#endif // __CONFIG_FRAME__
