/*******************************************************************************
//
// Name:        cardEntry.h
// Author:      enkeli
// Description:
//
*******************************************************************************/

#ifndef __CARD_ENTRY__
#define __CARD_ENTRY__

#include <wx/wx.h>
#include <wx/datetime.h>
#include <wx/dynarray.h>
#include "dayEntry.h"
#include "cyclesData_declarations.h"

WX_DEFINE_ARRAY_INT(int, intArray);

/*******************************************************************************
********************************************************************************
*******************************************************************************/

class cardEntry
{
    /** VARIABLES */
private:
    wxDateTime m_firstDayOfCycle;                     // [yyyy-mm-dd]
    wxDateTime m_temperatureUsualMeasurementTime;     // [hh:mm]
    int m_temperatureUsualMeasurementPlace;           // [-1 | 1-3]
    bool m_cardLocked;                                // [x]
    wxString m_notes;                                 // [<string>]
    int m_temperatureCorrectionWhenMeasuredInMouth;   // [(-)dd]  np. -10 == -0.10 st. C
    int m_temperatureCorrectionWhenMeasuredInRectum;  // [(-)dd]  np.  20 ==  0.20 st. C
    int m_temperatureCorrectionWhenMeasuredInVagina;  // [(-)dd]  np. -10 == -0.10 st. C
    // gdy temperature zmierzono 60 minut pozniej niz zwykle, to dodaj 'temperatureCorrectionTime' do zmierzonej temperatury.
    // if temperature is measured 60 minutes later that usual than add 'temperatureCorrectionTime' to the measured temperature.
    int m_temperatureCorrectionForMeasurementTimeSake;// [(-)dd]  np. -10 == -0.10 st. C

    intArray m_resultMucus1stDay;                     // array of int
    intArray m_resultMucus1stMoreFertileDay;          // array of int
    intArray m_resultMucusPeak;                       // array of int
    intArray m_resultCervix1stDay;                    // array of int
    intArray m_resultCervixPeak;                      // array of int
    int m_resultTemperatureLowLevelValue;             // [dayNo]
    int m_resultTemperatureLowLevelStart;             // [dayNo]
    int m_resultTemperatureHighLevelStart;            // [dayNo]
    int m_resultTemperatureHighLevelEnd;              // [dayNo]
    intArray m_resultInfertilePhaseStart;             // array of int
    intArray m_resultFertilePhaseStart;               // array of int

    dayEntryHash m_days;                              // keys of the hash table: [1...]

    /** METHODS */
public:
    /** CONSTRUCTORS */
    cardEntry();
    cardEntry(cardEntry*);

    /** STORING AND READING DAYS OJECTS */
    int addNewDay(dayEntry*);
    bool removeLastDay();
    bool removeAllDays();
    int getDaysCount();
    dayEntry * getDay(int);
    bool dayExist(int);

    /** STORING THE DATA */
    void setFirstDayOfCycle(wxDateTime);
    void setTemperatureUsualMeasurementTime(wxDateTime);
    void setTemperatureUsualMeasurementPlace(int);
    void setCardLocked(bool);
    void setNotes(wxString);
    void setTemperatureCorrectionWhenMeasuredInMouth(int);
    void setTemperatureCorrectionWhenMeasuredInRectum(int);
    void setTemperatureCorrectionWhenMeasuredInVagina(int);
    void setTemperatureCorrectionForMeasurementTimeSake(int);

    /** READING THE DATA */
    wxDateTime getFirstDayOfCycle();
    wxDateTime getTemperatureUsualMeasurementTime();
    int getTemperatureUsualMeasurementPlace();
    bool getCardLocked();
    wxString getNotes();
    int getTemperatureCorrectionWhenMeasuredInMouth();
    int getTemperatureCorrectionWhenMeasuredInRectum();
    int getTemperatureCorrectionWhenMeasuredInVagina();
    int getTemperatureCorrectionForMeasurementTimeSake();

    /** STORING RESULTS */
    void setResultMucus1stDay( intArray );
    void addResultMucus1stDay(int);
    void removeResultMucus1stDay(int);
    void removeAtResultMucus1stDay(int);
    void clearResultMucus1stDay();
    void setResultMucus1stMoreFertileDay( intArray );
    void addResultMucus1stMoreFertileDay(int);
    void removeResultMucus1stMoreFertileDay(int);
    void removeAtResultMucus1stMoreFertileDay(int);
    void clearResultMucus1stMoreFertileDay();
    void setResultMucusPeak( intArray );
    void addResultMucusPeak(int);
    void removeResultMucusPeak(int);
    void removeAtResultMucusPeak(int);
    void clearResultMucusPeak();
    void setResultCervix1stDay( intArray );
    void addResultCervix1stDay(int);
    void removeResultCervix1stDay(int);
    void removeAtResultCervix1stDay(int);
    void clearResultCervix1stDay();
    void setResultCervixPeak( intArray );
    void addResultCervixPeak(int);
    void removeResultCervixPeak(int);
    void removeAtResultCervixPeak(int);
    void clearResultCervixPeak();
    void clearResultsTemperature();
    void setResultFertilePhaseStart( intArray );
    void addResultFertilePhaseStart(int);
    void removeResultFertilePhaseStart(int);
    void removeAtResultFertilePhaseStart(int);
    void clearResultFertilePhaseStart();
    void setResultInfertilePhaseStart( intArray );
    void addResultInfertilePhaseStart(int);
    void removeResultInfertilePhaseStart(int);
    void removeAtResultInfertilePhaseStart(int);
    void clearResultInfertilePhaseStart();
    void setResultTemperatureLowLevelValue( int );
    void setResultTemperatureLowLevelStart( int );
    void setResultTemperatureHighLevelStart( int );
    void setResultTemperatureHighLevelEnd( int );

    /** READING RESULTS */
    intArray getResultMucus1stDay();
    intArray getResultMucus1stMoreFertileDay();
    intArray getResultMucusPeak();
    intArray getResultCervix1stDay();
    intArray getResultCervixPeak();
    int getResultTemperatureLowLevelValue();
    int getResultTemperatureLowLevelStart();
    int getResultTemperatureHighLevelStart();
    int getResultTemperatureHighLevelEnd();
    intArray getResultFertilePhaseStart();
    intArray getResultInfertilePhaseStart();

    bool isResultMucus1stDay(int day = -1);
    bool isResultMucus1stMoreFertileDay(int day = -1);
    bool isResultMucusPeak(int day = -1);
    bool isResultCervix1stDay(int day = -1);
    bool isResultCervixPeak(int day = -1);
    bool isResultTemperatureLowLevelStart(int day = -1);
    bool isResultTemperatureHighLevelStart(int day = -1);
    bool isResultTemperatureHighLevelEnd(int day = -1);
    bool isResultFertilePhaseStart(int day = -1);
    bool isResultInfertilePhaseStart(int day = -1);

    /** helping methods */
private:
    void setResult( intArray, intArray* );
    void addResult( int, intArray* );
    bool isResultDefinedInArray(intArray, int);
};


/*******************************************************************************
********************************************************************************
*******************************************************************************/

WX_DECLARE_HASH_MAP( int, cardEntry*, wxIntegerHash, wxIntegerEqual, cardEntryHash );

/*******************************************************************************
********************************************************************************
*******************************************************************************/

#endif

