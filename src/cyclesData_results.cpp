/*******************************************************************************
//
// m_name:      cycleDataClass.cpp
// Author:      Grzegorz Szura
// Description: Methods for defining results manually and calculating results automatically
//
*******************************************************************************/

#include "cyclesData.h"

/******************************************************************************
 ******************************************************************************
 ******************************************************************************/

/**
 * Check if day no and card no are corect. Check also if day and card objects exists
 */
bool cycleDataClass::checkSettingResultsBasicStaff(int cardNo, int dayNo)
{
    m_errorMessages = wxEmptyString;
    if ( cardNo < 1 || cardNo > getCardsCount() || dayNo < 1 || dayNo > getDaysCount() || getCard( cardNo ) == NULL || getDay( dayNo ) == NULL) {
        addErrorMessages( _T( "cycleDataClass::checkSettingResultsBasicStaff() failed" ) );
        return false;
    }
    return true;
}

/*******************************************************************************
***** DEFINING RESULTS MANUALLY ************************************************
*******************************************************************************/

/**
 * It seems that result is already defined on the card.
 * Ask user what should I do. If user answer:
 * Yes: remove result from other days on the card and set it only for this day
 * No: do not remove result from other days on the card and set it also for this day
 * Cancel: do nothing, let teh user check the situation
 */
int cycleDataClass::askForRemovingOtherResults()
{
    wxString message = _( "The result you want to set is already defined on the card.\nDo you want me to remove this result from other days?\nChoose:\n- 'Yes' to remove this result from other days on the card and set it only for this day.\n- 'No' to set it the result also for this day without removing result from other days.\n- 'Cancel' to exit without touching anything to let you check the situation");
    return wxMessageBox(message, _("What should I do?"), wxYES_NO | wxCANCEL);
}

