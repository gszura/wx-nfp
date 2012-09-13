/*******************************************************************************
//
// Name:        printFrame.cpp
// Author:      enkeli
// Description:
//
*******************************************************************************/

#ifndef __PRINTFRAME_h__
#define __PRINTFRAME_h__

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/dialog.h>
#else
#include <wx/wxprec.h>
#endif

/******************************************************************************/

#include <wx/button.h>
#include <wx/spinctrl.h>
#include <wx/radiobut.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/sizer.h>

#include "configClass.h"
#include "utilClass.h"

/******************************************************************************/
#undef printFrame_STYLE
#define printFrame_STYLE wxCAPTION | wxSYSTEM_MENU | wxSTAY_ON_TOP | wxCLOSE_BOX

/******************************************************************************/

/**
 *
 */
class printFrame : public wxDialog {
private:
     DECLARE_EVENT_TABLE();

     configClass *m_config;
     int m_activeCard;
     bool radioButtonClicked;


public:
     printFrame (wxWindow *parent, configClass *config, int firstCard, int lastCard, int activeCard, wxWindowID id = 1, const wxString &title = wxT ("NFP - goto frame"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = printFrame_STYLE);
     virtual ~printFrame();
     void buttonOkClick (wxCommandEvent& event);
     void buttonCancelClick (wxCommandEvent& event);
     void checkBoxPrintCardsClick (wxCommandEvent& event);
     void radioButtonPrintCurrentCardClick (wxCommandEvent& event);
     void radioButtonPrintAllCardsClick (wxCommandEvent& event);
     void radioButtonPrintSelectedCardsClick (wxCommandEvent& event);
     void spinFirstCardTextUpdated (wxCommandEvent& event );
     void spinLastCardTextUpdated (wxCommandEvent& event );
     void checkBoxPrintLegendClick (wxCommandEvent& event);

private:
     wxButton *buttonCancel;
     wxButton *buttonOk;
     wxBoxSizer *WxBoxSizerButtons;
     wxCheckBox *checkBoxPrintLegend;
     wxBoxSizer *WxBoxSizerPrintLegend;
     wxSpinCtrl *spinLastCard;
     wxStaticText *staticText4;
     wxSpinCtrl *spinFirstCard;
     wxRadioButton *radioButtonPrintSelectedCards;
     wxStaticText *staticText3;
     wxBoxSizer *WxBoxSizerPrintSelectedCards;
     wxRadioButton *radioButtonPrintAllCards;
     wxStaticText *staticText2;
     wxBoxSizer *WxBoxSizerPrintAllCards;
     wxRadioButton *radioButtonPrintCurrentCard;
     wxStaticText *staticText1;
     wxBoxSizer *WxBoxSizerPrintCurrentCard;
     wxCheckBox *checkBoxPrintCards;
     wxBoxSizer *WxBoxSizerPrintCards;
     wxBoxSizer *WxBoxSizerMain;

private:
     enum {
          ID_BUTTONCANCEL = 5500,
          ID_BUTTONOK,
          ID_SPINLASTCARD,
          ID_STATICTEXT4,
          ID_SPINFIRSTCARD,
          ID_RADIOBUTTONPRINTSELECTEDCARDS,
          ID_STATICTEXT3,
          ID_RADIOBUTTONPRINTALLCARDS,
          ID_STATICTEXT2,
          ID_RADIOBUTTONPRINTCURRENTCARD,
          ID_STATICTEXT1,
          ID_CHECKBOXPRINTCARDS,
          ID_CHECKBOXPRINTLEGEND,
          ////GUI Enum Control ID End
          ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
     };

private:
     void OnClose (wxCloseEvent& event);
     void CreateGUIControls();
};

/******************************************************************************/

#endif
