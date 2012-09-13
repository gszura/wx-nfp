/*******************************************************************************
//
// Name:        phasesChart.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef PHASESCHART_H
#define PHASESCHART_H

#include <chart.h>


/*******************************************************************************
********************************************************************************
*******************************************************************************/

class phasesChart : public chart
{
public:
    phasesChart(configClass *config, cycleDataClass *cycleData);
    virtual ~phasesChart();

    virtual void updateChartData();
    virtual void printChart(int, int, wxDC &dc);
protected:
private:
};

#endif // PHASESCHART_H
