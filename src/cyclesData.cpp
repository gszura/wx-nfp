/*******************************************************************************
//
// m_name:        cycleDataClass.cpp
// Author:      enkeli
// Description:
//
*******************************************************************************/

#include <wx/ffile.h>
#include <wx/filename.h>
#include "cyclesData.h"
#include <wx/dir.h>

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * Constructor
 */
cycleDataClass::cycleDataClass( )
{
    m_cardModified = false;
    m_activeCard = -1;
    m_activeDay = -1;
    m_prevActiveDay = -1;
    m_coitusRecordCounter = 0;

    // dane osobowe
    m_name = _( "your name" );
    m_birthdayDay = wxDateTime::Today();
}

/**
 *
 */
void cycleDataClass::addErrorMessages( wxString e )
{
    if ( e.Length() > 0 )
        m_errorMessages += _T( "\n- " ) + e;
}

/**
 *
 */
wxString cycleDataClass::getErrorMessages()
{
    return m_errorMessages;
}

/**
 *
 */
void cycleDataClass::setCardModified( bool value )
{
    m_cardModified = value;
}

/**
 *
 */
bool cycleDataClass::getCardModified()
{
    return m_cardModified;
}

/**
 *
 */
void cycleDataClass::setCoitusRecordCounter( int value )
{
    m_coitusRecordCounter = value;
}

/**
 *
 */
void cycleDataClass::increaseCoitusRecordCounter( int value )
{
    m_coitusRecordCounter += value;
}

/**
 *
 */
