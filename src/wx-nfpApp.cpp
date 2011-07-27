//---------------------------------------------------------------------------
//
// Name:        wx-nfpApp.cpp
// Author:      enkeli
// Created:     2006-06-13 22:42:38
// Description:
//
//---------------------------------------------------------------------------

#include <wx/socket.h>
//#include <wx/stdpaths.h>
#include <wx/filename.h>
#include "wx-nfpApp.h"
#include "nfpMainFrame.h"
#include "aboutFrame.h"
#include "utilClass.h"


IMPLEMENT_APP( nfpMainFrameApp )

bool nfpMainFrameApp::OnInit() {
    wxSocketBase::Initialize();

    utilClass util;

    wxFileName appFileName( argv[0] );
    appFileName.Normalize( wxPATH_NORM_DOTS | wxPATH_NORM_ABSOLUTE | wxPATH_NORM_TILDE );

    wxString path = util.getConfigPath();
    if ( ! wxDirExists( path ) )
        wxFileName::Mkdir( path, 0755, wxPATH_MKDIR_FULL );
    wxString m_configFile = path + appFileName.GetName() + _T( ".cfg" );

    // temporary only
    //wxMessageBox(util.getAllPathsPath());

    m_config = new configClass( m_configFile );
    bool configReadSucessfully = m_config->readParamsFromConfigFile();

    m_translationHelper = new translationHelper( util.getAvailableLanguagesConfigFilePath(), util.getLocalePath() );
    m_config->langId = m_translationHelper->load( m_config->langId );

#if defined(__WXMSW__)
    if ( !configReadSucessfully ) {
        int answer = wxMessageBox( _( "Should the application check periodically if there is new version available?\nThe only data which will be sent is the information if you are using Windows or Linux operating system." ), _( "Question" ), wxYES_NO );
        if ( answer == wxYES ) {
            m_config->checkForUpdates = true;
            m_config->updatesProxy = wxGetTextFromUser( _( "If you are using the proxy server to comunicate with the Internet\nthen write it down in the format 'hostname:port' or 'hostname' (in this case the default proxy port '8080' will be used)\n and press 'OK' button.\nIf you don't use the proxy server then press 'Cancel' button." ), _( "Question" ), _T( "" ) );
            if ( m_config->updatesProxy.Len() > 0 && m_config->updatesProxy.Find( _T( ":" ) ) == wxNOT_FOUND ) {
                m_config->updatesProxy = m_config->updatesProxy + _T( ":8080" );
            }

        } else {
            m_config->checkForUpdates = false;
        }
    }
#else
    m_config->checkForUpdates = false;
#endif


    wxString fileToOpen = _T( "" );
    if ( argc > 1 ) {
        fileToOpen = wxString( argv[1] );
    }

    aboutFrame *aboutFrm = new aboutFrame( NULL, fileToOpen, m_config );
    //SetTopWindow( aboutFrm );
    aboutFrm->Show();
    aboutFrm->Refresh();
    return true;
}

int nfpMainFrameApp::OnExit() {
    if ( m_translationHelper ) {
        wxDELETE( m_translationHelper );
    }
    return 0;
}

translationHelper * nfpMainFrameApp::getTranslationHelper() {
    return m_translationHelper;
}
