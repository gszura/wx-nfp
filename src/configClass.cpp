/*******************************************************************************
//
// Name:        configClass.cpp
// Author:      enkeli
// Description:
//
*******************************************************************************/

#include "configClass.h"
#include "wx-nfpAppInfo.h"
//#include <wx/filename.h>
//#include <wx/defs.h>

// deprecated
#include <wx/ffile.h>

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
configClass::configClass( wxString configFile )
{
    m_configFile = configFile;
    verticalDisplacement = 0;
    langId = -1;
    checkCurrentDayVisibility = false;
    checkFirstDayVisibility = false;
    checkLastDayVisibility = false;
    visibleNote = _T( "" );
    warningShown = false;
    dataFileName = _T( "" );
    openFileFromParams = false;
    useCoitusRecordCounter = false;

    setDefaultParams();
}

/**
 * odpalane przy starcie programu, oraz gdy wybrano przycisk "przywroc domyslne" w oknie konfiguracji.
 */
void configClass::setDefaultParams()
{


    // ogolne
    openLastOpenedFile = true;
    rememberPosition = true;
    checkForMissingDays = true;
#if defined(__WXMSW__)
    checkForUpdates = true;
#else
    checkForUpdates = false;
#endif
    updatesProxy = _T( "" );
    formMainMaximized = false;
    formMainHeight = 650;
    formMainWidth  = 800;
    formMainLeft   = 30;
    formMainTop    = 30;
    formDayLeft    = 50;
    formDayTop     = 100;
    formCardLeft   = 50;
    formCardTop    = 100;

#if defined(__UNIX__)
    useFlatButtons = false;
#else
    useFlatButtons = true;
#endif

    widowLeftWidth = 150; // off-line
    windowTopHeight = 40; // off-line

    breastSelfControlReminderDay = 6;
    breastSelfControlInterval = 30;
    breastSelfControlLastReminder = wxDateTime::Today();
    breastSelfControlLastReminder.Subtract( wxDateSpan::Days( breastSelfControlInterval + 1 ) );

    lengthInCentimeters = true;

    // wykres
    temperatureInCelsius = true;
    temperatureRangeLow  = 3620;
    temperatureRangeHigh  = 3710;

    //----------------------------
    // kolory
    colourBackground = wxColour( 255, 255, 255 );
    colourCell11 = wxColour( 240, 240, 255 );
    colourCell12 = wxColour( 220, 220, 255 );
    colourCell21 = wxColour( 255, 255, 255 );
    colourCell22 = wxColour( 230, 230, 255 );
    colourMarkedCell1 = wxColour( 213, 213, 253 );
    colourMarkedCell2 = wxColour( 179, 179, 251 );
    colourPointNormal = wxColour( 0, 0, 0 );
    colourPointBefore = wxColour( 255, 0, 0 );
    colourPointAfter = wxColour( 0, 255, 0 );
    colourTemperatureLine = wxColour( 0, 0, 0 );
    colourTemperatureLevelLine = wxColour( 255, 64, 255 );
    colourPhaseLine = wxColour( 148, 235, 174 );
    colourBorders = wxColour( 0, 0, 255 );
    colourMarkedBorders = wxColour( 255, 0, 0 );

    // fonty
#if defined(__UNIX__)
    showColoursDialogForFonts = true;
    fontHeadTopic = wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false );
    fontHeadName = wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );
    fontHeadValue = wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
    fontResultHeader = wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false );
    fontResultDefault = wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );
    fontResultResults = wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );
    fontResultHeart = wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );
    fontResultPhases = wxFont( 14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );

    /*
    fontHeadTopic = wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT( "Sans" ), wxFONTENCODING_UTF8 );
    fontHeadName = wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Sans" ), wxFONTENCODING_UTF8 );
    fontHeadValue = wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT( "Sans" ), wxFONTENCODING_UTF8 );
    fontResultHeader = wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT( "Sans" ), wxFONTENCODING_UTF8 );
    fontResultDefault = wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Sans" ), wxFONTENCODING_UTF8 );
    fontResultResults = wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Sans" ), wxFONTENCODING_UTF8 );
    fontResultHeart = wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Sans" ), wxFONTENCODING_UTF8 );
    fontResultPhases = wxFont( 14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Sans" ), wxFONTENCODING_UTF8 );
    */

