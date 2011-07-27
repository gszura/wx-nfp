#include "histogramsFrame.h"

//(*InternalHeaders(histogramsFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <iostream>
using namespace std;

//(*IdInit(histogramsFrame)
//*)

BEGIN_EVENT_TABLE( histogramsFrame, wxDialog )
    EVT_PAINT( histogramsFrame::OnPaint )
END_EVENT_TABLE()


histogramsFrame::histogramsFrame( wxWindow* parent, cycleDataClass *cycles ) {
    Create( parent, wxID_ANY, _( "Length of cycles" ), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T( "wxID_ANY" ) );
    boxSizer = new wxBoxSizer( wxVERTICAL );
    boxSizer->SetMinSize( 500, 500 );

    buttons = CreateStdDialogButtonSizer( wxOK );
    boxSizer->AddSpacer( 475 );
    boxSizer->Add( buttons, 0, wxRIGHT );
    SetSizerAndFit( boxSizer );

    initData(cycles, &items);

    maxValue = -1;
    for (size_t i = 0; i < items.size(); i++)
        if (items[i].quantity > maxValue)
            maxValue = items[i].quantity;
}


void histogramsFrame::OnPaint( wxPaintEvent& event ) {
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
    str = _( "cycles" );
    dc.DrawLabel( str, wxRect( 0, 0, 20, 10 ), wxALIGN_LEFT );


    for (size_t i = 0; i < items.size(); i++) {
        dc.DrawRectangle((blockL+space)*i+space+startX, startY, blockL, -(items[i].quantity*blockH));

        str = wxString::Format( wxT( "%d" ), items[i].value );
        dc.DrawLabel( str, wxRect( ( blockL + space ) * i + space + startX, startY, blockL, textH ) ,wxALIGN_CENTER );

        str = wxString::Format( wxT( "%d" ), items[i].quantity );
        dc.DrawLabel( str, wxRect( ( blockL + space ) * i + space + startX, startY - ( items[i].quantity * blockH ),
                                   blockL, -textH) ,wxALIGN_CENTER );
    }
}

int histogramsFrame::initData(cycleDataClass *cycles, vector< histItem > *items) {

    for(int i=1; i<=cycles->getCardsCount(); i++) {
        cardEntry *card=cycles->getCard(i);
        if(!card->getCardLocked())
            continue;

        int days=card->getDaysCount();

        while(items->size()<days+1) {
            histItem hhh= {items->size(), 0};
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
    if(!items->size()) {
        histItem hhh= {28, 0};
        items->push_back(hhh);
    }
}

int histogramsFrame::getMaxValue() {
    return maxValue;
}
vector<histItem> histogramsFrame::getHist() {
    return items;
}
