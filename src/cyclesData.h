#ifndef HEADER_459386AF70D44F07
#define HEADER_459386AF70D44F07

/*******************************************************************************
//
// Name:        cycleDataClass.h
// Author:      enkeli
// Description:
//
*******************************************************************************/

#ifndef __CYCLES_DATA__
#define __CYCLES_DATA__

#include <wx/datetime.h>
//#include "wx_pch.h"

#include "dayEntry.h"
#include "cardEntry.h"
#include "cyclesData_declarations.h"
#include "configClass.h"
#include "utilClass.h"

#define NO_RESULTS _T( "NO_RESULTS" )

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */

class cycleDataClass
{

private:
    // temporary
    wxString m_sexualRelationDataConversionMessages2;
    wxString m_sexualRelationDataConversionMessages3;
    wxString m_sexualRelationDataConversionMessages4;
    bool m_sexualRelationDataConverted;

    bool m_askUserToKeepResultsAlreadySetForOtherDays;

    wxString m_name;
    wxDateTime m_birthdayDay;

    int m_shortestCycleDays;
    int m_shortestCycleFromCycles;


    // keys of the hash table: [1...]
    cardEntryHash m_cards;


    wxString m_errorMessages;
    utilClass m_util;

    // currently displayed card
    int m_activeCard;
    // currently active day
    int m_activeDay;
    // previously active day
    int m_prevActiveDay;

    // true, if data has been modified
    bool m_cardModified;

    // ;-)
    int m_coitusRecordCounter;

    /**************************************************************************/

public:
    cycleDataClass();

    void addErrorMessages( wxString );
    wxString getErrorMessages();
    bool isSexualRelationDataConverted();
    wxString getSexualRelationDataConversionMessages2();
    wxString getSexualRelationDataConversionMessages3();
    wxString getSexualRelationDataConversionMessages4();

    bool isAskUserToKeepResultsAlreadySetForOtherDays();
    void setAskUserToKeepResultsAlreadySetForOtherDays(bool);

    void setCardModified( bool );
    bool getCardModified();

    void setCoitusRecordCounter( int );
    void increaseCoitusRecordCounter(int value = 1);
    int getCoitusRecordCounter();

    /**************************************************************************/
    bool setActiveCard( int );
    int getActiveCard();
    bool setActiveDay( int );
    int getActiveDay();
    int getPrevActiveDay();

    bool createNewSet();
    bool removeAll();

    /**************************************************************************/
    /** GENERAL INFO */
public:
    bool setName( wxString );
    bool setBirthdayDay( wxDateTime );
    bool setShortestCycleDays(int);
    bool setShortestCycleFromCycles(int);

    wxString getName();
    wxDateTime getBirthdayDay();
    int getShortestCycleDays();
    int getShortestCycleFromCycles();

    /**************************************************************************/
    /** CARDS */
private:
    bool removeAllCards();

public:
    int addNewCard();
    bool removeLastCard();
    int getCardsCount();
    cardEntry *getCard();
    cardEntry *getCard( int );


    /**************************************************************************/
    /** DAYS */
private:
    int addNewDay( int );

public:
    int addNewDay();
    bool removeLastDay();
    int getDaysCount();
    int getDaysCount( int );
    dayEntry *getDay();
    dayEntry *getDay( int );
    dayEntry *getDay( int, int );


    /**************************************************************************/
    /** READING AND STORING CYCLES DATA */
public:
    // reading cycles data
    bool readCardsDataFromFile( wxString );
    int getNumberOfHistoricalCyclesUsedToCalculateShortestCycle( int, configClass* );
    int getNumberOfHistoricalCyclesUsedToCalculateEarliestFirstDayOfHighLevelTemperature( int, configClass* );
    int getNumberOfDaysOfShortestCycle( int, configClass* );
    int getEarliestFirstDayOfHighLevelTemperature( int, configClass* );

private:
    bool       readPersonalData( wxString );
    bool       readCard( wxString );
    bool       readDay( wxString, int );
    wxString   getSection( wxString, wxString, int& );
    wxString   readString( wxString, wxString );
    bool       readBool( wxString, wxString );
    int        readInt( wxString, wxString );
    wxDateTime readDateTime( wxString, wxString );
    intArray   readList( wxString, wxString );

public:
    // storing cycles data
    bool       saveCardsDataToFile( wxString );

private:
    wxString   getNode( wxString, wxString );
    wxString   getNodeInt( wxString, int );
    wxString   getNodeDateTime( wxString, wxDateTime, wxString );
    wxString   getNodeBool( wxString, bool );
    wxString   getNodeList( wxString, intArray );