#else
    showColoursDialogForFonts = false;
    fontHeadTopic = wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false );
    fontHeadName = wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );
    fontHeadValue = wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false );
    fontResultHeader = wxFont( 7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false );
    fontResultDefault = wxFont( 7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );
    fontResultResults = wxFont( 7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );
    fontResultHeart = wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Symbol" ) );
    fontResultPhases = wxFont( 14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );

    /*
    fontHeadTopic = wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT( "Arial" ) );
    fontHeadName = wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Arial" ) );
    fontHeadValue = wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT( "Arial" ) );
    fontResultHeader = wxFont( 7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT( "Arial" ) );
    fontResultDefault = wxFont( 7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Arial" ) );
    fontResultResults = wxFont( 7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Arial" ) );
    fontResultHeart = wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Symbol" ) );
    fontResultPhases = wxFont( 14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Arial" ) );
    */

    /*
    fontHeadTopic = wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT( "Arial" ), wxFONTENCODING_CP1250 );
    fontHeadName = wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Arial" ), wxFONTENCODING_CP1250 );
    fontHeadValue = wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT( "Arial" ), wxFONTENCODING_CP1250 );
    fontResultHeader = wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT( "Arial" ), wxFONTENCODING_CP1250 );
    fontResultDefault = wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Arial" ), wxFONTENCODING_CP1250 );
    fontResultResults = wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Arial" ), wxFONTENCODING_CP1250 );
    fontResultHeart = wxFont( 8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Symbol" ), wxFONTENCODING_CP1250 );
    fontResultPhases = wxFont( 14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT( "Arial" ), wxFONTENCODING_CP1250 );
    */
#endif

    fontHeadTopicColour = wxColour( 128, 0, 0 );
    fontHeadNameColour = wxColour( 0, 0, 128 );
    fontHeadValueColour = wxColour( 0, 0, 128 );
    fontResultHeaderColour = wxColour( 0, 0, 0 );
    fontResultDefaultColour = wxColour( 0, 0, 0 );
    fontResultResultsColour = wxColour( 255, 0, 255 );
    fontResultHeartColour = wxColour( 0, 0, 0 );
    fontResultPhasesColour = wxColour( 0, 255, 0 );

#if defined(__UNIX__)
    coitusRecordCharacter = 0x56;
#else
    coitusRecordCharacter = 0xA9;
#endif

    calculateParams();
}

/**
 *
 */
