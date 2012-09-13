/*******************************************************************************
//
// Name:        cyclesLengthChart.h
// Author:      based on szybig 'histogramsFrame'
// Description:
//
*******************************************************************************/

#ifndef CYCLESLENGTHCHART_H
#define CYCLESLENGTHCHART_H

#include <chart.h>


/*******************************************************************************
********************************************************************************
*******************************************************************************/

class cyclesLengthChart : public chart
{
public:
    cyclesLengthChart(configClass *config, cycleDataClass *cycleData);
    virtual ~cyclesLengthChart();

    virtual void updateChartData();
    virtual void printChart(int, int, wxDC &dc);
protected:
private:
};

#endif // CYCLESLENGTHCHART_H