    /**************************************************************************/
    /** MOVING DAYS BETWEEN 2 LAST CARDS */
public:
    bool moveDaysToPreviousCard( int );
    bool moveDaysToNextCard( int );


    /**************************************************************************/
public:
    int calculateCorrectTemperatureValue( int, wxDateTime, int, int );
    int calculateCorrectTemperatureValue();
    int calculateCorrectTemperatureValue( int );
    int calculateCorrectTemperatureValue( int, int );

private:
    int calculateCorrectTemperatureValue( int, int, bool, int, wxDateTime, int, int );

    /**************************************************************************/
    /** RESULTS */

public:
    bool checkSettingResultsBasicStaff(int cardNo, int dayNo);

    /** DEFINING RESULTS MANUALLY */
private:
    int askToKeepResultsAlreadySetForOtherDays(int);
public:
    int * setResultMucus1stDay( int cardNo = -1, int dayNo = -1 );
    int * setResultMucus1stMoreFertileDay( int cardNo = -1, int dayNo = -1 );
    int * setResultMucusPeak( int cardNo = -1, int dayNo = -1 );
    int * setResultCervix1stDay( int cardNo = -1, int dayNo = -1 );
    int * setResultCervixPeak( int cardNo = -1, int dayNo = -1 );
    int * setResultTemperatureLevels( configClass*, int cardNo = -1, int dayNo = -1, bool resetIfExists = true );
    int * resetResultTemperatureLevels(int cardNo = -1);
    int * setResultFertilePhaseStart( int cardNo = -1, int dayNo = -1 );
    int * setResultInfertilePhaseStart( int cardNo = -1, int dayNo = -1 );

    /** DEFINING RESULTS MANUALLY */
    bool calculateResultsAutomatically( int, configClass* );
    bool removePreviouslySetResults(cardEntry*);
    bool calculateResultsAutomaticallyOnChange( int, configClass* );
private:
    bool calculateResultMucus1stDay( cardEntry*, int );
    bool calculateResultMucus1stMoreFertileDay( cardEntry*, int );
    bool calculateResultMucusPeak( cardEntry*, int );
    bool calculateResultCervix1stDay( cardEntry*, int );
    bool calculateResultCervixPeak( cardEntry*, int );
    bool calculateResultTemperatureLevels( cardEntry*, int, configClass* );
    int * calculateTemperatureLevels( cardEntry*, int, int, configClass*, bool );
    int getDayTemp( cardEntry*, int );
    bool are7measuredTemperatures( cardEntry* );
    bool wasMucusPeakBeforeDay(cardEntry*, int);
    bool calculateResultFertilePhaseStart( cardEntry*, int, configClass* );
    int getFirstDayOfFertilePhaseStartAccordingTo2120DaysRule( int, configClass* );
    int getFirstDayOfFertilePhaseStartAccordingToClinicalRule( int, configClass* );
    int getFirstDayOfFertilePhaseStartAccordingToDoeringRule( cardEntry*, int, configClass* );
    int getFirstDayOfFertilePhaseStartAccordingToCervicalMucusBasedRule( cardEntry*, int, configClass* );
    int getFirstDayOfFertilePhaseStartAccordingToCervicalPositionBasedRule( cardEntry*, int );
    bool calculateResultInfertilePhaseStart( cardEntry*, int );
    bool calculateResultPhasesInAfterPregnancyCycle( cardEntry*, int, configClass* );
    bool isBasicInfertilePatternWithMucus(cardEntry*);
    bool wasMoreFertileMucusFor5DaysInPreviousCycles( int, configClass* );
    bool isCardFromLast3AfterStoppedPills(int);
};

/*******************************************************************************
********************************************************************************
*******************************************************************************/

#endif


#endif // header guard
