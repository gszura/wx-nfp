/*******************************************************************************
//
// Name:        temperaturesChart.h
// Author:      inspired by szybig 'cycleGraph'
// Description:
//
*******************************************************************************/

#ifndef TEMPERATURESCHART_H
#define TEMPERATURESCHART_H

#include <chart.h>
#include <map>
#include <wx/dynarray.h>
using namespace std;

typedef map<int, int> temperaturesMap;
WX_DECLARE_OBJARRAY(temperaturesMap, wxArrayTemperatures);

//
#define STEP 5

/*******************************************************************************
********************************************************************************
*******************************************************************************/

class temperaturesChart : public chart
{
public:
    temperaturesChart(configClass *config, cycleDataClass *cycleData);
    virtual ~temperaturesChart();

    virtual void updateChartData();
    virtual void printChart(int, int, wxDC&);

protected:
private:
    void initData();
    int getNumberOfDaysInLongestNormalCycle();
    void drawTemperaturesLegend(wxDC&);
    void drawTemperaturesMatrix(wxDC&);


    wxArrayTemperatures m_data; // m_data[day][temperature] = count;
    wxArrayString m_points;
    int m_minTemp;
    int m_maxTemp;
    int m_daysCount;
    int m_tempPointsCount;
    int m_maxCount;

    /*
    vector< vector<int> > items;
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
    */
};

#endif // TEMPERATURESCHART_H
