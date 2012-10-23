/*******************************************************************************
//
// Name:        configClass.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "configClass.h"
#include "wx-nfpAppInfo.h"

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
    visibleNote = wxEmptyString;
    warningShown = false;
    dataFileName = wxEmptyString;

    openFileFromParams = false;
    useCoitusRecordCounter = false;
    openLastOpenedFile = true;
    autosaveChanges = true;
    autosaveSet = false;
    syncFileAutomatically = true;
    wxString password = wxEmptyString;
    rememberPassword = false;
    useCustomServer = false;
    customServerUri = wxEmptyString;

    rememberPosition = true;
    checkForMissingDays = true;
    checkForUpdates = true;
    updatesProxy = wxEmptyString;
    breastSelfControlReminderDay = 6;
    breastSelfControlInterval = 30;
    // analyze card after each change
    autoanalyzeCard = false;
    showAutoanalysisDetails = true;
    // temperature graph
    maxAllowedNotMesuredLowLevelDays = 3;
    maxIncludedNotMesuredLowLevelDays = 2;
    maxAllowedNotMesuredHighLevelDays = 1;
    maxIncludedNotMesuredHighLevelDays = 1;
    includeNotMesuredDaysIfAfterMucusPeak = true;
    // calculating beginning of the fertile phase
    numberOfHistoricalCyclesToUse = 12;
    autoanalyzeCardPreferResult1 = RULE_DOERING;
    autoanalyzeCardPreferResult2 = RULE_CERVICAL_MUCUS_BASED;
    autoanalyzeCardPreferResult3 = RULE_CERVICAL_POSITION_BASED;
    autoanalyzeCardPreferResult4 = RULE_CLINICAL;
    autoanalyzeCardPreferResult5 = RULE_2120;

    setDefaultParams();
}

/**
 * Function run during application start and when user press the button 'restore settings' in options dialog.
 */
void configClass::setDefaultParams()
{
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
    fontResultPhases = wxFont( 14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );

#else
    showColoursDialogForFonts = false;
    fontHeadTopic = wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false );
    fontHeadName = wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );
    fontHeadValue = wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false );
    fontResultHeader = wxFont( 7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false );
    fontResultDefault = wxFont( 7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );
    fontResultResults = wxFont( 7, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );
    fontResultPhases = wxFont( 14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false );

#endif

    fontHeadTopicColour = wxColour( 128, 0, 0 );
    fontHeadNameColour = wxColour( 0, 0, 128 );
    fontHeadValueColour = wxColour( 0, 0, 128 );
    fontResultHeaderColour = wxColour( 0, 0, 0 );
    fontResultDefaultColour = wxColour( 0, 0, 0 );
    fontResultResultsColour = wxColour( 255, 0, 255 );
    fontResultPhasesColour = wxColour( 0, 255, 0 );

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

