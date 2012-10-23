/*******************************************************************************
//
// Name:        configClass.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#ifndef __CONFIG_CLASS__
#define __CONFIG_CLASS__

#include <wx/wx.h>
#include <wx/fileconf.h>
#include <wx/arrstr.h>
#include "utilClass.h"

#define LEFT   1
#define CENTER 2
#define RIGHT  3

#define MINCELLWIDTH   30
#define MAXDAYSONCARD 500

#define RULE_2120 1
#define RULE_CLINICAL 2
#define RULE_DOERING 3
#define RULE_CERVICAL_MUCUS_BASED 4
#define RULE_CERVICAL_POSITION_BASED 5

#define RULE_2120_string _("21/20 days rule")
#define RULE_CLINICAL_string _("clinical rule")
#define RULE_DOERING_string _("Döring rule")
#define RULE_CERVICAL_MUCUS_BASED_string _("cervical mucus based rule")
#define RULE_CERVICAL_POSITION_BASED_string _("cervical mucus position rule")


/******************************************************************************/

/* GENERAL */
#define CONF_PATH_general _T( "/general/" )
#define CONF_ENTRY_langId _T( "langId" )
#define CONF_ENTRY_language _T( "language" )
#define CONF_ENTRY_rememberPosition _T( "rememberPosition" )
#define CONF_ENTRY_formMainMaximized _T( "formMainMaximized" )
#define CONF_ENTRY_formMainHeight _T( "formMainHeight" )
#define CONF_ENTRY_formMainWidth _T( "formMainWidth" )
#define CONF_ENTRY_formMainLeft _T( "formMainLeft" )
#define CONF_ENTRY_formMainTop _T( "formMainTop" )
#define CONF_ENTRY_formDayLeft _T( "formDayLeft" )
#define CONF_ENTRY_formDayTop _T( "formDayTop" )
#define CONF_ENTRY_formCardLeft _T( "formCardLeft" )
#define CONF_ENTRY_formCardTop _T( "formCardTop" )
#define CONF_ENTRY_widowLeftWidth _T( "widowLeftWidth" )
#define CONF_ENTRY_windowTopHeight _T( "windowTopHeight" )
#define CONF_ENTRY_useFlatButtons _T( "useFlatButtons" )
#define CONF_ENTRY_useCoitusRecordCounter _T( "useCoitusRecordCounter" )
#define CONF_ENTRY_checkForUpdates _T( "checkForUpdates" )
#define CONF_ENTRY_updatesProxy _T( "updatesProxy" )

/* APPLICATION */
#define CONF_PATH_application _T( "/application/" )
#define CONF_ENTRY_openLastOpenedFile _T( "openLastOpenedFile" )
#define CONF_ENTRY_syncFileAutomatically _T( "syncFileAutomatically" )
#define CONF_ENTRY_password _T( "password" )
#define CONF_ENTRY_rememberPassword _T( "rememberPassword" )
#define CONF_ENTRY_useCustomServer _T( "useCustomServer" )
#define CONF_ENTRY_customServerUri _T( "customServerUri" )
#define CONF_ENTRY_autosaveChanges _T( "autosaveChanges" )
#define CONF_ENTRY_autosaveSet _T( "autosaveSet" )
#define CONF_ENTRY_lastOpenedFileName _T( "lastOpenedFileName" )
#define CONF_ENTRY_EXT_ENCODING _T( ".encoding" )
#define CONF_ENTRY_PREFIX_previouslyOpenedFileNames _T( "previouslyOpenedFileName." )
#define CONF_ENTRY_checkForMissingDays _T( "checkForMissingDays" )
#define CONF_ENTRY_breastSelfControlReminderDay _T( "breastSelfControlReminderDay" )
#define CONF_ENTRY_breastSelfControlInterval _T( "breastSelfControlInterval" )
#define CONF_ENTRY_breastSelfControlLastReminder _T( "breastSelfControlLastReminder" )
#define CONF_ENTRY_lengthInCentimeters _T( "lengthInCentimeters" )
#define CONF_ENTRY_temperatureInCelsius _T( "temperatureInCelsius" )
#define CONF_ENTRY_temperatureRangeLow _T( "temperatureRangeLow" )
#define CONF_ENTRY_temperatureRangeHigh _T( "temperatureRangeHigh" )

