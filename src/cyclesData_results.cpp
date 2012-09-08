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
 * If the card type is normal or pregnancy: return wxNO to overwrite existing values (there can be only one value in this mode).
 * In case of other type of card, check the config parameter (isAskUserToKeepResultsAlreadySetForOtherDays)
 * Ask user what should I do. If user answer:
 * Yes: do not remove result from other days on the card and set it also for this day
 * No: remove result from other days on the card and set it only for this day
 * Cancel: do nothing, let teh user check the situation
 */
int cycleDataClass::askToKeepResultsAlreadySetForOtherDays(int cycleType)
{
    if (cycleType == CYCLE_TYPE_NORMAL || cycleType == CYCLE_TYPE_PREGNANCY) {
        return wxNO;
    }

    //if (autoMode || !isAskUserToKeepResultsAlreadySetForOtherDays()) {
    //    return wxYES;
    //}

    wxString message = _( "The result you want to set is already defined on the card.\nDo you want me to keep this result and set the same for selected day?\nChoose:\n- 'Yes' to set it the result also for this day without removing result from other days.\n- 'No' to remove this result from other days on the card and set it only for this day.\n- 'Cancel' to exit without touching anything to let you check the situation");
    return wxMessageBox(message, _("Keep already defined results?"), wxYES_NO | wxCANCEL);
}

/**
 * Set the day 'dayNo' of the card 'cardNo' as a first day when any kind of mucus appears.
 * If 'dayNo' == -1, then use active day.
 * If 'cardNo' == -1 then use active card.
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultMucus1stDay( int cardNo, int dayNo )
{
    if (cardNo == -1) {
        cardNo = m_activeCard;
    }
    if (dayNo == -1) {
        dayNo = m_activeDay;
    }
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) {
        return NULL;
    }

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
    if ( card->isResultMucus1stMoreFertileDay(dayNo) ) {
        card->removeResultMucus1stMoreFertileDay( dayNo );
    }

    if ( card->isResultMucusPeak(dayNo) ) {
        card->removeResultMucusPeak( dayNo );
        ret[1] = dayNo + 3;
    }

    if ( card->isResultMucus1stDaySet() ) {
        int answer = askToKeepResultsAlreadySetForOtherDays(card->getCycleType());
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxNO) {
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
 * If 'dayNo' == -1, then use active day.
 * If 'cardNo' == -1 then use active card.
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultMucus1stMoreFertileDay( int cardNo, int dayNo )
{
    if (cardNo == -1) {
        cardNo = m_activeCard;
    }
    if (dayNo == -1) {
        dayNo = m_activeDay;
    }
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) {
        return NULL;
    }

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
    if ( card->isResultMucus1stDay(dayNo) ) {
        card->removeResultMucus1stDay( dayNo );
    }

    if ( card->isResultMucusPeak(dayNo) ) {
        card->removeResultMucusPeak( dayNo );
        ret[1] = dayNo + 3;
    }

    if ( card->isResultMucus1stMoreFertileDaySet() ) {
        int answer = askToKeepResultsAlreadySetForOtherDays(card->getCycleType());
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxNO) {
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
 * If 'dayNo' == -1, then use active day.
 * If 'cardNo' == -1 then use active card.
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultMucusPeak( int cardNo, int dayNo )
{
    if (cardNo == -1) {
        cardNo = m_activeCard;
    }
    if (dayNo == -1) {
        dayNo = m_activeDay;
    }
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) {
        return NULL;
    }

    int * ret = new int[2];
    ret[0] = dayNo;
    ret[1] = dayNo + 4;
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
    if ( card->isResultMucus1stMoreFertileDay(dayNo) ) {
        card->removeResultMucus1stMoreFertileDay( dayNo );
    }


    if ( card->isResultMucusPeakSet() ) {
        int answer = askToKeepResultsAlreadySetForOtherDays(card->getCycleType());
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxNO) {
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
 * If 'dayNo' == -1, then use active day.
 * If 'cardNo' == -1 then use active card.
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultCervix1stDay( int cardNo, int dayNo )
{
    if (cardNo == -1) {
        cardNo = m_activeCard;
    }
    if (dayNo == -1) {
        dayNo = m_activeDay;
    }
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) {
        return NULL;
    }

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

    if ( card->isResultCervix1stDaySet() ) {
        int answer = askToKeepResultsAlreadySetForOtherDays(card->getCycleType());
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxNO) {
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
 * If 'dayNo' == -1, then use active day.
 * If 'cardNo' == -1 then use active card.
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultCervixPeak( int cardNo, int dayNo )
{
    if (cardNo == -1) {
        cardNo = m_activeCard;
    }
    if (dayNo == -1) {
        dayNo = m_activeDay;
    }
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) {
        return NULL;
    }

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
    if ( card->isResultCervix1stDay(dayNo) ) {
        card->removeResultCervix1stDay( dayNo );
    }

    if ( card->isResultCervixPeakSet() ) {
        int answer = askToKeepResultsAlreadySetForOtherDays(card->getCycleType());
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxNO) {
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
 * Set the day 'firstHighLevelDay' of the card 'cardNo' as a first day high level temperature.
 * If 'firstHighLevelDay' == -1, then use active day.
 * If 'cardNo' == -1 then use active card.
 * Calculate also:
 * - first day of low level temperature
 * - last day of high level temperature
 * - low level temperature value
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultTemperatureLevels( configClass *config, int cardNo, int firstHighLevelDay, bool resetIfExists )
{
    //m_errorMessages = wxEmptyString;

    if (cardNo == -1) {
        cardNo = m_activeCard;
    }
    if (firstHighLevelDay == -1) {
        firstHighLevelDay = m_activeDay;
    }
    if ( !checkSettingResultsBasicStaff (cardNo, firstHighLevelDay) ) {
        return NULL;
    }

    cardEntry *card = getCard( cardNo );

    // case 1/ unset existing result and exit
    if ( card->getResultTemperatureHighLevelStart() == firstHighLevelDay && resetIfExists ) {
        int * ret = new int[2];
        ret[0] = card->getResultTemperatureLowLevelStart();
        ret[1] = card->getResultTemperatureHighLevelStart() + 20;
        if ( ret[0] < 1 ) {
            ret[0] = firstHighLevelDay - 8;
        }
        if ( ret[1] < 1 ) {
            ret[1] = firstHighLevelDay + 20;
        }
        card->setResultsTemperature( -1, -1, -1, -1 );
        return ret;
    }

    // case 2/ set result
    int * ret = new int[2];
    ret[0] = card->getResultTemperatureLowLevelStart() - 3;
    ret[1] = card->getResultTemperatureHighLevelStart() + 20;

    int * result = calculateTemperatureLevels( card, cardNo, firstHighLevelDay, config, false );

    if (result != NULL) {
        card->setResultsTemperature( result[0], result[1], result[2], result[3] );

        if ( result[0] > 0 && result[0]-3 < ret[0] ) {
            ret[0] = result[0];
        }
        if ( result[2]+20 > ret[1] ) {
            ret[1] = result[2]+20;
        }
    }

    return ret;

    /*
    // previous simple version
    for ( int i = firstHighLevelDay - 1; i >= 1; i-- ) {
        int dayTemp = getDayTemp(card, i);
        if ( dayTemp > 0 ) {
            firstDay = i;
            count++;
            if ( lowLevel < dayTemp ) {
                lowLevel = dayTemp;
            }
            if ( count == 6 ) {
                break;
            }
        }
    }

    for ( int i = firstHighLevelDay; i <= getDaysCount(); i++ ) {
        int dayTemp = getDayTemp(card, i);
        if ( dayTemp > 0 ) {
            lastHighLevelDay = i;
            count++;
            // the third higher temperature should be >= 0.2C higher than 'lowLevel'
            if ( count == 3 && dayTemp >= lowLevel + 20 ) {
                break;
            }
            // in case when the third higher temperature is be < 0.2C then high level temperature level has 4 days
            if ( count == 4 ) {
                break;
            }
        }
    }

    */
}

