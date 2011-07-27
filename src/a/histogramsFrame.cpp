#include "histogramsFrame.h"
#include <iostream>
using namespace std;

BEGIN_EVENT_TABLE( histogramsFrame, wxDialog )
    EVT_PAINT( histogramsFrame::OnPaint )
END_EVENT_TABLE()

BEGIN_EVENT_TABLE( cycleGraph, wxDialog )
    EVT_PAINT( cycleGraph::OnPaint )
END_EVENT_TABLE()



histogramsFrame::histogramsFrame( wxWindow* parent, cycleDataClass *cycles ) {
    Create( parent, wxID_ANY, _( "Histogram" ), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T( "wxID_ANY" ) );
    boxSizer = new wxBoxSizer( wxVERTICAL );
    boxSizer->SetMinSize( 500, 500 );

    buttons = CreateStdDialogButtonSizer( wxOK );
    boxSizer->AddSpacer( 475 );
    boxSizer->Add( buttons, 0, wxRIGHT );
    SetSizerAndFit( boxSizer );

    initData(cycles, &items);

    maxValue = -1;
    for (int i = 0; i < items.size(); i++)
        if (items[i].quantity > maxValue)
            maxValue = items[i].quantity;
}


void histogramsFrame::OnPaint( wxPaintEvent& event ){
    wxPaintDC dc( this );

    wxCoord width;
    wxCoord height;
    dc.GetSize( &width, &height );
    margin = 20;
    bottomMargin = 50;
    textH = 15;
    space = 20;
    OXlength = width - margin * 2;
    OYlength = height-margin-bottomMargin;
    blockL = ( OXlength - 15 ) / items.size() - space;
    blockH = ( OYlength - 15 ) / ( maxValue ? maxValue : 1 );
    startY = height - bottomMargin;
    startX = margin;

    // axis
    dc.DrawLine( startX, startY, startX, startY - OYlength ); // OY
    dc.DrawLine( startX, startY, startX+OXlength, startY ); // OX
    // comment to axis
    wxString str;
    str = _( "days" );
    dc.DrawLabel( str, wxRect( width - margin -10 , startY, margin, textH ) ,wxALIGN_RIGHT );
    str = _( "Cycles" );
    dc.DrawLabel( str, wxRect( 0, 0, 20, 10 ), wxALIGN_LEFT );


    for (int i = 0; i < items.size(); i++) {
        dc.DrawRectangle((blockL+space)*i+space+startX, startY, blockL, -(items[i].quantity*blockH));

        str = wxString::Format( wxT( "%d" ), items[i].value );
        dc.DrawLabel( str, wxRect( ( blockL + space ) * i + space + startX, startY, blockL, textH ) ,wxALIGN_CENTER );

        str = wxString::Format( wxT( "%d" ), items[i].quantity );
        dc.DrawLabel( str, wxRect( ( blockL + space ) * i + space + startX, startY - ( items[i].quantity * blockH ),
                             blockL, -textH) ,wxALIGN_CENTER );
    }
}

int histogramsFrame::initData(cycleDataClass *cycles, vector< histItem > *items){

    for(int i=1; i<=cycles->getCardsCount(); i++){
        cardEntry *card=cycles->getCard(i);
        if(!card->getCardLocked())
            continue;

        int days=card->getDaysCount();

        while(items->size()<days+1){
            histItem hhh={items->size(), 0};
            items->push_back(hhh);
        }
        ((*items)[days].quantity)++;
    }

    // remove empty element from begining
    while(!items->empty())
        if(!items->front().quantity)
            items->erase(items->begin());
        else
            break;


    // if not enough elements to draw histogram
    if(!items->size()){
        histItem hhh={28, 0};
        items->push_back(hhh);
    }
}

int histogramsFrame::getMaxValue() { return maxValue; }
vector<histItem> histogramsFrame::getHist() { return items; }

/****************************************************************************/

cycleGraph::cycleGraph( wxWindow* parent, cycleDataClass *cycles) {
    Create( parent, wxID_ANY, _( "Histogram" ), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T( "wxID_ANY" ) );
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
                    if ( items[j][tmpIdx] > maxValue ){
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
        for ( int j = 0; j < items[i].size(); j++){
            dc.SetBrush( wxBrush( wxColour( (unsigned char)( 255 - ( 255 * items[i][j] / maxValue) ),
                                            255, (unsigned char)( 255 - ( 255 * items[i][j] / maxValue)))));
            dc.DrawRectangle( leftMargin + i * width, margin + ( verticalItems - j - 1 ) * height, width, height );
        }


    wxString str1, str2;
    // OY
    for ( int i = 0; i * 5 + minTemp <= maxTemp; i+=2 ) {
        str1 = wxString::Format( wxT( "%d" ), ( i * 5 + minTemp ) / 100 );
        str2 = wxString::Format( wxT( "%d" ), ( i * 5 + minTemp ) % 100 );
        str1 = str1 + _( "," ) + str2;
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
    str1 = _("Temperature");
    dc.DrawLabel( str1, wxRect( 0, 0, 25, 10), wxALIGN_LEFT );
    str1 = _("Day");
    dc.DrawLabel( str1, wxRect( X-rightMargin-25, margin+verticalItems*height+15, 25, 10 ), wxALIGN_RIGHT );
}


int cycleGraph::initData(cycleDataClass *cycles, vector< vector<int> > *hist,
                         int *minTemp, int *maxTemp, int *maxDays){

    *minTemp = 9999;
    *maxTemp = 0;
    *maxDays = 0;

    if( cycles == NULL || hist == NULL)
           return -1;
    if( !hist->empty() )
        hist->clear();

    for( int i = 1; i <= cycles->getCardsCount(); i++ ){
        cardEntry *card = cycles->getCard(i);
        hist->push_back( std::vector<int>() );

        int days = card->getDaysCount();
        if( days > *maxDays )
            *maxDays = days;

        for( int day=1; day<=days; day++ ){
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

int cycleGraph::getMaxTemp() { return maxTemp; }
int cycleGraph::getMinTemp() { return minTemp; }
int cycleGraph::getMaxValue() { return maxValue; }
int cycleGraph::getDays() { return days; }
vector<int> cycleGraph::getDaysTemperatures(int nDay) {
    nDay--;
    if(nDay < 0 || nDay >= days){
        vector<int> empty(0, 0);
        return empty;
    } else {
        return items[nDay];
    }
}