/* COLOURS */
#define CONF_PATH_colours _T( "/colours/" )
#define CONF_ENTRY_colourBackground _T( "colourBackground" )
#define CONF_ENTRY_colourCell11 _T( "colourCell11" )
#define CONF_ENTRY_colourCell12 _T( "colourCell12" )
#define CONF_ENTRY_colourCell21 _T( "colourCell21" )
#define CONF_ENTRY_colourCell22 _T( "colourCell22" )
#define CONF_ENTRY_colourMarkedCell1 _T( "colourMarkedCell1" )
#define CONF_ENTRY_colourMarkedCell2 _T( "colourMarkedCell2" )
#define CONF_ENTRY_colourPointNormal _T( "colourPointNormal" )
#define CONF_ENTRY_colourPointBefore _T( "colourPointBefore" )
#define CONF_ENTRY_colourPointAfter _T( "colourPointAfter" )
#define CONF_ENTRY_colourTemperatureLine _T( "colourTemperatureLine" )
#define CONF_ENTRY_colourTemperatureLevelLine _T( "colourTemperatureLevelLine" )
#define CONF_ENTRY_colourPhaseLine _T( "colourPhaseLine" )
#define CONF_ENTRY_colourBorders _T( "colourBorders" )
#define CONF_ENTRY_colourMarkedBorders _T( "colourMarkedBorders" )
#define CONF_ENTRY_EXT_RED _T( ".red" )
#define CONF_ENTRY_EXT_GREEN _T( ".green" )
#define CONF_ENTRY_EXT_BLUE _T( ".blue" )

/* FONTS */
#define CONF_PATH_fonts _T( "/fonts/" )
#define CONF_ENTRY_fontHeadTopic _T( "fontHeadTopic" )
#define CONF_ENTRY_fontHeadName _T( "fontHeadName" )
#define CONF_ENTRY_fontHeadValue _T( "fontHeadValue" )
#define CONF_ENTRY_fontResultHeader _T( "fontResultHeader" )
#define CONF_ENTRY_fontResultDefault _T( "fontResultDefault" )
#define CONF_ENTRY_fontResultResults _T( "fontResultResults" )
#define CONF_ENTRY_fontResultPhases _T( "fontResultPhases" )
#define CONF_ENTRY_fontHeadTopicColour _T( "fontHeadTopicColour" )
#define CONF_ENTRY_fontHeadNameColour _T( "fontHeadNameColour" )
#define CONF_ENTRY_fontHeadValueColour _T( "fontHeadValueColour" )
#define CONF_ENTRY_fontResultHeaderColour _T( "fontResultHeaderColour" )
#define CONF_ENTRY_fontResultDefaultColour _T( "fontResultDefaultColour" )
#define CONF_ENTRY_fontResultResultsColour _T( "fontResultResultsColour" )
#define CONF_ENTRY_fontResultPhasesColour _T( "fontResultPhasesColour" )
#define CONF_ENTRY_EXT_POINTSIZE _T( ".pointSize" )
#define CONF_ENTRY_EXT_FAMILY _T( ".family" )
#define CONF_ENTRY_EXT_STYLE _T( ".style" )
#define CONF_ENTRY_EXT_WEIGHT _T( ".weight" )
#define CONF_ENTRY_EXT_UNDERLINE _T( ".underline" )
#define CONF_ENTRY_EXT_FACENAME _T( ".faceName" )
#define CONF_ENTRY_EXT_ENCODING _T( ".encoding" )

/* ANALYSIS */
#define CONF_PATH_analysis _T( "/analysis/" )
#define CONF_ENTRY_autoanalyzeCard _T( "autoanalyzeCard" )
#define CONF_ENTRY_showAutoanalysisDetails _T( "showAutoanalysisDetails" )
#define CONF_ENTRY_maxAllowedNotMesuredLowLevelDays _T( "maxAllowedNotMesuredLowLevelDays" )
#define CONF_ENTRY_maxIncludedNotMesuredLowLevelDays _T( "maxIncludedNotMesuredLowLevelDays" )
#define CONF_ENTRY_maxAllowedNotMesuredHighLevelDays _T( "maxAllowedNotMesuredHighLevelDays" )
#define CONF_ENTRY_maxIncludedNotMesuredHighLevelDays _T( "maxIncludedNotMesuredHighLevelDays" )
#define CONF_ENTRY_includeNotMesuredDaysIfAfterMucusPeak _T( "includeNotMesuredDaysIfAfterMucusPeak" )
#define CONF_ENTRY_numberOfHistoricalCyclesToUse _T( "numberOfHistoricalCyclesToUse" )
#define CONF_ENTRY_autoanalyzeCardPreferResult1 _T( "autoanalyzeCardPreferResult1" )
#define CONF_ENTRY_autoanalyzeCardPreferResult2 _T( "autoanalyzeCardPreferResult2" )
#define CONF_ENTRY_autoanalyzeCardPreferResult3 _T( "autoanalyzeCardPreferResult3" )
#define CONF_ENTRY_autoanalyzeCardPreferResult4 _T( "autoanalyzeCardPreferResult4" )
#define CONF_ENTRY_autoanalyzeCardPreferResult5 _T( "autoanalyzeCardPreferResult5" )


/******************************************************************************/

// deprecated
WX_DECLARE_STRING_HASH_MAP( wxString, paramsHash );

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
class configClass
{
    /** methods */
public:
    configClass(wxString);
    void setDefaultParams();
    void calculateParams();
    void instertCurrentlyOpenedFileNameToHistory();

public:
    bool readParamsFromConfigFile();
private:
    bool readParamsColour(wxConfigBase*, wxString, wxColour&);
    bool readParamsFont(wxConfigBase*, wxString, wxFont&);

public:
    bool saveParamsToConfigFile();
private:
    bool saveParamColour(wxConfigBase*, wxString, wxColour);
    bool saveParamFont(wxConfigBase*, wxString, wxFont);

