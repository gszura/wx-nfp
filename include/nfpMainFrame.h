#ifndef HEADER_4081C4F6D602A2DC
#define HEADER_4081C4F6D602A2DC

/*******************************************************************************
//
// Name:        nfpMainFrame.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef __NFP_MAIN_FRAME__
#define __NFP_MAIN_FRAME__

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/frame.h>
#else
#include <wx/wxprec.h>
#include <wx/wxprec.h>
#endif

#include <wx/printdlg.h>
#include <wx/cmndata.h>
#include <wx/filedlg.h>
#include <wx/fontdlg.h>
#include <wx/menu.h>
#include <wx/button.h>
#include <wx/toolbar.h>
#include <wx/scrolbar.h>
#include <wx/scrolwin.h>
#include <wx/panel.h>
#include <wx/timer.h>
#include <vector>
#include <wx/log.h>

#include "customWindowMain.h"
#include "customWindowLeft.h"
#include "customWindowTop.h"
#include "configClass.h"
#include "cyclesData.h"
#include "utilClass.h"
#include "cardFrame.h"
#include "dayFrame.h"
#include "wxHttpThread.h"
#include "updatesNotificationForm.h"
#include "notificationFrame.h"
#include "IOoperations.h"


#undef nfpMainFrame_STYLE
#define nfpMainFrame_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX | wxCLIP_CHILDREN

/*******************************************************************************
********************************************************************************
*******************************************************************************/

