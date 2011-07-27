/*******************************************************************************
//
// Name:        dayEntry.cpp
// Author:      enkeli
// Description:
//
*******************************************************************************/

#include "dayEntry.h"

/*******************************************************************************
*** CONSTRUCTORS ***************************************************************
*******************************************************************************/

/**
 *
 */
dayEntry::dayEntry()
{
     m_menstruation = -1;
     m_coitusRecord = 0;
     m_otherDisturbances = false;
     m_temperatureDisturbances = false;
     m_temperatureMeasuredValue = -1;
     m_temperatureMeasurementTime = wxDateTime();
     m_temperatureMeasurementTime.Set( 0, 0, 0, 0 );
     m_temperatureMeasurementPlace = -1;
     m_temperatureAdditionalCorrection = 0;
     m_temperatureValueAfterCorrections = -1;
     m_mucusFeelingExperience = -1;
     m_mucusAppearance = 0;
     m_cervixPosition = -1;
     m_cervixDilation = -1;
     m_cervixHardness = -1;
     m_ovulationPain = -1;
     m_breastsTension = -1;
     m_spotting = -1;
     m_additionalNotes = wxEmptyString;
}

/*******************************************************************************
*** STORING THE DATA ***********************************************************
*******************************************************************************/

/**
 *
 */
bool dayEntry::setMenstruation( int value )
{
     m_menstruation = value;
     return true;
}

/**
 *
 */
bool dayEntry::setCoitusRecord( int value )
{
     m_coitusRecord = value;
     return true;
}

/**
 *
 */
bool dayEntry::setOtherDisturbances( bool value )
{
     m_otherDisturbances = value;
     return true;
}

/**
 *
 */
bool dayEntry::setTemperatureDisturbances( bool value )
{
     m_temperatureDisturbances = value;
     return true;
}

/**
 *
 */
bool dayEntry::setTemperatureMeasuredValue( int value )
{
     m_temperatureMeasuredValue = value;
     return true;
}

/**
 *
 */
bool dayEntry::setTemperatureMeasurementTime( wxDateTime value )
{
     m_temperatureMeasurementTime = value;
     return true;
}

/**
 *
 */
bool dayEntry::setTemperatureMeasurementPlace( int value )
{
     m_temperatureMeasurementPlace = value;
     return true;
}

/**
 *
 */
bool dayEntry::setTemperatureAdditionalCorrection( int value )
{
     m_temperatureAdditionalCorrection = value;
     return true;
}

/**
 *
 */
bool dayEntry::setTemperatureValueAfterCorrections( int value )
{
     m_temperatureValueAfterCorrections = value;
     return true;
}

/**
 *
 */
bool dayEntry::setMucusFeelingExperience( int value )
{
     m_mucusFeelingExperience = value;
     return true;
}

/**
 *
 */
bool dayEntry::setMucusAppearance( int value )
{
     m_mucusAppearance = value;
     return true;
}

/**
 *
 */
bool dayEntry::setCervixPosition( int value )
{
     m_cervixPosition = value;
     return true;
}

/**
 *
 */
bool dayEntry::setCervixDilation( int value )
{
     m_cervixDilation = value;
     return true;
}

/**
 *
 */
bool dayEntry::setCervixHardness( int value )
{
     m_cervixHardness = value;
     return true;
}

/**
 *
 */
bool dayEntry::setOvulationPain( int value )
{
     m_ovulationPain = value;
     return true;
}

/**
 *
 */
bool dayEntry::setBreastsTension( int value )
{
     m_breastsTension = value;
     return true;
}

/**
 *
 */
bool dayEntry::setSpotting( int value )
{
     m_spotting = value;
     return true;
}

/**
 *
 */
bool dayEntry::setAdditionalNotes( wxString value )
{
     m_additionalNotes = value;
     return true;
}

/*******************************************************************************
*** READING THE DATA ***********************************************************
*******************************************************************************/

/**
 *
 */
int dayEntry::getMenstruation()
{
     return m_menstruation;
}

/**
 *
 */
int dayEntry::getCoitusRecord()
{
     return m_coitusRecord;
}

/**
 *
 */
bool dayEntry::getOtherDisturbances()
{
     return m_otherDisturbances;
}

/**
 *
 */
bool dayEntry::getTemperatureDisturbances()
{
     return m_temperatureDisturbances;
}

/**
 *
 */
int dayEntry::getTemperatureMeasuredValue()
{
     return m_temperatureMeasuredValue;
}