    /**************************************************************************/
    /** variables */
private:

    utilClass m_util;
    wxString m_configFile;

public:
    // PARAMETERS SAVED IN CONFIG FILE
    int langId;

    // true - start with last opened file, false - start with new file
    bool openLastOpenedFile;
    bool autosaveChanges;
    bool autosaveSet;

    // currently opened file with cycles' data, or empty if not opened
    wxString dataFileName;
    wxArrayString previouslyOpenedFileNames;

    // saving file on server
    bool syncFileAutomatically;
    wxString password;
    bool rememberPassword;
    bool useCustomServer;
    wxString customServerUri;

    // true - prompt to add to the last card (if it's not locked) missing days (based on current date)
    bool checkForMissingDays;

    //
    bool checkForUpdates;
    wxString updatesProxy;

    // sizes and positions of frames
    bool rememberPosition;
    bool formMainMaximized;
    int formMainHeight;
    int formMainWidth;
    int formMainLeft;
    int formMainTop;
    int formDayLeft;
    int formDayTop;
    int formCardLeft;
    int formCardTop;
    //
    bool useFlatButtons;
    bool useCoitusRecordCounter;

    // if < 1 then do not remind about self-control of breast
    int breastSelfControlReminderDay;
    // if cycle is longer than 'breastSelfControlReminder' + 'breastSelfControlInterval' then remind again
    int breastSelfControlInterval;
    // day, when the reminder has been shown last time.
    wxDateTime breastSelfControlLastReminder;

    // analyze card after each change
    bool autoanalyzeCard;
    bool showAutoanalysisDetails;
    // temperature graph
    int maxAllowedNotMesuredLowLevelDays;
    int maxIncludedNotMesuredLowLevelDays;
    int maxAllowedNotMesuredHighLevelDays;
    int maxIncludedNotMesuredHighLevelDays;
    bool includeNotMesuredDaysIfAfterMucusPeak;
    // calculating beginning of the fertile phase
    int numberOfHistoricalCyclesToUse;
    int autoanalyzeCardPreferResult1;
    int autoanalyzeCardPreferResult2;
    int autoanalyzeCardPreferResult3;
    int autoanalyzeCardPreferResult4;
    int autoanalyzeCardPreferResult5;


    bool lengthInCentimeters;
    bool temperatureInCelsius;

    // temperatures' range displayed on the graph
    int temperatureRangeHigh; // temperatureRangeHigh
    int temperatureRangeLow; // temperatureRangeLow

    /**************************************************************************/
    // colours
    wxColour colourBackground;
    wxColour colourCell11;
    wxColour colourCell12;
    wxColour colourCell21;
    wxColour colourCell22;
    wxColour colourMarkedCell1;
    wxColour colourMarkedCell2;
    wxColour colourPointNormal;
    wxColour colourPointBefore;
    wxColour colourPointAfter;
    wxColour colourTemperatureLine;
    wxColour colourTemperatureLevelLine;
    wxColour colourPhaseLine;
    wxColour colourBorders;
    wxColour colourMarkedBorders;

    /**************************************************************************/
    // fonts
    bool showColoursDialogForFonts;
    wxFont fontHeadTopic;
    wxFont fontHeadName;
    wxFont fontHeadValue;
    wxFont fontResultHeader;
    wxFont fontResultDefault;
    wxFont fontResultResults;
    wxFont fontResultPhases;

    wxColour fontHeadTopicColour;
    wxColour fontHeadNameColour;
    wxColour fontHeadValueColour;
    wxColour fontResultHeaderColour;
    wxColour fontResultDefaultColour;
    wxColour fontResultResultsColour;
    wxColour fontResultPhasesColour;

    /**************************************************************************/
    // PARAMETERS NOT SAVED IN CONFIG FILE

    // true
    bool openFileFromParams;

    // przesuniecie w pionie
    // verticalDisplacement == (-xxxx - 0)
    int verticalDisplacement;

    // if true than check if the [current day | first day | last day] is visible on the screen
    bool checkCurrentDayVisibility;
    bool checkFirstDayVisibility;
    bool checkLastDayVisibility;

    // additionalNote which is currently visible, or empty string
    wxString visibleNote;

    // True means that the warning "you need to restart the application" has been already printed.
    // It's the information for other components which wanted to print the same warning.
    bool warningShown;

    /**************************************************************************/
    /** cells heights and widths */

    // off-line - if changed then application has to be restarted
    int widowLeftWidth;

    // off-line - if changed then application has to be restarted
    int windowTopHeight;

    static const int rowsCountAboveTemp = 6;
    static const int rowsCountBelowTemp = 14;
    static const int rowNoCervixBelowTemp  = 7;

    int rowsCountTemp;
    int rowsCount;
    int rowNoCervix;
};

#endif
