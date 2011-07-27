#ifndef _TRANSLATION_HELPER_H
#define _TRANSLATION_HELPER_H


#include <wx/wx.h>
#include <wx/intl.h>

class translationHelper {
private:
     wxString m_availableLanguagesConfigFilePath;
     wxString m_searchPath;
     wxLocale * m_locale;
     long m_defaultLanguageId;

public:
     translationHelper( const wxString &, const wxString & );
     ~translationHelper();

     wxLocale * getLocale();

     long load(long langId);
     void getInstalledLanguages( wxArrayString &, wxArrayLong & );
     long askUserForLanguage( wxArrayString &, wxArrayLong & );
     bool setApplicationLanguage( long  );
};

#endif
