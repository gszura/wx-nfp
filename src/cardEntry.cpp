/*******************************************************************************
//
// Name:        cardEntry.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/


#include "cardEntry.h"


/*******************************************************************************
*** CONSTRUCTORS ***************************************************************
*******************************************************************************/

/**
 *
 */
cardEntry::cardEntry()
{
    m_firstDayOfCycle = wxDateTime::Today();
    m_stoppedPills = false;
    m_corruptedData = false;
    m_temperatureUsualMeasurementTime = wxDateTime(7, 00, 0, 0);
    m_temperatureUsualMeasurementPlace = PLACE_VAGINA;
    m_cardLocked = false;
    m_notes = wxEmptyString;
    m_cycleType = CYCLE_TYPE_NORMAL;
    m_basicInfertilePattern = CYCLE_BIP_AUTO;
    m_temperatureCorrectionWhenMeasuredInMouth    = 0;
    m_temperatureCorrectionWhenMeasuredInRectum   = 0;
    m_temperatureCorrectionWhenMeasuredInVagina   = 0;
    m_temperatureCorrectionForMeasurementTimeSake = -10;

    m_resultTemperatureLowLevelValue = -1;
    m_resultTemperatureLowLevelStart = -1;
    m_resultTemperatureHighLevelStart = -1;
    m_resultTemperatureHighLevelEnd = -1;
    m_resultTemperatureLevelsAuto = -1;
}

/**
 *
 */
cardEntry::cardEntry(cardEntry *prevCard)
{
    m_firstDayOfCycle = prevCard->getFirstDayOfCycle() + wxDateSpan::Days( prevCard->getDaysCount() );
    m_stoppedPills = false;
    m_corruptedData = false;
    m_temperatureUsualMeasurementTime = prevCard->getTemperatureUsualMeasurementTime();
    m_temperatureUsualMeasurementPlace = prevCard->getTemperatureUsualMeasurementPlace();
    m_cardLocked = false;
    m_notes = wxEmptyString;
    m_cycleType = CYCLE_TYPE_NORMAL;
    if (prevCard->getCycleType() == CYCLE_TYPE_PREGNANCY)
        m_cycleType = CYCLE_TYPE_AFTER_PREGNANCY;
    m_basicInfertilePattern = CYCLE_BIP_AUTO;
    m_temperatureCorrectionWhenMeasuredInMouth    = prevCard->getTemperatureCorrectionWhenMeasuredInMouth();
    m_temperatureCorrectionWhenMeasuredInRectum   = prevCard->getTemperatureCorrectionWhenMeasuredInRectum();
    m_temperatureCorrectionWhenMeasuredInVagina   = prevCard->getTemperatureCorrectionWhenMeasuredInVagina();
    m_temperatureCorrectionForMeasurementTimeSake = prevCard->getTemperatureCorrectionForMeasurementTimeSake();

    m_resultTemperatureLowLevelValue = -1;
    m_resultTemperatureLowLevelStart = -1;
    m_resultTemperatureHighLevelStart = -1;
    m_resultTemperatureHighLevelEnd = -1;
    m_resultTemperatureLevelsAuto = -1;
}

/*******************************************************************************
*** STORING AND READING DAYS OJECTS ********************************************
*******************************************************************************/

/**
 * Add new day to the card. Keys in hash key 'm_days' are [1...]
 */
int cardEntry::addNewDay(dayEntry *day)
{
    if (day == NULL) {
        m_days[ getDaysCount()+1 ] = new dayEntry();
    } else {
        m_days[ getDaysCount()+1 ] = day;
    }

    return getDaysCount();
}

/**
 *
 */
bool cardEntry::removeLastDay()
{
    int daysCount = getDaysCount();
    if (daysCount > 1) {
        m_days.erase(daysCount);
    }

    if (getDaysCount() == daysCount-1) {
        return true;
    } else {
        return false;
    }
}

/**
 *
 */