void configClass::calculateParams()
{
    rowsCountTemp = ( temperatureRangeHigh - temperatureRangeLow ) / 5 + 1;
    rowsCount = rowsCountAboveTemp + rowsCountTemp + rowsCountBelowTemp;
    rowNoCervix = rowsCountAboveTemp + rowsCountTemp + rowNoCervixBelowTemp;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
bool configClass::readParamsFromConfigFile()
{
    if (!wxFileExists(m_configFile)) {
        return false;
    }

    /** Deprecated code START */
    wxFFile infile;
    wxString input;
    if ( !infile.Open(m_configFile, _T("r")) ) {
        wxRemoveFile(m_configFile);
        return false;
    }

    infile.ReadAll(&input);
    infile.Close();
    input = input.Trim(false);
    input = input.Trim(true);
    if ( !input.empty() ) {
        int n = input.find( wxT("logLevel"));
        if (n > -1) {
            return readParamsFromOldVersionOfConfigFile(input);
        }
    }
    /** Deprecated code END */


    wxConfigBase *config = new wxFileConfig( wxEmptyString, wxEmptyString, m_configFile );

    config->SetPath( CONF_PATH_general );

    /* GENERAL */
    // language
    config->Read( CONF_ENTRY_langId, &langId );
    // windows position
    config->Read( CONF_ENTRY_rememberPosition, &rememberPosition );
    config->Read( CONF_ENTRY_formMainMaximized, &formMainMaximized );
    config->Read( CONF_ENTRY_formMainHeight, &formMainHeight );
    config->Read( CONF_ENTRY_formMainWidth, &formMainWidth );
    config->Read( CONF_ENTRY_formMainLeft, &formMainLeft );
    config->Read( CONF_ENTRY_formMainTop, &formMainTop );
    config->Read( CONF_ENTRY_formDayLeft, &formDayLeft );
    config->Read( CONF_ENTRY_formDayTop, &formDayTop );
    config->Read( CONF_ENTRY_formCardLeft, &formCardLeft );
    config->Read( CONF_ENTRY_formCardTop, &formCardTop );
    config->Read( CONF_ENTRY_widowLeftWidth, &widowLeftWidth );
    config->Read( CONF_ENTRY_windowTopHeight, &windowTopHeight );
    // flat buttons
    config->Read( CONF_ENTRY_useFlatButtons, &useFlatButtons );
    // useCoitusRecordCounter
    config->Read( CONF_ENTRY_useCoitusRecordCounter, &useCoitusRecordCounter );
#if defined(__WXMSW__)
    // live update
    config->Read( CONF_ENTRY_checkForUpdates, &checkForUpdates );
    config->Read( CONF_ENTRY_updatesProxy, &updatesProxy );
#endif

    /* APPLICATION */
    config->SetPath( CONF_PATH_application );
    // last open file
    config->Read( CONF_ENTRY_openLastOpenedFile, &openLastOpenedFile );
    config->Read( CONF_ENTRY_lastOpenedFileName, &dataFileName );
    // missing days
    config->Read( CONF_ENTRY_checkForMissingDays, &checkForMissingDays );
    // breast self control reminder
    config->Read( CONF_ENTRY_breastSelfControlReminderDay, &breastSelfControlReminderDay );
    config->Read( CONF_ENTRY_breastSelfControlInterval, &breastSelfControlInterval );
    long breastSelfControlLastReminderLong = 0;
    config->Read( CONF_ENTRY_breastSelfControlLastReminder, &breastSelfControlLastReminderLong );
    if ( breastSelfControlLastReminderLong > 100000000 ) {
        breastSelfControlLastReminder.Set( breastSelfControlLastReminderLong );
    } else {
        breastSelfControlLastReminder = wxDateTime::Today();
        breastSelfControlLastReminder.Subtract( wxDateSpan::Days( breastSelfControlInterval + 1 ) );
    }
    // units
    config->Read( CONF_ENTRY_lengthInCentimeters, &lengthInCentimeters );
    config->Read( CONF_ENTRY_temperatureInCelsius, &temperatureInCelsius );
    // tempetature ranges on graph
    config->Read( CONF_ENTRY_temperatureRangeLow, &temperatureRangeLow );
    config->Read( CONF_ENTRY_temperatureRangeHigh, &temperatureRangeHigh );


    /* COLOURS */
    config->SetPath( CONF_PATH_colours );
    readParamsColour( config, CONF_ENTRY_colourBackground, colourBackground );
    readParamsColour( config, CONF_ENTRY_colourCell11, colourCell11 );
    readParamsColour( config, CONF_ENTRY_colourCell12, colourCell12 );
    readParamsColour( config, CONF_ENTRY_colourCell21, colourCell21 );
    readParamsColour( config, CONF_ENTRY_colourCell22, colourCell22 );
    readParamsColour( config, CONF_ENTRY_colourMarkedCell1, colourMarkedCell1 );
    readParamsColour( config, CONF_ENTRY_colourMarkedCell2, colourMarkedCell2 );
    readParamsColour( config, CONF_ENTRY_colourPointNormal, colourPointNormal );
    readParamsColour( config, CONF_ENTRY_colourPointBefore, colourPointBefore );
    readParamsColour( config, CONF_ENTRY_colourPointAfter, colourPointAfter );
    readParamsColour( config, CONF_ENTRY_colourTemperatureLine, colourTemperatureLine );
    readParamsColour( config, CONF_ENTRY_colourTemperatureLevelLine, colourTemperatureLevelLine );
    readParamsColour( config, CONF_ENTRY_colourPhaseLine, colourPhaseLine );
    readParamsColour( config, CONF_ENTRY_colourBorders, colourBorders );
    readParamsColour( config, CONF_ENTRY_colourMarkedBorders, colourMarkedBorders );


    /* FONTS */
    config->SetPath( CONF_PATH_fonts );
    readParamsFont( config, CONF_ENTRY_fontHeadTopic, fontHeadTopic );
    readParamsFont( config, CONF_ENTRY_fontHeadName, fontHeadName );
    readParamsFont( config, CONF_ENTRY_fontHeadValue, fontHeadValue );
    readParamsFont( config, CONF_ENTRY_fontResultHeader, fontResultHeader );
    readParamsFont( config, CONF_ENTRY_fontResultDefault, fontResultDefault );
    readParamsFont( config, CONF_ENTRY_fontResultResults, fontResultResults );
    readParamsFont( config, CONF_ENTRY_fontResultHeart, fontResultHeart );
    readParamsFont( config, CONF_ENTRY_fontResultPhases, fontResultPhases );
    // fonts' colours
    readParamsColour( config, CONF_ENTRY_fontHeadTopicColour, fontHeadTopicColour );
    readParamsColour( config, CONF_ENTRY_fontHeadNameColour, fontHeadNameColour );
    readParamsColour( config, CONF_ENTRY_fontHeadValueColour, fontHeadValueColour );
    readParamsColour( config, CONF_ENTRY_fontResultHeaderColour, fontResultHeaderColour );
    readParamsColour( config, CONF_ENTRY_fontResultDefaultColour, fontResultDefaultColour );
    readParamsColour( config, CONF_ENTRY_fontResultResultsColour, fontResultResultsColour );
    readParamsColour( config, CONF_ENTRY_fontResultHeartColour, fontResultHeartColour );
    readParamsColour( config, CONF_ENTRY_fontResultPhasesColour, fontResultPhasesColour );
    // character used in 'coitus record; row
    int coitusRecordCharacterInt = 0;
    if ( config->Read( CONF_ENTRY_coitusRecordCharacter, &coitusRecordCharacterInt )
       ) {
        if ( coitusRecordCharacterInt > 0 ) {
            coitusRecordCharacter = coitusRecordCharacterInt;
        }
    }

    calculateParams();

    delete config;
    return true;
}

/**
 *
 */
bool configClass::readParamsColour( wxConfigBase *config, wxString name, wxColour &colour )
{
    int red = -1, green = -1, blue = -1;

    if ( ! config->Read( name + CONF_ENTRY_EXT_RED, &red ) ) {
        return false;
    }
    if ( ! config->Read( name + CONF_ENTRY_EXT_GREEN, &green ) ) {
        return false;
    }
    if ( ! config->Read( name + CONF_ENTRY_EXT_BLUE, &blue ) ) {
        return false;
    }

    if ( red == -1 || green == -1 || blue == -1 ) {
        return false;
    }

    colour = wxColour( red, green, blue );
    return true;
}

/**
 *
 */
bool configClass::readParamsFont( wxConfigBase *config, wxString name, wxFont &font )
{
    int      pointSize = -1;
    int      family    = -1;
    int      style     = -1;
    int      weight    = -1;
    bool     underline = false;
    wxString faceName  = _T( "" );
    //int      encoding  = -1;

    if ( ! config->Read( name + CONF_ENTRY_EXT_POINTSIZE, &pointSize ) )
        return false;
    if ( ! config->Read( name + CONF_ENTRY_EXT_FAMILY, &family ) )
        return false;
    if ( ! config->Read( name + CONF_ENTRY_EXT_STYLE, &style ) )
        return false;
    if ( ! config->Read( name + CONF_ENTRY_EXT_WEIGHT, &weight ) )
        return false;
    if ( ! config->Read( name + CONF_ENTRY_EXT_UNDERLINE, &underline ) )
        return false;
    if ( ! config->Read( name + CONF_ENTRY_EXT_FACENAME, &faceName ) )
        return false;
    //if ( ! config->Read( name + CONF_ENTRY_EXT_ENCODING, &encoding ) )
    //    return false;

    //if ( pointSize == -1 || family == -1 || style == -1 || weight == -1 || encoding == -1 || faceName.IsEmpty() )
    if ( pointSize == -1 || family == -1 || style == -1 || weight == -1 || faceName.IsEmpty() )
        return false;

    //font = wxFont( pointSize, family, style, weight, underline, faceName, wxFontEncoding( encoding ) );
    font = wxFont( pointSize, family, style, weight, underline, faceName );
    return true;
}



/** Deprecated code START */

/**
 * Support for previous version of config file..
 */
bool configClass::readParamsFromOldVersionOfConfigFile(wxString input)
{
    // parse the configuration entries and put it to the 'params' hash map
    paramsHash params;
    wxString entry, name, value;
    int index;
    while ( ! input.IsEmpty() ) {
        index = input.First( _T("\n") ) ;
        if (index > -1) {
            entry = input.Mid(0, index);
            input = input.Mid(index).Trim(false);
            index = entry.First( _T("=") ) ;
            if (index > -1) {
                name  = entry.Mid(0, index);
                value = entry.Mid(index+1);
                if ( !name.IsEmpty() ) {
                    //log->debug(m_lClass , lMethod, _T("params[") + name + _T("] = ") + value );
                    params[name] = value;
                } else {
                    wxMessageBox( _T("Error while spliting configuration infile - 'name' is empty in entry: '") + entry + _T("'"), _T( "Warning" ), wxOK | wxICON_ERROR );
                }
            } else {
                wxMessageBox( _T("Error while spliting configuration infile - cannot find '=' in entry: '") + entry + _T("'"), _T( "Warning" ), wxOK | wxICON_ERROR );
            }

        } else {
            if ( !input.IsEmpty() ) {
                index = input.First( _T("=") ) ;
                if (index > -1) {
                    name  = input.Mid(0, index);
                    value = input.Mid(index+1);
                    if ( !name.IsEmpty() ) {
                        //log->debug(m_lClass , lMethod, _T("params[") + name + _T("] = ") + value );
                        params[name] = value;
                    } else {
                        wxMessageBox( _T("Error while spliting configuration infile - 'name' is empty in entry: '") + input + _T("'"), _T( "Warning" ), wxOK | wxICON_ERROR );
                    }
                } else {
                    wxMessageBox( _T("Error while spliting configuration infile - cannot find '=' in entry: '") + input + _T("'"), _T( "Warning" ), wxOK | wxICON_ERROR );
                }
                input = _T("");
            }
        }
    }

    // last open file
    readBool( params, _T("openLastOpenedFile"),           openLastOpenedFile );
    readString( params, _T("lastOpenedFileName"),         dataFileName );
    // missing days
    readBool( params, _T("checkForMissingDays"),          checkForMissingDays );
#if defined(__WXMSW__)
    // live update
    readBool( params, _T("checkForUpdates"),              checkForUpdates );
    readString( params, _T("updatesProxy"),               updatesProxy );
#endif
    // windows position
    readBool( params, _T("rememberPosition"),             rememberPosition );
    readBool( params, _T("formMainMaximized"),            formMainMaximized );
    readInt( params, _T("formMainHeight"),                formMainHeight );
    readInt( params, _T("formMainHeight"),                formMainHeight );
    readInt( params, _T("formMainWidth"),                 formMainWidth );
    readInt( params, _T("formMainLeft"),                  formMainLeft );
    readInt( params, _T("formMainTop"),                   formMainTop );
    readInt( params, _T("formDayLeft"),                   formDayLeft );
    readInt( params, _T("formDayTop"),                    formDayTop );
    readInt( params, _T("formCardLeft"),                  formCardLeft );
    readInt( params, _T("formCardTop"),                   formCardTop );
    readBool( params, _T("useFlatButtons"),               useFlatButtons );
    readInt( params, _T("widowLeftWidth"),                widowLeftWidth );
    readInt( params, _T("windowTopHeight"),               windowTopHeight );

    readInt( params, _T("breastSelfControlReminderDay"),     breastSelfControlReminderDay );
    readInt( params, _T("breastSelfControlInterval"),     breastSelfControlInterval );
    wxString tmp;
    readString( params, _T("breastSelfControlLastReminder"), tmp );
    try {
        if (tmp.IsEmpty()) {
            breastSelfControlLastReminder = wxDateTime::Today();
            breastSelfControlLastReminder.Subtract ( wxDateSpan::Days ( breastSelfControlInterval + 1 ) );
        }

        if (tmp.Mid(4,1)==_T("-") && tmp.Mid(7,1)==_T("-")) {
            breastSelfControlLastReminder.Set(m_util.strToInt(tmp.Mid(8,2)), wxDateTime::Month(m_util.strToInt(tmp.Mid(5,2))-1), m_util.strToInt(tmp.Mid(0,4)) );
        } else {
            breastSelfControlLastReminder = wxDateTime::Today();
            breastSelfControlLastReminder.Subtract ( wxDateSpan::Days ( breastSelfControlInterval + 1 ) );
        }

    } catch (...) {
        breastSelfControlLastReminder = wxDateTime::Today();
        breastSelfControlLastReminder.Subtract ( wxDateSpan::Days ( breastSelfControlInterval + 1 ) );
    }

    readBool( params, _T("lengthInCentimeters"),          lengthInCentimeters );

    // graph
    readBool( params, _T("temperatureInCelsius"),         temperatureInCelsius );
    readInt( params, _T("temperatureMin"),                temperatureRangeLow );
    readInt( params, _T("temperatureMax"),                temperatureRangeHigh );
    // colours
    readColour( params, _T("colourBackground"),           colourBackground );
    readColour( params, _T("colourCell11"),               colourCell11 );
    readColour( params, _T("colourCell12"),               colourCell12 );
    readColour( params, _T("colourCell21"),               colourCell21 );
    readColour( params, _T("colourCell22"),               colourCell22 );
    readColour( params, _T("colourMarkedCell1"),          colourMarkedCell1 );
    readColour( params, _T("colourMarkedCell2"),          colourMarkedCell2 );
    readColour( params, _T("colourPointNormal"),          colourPointNormal );
    readColour( params, _T("colourPointBefore"),          colourPointBefore );
    readColour( params, _T("colourPointAfter"),           colourPointAfter );
    readColour( params, _T("colourTemperatureLine"),      colourTemperatureLine );
    readColour( params, _T("colourTemperatureLevelLine"), colourTemperatureLevelLine );
    readColour( params, _T("colourPhaseLine"),            colourPhaseLine );
    readColour( params, _T("colourBorders"),              colourBorders );
    readColour( params, _T("colourMarkedBorders"),        colourMarkedBorders );
    // fonts
    readFont( params, _T("fontHeadTopic"),                fontHeadTopic );
    readFont( params, _T("fontHeadName"),                 fontHeadName );
    readFont( params, _T("fontHeadValue"),                fontHeadValue );
    readFont( params, _T("fontResultHeader"),             fontResultHeader );
    readFont( params, _T("fontResultDefault"),            fontResultDefault );
    readFont( params, _T("fontResultResults"),            fontResultResults );
    readFont( params, _T("fontResultHeart"),              fontResultHeart );
    readFont( params, _T("fontResultPhases"),             fontResultPhases );
    // fonts' colours
    readColour( params, _T("fontHeadTopicColour"),        fontHeadTopicColour );
    readColour( params, _T("fontHeadNameColour"),         fontHeadNameColour );
    readColour( params, _T("fontHeadValueColour"),        fontHeadValueColour );
    readColour( params, _T("fontResultHeaderColour"),     fontResultHeaderColour );
    readColour( params, _T("fontResultDefaultColour"),    fontResultDefaultColour );
    readColour( params, _T("fontResultResultsColour"),    fontResultResultsColour );
    readColour( params, _T("fontResultHeartColour"),      fontResultHeartColour );
    readColour( params, _T("fontResultPhasesColour"),     fontResultPhasesColour );

    calculateParams();

    wxRemoveFile(m_configFile);
    return true;
}

/**
 *
 */
void configClass::readString(paramsHash params, wxString name, wxString &paramToSet )
{
    if ( ! params[name].IsEmpty() ) {
        paramToSet = params[name];
    }
}

/**
 *
 */
void configClass::readInt(paramsHash params, wxString name, int &paramToSet )
{
    if ( ! params[name].IsEmpty() ) {
        paramToSet = m_util.strToInt(params[name]);
    }
}

/**
 *
 */
void configClass::readBool(paramsHash params, wxString name, bool &paramToSet )
{
    if ( ! params[name].IsEmpty() ) {
        paramToSet = m_util.strToBool(params[name]);
    }
}

/**
 *
 */
void configClass::readColour(paramsHash params, wxString name, wxColour &paramToSet )
{
    int red = -1, green = -1, blue = -1;

    if ( ! params[name + _T(".red")].IsEmpty() )  red = m_util.strToInt( params[name + _T(".red")] );
    if ( ! params[name + _T(".red")].IsEmpty() )  green = m_util.strToInt( params[name + _T(".green")] );
    if ( ! params[name + _T(".red")].IsEmpty() )  blue = m_util.strToInt( params[name + _T(".blue")] );

    if ( red != -1 && green != -1 && blue != -1 ) {
        paramToSet = wxColour(red, green, blue);
    }
}

/**
 *
 */
void configClass::readFont(paramsHash params, wxString name, wxFont &paramToSet)
{
    int      pointSize = -1;
    int      family    = -1;
    int      style     = -1;
    int      weight    = -1;
    bool     underline = false;
    wxString faceName  = _T("");
    //int      encoding  = -1;

    if ( ! params[name + _T(".pointSize")].IsEmpty() )  pointSize = m_util.strToInt( params[name + _T(".pointSize")] );
    if ( ! params[name + _T(".family")].IsEmpty() )     family = m_util.strToInt( params[name + _T(".family")] );
    if ( ! params[name + _T(".style")].IsEmpty() )      style = m_util.strToInt( params[name + _T(".style")] );
    if ( ! params[name + _T(".weight")].IsEmpty() )     weight = m_util.strToInt( params[name + _T(".weight")] );
    if ( ! params[name + _T(".underline")].IsEmpty() )  underline = m_util.strToBool( params[name + _T(".underline")] );
    if ( ! params[name + _T(".faceName")].IsEmpty() )   faceName = params[name + _T(".faceName")];
    //if ( ! params[name + _T(".encoding")].IsEmpty() )   encoding = m_util.strToInt( params[name + _T(".encoding")] );

    //if ( pointSize != -1 && family != -1 && style != -1 && weight != -1 && encoding != -1 && !faceName.IsEmpty() )
    //    paramToSet = wxFont (pointSize, family, style, weight, underline, faceName, wxFontEncoding(encoding) );

    if ( pointSize != -1 && family != -1 && style != -1 && weight != -1 && !faceName.IsEmpty() )
        paramToSet = wxFont (pointSize, family, style, weight, underline, faceName );
}


/** Deprecated code END */


/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
bool configClass::saveParamsToConfigFile()
{
    wxConfigBase * config = new wxFileConfig( wxEmptyString, wxEmptyString, m_configFile );

    /* GENERAL */
    config->SetPath( CONF_PATH_general );
    // language
    config->Write( CONF_ENTRY_langId, langId );
    // windows position
    config->Write( CONF_ENTRY_rememberPosition,             rememberPosition );
    if ( rememberPosition ) {
        config->Write( CONF_ENTRY_formMainMaximized,            formMainMaximized );
        config->Write( CONF_ENTRY_formMainHeight,                formMainHeight );
        config->Write( CONF_ENTRY_formMainWidth,                 formMainWidth );
        config->Write( CONF_ENTRY_formMainLeft,                  formMainLeft );
        config->Write( CONF_ENTRY_formMainTop,                   formMainTop );
        config->Write( CONF_ENTRY_formDayLeft,                   formDayLeft );
        config->Write( CONF_ENTRY_formDayTop,                    formDayTop );
        config->Write( CONF_ENTRY_formCardLeft,                  formCardLeft );
        config->Write( CONF_ENTRY_formCardTop,                   formCardTop );
    }
    config->Write( CONF_ENTRY_widowLeftWidth,                widowLeftWidth );
    config->Write( CONF_ENTRY_windowTopHeight,               windowTopHeight );
    // flat buttons
    config->Write( CONF_ENTRY_useFlatButtons,               useFlatButtons );
    // live update
    config->Write( CONF_ENTRY_checkForUpdates,              checkForUpdates );
    config->Write( CONF_ENTRY_updatesProxy,               updatesProxy );


    /* APPLICATION */
    config->SetPath( CONF_PATH_application );
    // last open file
    config->Write( CONF_ENTRY_openLastOpenedFile,           openLastOpenedFile );
    if ( openLastOpenedFile ) {
        config->Write( CONF_ENTRY_lastOpenedFileName,         dataFileName );
    } else {
        config->DeleteEntry( CONF_ENTRY_lastOpenedFileName, false );
    }
    // missing days
    config->Write( CONF_ENTRY_checkForMissingDays,          checkForMissingDays );
    // breast self control reminder
    config->Write( CONF_ENTRY_breastSelfControlReminderDay,     breastSelfControlReminderDay );
    config->Write( CONF_ENTRY_breastSelfControlInterval,     breastSelfControlInterval );
    config->Write( CONF_ENTRY_breastSelfControlLastReminder, breastSelfControlLastReminder.GetTicks() );
    // units
    config->Write( CONF_ENTRY_lengthInCentimeters,          lengthInCentimeters );
    config->Write( CONF_ENTRY_temperatureInCelsius,         temperatureInCelsius );
    // tempetature ranges on graph
    config->Write( CONF_ENTRY_temperatureRangeLow,                temperatureRangeLow );
    config->Write( CONF_ENTRY_temperatureRangeHigh,                temperatureRangeHigh );


    /* COLOURS */
    config->SetPath( CONF_PATH_colours );
    saveParamColour( config, CONF_ENTRY_colourBackground,           colourBackground );
    saveParamColour( config, CONF_ENTRY_colourCell11,               colourCell11 );
    saveParamColour( config, CONF_ENTRY_colourCell12,               colourCell12 );
    saveParamColour( config, CONF_ENTRY_colourCell21,               colourCell21 );
    saveParamColour( config, CONF_ENTRY_colourCell22,               colourCell22 );
    saveParamColour( config, CONF_ENTRY_colourMarkedCell1,          colourMarkedCell1 );
    saveParamColour( config, CONF_ENTRY_colourMarkedCell2,          colourMarkedCell2 );
    saveParamColour( config, CONF_ENTRY_colourPointNormal,          colourPointNormal );
    saveParamColour( config, CONF_ENTRY_colourPointBefore,          colourPointBefore );
    saveParamColour( config, CONF_ENTRY_colourPointAfter,           colourPointAfter );
    saveParamColour( config, CONF_ENTRY_colourTemperatureLine,      colourTemperatureLine );
    saveParamColour( config, CONF_ENTRY_colourTemperatureLevelLine, colourTemperatureLevelLine );
    saveParamColour( config, CONF_ENTRY_colourPhaseLine,            colourPhaseLine );
    saveParamColour( config, CONF_ENTRY_colourBorders,              colourBorders );
    saveParamColour( config, CONF_ENTRY_colourMarkedBorders,        colourMarkedBorders );


    /* FONTS */
    config->SetPath( CONF_PATH_fonts );
    saveParamFont( config, CONF_ENTRY_fontHeadTopic,                fontHeadTopic );
    saveParamFont( config, CONF_ENTRY_fontHeadName,                 fontHeadName );
    saveParamFont( config, CONF_ENTRY_fontHeadValue,                fontHeadValue );
    saveParamFont( config, CONF_ENTRY_fontResultHeader,             fontResultHeader );
    saveParamFont( config, CONF_ENTRY_fontResultDefault,            fontResultDefault );
    saveParamFont( config, CONF_ENTRY_fontResultResults,            fontResultResults );
    saveParamFont( config, CONF_ENTRY_fontResultHeart,              fontResultHeart );
    saveParamFont( config, CONF_ENTRY_fontResultPhases,             fontResultPhases );
    // fonts' colours
    saveParamColour( config, CONF_ENTRY_fontHeadTopicColour,        fontHeadTopicColour );
    saveParamColour( config, CONF_ENTRY_fontHeadNameColour,         fontHeadNameColour );
    saveParamColour( config, CONF_ENTRY_fontHeadValueColour,        fontHeadValueColour );
    saveParamColour( config, CONF_ENTRY_fontResultHeaderColour,     fontResultHeaderColour );
    saveParamColour( config, CONF_ENTRY_fontResultDefaultColour,    fontResultDefaultColour );
    saveParamColour( config, CONF_ENTRY_fontResultResultsColour,    fontResultResultsColour );
    saveParamColour( config, CONF_ENTRY_fontResultHeartColour,      fontResultHeartColour );
    saveParamColour( config, CONF_ENTRY_fontResultPhasesColour,     fontResultPhasesColour );
    // character used in 'coitus record' row
    config->Write( CONF_ENTRY_coitusRecordCharacter,                static_cast<int>( coitusRecordCharacter ) );

    config->Flush();
    delete config;
    return true;
}

/**
 *
 */
bool configClass::saveParamColour( wxConfigBase *config, wxString name, wxColour input )
{
    config->Write( wxString::Format( _T( "%s%s" ), name.c_str(), CONF_ENTRY_EXT_RED ), input.Red() );
    config->Write( wxString::Format( _T( "%s%s" ), name.c_str(), CONF_ENTRY_EXT_GREEN ), input.Green() );
    config->Write( wxString::Format( _T( "%s%s" ), name.c_str(), CONF_ENTRY_EXT_BLUE ), input.Blue() );
    return true;
}

/**
 *
 */
bool configClass::saveParamFont( wxConfigBase *config, wxString name, wxFont input )
{
    config->Write( wxString::Format( _T( "%s%s" ), name.c_str(), CONF_ENTRY_EXT_POINTSIZE ), input.GetPointSize() );
    config->Write( wxString::Format( _T( "%s%s" ), name.c_str(), CONF_ENTRY_EXT_FAMILY ), (long)input.GetFamily() );
    config->Write( wxString::Format( _T( "%s%s" ), name.c_str(), CONF_ENTRY_EXT_STYLE ), (long)input.GetStyle() );
    config->Write( wxString::Format( _T( "%s%s" ), name.c_str(), CONF_ENTRY_EXT_WEIGHT ), (long)input.GetWeight() );
    config->Write( wxString::Format( _T( "%s%s" ), name.c_str(), CONF_ENTRY_EXT_UNDERLINE ), input.GetUnderlined() );
    config->Write( wxString::Format( _T( "%s%s" ), name.c_str(), CONF_ENTRY_EXT_FACENAME ), input.GetFaceName() );
    //config->Write( wxString::Format( _T( "%s%s" ), name.c_str(), CONF_ENTRY_EXT_ENCODING ), (long)input.GetEncoding() );
    return true;
}



/*******************************************************************************
********************************************************************************
*******************************************************************************/
