/*******************************************************************************
//
// Name:        utilClass.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "utilClass.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/log.h>

#define HASH _T("Ala kota chciała ale kot powiedział Ali, że Ala może się wypchać")

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
int utilClass::strToInt( wxString input )
{
    int ret = -1;
    long l;

    if ( input.ToLong( &l ) ) {
        ret = l;
    }
    return ret;
}

/**
 *
 */
wxString utilClass::intToStr( int input )
{
    wxString ret = wxEmptyString;
    ret << input;
    return ret;
}

/**
 *
 */
long utilClass::strToLong( wxString input )
{
    long ret;

    if ( input.ToLong( &ret ) ) {
        return ret;
    } else {
        return -1;
    }
}

/**
 *
 */
wxString utilClass::longToStr( long input )
{
    wxString ret = wxEmptyString;
    ret << input;
    return ret;
}

/**
 *
 */
bool utilClass::strToBool( wxString input )
{
    if ( input.IsSameAs( _T( "true" ), false ) ) {
        return true;
    } else {
        return false;
    }
}

/**
 *
 */
wxString utilClass::boolToStr( bool input )
{

    if ( input ) {
        return ( wxString ) _T( "true" );
    } else {
        return ( wxString ) _T( "false" );
    }
}

/**
 *
 */
wxDateTime utilClass::getZeroDateTime()
{
    wxDateTime ret = wxDateTime();
    ret.Set( 0, 0, 0, 0 );
    ret.SetYear( 1901 );
    ret.SetMonth( wxDateTime::Month( 0 ) );
    ret.SetDay( 1 );
    return ret;
}

/**
 * Convert temperature stored in int to string.
 *
 * Parameters:
 * temp - tempetarute to convert
 * correction - if true, then add '+'/'-' sign to the output string
 * returnZero - if true, then return '0', when value of the parameter 'temp' == [-1 | 0]; if false, then return empty string.
 *
 * examples:
 * 10 -> '0,1'
 * -125 -> '-1,25' (if correction == true)
 *      -> '1,25'  (if correction == false)
 * 0    -> ''      (if returnZero == false)
 *      -> '0'     (if returnZero == true)
 */
wxString utilClass::temperatureToStr( int temp, bool correction, bool returnZero )
{
    wxString ret = _T( "" );
    int t = temp;

    if ( temp != -1 && temp != 0 ) {
        if ( correction ) {
            if ( t < 0 ) {
                ret << _T( "-" );
                t -= t * 2;
            } else {
                ret << _T( "+" );
            }
        }
        int t1 = t / 100;
        int t2 = t % 100;
        ret << t1 << _T( "," );

        if ( t2 > 0 && t2 < 10 ) {
            ret << _T( "0" );
        } else if ( t2 % 10 == 0 ) {
            t2 = t2 / 10;
        }
        ret << t2;
    }

    if ( returnZero && ret.IsEmpty() ) {
        ret = _T( "0" );
    }

    return ret;
}

/**
 * Convert temperature stored in string to int.
 * return -1, if 'temp' is an empty string.
 *
 * Parameters:
 * temp - tempetarute to convert (eg. '0,1' == 10; '-1,25' = -125; '+37,10' == 3710)
 */
int utilClass::strToTemperature( wxString temp )
{
    int negative = 1;

    if ( temp.IsEmpty() ) {
        return -1;
    }

    if ( temp.StartsWith( _T( "-" ) ) ) {
        negative = -1;
        temp = temp.Mid( 1 );
    } else if ( temp.StartsWith( _T( "+" ) ) ) {
        temp = temp.Mid( 1 );
    }

    wxString temp1 = _T( "" );
    wxString temp2 = _T( "" );

    int i = temp.Find( _T( "," ) );
    if ( i == -1 )
        i = temp.Find( _T( "." ) );

    if ( i > -1 ) {
        temp1 = temp.Mid( 0, i );
        temp2 = temp.Mid( i + 1 );
    } else {
        temp1 = temp;
        temp2 = _T( "00" );
    }

    if ( temp2.Length() == 0 )
        temp2 = _T( "00" );
    else if ( temp2.Length() == 1 )
        temp2 = temp2 + _T( "0" );
    else if ( temp2.Length() > 2 )
        temp2 = temp2.Mid( 0, 2 );

    return negative * strToInt( temp1 + temp2 );

}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 * Temporaty function for testing purpose only.
 */
