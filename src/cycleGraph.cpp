#include "cycleGraph.h"
#include <iostream>
using namespace std;

//(*InternalHeaders(cycleGraph)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(cycleGraph)
//*)

BEGIN_EVENT_TABLE( cycleGraph, wxDialog )
    EVT_PAINT( cycleGraph::OnPaint )
END_EVENT_TABLE()

cycleGraph::cycleGraph( wxWindow* parent, cycleDataClass *cycles) {
    Create( parent, wxID_ANY, _( "Temperature in cycles" ), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T( "wxID_ANY" ) );
    boxSizer = new wxBoxSizer( wxVERTICAL );
    X = 600;
    Y = 600;
    boxSizer->SetMinSize( X, Y );

    buttons = CreateStdDialogButtonSizer( wxOK );
    boxSizer->AddSpacer( Y - 25 );
    boxSizer->Add( buttons, 0, wxRIGHT );
    SetSizerAndFit( boxSizer );


    vector< vector<int> > hist;
    int minTemperature;
    int maxTemperature;
    int maxDays;
    initData(cycles, &hist, &minTemperature, &maxTemperature, &maxDays);


    days = maxDays;

    oYlabelsOffset = 7;
    step = 5;
    maxValue = 0;

    if( minTemperature > 4500 || maxTemperature < 3000 ) {
        minTemp = 3640;
        maxTemp = 3670;
        maxValue = 1;
        if ( maxDays <= 0 )
            maxDays = 28;
    } else {
        minTemp = minTemperature;
        maxTemp = maxTemperature;
    }

    while ( minTemp % step )
        minTemp--;
    maxTemp++;
    while ( maxTemp % step )
        maxTemp++;
    verticalItems = ( maxTemp - minTemp ) / step;
    days = maxDays;


    int tmpIdx;
    items.resize(maxDays, vector<int>( verticalItems, 0 ) );
    if ( maxDays )
        for ( int i = 0; i < hist.size(); i++ )
            for ( int j = 0; j < hist[i].size(); j++ )
                if ( hist[i][j] > 2000 ) {
                    tmpIdx = ( hist[i][j] - minTemp ) / step;
                    items[j][tmpIdx]++;
                    if ( items[j][tmpIdx] > maxValue ) {
                        maxValue = items[j][tmpIdx];
                    }
                }

    margin = 20;
    leftMargin = 40;
    rightMargin = 55;

    width = ( X - rightMargin - leftMargin ) / maxDays;
    height = ( Y - 20 - margin * 2 ) / verticalItems;
}


void cycleGraph::OnPaint( wxPaintEvent& event ) {
    wxPaintDC dc( this );

    // rectangles
    for ( int i = 0; i < items.size(); i++ )
        for ( int j = 0; j < items[i].size(); j++) {
            dc.SetBrush( wxBrush( wxColour( (unsigned char)( 255 - ( 255 * items[i][j] / maxValue) ),
                                            255, (unsigned char)( 255 - ( 255 * items[i][j] / maxValue)))));
            dc.DrawRectangle( leftMargin + i * width, margin + ( verticalItems - j - 1 ) * height, width, height );
        }


    wxString str1, str2;
    // OY
    for ( int i = 0; i * 5 + minTemp <= maxTemp; i+=2 ) {
        str1 = wxString::Format( wxT( "%d" ), ( i * 5 + minTemp ) / 100 );
        str2 = wxString::Format( wxT( "%d" ), ( i * 5 + minTemp ) % 100 );
        str1 = str1 + wxT( "," ) + str2;
        dc.DrawLabel( str1, wxRect( 10, margin + ( verticalItems - i ) * height - oYlabelsOffset, 15, 10 ), wxALIGN_CENTER );
    }

    // OX
    str1 = wxString::Format( wxT( "%d" ), 1 );
    dc.DrawLabel( str1, wxRect( leftMargin, margin + verticalItems * height, width, 15), wxALIGN_CENTER );
    for ( int i = 5; i <= days; i+=5) {
        str1 = wxString::Format( wxT( "%d" ), i );
        dc.DrawLabel( str1, wxRect( leftMargin + (i - 1) * width, margin + verticalItems * height, width, 15), wxALIGN_CENTER );
    }

    // legend
    int H = ( Y - 20 - margin * 6 ) / ( maxValue + 1 );
    for ( int i = 0; i <= maxValue; i++ ) {
        dc.SetBrush( wxBrush( wxColour( (unsigned char)( 255 - ( 255 * i / maxValue ) ),
                                        255, (unsigned char)( 255 - ( 255 * i / maxValue )))));
        dc.DrawRectangle( X - rightMargin + 22, -margin + verticalItems * height - H * i, 20, -H);
    }
    str1 = _( "0 times" );
    str2 = wxString::Format( wxT( "%d" ), maxValue );
    str2 = str2 + _( " times" );
    dc.DrawLabel( str1, wxRect( X - rightMargin, verticalItems * height, rightMargin, 10 ), wxALIGN_CENTER);
    dc.DrawLabel( str2, wxRect( X - rightMargin, margin, rightMargin, 10), wxALIGN_CENTER );

    // comment to axis
    str1 = _("temperature");
    dc.DrawLabel( str1, wxRect( 0, 0, 25, 10), wxALIGN_LEFT );
    str1 = _("day");
    dc.DrawLabel( str1, wxRect( X-rightMargin-25, margin+verticalItems*height+15, 25, 10 ), wxALIGN_RIGHT );
}


int cycleGraph::initData(cycleDataClass *cycles, vector< vector<int> > *hist,
                         int *minTemp, int *maxTemp, int *maxDays) {

    *minTemp = 9999;
    *maxTemp = 0;
    *maxDays = 0;

    if( cycles == NULL || hist == NULL)
        return -1;
    if( !hist->empty() )
        hist->clear();

    for( int i = 1; i <= cycles->getCardsCount(); i++ ) {
        cardEntry *card = cycles->getCard(i);
        hist->push_back( std::vector<int>() );

        int days = card->getDaysCount();
        if( days > *maxDays )
            *maxDays = days;

        for( int day=1; day<=days; day++ ) {
            int temper = card->getDay(day)->getTemperatureMeasuredValue();
            if( temper > *maxTemp )
                *maxTemp = temper;
            if(temper < *minTemp && temper > 2000)
                *minTemp = temper;
            (*hist)[i-1].push_back( temper );
        }
    }

    return 0;
}

int cycleGraph::getMaxTemp() {
    return maxTemp;
}
int cycleGraph::getMinTemp() {
    return minTemp;
}
int cycleGraph::getMaxValue() {
    return maxValue;
}
int cycleGraph::getDays() {
    return days;
}
vector<int> cycleGraph::getDaysTemperatures(int nDay) {
    nDay--;
    if(nDay < 0 || nDay >= days) {
        vector<int> empty(0, 0);
        return empty;
    } else {
        return items[nDay];
    }
}