/**
 * Reset temperature levels result.
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::resetResultTemperatureLevels( int cardNo )
{
    if (cardNo == -1) {
        cardNo = m_activeCard;
    }
    if ( !checkSettingResultsBasicStaff (cardNo, m_activeDay) ) {
        return NULL;
    }
    cardEntry *card = getCard( cardNo );

    // reset temperature levels
    int * ret = new int[2];
    ret[0] = card->getResultTemperatureLowLevelStart();
    ret[1] = card->getResultTemperatureHighLevelStart() + 20;
    if ( ret[0] < 1 ) {
        ret[0] = m_activeDay;
    }
    if ( ret[1] < 1 ) {
        ret[1] = m_activeDay;
    }
    card->clearResultsTemperature();
    return ret;
}

/**
 * Set the day 'dayNo' of the card 'cardNo' as a day of 2nd phase start.
 * If 'dayNo' == -1, then use active day.
 * If 'cardNo' == -1 then use active card.
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultFertilePhaseStart( int cardNo, int dayNo )
{
    if (cardNo == -1) {
        cardNo = m_activeCard;
    }
    if (dayNo == -1) {
        dayNo = m_activeDay;
    }
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) {
        return NULL;
    }

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
    if ( card->isResultInfertilePhaseStart(dayNo) ) {
        card->removeResultInfertilePhaseStart( dayNo );
    }

    if ( card->isResultFertilePhaseStartSet() ) {
        int answer = askToKeepResultsAlreadySetForOtherDays(card->getCycleType());
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxNO) {
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
 * If 'dayNo' == -1, then use active day.
 * If 'cardNo' == -1 then use active card.
 * Return the array int[2] with the range of days requiring refreshing.
 * In case of failure return NULL.
 */