/**
 *
 */
wxDateTime dayEntry::getTemperatureMeasurementTime()
{
     return m_temperatureMeasurementTime;
}

/**
 *
 */
int dayEntry::getTemperatureMeasurementPlace()
{
     return m_temperatureMeasurementPlace;
}

/**
 *
 */
int dayEntry::getTemperatureAdditionalCorrection()
{
     return m_temperatureAdditionalCorrection;
}

/**
 *
 */
int dayEntry::getTemperatureValueAfterCorrections()
{
     return m_temperatureValueAfterCorrections;
}

/**
 *
 */
int dayEntry::getMucusFeelingExperience()
{
     return m_mucusFeelingExperience;
}

/**
 *
 */
int dayEntry::getMucusAppearance()
{
     return m_mucusAppearance;
}

/**
 * Convert m_mucusAppearance from int to string
 */
wxString dayEntry::convertMucusAppearance( int input )
{
     wxString ret = _T( "" );

     if ( input >= MUCUS_LENGHTOFSTRETCH3 ) {
          input -= MUCUS_LENGHTOFSTRETCH3;
          ret = _T( " 3" ) + ret;
     }
     if ( input >= MUCUS_LENGHTOFSTRETCH2 ) {
          input -= MUCUS_LENGHTOFSTRETCH2;
          ret = _T( " 2" ) + ret;
     }
     if ( input >= MUCUS_LENGHTOFSTRETCH1 ) {
          input -= MUCUS_LENGHTOFSTRETCH1;
          ret = _T( " 1" ) + ret;
     }
     if ( input >= MUCUS_AMOUNT3 ) {
          input -= MUCUS_AMOUNT3;
          ret = _T( " +++" ) + ret;
     }
     if ( input >= MUCUS_AMOUNT2 ) {
          input -= MUCUS_AMOUNT2;
          ret = _T( " ++" ) + ret;
     }
     if ( input >= MUCUS_AMOUNT1 ) {
          input -= MUCUS_AMOUNT1;
          ret = _T( " +" ) + ret;
     }
     if ( input >= MUCUS_SEMINALRESIDUE ) {
          input -= MUCUS_SEMINALRESIDUE;
          ret = wxString::Format( _T( " %s%s" ), string_mucusAppearanceSeminalResidue, ret.c_str() );
     }
     if ( input >= MUCUS_STRETCHY ) {
          input -= MUCUS_STRETCHY;
          ret = wxString::Format( _T( " %s%s" ), string_mucusAppearanceStretchy, ret.c_str() );
     }
     if ( input >= MUCUS_CLEAR ) {
          input -= MUCUS_CLEAR;
          ret = wxString::Format( _T( " %s%s" ), string_mucusAppearanceClear, ret.c_str() );
     }
     if ( input >= MUCUS_TACKY ) {
          input -= MUCUS_TACKY;
          ret = wxString::Format( _T( " %s%s" ), string_mucusAppearanceTacky, ret.c_str() );
     }
     if ( input >= MUCUS_YELLOWISH ) {
          input -= MUCUS_YELLOWISH;
          ret = wxString::Format( _T( " %s%s" ), string_mucusAppearanceYellowish, ret.c_str() );
     }
     if ( input >= MUCUS_WHITE ) {
          input -= MUCUS_WHITE;
          ret = wxString::Format( _T( " %s%s" ), string_mucusAppearanceWhite, ret.c_str() );
     }
     if ( input >= MUCUS_OPAQUE ) {
          input -= MUCUS_OPAQUE;
          ret = wxString::Format( _T( " %s%s" ), string_mucusAppearanceOpaque, ret.c_str() );
     }

     return ret.Trim( false );
}

/**
 *
 */
int dayEntry::getCervixPosition()
{
     return m_cervixPosition;
}

/**
 *
 */
int dayEntry::getCervixDilation()
{
     return m_cervixDilation;
}

/**
 *
 */
int dayEntry::getCervixHardness()
{
     return m_cervixHardness;
}

/**
 *
 */
int dayEntry::getOvulationPain()
{
     return m_ovulationPain;
}

/**
 *
 */
int dayEntry::getBreastsTension()
{
     return m_breastsTension;
}

/**
 *
 */
int dayEntry::getSpotting()
{
     return m_spotting;
}

/**
 *
 */
wxString dayEntry::getAdditionalNotes()
{
     return m_additionalNotes;
}


/*******************************************************************************
********************************************************************************
*******************************************************************************/
