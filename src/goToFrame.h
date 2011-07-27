/***************************************************************
 * Name:      goToFrame.h
 * Purpose:   Dialog for choosing the card to open - header file
 * Author:    Grzegorz Szura (grzegorz@szura.net)
 * Created:   2010-03-09
 * Copyright: Grzegorz Szura (http://www.szura.net)
 * License:
 **************************************************************/

#ifndef GOTOFRAME_H
#define GOTOFRAME_H

//(*Headers(goToFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/datectrl.h>
#include <wx/spinctrl.h>
#include <wx/radiobut.h>
#include <wx/panel.h>
#include <wx/dateevt.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

/******************************************************************************/

#include "configClass.h"
#include "cyclesData.h"
#include "utilClass.h"

#define GOTO_CARD  1
#define GOTO_DAY   2


/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
class goToFrame: public wxDialog {
public:
     goToFrame(wxWindow* parent,configClass *config, cycleDataClass *cycleData, int focusIn, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
     virtual ~goToFrame();

     //(*Declarations(goToFrame)
     wxDatePickerCtrl* datePickerDate;
     wxPanel* panel1;
     wxButton* buttonCancel;
     wxStaticText* staticVaildDates;
     wxButton* buttonGoTo;
     wxStaticText* space1;
     wxRadioButton* radioButtonCardNumber;
     wxStaticText* staticDay;
     wxStaticText* textCard;
     wxStaticText* staticDate;
     wxRadioButton* radioButtonDate;
     wxStaticText* textDate;
     wxSpinCtrl* spinCardNumber;
     wxStaticText* staticCard;
     wxStaticText* textDay;
     //*)

protected:
     //(*Identifiers(goToFrame)
     static const long ID_radioButtonCardNumber;
     static const long ID_spinCardNumber;
     static const long ID_radioButtonDate;
     static const long ID_datePickerDate;
     static const long ID_space1;
     static const long ID_staticVaildDates;
     static const long ID_staticCard;
     static const long ID_textCard;
     static const long ID_staticDay;
     static const long ID_textDay;
     static const long ID_staticDate;
     static const long ID_textDate;
     static const long ID_buttonGoTo;
     static const long ID_buttonCancel;
     static const long ID_panel1;
     //*)

private:
     //(*Handlers(goToFrame)
     void goToFrameClose(wxCloseEvent& event);
     void buttonGoToClick(wxCommandEvent& event);
     void buttonCancelClick(wxCommandEvent& event);
     void radioButtonCardNumberClick(wxCommandEvent& event);
     void spinCardNumberChange(wxSpinEvent& event);
     void radioButtonDateClick(wxCommandEvent& event);
     void datePickerDateDateChanged(wxDateEvent& event );
     //*)

protected:

private:
     void buildGui(wxWindow* parent);
     DECLARE_EVENT_TABLE()

     // My methods
public:

private:
     void updateInfo();
     int findCard(wxDateTime);
     int findDay(wxDateTime, int);

     // My variables
private:
     configClass *m_config;
     cycleDataClass *m_cycleData;
     utilClass m_util;

};

#endif
