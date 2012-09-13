/*******************************************************************************
//
// Name:        nfpMainFrame.cpp
// Author:      enkeli
// Description:
//
*******************************************************************************/

#include "../data/xpm/buttonNextCard_XPM.xpm"
#include "../data/xpm/buttonPrevCard_XPM.xpm"
#include "../data/xpm/wx-nfp.xpm"

#include <wx/url.h>
#include <wx/sstream.h>
#include <wx/datetime.h>
#include <wx/filename.h>
#include <wx/numdlg.h>
#include <wx/dc.h>
#include <wx/dcprint.h>
/*
#include <wx/html/helpctrl.h>
#include <wx/filesys.h>
#include "wx/fs_zip.h"
*/

#include "nfpMainFrame.h"
#include "wx-nfpAppInfo.h"
#include "goToFrame.h"
#include "configFrame.h"
#include "customPrintout.h"
#include "printFrame.h"
#include "statisticsFrame.h"


/*******************************************************************************
********************************************************************************
*******************************************************************************/

BEGIN_EVENT_TABLE( nfpMainFrame, wxFrame )
    // LIVE UPDATE
    EVT_COMMAND( THREAD_EVENT, wxEVT_NEW_APP_AVAILABLE_EVENT, nfpMainFrame::newAppAvailableEvent )
    EVT_COMMAND( THREAD_EVENT, wxEVT_NEW_APP_DOWNLOADED_EVENT, nfpMainFrame::newAppDownloadedEvent )

    // CONFIG / CARD / DAY DATA UPDATES
    EVT_COMMAND( CONFIG_EVENT, wxEVT_CONFIG_DATA_MODIFIED_EVENT, nfpMainFrame::configDataModifiedEvent )
    EVT_COMMAND( CARD_EVENT, wxEVT_CARD_DATA_MODIFIED_EVENT, nfpMainFrame::cardDataModifiedEvent )
    EVT_COMMAND( DAY_EVENT, wxEVT_DAY_DATA_MODIFIED_EVENT, nfpMainFrame::dayDataModifiedEvent )

    // GENERAL
    EVT_CLOSE( nfpMainFrame::nfpMainFrameClose )
    EVT_COMMAND_SCROLL( ID_SCROLLBARVERTICAL, nfpMainFrame::scrollBarVerticalScroll )
    EVT_TIMER( ID_TIMERMAIN, nfpMainFrame::timerMainTimer )
    EVT_TIMER( ID_TIMERNOTIFICATION, nfpMainFrame::timerNotificationTimer )

    // TOOLBAR
    EVT_MENU( ID_BUTTONPREVCARD, nfpMainFrame::prevCardClick )
    EVT_MENU( ID_BUTTONNEXTCARD, nfpMainFrame::nextCardClick )
    EVT_BUTTON( ID_BUTTONNEWDAY, nfpMainFrame::newDayClick )
    EVT_BUTTON( ID_BUTTONANALYZECYCLE, nfpMainFrame::MnuResultsAutocalculateClick )

    // MAIN MENU
    EVT_MENU_OPEN( nfpMainFrame::MnuActivated )
    EVT_MENU( ID_MNU_NEW_SET, nfpMainFrame::MnuNewSetClick )
    EVT_MENU( ID_MNU_OPEN_SET, nfpMainFrame::MnuOpenSetClick )
    EVT_MENU( ID_MNU_SAVE_SET, nfpMainFrame::MnuSaveSetClick )
    EVT_MENU( ID_MNU_SAVE_SET_AS, nfpMainFrame::MnuSaveSetAsClick )
    EVT_MENU( ID_MNU_PRINT, nfpMainFrame::MnuPrintClick )
    EVT_MENU( ID_MNU_PRINT_PREVIEW, nfpMainFrame::MnuPrintPreviewClick )
    EVT_MENU( ID_MNU_PRINT_PAGE_SETUP, nfpMainFrame::MnuPrintPageSetupClick )
    EVT_MENU( ID_MNU_OPTIONS, nfpMainFrame::MnuOptionsClick )
    EVT_MENU( ID_MNU_EXIT, nfpMainFrame::MnuExitClick )
    EVT_MENU( ID_MNU_PREVIOUS_CARD, nfpMainFrame::MnuPreviousCardClick )
    EVT_MENU( ID_MNU_NEXT_CARD, nfpMainFrame::MnuNextCardClick )
    EVT_MENU( ID_MNU_GO_TO_CARD, nfpMainFrame::MnuGoToCardClick )
    EVT_MENU( ID_MNU_EDIT_CARD, nfpMainFrame::MnuEditCardClick )
    EVT_MENU( ID_MNU_DELETE_CARD, nfpMainFrame::MnuDeleteCardClick )
    EVT_MENU( ID_MNU_CARD_LOCKED, nfpMainFrame::MnuCardLockedClick )
    EVT_MENU( ID_MNU_CARD_CORRUPTED, nfpMainFrame::MnuCardCorruptedClick )
    EVT_MENU( ID_MNU_NEW_CARD, nfpMainFrame::MnuNewCardClick )
    EVT_MENU( ID_MNU_RESULTS_AUTOCALCULATE, nfpMainFrame::MnuResultsAutocalculateClick )
    EVT_MENU( ID_MNU_RESULTS_AUTOCALCULATE_ON_CHANGE, nfpMainFrame::MnuResultsAutocalculateOnChangeClick )
    EVT_MENU( ID_MNU_RESULTS_CHANGE_SETTINGS, nfpMainFrame::MnuResultsChangeAnalysisSettingsClick )
    EVT_MENU( ID_MNU_EDIT_DAY, nfpMainFrame::MnuEditDayClick )
    EVT_MENU( ID_MNU_DELETE_DAY, nfpMainFrame::MnuDeleteDayClick )
    EVT_MENU( ID_MNU_NEW_DAY, nfpMainFrame::MnuNewDayClick )
    EVT_MENU( ID_MNU_RESULTS_MUCUS_1ST_DAY, nfpMainFrame::MnuResultsMucus1stDayClick )
    EVT_MENU( ID_MNU_RESULTS_MUCUS_1ST_DAY_FERTILE, nfpMainFrame::MnuResultsMucus1stDayFertileClick )
    EVT_MENU( ID_MNU_RESULTS_MUCUS_PEAK_DAY, nfpMainFrame::MnuResultsMucusPeakDayClick )
    EVT_MENU( ID_MNU_RESULTS_CERVIX_1ST_DAY, nfpMainFrame::MnuResultsCervix1stDayClick )
    EVT_MENU( ID_MNU_RESULTS_CERVIX_PEAK_DAY, nfpMainFrame::MnuResultsCervixPeakDayClick )
    EVT_MENU( ID_MNU_RESULTS_TEMPERATURE_1ST_DAY, nfpMainFrame::MnuResultsTemperature1stDayClick )
    EVT_MENU( ID_MNU_RESULTS_TEMPERATURE_RESET, nfpMainFrame::MnuResultsTemperatureResetClick )
    EVT_MENU( ID_MNU_RESULTS_FERTILE_PHASE_START, nfpMainFrame::MnuResultsFertilePhaseStartClick )
    EVT_MENU( ID_MNU_RESULTS_INFERTILE_PHASE_START, nfpMainFrame::MnuResultsInfertilePhaseStartClick )
    EVT_MENU( ID_MNU_MOVE_DAYS_TO_PREV_CARD, nfpMainFrame::MnuMoveDaysToPrevCardClick )
    EVT_MENU( ID_MNU_MOVE_DAYS_TO_NEXT_CARD, nfpMainFrame::MnuMoveDaysToNextCardClick )
    EVT_MENU( ID_MNU_STAT_STATICTICS, nfpMainFrame::MnuStatStatisticsClick )
    EVT_MENU( ID_MNU_HELP, nfpMainFrame::MnuHelpClick )
    EVT_MENU( ID_MNU_HOME_PAGE, nfpMainFrame::MnuHomePageClick )
    EVT_MENU( ID_MNU_REPORT_BUG, nfpMainFrame::MnuReportBugClick )
    EVT_MENU( ID_MNU_UPDATE, nfpMainFrame::MnuUpdatesClick )
    EVT_MENU( ID_MNU_ABOUT, nfpMainFrame::MnuAboutClick )


    // POPUP MENU
    EVT_CONTEXT_MENU( nfpMainFrame::OnContextMenu )


END_EVENT_TABLE()

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * constructor
 */
nfpMainFrame::nfpMainFrame( wxWindow *parent, configClass *config, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style )
    : wxFrame( parent, id, title, position, size, style )
{
    m_config = config;
    m_parent = parent;

    m_doUpdateOnExit = false;
    m_newAppSetupFile = wxEmptyString;
    m_doCheckForMissingDays = false;

    // PRINTING
    m_printData = new wxPrintData;
    m_pageSetupData = new wxPageSetupDialogData;
    m_printData->SetOrientation( wxLANDSCAPE );

    m_cycleData = new cycleDataClass();
    m_cardFrm = new cardFrame( this, m_config, m_cycleData );
    m_dayFrm = new dayFrame( this, m_config, m_cycleData );
    wxPoint pos = GetPosition();
    pos.x += 10;
    pos.y += 130;
    m_notificationFrm = new notificationFrame( this, m_config, wxEmptyString, wxALIGN_LEFT, pos, true );
    m_notificationFrm->Hide();

    CreateGUIControls();

    scrollBarVertical->SetScrollbar( 0, 5, 30, 4 );
    m_config->verticalDisplacement = 0;

    if (( m_config->openLastOpenedFile || m_config->openFileFromParams ) && !m_config->dataFileName.IsEmpty() ) {
        if ( !m_cycleData->readCardsDataFromFile( m_config->dataFileName ) ) {
            wxMessageBox( wxString::Format( _( "Error occured while reading data from file:\n" ), m_cycleData->getErrorMessages().c_str() ), _( "Error" ), wxOK | wxICON_ERROR );
            m_cycleData->createNewSet();
            m_config->dataFileName = wxEmptyString;
        }

        informUserAboutChangesInThisRelease();
    } else {
        m_cycleData->createNewSet();
        m_config->dataFileName = wxEmptyString;
    }

    m_cycleData->setActiveCard( m_cycleData->getCardsCount() );
    m_config->checkLastDayVisibility = true;
    updateAll();

    if ( m_config->dataFileName.IsEmpty() ) {
        m_cardFrm->update();
        m_cardFrm->Show();
    }

    m_dataFileNamePrev = wxEmptyString;
    m_cardModifiedPrev = false;

    timerMain->Start( 500, wxTIMER_CONTINUOUS );

    m_newAppStatusMessage = 0;

#if defined(__WXMSW__)
    // check for updates
    if ( m_config->checkForUpdates ) {
        checkForUpdates( false );
    }
#endif

    m_doCheckForMissingDays = true;

    timerNotification->Start( 5000, wxTIMER_ONE_SHOT );
}

/**
 * destructor
 */