/*
wxString utilClass::getAllPathsPath() {
    wxString ret;
    ret << _T("GetUserDataDir() = '") << m_standardPaths.GetUserDataDir() << _T("'\n");
    ret << _T("GetDataDir() = '") << m_standardPaths.GetDataDir() << _T("'\n");
    ret << _T("GetDocumentsDir() = '") << m_standardPaths.GetDocumentsDir() << _T("'\n");
    //ret << _T("GetLocalizedResourcesDir(pl) = '") << m_standardPaths.GetLocalizedResourcesDir(_T("pl"), ResourceCat_None) << _T("'\n");
    ret << _T("'\n");
#if defined(__UNIX__)
    ret << _T("GetInstallPrefix() = '") << m_standardPaths.GetInstallPrefix() << _T("'\n");
#endif
    ret << _T("'\n");
    ret << _T("'\n");
    ret << _T("'\n");
    ret << _T("this.getConfigPath() = '") << getConfigPath() << _T("'\n");
    ret << _T("this.getCardSetDataPath() = '") << getCardSetDataPath() << _T("'\n");
    ret << _T("this.getAvailableLanguagesConfigFilePath() = '") << getAvailableLanguagesConfigFilePath() << _T("'\n");
    ret << _T("this.getLocalePath() = '") << getLocalePath() << _T("'\n");
    //ret << _T("this.getHelpFilePath(pl) = '") << getHelpFilePath( _T("pl")) << _T("'\n");
    ret << _T("this.getHelpUrl(pl) = '") << getHelpUrl( _T("pl")) << _T("'\n");
    ret << _T("'\n");
    ret << _T("'\n");
    ret << _T("'\n");
    ret << _T("GetExecutablePath() = '") << m_standardPaths.GetExecutablePath() << _T("'\n");
    ret << _T("GetDataDir() = '") << m_standardPaths.GetDataDir() << _T("'\n");
    ret << _T("GetLocalDataDir() = '") << m_standardPaths.GetLocalDataDir() << _T("'\n");
    ret << _T("GetUserDataDir() = '") << m_standardPaths.GetUserDataDir() << _T("'\n");
    ret << _T("GetUserLocalDataDir() = '") << m_standardPaths.GetUserLocalDataDir() << _T("'\n");
    ret << _T("'\n");
    ret << _T("GetConfigDir() = '") << m_standardPaths.GetConfigDir() << _T("'\n");
    ret << _T("GetUserConfigDir() = '") << m_standardPaths.GetUserConfigDir() << _T("'\n");
    ret << _T("GetResourcesDir() = '") << m_standardPaths.GetResourcesDir() << _T("'\n");
    //ret << _T("GetLocalizedResourcesDir(pl) = '") << m_standardPaths.GetLocalizedResourcesDir(_T("pl"), ResourceCat_None) << _T("'\n");
    ret << _T("'\n");
    ret << _T("GetDocumentsDir() = '") << m_standardPaths.GetDocumentsDir() << _T("'\n");
    ret << _T("GetTempDir() = '") << m_standardPaths.GetTempDir() << _T("'\n");
    return ret;
}
*/

/**
 * Return the path to the folder where config file is stored.
 * This method doesn't check if the folder exists, just return the path.
 */
wxString utilClass::getConfigPath()
{
    /* Linux: ~/wx-nfp/ */
    /* M$ Win: c:\Documents and Settings\<user>\Dane aplikacji\wx-nfp\ */
    return m_standardPaths.GetUserDataDir() + wxFileName::GetPathSeparator();
}

/**
 * Return the path to the folder where cards' set file is stored by default.
 * This method doesn't check if the folder exists, just return the path.
 */
