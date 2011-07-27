/*******************************************************************************
//
// Name:        configClass.h
// Author:      enkeli
// Description:
//
*******************************************************************************/

#ifndef __CONFIG_CLASS__
#define __CONFIG_CLASS__

#include <wx/wx.h>
#include <wx/fileconf.h>
#include "utilClass.h"

#define LEFT   1
#define CENTER 2
#define RIGHT  3

#define MINCELLWIDTH   30
#define MAXDAYSONCARD 500

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
#define CONF_ENTRY_lastOpenedFileName _T( "lastOpenedFileName" )
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
#define CONF_ENTRY_fontResultHeart _T( "fontResultHeart" )
#define CONF_ENTRY_fontResultPhases _T( "fontResultPhases" )
#define CONF_ENTRY_fontHeadTopicColour _T( "fontHeadTopicColour" )
#define CONF_ENTRY_fontHeadNameColour _T( "fontHeadNameColour" )
#define CONF_ENTRY_fontHeadValueColour _T( "fontHeadValueColour" )
#define CONF_ENTRY_fontResultHeaderColour _T( "fontResultHeaderColour" )
#define CONF_ENTRY_fontResultDefaultColour _T( "fontResultDefaultColour" )
#define CONF_ENTRY_fontResultResultsColour _T( "fontResultResultsColour" )
#define CONF_ENTRY_fontResultHeartColour _T( "fontResultHeartColour" )
#define CONF_ENTRY_fontResultPhasesColour _T( "fontResultPhasesColour" )
#define CONF_ENTRY_coitusRecordCharacter _T("coitusRecordCharacter")
#define CONF_ENTRY_EXT_POINTSIZE _T( ".pointSize" )
#define CONF_ENTRY_EXT_FAMILY _T( ".family" )
#define CONF_ENTRY_EXT_STYLE _T( ".style" )
#define CONF_ENTRY_EXT_WEIGHT _T( ".weight" )
#define CONF_ENTRY_EXT_UNDERLINE _T( ".underline" )
#define CONF_ENTRY_EXT_FACENAME _T( ".faceName" )
#define CONF_ENTRY_EXT_ENCODING _T( ".encoding" )

/******************************************************************************/

// deprecated
WX_DECLARE_STRING_HASH_MAP( wxString, paramsHash );

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
class configClass {
     /** methods */
public:
     configClass(wxString);
     void setDefaultParams();
     void calculateParams();

public:
     bool readParamsFromConfigFile();
     // deprecated
     bool readParamsFromOldVersionOfConfigFile(wxString);
private:
     bool readParamsColour(wxConfigBase*, wxString, wxColour&);
     bool readParamsFont(wxConfigBase*, wxString, wxFont&);
     // deprecated code start
     void readString(paramsHash, wxString, wxString&);
     void readInt(paramsHash, wxString, int&);
     void readBool(paramsHash, wxString, bool&);
     void readColour(paramsHash, wxString, wxColour&);
     void readFont(paramsHash, wxString, wxFont&);
     // deprecated code end

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
     // PARAMETERS KEPT IN CONFIG FILE
     int langId;

     // true - start with last opened file, false - start with new file
     bool openLastOpenedFile;
     // currently opened file with cycles' data, or empty if not opened
     wxString dataFileName;

     bool openFileFromParams;

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
     wxFont fontResultHeart;
     wxFont fontResultPhases;

     wxColour fontHeadTopicColour;
     wxColour fontHeadNameColour;
     wxColour fontHeadValueColour;
     wxColour fontResultHeaderColour;
     wxColour fontResultDefaultColour;
     wxColour fontResultResultsColour;
     wxColour fontResultHeartColour;
     wxColour fontResultPhasesColour;

     wxChar coitusRecordCharacter;


     /**************************************************************************/
     // PARAMETERS NOT KEPT IN CONFIG FILE

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

     static const int rowsCountAboveTemp = 7;
     static const int rowsCountBelowTemp = 14;
     static const int rowNoCervixBelowTemp  = 7;

     int rowsCountTemp;
     int rowsCount;
     int rowNoCervix;
};

#endif
