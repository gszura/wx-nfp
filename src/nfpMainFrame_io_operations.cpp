/*******************************************************************************
//
// Name:        nfpMainFrame_io_operations.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "nfpMainFrame.h"
#include "IOoperations.h"
#include "wx-nfpAppInfo.h"


/*******************************************************************************
********************************************************************************
*******************************************************************************/

void nfpMainFrame::readLastOpenedCard()
{
    if ( !m_config->openLastOpenedFile && !m_config->openFileFromParams)
        return;
    if ( m_config->dataFileName.IsEmpty() )
        return;

    if ( !readCard() ) {
        if ( m_config->dataFileName.IsEmpty()) {
            m_cycleData->createNewSet();
        } else {
            m_cycleData->removeAll();
            m_cycleData->setActiveCard( -1 );
            m_cycleData->setActiveDay( -1 );
            m_cycleData->setCardModified( false );
        }
        Refresh();
    }
    wxLogDebug( _T("[nfpMainFrame] card read"));

    updateAll();

    if ( m_config->dataFileName.IsEmpty() ) {
        m_cardFrm->update();
        m_cardFrm->Show();
    }

    m_dataFileNamePrev = wxEmptyString;
    m_cardModifiedPrev = false;

    m_newAppStatusMessage = 0;
    //m_doCheckForMissingDays = true;

    timerNotification->Start( 5000, wxTIMER_ONE_SHOT );

    menuBarMain->EnableTop( 1, true );
    menuBarMain->EnableTop( 2, true );
    menuBarMain->EnableTop( 3, true );
    menuBarMain->EnableTop( 4, true );
}

/**
 *
 */
bool nfpMainFrame::readCard()
{
    m_config->instertCurrentlyOpenedFileNameToHistory();
    updateRecentCardsMenu();

    IOoperations iOoperations(this, m_config, m_cycleData, getSyncServerName());
    bool ret = iOoperations.readCard();

    if (ret) {
        m_cycleData->setActiveCard( m_cycleData->getCardsCount() );
        m_config->checkLastDayVisibility = true;
        wxLogDebug( wxString::Format( _T("[nfpMainFrame] cards count: %i"), m_cycleData->getCardsCount() ) );
        informUserAboutChangesInThisRelease();
        checkForMissingDays();
    } else {
        m_cycleData->setActiveCard( -1 );
        m_config->dataFileName = wxEmptyString;
    }

    return ret;
}

/**
 *
 */
bool nfpMainFrame::askToSaveCard( bool cancelAllowed )
{
    wxLogDebug( _T("[nfpMainFrame] askToSaveCard()"));
    if ( checkCardAndDayFramesStates( true, cancelAllowed ) ) {
        if ( m_cycleData->getCardModified() || m_cycleData->getServerFileNotInSync() ) {

            if (m_config->autosaveSet && !m_config->dataFileName.IsEmpty() ) {
                return saveCard( false, cancelAllowed );
            }
            int answer;
            if ( cancelAllowed ) {
                answer = wxMessageBox( _( "Save changes in current cards' set to the file?" ), _( "Warning" ), wxYES_NO | wxCANCEL, m_parent );
            } else {
                answer = wxMessageBox( _( "Save changes in current cards' set to the file?" ), _( "Warning" ), wxYES_NO, m_parent );
            }
            if ( answer == wxCANCEL ) {
                return false;
            } else if ( answer == wxYES ) {
                return saveCard( false, cancelAllowed );
            }
        } else {
            wxLogDebug( _T("[nfpMainFrame] card not modified, no need to save"));
        }
    } else {
        return false;
    }
    return true;
}

bool nfpMainFrame::saveCard( bool forceNewFile, bool cancelAllowed )
{
    wxLogDebug( _T("[nfpMainFrame] saveCard()"));
    if ( !checkCardAndDayFramesStates( true, true ) ) {
        return false;
    }

    IOoperations iOoperations(this, m_config, m_cycleData, getSyncServerName());
    return iOoperations.saveCard( false, cancelAllowed );
}