bool cardEntry::removeAllDays()
{
    m_days.clear();

    if (getDaysCount() == 0) {
        return true;
    } else {
        return false;
    }
}

/**
 *
 */
int cardEntry::getDaysCount()
{
    return m_days.size();
}

/**
 *
 */
dayEntry * cardEntry::getDay(int id)
{
    if ( m_days.count(id) == 0) {
        return NULL;
    }
    return m_days[id];
}

/**
 *
 */
bool cardEntry::dayExist(int id)
{
    if ( m_days.count(id) == 0) {
        return false;
    }
    return true;
}

/*******************************************************************************
*** STORING THE DATA ***********************************************************
*******************************************************************************/

/**
 *
 */
void cardEntry::setFirstDayOfCycle(wxDateTime value)
{
    m_firstDayOfCycle = value;
}

/**
 *
 */
void cardEntry::setStoppedPills(bool value)
{
    m_stoppedPills= value;
}

/**
 *
 */
void cardEntry::setCorruptedData(bool value)
{
    m_corruptedData = value;
}

/**
 *
 */
void cardEntry::setTemperatureUsualMeasurementTime(wxDateTime value)
{
    m_temperatureUsualMeasurementTime = value;
}

/**
 *
 */
void cardEntry::setTemperatureUsualMeasurementPlace(int value)
{
    m_temperatureUsualMeasurementPlace = value;
}

/**
 *
 */
void cardEntry::setCardLocked(bool value)
{
    m_cardLocked = value;
}

/**
 *
 */
void cardEntry::setNotes(wxString value)
{
    m_notes = value;
}

/**
 *
 */
void cardEntry::setCycleType(int value)
{
    m_cycleType = value;
}

/**
 *
 */
void cardEntry::setBasicInfertilePattern(int value)
{
    m_basicInfertilePattern = value;
}

/**
 *
 */
void cardEntry::setTemperatureCorrectionWhenMeasuredInMouth(int value)
{
    m_temperatureCorrectionWhenMeasuredInMouth = value;
}

/**
 *
 */
void cardEntry::setTemperatureCorrectionWhenMeasuredInRectum(int value)
{
    m_temperatureCorrectionWhenMeasuredInRectum = value;
}

/**
 *
 */
void cardEntry::setTemperatureCorrectionWhenMeasuredInVagina(int value)
{
    m_temperatureCorrectionWhenMeasuredInVagina = value;
}

/**
 *
 */
void cardEntry::setTemperatureCorrectionForMeasurementTimeSake(int value)
{
    m_temperatureCorrectionForMeasurementTimeSake = value;
}

/*******************************************************************************
*** READING THE DATA ***********************************************************
*******************************************************************************/

/**
 *
 */
wxDateTime cardEntry::getFirstDayOfCycle()
{
    return m_firstDayOfCycle;
}

/**
 *
 */
bool cardEntry::getStoppedPills()
{
    return m_stoppedPills;
}

/**
 *
 */
bool cardEntry::getCorruptedData()
{
    return m_corruptedData;
}


/**
 *
 */
wxDateTime cardEntry::getTemperatureUsualMeasurementTime()
{
    return m_temperatureUsualMeasurementTime;
}

/**
 *
 */
int cardEntry::getTemperatureUsualMeasurementPlace()
{
    return m_temperatureUsualMeasurementPlace;
}

/**
 *
 */
bool cardEntry::getCardLocked()
{
    return m_cardLocked;
}

/**
 *
 */
wxString cardEntry::getNotes()
{
    return m_notes;
}

/**
 *
 */
int cardEntry::getCycleType()
{
    return m_cycleType;
}

/**
 *
 */
int cardEntry::getBasicInfertilePattern()
{
    return m_basicInfertilePattern;
}

/**
 *
 */
int cardEntry::getTemperatureCorrectionWhenMeasuredInMouth()
{
    return m_temperatureCorrectionWhenMeasuredInMouth;
}

