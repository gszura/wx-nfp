/*******************************************************************************
//
// Name:        statisticsFrame.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "statisticsFrame.h"
#include "phasesChart.h"
#include "lutealPhasesChart.h"
#include "cyclesLengthChart.h"
#include "temperaturesChart.h"

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(wxArrayChart);


//(*InternalHeaders(statisticsFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)


//(*IdInit(statisticsFrame)
const long statisticsFrame::ID_listBoxChartList = wxNewId();
const long statisticsFrame::ID_buttonClose = wxNewId();
const long statisticsFrame::ID_chartWindow = wxNewId();
const long statisticsFrame::ID_chartPanel = wxNewId();
//*)

/*******************************************************************************
********************************************************************************
*******************************************************************************/

BEGIN_EVENT_TABLE(statisticsFrame,wxFrame)
    //(*EventTable(statisticsFrame)
    //*)
END_EVENT_TABLE()

/*******************************************************************************
********************************************************************************
*******************************************************************************/

statisticsFrame::statisticsFrame(wxWindow* parent, configClass *config, cycleDataClass *cycleData, int visibleChartIndex, wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    /** Update when you add new chart */
    m_charts.Add(new chart(config, cycleData));
    m_charts.Add(new phasesChart(config, cycleData));
    m_charts.Add(new lutealPhasesChart(config, cycleData));
    m_charts.Add(new cyclesLengthChart(config, cycleData));
    m_charts.Add(new temperaturesChart(config, cycleData));

    m_parent = parent;
    m_config = config;
    m_cycleData = cycleData;

    buildGui(parent);

    addAvailableChartsToTheList();

    if (visibleChartIndex > 0)
        listBoxChartList->SetSelection(visibleChartIndex-1);
    chartWindow->setChart(getChart(visibleChartIndex));
    chartWindow->Refresh();
}

/**
 * Build GUI
 */
void statisticsFrame::buildGui(wxWindow* parent)
{
    //(*Initialize(statisticsFrame)
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer1;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    chartPanel = new wxPanel(this, ID_chartPanel, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_chartPanel"));
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    listBoxChartList = new wxListBox(chartPanel, ID_listBoxChartList, wxDefaultPosition, wxSize(180,400), 0, 0, 0, wxDefaultValidator, _T("ID_listBoxChartList"));
    listBoxChartList->SetMinSize(wxSize(150,400));
    BoxSizer3->Add(listBoxChartList, 1, wxTOP|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    buttonClose = new wxButton(chartPanel, ID_buttonClose, _("Close"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_buttonClose"));
    BoxSizer3->Add(buttonClose, 0, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer4 = new wxBoxSizer(wxVERTICAL);
    chartWindow = new customChartWindow(chartPanel,m_config,m_cycleData,ID_chartWindow,wxDefaultPosition,wxSize(650,-1));
    BoxSizer4->Add(chartWindow, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    chartPanel->SetSizer(BoxSizer2);
    BoxSizer2->Fit(chartPanel);
    BoxSizer2->SetSizeHints(chartPanel);
    BoxSizer1->Add(chartPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_listBoxChartList,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&statisticsFrame::listBoxChartListSelect);
    Connect(ID_listBoxChartList,wxEVT_COMMAND_LISTBOX_DOUBLECLICKED,(wxObjectEventFunction)&statisticsFrame::listBoxChartListDClick);
    Connect(ID_buttonClose,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&statisticsFrame::buttonCloseClick);
    Connect(wxEVT_SIZE,(wxObjectEventFunction)&statisticsFrame::resize);
    //*)
}

statisticsFrame::~statisticsFrame()
{
    //(*Destroy(statisticsFrame)
    //*)
}

/******************************************************************************/

int statisticsFrame::getChartsCount()
{
    return m_charts.GetCount();
}

wxString statisticsFrame::getChartName(int index)
{
    return m_charts.Item(index)->getName();
}

chart * statisticsFrame::getChart(int index)
{
    return m_charts.Item(index);
}


/******************************************************************************/

void statisticsFrame::buttonCloseClick(wxCommandEvent& event)
{
    Close();
}

void statisticsFrame::listBoxChartListSelect(wxCommandEvent& event)
{
    wxString msg = wxEmptyString;
    int chartToDisplay = listBoxChartList->GetSelection();

    if ( chartToDisplay == wxNOT_FOUND ) {
        chartToDisplay = 0;
    } else {
        chartToDisplay++;
    }

    chartWindow->setChart( getChart(chartToDisplay) );
    chartWindow->Refresh();
}

void statisticsFrame::listBoxChartListDClick(wxCommandEvent& event)
{
    wxString msg = wxEmptyString;
    int chartToDisplay = listBoxChartList->GetSelection();

    if ( chartToDisplay == wxNOT_FOUND ) {
        chartToDisplay = 0;
    } else {
        chartToDisplay++;
    }

    chartWindow->setChart( getChart(chartToDisplay), true );
    chartWindow->Refresh();
}

void statisticsFrame::addAvailableChartsToTheList()
{
    for (int i=1; i<getChartsCount(); i++) {
        listBoxChartList->Append(getChartName(i));
    }
}

/******************************************************************************/

void statisticsFrame::resize(wxSizeEvent& event)
{
    chartWindow->Refresh();
    event.Skip();
}

