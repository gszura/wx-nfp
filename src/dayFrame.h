/***************************************************************
 * Name:      dayFrame.cpp
 * Purpose:   Dialog for editing day's data - header file
 * Author:    Grzegorz Szura (grzegorz@szura.net)
 * Created:   2010-03-02
 * Copyright: Grzegorz Szura (http://www.szura.net)
 * License:
 **************************************************************/

#ifndef DAYFRAME_H
#define DAYFRAME_H

//(*Headers(dayFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/combobox.h>
//*)

#include "configClass.h"
#include "cyclesData.h"
#include "utilClass.h"

/******************************************************************************/

#define ACTIVE_DAY_UPDATE              1
#define ACTIVE_DAY_UPDATE_WITH_TEMP    2
#define ACTIVE_DAY_UPDATE_WITH_RESULTS 3
#define ACTIVE_DAY_CHANGED             4

extern const wxEventType wxEVT_DAY_DATA_MODIFIED_EVENT;

enum {
     DAY_EVENT
};

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
class dayFrame: public wxDialog {
public:
     dayFrame(wxWindow *parent, configClass *config, cycleDataClass *cycleData, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
     virtual ~dayFrame();

     //(*Declarations(dayFrame)
     wxStaticText* staticMucusAmount;
     wxStaticText* changesAdditionalNotes;
     wxButton* buttonNextDay;
     wxCheckBox* checkBoxMucusAppearanceOpaque;
     wxButton* buttonCancel;
     wxStaticText* changesCervixDilation;
     wxCheckBox* checkBoxBreastsTension1;
     wxStaticText* textCardNo;
     wxStaticText* staticOvulationPain;
     wxCheckBox* checkBoxOvulationPain1;
     wxStaticText* space3;
     wxStaticText* changesOvulationPain;
     wxStaticText* changesSexDay;
     wxStaticText* changesSpotting;
     wxComboBox* comboBoxCervixPosition;
     wxStaticText* staticMeasuredTemperature;
     wxStaticText* staticCardNo;
     wxCheckBox* checkBoxOtherDisturbances;
     wxStaticText* staticBreastsTension;
     wxComboBox* comboBoxCervixDilation;
     wxCheckBox* checkBoxLengthOfStretch2;
     wxStaticText* staticAdditionalNotes;
     wxStaticText* staticSexEvening;
     wxStaticText* staticMeasurementTime;
     wxCheckBox* checkBoxSpotting2;
     wxStaticText* changesMeasuredPlace;
     wxCheckBox* checkBoxLengthOfStretch1;
     wxStaticText* staticTemperatureAfterCorections;
     wxComboBox* comboBoxAdditionalTemperatureCorrection;
     wxStaticText* staticCervixHardness;
     wxCheckBox* checkBoxTemperatureDisturbances;
     wxStaticText* space2;
     wxStaticText* changesMeasuredTime;
     wxComboBox* comboBoxMeasurementTimeHour;
     wxCheckBox* checkBoxSpotting1;
     wxStaticText* staticLengthOfStretch;
     wxCheckBox* checkBoxSexDay;
     wxCheckBox* checkBoxMucusAppearanceSeminalResidue;
     wxTextCtrl* textMucusAppearance;
     wxStaticText* textCycleDay;
     wxComboBox* comboBoxMeasurementPlace;
     wxStaticText* changesOtherDisturbances;
     wxComboBox* comboBoxMeasurementTimeMinute;
     wxCheckBox* checkBoxMucusAppearanceWhite;
     wxStaticText* space1;
     wxCheckBox* checkBoxMucusAppearanceYellowish;
     wxCheckBox* checkBoxMucusAmount2;
     wxCheckBox* checkBoxLengthOfStretch3;
     wxStaticText* staticDate;
     wxStaticText* staticMucusAppearance;
     wxComboBox* comboBoxCervixHardness;
     wxStaticText* staticCervixPosition;
     wxStaticText* staticSexDay;
     wxStaticText* changesCervixHardness;
     wxStaticText* changesCervixPosition;
     wxStaticText* textTemperatureAfterCorections;
     wxCheckBox* checkBoxMucusAmount3;
     wxStaticText* changesBreastsTension;
     wxComboBox* comboBoxMeasuredTemperature;
     wxCheckBox* checkBoxMucusAppearanceClear;
     wxStaticText* changesMucusFeeling;
     wxStaticText* textCoitusRecordCounter;
     wxStaticText* textDate;
     wxStaticText* staticSpotting;
     wxCheckBox* checkBoxMenstruation1;
     wxComboBox* comboBoxMucusFeeling;
     wxPanel* panelMain;
     wxCheckBox* checkBoxMucusAppearanceTacky;
     wxButton* buttonClose;
     wxStaticText* changesSexMorning;
     wxCheckBox* checkBoxMucusAmount1;
     wxCheckBox* checkBoxSexEvening;
     wxStaticText* changesMenstruation;
     wxStaticText* staticSexMorning;
     wxStaticText* staticCardLocked;
     wxStaticText* staticCervixDilation;
     wxCheckBox* checkBoxMucusAppearanceStretchy;
     wxCheckBox* checkBoxBreastsTension2;
     wxStaticText* changesTemperatureDisturbances;
     wxStaticText* staticMenstruation;
     wxButton* buttonSave;
     wxStaticText* staticSpace7;
     wxStaticText* staticMucusFeeling;
     wxStaticText* changesSexEvening;
     wxButton* buttonAddNewDay;
     wxStaticText* staticCycleDay;
     wxButton* buttonPreviousDay;
     wxCheckBox* checkBoxSexMorning;
     wxStaticText* changesMucusAppearance;
     wxStaticText* staticMeasurementPlace;
     wxStaticText* changesMeasuredTemperature;
     wxStaticText* changesAdditionalTemperatureCorrection;
     wxTextCtrl* textAdditionalNotes;
     wxStaticText* staticAdditionalTemperatureCorrection;
     wxCheckBox* checkBoxOvulationPain2;
     wxCheckBox* checkBoxMenstruation2;
     //*)

protected:
     //(*Identifiers(dayFrame)
     static const long ID_staticCardNo;
     static const long ID_textCardNo;
     static const long ID_space1;
     static const long ID_space2;
     static const long ID_staticCycleDay;
     static const long ID_textCycleDay;
     static const long ID_buttonPreviousDay;
     static const long ID_buttonNextDay;
     static const long ID_staticDate;
     static const long ID_textDate;
     static const long ID_buttonAddNewDay;
     static const long ID_staticCardLocked;
     static const long ID_staticMenstruation;
     static const long ID_checkBoxMenstruation1;
     static const long ID_checkBoxMenstruation2;
     static const long ID_textCoitusRecordCounter;
     static const long ID_changesMenstruation;
     static const long ID_staticSexMorning;
     static const long ID_checkBoxSexMorning;
     static const long ID_changesSexMorning;
     static const long ID_staticSexDay;
     static const long ID_checkBoxSexDay;
     static const long ID_changesSexDay;
     static const long ID_staticSexEvening;
     static const long ID_checkBoxSexEvening;
     static const long ID_changesSexEvening;
     static const long ID_checkBoxOtherDisturbances;
     static const long ID_changesOtherDisturbances;
     static const long ID_staticMucusFeeling;
     static const long ID_comboBoxMucusFeeling;
     static const long ID_changesMucusFeeling;
     static const long ID_staticMucusAppearance;
     static const long ID_textMucusAppearance;
     static const long ID_changesMucusAppearance;
     static const long ID_checkBoxMucusAppearanceOpaque;
     static const long ID_checkBoxMucusAppearanceWhite;
     static const long ID_checkBoxMucusAppearanceYellowish;
     static const long ID_checkBoxMucusAppearanceTacky;
     static const long ID_checkBoxMucusAppearanceClear;
     static const long ID_checkBoxMucusAppearanceStretchy;
     static const long ID_checkBoxMucusAppearanceSeminalResidue;
     static const long ID_staticMucusAmount;
     static const long ID_checkBoxMucusAmount1;
     static const long ID_checkBoxMucusAmount2;
     static const long ID_checkBoxMucusAmount3;
     static const long ID_staticLengthOfStretch;
     static const long ID_checkBoxLengthOfStretch1;
     static const long ID_checkBoxLengthOfStretch2;
     static const long ID_checkBoxLengthOfStretch3;
     static const long ID_staticMeasuredTemperature;
     static const long ID_comboBoxMeasuredTemperature;
     static const long ID_changesMeasuredTemperature;
     static const long ID_staticMeasurementTime;
     static const long ID_comboBoxMeasurementTimeHour;
     static const long ID_comboBoxMeasurementTimeMinute;
     static const long ID_changesMeasuredTime;
     static const long ID_staticMeasurementPlace;
     static const long ID_comboBoxMeasurementPlace;
     static const long ID_changesMeasuredPlace;
     static const long ID_checkBoxTemperatureDisturbances;
     static const long ID_changesTemperatureDisturbances;
     static const long ID_staticAdditionalTemperatureCorrection;
     static const long ID_comboBoxAdditionalTemperatureCorrection;
     static const long ID_changesAdditionalTemperatureCorrection;
     static const long ID_staticTemperatureAfterCorections;
     static const long ID_textTemperatureAfterCorections;
     static const long ID_space3;
     static const long ID_staticCervixPosition;
     static const long ID_comboBoxCervixPosition;
     static const long ID_changesCervixPosition;
     static const long ID_staticCervixDilation;
     static const long ID_comboBoxCervixDilation;
     static const long ID_changesCervixDilation;
     static const long ID_staticCervixHardness;
     static const long ID_comboBoxCervixHardness;
     static const long ID_changesCervixHardness;
     static const long ID_staticOvulationPain;
     static const long ID_checkBoxOvulationPain1;
     static const long ID_checkBoxOvulationPain2;
     static const long ID_changesOvulationPain;
     static const long ID_staticBreastsTension;
     static const long ID_checkBoxBreastsTension1;
     static const long ID_checkBoxBreastsTension2;
     static const long ID_changesBreastsTension;
     static const long ID_staticSpotting;
     static const long ID_checkBoxSpotting1;
     static const long ID_checkBoxSpotting2;
     static const long ID_changesSpotting;
     static const long ID_staticAdditionalNotes;
     static const long ID_changesAdditionalNotes;
     static const long ID_textAdditionalNotes;
     static const long ID_buttonSave;
     static const long ID_buttonCancel;
     static const long ID_staticSpace7;
     static const long ID_buttonClose;
     static const long ID_panelMain;
     //*)

private:
     //(*Handlers(dayFrame)
     void dayFrameClose( wxCloseEvent& event );
     void buttonSaveClick( wxCommandEvent& event );
     void buttonCancelClick( wxCommandEvent& event );
     void buttonCloseClick( wxCommandEvent& event );
     void buttonPreviousDayClick( wxCommandEvent& event );
     void buttonNextDayClick( wxCommandEvent& event );
     void buttonAddNewDayClick( wxCommandEvent& event );
     void checkBoxMenstruation1Click( wxCommandEvent& event );
     void checkBoxMenstruation2Click( wxCommandEvent& event );
     void checkBoxSexMorningClick( wxCommandEvent& event );
     void checkBoxSexDayClick( wxCommandEvent& event );
     void checkBoxSexEveningClick( wxCommandEvent& event );
     void checkBoxOtherDisturbancesClick( wxCommandEvent& event );
     void comboBoxMucusFeelingUpdated( wxCommandEvent& event );
     void checkBoxMucusAppearanceClick( wxCommandEvent& event );
     void checkBoxMucusAmount1Click( wxCommandEvent& event );
     void checkBoxMucusAmount2Click( wxCommandEvent& event );
     void checkBoxMucusAmount3Click( wxCommandEvent& event );
     void checkBoxLengthOfStretch1Click( wxCommandEvent& event );
     void checkBoxLengthOfStretch2Click( wxCommandEvent& event );
     void checkBoxLengthOfStretch3Click( wxCommandEvent& event );
     void comboBoxMeasuredTemperatureUpdated( wxCommandEvent& event );
     void comboBoxMeasurementTimeUpdated( wxCommandEvent& event );
     void comboBoxMeasurementPlaceUpdated( wxCommandEvent& event );
     void checkBoxTemperatureDisturbancesClick( wxCommandEvent& event );
     void comboBoxAdditionalTemperatureCorrectionUpdated( wxCommandEvent& event );
     void comboBoxCervixPositionUpdated( wxCommandEvent& event );
     void comboBoxCervixDilationUpdated( wxCommandEvent& event );
     void comboBoxCervixHardnessUpdated( wxCommandEvent& event );
     void checkBoxOvulationPain1Click( wxCommandEvent& event );
     void checkBoxOvulationPain2Click( wxCommandEvent& event );
     void checkBoxBreastsTension1Click( wxCommandEvent& event );
     void checkBoxBreastsTension2Click( wxCommandEvent& event );
     void checkBoxSpotting1Click( wxCommandEvent& event );
     void checkBoxSpotting2Click( wxCommandEvent& event );
     void textAdditionalNotesUpdated( wxCommandEvent& event );
     //*)

private:
     void buildGui(wxWindow* parent);
     DECLARE_EVENT_TABLE()

     // My methods
public:
     void updateMeasuredTemperatureList();
     void setButtonsStyle();
     void update();
     bool checkIfDataHasBeenChanged( bool cancelAllowed );

private:
     void updateTemperatureAfterCorectionsValue();
     void updateButtonsState();
     int calculateMucusAppearance();
     bool save();
     void sendDataUpdateEvent( int id, wxString message );

     // My variables
private:
     wxWindow *m_parent;
     configClass *m_config;
     cycleDataClass *m_cycleData;
     utilClass m_util;

     int m_changes;
     int m_newSexualRelations;
     wxString m_none;
     bool m_textAdditionalNotesEventProcessing;
     int m_temperatureAfterCorections;
};

#endif
