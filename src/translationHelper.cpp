#include "translationHelper.h"
#include <wx/dir.h>
#include <wx/fileconf.h>
#include <wx/filename.h>
#include "wx-nfpAppInfo.h"
#include <wx/fileconf.h>

/**
 *
 */
translationHelper::translationHelper( const wxString & availableLanguagesConfigFilePath, const wxString & searchPath ) :
    m_availableLanguagesConfigFilePath( availableLanguagesConfigFilePath ),
    m_searchPath ( searchPath ),
    m_locale( NULL ) {
    m_defaultLanguageId = wxLocale::GetLanguageInfo( wxLANGUAGE_DEFAULT )->Language;
}

/**
 *
 */
translationHelper::~translationHelper() {
    if ( m_locale )
        wxDELETE( m_locale );
}

/**
 *
 */
wxLocale * translationHelper::getLocale() {
    return m_locale;
}

/**
 *
 */
long translationHelper::load( long langId ) {
    wxArrayString names;
    wxArrayLong identifiers;
    getInstalledLanguages( names, identifiers );

    if ( identifiers.GetCount() < 2 )
        return wxLANGUAGE_DEFAULT;

    if ( langId < 0 ) {
        // The application has been run for the first time:

        // 1/ set the language on the basis of system language
        if ( identifiers[0] == m_defaultLanguageId ) {
            setApplicationLanguage( identifiers[0] );
        }

        // 2/ ... and ask user for preferred language
        long newLangId = askUserForLanguage( names, identifiers );
        if ( newLangId < 0 ) {
            return wxLANGUAGE_DEFAULT;
        } else {
            return newLangId;
        }
    } else {
        // The application has been run already - set language without asking user
        if ( langId != wxLANGUAGE_DEFAULT ) {
            for ( size_t i = 0; i < identifiers.GetCount(); i++ ) {
                if ( identifiers[i] == langId ) {
                    setApplicationLanguage( identifiers[i] );
                    return langId;
                }
            }
        }
    }

    setApplicationLanguage( langId );
    return langId;
}

/**
 *
 */
void translationHelper::getInstalledLanguages( wxArrayString & names, wxArrayLong & identifiers ) {
    names.Clear();
    identifiers.Clear();
    wxString lang, langDescription;
    const wxLanguageInfo * langInfo;
    wxString langFile1 = wxString::Format( _T( "%s.mo" ), ORIGINAL_APP_FILENAME);
    wxString langFile2 = wxString::Format(_T( "LC_MESSAGES/%s.mo"), ORIGINAL_APP_FILENAME);

    names.Add( _( "Built-in (English)" ) );
    identifiers.Add( 0 );

    if ( !wxFileExists( m_availableLanguagesConfigFilePath ) )
        return;

    wxConfigBase *config = new wxFileConfig( wxEmptyString, wxEmptyString, m_availableLanguagesConfigFilePath );
    long dummy;
    bool bCont = config->GetFirstEntry(lang, dummy);
    while ( bCont ) {
        config->Read( lang, &langDescription );
        langInfo = wxLocale::FindLanguageInfo( lang );
        if ( langInfo != NULL ) {
            if ( langInfo->Language == m_defaultLanguageId ) {
                names.Insert( langInfo->Description, 0 );
                identifiers.Insert( langInfo->Language, 0 );
            } else {
                names.Add( langInfo->Description );
                identifiers.Add( langInfo->Language );
            }
        }
        bCont = config->GetNextEntry(lang, dummy);
    }

    /*
    wxDir dir( m_searchPath );
    for ( bool cont = dir.GetFirst( &lang, wxEmptyString, wxDIR_DIRS ); cont; cont = dir.GetNext( &lang ) ) {
        langDir = m_searchPath + lang + wxFileName::GetPathSeparator();
        if ( wxFileExists( langDir + langFile1 ) || wxFileExists( langDir + langFile2 ) ) {
            langInfo = wxLocale::FindLanguageInfo( lang );
            if ( langInfo != NULL ) {
                if ( langInfo->Language == m_defaultLanguageId ) {
                    names.Insert( langInfo->Description, 0 );
                    identifiers.Insert( langInfo->Language, 0 );
                } else {
                    names.Add( langInfo->Description );
                    identifiers.Add( langInfo->Language );
                }
            }
        }
    }
    */
}

/**
 * return < 0 ==> user pressed cancel -> language has not been changed.
 */
long translationHelper::askUserForLanguage( wxArrayString & names, wxArrayLong & identifiers ) {
    wxCHECK_MSG( names.Count() == identifiers.Count(), false, _T( "Array of language names and identifiers should have the same size." ) );

    int index = wxGetSingleChoiceIndex( _( "Select the application language:" ), _( "Language.." ), names, NULL, -1, -1, true, 100, 100 );

    if ( index < 0 )
        index = 0;

    setApplicationLanguage( identifiers[index] );
    return identifiers[index];
}

/**
 *
 */
bool translationHelper::setApplicationLanguage( long langId ) {
    if ( m_locale )
        wxDELETE( m_locale );

    if (langId > 0) {
        if (! wxLocale::IsAvailable(langId)) {
            wxMessageBox( _( "The selected language is not supported by your system.\nTry installing support for this language." ), _( "Warning" ), wxOK );
            return false;
        }

        m_locale = new wxLocale(langId);
#if defined(__WXMSW__)
        m_locale->AddCatalogLookupPathPrefix( m_searchPath );
#endif
        m_locale->AddCatalog( ORIGINAL_APP_FILENAME );

        if( ! m_locale->IsOk() ) {
            wxMessageBox( _( "The selected language is wrong.\nWrong format of .mo file?" ), _( "Warning" ), wxOK );
            wxDELETE( m_locale );
            return false;
        }
    }
    return true;
}
