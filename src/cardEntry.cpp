/*******************************************************************************
//
// Name:        cardEntry.cpp
// Author:      enkeli
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
cardEntry::cardEntry() {
    m_firstDayOfCycle = wxDateTime::Today();
    m_temperatureUsualMeasurementTime = wxDateTime(7, 00, 0, 0);
    m_temperatureUsualMeasurementPlace = PLACE_VAGINA;
    m_cardLocked = false;
    m_notes = wxEmptyString;
    m_temperatureCorrectionWhenMeasuredInMouth    = 0;
    m_temperatureCorrectionWhenMeasuredInRectum   = 0;
    m_temperatureCorrectionWhenMeasuredInVagina   = 0;
    m_temperatureCorrectionForMeasurementTimeSake = -10;

    m_resultTemperatureLowLevelValue = -1;
    m_resultTemperatureLowLevelStart = -1;
    m_resultTemperatureHighLevelStart = -1;
    m_resultTemperatureHighLevelEnd = -1;
}

/**
 *
 */
cardEntry::cardEntry(cardEntry *prevCard) {
    m_firstDayOfCycle = prevCard->getFirstDayOfCycle() + wxDateSpan::Days( prevCard->getDaysCount() );
    m_temperatureUsualMeasurementTime = prevCard->getTemperatureUsualMeasurementTime();
    m_temperatureUsualMeasurementPlace = prevCard->getTemperatureUsualMeasurementPlace();
    m_cardLocked = false;
    m_notes = wxEmptyString;
    m_temperatureCorrectionWhenMeasuredInMouth    = prevCard->getTemperatureCorrectionWhenMeasuredInMouth();
    m_temperatureCorrectionWhenMeasuredInRectum   = prevCard->getTemperatureCorrectionWhenMeasuredInRectum();
    m_temperatureCorrectionWhenMeasuredInVagina   = prevCard->getTemperatureCorrectionWhenMeasuredInVagina();
    m_temperatureCorrectionForMeasurementTimeSake = prevCard->getTemperatureCorrectionForMeasurementTimeSake();

    m_resultTemperatureLowLevelValue = -1;
    m_resultTemperatureLowLevelStart = -1;
    m_resultTemperatureHighLevelStart = -1;
    m_resultTemperatureHighLevelEnd = -1;
}

/*******************************************************************************
*** STORING AND READING DAYS OJECTS ********************************************
*******************************************************************************/

/**
 * Add new day to the card. Keys in hash key 'm_days' are [1...]
 */
int cardEntry::addNewDay(dayEntry *day) {
    if (day == NULL)
        m_days[ getDaysCount()+1 ] = new dayEntry();
    else
        m_days[ getDaysCount()+1 ] = day;

    return getDaysCount();
}

/**
 *
 */
bool cardEntry::removeLastDay() {
    int daysCount = getDaysCount();
    if (daysCount > 1)
        m_days.erase(daysCount);

    if (getDaysCount() == daysCount-1)
        return true;
    else
        return false;
}

/**
 *
 */
bool cardEntry::removeAllDays() {
    m_days.clear();

    if (getDaysCount() == 0)
        return true;
    else
        return false;
}

/**
 *
 */
int cardEntry::getDaysCount() {
    return m_days.size();
}

/**
 *
 */
dayEntry * cardEntry::getDay(int id) {
    if ( m_days.count(id) == 0) {
        return NULL;
    }
    return m_days[id];
}

/**
 *
 */