wxString utilClass::getCardSetDataPath()
{
    // old location //
    /* Linux: ~/.wx-nfp/data/ */
    /* M$ Win: c:\Documents and Settings\<user>\Dane aplikacji\wx-nfp\data\ */
    //return m_standardPaths.GetUserDataDir() + wxFileName::GetPathSeparator() + _T( "data" ) + wxFileName::GetPathSeparator();

    /* Linux: ~ (the home directory) */
    /* M$ Win: C:\Documents and Settings\username\Documents */
    return m_standardPaths.GetDocumentsDir() + wxFileName::GetPathSeparator() + _T( "wx-nfp" ) + wxFileName::GetPathSeparator();
}

/**
 * Return the path to the to the configuration file with list of available languages.
 */
wxString utilClass::getAvailableLanguagesConfigFilePath()
{
    /* Linux: <InstallPrefix>/share/wx-nfp/language.cfg */
    /* M$ Win: <installation path>\language.cfg */
    return m_standardPaths.GetDataDir() + wxFileName::GetPathSeparator() + _T( "languages.cfg" );
}

/**
 *
 */
wxString utilClass::getLocalePath()
{
#if defined(__UNIX__)
    /* Linux: <InstallPrefix>/share/locale/
       return wxEmptyString - system should find the locale file itself.. */
    return wxEmptyString;
#else
    /* M$ Win: <installation path>\language\ */
    return m_standardPaths.GetDataDir() + wxFileName::GetPathSeparator() + _T( "po" ) + wxFileName::GetPathSeparator();
#endif
}

/**
 *
 */
wxString utilClass::getTempFolderPath()
{
    return m_standardPaths.GetTempDir() + wxFileName::GetPathSeparator();
}

/**
 * Return the path to the help file for specific language (../<lang>/wx-nfp_doc.zip).
 * This method doesn't check if the file exists, just return the path.
 */
/*
wxString utilClass::getHelpFilePath( wxString lang ) {
    // TODO - this path can be different on other Linux distributions!!
    // Linux: <InstallPrefix>/share/wx-nfp/help/<lang>/wx-nfp_doc.zip
    // M$ Win: <installation path>\help\<lang>/wx-nfp_doc.zip
    return m_standardPaths.GetDataDir() + wxFileName::GetPathSeparator() + _T( "help" ) + wxFileName::GetPathSeparator() + lang + wxFileName::GetPathSeparator() + _T( "wx-nfp_doc.zip" );
}
*/

/**
 * Return the URI to the index.html help file for specific language.
 * If file does not exist, just return wxEmptyString (== no local help).
 */
wxString utilClass::getHelpUrl( wxString lang )
{
#if defined(__UNIX__)
    /* Linux: this path can be different on other Linux distributions
       so we try to find the 'index.html' file in following locations:
         <InstallPrefix>/share/doc/wx-nfp/html/<lang>/index.html
         /usr/local/share/doc/wx-nfp/html/<lang>/index.html
         /usr/share/doc/wx-nfp/html/<lang>/index.html
       In case of failure return wxEmptyString (== no local help).
       */
    wxString helpFile = m_standardPaths.GetInstallPrefix() + _T( "/share/doc/wx-nfp/html/" ) + lang + _T( "/index.html" );
    if ( wxFileExists(helpFile) ) {
        return _T( "file:///" ) + helpFile;
    } else {
        helpFile = _T( "/usr/local/share/doc/wx-nfp/html/" ) + lang + _T( "/index.html" );
        if ( wxFileExists(helpFile) ) {
            return _T( "file:///" ) + helpFile;
        } else {
            helpFile = _T( "/usr/share/doc/wx-nfp/html/" ) + lang + _T( "/index.html" );
            if ( wxFileExists(helpFile) ) {
                return _T( "file:///" ) + helpFile;
            } else {
                return wxEmptyString;
            }
        }
    }
#else
    /* M$ Win: Most probable location: <installation path>\help\<lang>\index.html */
    wxString helpFile = m_standardPaths.GetDataDir() + _T( "\\doc\\html\\" )+ lang + _T( "\\index.html" );
    if ( wxFileExists(helpFile) ) {
        return _T( "file:///" ) + helpFile;
    } else {
        return wxEmptyString;
    }
#endif
}

