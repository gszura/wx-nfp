#ifndef CYCLEGRAPH_H
#define CYCLEGRAPH_H

//(*Headers(cycleGraph)
#include <wx/dialog.h>
//*)

class cycleGraph: public wxDialog
{
	public:

		cycleGraph(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~cycleGraph();

		//(*Declarations(cycleGraph)
		//*)

	protected:

		//(*Identifiers(cycleGraph)
		//*)

	private:

		//(*Handlers(cycleGraph)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
