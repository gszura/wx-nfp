/*******************************************************************************
//
// Name:        utilClass.h
// Author:      Grzegorz Szura
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
class utilClass
{
public:
    int strToInt (wxString);
    wxString intToStr (int);
    long strToLong (wxString);
    wxString longToStr (long);
    bool strToBool (wxString);
    wxString boolToStr (bool);

    wxDateTime getZeroDateTime();

    wxString temperatureToStr (int temp, bool correction = true, bool returnZero = false);
    int strToTemperature (wxString);

private:
    wxStandardPaths m_standardPaths;

public:
    //wxString getAllPathsPath();

    wxString getConfigPath();
    wxString getCardSetDataPath();
    wxString getAvailableLanguagesConfigFilePath();
    wxString getLocalePath();
    wxString getTempFolderPath();
    //wxString getHelpFilePath(wxString);
    wxString getHelpUrl(wxString);

    wxArrayString prepareTemperaturesArray (int, int, int);
    int celsiusToFahrenheit (int);
    int fahrenheitCelsiusTo (int);

    int getNumberOfDays (wxDateTime, wxDateTime);

    wxString hashString(wxString);
    wxString unhashString(wxString);
    wxString generateFancyFileName(wxString, wxString);
    void backupFile(wxString);
};

#endif