/******************************************************************************/

/**
 * first, last, step - values in (temperature * 10)
 * eg. 3600 == 36,0 ; 54 == 0,54
 */
wxArrayString utilClass::prepareTemperaturesArray( int first, int last, int step )
{
    wxArrayString ret;

    for ( int t = last; t >= first; t -= step ) {
        ret.Add( temperatureToStr( t, false ) );
    }
    return ret;
}

/**
 * first, last, step - values in (Celsius * 10)
 * eg. 3600 == 36,0 C ; 54 == 0,54 C
 */
int utilClass::celsiusToFahrenheit( int in )
{
    float tC = ( float ) in / ( float ) 100;
    float tF = tC * ( float )( 9 / 5 ) + ( float ) 32;
    return ( int )( tF*100 );
}

/**
 * first, last, step - values in (Celsius * 10)
 * eg. 3600 == 36,0 C ; 54 == 0,54 C
 */
int utilClass::fahrenheitCelsiusTo( int in )
{
    float tF = ( float ) in / ( float ) 100;
    float tC = ( float )( 5 / 9 ) * ( tF - ( float ) 32 );
    return ( int )( tC*100 );
}

/******************************************************************************/

/**
 * get number of days between dateTime1 and dateTime2 (== dateTime2 - dateTime1)
 */
int utilClass::getNumberOfDays( wxDateTime dateTime1, wxDateTime dateTime2 )
{
    int year1  = dateTime1.GetYear();
    int month1 = dateTime1.GetMonth();
    int day1   = dateTime1.GetDay();
    int year2  = dateTime2.GetYear();
    int month2 = dateTime2.GetMonth();
    int day2   = dateTime2.GetDay();
    int daysNumber = 0;

    if ( year1 > year2 ) {

        return -1;
    }
    if ( year1 == year2 && month1 > month2 ) {

        return -1;
    }
    if ( year1 == year2 && month1 == month2 && day1 > day2 ) {

        return -1;
    }

    if ( year1 < year2 ) {
        daysNumber += wxDateTime::GetNumberOfDays(( wxDateTime::Month )( month1 ), year1, ( wxDateTime::Calendar )( 0 ) ) - day1;

        for ( int m = month1 + 1; m < 12; m++ ) {
            daysNumber += wxDateTime::GetNumberOfDays(( wxDateTime::Month )( m ), year1, ( wxDateTime::Calendar )( 0 ) );

        }
        for ( int y = year1 + 1; y < year2; y++ ) {
            for ( int m = 0; m < 12; m++ ) {
                daysNumber += wxDateTime::GetNumberOfDays(( wxDateTime::Month )( m ), y, ( wxDateTime::Calendar )( 0 ) );

            }
        }
        for ( int m = 0; m < month2; m++ ) {
            daysNumber += wxDateTime::GetNumberOfDays(( wxDateTime::Month )( m ), year2, ( wxDateTime::Calendar )( 0 ) );

        }
        daysNumber += day2;

    } else if ( month1 < month2 ) {
        daysNumber += wxDateTime::GetNumberOfDays(( wxDateTime::Month )( month1 ), year2, ( wxDateTime::Calendar )( 0 ) ) - day1;

        for ( int m = month1 + 1; m < month2; m++ ) {
            daysNumber += wxDateTime::GetNumberOfDays(( wxDateTime::Month )( m ), year2, ( wxDateTime::Calendar )( 0 ) );

        }
        daysNumber += day2;

    } else {
        daysNumber += day2 - day1;

    }

    return daysNumber;
}

/******************************************************************************/
wxString utilClass::generateFancyFileName(wxString str1, wxString str2)
{
    wxString ret = wxEmptyString;
    int l = ( str1.Length() > str2.Length() ? str1.Length() : str2.Length());
    int i2 = l-1;
    for (int i1=0; i1<l; i1++) {
        int x1 = 0;
        int x2 = 0;
        for (int e=i1; e<l; e++)
            x1 += (int)str1.Length() > e ? (int)str1[e] : 1;
        for (int e=i2; e<l; e++)
            x2 += (int)str2.Length() > e ? (int)str2[e] : 1;
        ret << (x1 * x2);
        i2--;
    }
    return ret;
}


