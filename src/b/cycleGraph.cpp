#include "cycleGraph.h"

//(*InternalHeaders(cycleGraph)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(cycleGraph)
//*)

BEGIN_EVENT_TABLE(cycleGraph,wxDialog)
	//(*EventTable(cycleGraph)
	//*)
END_EVENT_TABLE()

cycleGraph::cycleGraph(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(cycleGraph)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	//*)
}

cycleGraph::~cycleGraph()
{
	//(*Destroy(cycleGraph)
	//*)
}