int cycleDataClass::getCoitusRecordCounter()
{
    return m_coitusRecordCounter;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
bool cycleDataClass::setActiveCard( int cardNo )
{
    if ( cardNo < 1 || cardNo > getCardsCount() ) {
        m_activeCard = -1;
        return false;
    }

    m_activeCard = cardNo;
    //checkIfTemperatureResultIsDefined();
    return true;
}

/**
 *
 */
int cycleDataClass::getActiveCard()
{
    return m_activeCard;
}

/**
 *
 */
bool cycleDataClass::setActiveDay( int dayNo )
{
    if ( dayNo < 1 || dayNo > getDaysCount() ) {
        m_activeDay = -1;
        return false;
    }

    m_prevActiveDay = m_activeDay;
    m_activeDay = dayNo;
    return true;
}

/**
 *
 */
int cycleDataClass::getActiveDay()
{
    return m_activeDay;
}

/**
 *
 */
int cycleDataClass::getPrevActiveDay()
{
    return m_prevActiveDay;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * Create new card with one day.
 */
bool cycleDataClass::createNewSet()
{
    if ( getCardsCount() > 0 )
        removeAll();

    m_coitusRecordCounter = 0;

    if ( addNewCard() == -1 )
        return false;

    if ( addNewDay() == -1 )
        return false;

    return true;
}

/**
 * Remove current data
 */
bool cycleDataClass::removeAll()
{
    if ( removeAllCards() ) {
        m_name = _T( "your name" );
        m_birthdayDay = wxDateTime::Today();
        return true;
    } else {
        return false;
    }
}

/*******************************************************************************
***** GENERAL INFO *************************************************************
*******************************************************************************/

/**
 *
 */
bool cycleDataClass::setName( wxString value )
{
    m_name = value;
    return true;
}

/**
 *
 */
bool cycleDataClass::setBirthdayDay( wxDateTime value )
{
    m_birthdayDay = value;
    return true;
}

/**
 *
 */
wxString cycleDataClass::getName()
{
    return m_name;
}

/**
 *
 */
wxDateTime cycleDataClass::getBirthdayDay()
{
    return m_birthdayDay;
}

/*******************************************************************************
***** m_cards ********************************************************************
*******************************************************************************/

/**
 *
 */
int cycleDataClass::addNewCard()
{
    int cardsCount = getCardsCount();
    if ( cardsCount == 0 )
        m_cards[1] = new cardEntry();
    else
        m_cards[cardsCount+1] = new cardEntry( m_cards[cardsCount] );

    if ( getCardsCount() == cardsCount + 1 )
        return getCardsCount();
    else
        return -1;
}

/**
 *
 */
bool cycleDataClass::removeLastCard()
{
    int cardNo = getCardsCount();

    if ( cardNo > 0 ) {
        m_cards[cardNo]->removeAllDays();
        m_cards.erase( cardNo );
        return true;
    } else {
        return false;
    }
}

/**
 *
 */
bool cycleDataClass::removeAllCards()
{
    for ( int i = 1; i <= getCardsCount(); i++ )
        m_cards[i]->removeAllDays();

    m_cards.clear();

    return true;
}

/**
 *
 */
int cycleDataClass::getCardsCount()
{
    return m_cards.size();
}

/**
 *
 */
cardEntry * cycleDataClass::getCard()
{
    return getCard( m_activeCard );
}

/**
 *
 */
cardEntry * cycleDataClass::getCard( int cardNo )
{
    if ( m_cards.count( cardNo ) == 0 ) return NULL;

    return m_cards[cardNo];
}

/*******************************************************************************
***** DAYS *********************************************************************
*******************************************************************************/

/**
 *
 */
int cycleDataClass::addNewDay()
{
    return addNewDay( getCardsCount() );
}

/**
 *
 */
int cycleDataClass::addNewDay( int cardNo )
{
    if ( cardNo > 0 )
        if ( m_cards[cardNo]->addNewDay( NULL ) ) return getDaysCount( cardNo );
        else return -1;
    else return -1;
}

/**
 *
 */
bool cycleDataClass::removeLastDay()
{
    int cardNo = getCardsCount();
    if ( cardNo > 0 )
        if ( m_cards[cardNo]->removeLastDay() ) return true;
        else return false;
    else return false;
}

/**
 *
 */
int cycleDataClass::getDaysCount()
{
    return getDaysCount( m_activeCard );
}

/**
 *
 */
int cycleDataClass::getDaysCount( int cardNo )
{
    if ( m_cards.count( cardNo ) == 0 ) return -1;

    return m_cards[cardNo]->getDaysCount();
}

/**
 * Return active day on active card.
 */
dayEntry * cycleDataClass::getDay()
{
    return getDay( m_activeCard, m_activeDay );
}

/**
 * Return day 'dayNo' on active card.
 */
dayEntry * cycleDataClass::getDay( int dayNo )
{
    return getDay( m_activeCard, dayNo );
}

/**
 * Return day 'dayNo' on card 'cardNo'.
 */
dayEntry * cycleDataClass::getDay( int cardNo, int dayNo )
{
    if ( m_cards.count( cardNo ) == 0 || ! m_cards[cardNo]->dayExist( dayNo ) ) return NULL;

    return m_cards[cardNo]->getDay( dayNo );
}

/*******************************************************************************
***** READING CYCLES DATA FROM FILE ********************************************
*******************************************************************************/

/**
 *
 */
bool cycleDataClass::readCardsDataFromFile( wxString fileName )
{



    wxString input;
    wxString tmp, tmp2;
    int rest;
    wxFFile file;
    m_coitusRecordCounter = 0;

    m_errorMessages = wxEmptyString;

    if ( !wxFileExists( fileName ) ) {
        addErrorMessages( wxString::Format( _( "File doesn't exist: %s" ), fileName.c_str() ) );

        return false;
    }

    if ( !file.Open( fileName, _T( "r" ) ) ) {
        addErrorMessages( wxString::Format( _( "Cannot open file: %s" ), fileName.c_str() ) );

        return false;
    }

    if ( file.Length() < 11 ) {
        file.Close();
        addErrorMessages( wxString::Format( _( "File is not the data file of the NFP application: %s" ), fileName.c_str() ) );

        return false;
    }

    if ( ! file.ReadAll( &input ) ) {
        file.Close();
        addErrorMessages( wxString::Format( _( "Cannot read file: %s" ), fileName.c_str() ) );

        return false;
    }

    file.Close();

    if ( input.IsEmpty() ) {
        addErrorMessages( wxString::Format( _( "File is empty: %s" ), fileName.c_str() ) );

        return false;
    }

    input = getSection( input, _T( "nfp" ), rest );

    if ( input.Length() == 0 ) {
        addErrorMessages( wxString::Format( _( "File is not the data file of the NFP application: %s" ), fileName.c_str() ) );

        return false;
    }

    // dane osobowe
    tmp = getSection( input, _T( "personalData" ), rest );

    if ( tmp.Length() > 0 ) {
        if ( ! readPersonalData( tmp ) ) {
            return false;
        }
    } else {
        addErrorMessages( wxString::Format( _( "File is not the data file of the NFP application: %s" ), fileName.c_str() ) );

        return false;
    }

    // karty
    tmp = getSection( input, _T( "cardsList" ), rest );

    if ( tmp.Length() > 0 ) {
        tmp2 = getSection( tmp, _T( "card" ), rest );

        while ( tmp2.Length() > 0 ) {
            if ( ! readCard( tmp2 ) ) {
                return false;
            }

            if (( int ) tmp.Length() > rest + 1 ) {
                tmp = tmp.Mid( rest + 1, ( int ) tmp.Length() - rest ).Trim();
                tmp2 = getSection( tmp, _T( "card" ), rest );
            } else {
                tmp2 = wxEmptyString;
            }
        }

    }


    return true;
}

/**
 *
 */
bool cycleDataClass::readPersonalData( wxString input )
{

    m_name = readString( input, _T( "m_name" ) );
    if (m_name.empty()) {
        m_name = readString( input, _T( "name" ) );
    }

    wxDateTime now = wxDateTime::Now();
    m_birthdayDay = readDateTime( input, _T( "m_birthdayDay" ) );
    if (m_birthdayDay.GetYear() == now.GetYear()) {
        m_birthdayDay = readDateTime( input, _T( "birthdayDay" ) );
    }

    if ( m_name.length() == 0 ) {

    }

    return true;
}

/**
 *
 */
bool cycleDataClass::readCard( wxString input )
{


    int cardNo = addNewCard();

    if ( cardNo == -1 ) {
        addErrorMessages( _( "Error occured while adding new card" ) );

        return false;
    }

    cardEntry * card = m_cards[cardNo];

    int cardNo1 = readInt( input, _T( "no" ) );

    if ( cardNo != cardNo1 ) {
        addErrorMessages( wxString::Format( _( "Incorrect card number: %i, expected: %i" ), cardNo1, cardNo ) );
        return false;
    }

    // reading card data
    card->setFirstDayOfCycle( readDateTime( input, _T( "firstDay" ) ) );
    card->setTemperatureUsualMeasurementTime( readDateTime( input, _T( "tempTime" ) ) );
    card->setTemperatureUsualMeasurementPlace( readInt( input, _T( "tempPlace" ) ) );
    if ( card->getTemperatureUsualMeasurementPlace() == -1 ) {
        card->setTemperatureUsualMeasurementPlace( 2 );
    }
    card->setCardLocked( readBool( input, _T( "locked" ) ) );
    card->setNotes( readString( input, _T( "notes" ) ) );
    card->setTemperatureCorrectionWhenMeasuredInMouth( readInt( input, _T( "correctionMouth" ) ) );
    if ( card->getTemperatureCorrectionWhenMeasuredInMouth() == -1 ) {
        card->setTemperatureCorrectionWhenMeasuredInMouth( 0 );
    }
    card->setTemperatureCorrectionWhenMeasuredInVagina( readInt( input, _T( "correctionVagina" ) ) );

    if ( card->getTemperatureCorrectionWhenMeasuredInVagina() == -1 ) {
        card->setTemperatureCorrectionWhenMeasuredInVagina( 0 );
    }

    card->setTemperatureCorrectionWhenMeasuredInRectum( readInt( input, _T( "correctionRectum" ) ) );

    if ( card->getTemperatureCorrectionWhenMeasuredInRectum() == -1 ) {
        card->setTemperatureCorrectionWhenMeasuredInRectum( 0 );
    }

    int dataInt = readInt( input, _T( "correctionTime" ) );

    if ( dataInt > 0 ) {
        card->setTemperatureCorrectionForMeasurementTimeSake( dataInt );
    }

    card->setResultMucus1stDay( readHash( input, _T( "resultMucus1stDay" ) ) );
    card->setResultMucus1stMoreFertileDay( readHash( input, _T( "resultMucus1stMoreFertileDay" ) ) );
    card->setResultMucusPeak( readHash( input, _T( "resultMucusPeak" ) ) );
    card->setResultCervix1stDay( readHash( input, _T( "resultCervix1stDay" ) ) );
    card->setResultCervixPeak( readHash( input, _T( "resultCervixPeak" ) ) );
    card->setResultTemperatureLowLevelValue( readInt( input, _T( "resultTemperatureLowLevelValue" ) ) );
    card->setResultTemperatureLowLevelStart( readInt( input, _T( "resultTemperatureLowLevelStart" ) ) );
    card->setResultTemperatureHighLevelStart( readInt( input, _T( "resultTemperatureHighLevelStart" ) ) );
    card->setResultTemperatureHighLevelEnd( readInt( input, _T( "resultTemperatureHighLevelEnd" ) ) );

    // TODO DEPRECATED START
    if (readString(input, _T( "resultPhase2Start" )) != wxEmptyString) {
        card->setResultFertilePhaseStart( readHash( input, _T( "resultPhase2Start" ) ) );
    }
    if (readString(input, _T( "resultPhase3Start" )) != wxEmptyString) {
        card->setResultInfertilePhaseStart( readHash( input, _T( "resultPhase3Start" ) ) );
    }
    // DEPRECATED END
    card->setResultFertilePhaseStart( readHash( input, _T( "resultFertilePhaseStart" ) ) );
    card->setResultInfertilePhaseStart( readHash( input, _T( "resultInfertilePhaseStart" ) ) );


    // reading card's days data
    wxString tmp, tmp2;
    int rest;
    tmp = getSection( input, _T( "daysList" ), rest );

    if ( !tmp.IsEmpty() ) {
        tmp2 = getSection( tmp, _T( "day" ), rest );

        while ( tmp2.Length() > 0 ) {
            if ( ! readDay( tmp2, cardNo ) ) {
                return false;
            }

            if (( int ) tmp.Length() > rest + 1 ) {
                tmp = tmp.Mid( rest + 1, ( int ) tmp.Length() - rest ).Trim();
                tmp2 = getSection( tmp, _T( "day" ), rest );
            } else {
                tmp2 = wxEmptyString;
            }
        }

    }


    return true;
}

/**
 *
 */
bool cycleDataClass::readDay( wxString input, int cardNo )
{
    int dayNo = addNewDay();
    if ( dayNo == -1 ) {
        addErrorMessages( _( "Error occured while adding new day" ) );
        return false;
    }

    dayEntry * day = getDay( cardNo, dayNo );
    int dayNo1 = readInt( input, _T( "no" ) );
    if ( dayNo != dayNo1 ) {
        addErrorMessages( wxString::Format( _( "Incorrect day number: %i, expected: %i, card" ), dayNo1, dayNo, cardNo ) );
        return false;
    }


    day->setMenstruation( readInt( input, _T( "menstruation" ) ) );
    if ( day->getMenstruation() < 1 || day->getMenstruation() > 2 ) {
        day->setMenstruation( -1 );
    }

    day->setCoitusRecord( readInt( input, _T( "coitus" ) ) );
    if ( day->getCoitusRecord() > 0 ) {
        m_coitusRecordCounter += day->getCoitusRecord();
    }

    day->setOtherDisturbances( readBool( input, _T( "otherDisturbances" ) ) );
    day->setTemperatureDisturbances( readBool( input, _T( "tempDisturbances" ) ) );
    day->setTemperatureMeasuredValue( readInt( input, _T( "tempValue" ) ) );
    day->setTemperatureMeasurementTime( readDateTime( input, _T( "tempTime" ) ) );

    if ( day->getTemperatureMeasurementTime().GetHour() == 0 && day->getTemperatureMeasurementTime().GetMinute() == 0 ) {
        day->setTemperatureMeasurementTime( getCard( cardNo )->getTemperatureUsualMeasurementTime() );
    }

    day->setTemperatureMeasurementPlace( readInt( input, _T( "tempPlace" ) ) );
    if ( day->getTemperatureMeasurementPlace() < 1 || day->getTemperatureMeasurementPlace() > 3 ) {
        day->setTemperatureMeasurementPlace( getCard( cardNo )->getTemperatureUsualMeasurementPlace() );
    }

    day->setTemperatureAdditionalCorrection( readInt( input, _T( "tempCorrection" ) ) );
    if ( day->getTemperatureAdditionalCorrection() == -1 ) {
        day->setTemperatureAdditionalCorrection( 0 );
    }

    day->setTemperatureValueAfterCorrections( readInt( input, _T( "tempValueCorrected" ) ) );
    if ( day->getTemperatureValueAfterCorrections() < 0 && day->getTemperatureMeasuredValue() > 0 ) {
        day->setTemperatureValueAfterCorrections( calculateCorrectTemperatureValue( cardNo, dayNo ) );
        setCardModified( true );
    }

    day->setMucusFeelingExperience( readInt( input, _T( "mucusFeeling" ) ) );
    day->setMucusAppearance( readInt( input, _T( "mucusAppearance" ) ) );

    day->setCervixPosition( readInt( input, _T( "cervixPosition" ) ) );
    day->setCervixDilation( readInt( input, _T( "cervixDilation" ) ) );
    day->setCervixHardness( readInt( input, _T( "cervixHardness" ) ) );

    day->setOvulationPain( readInt( input, _T( "ovulationPain" ) ) );
    day->setBreastsTension( readInt( input, _T( "breastsTension" ) ) );
    day->setSpotting( readInt( input, _T( "spotting" ) ) );
    day->setAdditionalNotes( readString( input, _T( "additionalNotes" ) ) );

    return true;
}

/******************************************************************************/

/**
 *
 */
wxString cycleDataClass::getSection( wxString input, wxString tag, int &rest )
{

    rest = 0;

    if ( input.IsEmpty() )
        return wxEmptyString;

    if ( tag.IsEmpty() )
        return wxEmptyString;

    wxString t1 = _T( "<" ) + tag + _T( ">" );

    wxString t2 = _T( "</" ) + tag + _T( ">" );

    int s1 = input.Find( t1 );

    if ( s1 == 0 )
        return wxEmptyString;

    int s2 = input.Find( t2 );

    if ( s2 == 0 )
        return wxEmptyString;

    rest = s2 + t2.Length();

    return input.Mid( s1 + t1.Length(), s2 - s1 - t1.Length() );
}

/**
 *
 */
wxString cycleDataClass::readString( wxString input, wxString tag )
{

    if ( input.IsEmpty() ) {
        //
        return wxEmptyString;
    }

    if ( tag.IsEmpty() ) {
        //
        return wxEmptyString;
    }

    wxString t1 = _T( "<" ) + tag + _T( ">" );

    wxString t2 = _T( "</" ) + tag + _T( ">" );

    int s1 = input.Find( t1 );

    if ( s1 < 0 ) {
        //
        return wxEmptyString;
    }

    int s2 = input.Find( t2 );

    if ( s2 < 0 ) {
        //
        return wxEmptyString;
    }

    if ( s2-s1-t1.Length() < 1 ) {
        //
        return wxEmptyString;
    }

    wxString ret = input.Mid( s1 + t1.Length(), s2 - s1 - t1.Length() );

    ret = ret.Trim( true );
    ret = ret.Trim( false );

    //

    return ret;
}

/**
 *
 */
bool cycleDataClass::readBool( wxString input, wxString tag )
{

    wxString tmp = readString( input, tag );

    if ( !tmp.IsEmpty() ) {
        if ( tmp == _T( "x" ) ) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }

}

/**
 *
 */
int cycleDataClass::readInt( wxString input, wxString tag )
{

    wxString tmp = readString( input, tag );

    if ( tmp.IsEmpty() ) {
        //
        return -1;
    }

    int ret = m_util.strToInt( tmp );

    //

    return ret;
}

/**
 *
 */
wxDateTime cycleDataClass::readDateTime( wxString input, wxString tag )
{

    wxDateTime ret = wxDateTime();
    ret.Set( 0, 0, 0, 0 );

    try {
        wxString tmp = readString( input, tag );

        if ( tmp.IsEmpty() ) {
            return ret;
        }

        if ( tmp.Mid( 4, 1 ) == _T( "-" ) && tmp.Mid( 7, 1 ) == _T( "-" ) ) {
            // date yyyy-dd-mm
            ret.Set( m_util.strToInt( tmp.Mid( 8, 2 ) ), wxDateTime::Month( m_util.strToInt( tmp.Mid( 5, 2 ) ) - 1 ), m_util.strToInt( tmp.Mid( 0, 4 ) ) );
        } else if ( tmp.Mid( 2, 1 ) == _T( ":" ) ) {
            // time HH:MM
            ret.Set( m_util.strToInt( tmp.Mid( 0, 2 ) ), m_util.strToInt( tmp.Mid( 3, 2 ) ), 0, 0 );
        } else if ( tmp.Mid( 1, 1 ) == _T( ":" ) ) {
            // time H:MM
            ret.Set( m_util.strToInt( tmp.Mid( 0, 1 ) ), m_util.strToInt( tmp.Mid( 2, 2 ) ), 0, 0 );
        }

    } catch ( ... ) {}

    return ret;
}

/**
 * Read results stored in the string "day,day,day,.." and save it in the hash table
 */
intArray cycleDataClass::readHash( wxString input, wxString tag )
{
    wxString tmp = readString( input, tag );

    intArray ret;
    if ( ! tmp.empty() ) {
        int i = tmp.find( _T(",") );
        while ( i > -1 ) {
            ret.Add( m_util.strToInt(tmp.Mid(0,i)) );
            tmp = tmp.Mid(i+1);
            i = tmp.find( _T(",") );
        }
        ret.Add( m_util.strToInt(tmp) );
    }
    return ret;
}


/*******************************************************************************
***** STORING CYCLES DATA TO FILE **********************************************
*******************************************************************************/

/**
 *
 */
bool cycleDataClass::saveCardsDataToFile( wxString fileName )
{
    wxFFile file;
    if ( fileName.IsEmpty() ) {
        addErrorMessages( wxString::Format( _( "Incorrect file name: %s" ), fileName.c_str() ) );
        return false;
    }

    wxString data = _T( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" );

    // TODO add modifications control part

    data += _T( "<nfp>\n" );
    data += _T( " <personalData>" );
    data += getNode( _T( "name" ), m_name );
    data += getNodeDateTime( _T( "birthdayDay" ), m_birthdayDay, _T( "d" ) );
    data += _T( "</personalData>\n" );


    if ( m_name.length() == 0 ) {
        //TODO add assert
    }

    data += _T( " <cardsList>\n" );

    for ( int i = 1; i <= getCardsCount(); i++ ) {
        cardEntry * card = m_cards[i];
        data += _T( "  <card>" );
        data += getNodeInt( _T( "no" ), i );
        data += getNodeDateTime( _T( "firstDay" ), card->getFirstDayOfCycle(), _T( "d" ) );
        data += getNodeDateTime( _T( "tempTime" ), card->getTemperatureUsualMeasurementTime(), _T( "t" ) );
        data += getNodeInt( _T( "tempPlace" ), card->getTemperatureUsualMeasurementPlace() );
        data += getNodeBool( _T( "locked" ), card->getCardLocked() );
        data += getNode( _T( "notes" ), card->getNotes() );
        if ( card->getTemperatureCorrectionWhenMeasuredInMouth() != 0 )
            data += getNodeInt( _T( "correctionMouth" ), card->getTemperatureCorrectionWhenMeasuredInMouth() );
        if ( card->getTemperatureCorrectionWhenMeasuredInVagina() != 0 )
            data += getNodeInt( _T( "correctionVagina" ), card->getTemperatureCorrectionWhenMeasuredInVagina() );
        if ( card->getTemperatureCorrectionWhenMeasuredInRectum() != 0 )
            data += getNodeInt( _T( "correctionRectum" ), card->getTemperatureCorrectionWhenMeasuredInRectum() );
        if ( card->getTemperatureCorrectionForMeasurementTimeSake() != 0 )
            data += getNodeInt( _T( "correctionTime" ), card->getTemperatureCorrectionForMeasurementTimeSake() );
        data += getNodeHash( _T( "resultMucus1stDay" ), card->getResultMucus1stDay() );
        data += getNodeHash( _T( "resultMucus1stMoreFertileDay" ), card->getResultMucus1stMoreFertileDay() );
        data += getNodeHash( _T( "resultMucusPeak" ), card->getResultMucusPeak() );
        data += getNodeHash( _T( "resultCervix1stDay" ), card->getResultCervix1stDay() );
        data += getNodeHash( _T( "resultCervixPeak" ), card->getResultCervixPeak() );
        data += getNodeInt( _T( "resultTemperatureLowLevelValue" ), card->getResultTemperatureLowLevelValue() );
        data += getNodeInt( _T( "resultTemperatureLowLevelStart" ), card->getResultTemperatureLowLevelStart() );
        data += getNodeInt( _T( "resultTemperatureHighLevelStart" ), card->getResultTemperatureHighLevelStart() );
        data += getNodeInt( _T( "resultTemperatureHighLevelEnd" ), card->getResultTemperatureHighLevelEnd() );
        data += getNodeHash( _T( "resultFertilePhaseStart" ), card->getResultFertilePhaseStart() );
        data += getNodeHash( _T( "resultInfertilePhaseStart" ), card->getResultInfertilePhaseStart() );
        data += _T( "\n" );
        data += _T( "   <daysList>\n" );

        for ( int k = 1; k <= getDaysCount( i ); k++ ) {
            dayEntry * day = getDay( i, k );
            data += _T( "    <day>" );
            data += getNodeInt( _T( "no" ), k );
            data += getNodeInt( _T( "menstruation" ), day->getMenstruation() );

            if ( day->getCoitusRecord() > 0 ) {
                data += getNodeInt( _T( "coitus" ), day->getCoitusRecord() );
            }
            data += getNodeBool( _T( "tempDisturbances" ), day->getTemperatureDisturbances() );
            data += getNodeBool( _T( "otherDisturbances" ), day->getOtherDisturbances() );
            data += getNodeInt( _T( "tempValue" ), day->getTemperatureMeasuredValue() );
            if ( day->getTemperatureMeasuredValue() > 0 ) {
                if ( day->getTemperatureAdditionalCorrection() != 0 )
                    data += getNodeInt( _T( "tempCorrection" ), day->getTemperatureAdditionalCorrection() );
                wxString tmpT = day->getTemperatureMeasurementTime().Format( _T( "%H:%M" ) );
                if ( !tmpT.IsSameAs( _T( "00:00" ) ) && !tmpT.IsSameAs( card->getTemperatureUsualMeasurementTime().Format( _T( "%H:%M" ) ) ) ) {
                    data += getNodeDateTime( _T( "tempTime" ), day->getTemperatureMeasurementTime(), _T( "t" ) );
                }
                if ( day->getTemperatureMeasurementPlace() > -1 && day->getTemperatureMeasurementPlace() != card->getTemperatureUsualMeasurementPlace() ) {
                    data += getNodeInt( _T( "tempPlace" ), day->getTemperatureMeasurementPlace() );
                }
                data += getNodeInt( _T( "tempValueCorrected" ), day->getTemperatureValueAfterCorrections() );
            }

            data += getNodeInt( _T( "mucusFeeling" ), day->getMucusFeelingExperience() );
            if ( day->getMucusAppearance() > 0 )
                data += getNodeInt( _T( "mucusAppearance" ), day->getMucusAppearance() );
            data += getNodeInt( _T( "cervixPosition" ), day->getCervixPosition() );
            data += getNodeInt( _T( "cervixDilation" ), day->getCervixDilation() );
            data += getNodeInt( _T( "cervixHardness" ), day->getCervixHardness() );
            data += getNodeInt( _T( "ovulationPain" ), day->getOvulationPain() );
            data += getNodeInt( _T( "breastsTension" ), day->getBreastsTension() );
            data += getNodeInt( _T( "spotting" ), day->getSpotting() );
            data += getNode( _T( "additionalNotes" ), day->getAdditionalNotes() );
            data += _T( "</day>\n" );
        }
        data += _T( "   </daysList>\n" );
        data += _T( "  </card>\n" );
    }
    data += _T( " </cardsList>\n" );
    data += _T( "</nfp>\n" );

    if ( wxFileExists( fileName ) ) {
        wxString path;
        wxString m_name;
        wxString ext;
        wxString backupFile;

        wxFileName::SplitPath( fileName, &path, &m_name, &ext );

        //wxString path = m_util.findPath( fileName );

        if ( !path.IsEmpty() ) {
            if ( ! wxDirExists( path ) )
                wxFileName::Mkdir( path, 0755, wxPATH_MKDIR_FULL );

            path = path + wxFileName::GetPathSeparator() + _T( "backup" );
            backupFile = path + wxFileName::GetPathSeparator() + m_name;

            if ( ! wxDirExists( path ) )
                wxFileName::Mkdir( path, 0755, wxPATH_MKDIR_FULL );

            backupFile = backupFile + _T( "_" ) + wxDateTime::Now().Format( _T( "%Y%m%d%H%M" ) ) + _T( "." ) + ext;

            wxCopyFile( fileName, backupFile );

            // remove older backup files
            wxSortedArrayString backupFilesArr;
            wxDir::GetAllFiles( path, &backupFilesArr, m_name + _T("_*"), wxDIR_FILES );
            if (backupFilesArr.GetCount() > 15)
                for ( size_t i = 0; i < backupFilesArr.GetCount()-15; i++ )
                    wxRemoveFile( backupFilesArr[i] );
        }
    }

    // save data to file
    if ( file.Open( fileName, _T( "w" ) ) ) {

        file.Write( data );
        file.Close();
    } else {
        addErrorMessages( wxString::Format( _( "Cannot open file: %s" ), fileName.c_str() ) );
        return false;
    }

    return true;
}

/******************************************************************************/

/**
 *
 */
wxString cycleDataClass::getNode( wxString m_name, wxString value )
{
    if ( value.IsEmpty() ) {
        return wxEmptyString;
    } else {
        return _T( "<" ) + m_name + _T( ">" ) + value + _T( "</" ) + m_name + _T( ">" );
    }
}

/**
 *
 */
wxString cycleDataClass::getNodeInt( wxString m_name, int value )
{
    if ( value == -1 ) {
        return wxEmptyString;
    } else {
        return getNode( m_name, m_util.intToStr( value ) );
    }
}

/**
 *
 */
wxString cycleDataClass::getNodeDateTime( wxString m_name, wxDateTime value, wxString dateOrTime )
{
    if ( value == m_util.getZeroDateTime() ) {
        return wxEmptyString;
    } else if ( dateOrTime == _T( "d" ) ) {
        return getNode( m_name, value.Format( _T( "%Y-%m-%d" ) ) );
    } else if ( dateOrTime == _T( "t" ) ) {
        return getNode( m_name, value.Format( _T( "%H:%M" ) ) );
    } else {
        //ShowMessage("getNode: unknown 'dateOrTime' parameter value: " + what);
        return wxEmptyString;
    }
}

/**
 *
 */
wxString cycleDataClass::getNodeBool( wxString m_name, bool value )
{
    if ( value ) {
        return getNode( m_name, _T( "x" ) );
    } else {
        return wxEmptyString;
    }
}

/**
 *
 */
wxString cycleDataClass::getNodeHash( wxString m_name, intArray array )
{
    if ( array.IsEmpty() )
        return wxEmptyString;

    wxString ret = wxEmptyString;
    for (size_t i=0; i<array.GetCount(); i++) {
        if (i>0) ret << _T(",");
        ret << array[i];
    }
    return getNode( m_name, ret );
}


/*******************************************************************************
***** MOVING DAYS BETWEEN 2 LAST CARDS *****************************************
*******************************************************************************/

/**
 * Move days from 1 to 'lastDay' from current card to the previous one.
 * If at least one day left on the current card, then update the 'firstDayOfCycle' field of the current card.
 * If none days left on the current card, then remove this card.
 * Finally update m_activeCard and m_activeDay variables, when needed.
 *
 */
bool cycleDataClass::moveDaysToPreviousCard( int lastDay )
{



    cardEntry * prevCard    = getCard( m_activeCard - 1 );
    cardEntry * currentCard = getCard( m_activeCard );

    for ( int i = 1; i <= lastDay; i++ ) {
        prevCard->addNewDay( currentCard->getDay( i ) );
    }

    if ( lastDay < currentCard->getDaysCount() ) {
        // remove from the last card days moved to the previous card and re-create the last card
        cardEntry * newCard     = new cardEntry( currentCard );
        newCard->setFirstDayOfCycle( prevCard->getFirstDayOfCycle() + wxDateSpan::Days( prevCard->getDaysCount() ) );

        for ( int i = lastDay + 1; i <= currentCard->getDaysCount(); i++ ) {
            newCard->addNewDay( currentCard->getDay( i ) );
        }

        removeLastCard();

        m_cards[m_activeCard] = newCard;
        m_activeCard--;
        m_activeDay = prevCard->getDaysCount() - lastDay + 1;
    } else {
        // no days left on the last card - remove it
        removeLastCard();
        m_activeCard--;
        m_activeDay = prevCard->getDaysCount() - lastDay + 1;
        prevCard->setCardLocked( false );
    }

    return true;
}

/**
 * Move days from 'firstDay' to last day of the card from current card to the next one.
 * If next card doesn't exist, then creat it first.
 * Finally update the 'firstDayOfCycle' field of the next card
 * and m_activeCard and m_activeDay variables, when needed.
 */
bool cycleDataClass::moveDaysToNextCard( int firstDay )
{



    cardEntry * currentCard = getCard( m_activeCard );
    cardEntry * newCard;
    cardEntry * nextCard;

    // check if we move days to already existing card or if we create new one

    if ( getCardsCount() == m_activeCard ) {
        // new card will be created

        nextCard = NULL;
        newCard  = new cardEntry( currentCard );
    } else {
        // days will be moved to already existing card

        nextCard = getCard( m_activeCard + 1 );
        newCard  = new cardEntry( nextCard );
    }

    int c = currentCard->getDaysCount();

    // move days from current card to next one

    for ( int i = firstDay; i <= c; i++ ) {

        newCard->addNewDay( currentCard->getDay( i ) );
    }

    // remove from current card days which have been moved to the next one
    for ( int i = firstDay; i <= c; i++ ) {

        currentCard->removeLastDay();
    }

    if ( getCardsCount() != m_activeCard ) {
        // copy days from 'existing next card' to the 'new next card'
        for ( int i = 1; i <= nextCard->getDaysCount(); i++ ) {

            newCard->addNewDay( nextCard->getDay( i ) );
        }

        removeLastCard();
    }


    newCard->setFirstDayOfCycle( currentCard->getFirstDayOfCycle() + wxDateSpan::Days( currentCard->getDaysCount() ) );

    m_cards[getCardsCount()+1] = newCard;

    m_activeCard = getCardsCount();
    m_activeDay = 1;

    // lock the current card
    currentCard->setCardLocked( true );

    return true;
}


/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * calculate corrected value of the temperature based on m_activeCard and new day data (day data has been changed)
 */
int cycleDataClass::calculateCorrectTemperatureValue( int value, wxDateTime time, int place, int addCorr )
{
    return calculateCorrectTemperatureValue( m_activeCard, m_activeDay, true, value, time, place, addCorr );
}

/**
 * calculate corrected value of the temperature based on m_activeCard and m_activeDay
 */
int cycleDataClass::calculateCorrectTemperatureValue()
{
    return calculateCorrectTemperatureValue( m_activeCard, m_activeDay );
}

/**
 * calculate corrected value of the temperature based on m_activeCard and dayNo
 */
int cycleDataClass::calculateCorrectTemperatureValue( int dayNo )
{
    return calculateCorrectTemperatureValue( m_activeCard, dayNo );
}

/**
 * calculate corrected value of the temperature based on cardNo and dayNo
 */
int cycleDataClass::calculateCorrectTemperatureValue( int cardNo, int dayNo )
{
    return calculateCorrectTemperatureValue( cardNo, dayNo, false, -1, wxDateTime( 0, 00, 0, 0 ), -1, -1 );
}

/**
 * Calculate corrected value of the temperature based on cardNo and dayNo.
 * If 'newDayData' == true then use new data for day variables provided in patameters.
 */
int cycleDataClass::calculateCorrectTemperatureValue( int cardNo, int dayNo, bool newDayData, int value, wxDateTime time, int place, int addCorr )
{
    if ( cardNo < 1 || dayNo < 1 || dayNo > getDaysCount( cardNo ))
        return -1;

    cardEntry *card = getCard( cardNo );

    dayEntry * day = getDay( cardNo, dayNo );

    if ( card == NULL ) {

        return -1;
    }

    if ( day == NULL ) {

        return -1;
    }

    int measuredValue = day->getTemperatureMeasuredValue();

    if ( measuredValue <= 0 && !newDayData ) {

        return -1;
    }

    wxString measurementTime = day->getTemperatureMeasurementTime().Format( _T( "%H:%M" ) );

    int measurementPlace = day->getTemperatureMeasurementPlace();
    int corectionAdditional = day->getTemperatureAdditionalCorrection();

    if ( newDayData ) {
        // new data for day
        measuredValue = value;

        if ( measuredValue <= 0 ) {

            return -1;
        }

        measurementTime = time.Format( _T( "%H:%M" ) );

        measurementPlace = place;
        corectionAdditional = addCorr;
    }

    wxString cardMeasurementTime = card->getTemperatureUsualMeasurementTime().Format( _T( "%H:%M" ) );

    int cardMeasurementPlace = card->getTemperatureUsualMeasurementPlace();
    int cardCorrectionMouth  = card->getTemperatureCorrectionWhenMeasuredInMouth();
    int cardCorrectionVagina = card->getTemperatureCorrectionWhenMeasuredInVagina();
    int cardCorrectionRectum = card->getTemperatureCorrectionWhenMeasuredInRectum();
    int cardCorrectionTime   = card->getTemperatureCorrectionForMeasurementTimeSake();

    int corectionPlace = 0;
    int corectionTime = 0;
    int dayTemp = 0;

    if ( measurementPlace > 0 && measurementPlace != cardMeasurementPlace ) {
        if ( measurementPlace == PLACE_MOUTH )
            corectionPlace = cardCorrectionMouth;
        else if ( measurementPlace == PLACE_VAGINA )
            corectionPlace = cardCorrectionVagina;
        else if ( measurementPlace == PLACE_RECTUM )
            corectionPlace = cardCorrectionRectum;
    }

    if ( !measurementTime.IsSameAs( _T( "00:00" ) ) && !measurementTime.IsSameAs( cardMeasurementTime ) ) {
        corectionTime = ( m_util.strToInt( measurementTime.Mid( 0, 2 ) ) - m_util.strToInt( cardMeasurementTime.Mid( 0, 2 ) ) ) * 60;
        corectionTime += m_util.strToInt( measurementTime.Mid( 3, 2 ) ) - m_util.strToInt( cardMeasurementTime.Mid( 3, 2 ) );
        corectionTime = corectionTime * cardCorrectionTime / 60;
    }

    dayTemp = measuredValue + corectionPlace + corectionTime + corectionAdditional;

    int tmp = dayTemp % 5;

    if ( tmp < 3 )
        dayTemp -= tmp;
    else
        dayTemp += 5 - tmp;


    return dayTemp;
}





/*

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

int cycleDataClass::find_poziom_nizszy_temperatur(int cardNr) {
   try {
      int ret = -1;
      if (cardNr < 0 || cardNr >= cardsCount) return ret;
      if (cardsTab == NULL || cardsTab[cardNr] == NULL) return ret;

      for (int i=0; i<get_dlugosc_cyklu(cardNr); i++) {
         if (get_wynik_typ_temperatury(cardNr, i) == temp_przedwzrostowa) {
            int c = get_zmierzona_temperatura(cardNr, i, true);
            if (ret < c) ret = c;
         }
      }
      return ret;
   } catch(Exception &E) {
      return -1;
   }
}

//---------------------------------------------------------------------------
int cycleDataClass::find_first_temperature(int cardNr) {
   try {
      int ret = -1;
      if (cardNr < 0 || cardNr >= cardsCount) return ret;
      if (cardsTab == NULL || cardsTab[cardNr] == NULL) return ret;

      for (int i=0; i<get_dlugosc_cyklu(cardNr); i++) {
         if (get_wynik_typ_temperatury(cardNr, i) == temp_przedwzrostowa) {
            return i;
         }
      }
      return -1;
   } catch(Exception &E) {
      return -1;
   }
}

//---------------------------------------------------------------------------
int cycleDataClass::find_first_hight_temperature(int cardNr) {
   try {
      int ret = -1;
      if (cardNr < 0 || cardNr >= cardsCount) return ret;
      if (cardsTab == NULL || cardsTab[cardNr] == NULL) return ret;

      for (int i=0; i<get_dlugosc_cyklu(cardNr); i++) {
         if (get_wynik_typ_temperatury(cardNr, i) == temp_powzrostowa) {
            return i;
         }
      }
      return -1;
   } catch(Exception &E) {
      return -1;
   }
}

//---------------------------------------------------------------------------
int cycleDataClass::find_last_temperature(int cardNr) {
   try {
      int ret = -1;
      if (cardNr < 0 || cardNr >= cardsCount) return ret;
      if (cardsTab == NULL || cardsTab[cardNr] == NULL) return ret;

      for (int i=get_dlugosc_cyklu(cardNr)-1; i>=0; i--) {
         if (get_wynik_typ_temperatury(cardNr, i) == temp_powzrostowa) {
            return i;
         }
      }
      return -1;
   } catch(Exception &E) {
      return -1;
   }
}

*/


/*******************************************************************************
********************************************************************************
*******************************************************************************/
