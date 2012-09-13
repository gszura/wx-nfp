/*******************************************************************************
//
// Name:        statisticsFrame.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef STATISTICSFRAME_H
#define STATISTICSFRAME_H

//(*Headers(statisticsFrame)
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/listbox.h>
//*)

#include <wx/dynarray.h>
#include "customChartWindow.h"
#include "configClass.h"
#include "cyclesData.h"
#include "utilClass.h"
#include "chart.h"

WX_DECLARE_OBJARRAY(chart*, wxArrayChart);

/*******************************************************************************
********************************************************************************
*******************************************************************************/

class statisticsFrame: public wxFrame
{
public:

    statisticsFrame(wxWindow* parent, configClass *config, cycleDataClass *cycleData, int visibleChartIndex, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~statisticsFrame();

    int getChartsCount();
    wxString getChartName(int);
    chart * getChart(int);


    //(*Declarations(statisticsFrame)
    wxPanel* chartPanel;
    wxButton* buttonClose;
    wxListBox* listBoxChartList;
    customChartWindow* chartWindow;
    //*)

protected:

    //(*Identifiers(statisticsFrame)
    static const long ID_listBoxChartList;
    static const long ID_buttonClose;
    static const long ID_chartWindow;
    static const long ID_chartPanel;
    //*)

private:

    //(*Handlers(statisticsFrame)
    void buttonCloseClick(wxCommandEvent& event);
    void listBoxChartListSelect(wxCommandEvent& event);
    void resize(wxSizeEvent& event);
    void listBoxChartListDClick(wxCommandEvent& event);
    //*)

    DECLARE_EVENT_TABLE()

    void buildGui(wxWindow* parent);
    void addAvailableChartsToTheList();

    configClass *m_config;
    cycleDataClass *m_cycleData;
    wxArrayChart m_charts;
};

#endif