nfpMainFrame::~nfpMainFrame()
{
    if (timerNotification->IsRunning())
        timerNotification->Stop();
    if (timerMain->IsRunning())
        timerMain->Stop();
    delete m_printData;
    delete m_pageSetupData;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * CreateGUIControls
 */
void nfpMainFrame::CreateGUIControls( void )
{
    int flatButton = 0;
    int flatToolbar = 0;
    if ( m_config->useFlatButtons ) {
        flatButton = wxNO_BORDER;
        flatToolbar = wxTB_FLAT;
    }

    /**************************************************************************/
    // SIZERS, WINDOWS
    wxBoxSizer* WxBoxSizer1 = new wxBoxSizer( wxVERTICAL );
    SetSizer( WxBoxSizer1 );
    SetAutoLayout( TRUE );

    windowTop = new customWindowTop( this, m_cardFrm, m_config, m_cycleData, ID_WINDOWTOP, wxPoint( 0, 0 ), wxSize( 800, m_config->windowTopHeight ), wxNO_FULL_REPAINT_ON_RESIZE );
    windowTop->SetBackgroundColour( wxColour( *wxWHITE ) );
    WxBoxSizer1->Add( windowTop, 0, wxGROW | wxALL, 0 );

    panelMain = new wxPanel( this, ID_PANELMAIN, wxPoint( 0, 50 ), wxSize( 800, 600 ) );
    WxBoxSizer1->Add( panelMain, 1, wxGROW | wxALL, 0 );

    wxBoxSizer* WxBoxSizer2 = new wxBoxSizer( wxHORIZONTAL );
    panelMain->SetSizer( WxBoxSizer2 );
    panelMain->SetAutoLayout( TRUE );

    windowLeft = new customWindowLeft( panelMain, m_config, m_cycleData, ID_WINDOWLEFT, wxPoint( 0, 0 ), wxSize( m_config->widowLeftWidth, 450 ), wxNO_FULL_REPAINT_ON_RESIZE );
    WxBoxSizer2->Add( windowLeft, 0, wxGROW | wxALL, 0 );

    wxBoxSizer* WxBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    WxBoxSizer2->Add( WxBoxSizer3, 1, wxGROW | wxALL, 0 );

    windowMain = new customWindowMain( panelMain, windowLeft, m_dayFrm, m_config, m_cycleData, ID_WINDOWMAIN, wxPoint( 0, 0 ), wxSize( 550, 450 ), wxNO_FULL_REPAINT_ON_RESIZE );
    WxBoxSizer3->Add( windowMain, 1, wxGROW | wxALL, 0 );

    scrollBarVertical = new wxScrollBar( panelMain, ID_SCROLLBARVERTICAL, wxPoint( 482, 0 ), wxSize( 16, 360 ), wxSB_VERTICAL, wxDefaultValidator, _T( "scrollBarVertical" ) );
    WxBoxSizer3->Add( scrollBarVertical, 0, wxGROW | wxALL, 0 );

    /**************************************************************************/
    // TOOLBAR
    toolBar = new wxToolBar( this, ID_TOOLBAR, wxPoint( 0, 0 ), wxSize( 942, 29 ), flatToolbar );

    wxBitmap buttonPrevCard_BITMAP( buttonPrevCard_XPM );
    wxBitmap buttonPrevCard_DISABLE_BITMAP( wxNullBitmap );
    toolBar->AddTool( ID_BUTTONPREVCARD, wxEmptyString, buttonPrevCard_BITMAP, buttonPrevCard_DISABLE_BITMAP, wxITEM_NORMAL, _T( "Go to the previous card" ), wxEmptyString );

    wxBitmap buttonNextCard_BITMAP( buttonNextCard_XPM );
    wxBitmap buttonNextCard_DISABLE_BITMAP( wxNullBitmap );
    toolBar->AddTool( ID_BUTTONNEXTCARD, wxEmptyString, buttonNextCard_BITMAP, buttonNextCard_DISABLE_BITMAP, wxITEM_NORMAL, _T( "Go to the next card" ), wxEmptyString );

    toolBar->AddSeparator();
    buttonNewDay = new wxButton( toolBar, ID_BUTTONNEWDAY, _( "new day" ), wxPoint( 63, 0 ), wxSize( 100, -1 ), flatButton, wxDefaultValidator, _T( "buttonNewDay" ) );
    buttonNewDay->SetToolTip( _("Add new day to the card") );
    toolBar->AddControl( buttonNewDay );

    toolBar->AddSeparator();
    buttonAnalyzeCycle = new wxButton( toolBar, ID_BUTTONANALYZECYCLE, _( "analyze cycle" ), wxPoint( 63, 0 ), wxSize( 100, -1 ), flatButton, wxDefaultValidator, _T( "buttonAnalyzeCycle" ) );
    buttonAnalyzeCycle->SetToolTip( _("Analyze cycle data and calculate results") );
    toolBar->AddControl( buttonAnalyzeCycle );

    toolBar->SetToolBitmapSize( wxSize( 16, 16 ) );
    toolBar->SetToolSeparation( 15 );
    toolBar->Realize();
    SetToolBar( toolBar );

    /**************************************************************************/
    // MAIN MENU

    menuBarMain =  new wxMenuBar();

    /***********************************/

    menuNfp = new wxMenu( 0 );
    menuBarMain->Append( menuNfp, _( "NFP" ) );

    menuNfp->Append( ID_MNU_NEW_SET, _( "New cards' set\tCtrl+N" ), _( "Create new set of cycles' cards" ), wxITEM_NORMAL );
    menuNfp->Append( ID_MNU_OPEN_SET, _( "Open cards' set\tCtrl+O" ), _( "Open existing set of cycles' cards from file" ), wxITEM_NORMAL );
    menuNfp->Append( ID_MNU_SAVE_SET, _( "Save cards' set\tCtrl+S" ), _( "Save changes in currently opened file" ), wxITEM_NORMAL );
    menuNfp->Append( ID_MNU_SAVE_SET_AS, _( "Save cards' set as...\tCtrl+Shift+S" ), _( "Save set of cycles' cards in new file" ) , wxITEM_NORMAL );
    menuNfp->AppendSeparator();
    menuNfp->Append( ID_MNU_PRINT, _( "Print\tCtrl+P" ), _( "Print cards" ), wxITEM_NORMAL );
    /** TODO - the print preview can be implemented in the future ;-) */
    //menuNfp->Append (ID_MNU_PRINT_PREVIEW, _("Print preview"), _("Print preview"), wxITEM_NORMAL);
    //menuNfp->Append (ID_MNU_PRINT_PAGE_SETUP, _("Page setup"), _("Page setup"), wxITEM_NORMAL);
    menuNfp->AppendSeparator();
    menuNfp->Append( ID_MNU_OPTIONS, _( "Preferences\tF2" ), _( "Change the application preferences" ), wxITEM_NORMAL );
    menuNfp->AppendSeparator();
    menuNfp->Append( ID_MNU_EXIT, _( "Exit\tAlt+F4" ), _( "Close the application" ), wxITEM_NORMAL );

    /***********************************/

    menuCard = new wxMenu( 0 );
    menuBarMain->Append( menuCard, _( "Card" ) );

    menuCard->Append( ID_MNU_PREVIOUS_CARD, _( "Previous card\tCtrl+Left" ), _( "Go to the previous card" ), wxITEM_NORMAL );
    menuCard->Append( ID_MNU_NEXT_CARD, _( "Next card\tCtrl+Right" ), _( "Go to the next card" ), wxITEM_NORMAL );
    menuCard->Append( ID_MNU_GO_TO_CARD,  _( "Go to card..\tCtrl+G" ), _( "Go to the card with choosen number or based on date" ), wxITEM_NORMAL );
    menuCard->AppendSeparator();
    menuCard->Append( ID_MNU_EDIT_CARD, _( "Edit card's data" ), _( "Edit card's data" ), wxITEM_NORMAL );
    menuCard->Append( ID_MNU_DELETE_CARD, _( "Remove card" ), _( "Remove card. It is possible to remove only the last card from the set" ), wxITEM_NORMAL );
    menuCard->Append( ID_MNU_CARD_LOCKED, _( "Card locked\tCtrl+L" ), _( "Lock card. This option protects card's data against accidental changes. Also prevents from autocalculating results so manually set results will not be lost." ), wxITEM_CHECK );
    menuCard->Append( ID_MNU_CARD_CORRUPTED, _( "Corrupted/incomplete data" ), _( "Card contains corrupted or incomplete data. If selected then data from this cycle will not be used to e.g. calculate begining of the fertile phase in next cycles." ), wxITEM_CHECK );
    menuCard->AppendSeparator();
    menuCard->Append( ID_MNU_NEW_CARD, _( "New card\tCtrl+C" ), _( "Add new card - new cycle begun" ), wxITEM_NORMAL );

    /***********************************/

    menuDay = new wxMenu( 0 );
    menuBarMain->Append( menuDay, _( "Day" ) );

    menuDay->Append( ID_MNU_DAY_NO, _( "Day XX" ), wxEmptyString, wxITEM_NORMAL );
    menuDay->Enable( ID_MNU_DAY_NO, false );
    menuDay->AppendSeparator();
    menuDay->Append( ID_MNU_EDIT_DAY, _( "Edit day's data" ), _( "Edit day's data" ), wxITEM_NORMAL );
    menuDay->Append( ID_MNU_DELETE_DAY, _( "Remove day" ), _( "Remove day. It is possible to remove only the last day from the last card from the set" ), wxITEM_NORMAL );

    menuMoveDays = new wxMenu( 0 );
    menuMoveDays->Append( ID_MNU_MOVE_DAYS_TO_PREV_CARD, _( "XX - XX to the previous card" ), _( "Move the currently selected day and preceding ones to the next card" ), wxITEM_NORMAL );
    menuMoveDays->Append( ID_MNU_MOVE_DAYS_TO_NEXT_CARD, _( "XX - XX to the next card" ), _( "Move the currently selected day and following ones to the next card. Create next card if it doesn't exist" ), wxITEM_NORMAL );

    menuDay->AppendSeparator();
    menuDay->Append( ID_MNU_MOVE_DAYS, _( "Move days.." ), menuMoveDays );
    menuDay->AppendSeparator();
    menuDay->Append( ID_MNU_NEW_DAY, _( "New day\tCtrl+D" ), _( "Add new day to the card" ), wxITEM_NORMAL );

    /***********************************/

    menuResults = new wxMenu( 0 );
    menuBarMain->Append( menuResults, _( "Analysis" ) );

    menuResultsMarkDayAs = new wxMenu( 0 );
    menuResultsMarkDayAs->Append( ID_MNU_RESULTS_MUCUS_1ST_DAY, _( "first day of mucus apperance" ) , _( "Mark this day as a first day of mucus apperance" ) , wxITEM_CHECK );
    menuResultsMarkDayAs->Append( ID_MNU_RESULTS_MUCUS_1ST_DAY_FERTILE, _( "first day of more fertile mucus apperance" ), _( "Mark this day as a first day of more fertile mucus apperance" ), wxITEM_CHECK );
    menuResultsMarkDayAs->Append( ID_MNU_RESULTS_MUCUS_PEAK_DAY, _( "mucus peak day" ), _( "Mark this day as a mucus peak day" ), wxITEM_CHECK );
    menuResultsMarkDayAs->AppendSeparator();
    menuResultsMarkDayAs->Append( ID_MNU_RESULTS_CERVIX_1ST_DAY, _( "first day of cervix changes" ), _( "Mark this day as a first day of cervix changes" ) , wxITEM_CHECK );
    menuResultsMarkDayAs->Append( ID_MNU_RESULTS_CERVIX_PEAK_DAY, _( "cervix peak day" ), _( "Mark this day as a cervix peak day" ) , wxITEM_CHECK );
    menuResultsMarkDayAs->AppendSeparator();
    menuResultsMarkDayAs->Append( ID_MNU_RESULTS_TEMPERATURE_1ST_DAY, _( "first day of high temperature level" ), _( "Mark this day as a first day of high temperature level" ), wxITEM_CHECK );
    menuResultsMarkDayAs->AppendSeparator();
    menuResultsMarkDayAs->Append( ID_MNU_RESULTS_FERTILE_PHASE_START, _( "first day of fertile phase" ), _( "Mark this day as a first day of the fertile phase" ), wxITEM_CHECK );
    menuResultsMarkDayAs->Append( ID_MNU_RESULTS_INFERTILE_PHASE_START, _( "first day of infertile phase" ), _( "Mark this day as a first day of the infertile phase (pre- or post-ovulatory infertility)" ), wxITEM_CHECK );

    menuResults->Append( ID_MNU_RESULTS_MARK_DAYS_AS, _("Mark day XX as.."), menuResultsMarkDayAs );
    menuResults->AppendSeparator();
    menuResults->Append( ID_MNU_RESULTS_AUTOCALCULATE, _( "Analyze cycle data now" ) , _( "Analyze cycle data and calculate results" ), wxITEM_NORMAL );
    menuResults->Append( ID_MNU_RESULTS_AUTOCALCULATE_ON_CHANGE, _( "Analyze cycle after each data change" ) , _( "Analyze cycle automatically after each data change" ), wxITEM_CHECK );
    menuResults->Append( ID_MNU_RESULTS_CHANGE_SETTINGS, _( "Change analysis settings" ) , _( "Change analysis settings" ), wxITEM_CHECK );


    /*********************/

    menuStats = new wxMenu( 0 );
    menuBarMain->Append( menuStats, _( "Statistics" ) );
    menuStats->Append( ID_MNU_STAT_STATICTICS, _( "Statistics" ), wxEmptyString, wxITEM_NORMAL );
    /*
    menuStats->Append( ID_MNU_STAT_CYCLE_HIST, _( "Length of cycles" ), wxEmptyString, wxITEM_NORMAL );
    menuStats->Append( ID_MNU_STAT_TEMPER_HIST, _( "Temperature in cycles" ), wxEmptyString, wxITEM_NORMAL );
    */

    /*********************/

    menuHelp = new wxMenu( 0 );
    menuBarMain->Append( menuHelp, _( "Help" ) );

    menuHelp->Append( ID_MNU_HELP, _( "Help\tF1" ), _( "Help" ), wxITEM_NORMAL );
    menuHelp->Append( ID_MNU_HOME_PAGE, _( "Home page" ), _( "Visit the web page of wx-nfp" ), wxITEM_NORMAL );
    menuHelp->Append( ID_MNU_REPORT_BUG, _( "Report bug / comments" ), _( "Report bug found in the application or any comments to the application" ), wxITEM_NORMAL );
#if defined(__WXMSW__)
    menuHelp->AppendSeparator();
    menuHelp->Append( ID_MNU_UPDATE, _( "Check for updates..." ), _( "Check if there is a new version of the application to download.." ), wxITEM_NORMAL );
#endif
    menuHelp->AppendSeparator();
    menuHelp->Append( ID_MNU_ABOUT, _( "About..." ), _( "General information about the application" ) , wxITEM_NORMAL );

    /***********************************/
    SetMenuBar( menuBarMain );

    /**************************************************************************/
    // POPUP MENU
    menuDayPopup = new wxMenu( 0 );

    menuDayPopup->Append( ID_MNU_DAY_NO, _( "Day XX" ), wxEmptyString, wxITEM_NORMAL );
    menuDayPopup->Enable( ID_MNU_DAY_NO, false );
    menuDayPopup->AppendSeparator();
    menuDayPopup->Append( ID_MNU_EDIT_DAY, _( "Edit day's data" ), _( "Edit day's data" ), wxITEM_NORMAL );
    menuDayPopup->Append( ID_MNU_DELETE_DAY, _( "Remove day" ), _( "Remove day. It is possible to remove only the last day from the last card from the set" ), wxITEM_NORMAL );
    menuDayPopup->AppendSeparator();

    menuDayPopup->Append( ID_MNU_RESULTS_MARK_DAYS_AS, _( "Mark day XX as.." ), menuResultsMarkDayAs );
    menuDayPopup->Append( ID_MNU_MOVE_DAYS, _( "Move days.." ), menuMoveDays );

    /**************************************************************************/
    // OTHER

    statusBar = new wxStatusBar( this, ID_STATUSBAR );
    statusBar->SetFieldsCount( 2 );
    statusBar->SetStatusText( wxEmptyString, 0 );
    statusBar->SetStatusText( wxEmptyString, 1 );
    int WxStatusBar1_Widths[2];
    WxStatusBar1_Widths[0] = -1;
    WxStatusBar1_Widths[1] = -1;
    statusBar->SetStatusWidths( 2, WxStatusBar1_Widths );
    SetStatusBar( statusBar );

    timerMain = new wxTimer();
    timerMain->SetOwner( this, ID_TIMERMAIN );

    timerNotification = new wxTimer();
    timerNotification->SetOwner( this, ID_TIMERNOTIFICATION );

    GetSizer()->Fit( this );
    GetSizer()->SetSizeHints( this );

    SetSize( m_config->formMainLeft, m_config->formMainTop, m_config->formMainWidth, m_config->formMainHeight );
    Maximize( m_config->formMainMaximized );

    wxIcon wx_nfp_ICON( wx_nfp_xpm );
    SetIcon( wx_nfp_ICON );

    SetTitle( _( "Natural Family Planing" ) );



    // -------------------------------------------------------------------------
    ////GUI Items Creation End
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
void nfpMainFrame::newAppAvailableEvent( wxCommandEvent& event )
{
    int id = event.GetInt();
    if ( id == EVENT_STATUS_UPDATE_AVAILABLE ) {
        statusBar->SetStatusText( wxEmptyString, 1 );

        updatesNotificationForm *frame = new updatesNotificationForm( this, m_config, event.GetString() );
        frame->Show( true );
    } else {
        if ( id == EVENT_STATUS_UPDATE_NOT_AVAILABLE ) {

            statusBar->SetStatusText( _( "New version of application is not available." ), 1 );
            if ( m_showNewAppMessage ) {
                wxMessageBox( _( "New version of application is not available." ), _( "Notification" ), wxOK );
            }
        } else if ( id == EVENT_STATUS_ERROR ) {

            statusBar->SetStatusText( event.GetString(), 1 );
            if ( m_showNewAppMessage ) {
                wxMessageBox( event.GetString(), _( "Warning" ), wxOK );
            }
        } else {
            statusBar->SetStatusText( wxString::Format( _( "Unknown event ID: %i, message: %s" ), event.GetInt(), event.GetString().c_str() ), 1 );
            if ( m_showNewAppMessage ) {
                wxMessageBox( wxString::Format( _( "Unknown event ID: %i, message: %s" ), event.GetInt(), event.GetString().c_str() ), _( "Warning" ), wxOK );
            }
        }
        menuHelp->Enable( ID_MNU_UPDATE, true );
        m_newAppStatusMessage = 30;
    }

    m_showNewAppMessage = false;

}

/**
 *
 */
void nfpMainFrame::newAppDownloadedEvent( wxCommandEvent& event )
{
    int id = event.GetInt();
    if ( id == EVENT_STATUS_UPDATE_DOWNLOADED ) {
        m_newAppSetupFile = event.GetString();

        int answer = wxMessageBox( _( "New version of application is ready for installation.\n-Press 'Yes' if you want to reinstall the application now.\n-Press 'No' if you prefer to reinstall it later." ) , _( "Question" ), wxYES_NO );
        if ( answer == wxYES ) {
            if ( askToSaveChanges( false ) ) {
                m_cycleData->setCardModified( false );
                runUpdateProgram( true );
            }
        } else {
            m_doUpdateOnExit = true;
            wxMessageBox( _( "You chose to not reinstall the application now. I ask you again when you close the application." ), _( "Notification" ), wxOK | wxICON_INFORMATION );
        }
    } else {

    }
}

/**
 * runUpdateProgram
 */
void nfpMainFrame::runUpdateProgram( bool closeWindowIfSuccess )
{
#if defined(__UNIX__)
    // TODO
    wxMessageBox( wxString::Format( _( "Cannot execute file: %s - NOT IMPLEMENTED YET!" ), m_newAppSetupFile.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, this );
#else

    long pid = wxExecute( m_newAppSetupFile, wxEXEC_ASYNC );
    if ( pid ) {
        if ( closeWindowIfSuccess ) {

            Close();
        }
    } else {
        wxMessageBox( wxString::Format( _( "Cannot execute file: %s" ), m_newAppSetupFile.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, this );
    }
#endif
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * configDataModifiedEvent
 */
void nfpMainFrame::configDataModifiedEvent( wxCommandEvent& event )
{
    int id = event.GetInt();
    wxString message = event.GetString();

    if ( id == CONFIG_LANGUAGE_CHANGED ) {
        // Language update notification
        // actually nothing to do with this event
    } else if ( id == CONFIG_FONT_CHANGED ) {
        // Font update notification
        // TODO Font update notification - recalculate labels sizes in windowTop
        windowTop->recalculateComponentsSizes();
        windowLeft->recalculateComponentsSizes();
    } else if ( id == CONFIG_BUTTONS_STYLE_CHANGED ) {
        // Buttons style update notification
        // TODO
        setButtonsStyle();
        m_cardFrm->setButtonsStyle();
        m_dayFrm->setButtonsStyle();
    } else {
        // Config update
        Refresh();
        m_dayFrm->updateMeasuredTemperatureList();
    }
}

/**
 * cardDataModifiedEvent
 */
void nfpMainFrame::cardDataModifiedEvent( wxCommandEvent& event )
{
    int id = event.GetInt();
    wxString message = event.GetString();

    if (m_config->autoanalyzeCard && ! m_cycleData->getCard()->getCardLocked() && id != ACTIVE_CARD_UPDATE ) {
        m_cycleData->calculateResultsAutomaticallyOnChange(m_cycleData->getActiveCard(), m_config);

        if ( !m_cycleData->getErrorMessages().IsEmpty() ) {
            showAnalysisResultNotification(m_cycleData->getErrorMessages());
        }

        m_cycleData->setCardModified( true );
        //windowMain->Refresh();
    }

    if ( id == ACTIVE_CARD_UPDATE ) {
        windowTop->Refresh();
    } else if ( id == ACTIVE_CARD_UPDATE_WITH_1ST_DAY ) {
        checkForMissingDays();
        windowTop->Refresh();
        windowMain->Refresh();
    } else if ( id == ACTIVE_CARD_UPDATE_WITH_PLACES ) {
        windowTop->Refresh();
        windowMain->Refresh();
    } else {
        windowTop->Refresh();
        windowLeft->repaint_activeCardUpdated();
        windowMain->Refresh();
    }
}

/**
 * dayDataModifiedEvent
 */
void nfpMainFrame::dayDataModifiedEvent( wxCommandEvent& event )
{
    int id = event.GetInt();
    wxString message = event.GetString();

    if (m_config->autoanalyzeCard && ! m_cycleData->getCard()->getCardLocked()) {
        m_cycleData->calculateResultsAutomaticallyOnChange(m_cycleData->getActiveCard(), m_config);

        if ( !m_cycleData->getErrorMessages().IsEmpty() ) {
            showAnalysisResultNotification(m_cycleData->getErrorMessages());
        }

        m_cycleData->setCardModified( true );
        windowMain->Refresh();
    } else {
        if ( id == ACTIVE_DAY_UPDATE_WITH_RESULTS ) {
            int start = m_cycleData->getCard()->getResultTemperatureLowLevelStart() - 1;
            int end   = m_cycleData->getCard()->getResultTemperatureHighLevelStart() + 20;
            if ( start < 1 )
                start = 1;
            if ( end > m_cycleData->getDaysCount() )
                end = m_cycleData->getDaysCount();
            windowMain->repaint_daysUpdated( start, end );
            id = ACTIVE_DAY_UPDATE_WITH_TEMP;
        }
        windowMain->repaint( id );
    }
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * nfpMainFrameClose
 */
void nfpMainFrame::nfpMainFrameClose( wxCloseEvent& event )
{
    if ( askToSaveChanges( true ) ) {
        m_cardFrm->GetPosition( & ( m_config->formCardLeft ), & ( m_config->formCardTop ) );
        m_dayFrm->GetPosition( & ( m_config->formDayLeft ), & ( m_config->formDayTop ) );
        m_config->formMainMaximized = this->IsMaximized();
        if ( !m_config->formMainMaximized ) {
            this->GetPosition( & ( m_config->formMainLeft ), & ( m_config->formMainTop ) );
            this->GetSize( & ( m_config->formMainWidth ), & ( m_config->formMainHeight ) );
        }
        m_config->saveParamsToConfigFile();

        if (timerNotification->IsRunning())
            timerNotification->Stop();
        if (timerMain->IsRunning())
            timerMain->Stop();

        if ( m_doUpdateOnExit ) {
            int answer = wxMessageBox( _( "New version of application is ready for installation.\n-Press 'Yes' if you want to reinstall the application now.\n-Press 'No' if you prefer to reinstall it later." ), _( "Question" ), wxYES_NO );
            if ( answer == wxYES ) {
                runUpdateProgram( false );

                long pid = wxExecute( m_newAppSetupFile, wxEXEC_ASYNC );
                if ( !pid ) {
                    wxMessageBox( wxString::Format( _( "Cannot execute file: %s" ), m_newAppSetupFile.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, this );
                }
            }
        }
        m_parent->Close();
        Destroy();
    }
}

/**
 * nfpMainFrameMouseWheel
 */
void nfpMainFrame::nfpMainFrameMouseWheel( wxMouseEvent& event )
{
    // insert your code here
}

/**
 * nfpMainFrameSize
 */
void nfpMainFrame::nfpMainFrameSize( wxSizeEvent& event )
{
    // insert your code here
}

/**
 * scrollBarVerticalScroll
 */
void nfpMainFrame::scrollBarVerticalScroll( wxScrollEvent& event )
{


    if ( m_config->verticalDisplacement != ( 0 - windowMain->getCellHeight() * event.GetPosition() ) ) {
        m_config->verticalDisplacement = 0 - windowMain->getCellHeight() * event.GetPosition();

        Refresh();
    }
}

/**
 * timerMainTimer
 */
void nfpMainFrame::timerMainTimer( wxTimerEvent& event )
{
    if (( m_cycleData->getCardModified() != m_cardModifiedPrev ) || ( ! m_config->dataFileName.IsSameAs( m_dataFileNamePrev ) ) ) {

        m_dataFileNamePrev = m_config->dataFileName;
        m_cardModifiedPrev = m_cycleData->getCardModified();

        wxString t = _( "Natural Family Planing" );
        t << _T( "  -  " );
        if ( m_dataFileNamePrev.IsEmpty() ) {
            t << _( "new_set" );
        } else {
            t << m_dataFileNamePrev;
        }
        if ( m_cardModifiedPrev ) {
            t << _T( " (*)" );
        }

        this->SetTitle( t );
    }

    if ( m_newAppStatusMessage > 1 ) {
        m_newAppStatusMessage--;
    }
    if ( m_newAppStatusMessage == 1 ) {
        m_newAppStatusMessage--;
        statusBar->SetStatusText( wxEmptyString, 1 );
    }

    if ( m_doCheckForMissingDays ) {
        m_doCheckForMissingDays = false;
        checkForMissingDays();
    }

}

/**
 * timerNotificationTimer
 */
void nfpMainFrame::timerNotificationTimer( wxTimerEvent& event )
{
    if ( m_config->breastSelfControlReminderDay > 0 ) {
        wxDateTime ftoc = m_cycleData->getCard( m_cycleData->getCardsCount() )->getFirstDayOfCycle();
        wxDateTime today = wxDateTime::Today();
        int cycleDay = getNumberOfDays( ftoc, today );
        int daysFromLastReminder = getNumberOfDays( m_config->breastSelfControlLastReminder, today );
        cycleDay++;
        bool showBreastSelfControlReminder = false;

        if ( cycleDay < m_config->breastSelfControlReminderDay ) {
            showBreastSelfControlReminder = false;
        } else if ( cycleDay == m_config->breastSelfControlReminderDay && daysFromLastReminder > 0 ) {
            showBreastSelfControlReminder = true;
            m_config->breastSelfControlLastReminder = today;
        } else if ( daysFromLastReminder >= m_config->breastSelfControlInterval ) {
            showBreastSelfControlReminder = true;
            m_config->breastSelfControlLastReminder = today;
        } else if ( daysFromLastReminder >= cycleDay ) {
            // reminder byl pokazany w poprzednim cyklu
            showBreastSelfControlReminder = true;
            m_config->breastSelfControlLastReminder = today;
        }

        if ( showBreastSelfControlReminder )
            showNotification(_( "Please, remember to perform today a breasts self-examination." ), wxALIGN_CENTRE );
    }
}

/******************************************************************************/
/****** TOOLBAR ***************************************************************/
/******************************************************************************/

/**
 * prevCardClick
 */
void nfpMainFrame::prevCardClick( wxCommandEvent& event )
{
    if ( checkCardAndDayFramesStates( true, true ) ) {
        int c = m_cycleData->getActiveCard() - 1;
        if ( c < 1 )
            c = 1;
        m_cycleData->setActiveCard( c );
        m_cycleData->setActiveDay( -1 );
        m_config->checkFirstDayVisibility = true;
        updateAll();
    }
}

/**
 * nextCardClick
 */
void nfpMainFrame::nextCardClick( wxCommandEvent& event )
{
    if ( checkCardAndDayFramesStates( true, true ) ) {
        int c = m_cycleData->getActiveCard() + 1;
        if ( c > m_cycleData->getCardsCount() )
            c = m_cycleData->getCardsCount();
        m_cycleData->setActiveCard( c );
        m_cycleData->setActiveDay( -1 );
        m_config->checkFirstDayVisibility = true;
        updateAll();
    }
}

/**
 * newDayClick
 */
void nfpMainFrame::newDayClick( wxCommandEvent& event )
{
    if ( checkDayFrameState( false, true ) ) {
        if ( m_cycleData->addNewDay() > -1 ) {
            m_cycleData->setActiveDay( m_cycleData->getDaysCount() );
            m_cycleData->setCardModified( true );
            m_config->checkCurrentDayVisibility = true;
            updateAll();
            m_dayFrm->update();
            m_dayFrm->Show();
        } else {
            wxMessageBox( _( "Error occured while adding new day" ), _( "Error" ), wxOK | wxICON_ERROR );
        }
    }
}

/******************************************************************************/
/****** MAIN MENU *************************************************************/
/******************************************************************************/

/**
 * MnuActivated
 */
void nfpMainFrame::MnuActivated( wxMenuEvent& event )
{
    menuResultsMarkDayAs->Check( ID_MNU_RESULTS_MUCUS_1ST_DAY, false );
    menuResultsMarkDayAs->Check( ID_MNU_RESULTS_MUCUS_1ST_DAY_FERTILE, false );
    menuResultsMarkDayAs->Check( ID_MNU_RESULTS_MUCUS_PEAK_DAY, false );
    menuResultsMarkDayAs->Check( ID_MNU_RESULTS_CERVIX_1ST_DAY, false );
    menuResultsMarkDayAs->Check( ID_MNU_RESULTS_CERVIX_PEAK_DAY, false );
    menuResultsMarkDayAs->Check( ID_MNU_RESULTS_TEMPERATURE_1ST_DAY, false );
    menuResultsMarkDayAs->Check( ID_MNU_RESULTS_FERTILE_PHASE_START, false );
    menuResultsMarkDayAs->Check( ID_MNU_RESULTS_INFERTILE_PHASE_START, false );
    menuMoveDays->Enable( ID_MNU_MOVE_DAYS_TO_PREV_CARD, false );
    menuMoveDays->Enable( ID_MNU_MOVE_DAYS_TO_NEXT_CARD, false );
    menuResults->Check( ID_MNU_RESULTS_AUTOCALCULATE_ON_CHANGE, m_config->autoanalyzeCard );

    wxString dayNoString = _( "Day" );
    wxString markDayAsString = _("Mark day XX as..");
    wxString moveDaysToPrevCardString = _( "XX - XX to the previous card" );
    wxString moveDaysToNextCardString = _( "XX - XX to the next card" );

    int activeDay = m_cycleData->getActiveDay();
    int activeCard = m_cycleData->getActiveCard();
    int cardsCount = m_cycleData->getCardsCount();
    int daysCount = m_cycleData->getDaysCount();

    if ( activeDay > 0 ) {
        dayNoString << _T( " " ) << activeDay;
        markDayAsString = wxString::Format( _("Mark day %i as.."), activeDay );

        cardEntry *card = m_cycleData->getCard();
        if ( card->isResultMucus1stDay(activeDay) )
            menuResultsMarkDayAs->Check( ID_MNU_RESULTS_MUCUS_1ST_DAY, true );
        if ( card->isResultMucus1stMoreFertileDay(activeDay) )
            menuResultsMarkDayAs->Check( ID_MNU_RESULTS_MUCUS_1ST_DAY_FERTILE, true );
        if ( card->isResultMucusPeak(activeDay) )
            menuResultsMarkDayAs->Check( ID_MNU_RESULTS_MUCUS_PEAK_DAY, true );
        if ( card->isResultCervix1stDay(activeDay) )
            menuResultsMarkDayAs->Check( ID_MNU_RESULTS_CERVIX_1ST_DAY, true );
        if ( card->isResultCervixPeak(activeDay) )
            menuResultsMarkDayAs->Check( ID_MNU_RESULTS_CERVIX_PEAK_DAY, true );
        if ( card->getResultTemperatureHighLevelStart() == activeDay )
            menuResultsMarkDayAs->Check( ID_MNU_RESULTS_TEMPERATURE_1ST_DAY, true );
        if ( card->isResultFertilePhaseStart(activeDay) )
            menuResultsMarkDayAs->Check( ID_MNU_RESULTS_FERTILE_PHASE_START, true );
        if ( card->isResultInfertilePhaseStart(activeDay))
            menuResultsMarkDayAs->Check( ID_MNU_RESULTS_INFERTILE_PHASE_START, true );


        menuDay->Enable( ID_MNU_EDIT_DAY, true );
        menuDayPopup->Enable( ID_MNU_EDIT_DAY, true );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_MUCUS_1ST_DAY, true );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_MUCUS_1ST_DAY_FERTILE, true );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_MUCUS_PEAK_DAY, true );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_CERVIX_1ST_DAY, true );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_CERVIX_PEAK_DAY, true );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_TEMPERATURE_1ST_DAY, true );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_FERTILE_PHASE_START, true );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_INFERTILE_PHASE_START, true );

        if ( activeCard == cardsCount ) {
            menuMoveDays->Enable( ID_MNU_MOVE_DAYS_TO_PREV_CARD, true );
            if ( activeDay > 1 )
                menuMoveDays->Enable( ID_MNU_MOVE_DAYS_TO_NEXT_CARD, true );
        } else if ( activeCard == cardsCount - 1 ) {
            if ( activeDay > 1 )
                menuMoveDays->Enable( ID_MNU_MOVE_DAYS_TO_NEXT_CARD, true );
        }
    } else {
        dayNoString << _T( " XX" );

        menuDay->Enable( ID_MNU_EDIT_DAY, false );
        menuDayPopup->Enable( ID_MNU_EDIT_DAY, false );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_MUCUS_1ST_DAY, false );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_MUCUS_1ST_DAY_FERTILE, false );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_MUCUS_PEAK_DAY, false );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_CERVIX_1ST_DAY, false );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_CERVIX_PEAK_DAY, false );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_TEMPERATURE_1ST_DAY, false );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_FERTILE_PHASE_START, false );
        menuResultsMarkDayAs->Enable( ID_MNU_RESULTS_INFERTILE_PHASE_START, false );
    }

    if ( activeDay == daysCount) {
        moveDaysToNextCardString = wxString::Format( _( "%i to the next card" ), activeDay);
    } else {
        moveDaysToNextCardString = wxString::Format( _( "%i - %i to the next card" ), activeDay, daysCount);
    }

    if ( activeDay == 1) {
        moveDaysToPrevCardString = _( "1 to the previous card" );
    } else {
        moveDaysToPrevCardString = wxString::Format( _( "1 - %i to the previous card" ), activeDay);
    }

    menuDay->SetLabel( ID_MNU_DAY_NO, dayNoString );
    menuDayPopup->SetLabel( ID_MNU_DAY_NO, dayNoString );
    menuResults->SetLabel( ID_MNU_RESULTS_MARK_DAYS_AS, markDayAsString );
    menuDayPopup->SetLabel( ID_MNU_RESULTS_MARK_DAYS_AS, markDayAsString );
    menuDayPopup->SetLabel( ID_MNU_MOVE_DAYS_TO_PREV_CARD, moveDaysToPrevCardString );
    menuDayPopup->SetLabel( ID_MNU_MOVE_DAYS_TO_NEXT_CARD, moveDaysToNextCardString );

    menuCard->Check(ID_MNU_CARD_LOCKED, m_cycleData->getCard()->getCardLocked());
    menuCard->Check(ID_MNU_CARD_CORRUPTED, m_cycleData->getCard()->getCorruptedData());

    if ( m_cycleData->getCard()->getCardLocked() ) {
        // card locked
        menuDay->Enable( ID_MNU_EDIT_DAY, false );
        menuDay->Enable( ID_MNU_DELETE_DAY, false );
        menuDay->Enable( ID_MNU_NEW_DAY, false );
        menuDayPopup->Enable( ID_MNU_EDIT_DAY, false );
        menuDayPopup->Enable( ID_MNU_DELETE_DAY, false );
    } else {
        if ( activeCard == cardsCount && activeDay == daysCount && daysCount > 1 ) {
            menuDay->Enable( ID_MNU_DELETE_DAY, true );
            menuDayPopup->Enable( ID_MNU_DELETE_DAY, true );
        } else {
            menuDay->Enable( ID_MNU_DELETE_DAY, false );
            menuDayPopup->Enable( ID_MNU_DELETE_DAY, false );
        }

        menuDay->Enable( ID_MNU_NEW_DAY, true );
    }

}

