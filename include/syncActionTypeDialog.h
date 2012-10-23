#ifndef SYNCACTIONTYPEDIALOG_H
#define SYNCACTIONTYPEDIALOG_H

//(*Headers(syncActionTypeDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/hyperlink.h>
#include <wx/panel.h>
#include <wx/stattext.h>
//*)

#define SYNC_CANCEL             0
#define SYNC_READ_EXISTING_CARD 1
#define SYNC_CREATE_NEW_CARD    2

class syncActionTypeDialog: public wxDialog
{
public:

    syncActionTypeDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~syncActionTypeDialog();

    //(*Declarations(syncActionTypeDialog)
    wxPanel* Panel1;
    wxButton* buttonCreateNewCard;
    wxStaticText* StaticText1;
    wxButton* buttonReadExistingCard;
    wxButton* buttonCancel;
    wxHyperlinkCtrl* hyperlinkCtrl;
    //*)

protected:

    //(*Identifiers(syncActionTypeDialog)
    static const long ID_STATICTEXT1;
    static const long ID_HYPERLINKCTRL;
    static const long ID_buttonReadExistingCard;
    static const long ID_buttonCreateNewCard;
    static const long ID_PANEL1;
    //*)

private:

    //(*Handlers(syncActionTypeDialog)
    void OnbuttonReadExistingCardClick(wxCommandEvent& event);
    void OnbuttonCreateNewCardClick(wxCommandEvent& event);
    void OnbuttonCancelClick(wxCommandEvent& event);
    //*)

    DECLARE_EVENT_TABLE()
};

#endif