wxString utilClass::hashString(wxString input)
{
    wxString ret = wxEmptyString;
    size_t c;
    for (size_t i=0; i<64; i++) {
        c = (input.Length() > i ? (int)input[i] : 0) + (int)HASH[i];
        if (c < 100)
            ret << _T("0");
        if (c < 10)
            ret << _T("0");
        ret << c;
    }
    return ret;
}

wxString utilClass::unhashString(wxString input)
{
    wxString ret = wxEmptyString;
    wxChar c;
    for (int i=0; i<64; i++) {
        int x = strToInt( input.Mid(i*3, 3) ) - (int)HASH[i];
        if (x > 0) {
            c = x;
            ret.Append(c);
        }
    }
    return ret;
}

/******************************************************************************/

/**
 * Make a backup of the file, but only one per minute,
 * i.e. if the file '<fileName>_YYYYmmddHH.<ext>' already exists in the 'backup' folder then new backup is not created.
 */
void utilClass::backupFile(wxString fileName)
{
    wxLogDebug( wxString::Format( _T("[utilClass] making backup of file: '%s'"), fileName.c_str()) );
    if ( wxFileExists( fileName ) ) {
        wxString path = wxEmptyString;
        wxString name = wxEmptyString;
        wxString ext = wxEmptyString;
        wxString backupFile = wxEmptyString;

        wxLogDebug( wxString::Format( _T("[utilClass] file exists: '%s'"), fileName.c_str()) );

        wxFileName::SplitPath( fileName, &path, &name, &ext );

        wxLogDebug( wxString::Format( _T("[utilClass] file path: '%s'"), path.c_str()) );

        if ( !path.IsEmpty() ) {
            path << wxFileName::GetPathSeparator() << _T( "backup" );
            wxLogDebug( wxString::Format( _T("[utilClass] path: '%s'"), path.c_str()) );

            if ( ! wxDirExists( path ) ) {
                wxLogDebug( wxString::Format( _T("[utilClass] mkdir: '%s'"), path.c_str()) );
                wxFileName::Mkdir( path, 0755, wxPATH_MKDIR_FULL );
            }

            backupFile << path << wxFileName::GetPathSeparator() << name << wxDateTime::Now().Format( _T( "_%Y%m%d%H%M." ) ) << ext;
            wxLogDebug( wxString::Format( _T("[utilClass] backupFile: '%s'"), backupFile.c_str()) );

            if ( !wxFileExists( backupFile ) ) {
                wxLogDebug( wxString::Format( _T("[utilClass] copy: %s -> %s"), fileName.c_str(), backupFile.c_str()) );
                wxCopyFile( fileName, backupFile );
            } else {
                wxLogDebug( _T("[utilClass] backupFile with this name already exists (we can do one backup per minute)'") );
            }

            // remove older backup files
            wxSortedArrayString backupFilesArr;
            wxDir::GetAllFiles( path, &backupFilesArr, name + _T("_*"), wxDIR_FILES );
            if (backupFilesArr.GetCount() > 30)
                for ( size_t i = 0; i < backupFilesArr.GetCount()-15; i++ ) {
                    wxLogDebug( wxString::Format( _T("[utilClass] remove old backup: '%s'"), backupFilesArr[i].c_str()) );
                    wxRemoveFile( backupFilesArr[i] );
                }
        } else {
            wxLogDebug( wxString::Format( _T("[utilClass] cannot extract path from the file path: '%s'"), fileName.c_str()) );
        }
    } else {
        wxLogDebug( wxString::Format( _T("[utilClass] given file doesn't exist: '%s'"), fileName.c_str()) );
    }

    wxLogDebug( _T("[utilClass] making backup done") );
}

/******************************************************************************/



/*******************************************************************************
********************************************************************************
*******************************************************************************/