/******************************************************************************/

/**
 * MnuNewSetClick
 */
void nfpMainFrame::MnuNewSetClick( wxCommandEvent& event )
{
    if ( askToSaveChanges( true ) ) {
        m_cycleData->createNewSet();
        m_config->dataFileName = wxEmptyString;
        m_cycleData->setActiveCard( m_cycleData->getCardsCount() );
        m_cycleData->setActiveDay( -1 );
        m_cycleData->setCardModified( true );
        m_config->checkLastDayVisibility = true;
        updateAll();
        m_cardFrm->update();
        m_cardFrm->Show();
        m_cardFrm->Raise();
    }
}

/**
 * MnuOpenSetClick
 */
void nfpMainFrame::MnuOpenSetClick( wxCommandEvent& event )
{
    if ( askToSaveChanges( true ) ) {
        wxString message = _( "Open cards' set..." );
        wxString default_path = wxEmptyString;
        wxString default_filename = wxEmptyString;
        wxString default_extension = wxEmptyString;
        wxString wildcard = _T( "*.nfpdata" );
        int flags = wxFD_OPEN | wxFD_FILE_MUST_EXIST;
        wxString filename = wxFileSelector( message, default_path, default_filename, default_extension, wildcard, flags, this );
        if ( !filename.empty() ) {
            m_cycleData->removeAll();
            Refresh();
            m_cycleData->setActiveCard( -1 );
            m_cycleData->setActiveDay( -1 );
            m_config->dataFileName = filename;

            m_cycleData->setCardModified( false );
            if ( m_cycleData->readCardsDataFromFile( m_config->dataFileName ) ) {
                m_cycleData->setActiveCard( m_cycleData->getCardsCount() );
                m_config->checkLastDayVisibility = true;
                updateAll();

                informUserAboutChangesInThisRelease();

                checkForMissingDays();
            } else {
                wxMessageBox( wxString::Format( _( "Error occured while reading data from file:\n%s" ), m_cycleData->getErrorMessages().c_str() ), _( "Error" ), wxOK | wxICON_ERROR );
                MnuNewSetClick( event );
            }
        }
    }
}

