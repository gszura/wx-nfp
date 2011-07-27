#ifndef HISTOGRAMSFRAME_H
#define HISTOGRAMSFRAME_H

//(*Headers(histogramsFrame)
#include <wx/dialog.h>
//*)

class histogramsFrame: public wxDialog
{
	public:

		histogramsFrame(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~histogramsFrame();

		//(*Declarations(histogramsFrame)
		//*)

	protected:

		//(*Identifiers(histogramsFrame)
		//*)

	private:

		//(*Handlers(histogramsFrame)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
