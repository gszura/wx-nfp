#include "histogramsFrame.h"

//(*InternalHeaders(histogramsFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(histogramsFrame)
//*)

BEGIN_EVENT_TABLE(histogramsFrame,wxDialog)
	//(*EventTable(histogramsFrame)
	//*)
END_EVENT_TABLE()

histogramsFrame::histogramsFrame(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(histogramsFrame)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	//*)
}

histogramsFrame::~histogramsFrame()
{
	//(*Destroy(histogramsFrame)
	//*)
}

