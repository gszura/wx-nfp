/***************************************************************
 * Name:      cardFrame.h
 * Purpose:   Dialog for editing card's data - header file
 * Author:    Grzegorz Szura (grzegorz@szura.net)
 * Created:   2010-03-02
 * Copyright: Grzegorz Szura (http://www.szura.net)
 * License:
 **************************************************************/

#ifndef __CARD_FRAME__
#define __CARD_FRAME__

//(*Headers(cardFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/datectrl.h>
#include <wx/panel.h>
#include <wx/dateevt.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/combobox.h>
//*)

#include "configClass.h"
#include "cyclesData.h"
#include "utilClass.h"

/******************************************************************************/

#define ACTIVE_CARD_UPDATE              11
#define ACTIVE_CARD_UPDATE_WITH_TEMP    12
#define ACTIVE_CARD_UPDATE_WITH_PLACES  13
#define ACTIVE_CARD_UPDATE_WITH_1ST_DAY 14

extern const wxEventType wxEVT_CARD_DATA_MODIFIED_EVENT;

enum {
     CARD_EVENT
};

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
class cardFrame: public wxDialog {
public:
     cardFrame(wxWindow* parent,configClass *config, cycleDataClass *cycleData, wxWindowID id=wxID_ANY);
     virtual ~cardFrame();

     //(*Declarations(cardFrame)
     wxStaticText* changesBirthdayDay;
     wxStaticText* changesTempCorrectionMouth;
     wxButton* buttonCancel;
     wxStaticText* textCardNo;
     wxComboBox* comboBoxTempCorrectionTime;
     wxComboBox* comboBoxTempCorrectionVagina;
     wxStaticText* changesTempPlace;
     wxStaticText* changes1stDayOfCycle;
     wxStaticText* staticTempTime;
     wxStaticText* changesTempCorrectionRectum;
     wxComboBox* comboBoxTempPlace;
     wxStaticText* changesTempCorrectionVagina;
     wxStaticText* staticCardNo;
     wxStaticText* staticTempCorrectionRectum;
     wxComboBox* comboBoxTempTimeMinute;
     wxStaticText* changesTempTime;
     wxDatePickerCtrl* datePickerBirthdayDay;
     wxStaticText* changesNotes;
     wxTextCtrl* textName;
     wxStaticText* staticTempCorrection;
     wxComboBox* comboBoxTempCorrectionMouth;
     wxStaticText* staticSpace5;
     wxComboBox* comboBoxTempCorrectionRectum;
     wxStaticText* staticTemp;
     wxStaticText* staticBirthdayDay;
     wxStaticText* changesName;
     wxStaticText* staticSpace1;
     wxStaticText* staticTempCorrectionMouth;
     wxStaticText* staticTempPlace;
     wxStaticText* changesTempCorrectionTime;
     wxStaticText* staticTempCorrectionTime;
     wxStaticText* staticTempCorrectionVagina;
     wxStaticText* staticSpace6;
     wxDatePickerCtrl* datePicker1stDayOfCycle;
     wxPanel* panelMain;
     wxButton* buttonClose;
     wxStaticText* staticNotes;
     wxStaticText* static1stDayOfCycle;
     wxStaticText* changesCardNo;
     wxStaticText* staticSpace3;
     wxButton* buttonSave;
     wxStaticText* staticSpace7;
     wxStaticText* staticName;
     wxStaticText* staticSpace4;
     wxComboBox* comboBoxTempTimeHour;
     wxTextCtrl* textNotes;
     wxStaticText* staticSpace2;
     //*)

protected:
     //(*Identifiers(cardFrame)
     static const long ID_staticCardNo;
     static const long ID_textCardNo;
     static const long ID_changesCardNo;
     static const long ID_static1stDayOfCycle;
     static const long ID_datePicker1stDayOfCycle;
     static const long ID_changes1stDayOfCycle;
     static const long ID_staticTemp;
     static const long ID_staticSpace1;
     static const long ID_staticTempTime;
     static const long ID_comboBoxTempTimeHour;
     static const long ID_comboBoxTempTimeMinute;
     static const long ID_changesTempTime;
     static const long ID_staticSpace2;
     static const long ID_staticTempPlace;
     static const long ID_comboBoxTempPlace;
     static const long ID_changesTempPlace;
     static const long ID_staticTempCorrection;
     static const long ID_staticSpace3;
     static const long ID_staticTempCorrectionMouth;
     static const long ID_comboBoxTempCorrectionMouth;
     static const long ID_changesTempCorrectionMouth;
     static const long ID_staticSpace4;
     static const long ID_staticTempCorrectionVagina;
     static const long ID_comboBoxTempCorrectionVagina;
     static const long ID_changesTempCorrectionVagina;
     static const long ID_staticSpace5;
     static const long ID_staticTempCorrectionRectum;
     static const long ID_comboBoxTempCorrectionRectum;
     static const long ID_changesTempCorrectionRectum;
     static const long ID_staticSpace6;
     static const long ID_staticTempCorrectionTime;
     static const long ID_comboBoxTempCorrectionTime;
     static const long ID_changesTempCorrectionTime;
     static const long ID_staticNotes;
     static const long ID_changesNotes;
     static const long ID_textNotes;
     static const long ID_staticName;
     static const long ID_textName;
     static const long ID_changesName;
     static const long ID_staticBirthdayDay;
     static const long ID_datePickerBirthdayDay;
     static const long ID_changesBirthdayDay;
     static const long ID_buttonSave;
     static const long ID_buttonCancel;
     static const long ID_staticSpace7;
     static const long ID_buttonClose;
     static const long ID_panelMain;
     //*)

private:
     //(*Handlers(cardFrame)
     void cardFrameClose(wxCloseEvent& event);
     void buttonCloseClick(wxCommandEvent& event);
     void buttonSaveClick(wxCommandEvent& event);
     void buttonCancelClick(wxCommandEvent& event);
     void cardFrameKeyDown(wxKeyEvent& event);

     void datePicker1stDayOfCycleDateChanged(wxDateEvent& event );
     void comboBoxTempTimeUpdated(wxCommandEvent& event );
     void comboBoxTempPlaceUpdated(wxCommandEvent& event );
     void comboBoxTempCorrectionMouthUpdated(wxCommandEvent& event );
     void comboBoxTempCorrectionVaginaUpdated(wxCommandEvent& event );
     void comboBoxTempCorrectionRectumUpdated(wxCommandEvent& event );
     void comboBoxTempCorrectionTimeUpdated(wxCommandEvent& event );
     void textNotesUpdated(wxCommandEvent& event);
     void textNameUpdated(wxCommandEvent& event);
     void datePickerBirthdayDayDateChanged(wxDateEvent& event );
     //*)

private:
     void buildGui(wxWindow* parent);
     DECLARE_EVENT_TABLE()

     // My methods
public:
     void setButtonsStyle();
     void update();
     bool checkIfCanExit(bool cancelAllowed);

private:
     void updateTemperatureCorrectedValues();
     void updateButtonsState();
     bool save();
     void sendDataUpdateEvent(int id, wxString message);

     // My variables
private:
     wxWindow *m_parent;
     configClass *m_config;
     cycleDataClass *m_cycleData;
     utilClass m_util;

     int m_changes;
     bool m_notesEventProcessing;
};

#endif // __CARD_FRAME__