/**
 * MnuSaveSetClick
 */
void nfpMainFrame::MnuSaveSetClick( wxCommandEvent& event )
{
    saveChanges( false, true );
}

/**
 * MnuSaveSetAsClick
 */
void nfpMainFrame::MnuSaveSetAsClick( wxCommandEvent& event )
{
    saveChanges( true, true );
}

/**
 * MnuPrintClick
 */
void nfpMainFrame::MnuPrintClick( wxCommandEvent& event )
{
    //printFrame *frame = new printFrame (this, m_config, m_cycleData, GOTO_CARD);
    printFrame *frame = new printFrame( this, m_config, 1, m_cycleData->getCardsCount(), m_cycleData->getActiveCard() );
    int ret = frame->ShowModal();

    if ( ret > 0 ) {
        int firstCard = 0;
        int lastCard = 0;
        bool printLegend = false;
        if ( ret > 999999 ) {
            printLegend = true;
            ret = ret % 1000000;
        }
        firstCard = ret / 1000;
        lastCard = ret % 1000;

        wxPrintDialogData printDialogData( * m_printData );
        printDialogData.EnablePageNumbers( false );
        printDialogData.EnableSelection( false );
        printDialogData.EnablePrintToFile( false );

        wxPrinter printer( & printDialogData );
        customPrintout printout( m_config, m_cycleData, firstCard, lastCard, printLegend, _( "wx-nfp" ) );

        if ( !printer.Print( this, &printout, true ) ) {
            if ( wxPrinter::GetLastError() == wxPRINTER_ERROR )
                wxMessageBox( _( "Problem with printing occurred.\nPerhaps your current printer is not set correctly?" ) , _( "Error" ), wxOK );
            else
                wxMessageBox( _( "Printing has been canceled." ), _( "Error" ), wxOK );
        } else {
            ( *m_printData ) = printer.GetPrintDialogData().GetPrintData();
        }
    }
}