/**
 *
 */
int cardEntry::getTemperatureCorrectionWhenMeasuredInRectum()
{
    return m_temperatureCorrectionWhenMeasuredInRectum;
}

/**
 *
 */
int cardEntry::getTemperatureCorrectionWhenMeasuredInVagina()
{
    return m_temperatureCorrectionWhenMeasuredInVagina;
}

/**
 *
 */
int cardEntry::getTemperatureCorrectionForMeasurementTimeSake()
{
    return m_temperatureCorrectionForMeasurementTimeSake;
}

/*******************************************************************************
*** STORING RESULTS ************************************************************
*******************************************************************************/

/**
 *
 */
void cardEntry::setResultMucus1stDay( intArray input, intArray inputAuto )
{
    setResult(input, inputAuto, &m_resultMucus1stDay, &m_resultMucus1stDayAuto);
}

/**
 *
 */
void cardEntry::addResultMucus1stDay(int value, bool autoset)
{
    addResult(value, &m_resultMucus1stDay, &m_resultMucus1stDayAuto, autoset);
}

/**
 *
 */
void cardEntry::removeResultMucus1stDay(int value)
{
    m_resultMucus1stDay.Remove(value);

    if (isResultDefinedInArray(&m_resultMucus1stDayAuto, value))
        m_resultMucus1stDayAuto.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultMucus1stDay(int index)
{
    if (isResultDefinedInArray(&m_resultMucus1stDayAuto, m_resultMucus1stDay[index]))
        m_resultMucus1stDayAuto.Remove(m_resultMucus1stDay[index]);

    m_resultMucus1stDay.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultMucus1stDay()
{
    m_resultMucus1stDay.Clear();
    m_resultMucus1stDayAuto.Clear();
}

/**
 *
 */
void cardEntry::setResultMucus1stMoreFertileDay( intArray input, intArray inputAuto )
{
    setResult(input, inputAuto, &m_resultMucus1stMoreFertileDay, &m_resultMucus1stMoreFertileDayAuto);
}

/**
 *
 */
void cardEntry::addResultMucus1stMoreFertileDay(int value, bool autoset)
{
    addResult(value, &m_resultMucus1stMoreFertileDay, &m_resultMucus1stMoreFertileDayAuto, autoset);
}

/**
 *
 */
void cardEntry::removeResultMucus1stMoreFertileDay(int value)
{
    m_resultMucus1stMoreFertileDay.Remove(value);

    if (isResultDefinedInArray(&m_resultMucus1stMoreFertileDayAuto, value))
        m_resultMucus1stMoreFertileDayAuto.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultMucus1stMoreFertileDay(int index)
{
    if (isResultDefinedInArray(&m_resultMucus1stMoreFertileDayAuto, m_resultMucus1stMoreFertileDay[index]))
        m_resultMucus1stMoreFertileDayAuto.Remove(m_resultMucus1stMoreFertileDay[index]);
    m_resultMucus1stMoreFertileDay.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultMucus1stMoreFertileDay()
{
    m_resultMucus1stMoreFertileDay.Clear();
    m_resultMucus1stMoreFertileDayAuto.Clear();
}

/**
 *
 */
void cardEntry::setResultMucusPeak( intArray input, intArray inputAuto )
{
    setResult(input, inputAuto, &m_resultMucusPeak, &m_resultMucusPeakAuto);
}

/**
 *
 */
void cardEntry::addResultMucusPeak(int value, bool autoset)
{
    addResult(value, &m_resultMucusPeak, &m_resultMucusPeakAuto, autoset);
}

/**
 *
 */
void cardEntry::removeResultMucusPeak(int value)
{
    m_resultMucusPeak.Remove(value);

    if (isResultDefinedInArray(&m_resultMucusPeakAuto, value))
        m_resultMucusPeakAuto.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultMucusPeak(int index)
{
    if (isResultDefinedInArray(&m_resultMucusPeakAuto, m_resultMucusPeak[index]))
        m_resultMucusPeakAuto.Remove(m_resultMucusPeak[index]);
    m_resultMucusPeak.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultMucusPeak()
{
    m_resultMucusPeak.Clear();
    m_resultMucusPeakAuto.Clear();
}

/**
 *
 */
void cardEntry::setResultCervix1stDay( intArray input, intArray inputAuto )
{
    setResult(input, inputAuto, &m_resultCervix1stDay, &m_resultCervix1stDayAuto);
}

/**
 *
 */
void cardEntry::addResultCervix1stDay(int value, bool autoset)
{
    addResult(value, &m_resultCervix1stDay, &m_resultCervix1stDayAuto, autoset);
}

/**
 *
 */
void cardEntry::removeResultCervix1stDay(int value)
{
    m_resultCervix1stDay.Remove(value);

    if (isResultDefinedInArray(&m_resultCervix1stDayAuto, value))
        m_resultCervix1stDayAuto.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultCervix1stDay(int index)
{
    if (isResultDefinedInArray(&m_resultCervix1stDayAuto, m_resultCervix1stDay[index]))
        m_resultCervix1stDayAuto.Remove(m_resultCervix1stDay[index]);
    m_resultCervix1stDay.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultCervix1stDay()
{
    m_resultCervix1stDay.Clear();
    m_resultCervix1stDayAuto.Clear();
}

/**
 *
 */
void cardEntry::setResultCervixPeak( intArray input, intArray inputAuto )
{
    setResult(input, inputAuto, &m_resultCervixPeak, &m_resultCervixPeakAuto);
}

/**
 *
 */
void cardEntry::addResultCervixPeak(int value, bool autoset)
{
    addResult(value, &m_resultCervixPeak, &m_resultCervixPeakAuto, autoset);
}

/**
 *
 */
void cardEntry::removeResultCervixPeak(int value)
{
    m_resultCervixPeak.Remove(value);

    if (isResultDefinedInArray(&m_resultCervixPeakAuto, value))
        m_resultCervixPeakAuto.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultCervixPeak(int index)
{
    if (isResultDefinedInArray(&m_resultCervixPeakAuto, m_resultCervixPeak[index]))
        m_resultCervixPeakAuto.Remove(m_resultCervixPeak[index]);
    m_resultCervixPeak.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultCervixPeak()
{
    m_resultCervixPeak.Clear();
    m_resultCervixPeakAuto.Clear();
}

/**
 *
 */
void cardEntry::setResultFertilePhaseStart( intArray input, intArray inputAuto )
{
    setResult(input, inputAuto, &m_resultFertilePhaseStart, &m_resultFertilePhaseStartAuto);
}

/**
 *
 */
void cardEntry::addResultFertilePhaseStart(int value, bool autoset)
{
    addResult(value, &m_resultFertilePhaseStart, &m_resultFertilePhaseStartAuto, autoset);
}

/**
 *
 */
void cardEntry::removeResultFertilePhaseStart(int value)
{
    m_resultFertilePhaseStart.Remove(value);

    if (isResultDefinedInArray(&m_resultFertilePhaseStartAuto, value))
        m_resultFertilePhaseStartAuto.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultFertilePhaseStart(int index)
{
    if (isResultDefinedInArray(&m_resultFertilePhaseStartAuto, m_resultFertilePhaseStart[index]))
        m_resultFertilePhaseStartAuto.Remove(m_resultFertilePhaseStart[index]);
    m_resultFertilePhaseStart.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultFertilePhaseStart()
{
    m_resultFertilePhaseStart.Clear();
    m_resultFertilePhaseStartAuto.Clear();
}

/**
 *
 */
void cardEntry::setResultInfertilePhaseStart( intArray input, intArray inputAuto )
{
    setResult(input, inputAuto, &m_resultInfertilePhaseStart, &m_resultInfertilePhaseStartAuto);
}

/**
 *
 */
void cardEntry::addResultInfertilePhaseStart(int value, bool autoset)
{
    addResult(value, &m_resultInfertilePhaseStart, &m_resultInfertilePhaseStartAuto, autoset);
}

/**
 *
 */
void cardEntry::removeResultInfertilePhaseStart(int value)
{
    m_resultInfertilePhaseStart.Remove(value);

    if (isResultDefinedInArray(&m_resultInfertilePhaseStartAuto, value))
        m_resultInfertilePhaseStartAuto.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultInfertilePhaseStart(int index)
{
    if (isResultDefinedInArray(&m_resultInfertilePhaseStartAuto, m_resultInfertilePhaseStart[index]))
        m_resultInfertilePhaseStartAuto.Remove(m_resultInfertilePhaseStart[index]);
    m_resultInfertilePhaseStart.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultInfertilePhaseStart()
{
    m_resultInfertilePhaseStart.Clear();
    m_resultInfertilePhaseStartAuto.Clear();
}

/**
 *
 */
void cardEntry::setResultsTemperature( int lowLevelStart, int lowLevelValue, int highLevelStart, int highLevelEnd, bool autoset)
{
    m_resultTemperatureLowLevelStart  = lowLevelStart;
    m_resultTemperatureLowLevelValue  = lowLevelValue;
    m_resultTemperatureHighLevelStart  = highLevelStart;
    m_resultTemperatureHighLevelEnd  = highLevelEnd;
    m_resultTemperatureLevelsAuto = autoset;
}

/**
 *
 */
void cardEntry::clearResultsTemperature()
{
    m_resultTemperatureLowLevelValue  = -1;
    m_resultTemperatureLowLevelStart  = -1;
    m_resultTemperatureHighLevelStart = -1;
    m_resultTemperatureHighLevelEnd   = -1;
    m_resultTemperatureLevelsAuto     = false;
}



/*******************************************************************************
*** READING RESULTS ************************************************************
*******************************************************************************/

/**
 *
 */
intArray cardEntry::getResultMucus1stDay()
{
    return m_resultMucus1stDay;
}

/**
 *
 */
intArray cardEntry::getResultMucus1stMoreFertileDay()
{
    return m_resultMucus1stMoreFertileDay;
}

/**
 *
 */
intArray cardEntry::getResultMucusPeak()
{
    return m_resultMucusPeak;
}

/**
 *
 */
intArray cardEntry::getResultCervix1stDay()
{
    return m_resultCervix1stDay;
}

/**
 *
 */
intArray cardEntry::getResultCervixPeak()
{
    return m_resultCervixPeak;
}

/**
 *
 */
int cardEntry::getResultTemperatureLowLevelValue()
{
    return m_resultTemperatureLowLevelValue;
}

/**
 *
 */
int cardEntry::getResultTemperatureLowLevelStart()
{
    return m_resultTemperatureLowLevelStart;
}

/**
 *
 */
int cardEntry::getResultTemperatureHighLevelStart()
{
    return m_resultTemperatureHighLevelStart;
}

/**
 *
 */
int cardEntry::getResultTemperatureHighLevelEnd()
{
    return m_resultTemperatureHighLevelEnd;
}

/**
 *
 */
intArray cardEntry::getResultFertilePhaseStart()
{
    return m_resultFertilePhaseStart;
}

/**
 *
 */
intArray cardEntry::getResultInfertilePhaseStart()
{
    return m_resultInfertilePhaseStart;
}

/**
*
*/
intArray cardEntry::getResultMucus1stDayAuto()
{
    return m_resultMucus1stDayAuto;
}

/**
*
*/
intArray cardEntry::getResultMucus1stMoreFertileDayAuto()
{
    return m_resultMucus1stMoreFertileDayAuto;
}

/**
*
*/
intArray cardEntry::getResultMucusPeakAuto()
{
    return m_resultMucusPeakAuto;
}

/**
*
*/
intArray cardEntry::getResultCervix1stDayAuto()
{
    return m_resultCervix1stDayAuto;
}

/**
*
*/
intArray cardEntry::getResultCervixPeakAuto()
{
    return m_resultCervixPeakAuto;
}

/**
*
*/
bool cardEntry::isResultTemperatureLevelsAuto()
{
    return m_resultTemperatureLevelsAuto;
}

/**
*
*/
intArray cardEntry::getResultFertilePhaseStartAuto()
{
    return m_resultFertilePhaseStartAuto;
}

/**
*
*/
intArray cardEntry::getResultInfertilePhaseStartAuto()
{
    return m_resultInfertilePhaseStartAuto;
}


/**
 * Check if there is an result defined for selected day.
 * If 'day' param == -100 then return true if there is any result defined.
 */
bool cardEntry::isResultMucus1stDay(int day)
{
    return isResultDefinedInArray(&m_resultMucus1stDay, day);
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param == -100 then return true if there is any result defined.
 */
bool cardEntry::isResultMucus1stMoreFertileDay(int day)
{
    return isResultDefinedInArray(&m_resultMucus1stMoreFertileDay, day);
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param == -100 then return true if there is any result defined.
 */
bool cardEntry::isResultMucusPeak(int day)
{
    return isResultDefinedInArray(&m_resultMucusPeak, day);
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param == -100 then return true if there is any result defined.
 */
bool cardEntry::isResultCervix1stDay(int day)
{
    return isResultDefinedInArray(&m_resultCervix1stDay, day);
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param == -100 then return true if there is any result defined.
 */
bool cardEntry::isResultCervixPeak(int day)
{
    return isResultDefinedInArray(&m_resultCervixPeak, day);
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param == -100 then return true if there is any result defined.
 */
bool cardEntry::isResultTemperatureLowLevelStart(int day)
{
    if ( m_resultTemperatureLowLevelStart == day) {
        return true;
    } else {
        return false;
    }
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param == -100 then return true if there is any result defined.
 */
bool cardEntry::isResultTemperatureHighLevelStart(int day)
{
    if ( m_resultTemperatureHighLevelStart == day) {
        return true;
    } else {
        return false;
    }
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param == -100 then return true if there is any result defined.
 */
bool cardEntry::isResultTemperatureHighLevelEnd(int day)
{
    if ( m_resultTemperatureHighLevelEnd == day) {
        return true;
    } else {
        return false;
    }
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param == -100 then return true if there is any result defined.
 */
bool cardEntry::isResultFertilePhaseStart(int day)
{
    return isResultDefinedInArray(&m_resultFertilePhaseStart, day);
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param == -100 then return true if there is any result defined.
 */
bool cardEntry::isResultInfertilePhaseStart(int day)
{
    return isResultDefinedInArray(&m_resultInfertilePhaseStart, day);
}


bool cardEntry::isResultMucus1stDaySet()
{
    if (m_resultMucus1stDay.IsEmpty()) {
        return false;
    } else {
        return true;
    }
}

bool cardEntry::isResultMucus1stMoreFertileDaySet()
{
    if (m_resultMucus1stMoreFertileDay.IsEmpty()) {
        return false;
    } else {
        return true;
    }
}

bool cardEntry::isResultMucusPeakSet()
{
    if (m_resultMucusPeak.IsEmpty()) {
        return false;
    } else {
        return true;
    }
}

bool cardEntry::isResultCervix1stDaySet()
{
    if (m_resultCervix1stDay.IsEmpty()) {
        return false;
    } else {
        return true;
    }
}

bool cardEntry::isResultCervixPeakSet()
{
    if (m_resultCervixPeak.IsEmpty()) {
        return false;
    } else {
        return true;
    }
}

bool cardEntry::isResultTemperatureLevelSet()
{
    if ( m_resultTemperatureHighLevelStart > -1) {
        return true;
    } else {
        return false;
    }
}

bool cardEntry::isResultFertilePhaseStartSet()
{
    if (m_resultFertilePhaseStart.IsEmpty()) {
        return false;
    } else {
        return true;
    }
}

bool cardEntry::isResultInfertilePhaseStartSet()
{
    if (m_resultInfertilePhaseStart.IsEmpty()) {
        return false;
    } else {
        return true;
    }
}

/*******************************************************************************
*** helping methods ************************************************************
*******************************************************************************/

/**
*
*/
void cardEntry::setResult( intArray input, intArray inputAuto, intArray *inArray, intArray *inArrayAuto )
{
    if ( !input.IsEmpty() )
        for (size_t i=0; i<input.GetCount(); i++) {
            addResult(input[i], inArray, inArrayAuto, isResultDefinedInArray(inArrayAuto, input[i]));
        }
}

/**
 *
 */
void cardEntry::addResult( int value, intArray *inArray, intArray *inArrayAuto, bool autoset)
{
    bool added = false;
    if ( !inArray->IsEmpty() ) {
        for (size_t i=0; i<inArray->GetCount(); i++) {
            if (inArray->Item(i) > value) {
                inArray->Insert(value, i);
                added = true;
                break;
            }
        }
    }
    if (!added)
        inArray->Add( value );

    added = false;
    if (autoset) {
        if ( !inArrayAuto->IsEmpty() ) {
            for (size_t i=0; i<inArrayAuto->GetCount(); i++) {
                if (inArrayAuto->Item(i) > value) {
                    inArrayAuto->Insert(value, i);
                    added = true;
                    break;
                }
            }
        }
        if (!added)
            inArrayAuto->Add( value );
    }
}

/**
 * Check if there is an result defined in the array for selected day
 */
bool cardEntry::isResultDefinedInArray(intArray *inArray, int day)
{
    if ( inArray->IsEmpty() ) {
        return false;
    }

    if (day < 0) {
        return false;
    }

    for (size_t i=0; i<inArray->GetCount(); i++) {
        if (inArray->Item(i)== day) {
            return true;
        }
    }
    return false;
}

void cardEntry::removeAllResults()
{
    clearResultMucus1stDay();
    clearResultMucus1stMoreFertileDay();
    clearResultMucusPeak();
    clearResultCervix1stDay();
    clearResultCervixPeak();
    clearResultsTemperature();
    clearResultFertilePhaseStart();
    clearResultInfertilePhaseStart();
}

void cardEntry::removeResultsSetAutomatically()
{
    removeResultsSetAutomatically(&m_resultMucus1stDay, &m_resultMucus1stDayAuto);
    removeResultsSetAutomatically(&m_resultMucus1stMoreFertileDay, &m_resultMucus1stMoreFertileDayAuto);
    removeResultsSetAutomatically(&m_resultMucusPeak, &m_resultMucusPeakAuto);
    removeResultsSetAutomatically(&m_resultCervix1stDay, &m_resultCervix1stDayAuto);
    removeResultsSetAutomatically(&m_resultCervixPeak, &m_resultCervixPeakAuto);
    removeResultsSetAutomatically(&m_resultFertilePhaseStart, &m_resultFertilePhaseStartAuto);
    removeResultsSetAutomatically(&m_resultInfertilePhaseStart, &m_resultInfertilePhaseStartAuto);
    if (isResultTemperatureLevelsAuto());
    clearResultsTemperature();
}

void cardEntry::removeResultsSetAutomatically(intArray *inArray, intArray *inArrayAuto)
{
    if ( !inArrayAuto->IsEmpty() ) {
        for (size_t i=0; i<inArrayAuto->GetCount(); i++) {
            inArray->Remove(inArrayAuto->Item(i));
        }
    }
    inArrayAuto->Clear();
}



/*******************************************************************************
********************************************************************************
*******************************************************************************/

