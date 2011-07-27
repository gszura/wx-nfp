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
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/listbox.h>
#include <wx/spinctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/combobox.h>
//*)

#include "configClass.h"
#include "utilClass.h"
#include <wx/fontdlg.h>

/******************************************************************************/

#define CONFIG_CHANGED                 91
#define CONFIG_FONT_CHANGED            92
#define CONFIG_LANGUAGE_CHANGED        93
#define CONFIG_BUTTONS_STYLE_CHANGED   94

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
    configFrame(wxWindow* parent,configClass *config, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~configFrame();

    //(*Declarations(configFrame)
    wxStaticText* staticUnits;
    wxComboBox* comboBoxTemperatureRangeLow;
    wxPanel* panelApplication;
    wxButton* buttonFontResultResults;
    wxStaticText* changesFontResultHeader;
    wxButton* buttonColourMarkedCell2;
    wxButton* buttonFontResultDefault;
    wxStaticText* changesBreastAutocontrolInterval;
    wxButton* buttonCancel;
    wxStaticText* changesTemperatureRangeHigh;
    wxStaticText* space7;
    wxPanel* panelColours;
    wxStaticText* space3;
    wxButton* buttonFontHeadTopic;
    wxButton* buttonFontResultPhases;
    wxListBox* listBoxLanguage;
    wxStaticText* changesFontResultDefault;
    wxStaticText* changesColourPointAfter;
    wxPanel* panelFonts;
    wxStaticText* staticLengthUnit;
    wxStaticText* changesColourPhaseLine;
    wxNotebook* notebook;
    wxStaticText* changesColourTemperatureLine;
    wxCheckBox* checkBoxCheckForUpdates;
    wxButton* buttonSetDefaults;
    wxStaticText* changesColourTemperatureLevelLine;
    wxTextCtrl* textUpdatesProxy;
    wxStaticText* changesFontHeadName;
    wxStaticText* staticLanguage;
    wxComboBox* comboBoxTemperatureUnit;
    wxStaticText* space4;
    wxStaticText* changesFontResultHeart;
    wxStaticText* space10;
    wxButton* buttonColourTemperatureLevelLine;
    wxStaticText* changesRememberPosition;
    wxStaticText* space8;
    wxComboBox* comboBoxLengthUnit;
    wxStaticText* space2;
    wxStaticText* changesCheckForUpdates;
    wxStaticText* staticFontResultHeart;
    wxButton* buttonColourBorders;
    wxStaticText* changesFontResultResults;
    wxStaticText* space5;
    wxStaticText* changesColourBorders;
    wxCheckBox* checkBoxBreastsAutocontrolReminder;
    wxStaticText* changesColourCell;
    wxStaticText* changesFontHeadValue;
    wxButton* buttonColourPointAfter;
    wxStaticText* staticBreastsAutocontrolReminderDay1;
    wxStaticText* changesFontHeadTopic;
    wxStaticText* changesLengthUnit;
    wxStaticText* changesBreastsAutocontrolReminder;
    wxStaticText* space1;
    wxStaticText* changesBreastsAutocontrolReminderDay;
    wxCheckBox* checkBoxFlatButtons;
    wxButton* buttonFontResultHeader;
    wxSpinCtrl* spinCtrlBreastAutocontrolInterval;
    wxButton* buttonColourCell21;
    wxStaticText* changesColourBackground;
    wxButton* buttonColourMarkedCell1;
    wxStaticText* staticBreastAutocontrolInterval1;
    wxStaticText* changesLanguage;
    wxStaticText* staticColourCell;
    wxButton* buttonFontHeadName;
    wxStaticText* changesColourPointNormal;
    wxStaticText* space9;
    wxStaticText* staticBreastAutocontrolInterval2;
    wxStaticText* space6;
    wxCheckBox* checkBoxRememberPosition;
    wxStaticText* staticTemperatureRange;
    wxCheckBox* checkBoxOpenLastOpenedFile;
    wxStaticText* staticColours;
    wxStaticText* changesColourPointBefore;
    wxCheckBox* checkBoxCheckForMissingDays;
    wxButton* buttonColourCell12;
    wxPanel* panelOther;
    wxButton* buttonColourCell11;
    wxStaticText* changesCheckForMissingDays;
    wxStaticText* staticTemperatureCorF2;
    wxStaticText* staticTemperatureRangeHigh;
    wxStaticText* changesTemperatureUnit;
    wxPanel* panelMain;
    wxButton* buttonFontHeadValue;
    wxButton* buttonOk;
    wxButton* buttonColourPhaseLine;
    wxStaticText* changesFontResultPhases;
    wxStaticText* staticUpdatesProxy;
    wxStaticText* staticTemperatureCorF1;
    wxStaticText* staticFonts;
    wxButton* buttonColourPointNormal;
    wxStaticText* changesUpdatesProxy;
    wxButton* buttonColourTemperatureLine;
    wxButton* buttonSave;
    wxComboBox* comboBoxTemperatureRangeHigh;
    wxStaticText* staticTemperatureRangeLow;
    wxButton* buttonColourPointBefore;
    wxStaticText* changesFlatButtons;
    wxPanel* panelGeneral;
    wxSpinCtrl* spinCtrlBreastsAutocontrolReminderDay;
    wxStaticText* staticBreastsAutocontrolReminderDay2;
    wxButton* buttonColourCell22;
    wxButton* buttonFontResultHeart;
    wxButton* buttonColourBackground;
    wxStaticText* changesTemperatureRangeLow;
    wxStaticText* staticTemperatureUnit;
    wxStaticText* changesOpenLastOpenedFile;
    //*)

protected:
    //(*Identifiers(configFrame)
    static const long ID_staticLanguage;
    static const long ID_changesLanguage;
    static const long ID_listBoxLanguage;
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
    static const long ID_checkBoxOpenLastOpenedFile;
    static const long ID_changesOpenLastOpenedFile;
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
    static const long ID_staticUnits;
    static const long ID_space7;
    static const long ID_staticLengthUnit;
    static const long ID_comboBoxLengthUnit;
    static const long ID_changesLengthUnit;
    static const long ID_space8;
    static const long ID_staticTemperatureUnit;
    static const long ID_comboBoxTemperatureUnit;
    static const long ID_changesTemperatureUnit;
    static const long ID_staticTemperatureRange;
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
    static const long ID_staticFontResultHeart;
    static const long ID_buttonFontResultHeart;
    static const long ID_changesFontResultHeart;
    static const long ID_buttonFontResultResults;
    static const long ID_changesFontResultResults;
    static const long ID_buttonFontResultPhases;
    static const long ID_changesFontResultPhases;
    static const long ID_panelFonts;
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
    void buttonFontResultHeartClick (wxCommandEvent& event);
    void buttonFontResultResultsClick (wxCommandEvent& event);
    void buttonFontResultPhasesClick (wxCommandEvent& event);

    void buttonSetDefaultsClick (wxCommandEvent& event);
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
};

#endif // __CONFIG_FRAME__