/**
 * Set the day 'dayNo' of the card 'cardNo' as a first day when any kind of mucus appears.
 * If 'dayNo' != 1 || 'cardNo' != -1 then set it for active day of active card
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultMucus1stDay( int cardNo, int dayNo )
{
    if (cardNo == -1) cardNo = m_activeCard;
    if (dayNo == -1) dayNo = m_activeDay;
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) return NULL;

    int * ret = new int[2];
    ret[0] = dayNo;
    ret[1] = dayNo;
    cardEntry *card = getCard( cardNo );

    if ( card->isResultMucus1stDay(dayNo) ) {
        // unset and exit
        card->removeResultMucus1stDay( dayNo );
        return ret;
    }

    // check if other results are not defined in this day
    if ( card->isResultMucus1stMoreFertileDay(dayNo) )
        card->removeResultMucus1stMoreFertileDay( dayNo );

    if ( card->isResultMucusPeak(dayNo) ) {
        card->removeResultMucusPeak( dayNo );
        ret[1] = dayNo + 3;
    }

    if ( card->isResultMucus1stDay() ) {
        int answer = askForRemovingOtherResults();
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxYES) {
            // remove other results from the card
            card->clearResultMucus1stDay();
            ret[0] = 1;
            ret[1] = card->getDaysCount();
        }
        // set result
    }
    card->addResultMucus1stDay(dayNo);
    return ret;
}

/**
 * Set the day 'dayNo' of the card 'cardNo' as a first day when more fertile mucus appears.
 * If 'dayNo' != 1 || 'cardNo' != -1 then set it for active day of active card
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultMucus1stMoreFertileDay( int cardNo, int dayNo )
{
    if (cardNo == -1) cardNo = m_activeCard;
    if (dayNo == -1) dayNo = m_activeDay;
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) return NULL;

    int * ret = new int[2];
    ret[0] = dayNo;
    ret[1] = dayNo;
    cardEntry *card = getCard( cardNo );

    if ( card->isResultMucus1stMoreFertileDay(dayNo) ) {
        // unset and exit
        card->removeResultMucus1stMoreFertileDay( dayNo );
        return ret;
    }

    // check if other results are not defined in this day
    if ( card->isResultMucus1stDay(dayNo) )
        card->removeResultMucus1stDay( dayNo );

    if ( card->isResultMucusPeak(dayNo) ) {
        card->removeResultMucusPeak( dayNo );
        ret[1] = dayNo + 3;
    }

    if ( card->isResultMucus1stMoreFertileDay() ) {
        int answer = askForRemovingOtherResults();
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxYES) {
            // remove other results from the card
            card->clearResultMucus1stMoreFertileDay();
            ret[0] = 1;
            ret[1] = card->getDaysCount();
        }
        // set result
    }
    card->addResultMucus1stMoreFertileDay(dayNo);
    return ret;
}

/**
 * Set the day 'dayNo' of the card 'cardNo' as a day of mucus peak.
 * If 'dayNo' != 1 || 'cardNo' != -1 then set it for active day of active card
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultMucusPeak( int cardNo, int dayNo )
{
    if (cardNo == -1) cardNo = m_activeCard;
    if (dayNo == -1) dayNo = m_activeDay;
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) return NULL;

    int * ret = new int[2];
    ret[0] = dayNo;
    ret[1] = dayNo + 3;
    cardEntry *card = getCard( cardNo );

    if ( card->isResultMucusPeak(dayNo) ) {
        // unset and exit
        card->removeResultMucusPeak( dayNo );
        return ret;
    }

    // check if other results are not defined in this day
    if ( card->isResultMucus1stDay(dayNo) ) {
        card->removeResultMucus1stDay( dayNo );
    }
    if ( card->isResultMucus1stMoreFertileDay(dayNo) )
        card->removeResultMucus1stMoreFertileDay( dayNo );


    if ( card->isResultMucusPeak() ) {
        int answer = askForRemovingOtherResults();
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxYES) {
            // remove other results from the card
            card->clearResultMucusPeak();
            ret[0] = 1;
            ret[1] = card->getDaysCount();
        }
        // set result
    }
    card->addResultMucusPeak(dayNo);
    return ret;
}

/**
 * Set the day 'dayNo' of the card 'cardNo' as a first day when cervix starts changes.
 * If 'dayNo' != 1 || 'cardNo' != -1 then set it for active day of active card
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultCervix1stDay( int cardNo, int dayNo )
{
    if (cardNo == -1) cardNo = m_activeCard;
    if (dayNo == -1) dayNo = m_activeDay;
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) return NULL;

    int * ret = new int[2];
    ret[0] = dayNo;
    ret[1] = dayNo;
    cardEntry *card = getCard( cardNo );

    if ( card->isResultCervix1stDay(dayNo) ) {
        // unset and exit
        card->removeResultCervix1stDay( dayNo );
        return ret;
    }

    // check if other results are not defined in this day
    if ( card->isResultCervixPeak(dayNo) ) {
        card->removeResultCervixPeak( dayNo );
        ret[1] = dayNo + 3;
    }

    if ( card->isResultCervix1stDay() ) {
        int answer = askForRemovingOtherResults();
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxYES) {
            // remove other results from the card
            card->clearResultCervix1stDay();
            ret[0] = 1;
            ret[1] = card->getDaysCount();
        }
        // set result
    }
    card->addResultCervix1stDay(dayNo);
    return ret;
}

/**
 * Set the day 'dayNo' of the card 'cardNo' as a day of cervix peak.
 * If 'dayNo' != 1 || 'cardNo' != -1 then set it for active day of active card
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultCervixPeak( int cardNo, int dayNo )
{
    if (cardNo == -1) cardNo = m_activeCard;
    if (dayNo == -1) dayNo = m_activeDay;
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) return NULL;

    int * ret = new int[2];
    ret[0] = dayNo;
    ret[1] = dayNo + 3;
    cardEntry *card = getCard( cardNo );

    if ( card->isResultCervixPeak(dayNo) ) {
        // unset and exit
        card->removeResultCervixPeak( dayNo );
        return ret;
    }

    // check if other results are not defined in this day
    if ( card->isResultCervix1stDay(dayNo) )
        card->removeResultCervix1stDay( dayNo );

    if ( card->isResultCervixPeak() ) {
        int answer = askForRemovingOtherResults();
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxYES) {
            // remove other results from the card
            card->clearResultCervixPeak();
            ret[0] = 1;
            ret[1] = card->getDaysCount();
        }
        // set result
    }
    card->addResultCervixPeak(dayNo);
    return ret;
}

/**
 * Set the day 'dayNo' of the card 'cardNo' as a first day high level temperature.
 * If 'dayNo' != 1 || 'cardNo' != -1 then set it for active day of active card.
 * Calculate also:
 * - first day of low level temperature
 * - last day of high level temperature
 * - low level temperature value
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultTemperaturesLevels( int cardNo, int firstHighLevelDay, bool resetIfExists )
{
    if (cardNo == -1) cardNo = m_activeCard;
    if (firstHighLevelDay == -1) firstHighLevelDay = m_activeDay;
    if ( !checkSettingResultsBasicStaff (cardNo, firstHighLevelDay) ) return NULL;

    cardEntry *card = getCard( cardNo );

    if ( card->getResultTemperatureHighLevelStart() == firstHighLevelDay && resetIfExists ) {
        // unset and exit
        int * ret = new int[2];
        ret[0] = card->getResultTemperatureLowLevelStart();
        ret[1] = card->getResultTemperatureHighLevelEnd();
        if ( ret[0] < 1 ) ret[0] = firstHighLevelDay - 8;
        if ( ret[1] < 1 ) ret[1] = firstHighLevelDay + 5;
        card->setResultTemperatureLowLevelStart( -1 );
        card->setResultTemperatureLowLevelValue( -1 );
        card->setResultTemperatureHighLevelStart( -1 );
        card->setResultTemperatureHighLevelEnd( -1 );
        return ret;
    }

    int firstDay = -1;
    int lastDay  = -1;
    int lowLevel = 0;
    int count = 0;

    // calculate the first day of low level temperatures and low level temperature value
    for ( int i = firstHighLevelDay - 1; i >= 1; i-- ) {
        dayEntry *day = card->getDay(i);
        if (day != NULL && !day->getTemperatureDisturbances() ) {
            int dayTemp = day->getTemperatureValueAfterCorrections();
            if ( dayTemp > 0 ) {
                firstDay = i;
                count++;
                if ( lowLevel < dayTemp )
                    lowLevel = dayTemp;
                if ( count == 6 )
                    break;
            }
        }
    }

    // calculate the first day of low level temperatures and low level temperature value
    count = 0;
    for ( int i = firstHighLevelDay; i <= getDaysCount(); i++ ) {
        dayEntry *day = card->getDay(i);
        if (day != NULL && !day->getTemperatureDisturbances() ) {
            int dayTemp = day->getTemperatureValueAfterCorrections();
            if ( dayTemp > 0 ) {
                lastDay = i;
                count++;
                // the third higher temperature should be >= 0.2C higher than 'lowLevel'
                if ( count == 3 && dayTemp >= lowLevel + 20 )
                    break;
                // in case when the third higher temperature is be < 0.2C then high level temperature level has 4 days
                if ( count == 4 )
                    break;
            }
        }
    }

    int * ret = new int[2];
    ret[0] = firstDay;
    ret[1] = lastDay;

    int prevFirstDay = card->getResultTemperatureLowLevelStart();
    int prevLastDay = card->getResultTemperatureHighLevelEnd();
    if ( prevFirstDay > 0 && prevFirstDay < ret[0] )
        ret[0] = prevFirstDay;
    if ( prevLastDay > ret[1] )
        ret[1] = prevLastDay;

    card->setResultTemperatureLowLevelStart( firstDay );
    card->setResultTemperatureLowLevelValue( lowLevel );
    card->setResultTemperatureHighLevelStart( firstHighLevelDay );
    card->setResultTemperatureHighLevelEnd( lastDay );

    return ret;
}

/**
 * Reset temperature levels result.
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::resetResultTemperaturesLevels( int cardNo )
{
    if (cardNo == -1) cardNo = m_activeCard;
    if ( !checkSettingResultsBasicStaff (cardNo, m_activeDay) ) return NULL;
    cardEntry *card = getCard( cardNo );

    // reset temperature levels
    int * ret = new int[2];
    ret[0] = card->getResultTemperatureLowLevelStart();
    ret[1] = card->getResultTemperatureHighLevelEnd();
    if ( ret[0] < 1 ) ret[0] = m_activeDay;
    if ( ret[1] < 1 ) ret[1] = m_activeDay;
    card->setResultTemperatureLowLevelStart( -1 );
    card->setResultTemperatureLowLevelValue( -1 );
    card->setResultTemperatureHighLevelStart( -1 );
    card->setResultTemperatureHighLevelEnd( -1 );
    return ret;
}

/**
 * Set the day 'dayNo' of the card 'cardNo' as a day of 2nd phase start.
 * If 'dayNo' != 1 || 'cardNo' != -1 then set it for active day of active card.
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultFertilePhaseStart( int cardNo, int dayNo )
{
    if (cardNo == -1) cardNo = m_activeCard;
    if (dayNo == -1) dayNo = m_activeDay;
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) return NULL;

    int * ret = new int[2];
    ret[0] = dayNo;
    ret[1] = dayNo + 5;
    cardEntry *card = getCard( cardNo );

    if ( card->isResultFertilePhaseStart(dayNo) ) {
        // unset and exit
        card->removeResultFertilePhaseStart( dayNo );
        return ret;
    }

    // check if other results are not defined in this day
    if ( card->isResultInfertilePhaseStart(dayNo) )
        card->removeResultInfertilePhaseStart( dayNo );

    if ( card->isResultFertilePhaseStart() ) {
        int answer = askForRemovingOtherResults();
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxYES) {
            // remove other results from the card
            card->clearResultFertilePhaseStart();
            ret[0] = 1;
            ret[1] = card->getDaysCount();
        }
        // set result
    }
    card->addResultFertilePhaseStart(dayNo);
    return ret;
}

/**
 * Set the day 'dayNo' of the card 'cardNo' as a day of 3rd phase start.
 * If 'dayNo' != 1 || 'cardNo' != -1 then set it for active day of active card.
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultInfertilePhaseStart( int cardNo, int dayNo )
{
    if (cardNo == -1) cardNo = m_activeCard;
    if (dayNo == -1) dayNo = m_activeDay;
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) return NULL;

    int * ret = new int[2];
    ret[0] = dayNo;
    ret[1] = dayNo + 5;
    cardEntry *card = getCard( cardNo );

    if ( card->isResultInfertilePhaseStart(dayNo) ) {
        // unset and exit
        card->removeResultInfertilePhaseStart( dayNo );
        return ret;
    }

    // check if other results are not defined in this day
    if ( card->isResultFertilePhaseStart(dayNo) )
        card->removeResultFertilePhaseStart( dayNo );

    if ( card->isResultInfertilePhaseStart() ) {
        int answer = askForRemovingOtherResults();
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxYES) {
            // remove other results from the card
            card->clearResultInfertilePhaseStart();
            ret[0] = 1;
            ret[1] = card->getDaysCount();
        }
        // set result
    }
    card->addResultInfertilePhaseStart(dayNo);
    return ret;
}


/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
int * cycleDataClass::calculateResultsAutomatically( int cardNo )
{
    if (cardNo == -1) cardNo = m_activeCard;
    return NULL;
}

/**
 *
 */
int * cycleDataClass::calculateResultMucus1stDay( int cardNo )
{
    return NULL;
}

/**
 *
 */
int * cycleDataClass::calculateResultMucus1stMoreFertileDay( int cardNo )
{
    return NULL;
}

/**
 *
 */
int * cycleDataClass::calculateResultMucusPeak( int cardNo )
{
    return NULL;
}

/**
 *
 */
int * cycleDataClass::calculateResultCervix1stDay( int cardNo )
{
    return NULL;
}

/**
 *
 */
int * cycleDataClass::calculateResultCervixPeak( int cardNo )
{
    return NULL;
}

/**
 *
 */
int * cycleDataClass::calculateResultTemperaturesLevels( int cardNo )
{
    return NULL;
}

/**
 *
 */
int * cycleDataClass::calculateResultFertilePhaseStart( int cardNo )
{
    return NULL;
}

/**
 *
 */
int * cycleDataClass::calculateResultInfertilePhaseStart( int cardNo )
{
    return NULL;
}
