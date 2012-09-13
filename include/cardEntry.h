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
    bool m_stoppedPills;                              // [x]
    bool m_corruptedData;                             // [x]
    wxDateTime m_temperatureUsualMeasurementTime;     // [hh:mm]
    int m_temperatureUsualMeasurementPlace;           // [-1 | 1-3]
    bool m_cardLocked;                                // [x]
    wxString m_notes;                                 // [<string>]
    int m_cycleType;                                  // 1-4
    int m_basicInfertilePattern;                      // 0-2
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

    // information which results have been set automatically
    intArray m_resultMucus1stDayAuto;                     // array of int
    intArray m_resultMucus1stMoreFertileDayAuto;          // array of int
    intArray m_resultMucusPeakAuto;                       // array of int
    intArray m_resultCervix1stDayAuto;                    // array of int
    intArray m_resultCervixPeakAuto;                      // array of int
    int m_resultTemperatureLevelsAuto;             // [dayNo]
    intArray m_resultInfertilePhaseStartAuto;             // array of int
    intArray m_resultFertilePhaseStartAuto;               // array of int

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
    void setStoppedPills(bool);
    void setCorruptedData(bool);
    void setTemperatureUsualMeasurementTime(wxDateTime);
    void setTemperatureUsualMeasurementPlace(int);
    void setCardLocked(bool);
    void setNotes(wxString);
    void setCycleType(int);
    void setBasicInfertilePattern(int);
    void setTemperatureCorrectionWhenMeasuredInMouth(int);
    void setTemperatureCorrectionWhenMeasuredInRectum(int);
    void setTemperatureCorrectionWhenMeasuredInVagina(int);
    void setTemperatureCorrectionForMeasurementTimeSake(int);

    /** READING THE DATA */
    wxDateTime getFirstDayOfCycle();
    bool getStoppedPills();
    bool getCorruptedData();
    wxDateTime getTemperatureUsualMeasurementTime();
    int getTemperatureUsualMeasurementPlace();
    bool getCardLocked();
    wxString getNotes();
    int getCycleType();
    int getBasicInfertilePattern();
    int getTemperatureCorrectionWhenMeasuredInMouth();
    int getTemperatureCorrectionWhenMeasuredInRectum();
    int getTemperatureCorrectionWhenMeasuredInVagina();
    int getTemperatureCorrectionForMeasurementTimeSake();

    /** STORING RESULTS */
    void setResultMucus1stDay( intArray, intArray );
    void addResultMucus1stDay(int, bool autoset = false);
    void removeResultMucus1stDay(int);
    void removeAtResultMucus1stDay(int);
    void clearResultMucus1stDay();
    void setResultMucus1stMoreFertileDay( intArray, intArray );
    void addResultMucus1stMoreFertileDay(int, bool autoset = false);
    void removeResultMucus1stMoreFertileDay(int);
    void removeAtResultMucus1stMoreFertileDay(int);
    void clearResultMucus1stMoreFertileDay();
    void setResultMucusPeak( intArray, intArray );
    void addResultMucusPeak(int, bool autoset = false);
    void removeResultMucusPeak(int);
    void removeAtResultMucusPeak(int);
    void clearResultMucusPeak();
    void setResultCervix1stDay( intArray, intArray );
    void addResultCervix1stDay(int, bool autoset = false);
    void removeResultCervix1stDay(int);
    void removeAtResultCervix1stDay(int);
    void clearResultCervix1stDay();
    void setResultCervixPeak( intArray, intArray );
    void addResultCervixPeak(int, bool autoset = false);
    void removeResultCervixPeak(int);
    void removeAtResultCervixPeak(int);
    void clearResultCervixPeak();
    void setResultsTemperature( int, int, int, int, bool autoset = false );
    void clearResultsTemperature();
    void setResultFertilePhaseStart( intArray, intArray );
    void addResultFertilePhaseStart(int, bool autoset = false);
    void removeResultFertilePhaseStart(int);
    void removeAtResultFertilePhaseStart(int);
    void clearResultFertilePhaseStart();
    void setResultInfertilePhaseStart( intArray, intArray );
    void addResultInfertilePhaseStart(int, bool autoset = false);
    void removeResultInfertilePhaseStart(int);
    void removeAtResultInfertilePhaseStart(int);
    void clearResultInfertilePhaseStart();

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

    intArray getResultMucus1stDayAuto();
    intArray getResultMucus1stMoreFertileDayAuto();
    intArray getResultMucusPeakAuto();
    intArray getResultCervix1stDayAuto();
    intArray getResultCervixPeakAuto();
    bool isResultTemperatureLevelsAuto();
    intArray getResultFertilePhaseStartAuto();
    intArray getResultInfertilePhaseStartAuto();

    bool isResultMucus1stDay(int day);
    bool isResultMucus1stMoreFertileDay(int day);
    bool isResultMucusPeak(int day);
    bool isResultCervix1stDay(int day);
    bool isResultCervixPeak(int day);
    bool isResultTemperatureLowLevelStart(int day);
    bool isResultTemperatureHighLevelStart(int day);
    bool isResultTemperatureHighLevelEnd(int day);
    bool isResultFertilePhaseStart(int day);
    bool isResultInfertilePhaseStart(int day);

    bool isResultMucus1stDaySet();
    bool isResultMucus1stMoreFertileDaySet();
    bool isResultMucusPeakSet();
    bool isResultCervix1stDaySet();
    bool isResultCervixPeakSet();
    bool isResultTemperatureLevelSet();
    bool isResultFertilePhaseStartSet();
    bool isResultInfertilePhaseStartSet();

    void removeAllResults();
    void removeResultsSetAutomatically();

    /** helping methods */
private:
    void setResult( intArray, intArray, intArray*, intArray* );
    void addResult( int, intArray*, intArray*, bool );
    bool isResultDefinedInArray(intArray*, int);
    void removeResultsSetAutomatically(intArray*, intArray*);
};


/*******************************************************************************
********************************************************************************
*******************************************************************************/

WX_DECLARE_HASH_MAP( int, cardEntry*, wxIntegerHash, wxIntegerEqual, cardEntryHash );

/*******************************************************************************
********************************************************************************
*******************************************************************************/

#endif
