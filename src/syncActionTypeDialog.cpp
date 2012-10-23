#include "syncActionTypeDialog.h"
#include "wx-nfpAppInfo.h"

//(*InternalHeaders(syncActionTypeDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(syncActionTypeDialog)
const long syncActionTypeDialog::ID_STATICTEXT1 = wxNewId();
const long syncActionTypeDialog::ID_HYPERLINKCTRL = wxNewId();
const long syncActionTypeDialog::ID_buttonReadExistingCard = wxNewId();
const long syncActionTypeDialog::ID_buttonCreateNewCard = wxNewId();
const long syncActionTypeDialog::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(syncActionTypeDialog,wxDialog)
    //(*EventTable(syncActionTypeDialog)
    //*)
END_EVENT_TABLE()

syncActionTypeDialog::syncActionTypeDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(syncActionTypeDialog)
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer1;

    Create(parent, wxID_ANY, _("NFP - synchronizing cards\' set with server"), wxDefaultPosition, wxDefaultSize, wxCAPTION, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("If your cards\' set is already stored on the server\n(e.g. synchronization is enabled on another computer),\nselect \'read existing cards\' set\'\n\nIf your cards\' set is not yet stored on the server,\nselect \'create new cards\' set\' button."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer2->Add(StaticText1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    hyperlinkCtrl = new wxHyperlinkCtrl(Panel1, ID_HYPERLINKCTRL, _("Read more information about this feature"), wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHL_CONTEXTMENU|wxHL_ALIGN_LEFT|wxNO_BORDER, _T("ID_HYPERLINKCTRL"));
    BoxSizer2->Add(hyperlinkCtrl, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    buttonReadExistingCard = new wxButton(Panel1, ID_buttonReadExistingCard, _("read existing cards\' set"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_buttonReadExistingCard"));
    BoxSizer2->Add(buttonReadExistingCard, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    buttonCreateNewCard = new wxButton(Panel1, ID_buttonCreateNewCard, _("create new cards\' set"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_buttonCreateNewCard"));
    BoxSizer2->Add(buttonCreateNewCard, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    buttonCancel = new wxButton(Panel1, wxID_CANCEL, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
    BoxSizer2->Add(buttonCancel, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_buttonReadExistingCard,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&syncActionTypeDialog::OnbuttonReadExistingCardClick);
    Connect(ID_buttonCreateNewCard,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&syncActionTypeDialog::OnbuttonCreateNewCardClick);
    Connect(wxID_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&syncActionTypeDialog::OnbuttonCancelClick);
    //*)

    hyperlinkCtrl->SetURL( wxString::Format( _( "%s%s?l=en" ), HOME_URL, ONLINE_DOC ) );
}

syncActionTypeDialog::~syncActionTypeDialog()
{
    //(*Destroy(syncActionTypeDialog)
    //*)
}


void syncActionTypeDialog::OnbuttonReadExistingCardClick(wxCommandEvent& event)
{
    EndModal(SYNC_READ_EXISTING_CARD);
}

void syncActionTypeDialog::OnbuttonCreateNewCardClick(wxCommandEvent& event)
{
    EndModal(SYNC_CREATE_NEW_CARD);
}

void syncActionTypeDialog::OnbuttonCancelClick(wxCommandEvent& event)
{
    EndModal(SYNC_CANCEL);
}
