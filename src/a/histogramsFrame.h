#ifndef HISTOGRAMSFRAME_H
#define HISTOGRAMSFRAME_H

#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/dc.h>
#include <wx/dcclient.h>
#include "nfpMainFrame.h"
#include <vector>
using namespace std;

struct histItem{
    int value;
    int quantity;
};

class histogramsFrame: public wxDialog {
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


class cycleGraph: public wxDialog {
private:
  DECLARE_EVENT_TABLE()

private:
  wxBoxSizer *boxSizer;
  wxStdDialogButtonSizer *buttons;
  vector< vector<int> > items;
  int minTemp;
  int maxTemp;
  int height;
  int width;
  int margin;
  int leftMargin;
  int rightMargin;
  int verticalItems;
  int days;
  int step;
  int maxValue;
  int oYlabelsOffset;
  int X,Y;

 public:
  cycleGraph(wxWindow* parent, cycleDataClass *cycles);
  int getMaxTemp();
  int getMinTemp();
  /**
    * max number of temperature repetiotion through all cards
    */
  int getMaxValue();
  /**
    * Return number of days in graph.
    */
  int getDays();
  /**
    * Function return vector of temperatures at day through all cards
    *
    * nDay - number of day. 0 <= nDay < days.
    */
  vector<int> getDaysTemperatures(int nDay);

private:
  void OnPaint(wxPaintEvent& event);
  int initData(cycleDataClass *cycles, vector< vector<int> > *hist, int *minTemerature, int *maxTemperature, int *maxDays);


};

#endif