/**
 * MnuPrintPreviewClick
 */
void nfpMainFrame::MnuPrintPreviewClick( wxCommandEvent& event )
{
    // Pass two printout objects: for preview, and possible printing.
    wxPrintDialogData printDialogData( * m_printData );
    wxPrintPreview *preview = new wxPrintPreview( new customPrintout( m_config, m_cycleData, 11, 11, false ), new customPrintout( m_config, m_cycleData, 11, 11, false ), & printDialogData );
    if ( !preview->Ok() ) {
        delete preview;
        wxMessageBox( _( "There was a problem previewing.\nPerhaps your current printer is not set correctly?" ), _( "Previewing" ), wxOK );
        return;
    }

    wxPreviewFrame *frame = new wxPreviewFrame( preview, this, _( "Demo Print Preview" ), wxPoint( 100, 100 ), wxSize( 600, 650 ) );
    frame->Centre( wxBOTH );
    frame->Initialize();
    frame->Show();

    //preview->SetZoom(int percent);
}

/**
 * MnuPrintPageSetupClick
 */
void nfpMainFrame::MnuPrintPageSetupClick( wxCommandEvent& event )
{
    // TODO
}

/**
 * MnuOptionsClick
 */
void nfpMainFrame::MnuOptionsClick( wxCommandEvent& event )
{
    configFrame *frame = new configFrame( this, m_config );
    frame->ShowModal();

    //int ret = frame->ShowModal();
    //wxString aaa = _("\nReturn code: ");
    //aaa << ret << _("\n");
    //m_text->AppendText(aaa);
}

/**
 * nfpMainFrame
 */
void nfpMainFrame::MnuExitClick( wxCommandEvent& event )
{
    Close();
}

/******************************************************************************/

/**
 * MnuPreviousCardClick
 */
