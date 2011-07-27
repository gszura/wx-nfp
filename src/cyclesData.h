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
#include "utilClass.h"

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */

class cycleDataClass
{

private:
    wxString m_name;
    wxDateTime m_birthdayDay;

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

    void setCardModified( bool );
    bool getCardModified();

    void setCoitusRecordCounter( int );
    void increaseCoitusRecordCounter( int );
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

    wxString getName();
    wxDateTime getBirthdayDay();

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
    bool   readCardsDataFromFile( wxString );

private:
    bool       readPersonalData( wxString );
    bool       readCard( wxString );
    bool       readDay( wxString, int );
    wxString   getSection( wxString, wxString, int& );
    wxString   readString( wxString, wxString );
    bool       readBool( wxString, wxString );
    int        readInt( wxString, wxString );
    wxDateTime readDateTime( wxString, wxString );
    intArray   readHash( wxString, wxString );

public:
    // storing cycles data
    bool       saveCardsDataToFile( wxString );

private:
    wxString   getNode( wxString, wxString );
    wxString   getNodeInt( wxString, int );
    wxString   getNodeDateTime( wxString, wxDateTime, wxString );
    wxString   getNodeBool( wxString, bool );
    wxString   getNodeHash( wxString, intArray );


    /**************************************************************************/
    /** MOVING DAYS BETWEEN 2 LAST CARDS */
public:
    bool moveDaysToPreviousCard( int );
    bool moveDaysToNextCard( int );


    /**************************************************************************/
    /** RESULTS */

public:
    bool checkSettingResultsBasicStaff(int cardNo, int dayNo);

    /** DEFINING RESULTS MANUALLY */
private:
    int askForRemovingOtherResults();
public:
    int * setResultMucus1stDay( int cardNo = -1, int dayNo = -1 );
    int * setResultMucus1stMoreFertileDay( int cardNo = -1, int dayNo = -1 );
    int * setResultMucusPeak( int cardNo = -1, int dayNo = -1 );
    int * setResultCervix1stDay( int cardNo = -1, int dayNo = -1 );
    int * setResultCervixPeak( int cardNo = -1, int dayNo = -1 );
    int * setResultTemperaturesLevels( int cardNo = -1, int dayNo = -1, bool resetIfExists = true );
    int * resetResultTemperaturesLevels(int cardNo = -1);
    int * setResultFertilePhaseStart( int cardNo = -1, int dayNo = -1 );
    int * setResultInfertilePhaseStart( int cardNo = -1, int dayNo = -1 );

    /** DEFINING RESULTS MANUALLY */
    int * calculateResultsAutomatically( int cardNo = -1 );
    int * calculateResultMucus1stDay( int );
    int * calculateResultMucus1stMoreFertileDay( int );
    int * calculateResultMucusPeak( int );
    int * calculateResultCervix1stDay( int );
    int * calculateResultCervixPeak( int );
    int * calculateResultTemperaturesLevels( int );
    int * calculateResultFertilePhaseStart( int );
    int * calculateResultInfertilePhaseStart( int );

    /**************************************************************************/
    int calculateCorrectTemperatureValue( int, wxDateTime, int, int );
    int calculateCorrectTemperatureValue();
    int calculateCorrectTemperatureValue( int );
    int calculateCorrectTemperatureValue( int, int );

private:
    int calculateCorrectTemperatureValue( int, int, bool, int, wxDateTime, int, int );

    /*

    // -----------------------
    // FUNKCJE DO OBLICZANIA WYNIKU

    public:
       // sprawdzenie, czy dany dzien moze byc zaznaczony jako dzien "specjalny"
       bool checkTheDayPossibility_1_sluz(int, int, bool);
       bool checkTheDayPossibility_1_sluz_plodny(int, int, bool);
       bool checkTheDayPossibility_sluz_szczyt(int, int, bool);
       bool checkTheDayPossibility_1_szyjka(int, int, bool);
       bool checkTheDayPossibility_szyjka_szczyt(int, int, bool);
       bool checkTheDayPossibility_temperatura(int, int, bool);

       int find_poziom_nizszy_temperatur(int);
       int find_first_temperature(int);
       int find_first_hight_temperature(int);
       int find_last_temperature(int);
    */

// -----------------------
// FUNKCJE POMOCNICZE
//

    /*
    public:
       bool correctDates();
       wxString convertTemperature(int, bool);
       int countWspolzycieTotal();
    */








};

/*******************************************************************************
********************************************************************************
*******************************************************************************/

#endif

