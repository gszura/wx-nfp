/*******************************************************************************
//
// Name:        utilClass.h
// Author:      enkeli
// Description:
//
*******************************************************************************/

#ifndef __UTIL_CLASS__
#define __UTIL_CLASS__

//#include "wx_pch.h"
#include <wx/datetime.h>
#include <wx/stdpaths.h>

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
class utilClass {
public:
     utilClass();

     int strToInt (wxString);
     wxString intToStr (int);

     bool strToBool (wxString);
     wxString boolToStr (bool);

     wxDateTime getZeroDateTime();

     wxString temperatureToStr (int, bool);
     wxString temperatureToStr (int, bool, bool);
     int strToTemperature (wxString);

private:
     wxStandardPaths m_standardPaths;

public:
     //wxString getAllPathsPath();

     wxString getConfigPath();
     wxString getCardSetDataPath();
     wxString getAvailableLanguagesConfigFilePath();
     wxString getLocalePath();
     //wxString getHelpFilePath(wxString);
     wxString getHelpUrl(wxString);

     wxArrayString prepareTemperaturesArray (int, int, int);
     int celsiusToFahrenheit (int);
     int fahrenheitCelsiusTo (int);
};

#endif