void nfpMainFrame::MnuPreviousCardClick( wxCommandEvent& event )
{
    prevCardClick( event );
}

/**
 * MnuNextCardClick
 */
void nfpMainFrame::MnuNextCardClick( wxCommandEvent& event )
{
    nextCardClick( event );
}

/**
 * MnuGoToCardClick
 */
void nfpMainFrame::MnuGoToCardClick( wxCommandEvent& event )
{
    if ( m_cycleData->getCardsCount() < 1 ) {
        return;
    }

    if ( checkCardAndDayFramesStates( true, true ) ) {
        goToFrame *frame = new goToFrame( this, m_config, m_cycleData, GOTO_CARD );
        int ret = frame->ShowModal();

        if ( ret > 0 ) {
            updateAll();
        }
    }
}

/**
 * MnuEditCardClick
 */
void nfpMainFrame::MnuEditCardClick( wxCommandEvent& event )
{
    if ( !m_cardFrm->IsShown() ) {
        m_cardFrm->update();
        m_cardFrm->Show();
    }
}

/**
 * MnuDeleteCardClick
 */
void nfpMainFrame::MnuDeleteCardClick( wxCommandEvent& event )
{
    if ( checkCardAndDayFramesStates( true, true ) ) {
        if ( m_cycleData->removeLastCard() ) {
            m_cycleData->setActiveDay( -1 );
            m_cycleData->setActiveCard( m_cycleData->getCardsCount() );
            m_cycleData->setCardModified( true );
            m_config->checkFirstDayVisibility = true;
            updateAll();
        } else {
            // removing card failed
        }
    }
}

/**
 * MnuCardLockedClick
 */
void nfpMainFrame::MnuCardLockedClick( wxCommandEvent& event )
{
    if ( m_cycleData->getActiveCard() > 0 && checkCardAndDayFramesStates( true, true ) ) {
        if ( m_cycleData->getCard()->getCardLocked() ) {
            int answer = wxMessageBox( _( "Are you sure you want to unlock the card?\nCard's data will not be protected against accidental changes." ), _( "Warning" ), wxYES_NO );
            if ( answer == wxYES ) {
                m_cycleData->getCard()->setCardLocked( false );
                m_cycleData->setCardModified( true );
                updateAll();
                m_dayFrm->checkIfDataHasBeenChanged(true);
            }
        } else {
            // lock card
            m_cycleData->getCard()->setCardLocked( true );
            m_cycleData->setCardModified( true );
            updateAll();
        }
    }
}

/**
 * MnuCardCorruptedClick
 */
void nfpMainFrame::MnuCardCorruptedClick( wxCommandEvent& event )
{
    if ( m_cycleData->getActiveCard() > 0 && checkCardAndDayFramesStates( true, true ) ) {
        m_cycleData->getCard()->setCorruptedData( !m_cycleData->getCard()->getCorruptedData() );
        m_cycleData->setCardModified( true );
        updateAll();

        /*
        if ( m_cycleData->getCard()->getCorruptedData() ) {
            int answer = wxMessageBox( _( "Are you sure you want to unlock the card?\nCard's data will not be protected against accidental changes." ), _( "Warning" ), wxYES_NO );
            if ( answer == wxYES ) {
                m_cycleData->getCard()->setCardLocked( false );
                m_cycleData->setCardModified( true );
                updateAll();
                m_dayFrm->checkIfDataHasBeenChanged(true);
            }
        } else {
            // lock card
            m_cycleData->getCard()->setCardLocked( true );
            m_cycleData->setCardModified( true );
            updateAll();
        }
        */
    }
}

/**
 * MnuNewCardClick
 */
void nfpMainFrame::MnuNewCardClick( wxCommandEvent& event )
{
    if ( checkCardAndDayFramesStates( true, true ) ) {
        // lock the current card
        m_cycleData->getCard()->setCardLocked( true );
        m_cycleData->setCardModified( true );

        // create new card
        if ( m_cycleData->addNewCard() > -1 ) {
            m_cycleData->setActiveCard( m_cycleData->getCardsCount() );
            if ( m_cycleData->addNewDay() > -1 ) {
                m_cycleData->setActiveDay( -1 );
                m_config->breastSelfControlLastReminder = -1;

                m_config->checkLastDayVisibility = true;
                updateAll();
                m_cardFrm->update();
                m_cardFrm->Show();
            } else {
                updateAll();
                wxMessageBox( _( "Error occured while adding new day" ), _( "Error" ), wxOK | wxICON_ERROR );

                // what should I do here? remove added card?

            }
        } else {
            updateAll();
            wxMessageBox( _( "Error occured while adding new card" ), _( "Error" ), wxOK | wxICON_ERROR );
        }
    }
}

/******************************************************************************/

/**
 * MnuEditDayClick
 */
void nfpMainFrame::MnuEditDayClick( wxCommandEvent& event )
{



    if ( !m_dayFrm->IsShown() ) {
        m_dayFrm->update();
        m_dayFrm->Show();
    }
}

/**
 * MnuDeleteDayClick
 */
void nfpMainFrame::MnuDeleteDayClick( wxCommandEvent& event )
{



    if ( checkDayFrameState( true, true ) ) {
        if ( m_cycleData->removeLastDay() ) {
            if ( m_cycleData->getActiveDay() > m_cycleData->getDaysCount() ) {
                m_cycleData->setActiveDay( m_cycleData->getDaysCount() );
            }
            m_cycleData->setCardModified( true );
            if ( m_cycleData->getActiveDay() > 0 ) {
                m_config->checkCurrentDayVisibility = true;
            } else {
                m_config->checkLastDayVisibility = true;
            }
            updateAll();
        } else {
            // removing day failed
        }
    }
}

/**
 * MnuNewDayClick
 */
void nfpMainFrame::MnuNewDayClick( wxCommandEvent& event )
{
    newDayClick( event );
}

/**
 * MnuMoveDaysToPrevCardClick
 */
void nfpMainFrame::MnuMoveDaysToPrevCardClick( wxCommandEvent& event )
{



    if ( checkDayFrameState( true, true ) ) {
        int activeDay = m_cycleData->getActiveDay();
        int daysCount = m_cycleData->getDaysCount();
        wxString msg;

        if ( activeDay == 1 )
            msg.Printf( _( "Should I move day %i to the previous card?" ), 1 );
        else
            msg.Printf( _( "Should I move days %i - %i to the previous card?" ), 1, activeDay );

        if ( activeDay == daysCount )
            msg << _T( "\n" ) << _( "Current card will be removed, because all days will be moved." );

        if ( wxMessageBox( msg, _( "Question" ), wxYES_NO ) == wxYES ) {
            if ( ! m_cycleData->moveDaysToPreviousCard( activeDay ) ) {
                wxMessageBox( wxString::Format( _( "Error occured while moving days to the previous card\n%s" ), m_cycleData->getErrorMessages().c_str() ), _( "Error" ), wxOK | wxICON_ERROR );
            }
            m_cycleData->setCardModified( true );
            updateAll();
        }
    }
}

/**
 * MnuMoveDaysToNextCardClick
 */
void nfpMainFrame::MnuMoveDaysToNextCardClick( wxCommandEvent& event )
{
    if ( checkDayFrameState( true, true ) ) {
        int activeDay = m_cycleData->getActiveDay();
        int activeCard = m_cycleData->getActiveCard();
        int daysCount = m_cycleData->getDaysCount();
        int cardsCount = m_cycleData->getCardsCount();
        wxString msg;

        if ( activeDay == daysCount )
            msg.Printf( _( "Should I move day %i to the next card?" ), activeDay );
        else
            msg.Printf( _( "Should I move days %i - %i to the next card?" ), activeDay, daysCount );

        if ( activeCard == cardsCount )
            msg << _T( "\n" ) << _( "New card will be created." );

        if ( wxMessageBox( msg, _( "Question" ), wxYES_NO ) == wxYES ) {
            if ( ! m_cycleData->moveDaysToNextCard( activeDay ) ) {
                wxMessageBox( wxString::Format( _( "Error occured while moving days to the next card\n%s" ), m_cycleData->getErrorMessages().c_str() ), _( "Error" ), wxOK | wxICON_ERROR );
            }
            m_cycleData->setCardModified( true );
            updateAll();
        }
    }
}

/******************************************************************************/

/**
 * MnuResultsAutocalculateClick
 */
void nfpMainFrame::MnuResultsAutocalculateClick( wxCommandEvent& event )
{
    if ( ! doModifyLockedCard() ) return;

    m_cycleData->calculateResultsAutomatically(m_cycleData->getActiveCard(), m_config);

    if ( !m_cycleData->getErrorMessages().IsEmpty() ) {
        showAnalysisResultNotification(m_cycleData->getErrorMessages());
    }
    m_cycleData->setCardModified( true );
    windowMain->Refresh();
}

/**
 * MnuResultsAutocalculateOnChangeClick
 */
void nfpMainFrame::MnuResultsAutocalculateOnChangeClick( wxCommandEvent& event )
{
    m_config->autoanalyzeCard = !m_config->autoanalyzeCard;
    menuResults->Check( ID_MNU_RESULTS_AUTOCALCULATE_ON_CHANGE, m_config->autoanalyzeCard );
}

/**
 * MnuResultsChangeAnalysisSettingsClick
 */
void nfpMainFrame::MnuResultsChangeAnalysisSettingsClick( wxCommandEvent& event )
{
    configFrame *frame = new configFrame( this, m_config, PAGE_ANALYSIS_NO );
    frame->ShowModal();
}

/**
 * MnuResultsMucus1stDayClick
 */
void nfpMainFrame::MnuResultsMucus1stDayClick( wxCommandEvent& event )
{
    if ( ! doModifyLockedCard() ) return;

    int * ret = m_cycleData->setResultMucus1stDay();
    if ( ret == NULL ) {
        showNotification(_("Setting result faild:") + m_cycleData->getErrorMessages());
        return;
    }

    windowMain->repaint_daysUpdated( ret[0], ret[1] );
    m_cycleData->setCardModified( true );
}

/**
 * MnuResultsMucus1stDayFertileClick
 */
void nfpMainFrame::MnuResultsMucus1stDayFertileClick( wxCommandEvent& event )
{
    if ( ! doModifyLockedCard() ) return;

    int * ret = m_cycleData->setResultMucus1stMoreFertileDay();
    if ( ret == NULL ) {
        showNotification(_("Setting result faild:") + m_cycleData->getErrorMessages());
        return;
    }

    windowMain->repaint_daysUpdated( ret[0], ret[1] );
    m_cycleData->setCardModified( true );
}

/**
 * MnuResultsMucusPeakDayClick
 */
void nfpMainFrame::MnuResultsMucusPeakDayClick( wxCommandEvent& event )
{
    if ( ! doModifyLockedCard() ) return;

    int * ret = m_cycleData->setResultMucusPeak();
    if ( ret == NULL ) {
        showNotification(_("Setting result faild:") + m_cycleData->getErrorMessages());
        return;
    }

    windowMain->repaint_daysUpdated( ret[0], ret[1] );
    m_cycleData->setCardModified( true );
}

