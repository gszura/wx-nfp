/*******************************************************************************
//
// Name:        dayEntry.h
// Author:      enkeli
// Description:
//
*******************************************************************************/


#ifndef __DAY_ENTRY__
#define __DAY_ENTRY__

#include <wx/wx.h>
#include <wx/datetime.h>
#include "cyclesData_declarations.h"


/*******************************************************************************
********************************************************************************
*******************************************************************************/

class dayEntry {

// VARIABLES
private:
     int m_menstruation;                      // [-1 | 1-2]
     int m_coitusRecord;                      // [-1 | 1..]
     bool m_otherDisturbances;                // [x]

     bool m_temperatureDisturbances;          // [x]
     int m_temperatureMeasuredValue;          // [dddd]  eg. 3655 == 36.55 st. C
     wxDateTime m_temperatureMeasurementTime; // [hh:mm]  eg. 08:00
     int m_temperatureMeasurementPlace;       // [-1, 1-3]
     int m_temperatureAdditionalCorrection;   // [(-)dd]  eg. -10 == -0.10 st. C
     int m_temperatureValueAfterCorrections;  // [dddd]  eg. 3655 == 36.55 st. C

     int m_mucusFeelingExperience;            // [-1 | 1-4]
     int m_mucusAppearance;                   // [-1 | 1-8191]

     int m_cervixPosition;                    // [-1 | 1-5]
     int m_cervixDilation;                    // [-1 | 1-3]
     int m_cervixHardness;                    // [-1 | 1-3]

     int m_ovulationPain;                     // [-1 | 1-2]
     int m_breastsTension;                    // [-1 | 1-2]
     int m_spotting;                          // [-1 | 1-2]
     wxString m_additionalNotes;              // [<string>]

// METHODS
public:
     // CONSTRUCTORS
     dayEntry();

     // STORING THE DATA
     bool setMenstruation(int);
     bool setCoitusRecord(int);
     bool setOtherDisturbances(bool);
     bool setTemperatureDisturbances(bool);
     bool setTemperatureMeasuredValue(int);
     bool setTemperatureMeasurementTime(wxDateTime);
     bool setTemperatureMeasurementPlace(int);
     bool setTemperatureAdditionalCorrection(int);
     bool setTemperatureValueAfterCorrections(int);
     bool setMucusFeelingExperience(int);
     bool setMucusAppearance(int);
     bool setCervixPosition(int);
     bool setCervixDilation(int);
     bool setCervixHardness(int);
     bool setOvulationPain(int);
     bool setBreastsTension(int);
     bool setSpotting(int);
     bool setAdditionalNotes(wxString);

     // READING THE DATA
     int getMenstruation();
     int getCoitusRecord();
     bool getOtherDisturbances();
     bool getTemperatureDisturbances();
     int getTemperatureMeasuredValue();
     wxDateTime getTemperatureMeasurementTime();
     int getTemperatureMeasurementPlace();
     int getTemperatureAdditionalCorrection();
     int getTemperatureValueAfterCorrections();
     int getMucusFeelingExperience();
     int getMucusAppearance();
     wxString convertMucusAppearance( int );
     int getCervixPosition();
     int getCervixDilation();
     int getCervixHardness();
     int getOvulationPain();
     int getBreastsTension();
     int getSpotting();
     wxString getAdditionalNotes();

};

/*******************************************************************************
********************************************************************************
*******************************************************************************/

WX_DECLARE_HASH_MAP( int, dayEntry*, wxIntegerHash, wxIntegerEqual, dayEntryHash );

/*******************************************************************************
********************************************************************************
*******************************************************************************/

#endif