int * cycleDataClass::setResultInfertilePhaseStart( int cardNo, int dayNo )
{
    if (cardNo == -1) {
        cardNo = m_activeCard;
    }
    if (dayNo == -1) {
        dayNo = m_activeDay;
    }
    if ( !checkSettingResultsBasicStaff (cardNo, dayNo) ) {
        return NULL;
    }

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
    if ( card->isResultFertilePhaseStart(dayNo) ) {
        card->removeResultFertilePhaseStart( dayNo );
    }

    if ( card->isResultInfertilePhaseStartSet() ) {
        int answer = askToKeepResultsAlreadySetForOtherDays(card->getCycleType());
        if (answer == wxCANCEL) {
            // do nothing
            return ret;
        } else if (answer == wxNO) {
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
***** CALCULATING RESULTS AUTOMATICALLY ****************************************
*******************************************************************************/

/**
 * Return a message with info what has been done
 * or empty string if nothing has not been done.
 * Store in 'm_errorMessages' all errors.
 */
bool cycleDataClass::calculateResultsAutomatically( int cardNo, configClass *config )
{
    if (cardNo == -1) {
        cardNo = m_activeCard;
    }

    cardEntry *card = getCard( cardNo );

    if (!removePreviouslySetResults(card)) {
        return wxEmptyString;
    }

    bool retMessage = true;
    m_errorMessages = wxEmptyString;

    if (!calculateResultCervixPeak(card, cardNo)) retMessage = false;
    if (!calculateResultCervix1stDay(card, cardNo)) retMessage = false;

    if (card->getCycleType() == CYCLE_TYPE_NORMAL || card->getCycleType() == CYCLE_TYPE_PREGNANCY) {
        if (!calculateResultMucusPeak(card, cardNo)) retMessage = false;
        if (!calculateResultMucus1stMoreFertileDay(card, cardNo)) retMessage = false;
        if (!calculateResultMucus1stDay(card, cardNo)) retMessage = false;
    } else {
        // calculated by 'calculateResultPhasesInAfterPregnancyCycle()'
    }

    if (!calculateResultTemperatureLevels(card, cardNo, config)) retMessage = false;

    if (card->getCycleType() == CYCLE_TYPE_NORMAL || card->getCycleType() == CYCLE_TYPE_PREGNANCY) {
        if (!calculateResultInfertilePhaseStart(card, cardNo)) retMessage = false;
        if (!calculateResultFertilePhaseStart(card, cardNo, config)) retMessage = false;
    } else {
        if (!calculateResultPhasesInAfterPregnancyCycle(card, cardNo, config)) retMessage = false;
    }

    return retMessage;
}

/**
 * Before we can calculate results automatically, we have to remove previously set results.
 * If there are no results set on the card, then return true.
 * If there are any results set, ask user if she wants to contiue and return true or false.
 */
bool cycleDataClass::removePreviouslySetResults(cardEntry *card)
{
    bool resultIsSet = false;

    if (card->isResultMucus1stDaySet()) resultIsSet = true;
    if (card->isResultMucus1stMoreFertileDaySet()) resultIsSet = true;
    if (card->isResultMucusPeakSet()) resultIsSet = true;
    if (card->isResultCervix1stDaySet()) resultIsSet = true;
    if (card->isResultCervixPeakSet()) resultIsSet = true;
    if (card->isResultTemperatureLevelSet()) resultIsSet = true;
    if (card->isResultFertilePhaseStartSet()) resultIsSet = true;
    if (card->isResultInfertilePhaseStartSet()) resultIsSet = true;


    if (!resultIsSet) {
        return true;
    }

    wxString message = _( "Before the card can be analyzed automatically, previously defined results must be removed.\nDo you want me to continue?\nChoose:\n- 'Yes' to remove previously defined results and analyze the card automatically.\n- 'No' to cancel the operation without changing anything");
    bool removeOldResults = (wxMessageBox(message, _("What should I do?"), wxYES_NO) == wxYES);

    if (removeOldResults) {
        card->removeAllResults();
        return true;
    } else  {
        return false;
    }
}

/**
 * Return true if OK, false otherwise (+ error in 'm_errorMessages').
 */
bool cycleDataClass::calculateResultsAutomaticallyOnChange( int cardNo, configClass *config )
{
    if (cardNo == -1) {
        cardNo = m_activeCard;
    }

    cardEntry *card = getCard( cardNo );

    card->removeAllResults();

    bool retMessage = true;
    m_errorMessages = wxEmptyString;

    if (!calculateResultCervixPeak(card, cardNo)) retMessage = false;
    if (!calculateResultCervix1stDay(card, cardNo)) retMessage = false;

    if (card->getCycleType() == CYCLE_TYPE_NORMAL || card->getCycleType() == CYCLE_TYPE_PREGNANCY) {
        if (!calculateResultMucusPeak(card, cardNo)) retMessage = false;
        if (!calculateResultMucus1stMoreFertileDay(card, cardNo)) retMessage = false;
        if (!calculateResultMucus1stDay(card, cardNo)) retMessage = false;
    } else {
        // calculated by 'calculateResultPhasesInAfterPregnancyCycle()'
    }

    if (!calculateResultTemperatureLevels(card, cardNo, config)) retMessage = false;

    if (card->getCycleType() == CYCLE_TYPE_NORMAL || card->getCycleType() == CYCLE_TYPE_PREGNANCY) {
        if (!calculateResultInfertilePhaseStart(card, cardNo)) retMessage = false;
        if (!calculateResultFertilePhaseStart(card, cardNo, config)) retMessage = false;
    } else {
        if (!calculateResultPhasesInAfterPregnancyCycle(card, cardNo, config)) retMessage = false;
    }

    return retMessage;
}

/******************************************************************************/

/**
 *
 */
bool cycleDataClass::calculateResultMucus1stDay( cardEntry *card, int cardNo )
{
    for ( int dayNo = 2; dayNo < card->getDaysCount(); dayNo++ ) {
        if ( (card->isResultMucusPeak(dayNo) || card->isResultMucus1stMoreFertileDay(dayNo))
                && (card->getCycleType() == CYCLE_TYPE_NORMAL || card->getCycleType() == CYCLE_TYPE_PREGNANCY)) {
            break;
        }

        if ( card->getDay(dayNo)->isMucus() && !card->isResultMucusPeak(dayNo) && !card->isResultMucus1stMoreFertileDay(dayNo) && !card->getDay(dayNo-1)->isMucus() ) {
            card->addResultMucus1stDay(dayNo, true);
            //retMessage << wxString::Format( _( "\n- day %i: 1st day of mucus apperance" ), dayNo );
            if (card->getCycleType() == CYCLE_TYPE_NORMAL || card->getCycleType() == CYCLE_TYPE_PREGNANCY) {
                break;
            }
        }
    }
    return true;
}

/**
 *
 */
bool cycleDataClass::calculateResultMucus1stMoreFertileDay( cardEntry *card, int cardNo )
{
    for ( int dayNo = 2; dayNo < card->getDaysCount(); dayNo++ ) {
        if ( card->isResultMucusPeak(dayNo)
                && (card->getCycleType() == CYCLE_TYPE_NORMAL || card->getCycleType() == CYCLE_TYPE_PREGNANCY)) {
            break;
        }

        if (card->getDay(dayNo)->isMucusMoreFertile() && !card->isResultMucusPeak(dayNo) && !card->getDay(dayNo-1)->isMucusMoreFertile()) {
            card->addResultMucus1stMoreFertileDay(dayNo, true);
            //retMessage << wxString::Format( _( "\n- day %i: 1st day of more fertile mucus apperance" ), dayNo );
            if (card->getCycleType() == CYCLE_TYPE_NORMAL || card->getCycleType() == CYCLE_TYPE_PREGNANCY) {
                break;
            }
        }
    }
    return true;
}

/**
 *
 */
bool cycleDataClass::calculateResultMucusPeak( cardEntry *card, int cardNo )
{
    if (card->getCycleType() == CYCLE_TYPE_NORMAL || card->getCycleType() == CYCLE_TYPE_PREGNANCY) {
        int mucusPeakDate = 0;

        for ( int dayNo = 3; dayNo <= card->getDaysCount(); dayNo++ ) {
            if ( card->getDay(dayNo)->isMucusMoreFertile() && !card->getDay(dayNo-1)->isMucusMoreFertile() ) {
                if ( mucusPeakDate != 0 && dayNo - mucusPeakDate < 3 ) {
                    mucusPeakDate = 0;
                }
            } else if ( !card->getDay(dayNo)->isMucusMoreFertile() && card->getDay(dayNo-1)->isMucusMoreFertile() ) {
                if ( mucusPeakDate == 0 || dayNo - mucusPeakDate < 6 ) {
                    mucusPeakDate = dayNo -1;
                }
            }
        }
        if (mucusPeakDate > 0) {
            card->addResultMucusPeak(mucusPeakDate, true);
            //retMessage << wxString::Format( _( "\n- day %i: mucus peak day" ), mucusPeakDate );
        }
    } else {
        for ( int dayNo = 2; dayNo < card->getDaysCount(); dayNo++ ) {
            if ( !card->getDay(dayNo)->isMucusMoreFertile() && card->getDay(dayNo-1)->isMucusMoreFertile() ) {
                card->addResultMucusPeak(dayNo-1, true);
                //retMessage << wxString::Format( _( "\n- day %i: mucus peak day" ), dayNo-1 );
            }
        }
    }
    return true;
}

/**
 *
 */
bool cycleDataClass::calculateResultCervix1stDay( cardEntry *card, int cardNo )
{
    for ( int dayNo = 2; dayNo < card->getDaysCount(); dayNo++ ) {
        if ( card->isResultCervixPeak(dayNo)
                && (card->getCycleType() == CYCLE_TYPE_NORMAL || card->getCycleType() == CYCLE_TYPE_PREGNANCY)) {
            break;
        }

        if (card->getDay(dayNo)->isCervixChange() && !card->isResultCervixPeak(dayNo) && !card->getDay(dayNo-1)->isCervixChange()) {
            card->addResultCervix1stDay(dayNo, true);
            //retMessage << wxString::Format( _( "\n- day %i: 1st day of cervix changes" ), dayNo );
            if (card->getCycleType() == CYCLE_TYPE_NORMAL || card->getCycleType() == CYCLE_TYPE_PREGNANCY) {
                break;
            }
        }
    }
    return true;
}

/**
 *
 */
bool cycleDataClass::calculateResultCervixPeak( cardEntry *card, int cardNo )
{
    dayEntry * cDay;
    dayEntry * pDay;

    /*
    if (card->getCycleType() == CYCLE_TYPE_NORMAL || card->getCycleType() == CYCLE_TYPE_PREGNANCY) {
    */
    int cervixPeakDate = 0;
    int highestPosition = CERVIX_LOW;
    int lastDayWithHighestPosition = 0;
    int biggestDilation = CERVIX_CLOSED;
    int lastDayWithBiggestDilation = 0;
    int mostSotfness = CERVIX_FIRM;
    int lastDayWithMostSotfness = 0;

    for ( int dayNo = 2; dayNo < card->getDaysCount(); dayNo++ ) {
        cDay = card->getDay(dayNo);
        pDay = card->getDay(dayNo-1);

        if ( cDay->isCervixChange() ) {
            if (cDay->getCervixPosition() > CERVIX_LOW) {
                if (cDay->getCervixPosition() > highestPosition) {
                    highestPosition = cDay->getCervixPosition();
                    lastDayWithHighestPosition = dayNo;
                } else if (cDay->getCervixPosition() == highestPosition) {
                    if (cDay->getCervixDilation() > biggestDilation) {
                        highestPosition = cDay->getCervixPosition();
                        lastDayWithHighestPosition = dayNo;
                    } else if (cDay->getCervixDilation() == biggestDilation) {
                        if (cDay->getCervixHardness() > CERVIX_FIRM) {
                            if (cDay->getCervixHardness() >= mostSotfness) {
                                highestPosition = cDay->getCervixPosition();
                                lastDayWithHighestPosition = dayNo;
                            }
                        } else {
                            highestPosition = cDay->getCervixPosition();
                            lastDayWithHighestPosition = dayNo;
                        }
                    }
                }
                if (cDay->getCervixDilation() > CERVIX_CLOSED && cDay->getCervixDilation() >= biggestDilation) {
                    biggestDilation = cDay->getCervixDilation();
                    lastDayWithBiggestDilation = dayNo;
                }
                if (cDay->getCervixHardness() > CERVIX_FIRM && cDay->getCervixHardness() >= mostSotfness) {
                    mostSotfness = cDay->getCervixHardness();
                    lastDayWithMostSotfness = dayNo;
                }
            }
        }
    }

    if (highestPosition > CERVIX_LOW && lastDayWithHighestPosition > 0) {
        cervixPeakDate = lastDayWithHighestPosition;
    } else if (biggestDilation > CERVIX_CLOSED && lastDayWithBiggestDilation > 0) {
        cervixPeakDate = lastDayWithBiggestDilation;
    } else if (mostSotfness > CERVIX_FIRM && lastDayWithMostSotfness > 0) {
        cervixPeakDate = lastDayWithMostSotfness;
    }

    if (cervixPeakDate > 0) {
        card->addResultCervixPeak(cervixPeakDate, true);
        //retMessage << wxString::Format( _( "\n- day %i: cervix peak day" ), cervixPeakDate );
    }

    /*
    } else {
        int prevDayWithCervixChange = 0;

        for ( int dayNo = 2; dayNo < card->getDaysCount(); dayNo++ ) {
            if ( card->getDay(dayNo)->isCervixChange() ) {
                pDay = cDay;
                cDay = card->getDay(dayNo);
                prevDayWithCervixChange = dayNo-1;
            } else if (dayNo-prevDayWithCervixChange > 2) {
                // we accept the situation when cervix has not been monitored for max 2 days.
                cDay = card->getDay(dayNo);
            } else {
                continue;
            }

            if ( pDay->isCervixChange() &&
                    (cDay->getCervixPosition() < pDay->getCervixPosition()
                     || cDay->getCervixDilation() < pDay->getCervixDilation()
                     || cDay->getCervixHardness() < pDay->getCervixHardness())
               ) {
                setResultCervixPeak(cardNo, dayNo-1, true);
                retMessage << wxString::Format( _( "\n- day %i: cervix peak day" ), dayNo-1 );
            }
        }
    }
    */
    return true;
}

/**
_( "First day of high temperature level" )
 *
 */
bool cycleDataClass::calculateResultTemperatureLevels( cardEntry *card, int cardNo, configClass *config)
{
    /*
    if ( !are7measuredTemperatures(card) ) {
        return false;
    }
    */

    for ( int firstHighLevelDay = 7; firstHighLevelDay <= card->getDaysCount(); firstHighLevelDay++ ) {
        int * result = calculateTemperatureLevels( card, cardNo, firstHighLevelDay, config, true );

        if (result != NULL) {
            card->setResultsTemperature( result[0], result[1], result[2], result[3] );
            return true;
        }
    }

    return false;
}

/**
 *
 */
int * cycleDataClass::calculateTemperatureLevels( cardEntry *card, int cardNo, int firstHighLevelDay, configClass *config, bool autoMode  )
{
    if (autoMode && getDayTemp(card, firstHighLevelDay) <= 0 ) {
        // temperary log
        //retMessage << wxString::Format( _("- Temperature for firstHighLevelDay %i is not measured - exit\n"), firstHighLevelDay);
        return NULL;
    }

    int firstLowLevelDay = 0;
    int lastHighLevelDay  = 0;
    int lowLevelTemp = 0;
    int lowLevelCount = 0;
    int noOfNotMesuredLowLevelDaysCatched = 0;
    int highLevelCount = 0;
    int highLevelAboveLineCount = 0; // used for three cycles after stopping using birth controls pills
    int noOfNotMesuredHighLevelDaysCatched = 0;
    wxString retMessage = wxEmptyString;
    bool wasMucusPeakBeforeFirstHighLevelDay = wasMucusPeakBeforeDay(card, firstHighLevelDay);

    // temperary log
    //retMessage << wxString::Format( _("- Checking if day %i is firstHighLevelDay\n"), firstHighLevelDay);


    // 1/ calculate the first day of low level temperatures and low level temperature value
    for ( int dayNo = firstHighLevelDay-1; dayNo >= 1; dayNo-- ) {
        int dayTemp = getDayTemp(card, dayNo);
        if ( dayTemp > 0 ) {
            // temperature measured correctly
            lowLevelCount++;
            firstLowLevelDay = dayNo;
            if ( lowLevelTemp < dayTemp ) {
                lowLevelTemp = dayTemp;
            }
        } else {
            // temperature not measured or marked as disrupted
            noOfNotMesuredLowLevelDaysCatched++;
            if ( noOfNotMesuredLowLevelDaysCatched <= config->maxIncludedNotMesuredLowLevelDays
                    && config->includeNotMesuredDaysIfAfterMucusPeak
                    && wasMucusPeakBeforeFirstHighLevelDay
               ) {
                lowLevelCount++;
                firstLowLevelDay = dayNo;
                // temperary log
                //retMessage << wxString::Format( _("- Day %i without measured temperature added to the low level temperature days\n"), dayNo);
            } else if (noOfNotMesuredLowLevelDaysCatched > config->maxAllowedNotMesuredLowLevelDays) {
                // limit of not mesured low temperatures catched and count < 6:
                // if autoMode==true then return NULL
                // if autoMode==false and there is at least one day with real temperature then just continue (allow user to set whatever she wants ;)
                if (autoMode) {
                    // temperary log
                    //retMessage << wxString::Format( _("- Catched %i possible low level days without measured temperature - exit\n"), noOfNotMesuredLowLevelDaysCatched);
                    return NULL;
                } else if (lowLevelTemp == 0) {
                    // friendly warning ;)
                    retMessage << wxString::Format( _("- Cannot calculate low level value of temperatures - days %i-%i doesn't have measured temperature - exit\n"), dayNo, dayNo+noOfNotMesuredLowLevelDaysCatched);
                    return NULL;
                } else {
                    continue;
                }
            }
        }
        if ( lowLevelCount == 6 ) {
            break;
        }
    }
    // temperary log
    //retMessage << wxString::Format( _("- Found %i low level temps (%i C); days %i - %i\n"), lowLevelCount, lowLevelTemp, firstLowLevelDay, firstLowLevelDay+lowLevelCount);


    // 2/ calculate the first day of high level temperatures and high level temperature value
    for ( int dayNo = firstHighLevelDay; dayNo <= card->getDaysCount(); dayNo++ ) {
        int dayTemp = getDayTemp(card, dayNo);
        if ( dayTemp > 0 ) {
            // temperature measured correctly
            if (autoMode && dayTemp <= lowLevelTemp ) {
                // it's not a first day of high level temperatures - go to the next day
                // temperary log
                //retMessage << wxString::Format( _("- Temperature for day %i is not higher that low level temp - exit\n"), dayNo);
                return NULL;
            }
            highLevelCount++;
            if ( dayTemp >= lowLevelTemp + 20 ) {
                highLevelAboveLineCount++;
            }

            lastHighLevelDay = dayNo;
        } else {
            // temperature not measured or marked as disrupted
            if (dayNo == firstHighLevelDay && !autoMode) {
                // friendly warning ;)
                retMessage << wxString::Format( _("- Day %i pointed by you as a first day of high level temperature doesn't have measured temperature. I hope that you know what are you doing ;)\n"), dayNo);
                lastHighLevelDay = dayNo;
            }

            noOfNotMesuredHighLevelDaysCatched++;
            if (noOfNotMesuredHighLevelDaysCatched <= config->maxIncludedNotMesuredHighLevelDays
                    && config->includeNotMesuredDaysIfAfterMucusPeak
                    && wasMucusPeakBeforeFirstHighLevelDay
               ) {
                highLevelCount++;
                highLevelAboveLineCount++;
                lastHighLevelDay = dayNo;
                // temperary log
                //retMessage << wxString::Format( _("- Day %i without measured temperature added to the high level temperature days\n"), dayNo);
            } else if (noOfNotMesuredHighLevelDaysCatched > config->maxAllowedNotMesuredHighLevelDays) {
                // limit of not mesured high temperatures catched and count < 3|4:
                // continue:
                // - in auto mode we already know that there is at least one temperature measured
                // - in manual mode allow user to set whatever she wants, but report the problem ;)
                break;
            }
        }

        if ( isCardFromLast3AfterStoppedPills(cardNo) ) {
            if ( highLevelCount >= 5 && highLevelAboveLineCount >= 3 ) {
                // cycles after stopping using birth controls pills
                break;
            }
        } else {
            if ( highLevelCount == 3 && dayTemp >= lowLevelTemp + 20 ) {
                // the third higher temperature should be >= 0.2C higher than 'lowLevelTemp'
                break;
            }
            if ( highLevelCount == 4 ) {
                // in case when the third higher temperature is be < 0.2C then high level temperature level has 4 days
                break;
            }
        }

    }
    // temperary log
    //retMessage << wxString::Format( _("- Found %i high level temps; days %i - %i\n"), highLevelCount, firstHighLevelDay, lastHighLevelDay);


    m_errorMessages << retMessage;

    int * ret = new int[4];
    ret[0] = firstLowLevelDay;
    ret[1] = lowLevelTemp;
    ret[2] = firstHighLevelDay;
    ret[3] = lastHighLevelDay;

    return ret;
}

/**
 *
 */
int cycleDataClass::getDayTemp( cardEntry *card, int dayNo )
{
    dayEntry *day = card->getDay(dayNo);
    if (day != NULL && !day->getTemperatureDisturbances() ) {
        return day->getTemperatureValueAfterCorrections();
    } else {
        return -1;
    }
}

/**
 *
 */
bool cycleDataClass::are7measuredTemperatures( cardEntry *card )
{
    int measuredTemperaturesCount = 0;
    for ( int i = 1; i <= card->getDaysCount(); i++ ) {
        if (getDayTemp(card, i) > 0 ) {
            measuredTemperaturesCount++;
        }
    }
    return ( measuredTemperaturesCount >=7 );
}

bool cycleDataClass::wasMucusPeakBeforeDay(cardEntry *card, int dayNo)
{
    for ( int d = dayNo-1; d >= dayNo-4; d-- )
        if (card->isResultMucusPeak(d))
            return true;

    return false;
}

/******************************************************************************/

/**
 * only for CYCLE_TYPE_NORMAL & CYCLE_TYPE_PREGNANCY
 */
bool cycleDataClass::calculateResultFertilePhaseStart( cardEntry *card, int cardNo, configClass *config )
{
    int * results = new int[6];
    for (int i=0; i<6; i++)
        results[i] = -1;

    if (cardNo == 1) {
        m_errorMessages << _("\n- On first card we don't calculate beginning of fertile phase. Fertile phase starts at first day of the cycle.");
    } else if (cardNo < 4) {
        int histCyclesCount = getNumberOfHistoricalCyclesUsedToCalculateShortestCycle(cardNo, config);
        if (histCyclesCount < 6) {
            m_errorMessages << wxString::Format( _("\n- There are only %i cards recorded and no information about the length of historical cycles, so beginning of fertile phase cannot be calculated.\nPlease add this information in the 'edit card' dialog."), histCyclesCount);
        } else {
            results[RULE_2120] = getFirstDayOfFertilePhaseStartAccordingTo2120DaysRule(cardNo, config);
            results[RULE_CLINICAL] = getFirstDayOfFertilePhaseStartAccordingToClinicalRule(cardNo, config);
        }
    } else {
        results[RULE_2120] = getFirstDayOfFertilePhaseStartAccordingTo2120DaysRule(cardNo, config);
        results[RULE_CLINICAL] = getFirstDayOfFertilePhaseStartAccordingToClinicalRule(cardNo, config);
        results[RULE_DOERING] = getFirstDayOfFertilePhaseStartAccordingToDoeringRule(card, cardNo, config);
        results[RULE_CERVICAL_MUCUS_BASED] = getFirstDayOfFertilePhaseStartAccordingToCervicalMucusBasedRule(card, cardNo, config);
        results[RULE_CERVICAL_POSITION_BASED] = getFirstDayOfFertilePhaseStartAccordingToCervicalPositionBasedRule(card, cardNo);
    }

    int resultSet = results[config->autoanalyzeCardPreferResult1];
    if (resultSet < 1) resultSet = results[config->autoanalyzeCardPreferResult2];
    if (resultSet < 1) resultSet = results[config->autoanalyzeCardPreferResult3];
    if (resultSet < 1) resultSet = results[config->autoanalyzeCardPreferResult4];
    if (resultSet < 1) resultSet = results[config->autoanalyzeCardPreferResult5];

    m_errorMessages << _("\nCalculated beginning of fertile phase:");
    if (results[RULE_2120] > 0)
        m_errorMessages << wxString::Format( _("\n   - day %i (according to %s)"), results[RULE_2120], RULE_2120_string);
    if (results[RULE_CLINICAL] > 0)
        m_errorMessages << wxString::Format( _("\n   - day %i (according to %s)"), results[RULE_CLINICAL], RULE_CLINICAL_string);
    if (results[RULE_DOERING] > 0)
        m_errorMessages << wxString::Format( _("\n   - day %i (according to %s)"), results[RULE_DOERING], RULE_DOERING_string);
    if (results[RULE_CERVICAL_MUCUS_BASED] > 0)
        m_errorMessages << wxString::Format( _("\n   - day %i (according to %s)"), results[RULE_CERVICAL_MUCUS_BASED], RULE_CERVICAL_MUCUS_BASED_string);
    if (results[RULE_CERVICAL_POSITION_BASED] > 0)
        m_errorMessages << wxString::Format( _("\n   - day %i (according to %s)"), results[RULE_CERVICAL_POSITION_BASED], RULE_CERVICAL_POSITION_BASED_string);

    if (resultSet > 0) {
        m_errorMessages << wxString::Format( _("\n- choosing day %i as a result (according to settings)"), resultSet);
        card->addResultFertilePhaseStart( resultSet, true );
        return true;
    } else {
        return false;
    }
}

/**
 * Calculate the first day of fertile phase according to 21/20 days rule.
 * Only for CYCLE_TYPE_NORMAL & CYCLE_TYPE_PREGNANCY
 */
int cycleDataClass::getFirstDayOfFertilePhaseStartAccordingTo2120DaysRule( int cardNo, configClass *config )
{
    return getNumberOfDaysOfShortestCycle(cardNo, config) - (getNumberOfHistoricalCyclesUsedToCalculateShortestCycle(cardNo, config) < 12 ? 21 : 20) + 1;
    // + 1 because the 21/20 rule calculate the last day of infertile phase, when this function returns the first day of fertile phase.
}

/**
 * Calculate the first day of fertile phase according to clinical rule (4/5/6 day rule).
 * Only for CYCLE_TYPE_NORMAL & CYCLE_TYPE_PREGNANCY
 */
int cycleDataClass::getFirstDayOfFertilePhaseStartAccordingToClinicalRule( int cardNo, configClass *config )
{
    int numberOfDaysOfShortestCycle = getNumberOfDaysOfShortestCycle(cardNo, config);
    if (numberOfDaysOfShortestCycle < 23) {
        return 4;
    } else if (numberOfDaysOfShortestCycle < 26) {
        return 6;
    } else {
        return 7;
    }
}

/**
 * Calculate the first day of fertile phase according to Döring rule.
 * Only for CYCLE_TYPE_NORMAL & CYCLE_TYPE_PREGNANCY
 */
/*
Ostatni dzień fazy niepłodności przedowulacyjnej to najwcześniejszy dzień wzrostu temperatury (z co najmniej ostatnich sześciu cykli) minus 7, po warunkiem, że:
 Jeśli w poprzednich cyklach bardziej płodny śluz występował przez co najmniej pięć dni (licząc od momentu pojawienia się do dnia szczytu włącznie), to w dniu,
    w którym pojawia się śluz bardziej płodnego typu, rozpoczyna się faza płodna, niezależnie od granicy wyznaczonej przez regułę Döringa
 W innym przypadku w dniu, w którym pojawia się jakikolwiek śluz, rozpoczyna się faza płodna, niezależnie od granicy wyznaczonej przez regułę Döringa
*/
int cycleDataClass::getFirstDayOfFertilePhaseStartAccordingToDoeringRule( cardEntry *card, int cardNo, configClass *config )
{
    int fertilePhaseStartDay = getEarliestFirstDayOfHighLevelTemperature(cardNo, config) - 6;
    if (fertilePhaseStartDay < 1)
        return -1;

    if ( wasMoreFertileMucusFor5DaysInPreviousCycles(cardNo, config) ) {
        // check if more fertile mucus has not been observed in previous days.
        for ( int d = 1; d < fertilePhaseStartDay; d++ )
            if (card->getDay(d)->isMucusMoreFertile())
                return d;
    } else {
        // check if any type of mucus has not been observed in previous days.
        for ( int d = 1; d < fertilePhaseStartDay; d++ )
            if (card->getDay(d)->isMucus())
                return d;
    }

    return fertilePhaseStartDay;
}

/**
 * Calculate the first day of fertile phase according cervical mucus based (last dry day) rule.
 * Only for CYCLE_TYPE_NORMAL & CYCLE_TYPE_PREGNANCY
 */
/*
W poprzednich cyklach śluz występował przez co najmniej pięć dni (licząc od momentu pojawienia się do dnia szczytu włącznie)

    Faza niepłodności przedowulacyjnej trwa od początku cyklu do końca dni suchych, czyli dni bez śluzu lub odczucia mokrości
    W przypadku, gdy jest zaobserwowana stała wydzielina, wtedy zwraca się uwagę na zmianę jakości śluzu a nie na jego występowanie lub brak
    An unchanging discharge at the vulva
*/
int cycleDataClass::getFirstDayOfFertilePhaseStartAccordingToCervicalMucusBasedRule( cardEntry *card, int cardNo, configClass *config )
{
    bool wasDryDaysObserved = false;

    for ( int d = 1; d <= card->getDaysCount(); d++ ) {
        dayEntry *day = card->getDay(d);
        if ( day->getMenstruation() > -1 ) {
            continue;
        }

        if (!day->isMucus()) {
            // dry day occured
            wasDryDaysObserved = true;
        } else {
            // mucus observed
            if (wasDryDaysObserved) {
                return d;
            } else if (day->isMucusMoreFertile()) {
                return d;
            }
        }
    }
    return -1;
}

/**
 * Calculate the first day of fertile phase according cervical position based rule.
 * Only for CYCLE_TYPE_NORMAL & CYCLE_TYPE_PREGNANCY
 */
/*
    Faza niepłodności przedowulacyjnej kończy się dzień przed jakąkolwiek zmianą w szyjce macicy.
*/
int cycleDataClass::getFirstDayOfFertilePhaseStartAccordingToCervicalPositionBasedRule( cardEntry *card, int cardNo )
{
    // check if cervix change has been observed
    for ( int d = 1; d < card->getDaysCount(); d++ )
        if (card->getDay(d)->isCervixChange())
            return d;

    return -1;
}


/******************************************************************************/

/**
 * only for CYCLE_TYPE_NORMAL & CYCLE_TYPE_PREGNANCY
 */
bool cycleDataClass::calculateResultInfertilePhaseStart( cardEntry *card, int cardNo )
{
    int infertilePhaseStartDay = -1;
    bool temperatureSet = card->isResultTemperatureLevelSet();
    int startDay = 7;
    if (temperatureSet) {
        startDay = card->getResultTemperatureHighLevelEnd();
        infertilePhaseStartDay = card->getResultTemperatureHighLevelEnd();
    }

    // if temperature is set then check if (mucus peak + 3) or (cervix peak +3) is not set later.
    // if temperature is not set then search the day (mucus peak + 4) or (cervix peak +3) and take the one set later.
    for ( int dayNo = startDay; dayNo <= card->getDaysCount(); dayNo++ ) {
        if ( card->isResultCervixPeak(dayNo-3) ) {
            infertilePhaseStartDay = dayNo;
        }

        if ( card->isResultMucusPeak( dayNo - (temperatureSet ? 3 : 4) ) ) {
            infertilePhaseStartDay = dayNo;
        }
    }

    if (infertilePhaseStartDay > 0) {
        card->addResultInfertilePhaseStart(infertilePhaseStartDay, true);
        return true;
    }
    return false;
}

/******************************************************************************/

/**
 * only for CYCLE_TYPE_AFTER_PREGNANCY & CYCLE_TYPE_PERI_MENOPAUSE
 */
bool cycleDataClass::calculateResultPhasesInAfterPregnancyCycle( cardEntry *card, int cardNo, configClass *config )
{
    if (card->getDaysCount() <= 12*7) {
        // not enouth days to calculate anything.
        return false;
    }

    bool basicInfertilePatternWithMucus = isBasicInfertilePatternWithMucus(card);

    //if (basicInfertilePatternWithMucus)
    //std::cout << "basic infertile pattern: with mucus" << "\n" << std::flush;
    // else
    //std::cout << "basic infertile pattern: dry" << "\n" << std::flush;

    bool infertilePhase = true;
    int dayAfterPeak = 0;

    for (int dayNo = 12*7; dayNo <= card->getDaysCount(); dayNo++) {
        //std::cout << "day " << dayNo;
        dayEntry *day = card->getDay(dayNo);
        if (infertilePhase) {
            // search for beginning of fertile phase
            if (basicInfertilePatternWithMucus) {
                if ( day->isMucusMoreFertile() || day->isCervixChange() || day->isSpotting() ) {
                    card->addResultMucus1stMoreFertileDay(dayNo, true);
                    card->addResultFertilePhaseStart(dayNo, true);
                    //std::cout << " - fertile phase";
                    infertilePhase = false;
                }
            } else {
                if ( day->isMucus() || day->isCervixChange() || day->isSpotting() ) {
                    card->addResultMucus1stDay(dayNo, true);
                    card->addResultFertilePhaseStart(dayNo, true);
                    //std::cout << " - fertile phase";
                    infertilePhase = false;
                }
            }
        } else {
            if (basicInfertilePatternWithMucus) {
                if ( day->isMucusMoreFertile() || day->isSpotting() ) {
                    dayAfterPeak = 0;
                } else {
                    dayAfterPeak++;
                }
            } else {
                if ( day->isMucus() || day->isSpotting() ) {
                    dayAfterPeak = 0;
                } else {
                    dayAfterPeak++;
                }
            }
            //std::cout << " - dayAfterPeak = " << dayAfterPeak;
            if (dayAfterPeak == 4) {
                dayAfterPeak = 0;
                card->addResultMucusPeak(dayNo-4, true);
                card->addResultInfertilePhaseStart(dayNo, true);
                infertilePhase = true;
                //std::cout << " - infertile phase";
            }
        }
        //std::cout << "\n" << std::flush;
    }
    return true;
}

bool cycleDataClass::isBasicInfertilePatternWithMucus(cardEntry *card)
{
    int bip = card->getBasicInfertilePattern();
    if (bip == CYCLE_BIP_MUCUS) {
        return true;
    } else if (bip == CYCLE_BIP_DRY) {
        return false;
    }

    // auto so we have to calculate the pattern
    int numberOfDryDays = 0;
    int numberOfDaysWithMucus = 0;
    // check the basic infertile pattern
    for (int dayNo = 5*7; dayNo < 12*7; dayNo++) {
        if (card->getDay(dayNo)->isMucus()) {
            // mucus
            numberOfDryDays = 0;
            numberOfDaysWithMucus++;
            if (dayNo > 7*7 && numberOfDryDays < 12 && numberOfDaysWithMucus > 2) {
                return true;
            }
        } else {
            // dry
            numberOfDryDays++;
            numberOfDaysWithMucus = 0;
        }
    }
    return false;
}

/******************************************************************************
*******************************************************************************
******************************************************************************/

/**
 * Return number of days historical cycles from which the shortest cycle is calculated.
 */
int cycleDataClass::getNumberOfHistoricalCyclesUsedToCalculateShortestCycle( int cardNo, configClass* config )
{
    if (config->numberOfHistoricalCyclesToUse * 2 / 3 > cardNo  && m_shortestCycleDays > 0) {
        return m_shortestCycleFromCycles + cardNo -1;
    } else if (cardNo <= config->numberOfHistoricalCyclesToUse) {
        return cardNo -1;
    } else {
        return config->numberOfHistoricalCyclesToUse;
    }
}

/**
 * Return number of days historical cycles from which the earliest first day of high level temperature is calculated.
 */
int cycleDataClass::getNumberOfHistoricalCyclesUsedToCalculateEarliestFirstDayOfHighLevelTemperature( int cardNo, configClass* config )
{
    if (cardNo <= config->numberOfHistoricalCyclesToUse) {
        return cardNo -1;
    } else {
        return config->numberOfHistoricalCyclesToUse;
    }
}

/**
 * Return number of days of the shortest cycle from last 'config->numberOfHistoricalCyclesToUse' cycles (or less if there are no such many cycles stored)
 */
int cycleDataClass::getNumberOfDaysOfShortestCycle( int cardNo, configClass* config )
{
    if ( cardNo < 1 || cardNo > getCardsCount()) {
        addErrorMessages( _T( "cycleDataClass::getNumberOfDaysOfShortestCycle() failed" ) );
        return false;
    }

    int ret = 2000;
    int firstCard = (cardNo <= config->numberOfHistoricalCyclesToUse ? 1 : cardNo - config->numberOfHistoricalCyclesToUse);
    for ( int i = firstCard; i < cardNo; i++ ) {
        if (getCard(i)->getDaysCount() < ret) {
            ret = getCard(i)->getDaysCount();
        }
    }

    if (config->numberOfHistoricalCyclesToUse * 2 / 3 > cardNo  && m_shortestCycleDays > 0 && m_shortestCycleDays < ret) {
        return m_shortestCycleDays;
    }

    if (ret == 2000) {
        return -1;
    } else {
        return ret;
    }
}

/**
 * Return earliest first day of high level temperature from last 'config->numberOfHistoricalCyclesToUse' cycles (or less if there are no such many cycles stored)
 */
int cycleDataClass::getEarliestFirstDayOfHighLevelTemperature( int cardNo, configClass* config )
{
    if ( cardNo < 1 || cardNo > getCardsCount()) {
        addErrorMessages( _T( "cycleDataClass::getNumberOfDaysOfShortestCycle() failed" ) );
        return false;
    }
    int ret = 2000;
    int firstCard = (cardNo <= config->numberOfHistoricalCyclesToUse ? 1 : cardNo - config->numberOfHistoricalCyclesToUse);
    for ( int c = firstCard; c < cardNo; c++ ) {
        cardEntry *card = getCard( c );
        if (!card->getCorruptedData() && card->isResultTemperatureLevelSet() && card->getResultTemperatureHighLevelStart() < ret) {
            ret = card->getResultTemperatureHighLevelStart();
        }
    }
    if (ret == 2000) {
        return -1;
    } else {
        return ret;
    }
}


/**
 *
 */
bool cycleDataClass::wasMoreFertileMucusFor5DaysInPreviousCycles( int cardNo, configClass* config )
{
    if ( cardNo < 1 || cardNo > getCardsCount()) {
        addErrorMessages( _T( "cycleDataClass::wasMoreFertileMucusFor5DaysInPreviousCycles() failed" ) );
        return false;
    }
    int firstCard = (cardNo <= config->numberOfHistoricalCyclesToUse ? 1 : cardNo - config->numberOfHistoricalCyclesToUse);
    for ( int c = firstCard; c < cardNo; c++ ) {
        cardEntry *card = getCard( c );
        if ( card->getCorruptedData() || card->getCycleType() == CYCLE_TYPE_AFTER_PREGNANCY )
            continue;

        // TEMP
        if ( card->isResultMucusPeakSet() && card->isResultMucus1stMoreFertileDaySet() ) {
            //m_errorMessages << wxString::Format ( _("\n(card %i, more fertile mucus observed for %i days)"), c, card->getResultMucusPeak()[0] - card->getResultMucus1stMoreFertileDay()[0] + 1);
            if ( card->getResultMucusPeak()[0] - card->getResultMucus1stMoreFertileDay()[0] + 1 < 5)
                return false;
        } else {
            int moreFertileDaysCount = 0;
            for ( int d = 1; d <= card->getDaysCount(); d++ )
                if (card->getDay(d)->isMucusMoreFertile())
                    moreFertileDaysCount++;

            if (moreFertileDaysCount < 5)
                return false;
        }
    }
    return true;
}

bool cycleDataClass::isCardFromLast3AfterStoppedPills(int cardNo)
{
    if (getCard(cardNo)->getStoppedPills())
        return true;
    if (cardNo > 1 && getCard(cardNo-1)->getStoppedPills())
        return true;
    if (cardNo > 2 && getCard(cardNo-2)->getStoppedPills())
        return true;

    return false;
}