bool nfpMainFrame::saveCardWithInitialSync()
{
    wxLogDebug( _T("[nfpMainFrame] saveCard()"));
    if ( !checkCardAndDayFramesStates( true, true ) ) {
        return false;
    }

    IOoperations iOoperations(this, m_config, m_cycleData, getSyncServerName());
    bool ret = iOoperations.saveCard( false, true, ACTION_SYNC );

    if (ret) {
        m_cycleData->setActiveCard( m_cycleData->getCardsCount() );
        m_config->checkLastDayVisibility = true;
        wxLogDebug( wxString::Format( _T("[nfpMainFrame] cards count: %i"), m_cycleData->getCardsCount() ) );
        informUserAboutChangesInThisRelease();
        checkForMissingDays();
    } else {
        m_cycleData->setActiveCard( -1 );
        m_config->dataFileName = wxEmptyString;
    }
    return ret;
}

bool nfpMainFrame::syncCard()
{
    wxLogDebug( _T("[nfpMainFrame] syncCard()"));
    if ( !checkCardAndDayFramesStates( true, true ) ) {
        return false;
    }

    IOoperations iOoperations(this, m_config, m_cycleData, getSyncServerName());
    bool ret = iOoperations.saveCard( false, true, ACTION_SYNC );

    if (ret) {
        m_cycleData->setActiveCard( m_cycleData->getCardsCount() );
        m_config->checkLastDayVisibility = true;
        wxLogDebug( wxString::Format( _T("[nfpMainFrame] cards count: %i"), m_cycleData->getCardsCount() ) );
        informUserAboutChangesInThisRelease();
        checkForMissingDays();
    } else {
        m_cycleData->setActiveCard( -1 );
        m_config->dataFileName = wxEmptyString;
    }

    return ret;


}

bool nfpMainFrame::moveCardToNewSyncServer()
{
    wxLogDebug( _T("[nfpMainFrame] actionForSyncServerChaged()"));

    if ( !m_cycleData->getServerFileName().IsEmpty() ) {
        int answer = wxMessageBox( _( "You have just changed the synchronization server.\nDo you want to remove cards' set from previous server and enable synchronization on new one?" ), _( "Question" ), wxYES_NO | wxICON_QUESTION, this );
        if ( answer == wxYES ) {
            if ( !removeCardFromServer(m_cycleData->getServerUri()) ) {
                wxLogDebug( _T("[nfpMainFrame] removing card from previous server was canceled or failed.."));

                int answer2 = wxMessageBox( _( "Removing card from previous server was canceled or failed.\nDo you anyway want to enable synchronization on new server?" ), _( "Question" ), wxYES_NO | wxICON_QUESTION, this );
                if ( answer2 != wxYES )
                    return false;
            }

            m_cycleData->setServerSyncData(wxEmptyString, wxEmptyString, 0, wxEmptyString);
            return saveCardWithInitialSync();
        } else {
            wxLogDebug( _T("[nfpMainFrame] user doesn't want to remove cards' set from previous server and enable synchronization on new one"));
            return false;
        }
    } else {
        wxLogDebug( _T("[nfpMainFrame] card is not stored on server - no need for synchronization"));
        return false;

    }
}

bool nfpMainFrame::removeCardFromServer(wxString syncServerName)
{
    wxLogDebug( _T("[nfpMainFrame] removeCardFromServer()"));
    if ( !checkCardAndDayFramesStates( true, true ) ) {
        return false;
    }

    IOoperations iOoperations(this, m_config, m_cycleData, (syncServerName.IsEmpty() ? getSyncServerName() : syncServerName) );
    return iOoperations.removeCardFromServer();
}

wxString nfpMainFrame::getSyncServerName()
{
    if ( m_config->useCustomServer && !m_config->customServerUri.IsEmpty() ) {
        return m_config->customServerUri;
    } else {
        return SYNC_SERVER_PATH;
    }
}

/*******************************************************************************/
