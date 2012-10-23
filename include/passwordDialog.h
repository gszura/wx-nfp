/*******************************************************************************
//
// Name:        passwordDialog.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef passwordDialog_H
#define passwordDialog_H

#include "configClass.h"

//(*Headers(passwordDialog)
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/hyperlink.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class passwordDialog: public wxDialog
{
public:

    passwordDialog(wxWindow* parent, configClass *config, bool fileAlreadyStoredOnServer, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~passwordDialog();

    //(*Declarations(passwordDialog)
    wxPanel* Panel1;
    wxButton* buttonOk;
    wxStaticText* staticInfo;
    wxCheckBox* checkBoxRemember;
    wxStaticText* StaticText3;
    wxButton* buttonCancel;
    wxStaticText* StaticText2;
    wxHyperlinkCtrl* hyperlinkCtrl;
    wxTextCtrl* textPassword;
    //*)

protected:

    //(*Identifiers(passwordDialog)
    static const long ID_staticInfo;
    static const long ID_textPassword;
    static const long ID_STATICTEXT3;
    static const long ID_checkBoxRemember;
    static const long ID_STATICTEXT2;
    static const long ID_HYPERLINKCTRL;
    static const long ID_PANEL1;
    //*)

private:

    //(*Handlers(passwordDialog)
    void OnbuttonCancelClick(wxCommandEvent& event);
    void OnbuttonOkClick(wxCommandEvent& event);
    //*)

    DECLARE_EVENT_TABLE()

    wxWindow *m_parent;
    configClass *m_config;
};

#endif