void configClass::instertCurrentlyOpenedFileNameToHistory()
{
    // file name we're just adding should be on first place on the list and it should be only once on the list
    wxLogDebug( wxString::Format( _T("[configClass] cards in history: %i, current card: '%s'"), previouslyOpenedFileNames.GetCount(), dataFileName.c_str() ) );
    if ( !dataFileName.IsEmpty() && previouslyOpenedFileNames.GetCount() > 0) {
        for ( int i = previouslyOpenedFileNames.GetCount()-1; i>=0; i-- ) {
            wxLogDebug( wxString::Format( _T("[configClass] testing card %i from history '%s'"), i, previouslyOpenedFileNames.Item(i).c_str() ) );
            if ( dataFileName.IsSameAs(previouslyOpenedFileNames.Item(i)) ) {
                wxLogDebug( wxString::Format( _T("[configClass] the same name - removing") ) );
                previouslyOpenedFileNames.RemoveAt(i);
            }
        }
    }
    // we want to keep max 10 entries, so leave only 9 entries
    if ( previouslyOpenedFileNames.GetCount() > 9 ) {
        wxLogDebug( wxString::Format( _T("[configClass] removing card 9 from history") ) );
        previouslyOpenedFileNames.RemoveAt( 9, previouslyOpenedFileNames.GetCount() - 9 );
    }

    wxLogDebug( wxString::Format( _T("[configClass] insterting current card to the 1st place in the history") ) );
    previouslyOpenedFileNames.Insert(dataFileName, 0);
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
//#if defined(__WXMSW__)
    // live update
    config->Read( CONF_ENTRY_checkForUpdates, &checkForUpdates );
    config->Read( CONF_ENTRY_updatesProxy, &updatesProxy );
//#endif

    /* APPLICATION */
    config->SetPath( CONF_PATH_application );
    // last open file
    config->Read( CONF_ENTRY_openLastOpenedFile, &openLastOpenedFile );
    config->Read( CONF_ENTRY_lastOpenedFileName, &dataFileName );
    wxString fileName;
    for (int i=0; i<10; i++) {
        if ( config->Read( wxString::Format( _T("%s%i"), CONF_ENTRY_PREFIX_previouslyOpenedFileNames, i ), &fileName ) )
            previouslyOpenedFileNames.Add(fileName);
    }

    // autosave
    config->Read( CONF_ENTRY_autosaveChanges, &autosaveChanges );
    config->Read( CONF_ENTRY_autosaveSet, &autosaveSet );
    // saving file on server
    config->Read( CONF_ENTRY_syncFileAutomatically, &syncFileAutomatically );
    config->Read( CONF_ENTRY_rememberPassword, &rememberPassword );
    config->Read( CONF_ENTRY_password, &password );
    password = m_util.unhashString(password);

    config->Read( CONF_ENTRY_useCustomServer, &useCustomServer );
    config->Read( CONF_ENTRY_customServerUri, &customServerUri );

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
    readParamsFont( config, CONF_ENTRY_fontResultPhases, fontResultPhases );
    // fonts' colours
    readParamsColour( config, CONF_ENTRY_fontHeadTopicColour, fontHeadTopicColour );
    readParamsColour( config, CONF_ENTRY_fontHeadNameColour, fontHeadNameColour );
    readParamsColour( config, CONF_ENTRY_fontHeadValueColour, fontHeadValueColour );
    readParamsColour( config, CONF_ENTRY_fontResultHeaderColour, fontResultHeaderColour );
    readParamsColour( config, CONF_ENTRY_fontResultDefaultColour, fontResultDefaultColour );
    readParamsColour( config, CONF_ENTRY_fontResultResultsColour, fontResultResultsColour );
    readParamsColour( config, CONF_ENTRY_fontResultPhasesColour, fontResultPhasesColour );

    /* ANALYSIS */
    config->SetPath( CONF_PATH_analysis );
    config->Read( CONF_ENTRY_autoanalyzeCard, &autoanalyzeCard );
    config->Read( CONF_ENTRY_showAutoanalysisDetails, &showAutoanalysisDetails );
    config->Read( CONF_ENTRY_maxAllowedNotMesuredLowLevelDays, &maxAllowedNotMesuredLowLevelDays );
    config->Read( CONF_ENTRY_maxIncludedNotMesuredLowLevelDays, &maxIncludedNotMesuredLowLevelDays );
    config->Read( CONF_ENTRY_maxAllowedNotMesuredHighLevelDays, &maxAllowedNotMesuredHighLevelDays );
    config->Read( CONF_ENTRY_maxIncludedNotMesuredHighLevelDays, &maxIncludedNotMesuredHighLevelDays );
    config->Read( CONF_ENTRY_includeNotMesuredDaysIfAfterMucusPeak, &includeNotMesuredDaysIfAfterMucusPeak );
    config->Read( CONF_ENTRY_numberOfHistoricalCyclesToUse, &numberOfHistoricalCyclesToUse );
    config->Read( CONF_ENTRY_autoanalyzeCardPreferResult1, &autoanalyzeCardPreferResult1 );
    config->Read( CONF_ENTRY_autoanalyzeCardPreferResult2, &autoanalyzeCardPreferResult2 );
    config->Read( CONF_ENTRY_autoanalyzeCardPreferResult3, &autoanalyzeCardPreferResult3 );
    config->Read( CONF_ENTRY_autoanalyzeCardPreferResult4, &autoanalyzeCardPreferResult4 );
    config->Read( CONF_ENTRY_autoanalyzeCardPreferResult5, &autoanalyzeCardPreferResult5 );

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
    wxString faceName  = wxEmptyString;
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

    for (size_t i=0; i<previouslyOpenedFileNames.GetCount(); i++) {
        config->Write( wxString::Format( _T("%s%i"), CONF_ENTRY_PREFIX_previouslyOpenedFileNames, i ), previouslyOpenedFileNames.Item(i) );
    }

    // autosave
    config->Write( CONF_ENTRY_autosaveChanges,             autosaveChanges );
    config->Write( CONF_ENTRY_autosaveSet,                 autosaveSet );
    // saving file on server
    config->Write( CONF_ENTRY_syncFileAutomatically, syncFileAutomatically );
    config->Write( CONF_ENTRY_rememberPassword, rememberPassword );
    if ( rememberPassword ) {
        config->Write( CONF_ENTRY_password, m_util.hashString(password) );
    } else {
        config->Write( CONF_ENTRY_password, wxEmptyString );
    }
    config->Write( CONF_ENTRY_useCustomServer, useCustomServer );
    config->Write( CONF_ENTRY_customServerUri, customServerUri );

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
    saveParamFont( config, CONF_ENTRY_fontResultPhases,             fontResultPhases );
    // fonts' colours
    saveParamColour( config, CONF_ENTRY_fontHeadTopicColour,        fontHeadTopicColour );
    saveParamColour( config, CONF_ENTRY_fontHeadNameColour,         fontHeadNameColour );
    saveParamColour( config, CONF_ENTRY_fontHeadValueColour,        fontHeadValueColour );
    saveParamColour( config, CONF_ENTRY_fontResultHeaderColour,     fontResultHeaderColour );
    saveParamColour( config, CONF_ENTRY_fontResultDefaultColour,    fontResultDefaultColour );
    saveParamColour( config, CONF_ENTRY_fontResultResultsColour,    fontResultResultsColour );
    saveParamColour( config, CONF_ENTRY_fontResultPhasesColour,     fontResultPhasesColour );

    /* ANALYSIS */
    config->SetPath( CONF_PATH_analysis );
    config->Write( CONF_ENTRY_autoanalyzeCard,                       autoanalyzeCard );
    config->Write( CONF_ENTRY_showAutoanalysisDetails,               showAutoanalysisDetails );
    config->Write( CONF_ENTRY_maxAllowedNotMesuredLowLevelDays,      maxAllowedNotMesuredLowLevelDays );
    config->Write( CONF_ENTRY_maxIncludedNotMesuredLowLevelDays,     maxIncludedNotMesuredLowLevelDays );
    config->Write( CONF_ENTRY_maxAllowedNotMesuredHighLevelDays,     maxAllowedNotMesuredHighLevelDays );
    config->Write( CONF_ENTRY_maxIncludedNotMesuredHighLevelDays,    maxIncludedNotMesuredHighLevelDays );
    config->Write( CONF_ENTRY_includeNotMesuredDaysIfAfterMucusPeak, includeNotMesuredDaysIfAfterMucusPeak );
    config->Write( CONF_ENTRY_numberOfHistoricalCyclesToUse,         numberOfHistoricalCyclesToUse );
    config->Write( CONF_ENTRY_autoanalyzeCardPreferResult1,          autoanalyzeCardPreferResult1 );
    config->Write( CONF_ENTRY_autoanalyzeCardPreferResult2,          autoanalyzeCardPreferResult2 );
    config->Write( CONF_ENTRY_autoanalyzeCardPreferResult3,          autoanalyzeCardPreferResult3 );
    config->Write( CONF_ENTRY_autoanalyzeCardPreferResult4,          autoanalyzeCardPreferResult4 );
    config->Write( CONF_ENTRY_autoanalyzeCardPreferResult5,          autoanalyzeCardPreferResult5 );

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