class nfpMainFrame : public wxFrame
{
private:
    DECLARE_EVENT_TABLE();

public:
    nfpMainFrame(wxWindow *parent, configClass *config, wxWindowID id = 1, const wxString &title = _("NFP"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = nfpMainFrame_STYLE);
    virtual ~nfpMainFrame();

public:
    wxMenuBar *menuBarMain;
    wxMenu *menuNfp;
    wxMenu *menuOpenedCardHistory;
    wxMenu *menuCard;
    wxMenu *menuDay;
    wxMenu *menuResults;
    wxMenu *menuResultsMarkDayAs;
    wxMenu *menuMoveDays;
    wxMenu *menuStats;
    wxMenu *menuHelp;
    wxMenu *menuDayPopup;

    wxToolBar *toolBar;
    wxButton *buttonNewDay;
    wxButton *buttonAnalyzeCycle;

    wxStatusBar *statusBar;
    wxScrollBar *scrollBarVertical;
    wxPanel *panelMain;
    wxTimer *timerMain;
    wxTimer *timerNotification;

    customWindowLeft *windowLeft;
    customWindowMain *windowMain;
    customWindowTop *windowTop;

    wxBoxSizer *WxBoxSizer3;
    wxBoxSizer *WxBoxSizer2;
    wxBoxSizer *WxBoxSizer1;

    /**************************************************************************/
public:
    enum {
        ID_MNU_NFP = 1000,
        ID_MNU_NEW_SET,
        ID_MNU_OPEN_SET,
        ID_MNU_SAVE_SET,
        ID_MNU_SAVE_SET_AS,
        ID_MNU_SEPARATOR_11,
        ID_MNU_ENABLE_SYNC,
        ID_MNU_AUTO_SYNC,
        ID_MNU_SYNC_NOW,
        ID_MNU_SEPARATOR_12,
        ID_MNU_PRINT,
        ID_MNU_PRINT_PREVIEW,
        ID_MNU_PRINT_PAGE_SETUP,
        ID_MNU_SEPARATOR_13,
        ID_MNU_OPTIONS,
        ID_MNU_SEPARATOR_14,
        ID_MNU_SEPARATOR_15,
        ID_MNU_EXIT,
        ID_MNU_CARD,
        ID_MNU_PREVIOUS_CARD,
        ID_MNU_NEXT_CARD,
        ID_MNU_GO_TO_CARD,
        ID_MNU_SEPARATOR_21,
        ID_MNU_EDIT_CARD,
        ID_MNU_DELETE_CARD,
        ID_MNU_CARD_LOCKED,
        ID_MNU_CARD_CORRUPTED,
        ID_MNU_SEPARATOR_22,
        ID_MNU_NEW_CARD,
        ID_MNU_RESULTS_MARK_DAYS_AS,
        ID_MNU_RESULTS_AUTOCALCULATE,
        ID_MNU_RESULTS_AUTOCALCULATE_ON_CHANGE,
        ID_MNU_RESULTS_CHANGE_SETTINGS,
        ID_MNU_DAY,
        ID_MNU_DAY_NO,
        ID_MNU_SEPARATOR_31,
        ID_MNU_EDIT_DAY,
        ID_MNU_DELETE_DAY,
        ID_MNU_SEPARATOR_32,
        ID_MNU_NEW_DAY,
        ID_MNU_RESULTS,
        ID_MNU_RESULTS_MUCUS_1ST_DAY,
        ID_MNU_RESULTS_MUCUS_1ST_DAY_FERTILE,
        ID_MNU_RESULTS_MUCUS_PEAK_DAY,
        ID_MNU_RESULTS_CERVIX_1ST_DAY,
        ID_MNU_RESULTS_CERVIX_PEAK_DAY,
        ID_MNU_RESULTS_TEMPERATURE_1ST_DAY,
        ID_MNU_RESULTS_TEMPERATURE_RESET,
        ID_MNU_RESULTS_FERTILE_PHASE_START,
        ID_MNU_RESULTS_INFERTILE_PHASE_START,
        ID_MNU_SEPARATOR_33,
        ID_MNU_MOVE_DAYS,
        ID_MNU_MOVE_DAYS_TO_PREV_CARD,
        ID_MNU_MOVE_DAYS_TO_NEXT_CARD,
        ID_MNU_STAT_STATICTICS,
        ID_MNU_HELP_MENU,
        ID_MNU_HELP,
        ID_MNU_HOME_PAGE,
        ID_MNU_REPORT_BUG,
        ID_MNU_UPDATE,
        ID_MNU_ABOUT,

        ID_STATUSBAR,
        ID_BUTTONNEXTCARD,
        ID_BUTTONPREVCARD,
        ID_BUTTONNEWDAY,
        ID_BUTTONANALYZECYCLE,
        ID_BUTTONSAVESET,
        ID_BUTTONSYNCSET,
        ID_TOOLBAR,

        ID_WINDOWMAIN,
        ID_WINDOWLEFT,
        ID_WINDOWTOP,
        ID_PANELMAIN,
        ID_SCROLLBARVERTICAL,
        ID_TIMERMAIN,
        ID_TIMERNOTIFICATION,
        ID_thread,

        ID_MNU_OPENED_CARD_HISTORY_CLEAR = 9900,
        ID_MNU_OPENED_CARD_HISTORY,

        ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
    };
    /**************************************************************************/
private:
    void CreateGUIControls(void);
    void updateRecentCardsMenu();

    void newAppAvailableEvent( wxCommandEvent& event);
    void newAppDownloadedEvent( wxCommandEvent& event);
    void configDataModifiedEvent( wxCommandEvent& event);
    void cardDataModifiedEvent( wxCommandEvent& event);
    void dayDataModifiedEvent( wxCommandEvent& event);

    void nfpMainFrameClose(wxCloseEvent& event);
    void nfpMainFrameMouseWheel(wxMouseEvent& event);
    void nfpMainFrameSize(wxSizeEvent& event);
    void scrollBarVerticalScroll(wxScrollEvent& event);
    void timerMainTimer(wxTimerEvent& event);
    void timerNotificationTimer(wxTimerEvent& event);
    void runUpdateProgram(bool);

    /**************************************************************************/
    // TOOLBAR
    void prevCardClick(wxCommandEvent& event);
    void nextCardClick(wxCommandEvent& event);
    void newDayClick(wxCommandEvent& event);

    /**************************************************************************/
    // MAIN MENU
    void MnuActivated(wxMenuEvent& event);

    void MnuNewSetClick(wxCommandEvent& event);
    void MnuOpenSetClick(wxCommandEvent& event);
    void MnuOpenCardFromHistoryClick(wxCommandEvent& event);
    void MnuClearCardHistoryClick(wxCommandEvent& event);
    void MnuSaveSetClick(wxCommandEvent& event);
    void MnuSaveSetAsClick(wxCommandEvent& event);
    void MnuEnableSyncClick(wxCommandEvent& event);
    void MnuAutoSyncClick(wxCommandEvent& event);
    void MnuSyncNowClick(wxCommandEvent& event);
    void MnuPrintClick(wxCommandEvent& event);
    void MnuPrintPreviewClick(wxCommandEvent& event);
    void MnuPrintPageSetupClick(wxCommandEvent& event);
    void MnuOptionsClick(wxCommandEvent& event);
    void MnuExitClick(wxCommandEvent& event);

    void MnuPreviousCardClick(wxCommandEvent& event);
    void MnuNextCardClick(wxCommandEvent& event);
    void MnuGoToCardClick(wxCommandEvent& event);
    void MnuEditCardClick(wxCommandEvent& event);
    void MnuDeleteCardClick(wxCommandEvent& event);
    void MnuCardLockedClick(wxCommandEvent& event);
    void MnuCardCorruptedClick(wxCommandEvent& event);
    void MnuNewCardClick(wxCommandEvent& event);

    void MnuEditDayClick(wxCommandEvent& event);
    void MnuDeleteDayClick(wxCommandEvent& event);
    void MnuNewDayClick(wxCommandEvent& event);
    void MnuMoveDaysToPrevCardClick(wxCommandEvent& event);
    void MnuMoveDaysToNextCardClick(wxCommandEvent& event);

    void MnuResultsMucus1stDayClick(wxCommandEvent& event);
    void MnuResultsMucus1stDayFertileClick(wxCommandEvent& event);
    void MnuResultsMucusPeakDayClick(wxCommandEvent& event);
    void MnuResultsCervix1stDayClick(wxCommandEvent& event);
    void MnuResultsCervixPeakDayClick(wxCommandEvent& event);
    void MnuResultsTemperature1stDayClick(wxCommandEvent& event);
    void MnuResultsTemperatureResetClick(wxCommandEvent& event);
    void MnuResultsFertilePhaseStartClick(wxCommandEvent& event);
    void MnuResultsInfertilePhaseStartClick(wxCommandEvent& event);
    void MnuResultsAutocalculateClick(wxCommandEvent& event);
    void MnuResultsAutocalculateOnChangeClick(wxCommandEvent& event);
    void MnuResultsChangeAnalysisSettingsClick(wxCommandEvent& event);

    void MnuStatStatisticsClick(wxCommandEvent& event);
    void MnuLengthOfCycleHist(wxCommandEvent& event);
    void MnuCycleHist(wxCommandEvent& event);

    void MnuHelpClick(wxCommandEvent& event);
    void MnuHomePageClick(wxCommandEvent& event);
    void MnuReportBugClick(wxCommandEvent& event);
    void MnuUpdatesClick(wxCommandEvent& event);
    void MnuAboutClick(wxCommandEvent& event);

    /**************************************************************************/
    // POPUP MENU
    void OnContextMenu(wxContextMenuEvent& event);


private:
    cardFrame *m_cardFrm;
    dayFrame *m_dayFrm;
    notificationFrame *m_notificationFrm;

    bool m_initCard;
    wxWindow *m_parent;
    configClass *m_config;
    cycleDataClass *m_cycleData;
    utilClass m_util;
    bool m_showNewAppMessage;
    int m_newAppStatusMessage;

    wxHttpThread *m_checkUpdatesThread;
    updatesNotificationForm *m_updatesNotificationFrame;
    bool m_doUpdateOnExit;
    wxString m_newAppSetupFile;
    //bool m_doCheckForMissingDays;

    // variables needed to monitor if the frame title needs to be updated.
    wxString m_dataFileNamePrev;
    bool m_cardModifiedPrev;
    wxString m_serverDataFileNamePrev;
    bool m_serverFileNotInSyncPrev;

    // PRINTING
    // print data, to remember settings during the session
    wxPrintData *m_printData;

    // page setup data
    wxPageSetupData* m_pageSetupData;

public:
    void setFocusOnCardFrm();
    void checkForUpdates(bool);
    void setLanguage();
    void setButtonsStyle();
    void updateAll();
    void updateButtons();
    bool checkCardAndDayFramesStates(bool, bool);
    bool checkDayFrameState(bool, bool);
    bool checkCardFrameState(bool, bool);
    bool checkForMissingDays();
    void showNotification( const wxString& message, int textAlign = wxALIGN_LEFT );
    void showAnalysisResultNotification( const wxString&);
    void closeAnalysisResultNotification();

private:
    bool doModifyLockedCard();
    void informUserAboutChangesInThisRelease();


    /** FILE: nfpMainFrame_io_operations.cpp */
public:
    void readLastOpenedCard();
    bool readCard();
    bool askToSaveCard(bool);
    bool saveCard(bool forceNewFile, bool cancelAllowed);
    bool saveCardWithInitialSync();
    bool syncCard();
    bool removeCardFromServer(wxString syncServerName = wxEmptyString);
    bool moveCardToNewSyncServer();
    wxString getSyncServerName();
};

#endif

#endif // header guard
