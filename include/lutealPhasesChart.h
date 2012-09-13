/*******************************************************************************
//
// Name:        lutealPhasesChart.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef LUTEALPHASESCHART_H
#define LUTEALPHASESCHART_H

#include <chart.h>


/*******************************************************************************
********************************************************************************
*******************************************************************************/

class lutealPhasesChart : public chart
{
public:
    lutealPhasesChart(configClass *config, cycleDataClass *cycleData);
    virtual ~lutealPhasesChart();

    virtual void updateChartData();
    virtual void printChart(int, int, wxDC &dc);
protected:
private:
};

#endif // LUTEALPHASESCHART_H
