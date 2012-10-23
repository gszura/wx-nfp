/*******************************************************************************
//
// Name:        passwordDialog.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "passwordDialog.h"
#include "wx-nfpAppInfo.h"

//(*InternalHeaders(passwordDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(passwordDialog)
const long passwordDialog::ID_staticInfo = wxNewId();
const long passwordDialog::ID_textPassword = wxNewId();
const long passwordDialog::ID_STATICTEXT3 = wxNewId();
const long passwordDialog::ID_checkBoxRemember = wxNewId();
const long passwordDialog::ID_STATICTEXT2 = wxNewId();
const long passwordDialog::ID_HYPERLINKCTRL = wxNewId();
const long passwordDialog::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(passwordDialog,wxDialog)
    //(*EventTable(passwordDialog)
    //*)
END_EVENT_TABLE()

passwordDialog::passwordDialog(wxWindow* parent, configClass *config, bool fileAlreadyStoredOnServer, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    m_parent = parent;
    m_config = config;
    //(*Initialize(passwordDialog)
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer5;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxCAPTION, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    staticInfo = new wxStaticText(Panel1, ID_staticInfo, _("Type the password which will be used to encrypt the file:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_staticInfo"));
    BoxSizer2->Add(staticInfo, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    textPassword = new wxTextCtrl(Panel1, ID_textPassword, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD, wxDefaultValidator, _T("ID_textPassword"));
    BoxSizer2->Add(textPassword, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, wxEmptyString, wxDefaultPosition, wxSize(15,0), 0, _T("ID_STATICTEXT3"));
    BoxSizer4->Add(StaticText3, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxVERTICAL);
    checkBoxRemember = new wxCheckBox(Panel1, ID_checkBoxRemember, _("Remember permanently"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_checkBoxRemember"));
    checkBoxRemember->SetValue(false);
    BoxSizer5->Add(checkBoxRemember, 0, wxTOP|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("It\'s not recomended to save password\nif it\'s not your private computer!"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer5->Add(StaticText2, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    hyperlinkCtrl = new wxHyperlinkCtrl(Panel1, ID_HYPERLINKCTRL, _("Read more information in documentation"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_LEFT|wxNO_BORDER, _T("ID_HYPERLINKCTRL"));
    BoxSizer5->Add(hyperlinkCtrl, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4->Add(BoxSizer5, 1, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    buttonOk = new wxButton(Panel1, wxID_OK, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
    BoxSizer3->Add(buttonOk, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    buttonCancel = new wxButton(Panel1, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
    BoxSizer3->Add(buttonCancel, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer2->Add(BoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&passwordDialog::OnbuttonOkClick);
    Connect(wxID_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&passwordDialog::OnbuttonCancelClick);
    //*)

    hyperlinkCtrl->SetURL( wxString::Format( _( "%s%s?l=en" ), HOME_URL, ONLINE_DOC ) );
    if (fileAlreadyStoredOnServer) {
        staticInfo->SetLabel( _("Type the password which has been used to encrypt the file:") );
    }
    BoxSizer1->Fit(this);
    buttonOk->SetDefault();
    textPassword->SetFocus();
}

passwordDialog::~passwordDialog()
{
    //(*Destroy(passwordDialog)
    //*)
}


void passwordDialog::OnbuttonOkClick(wxCommandEvent& event)
{
    m_config->rememberPassword = checkBoxRemember->GetValue();
    m_config->password = textPassword->GetValue();
    EndModal(0);
}

void passwordDialog::OnbuttonCancelClick(wxCommandEvent& event)
{
    EndModal(-1);
}