/**
 * MnuResultsCervix1stDayClick
 */
void nfpMainFrame::MnuResultsCervix1stDayClick( wxCommandEvent& event )
{
    if ( ! doModifyLockedCard() ) return;

    int * ret = m_cycleData->setResultCervix1stDay();
    if ( ret == NULL ) {
        showNotification(_("Setting result faild:") + m_cycleData->getErrorMessages());
        return;
    }

    windowMain->repaint_daysUpdated( ret[0], ret[1] );
    m_cycleData->setCardModified( true );
}

/**
 * MnuResultsCervixPeakDayClick
 */
void nfpMainFrame::MnuResultsCervixPeakDayClick( wxCommandEvent& event )
{
    if ( ! doModifyLockedCard() ) return;

    int * ret = m_cycleData->setResultCervixPeak();
    if ( ret == NULL ) {
        showNotification(_("Setting result faild:") + m_cycleData->getErrorMessages());
        return;
    }

    windowMain->repaint_daysUpdated( ret[0], ret[1] );
    m_cycleData->setCardModified( true );
}

/**
 * MnuResultsTemperature1stDayClick
 */
void nfpMainFrame::MnuResultsTemperature1stDayClick( wxCommandEvent& event )
{
    if ( ! doModifyLockedCard() ) return;

    int * ret = m_cycleData->setResultTemperatureLevels(m_config);
    if ( ret == NULL ) {
        showNotification(_("Setting result faild:") + m_cycleData->getErrorMessages());
        return;
    } else if ( !m_cycleData->getErrorMessages().IsEmpty() ) {
        showNotification(m_cycleData->getErrorMessages());
    }

    windowMain->repaint_daysUpdated( ret[0], ret[1] );
    m_cycleData->setCardModified( true );
}

/**
 * MnuResultsTemperatureResetClick
 */
void nfpMainFrame::MnuResultsTemperatureResetClick( wxCommandEvent& event )
{
    if ( ! doModifyLockedCard() ) return;

    int * ret = m_cycleData->resetResultTemperatureLevels();
    if ( ret == NULL ) {
        showNotification(_("Setting result faild:") + m_cycleData->getErrorMessages());
        return;
    }

    showNotification( wxString::Format(_("%i, %i"), ret[0], ret[1]));

    windowMain->repaint_daysUpdated( ret[0], ret[1] );
    m_cycleData->setCardModified( true );
}

/**
 * MnuResultsFertilePhaseStartClick
 */
void nfpMainFrame::MnuResultsFertilePhaseStartClick( wxCommandEvent& event )
{
    if ( ! doModifyLockedCard() ) return;

    int * ret = m_cycleData->setResultFertilePhaseStart();
    if ( ret == NULL ) {
        showNotification(_("Setting result faild:") + m_cycleData->getErrorMessages());
        return;
    }

    windowMain->repaint_daysUpdated( ret[0], ret[1] );
    m_cycleData->setCardModified( true );
}

/**
 * MnuResultsInfertilePhaseStartClick
 */
void nfpMainFrame::MnuResultsInfertilePhaseStartClick( wxCommandEvent& event )
{
    if ( ! doModifyLockedCard() ) return;

    int * ret = m_cycleData->setResultInfertilePhaseStart();
    if ( ret == NULL ) {
        showNotification(_("Setting result faild:") + m_cycleData->getErrorMessages());
        return;
    }

    windowMain->repaint_daysUpdated( ret[0], ret[1] );
    m_cycleData->setCardModified( true );
}

/******************************************************************************/

/**
 * Display the frame with statictic
 */
void nfpMainFrame::MnuStatStatisticsClick( wxCommandEvent& event )
{
    statisticsFrame *frame = new statisticsFrame(this, m_config, m_cycleData, 0);
    if ( frame->Show() == wxID_OK ) {
    } else { // something wrong
    }

    //frame->Destroy();
}



/**
 * Display histogram of length of cycles
 */
/*
void nfpMainFrame::MnuLengthOfCycleHist( wxCommandEvent& event )
{
    histogramsFrame *hist = new histogramsFrame(this, m_cycleData);
    if ( hist->ShowModal() == wxID_OK ) {
    } else { // something wrong
    }

    hist->Destroy();
}
*/

/******************************************************************************/
/**
 * Display histogram of temperature in cycles
 */
/*
void nfpMainFrame::MnuCycleHist( wxCommandEvent& event )
{


    cycleGraph *hist = new cycleGraph(this, m_cycleData);
    if ( hist->ShowModal() == wxID_OK ) {
    } else { // something wrong
    }

    hist->Destroy();
}
*/

/******************************************************************************/

/**
 * MnuHelpClick
 */
void nfpMainFrame::MnuHelpClick( wxCommandEvent& event )
{
    /*
    Offline help
    wxString helpUrl = m_util.getHelpUrl( _("en") );
    if (helpUrl == wxEmptyString) {
        helpUrl = wxString::Format( _( "%s%s?l=en" ), HOME_URL, ONLINE_DOC );
    }
    */

    // Online help
    wxLaunchDefaultBrowser( wxString::Format( _( "%s%s?l=en" ), HOME_URL, ONLINE_DOC ) );
}

/**
 * MnuHomePageClick
 */
void nfpMainFrame::MnuHomePageClick( wxCommandEvent& event )
{
    wxLaunchDefaultBrowser( wxString::Format( _( "%s?l=en" ), HOME_URL ) );
}

/**
 * MnuReportBugClick
 */
void nfpMainFrame::MnuReportBugClick( wxCommandEvent& event )
{
    wxLaunchDefaultBrowser( wxString::Format( _( "%s%s?l=en" ), HOME_URL, REPORT_BUG_PATH ) );
}

/**
 * MnuAboutClick
 */
void nfpMainFrame::MnuUpdatesClick( wxCommandEvent& event )
{
    checkForUpdates( true );
}

/**
 * MnuAboutClick
 */
void nfpMainFrame::MnuAboutClick( wxCommandEvent& event )
{
    m_parent->Show();
    m_parent->SetFocus();
}


/******************************************************************************/
/****** POPUP MENU ************************************************************/
/******************************************************************************/

/**
 * OnContextMenu
 */
void nfpMainFrame::OnContextMenu( wxContextMenuEvent& event )
{
    wxPoint point = event.GetPosition();
    point = ScreenToClient( point );

    int x1 = windowLeft->GetPosition().x + windowLeft->GetSize().GetX();
    int y1 = windowTop->GetPosition().y + windowTop->GetSize().GetY();

    if ( point.y <= y1 || point.x <= x1 ) {
        PopupMenu( menuCard );
    } else {
        PopupMenu( menuDayPopup );
    }
}


/******************************************************************************/
/****** OTHER METHODS *********************************************************/
/******************************************************************************/

/**
 * Set focus on the card frame.
 */
void nfpMainFrame::setFocusOnCardFrm()
{
    if ( m_cardFrm->IsShown() ) {

        m_cardFrm->SetFocus();
    }
}


/**
 * check if new version of application is available.
 */
void nfpMainFrame::checkForUpdates( bool showMessage )
{
    m_showNewAppMessage = showMessage;

    liveUpdateClass *checkUpdatesThread = new liveUpdateClass( this, m_config, true );
    if ( checkUpdatesThread->Create() != wxTHREAD_NO_ERROR ) {
        // ...
    }
    if ( checkUpdatesThread->Run() != wxTHREAD_NO_ERROR ) {
        // ...
    }
    menuHelp->Enable( ID_MNU_UPDATE, false );
    statusBar->SetStatusText( _( "Checking if new version of application is available." ) , 1 );
}

/**
 *
 */
void nfpMainFrame::setButtonsStyle()
{
    int flatButton = 0;
    int flatToolbar = 0;
    if ( m_config->useFlatButtons ) {
        flatButton = wxNO_BORDER;
        flatToolbar = wxTB_FLAT;
    }

    buttonNewDay->SetWindowStyle( flatButton );
    buttonAnalyzeCycle->SetWindowStyle( flatButton );
    toolBar->SetWindowStyle( flatToolbar );

    buttonNewDay->Refresh();
    buttonAnalyzeCycle->Refresh();
    toolBar->Refresh();
}


/**
 *
 */
void nfpMainFrame::updateAll()
{
    Refresh();
    //windowMain->repaint(-1, -1);
    //windowLeft->Refresh();
    //windowTop->Refresh();
    updateButtons();
}

/**
 *
 */
void nfpMainFrame::updateButtons()
{
    if ( m_cycleData->getActiveCard() == 1 ) {
        toolBar->EnableTool( ID_BUTTONPREVCARD, false );
        menuCard->Enable( ID_MNU_PREVIOUS_CARD, false );
    } else {
        toolBar->EnableTool( ID_BUTTONPREVCARD, true );
        menuCard->Enable( ID_MNU_PREVIOUS_CARD, true );
    }

    if ( m_cycleData->getActiveCard() == m_cycleData->getCardsCount() ) {
        toolBar->EnableTool( ID_BUTTONNEXTCARD, false );
        menuCard->Enable( ID_MNU_NEXT_CARD, false );
        menuCard->Enable( ID_MNU_DELETE_CARD, true );
        buttonNewDay->Enable( true );
    } else {
        toolBar->EnableTool( ID_BUTTONNEXTCARD, true );
        menuCard->Enable( ID_MNU_NEXT_CARD, true );
        menuCard->Enable( ID_MNU_DELETE_CARD, false );
        buttonNewDay->Enable( false );
    }

    if ( m_cycleData->getActiveCard() > 0 ) {
        if ( m_cycleData->getCard()->getCardLocked() ) {
            menuCard->Enable( ID_MNU_EDIT_CARD, false );
            menuCard->Enable( ID_MNU_DELETE_CARD, false );
            buttonNewDay->Enable( false );
            menuCard->Check( ID_MNU_CARD_LOCKED, true );
        } else {
            menuCard->Enable( ID_MNU_EDIT_CARD, true );
            menuCard->Check( ID_MNU_CARD_LOCKED, false );
        }
    }
}

/**
 *
 */
bool nfpMainFrame::askToSaveChanges( bool cancelAllowed )
{
    if ( checkCardAndDayFramesStates( true, cancelAllowed ) ) {
        if ( m_cycleData->getCardModified() ) {
            if (m_config->autosaveSet && !m_config->dataFileName.IsEmpty() ) {
                return saveChanges( false, cancelAllowed );
            }
            int answer;
            if ( cancelAllowed ) {
                answer = wxMessageBox( _( "Save changes in current cards' set to the file?" ), _( "Warning" ), wxYES_NO | wxCANCEL );
            } else {
                answer = wxMessageBox( _( "Save changes in current cards' set to the file?" ), _( "Warning" ), wxYES_NO );
            }
            if ( answer == wxCANCEL ) {
                return false;
            } else if ( answer == wxYES ) {
                return saveChanges( false, cancelAllowed );
            }
        }
    } else {
        return false;
    }
    return true;
}

