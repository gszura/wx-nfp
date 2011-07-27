#ifndef HISTOGRAMSFRAME_H
#define HISTOGRAMSFRAME_H

//(*Headers(histogramsFrame)
#include <wx/dialog.h>
//*)

#include <wx/sizer.h>
#include <wx/dc.h>
#include <wx/dcclient.h>
#include "nfpMainFrame.h"
#include <vector>
using namespace std;

struct histItem
{
    int value;
    int quantity;
};

class histogramsFrame: public wxDialog
{
private:
    DECLARE_EVENT_TABLE()

private:
    wxBoxSizer *boxSizer;
    wxStdDialogButtonSizer *buttons;
    vector<histItem> items;
    int maxValue;
    int margin;
    int bottomMargin;
    int OXlength;
    int OYlength;
    int space;
    int blockL;
    int blockH;
    int startY;
    int startX;
    int textH;

public:
    histogramsFrame(wxWindow* parent, cycleDataClass *cycles);
    /**
      * Return max number of cycles which has the same length.
      */
    int getMaxValue();
    vector<histItem> getHist();

private:
    void OnPaint(wxPaintEvent& event);
    int initData(cycleDataClass *cycles, vector< histItem > *items);
};

#endif
