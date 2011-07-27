/*******************************************************************************
//
// Name:        utilClass.cpp
// Author:      enkeli
// Description:
//
*******************************************************************************/

#include "utilClass.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/**
 *
 */
utilClass::utilClass() {
//#if defined(__UNIX__)
//    m_standardPaths.SetInstallPrefix( _T("/usr") );
//#endif
}

/******************************************************************************/

/**
 *
 */
int utilClass::strToInt( wxString input ) {
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
wxString utilClass::intToStr( int input ) {
    wxString ret = wxEmptyString;
    ret << input;
    return ret;
}

/**
 *
 */
bool utilClass::strToBool( wxString input ) {
    if ( input.IsSameAs( _T( "true" ), false ) ) {
        return true;
    } else {
        return false;
    }
}

/**
 *
 */
wxString utilClass::boolToStr( bool input ) {

    if ( input ) {
        return ( wxString ) _T( "true" );
    } else {
        return ( wxString ) _T( "false" );
    }
}

/**
 *
 */
wxDateTime utilClass::getZeroDateTime() {
    wxDateTime ret = wxDateTime();
    ret.Set( 0, 0, 0, 0 );
    ret.SetYear( 1901 );
    ret.SetMonth( wxDateTime::Month( 0 ) );
    ret.SetDay( 1 );
    return ret;
}

/**
 * Convert temperature stored in int to string.
 * When value of the parameter 'temp' == [-1 | 0], then return empty string.
 *
 * Parameters:
 * temp - tempetarute to convert (eg. 10 == '0,1'; -125 ==  '-1,25' )
 * correction - if true, then add '+'/'-' sign to the output string
 */
wxString utilClass::temperatureToStr( int temp, bool correction ) {
    return temperatureToStr( temp, correction, false );
}

/**
 * Convert temperature stored in int to string.
 *
 * Parameters:
 * temp - tempetarute to convert (eg. 10 == '0,1'; -125 ==  '-1,25' )
 * correction - if true, then add '+'/'-' sign to the output string
 * returnZero - if true, then return '0', when value of the parameter 'temp' == [-1 | 0]; if false, then return empty string.
 */
wxString utilClass::temperatureToStr( int temp, bool correction, bool returnZero ) {
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
int utilClass::strToTemperature( wxString temp ) {
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
wxString utilClass::getConfigPath() {
    /* Linux: ~/wx-nfp/ */
    /* M$ Win: c:\Documents and Settings\<user>\Dane aplikacji\wx-nfp\ */
    return m_standardPaths.GetUserDataDir() + wxFileName::GetPathSeparator();
}

/**
 * Return the path to the folder where cards' set file is stored by default.
 * This method doesn't check if the folder exists, just return the path.
 */
wxString utilClass::getCardSetDataPath() {
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
wxString utilClass::getAvailableLanguagesConfigFilePath() {
    /* Linux: <InstallPrefix>/share/wx-nfp/language.cfg */
    /* M$ Win: <installation path>\language.cfg */
    return m_standardPaths.GetDataDir() + wxFileName::GetPathSeparator() + _T( "languages.cfg" );
}

/**
 *
 */
wxString utilClass::getLocalePath() {
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
wxString utilClass::getHelpUrl( wxString lang ) {
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
wxArrayString utilClass::prepareTemperaturesArray( int first, int last, int step ) {
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
int utilClass::celsiusToFahrenheit( int in ) {
    float tC = ( float ) in / ( float ) 100;
    float tF = tC * ( float )( 9 / 5 ) + ( float ) 32;
    return ( int )( tF*100 );
}

/**
 * first, last, step - values in (Celsius * 10)
 * eg. 3600 == 36,0 C ; 54 == 0,54 C
 */
int utilClass::fahrenheitCelsiusTo( int in ) {
    float tF = ( float ) in / ( float ) 100;
    float tC = ( float )( 5 / 9 ) * ( tF - ( float ) 32 );
    return ( int )( tC*100 );
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