bool cardEntry::dayExist(int id) {
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
void cardEntry::setFirstDayOfCycle(wxDateTime value) {
    m_firstDayOfCycle = value;
}

/**
 *
 */
void cardEntry::setTemperatureUsualMeasurementTime(wxDateTime value) {
    m_temperatureUsualMeasurementTime = value;
}

/**
 *
 */
void cardEntry::setTemperatureUsualMeasurementPlace(int value) {
    m_temperatureUsualMeasurementPlace = value;
}

/**
 *
 */
void cardEntry::setCardLocked(bool value) {
    m_cardLocked = value;
}

/**
 *
 */
void cardEntry::setNotes(wxString value) {
    m_notes = value;
}

/**
 *
 */
void cardEntry::setTemperatureCorrectionWhenMeasuredInMouth(int value) {
    m_temperatureCorrectionWhenMeasuredInMouth = value;
}

/**
 *
 */
void cardEntry::setTemperatureCorrectionWhenMeasuredInRectum(int value) {
    m_temperatureCorrectionWhenMeasuredInRectum = value;
}

/**
 *
 */
void cardEntry::setTemperatureCorrectionWhenMeasuredInVagina(int value) {
    m_temperatureCorrectionWhenMeasuredInVagina = value;
}

/**
 *
 */
void cardEntry::setTemperatureCorrectionForMeasurementTimeSake(int value) {
    m_temperatureCorrectionForMeasurementTimeSake = value;
}

/*******************************************************************************
*** READING THE DATA ***********************************************************
*******************************************************************************/

/**
 *
 */
wxDateTime cardEntry::getFirstDayOfCycle() {
    return m_firstDayOfCycle;
}

/**
 *
 */
wxDateTime cardEntry::getTemperatureUsualMeasurementTime() {
    return m_temperatureUsualMeasurementTime;
}

/**
 *
 */
int cardEntry::getTemperatureUsualMeasurementPlace() {
    return m_temperatureUsualMeasurementPlace;
}

/**
 *
 */
bool cardEntry::getCardLocked() {
    return m_cardLocked;
}

/**
 *
 */
wxString cardEntry::getNotes() {
    return m_notes;
}

/**
 *
 */
int cardEntry::getTemperatureCorrectionWhenMeasuredInMouth() {
    return m_temperatureCorrectionWhenMeasuredInMouth;
}

/**
 *
 */
int cardEntry::getTemperatureCorrectionWhenMeasuredInRectum() {
    return m_temperatureCorrectionWhenMeasuredInRectum;
}

/**
 *
 */
int cardEntry::getTemperatureCorrectionWhenMeasuredInVagina() {
    return m_temperatureCorrectionWhenMeasuredInVagina;
}

/**
 *
 */
int cardEntry::getTemperatureCorrectionForMeasurementTimeSake() {
    return m_temperatureCorrectionForMeasurementTimeSake;
}

/*******************************************************************************
*** STORING RESULTS ************************************************************
*******************************************************************************/

/**
 *
 */
void cardEntry::setResultMucus1stDay( intArray input ) {
    setResult(input, &m_resultMucus1stDay);
}

/**
 *
 */
void cardEntry::addResultMucus1stDay(int value) {
    addResult(value, &m_resultMucus1stDay);
}

/**
 *
 */
void cardEntry::removeResultMucus1stDay(int value) {
    m_resultMucus1stDay.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultMucus1stDay(int index) {
    m_resultMucus1stDay.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultMucus1stDay() {
    m_resultMucus1stDay.Clear();
}

/**
 *
 */
void cardEntry::setResultMucus1stMoreFertileDay( intArray input ) {
    setResult(input, &m_resultMucus1stMoreFertileDay);
}

/**
 *
 */
void cardEntry::addResultMucus1stMoreFertileDay(int value) {
    addResult(value, &m_resultMucus1stMoreFertileDay);
}

/**
 *
 */
void cardEntry::removeResultMucus1stMoreFertileDay(int value) {
    m_resultMucus1stMoreFertileDay.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultMucus1stMoreFertileDay(int index) {
    m_resultMucus1stMoreFertileDay.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultMucus1stMoreFertileDay() {
    m_resultMucus1stMoreFertileDay.Clear();
}

/**
 *
 */
void cardEntry::setResultMucusPeak( intArray input ) {
    setResult(input, &m_resultMucusPeak);
}

/**
 *
 */
void cardEntry::addResultMucusPeak(int value) {
    addResult(value, &m_resultMucusPeak);
}

/**
 *
 */
void cardEntry::removeResultMucusPeak(int value) {
    m_resultMucusPeak.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultMucusPeak(int index) {
    m_resultMucusPeak.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultMucusPeak() {
    m_resultMucusPeak.Clear();
}

/**
 *
 */
void cardEntry::setResultCervix1stDay( intArray input ) {
    setResult(input, &m_resultCervix1stDay);
}

/**
 *
 */
void cardEntry::addResultCervix1stDay(int value) {
    addResult(value, &m_resultCervix1stDay);
}

/**
 *
 */
void cardEntry::removeResultCervix1stDay(int value) {
    m_resultCervix1stDay.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultCervix1stDay(int index) {
    m_resultCervix1stDay.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultCervix1stDay() {
    m_resultCervix1stDay.Clear();
}

/**
 *
 */
void cardEntry::setResultCervixPeak( intArray input ) {
    setResult(input, &m_resultCervixPeak);
}

/**
 *
 */
void cardEntry::addResultCervixPeak(int value) {
    addResult(value, &m_resultCervixPeak);
}

/**
 *
 */
void cardEntry::removeResultCervixPeak(int value) {
    m_resultCervixPeak.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultCervixPeak(int index) {
    m_resultCervixPeak.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultCervixPeak() {
    m_resultCervixPeak.Clear();
}

/**
 *
 */
void cardEntry::clearResultsTemperature() {
    m_resultTemperatureLowLevelValue  = -1;
    m_resultTemperatureLowLevelStart  = -1;
    m_resultTemperatureHighLevelStart = -1;
    m_resultTemperatureHighLevelEnd   = -1;
}

/**
 *
 */
void cardEntry::setResultFertilePhaseStart( intArray input ) {
    setResult(input, &m_resultFertilePhaseStart);
}

/**
 *
 */
void cardEntry::addResultFertilePhaseStart(int value) {
    addResult(value, &m_resultFertilePhaseStart);
}

/**
 *
 */
void cardEntry::removeResultFertilePhaseStart(int value) {
    m_resultFertilePhaseStart.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultFertilePhaseStart(int index) {
    m_resultFertilePhaseStart.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultFertilePhaseStart() {
    m_resultFertilePhaseStart.Clear();
}

/**
 *
 */
void cardEntry::setResultInfertilePhaseStart( intArray input ) {
    setResult(input, &m_resultInfertilePhaseStart);
}

/**
 *
 */
void cardEntry::addResultInfertilePhaseStart(int value) {
    addResult(value, &m_resultInfertilePhaseStart);
}

/**
 *
 */
void cardEntry::removeResultInfertilePhaseStart(int value) {
    m_resultInfertilePhaseStart.Remove(value);
}

/**
 *
 */
void cardEntry::removeAtResultInfertilePhaseStart(int index) {
    m_resultInfertilePhaseStart.RemoveAt(index);
}

/**
 *
 */
void cardEntry::clearResultInfertilePhaseStart() {
    m_resultInfertilePhaseStart.Clear();
}

/**
 *
 */
void cardEntry::setResultTemperatureLowLevelValue(int value) {
    m_resultTemperatureLowLevelValue  = value;
}

/**
 *
 */
void cardEntry::setResultTemperatureLowLevelStart(int value) {
    m_resultTemperatureLowLevelStart  = value;
}

/**
 *
 */
void cardEntry::setResultTemperatureHighLevelStart(int value) {
    m_resultTemperatureHighLevelStart  = value;
}

/**
 *
 */
void cardEntry::setResultTemperatureHighLevelEnd(int value) {
    m_resultTemperatureHighLevelEnd  = value;
}


/*******************************************************************************
*** READING RESULTS ************************************************************
*******************************************************************************/

/**
 *
 */
intArray cardEntry::getResultMucus1stDay() {
    return m_resultMucus1stDay;
}

/**
 *
 */
intArray cardEntry::getResultMucus1stMoreFertileDay() {
    return m_resultMucus1stMoreFertileDay;
}

/**
 *
 */
intArray cardEntry::getResultMucusPeak() {
    return m_resultMucusPeak;
}

/**
 *
 */
intArray cardEntry::getResultCervix1stDay() {
    return m_resultCervix1stDay;
}

/**
 *
 */
intArray cardEntry::getResultCervixPeak() {
    return m_resultCervixPeak;
}

/**
 *
 */
int cardEntry::getResultTemperatureLowLevelValue() {
    return m_resultTemperatureLowLevelValue;
}

/**
 *
 */
int cardEntry::getResultTemperatureLowLevelStart() {
    return m_resultTemperatureLowLevelStart;
}

/**
 *
 */
int cardEntry::getResultTemperatureHighLevelStart() {
    return m_resultTemperatureHighLevelStart;
}

/**
 *
 */
int cardEntry::getResultTemperatureHighLevelEnd() {
    return m_resultTemperatureHighLevelEnd;
}

/**
 *
 */
intArray cardEntry::getResultFertilePhaseStart() {
    return m_resultFertilePhaseStart;
}

/**
 *
 */
intArray cardEntry::getResultInfertilePhaseStart() {
    return m_resultInfertilePhaseStart;
}

/**
 * Check if there is an result defined for selected day.
 * If 'day' param < 0 then check if there is any result defined.
 */
bool cardEntry::isResultMucus1stDay(int day) {
    return isResultDefinedInArray(m_resultMucus1stDay, day);
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param < 0 then check if there is any result defined.
 */
bool cardEntry::isResultMucus1stMoreFertileDay(int day) {
    return isResultDefinedInArray(m_resultMucus1stMoreFertileDay, day);
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param < 0 then check if there is any result defined.
 */
bool cardEntry::isResultMucusPeak(int day) {
    return isResultDefinedInArray(m_resultMucusPeak, day);
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param < 0 then check if there is any result defined.
 */
bool cardEntry::isResultCervix1stDay(int day) {
    return isResultDefinedInArray(m_resultCervix1stDay, day);
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param < 0 then check if there is any result defined.
 */
bool cardEntry::isResultCervixPeak(int day) {
    return isResultDefinedInArray(m_resultCervixPeak, day);
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param < 0 then check if there is any result defined.
 */
bool cardEntry::isResultTemperatureLowLevelStart(int day) {
    if ( m_resultTemperatureLowLevelStart == day)
        return true;
    else
        return false;
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param < 0 then check if there is any result defined.
 */
bool cardEntry::isResultTemperatureHighLevelStart(int day) {
    if ( m_resultTemperatureHighLevelStart == day)
        return true;
    else
        return false;
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param < 0 then check if there is any result defined.
 */
bool cardEntry::isResultTemperatureHighLevelEnd(int day) {
    if ( m_resultTemperatureHighLevelEnd == day)
        return true;
    else
        return false;
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param < 0 then check if there is any result defined.
 */
bool cardEntry::isResultFertilePhaseStart(int day) {
    return isResultDefinedInArray(m_resultFertilePhaseStart, day);
}

/**
 * Check if there is an result defined for selected day
 * If 'day' param < 0 then check if there is any result defined.
 */
bool cardEntry::isResultInfertilePhaseStart(int day) {
    return isResultDefinedInArray(m_resultInfertilePhaseStart, day);
}

/*******************************************************************************
*** helping methods ************************************************************
*******************************************************************************/

/**
 *
 */
void cardEntry::setResult( intArray input, intArray *array ) {
    if ( !input.IsEmpty() )
        for (size_t i=0; i<input.GetCount(); i++)
            addResult(input[i], array);
    //array->Add( input[i] );
}

/**
 *
 */
void cardEntry::addResult( int value, intArray *array ) {
    if ( !array->IsEmpty() ) {
        for (size_t i=0; i<array->GetCount(); i++) {
            if (array->Item(i) > value) {
                array->Insert(value, i);
                return;
            }
        }
    }
    array->Add( value );
}

/**
 * Check if there is an result defined in the array for selected day
 * If 'day' param < 0 then check if there is any result defined.
 */
bool cardEntry::isResultDefinedInArray(intArray array, int day) {
    if ( array.IsEmpty() )
        return false;

    if (day < 0) {
        if ( array.IsEmpty() )
            return false;
        else
            return true;
    }

    for (size_t i=0; i<array.GetCount(); i++) {
        if (array[i] == day)
            return true;
    }
    return false;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