/**
 *
 */
bool nfpMainFrame::saveChanges( bool forceNewFile, bool cancelAllowed )
{
    if ( checkCardAndDayFramesStates( false, true ) ) {
        if ( m_config->dataFileName.IsEmpty() || forceNewFile ) {

            wxString message = _( "Save cards' set as..." ) ;
            wxString default_path = wxEmptyString;
            wxString default_filename = wxEmptyString;
            wxString default_extension = wxEmptyString;
            wxString wildcard = _T( "*.nfpdata" );
            int flags = wxFD_SAVE | wxFD_OVERWRITE_PROMPT;

            if ( m_config->dataFileName.IsEmpty() ) {
                if ( !wxDirExists( m_util.getCardSetDataPath() ) ) {
                    wxFileName::Mkdir( m_util.getCardSetDataPath(), 0755, wxPATH_MKDIR_FULL );
                }
                default_path = m_util.getCardSetDataPath();
                default_filename = _( "new_set" );
                default_extension = _T( ".nfpdata" );
            } else {
                default_filename = m_config->dataFileName;
            }

            wxString filename = wxFileSelector( message, default_path, default_filename, default_extension, wildcard, flags, this );
            if ( !filename.empty() ) {
                // set extension of the file if it's missing
                if (filename.Find( _T( ".nfpdata" )) == -1)
                    filename << _T( ".nfpdata" );
                m_config->dataFileName = filename;
            } else {
                if ( cancelAllowed ) {
                    return false;
                } else {
                    return true;
                }
            }
        }

        if ( ! m_config->dataFileName.IsEmpty() && ( m_cycleData->getCardModified() || forceNewFile ) ) {
            if ( m_cycleData->saveCardsDataToFile( m_config->dataFileName ) ) {
                m_cycleData->setCardModified( false );
            } else {
                wxMessageBox( wxString::Format( _( "Error occured while saving data to file:\n%s" ), m_cycleData->getErrorMessages().c_str() ), _( "Error" ), wxOK | wxICON_ERROR );
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

/**
 * check if card or day frames are visible and if data have been modified, ask to save changes
 */
bool nfpMainFrame::checkCardAndDayFramesStates( bool closeFrame, bool cancelAllowed )
{
    if (closeFrame) {
        closeAnalysisResultNotification();
    }

    if ( !checkCardFrameState( closeFrame, cancelAllowed ) ) {
        return false;
    } else if ( ! checkDayFrameState( closeFrame, cancelAllowed ) ) {
        return false;
    } else {
        return true;
    }
}

/**
 * check if the day frame is visible and if data have been modified, ask to save changes
 */
bool nfpMainFrame::checkDayFrameState( bool closeFrame, bool cancelAllowed )
{
    if ( m_dayFrm->IsShown() ) {
        if ( m_dayFrm->checkIfDataHasBeenChanged( cancelAllowed ) ) {
            if ( closeFrame )
                m_dayFrm->Hide();
        } else {
            return false;
        }
    }
    return true;
}

/**
 * check if the card frame is visible and if data have been modified, ask to save changes
 */
bool nfpMainFrame::checkCardFrameState( bool closeFrame, bool cancelAllowed )
{
    if ( m_cardFrm->IsShown() ) {
        if ( m_cardFrm->checkIfCanExit( cancelAllowed ) ) {
            if ( closeFrame )
                m_cardFrm->Hide();
        } else {
            return false;
        }
    }
    return true;
}

/**
 * If config->checkForMissingDays and last card is not locked then
 * check if there are missing days (based on current date) on the card
 * and prompt to add them.
 */
bool nfpMainFrame::checkForMissingDays()
{
    if ( !m_config->checkForMissingDays ) {
        return true;
    }
    if ( m_cycleData->getActiveCard() < 1 ) {
        return true;
    }
    if ( m_cycleData->getCard()->getCardLocked() ) {
        return true;
    }

    wxDateTime lastDay = m_cycleData->getCard()->getFirstDayOfCycle();
    lastDay.Add( wxDateSpan::Days( m_cycleData->getCard()->getDaysCount() - 1 ) );
    wxDateTime today = wxDateTime::Today();

    int daysToAdd = getNumberOfDays( lastDay, today );
    if ( daysToAdd < 1 ) {
        return true;
    }


    int answer = wxMessageBox( wxString::Format( wxPLURAL( "%i day should be added to the current card to have on the card all days including today.\nDo you want me to add it now?", "%i days should be added to the current card to have on the card all days including today.\nDo you want me to add them now?", daysToAdd), daysToAdd), _( "Question" ), wxYES_NO );
    if ( answer == wxYES ) {
        bool ok = true;

        for ( int i = 0; i < daysToAdd; i++ ) {
            if ( m_cycleData->addNewDay() < 1 ) {
                ok = false;
            }
        }

        if ( ok ) {
            m_cycleData->setActiveDay( m_cycleData->getDaysCount() - daysToAdd + 1 );
            m_cycleData->setCardModified( true );
            m_config->checkCurrentDayVisibility = true;
            updateAll();
            m_dayFrm->update();
            m_dayFrm->Show();
        } else {
            wxMessageBox( _( "Error occured while adding new day" ), _( "Error" ), wxOK | wxICON_ERROR );
        }
    } else {

    }

    return true;
}


/**
 * get number of days between dateTime1 and dateTime2 (== dateTime2 - dateTime1)
 */
int nfpMainFrame::getNumberOfDays( wxDateTime dateTime1, wxDateTime dateTime2 )
{
    int year1  = dateTime1.GetYear();
    int month1 = dateTime1.GetMonth();
    int day1   = dateTime1.GetDay();
    int year2  = dateTime2.GetYear();
    int month2 = dateTime2.GetMonth();
    int day2   = dateTime2.GetDay();
    int daysNumber = 0;

    if ( year1 > year2 ) {

        return -1;
    }
    if ( year1 == year2 && month1 > month2 ) {

        return -1;
    }
    if ( year1 == year2 && month1 == month2 && day1 > day2 ) {

        return -1;
    }

    if ( year1 < year2 ) {
        daysNumber += wxDateTime::GetNumberOfDays(( wxDateTime::Month )( month1 ), year1, ( wxDateTime::Calendar )( 0 ) ) - day1;

        for ( int m = month1 + 1; m < 12; m++ ) {
            daysNumber += wxDateTime::GetNumberOfDays(( wxDateTime::Month )( m ), year1, ( wxDateTime::Calendar )( 0 ) );

        }
        for ( int y = year1 + 1; y < year2; y++ ) {
            for ( int m = 0; m < 12; m++ ) {
                daysNumber += wxDateTime::GetNumberOfDays(( wxDateTime::Month )( m ), y, ( wxDateTime::Calendar )( 0 ) );

            }
        }
        for ( int m = 0; m < month2; m++ ) {
            daysNumber += wxDateTime::GetNumberOfDays(( wxDateTime::Month )( m ), year2, ( wxDateTime::Calendar )( 0 ) );

        }
        daysNumber += day2;

    } else if ( month1 < month2 ) {
        daysNumber += wxDateTime::GetNumberOfDays(( wxDateTime::Month )( month1 ), year2, ( wxDateTime::Calendar )( 0 ) ) - day1;

        for ( int m = month1 + 1; m < month2; m++ ) {
            daysNumber += wxDateTime::GetNumberOfDays(( wxDateTime::Month )( m ), year2, ( wxDateTime::Calendar )( 0 ) );

        }
        daysNumber += day2;

    } else {
        daysNumber += day2 - day1;

    }

    return daysNumber;
}

void nfpMainFrame::showNotification( const wxString& message, int textAlign )
{
    wxPoint pos = GetPosition();
    pos.x += 10;
    pos.y += 130;
    //notificationFrame *frame = new notificationFrame( this, m_config, message, textAlign, pos, wxSize(300, 500) );
    notificationFrame *frame = new notificationFrame( this, m_config, message, textAlign, pos );
    frame->Show();
}

void nfpMainFrame::showAnalysisResultNotification( const wxString& message )
{
    m_notificationFrm->Destroy();
    wxPoint pos = GetPosition();
    pos.x += 10;
    pos.y += 130;
    m_notificationFrm = new notificationFrame( this, m_config, message, wxALIGN_LEFT, pos, true );
    m_notificationFrm->Show();
}

void nfpMainFrame::closeAnalysisResultNotification()
{
    if (m_notificationFrm->IsShown())
        m_notificationFrm->Hide();
}

/**
 * Check if card is protected agains changes:
 * - if not then return true
 * = if yes then ask user whether to modify it (return true) or not (return false).
 */
bool nfpMainFrame::doModifyLockedCard()
{
    if ( ! m_cycleData->getCard()->getCardLocked() )
        return true;

    if ( wxMessageBox( _( "Card is protected agains changes!\nDo you anyway want to updates results?" ) , _( "Warning" ), wxYES_NO ) == wxYES )
        return true;

    return false;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

void nfpMainFrame::informUserAboutChangesInThisRelease()
{
    // v. 0.9
    if (m_cycleData->isSexualRelationDataConverted()) {
        // make backup
        wxString path;
        wxString m_name;
        wxString ext;
        wxString backupFile;

        wxFileName::SplitPath( m_config->dataFileName, &path, &m_name, &ext );
        backupFile = path + wxFileName::GetPathSeparator() + m_name + _T( "_" ) + wxDateTime::Now().Format( _T( "%Y%m%d%H%M" ) ) + _T( "." ) + ext;
        wxCopyFile( m_config->dataFileName, backupFile );

        //inform user about changes
        wxString message = _("In this release the automatic interpretation of cycle data has been implemented.\nPlease read the documentation to understand how it works!");
        message << _("\n\nAlso the way how sexual relations are stored has been changed.\nInstead of storing number of sexual relations, you can now set\nthat there was a sexual relations in the morning, during the day and in the evening.\nBecause of that all existing data has been converted in following way:");
        message << _("\n- 1st reported sexual relation is now marked as 'in the evening'");
        message << _("\n- 2nd reported sexual relation is now marked as 'during the day'");
        if ( !m_cycleData->getSexualRelationDataConversionMessages2().IsEmpty() ) {
            message << _T(" (converted in: ") << m_cycleData->getSexualRelationDataConversionMessages2() << _T(")");
        }
        message << _("\n- 3rd reported sexual relation is now marked as 'in the evening'");
        if ( !m_cycleData->getSexualRelationDataConversionMessages3().IsEmpty() ) {
            message << _T(" (converted in: ") << m_cycleData->getSexualRelationDataConversionMessages3() << _T(")");
        }
        message << _("\n- 4th and other reported sexual relations reported for a day are not stored anymore");
        if ( !m_cycleData->getSexualRelationDataConversionMessages4().IsEmpty() ) {
            message << _T(":") << m_cycleData->getSexualRelationDataConversionMessages4() << _T(")");
        }
        message << _("\nLast file in previous format has been backed-up in:\n") << backupFile;
        m_cycleData->setCardModified( true );
        showNotification(message);
    }
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/
