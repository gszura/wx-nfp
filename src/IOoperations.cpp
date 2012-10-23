/*******************************************************************************
//
// Name:        IOoperations.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/

#include "IOoperations.h"
#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/tokenzr.h>
#include "serverOperationsForm.h"
#include "syncActionTypeDialog.h"
#include "passwordDialog.h"
#include "Crypto.h"
#include "wx-nfpAppInfo.h"

/*******************************************************************************
********************************************************************************
*******************************************************************************/

IOoperations::IOoperations(wxWindow* parent, configClass *config, cycleDataClass *cycleData, wxString syncServerName)
{
    m_parent = parent;
    m_config = config;
    m_cycleData = cycleData;
    m_syncServerName = syncServerName;
}

/******************************************************************************/

bool IOoperations::readCard()
{
    wxLogDebug( _T("[IOoperations] readCard()"));

    bool ret = readCardFromFile();
    if ( !ret ) {
        return false;
    }

    int numberOfCardsInSetBeforeSync = m_cycleData->getCardsCount();

#ifdef __WXDEBUG__
    if (m_config->syncFileAutomatically)
        wxLogDebug( _T("[IOoperations] m_config->syncFileAutomatically = true"));
    else
        wxLogDebug( _T("[IOoperations] m_config->syncFileAutomatically = false"));
    if (m_cycleData->getServerFileName().IsEmpty())
        wxLogDebug( _T("[IOoperations] m_cycleData->getServerFileName().IsEmpty() = true"));
    else
        wxLogDebug( _T("[IOoperations] m_cycleData->getServerFileName().IsEmpty() = false"));
    if (m_cycleData->getServerFileHash().IsEmpty())
        wxLogDebug( _T("[IOoperations] m_cycleData->getServerFileHash().IsEmpty() = true"));
    else
        wxLogDebug( _T("[IOoperations] m_cycleData->getServerFileHash().IsEmpty() = false"));
#endif

    if ( m_config->syncFileAutomatically
            && !m_cycleData->getServerFileName().IsEmpty()
            && !m_cycleData->getServerFileHash().IsEmpty() ) {
        // automatic sync with server enabled
        wxLogDebug( _T("[IOoperations] sync with server"));
        syncWithServer(ACTION_READ);

        readCardFromFile();

        if ( abs(numberOfCardsInSetBeforeSync - m_cycleData->getCardsCount()) > 1 ) {
            int answer = wxMessageBox( wxString::Format( _( "Hmm.. that's strange - before synchronization there were %i cards in the set, but in the set downloaded from the server are %i cards.\nIs that correct?\nSelect 'Yes' to ignore this warning.\nSelect 'No' to restore last local backup." ), numberOfCardsInSetBeforeSync, m_cycleData->getCardsCount() ), _( "Warning" ), wxYES_NO | wxICON_WARNING, m_parent );
            if (answer == wxNO) {
                // restore last backup
                wxMessageBox( _( "Restoring backups is not supported yet.. sorry ;)" ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
            }
        }
    }

    return ret;
}

bool IOoperations::readSyncDetailsFromFile()
{
    wxLogDebug( _T("[IOoperations] readSyncDetailsFromFile()"));
    return m_cycleData->readSyncDetailsFromFile(m_config->dataFileName);
}

bool IOoperations::readCardFromFile()
{
    wxLogDebug( _T("[IOoperations] readCardFromFile()"));
    if ( m_cycleData->readCardsDataFromFile(m_config->dataFileName) ) {
        return true;
    } else {
        wxMessageBox( wxString::Format( _( "Error occured while reading data from file:\n%s" ), m_cycleData->getErrorMessages().c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }
}

/*******************************************************************************/

/**
 *
 */
bool IOoperations::saveCard( bool forceNewFile, bool cancelAllowed, int syncType )
{
    if ( m_config->dataFileName.IsEmpty() || forceNewFile ) {
        prepareNewFileName();
        if ( m_config->dataFileName.IsEmpty() ) {
            if ( cancelAllowed ) {
                return false;
            } else {
                return true;
            }
        }
    }

#ifdef __WXDEBUG__
    if (m_config->dataFileName.IsEmpty())
        wxLogDebug( _T("[IOoperations] m_config->dataFileName.IsEmpty() = true"));
    else
        wxLogDebug( _T("[IOoperations] m_config->dataFileName.IsEmpty() = false"));
    if (m_cycleData->getCardModified())
        wxLogDebug( _T("[IOoperations] m_cycleData->getCardModified() = true"));
    else
        wxLogDebug( _T("[IOoperations] m_cycleData->getCardModified() = false"));
    if (m_cycleData->getServerFileNotInSync())
        wxLogDebug( _T("[IOoperations] m_cycleData->getServerFileNotInSync() = true"));
    else
        wxLogDebug( _T("[IOoperations] m_cycleData->getServerFileNotInSync() = false"));
    if (forceNewFile)
        wxLogDebug( _T("[IOoperations] forceNewFile = true"));
    else
        wxLogDebug( _T("[IOoperations] forceNewFile = false"));
    if (m_config->syncFileAutomatically)
        wxLogDebug( _T("[IOoperations] m_config->syncFileAutomatically = true"));
    else
        wxLogDebug( _T("[IOoperations] m_config->syncFileAutomatically = false"));
    if (m_cycleData->getServerFileName().IsEmpty())
        wxLogDebug( _T("[IOoperations] m_cycleData->getServerFileName().IsEmpty() = true"));
    else
        wxLogDebug( _T("[IOoperations] m_cycleData->getServerFileName().IsEmpty() = false"));
    if (m_cycleData->getServerFileHash().IsEmpty())
        wxLogDebug( _T("[IOoperations] m_cycleData->getServerFileHash().IsEmpty() = true"));
    else
        wxLogDebug( _T("[IOoperations] m_cycleData->getServerFileHash().IsEmpty() = false"));

    if (m_syncActionType == ACTION_SYNC)
        wxLogDebug( _T("[IOoperations] ACTION_SYNC"));
    if (m_syncActionType == ACTION_READ)
        wxLogDebug( _T("[IOoperations] ACTION_READ"));
    if (m_syncActionType == ACTION_WRITE)
        wxLogDebug( _T("[IOoperations] ACTION_WRITE"));
    if (m_syncActionType == ACTION_REMOVE)
        wxLogDebug( _T("[IOoperations] ACTION_REMOVE"));
#endif

    if ( syncType == ACTION_SYNC && !m_config->dataFileName.IsEmpty() ) {
        if ( m_cycleData->getCardModified() && !saveCardToFile() )
            return false;

        m_cycleData->setCardModified( false );

        // even if there are problems with synchronization with server, we want to continue..
        // in other case user cannot .e.g close the application if server is not available.
        //return syncWithServer(ACTION_WRITE);
        syncWithServer(syncType);
        return true;

    } else if ( ! m_config->dataFileName.IsEmpty() && ( m_cycleData->getCardModified() || m_cycleData->getServerFileNotInSync() || forceNewFile ) ) {
        if ( saveCardToFile() ) {
            m_cycleData->setCardModified( false );

            if (m_config->syncFileAutomatically) {
                if ( forceNewFile && askIfCreateNewServerCard() ) {
                    m_cycleData->setServerSyncData(wxEmptyString, wxEmptyString, 0, wxEmptyString);
                }
                // even if there are problems with synchronization with server, we want to continue..
                // in other case user cannot .e.g close the application if server is not available.
                //return syncWithServer(ACTION_WRITE);
                syncWithServer(syncType);
                return true;
            }
        } else {
            return false;
        }
    }

    return true;
}

bool IOoperations::saveCardToFile()
{
    if ( m_cycleData->saveCardsDataToFile( m_config->dataFileName ) ) {
        return true;
    } else {
        wxMessageBox( wxString::Format( _( "Error occured while saving card to file:\n%s" ), m_cycleData->getErrorMessages().c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }
}

/******************************************************************************/

bool IOoperations::removeCardFromServer()
{
    return syncWithServer(ACTION_REMOVE);
}

/******************************************************************************/

void IOoperations::prepareNewFileName()
{
    wxString message = _( "Save cards' set as..." ) ;
    wxString default_path = wxEmptyString;
    wxString default_filename = wxEmptyString;
    wxString default_extension = wxEmptyString;
    wxString wildcard = _T( "*.nfpdata" );
    int flags = wxFD_SAVE | wxFD_OVERWRITE_PROMPT;

    if ( m_config->dataFileName.IsEmpty() ) {
        if ( !wxDirExists( m_util.getCardSetDataPath() ) ) {
            wxFileName::Mkdir( m_util.getCardSetDataPath(), 0755, wxPATH_MKDIR_FULL );
        }
        default_path = m_util.getCardSetDataPath();
        default_filename = _( "new_set" );
        default_extension = _T( ".nfpdata" );
    } else {
        default_filename = m_config->dataFileName;
    }

    wxString filename = wxFileSelector( message, default_path, default_filename, default_extension, wildcard, flags, m_parent );
    if ( !filename.IsEmpty() ) {
        // set extension of the file if it's missing
        if (filename.Find( _T( ".nfpdata" )) == -1)
            filename << _T( ".nfpdata" );
        m_config->dataFileName = filename;
    }
}

bool IOoperations::askIfCreateNewServerCard()
{
    int answer = wxMessageBox( _("You're saving the card set in the new file.\nDou you want also to create new file on server for this card?"),
                               _("Question"), wxYES_NO | wxICON_QUESTION, m_parent);
    return (answer == wxYES);
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/

/***** SYNC WITH SERVER ****/

bool IOoperations::syncWithServer(int actionType)
{
    m_syncActionType = actionType;
    if (m_syncActionType == ACTION_SYNC)
        wxLogDebug( _T("[IOoperations] ACTION_SYNC"));
    if (m_syncActionType == ACTION_READ)
        wxLogDebug( _T("[IOoperations] ACTION_READ"));
    if (m_syncActionType == ACTION_WRITE)
        wxLogDebug( _T("[IOoperations] ACTION_WRITE"));
    if (m_syncActionType == ACTION_REMOVE)
        wxLogDebug( _T("[IOoperations] ACTION_REMOVE"));

    m_serverFileMd5Sum = wxEmptyString;
    m_realServerCardName = wxEmptyString;
    m_encryptedFile = wxEmptyString;
    m_serverCardName = m_cycleData->getServerFileName();

    if ( m_serverCardName.IsEmpty() && m_syncActionType != ACTION_SYNC ) {
        // do not synchronize
        wxLogDebug( _T("[IOoperations] m_serverCardName.IsEmpty() && m_syncActionType != ACTION_SYNC - exit") );
        return false;
    }

    if ( !isServerAlive() ) {
        // server is not alive
        wxMessageBox( wxString::Format( _( "Request to this URL faild:\n%s%s\nso either server is down or it's incorrectly defined.\nAnyway I cannot sync data." ), m_syncServerName.c_str(), SERVER_PING_PATH ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }

    if ( !m_serverCardName.IsEmpty() ) {
        // file already stored on server
        wxLogDebug( wxString::Format( _T("[IOoperations] file should be already stored on server, m_serverCardName = '%s'"), m_serverCardName.c_str() ) );

        bool saveAsNewFileOnServer = false;

        while (m_serverFileMd5Sum.IsEmpty()) {
            // ask for pass if not set yet
            if ( !askForPasswordIfNeeded(true) )
                return false;

            // Read md5sum of the file on server
            if ( ! checkName() ) {
                // ERROR - file should be stored on server bug it has not been found there - wrong pass? server has been changed? server error?
                int answer = wxMessageBox( _( "I cannot find your file on the server.\nAre you sure you have given correct password?" ), _( "Error" ), wxYES_NO | wxICON_ERROR, m_parent );
                if (answer == wxYES) {
                    if (m_syncActionType == ACTION_READ) {
                        answer = wxMessageBox( _( "So I don't know what's wrong.. there were problems on server or you have changed the server.. sorry.\nI'll check it again when you save the card.." ), _( "Error" ), wxOK | wxICON_INFORMATION, m_parent );
                        return false;
                    } else if (m_syncActionType == ACTION_REMOVE) {
                        answer = wxMessageBox( _( "So I don't know what's wrong.. there were problems on server or you have changed the server.. sorry.\nI cannot remove something what I cannot find ;)" ), _( "Error" ), wxOK | wxICON_INFORMATION, m_parent );
                        return false;
                    } else {
                        answer = wxMessageBox( _( "So I don't know what's wrong.. there were problems on server or you have changed the server.. sorry.\nDou you want me to save your card on the server anyway?" ), _( "Question" ), wxYES_NO | wxICON_QUESTION, m_parent );
                        if (answer == wxYES) {
                            saveAsNewFileOnServer = true;
                            break;
                        } else {
                            return false;
                        }
                    }
                } else {
                    // wrong pass
                    m_config->password = wxEmptyString;
                    m_serverFileMd5Sum = wxEmptyString;
                }
            } else if (m_serverFileMd5Sum.IsEmpty()) {
                wxLogDebug( _T( "[IOoperations] file has been found on server but m_serverFileMd5Sum is empty.." ) );
            }
        } // while
        wxLogDebug( wxString::Format( _T("[IOoperations] m_serverFileMd5Sum = '%s'"), m_serverFileMd5Sum.c_str() ) );

        if ( saveAsNewFileOnServer ) {
            // file has not been found on server but user asked to save it as a new file
            wxLogDebug( wxString::Format( _T("[IOoperations] file has not been found on server but user asked to save it as a new file") ) );
            return uploadFile();
        } else {
            wxLogDebug( _T("[IOoperations] file has been found on server - check hash"));
            // file has been found on server - check hash
            if (m_serverFileMd5Sum.IsEmpty()) {
                wxMessageBox( _( "File has been checked on server correctly, but m_serverFileMd5Sum is still empty in sync().. this issue shouldn't occured, please inform author" ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
                return false;
            }

            if (m_syncActionType == ACTION_REMOVE) {
                return removeFile();
            } else if ( m_serverFileMd5Sum.IsSameAs( m_cycleData->getServerFileHash() ) ) {
                // hashes are the same
                wxLogDebug( wxString::Format( _T("[IOoperations] hashes are the same") ) );

                if (m_syncActionType != ACTION_READ && m_cycleData->getServerFileNotInSync() ) {
                    // local file has been changed -> upload file on server, but only when ACTION_WRITE or ACTION_SYNC
                    return uploadFile();
                }

            } else {
                // hashes are not the same
                wxLogDebug( wxString::Format( _T("[IOoperations] hashes are not the same") ) );

                if (m_cycleData->getServerFileNotInSync() ) {
                    wxLogDebug( _T("[IOoperations] local file has been changed since last sync -> ask which file to use"));
                    // local file has been changed since last sync -> ask which file to use?
                    int answer = wxMessageBox( wxString::Format( _( "File on server has been update since last sync (which you made at %s).\nSelect 'Yes' to upload your local file and overwrite the file on server with your latest changes?\n Select 'No' to download the file from the server and see the changes between it and your local file." ), m_cycleData->getServerFileSyncHumanReadableDate().c_str()), _( "Do overwrite remote file?" ), wxYES_NO | wxICON_QUESTION, m_parent );
                    if (answer == wxYES) {
                        return uploadFile();
                    } else {
                        return downloadFile(true);
                    }
                } else {
                    wxLogDebug( _T("[IOoperations] local file has not been changed since last sync"));
                    if (m_syncActionType == ACTION_WRITE) {
                        // remote file has been changed since last sync -> ask which file to use?
                        int answer = wxMessageBox( wxString::Format( _( "File on server has been update since last sync (which you made at %s).\nSelect 'Yes' to upload your local file and overwrite the file on server with your latest changes?\n Select 'No' to download the file from the server and see the changes between it and your local file." ), m_cycleData->getServerFileSyncHumanReadableDate().c_str()), _( "Do overwrite remote file?" ), wxYES_NO | wxICON_QUESTION, m_parent );
                        if (answer == wxYES) {
                            return uploadFile();
                        } else {
                            return downloadFile(true);
                        }
                    } else {
                        // local file has not been changed since last sync -> download from server
                        wxLogDebug( _T("[IOoperations] local file has not been changed since last sync -> download from server"));
                        return downloadFile();
                    }
                }
            }
        }
    } else if (m_syncActionType == ACTION_SYNC) {
        wxLogDebug( _T("[IOoperations] server card name is empty, so either file is not stored on server or we don't know anything about it"));

        // ask user what to do
        syncActionTypeDialog *dialog = new syncActionTypeDialog(m_parent);
        int retCode = dialog->ShowModal();
        if (retCode != SYNC_READ_EXISTING_CARD && retCode != SYNC_CREATE_NEW_CARD)
            return false;

        if (retCode == SYNC_READ_EXISTING_CARD) {
            // read existing card
            wxLogDebug( _T("[IOoperations] synchronizing file already stored on server (new PC installation)"));
            while ( m_realServerCardName.IsEmpty() ) {
                if ( !askForServerCardName(true) )
                    return false;
                if ( !askForPasswordIfNeeded(true) )
                    return false;

                // check if we can find the file with this name
                if ( !checkName() ) {
                    // ERROR - file should be stored on server bug it has not been found there - wrong pass? server has been changed? server error?
                    int answer = wxMessageBox( _( "I cannot find your file on the server.\nAre you sure you have given correct name of the cards' set stored on the server and password?" ), _( "Error" ), wxYES_NO | wxICON_ERROR, m_parent );
                    if (answer == wxYES) {
                        answer = wxMessageBox( _( "So I don't know what's wrong.. there were problems on server or... sorry.\n" ), _( "Error" ), wxOK | wxICON_INFORMATION, m_parent );
                        return false;
                    } else {
                        // wrong pass
                        m_config->password = wxEmptyString;
                        m_serverCardName = wxEmptyString;
                    }

                    // file not found
                    m_realServerCardName = wxEmptyString;
                }
            }
            return downloadFile(true);

        } else {
            // store as a new card
            wxLogDebug( _T("[IOoperations] storing new file on the server "));
            while ( m_realServerCardName.IsEmpty() ) {
                if ( !askForServerCardName(false) )
                    return false;
                if ( !askForPasswordIfNeeded(false) )
                    return false;

                // check if name is not used yet
                if ( checkName() ) {
                    // nazwa zajeta
                    m_realServerCardName = wxEmptyString;
                    wxLogDebug( _T("[IOoperations] name already taken - ask for new one"));
                }
            }

            return uploadFile();
        }



    } else {
        wxLogDebug( _T("[IOoperations] server card name is empty, action != SYNC - exit"));
    }

    return true;
}

/******************************************************************************/

/**
 * return true if file has been found on server.
 */
bool IOoperations::isServerAlive()
{
    return runThread(ACTION_IS_SERVER_ALIVE, wxEmptyString, wxEmptyString);
}

/******************************************************************************/

/**
 * return true if file has been found on server.
 */
bool IOoperations::checkName()
{
    // prepare server file name
    m_realServerCardName = m_util.generateFancyFileName(m_serverCardName, m_config->password);

    wxLogDebug( wxString::Format( _T("[IOoperations] running checkName() m_realServerCardName = '%s'"), m_realServerCardName.c_str() ) );
    m_serverFileMd5Sum = wxEmptyString;

    if ( runThread(ACTION_CHECK_USER_DATA_FILE, m_realServerCardName, wxEmptyString) ) {
        m_serverFileMd5Sum = m_serverSyncThreadResponse;
        return true;
    } else {
        wxLogDebug( wxString::Format( _T( "Unexpected response from server on file check (file not found on server). Expected string: '<md5sum>'. Found: %s" ), m_serverSyncThreadResponse.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }
}

/******************************************************************************/
/******************************************************************************/

bool IOoperations::removeFile()
{
    wxLogDebug( wxString::Format( _T("[IOoperations] removeFile()") ) );

    m_realServerCardName = m_util.generateFancyFileName(m_serverCardName, m_config->password);

    // upload file
    if ( !runThread(ACTION_REMOVE_USER_DATA_FILE, m_realServerCardName) ) {
        wxMessageBox( wxString::Format( _( "Problem occurred when removing your file from server.\nExpected response string: 'OK'\nFound: %s" ), m_serverSyncThreadResponse.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }
    if ( !m_serverSyncThreadResponse.StartsWith( _( "OK" )) ) {
        wxMessageBox( wxString::Format( _( "Problem occurred when removing your file from server.\nExpected response string: 'OK'\nFound: %s" ), m_serverSyncThreadResponse.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }
    return true;
}


/******************************************************************************/
/******************************************************************************/

bool IOoperations::uploadFile()
{
    wxLogDebug( wxString::Format( _T("[IOoperations] uploadFile()") ) );

    // prepare server file name
    m_serverFileSyncTimestamp = 0;
    m_serverFileMd5Sum = wxEmptyString;
    m_realServerCardName = m_util.generateFancyFileName(m_serverCardName, m_config->password);
    m_encryptedFile = m_util.getTempFolderPath() + m_realServerCardName;
    if ( wxFileExists(m_encryptedFile) )
        wxRemoveFile(m_encryptedFile);

    Crypto crypto(m_config->password, m_config->dataFileName, m_encryptedFile);
    crypto.encryptFile();
    wxLogDebug( wxString::Format( _T("[IOoperations] encrypted file: %s"), m_encryptedFile.c_str() ) );
    /*
    if ( !wxCopyFile(m_config->dataFileName, m_encryptedFile) ) {
        wxMessageBox( wxString::Format( _( "Cannot copy file: '%s' -> '%s'" ), m_config->dataFileName.c_str(), m_encryptedFile.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }
    */

    // upload file
    if ( !runThread(ACTION_UPLOAD_USER_DATA_FILE, m_encryptedFile, m_realServerCardName) ) {
        wxMessageBox( wxString::Format( _( "Problem occurred with sending your file on server.\nExpected response string: 'OK:<timestamp>:<md5sum>'\nFound: %s" ), m_serverSyncThreadResponse.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }

    if ( wxFileExists(m_encryptedFile) )
        wxRemoveFile(m_encryptedFile);

    // parsing response, expected: OK:1348561375:c7e4e472a97694e29a49792a32aeb298
    if ( !m_serverSyncThreadResponse.StartsWith( _T( "OK:" )) ) {
        wxMessageBox( wxString::Format( _( "Problem occurred with sending your file on server.\nExpected response string: 'OK:<timestamp>:<md5sum>'\nFound: %s" ), m_serverSyncThreadResponse.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }

    wxStringTokenizer tkz(m_serverSyncThreadResponse, wxT(":"));
    if (tkz.CountTokens() != 3) {
        wxMessageBox( wxString::Format( _( "Problem occurred with sending your file on server.\nExpected response string: 'OK:<timestamp>:<md5sum>'\nFound: %s" ), m_serverSyncThreadResponse.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }
    // read output
    tkz.GetNextToken();
    m_serverFileSyncTimestamp = m_util.strToLong(tkz.GetNextToken());
    m_serverFileMd5Sum = tkz.GetNextToken();

    if (m_serverFileSyncTimestamp == 0) {
        wxMessageBox( _( "File has been uploaded to server correctly, but m_serverFileSyncTimestamp is still empty in uploadFile().. this issue shouldn't occured, please inform author" ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }
    if (m_serverFileMd5Sum.IsEmpty()) {
        wxMessageBox( _( "File has been uploaded to server correctly, but m_serverFileMd5Sum is still empty in uploadFile().. this issue shouldn't occured, please inform author" ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }
    wxLogDebug( wxString::Format( _T("[IOoperations] set sync options: name: %s | md5sum:  %s | timestamp:  %i"), m_serverCardName.c_str(), m_serverFileMd5Sum.c_str(), m_serverFileSyncTimestamp ) );
    m_cycleData->setCardModified(true);
    m_cycleData->setServerSyncData(m_serverCardName, m_serverFileMd5Sum, m_serverFileSyncTimestamp, m_syncServerName);
    m_cycleData->setServerFileNotInSync(false);

    return saveCardToFile();
}

/******************************************************************************/
/******************************************************************************/

bool IOoperations::downloadFile(bool compareFiles)
{
    wxLogDebug( wxString::Format( _T("[IOoperations] downloadFile()") ) );

    // prepare server file name
    m_realServerCardName = m_util.generateFancyFileName(m_serverCardName, m_config->password);
    m_encryptedFile = wxEmptyString;
    wxString decryptedFile = wxFileName::CreateTempFileName(_T("nfp"));

    if ( wxFileExists(m_encryptedFile) )
        wxRemoveFile(m_encryptedFile);

    // download file
    if ( !runThread(ACTION_DOWNLOAD_USER_DATA_FILE, m_realServerCardName) ) {
        wxMessageBox( wxString::Format( _( "Problem occurred with downloading your file from server.\nExpected your cards file.\nFound: %s" ), m_serverSyncThreadResponse.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }

    wxLogDebug( wxString::Format( _T("[IOoperations] downloadFile(): '%s'"), m_serverSyncThreadResponse.c_str()) );

    if (m_serverSyncThreadResponse.StartsWith( _( "Error" ))) {
        wxMessageBox( wxString::Format( _( "Problem occurred with downloading your file from server.\nExpected your cards file.\nFound: %s" ), m_serverSyncThreadResponse.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }

    m_encryptedFile = m_serverSyncThreadResponse;

    if (m_serverFileMd5Sum.IsEmpty()) {
        wxMessageBox( _( "File has been downloaded from server correctly, but m_serverFileMd5Sum is empty in downloadFile().. this issue shouldn't occured, please inform author" ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }

    if ( !wxFileExists(m_encryptedFile) ) {
        wxMessageBox( wxString::Format( _( "File has been downloaded from server correctly, but I cannot fine this file stored on hard disk:\n%s" ), m_encryptedFile.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return false;
    }

    // backup of existing file
    wxLogDebug( wxString::Format( _T("[IOoperations] backup of existing file: '%s'"), m_config->dataFileName.c_str()) );
    m_util.backupFile(m_config->dataFileName);

    Crypto crypto(m_config->password, m_encryptedFile, decryptedFile);
    crypto.decryptFile();
    wxLogDebug( wxString::Format( _T("[IOoperations] decrypted file: %s"), decryptedFile.c_str() ) );

    if ( wxFileExists(m_encryptedFile) )
        wxRemoveFile(m_encryptedFile);

    cycleDataClass *remoteCycleData = tryToReadDownloadedCards(decryptedFile);
    if (remoteCycleData == NULL) {
        return false;
    }

    bool useRemoteCopy = true;

    if ( compareFiles ) {
        useRemoteCopy = compareRemoteAndLocalFiles(remoteCycleData);
    }

    if (useRemoteCopy) {
        wxLogDebug( wxString::Format( _T("[IOoperations] copy %s -> %s"), m_encryptedFile.c_str(), m_config->dataFileName.c_str() ) );
        if ( !wxCopyFile(decryptedFile, m_config->dataFileName) ) {
            wxMessageBox( wxString::Format( _( "Cannot copy file: '%s' -> '%s'" ), m_encryptedFile.c_str(), m_config->dataFileName.c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
            return false;
        }

        if ( wxFileExists(decryptedFile) )
            wxRemoveFile(decryptedFile);

        if (! readCardFromFile() ) {
            return false;
        }

        wxLogDebug( wxString::Format( _T("[IOoperations] set sync options: name: %s | md5sum:  %s | timestamp:  %i"), m_serverCardName.c_str(), m_serverFileMd5Sum.c_str(), -1 ) );
        m_cycleData->setServerSyncData(m_serverCardName, m_serverFileMd5Sum, -1, m_syncServerName);
        m_cycleData->setCardModified(true);
        m_cycleData->setServerFileNotInSync(false);

        return saveCardToFile();
    } else {
        return uploadFile();
    }
}


cycleDataClass *IOoperations::tryToReadDownloadedCards(wxString filePath)
{
    cycleDataClass *cycleData = new cycleDataClass();
    wxLogDebug( _T("[IOoperations] readCardFromFile()"));
    if ( cycleData->readCardsDataFromFile(filePath) ) {
        return cycleData;
    } else {
        wxMessageBox( wxString::Format( _( "Error occured while reading cycles data from just downloaded file.\nAre you sure that it's your file and you gave correct password?:\nDetails:\n%s" ), m_cycleData->getErrorMessages().c_str() ), _( "Error" ), wxOK | wxICON_ERROR, m_parent );
        return NULL;
    }

}

/******************************************************************************/

bool IOoperations::compareRemoteAndLocalFiles(cycleDataClass *remoteCycleData)
{
    // TODO: compare files, print differences and let user decide what to do..
    int retCode = wxMessageBox( wxString::Format( _( "I'm sorry but file comparison is not yet implemented..\nSelect 'Yes' to upload your local file and overwrite the file on server with your latest changes?\n Select 'No' to download the file from the server and overwrite changes you made locally." ), m_cycleData->getServerFileSyncHumanReadableDate().c_str()), _( "Do overwrite remote file?" ), wxYES_NO | wxICON_QUESTION, m_parent );
    return (retCode == wxNO);

    /*
    wxString differences = wxEmptyString;
    if ( !m_cycleData->getName().IsSameAs( remoteCycleData->getName() ) )
        differences  << wxString::Format( _("'name' on local card is: '%s', on remote card is: '%s'\n"), m_cycleData->getName().c_str(), remoteCycleData->getName().c_str() );
    if ( !m_cycleData->getBirthdayDay().FormatISODate().IsSameAs( remoteCycleData->getBirthdayDay().FormatISODate() ) )
        differences  << wxString::Format( _("'birthday' on local card is: '%s', on remote card is: '%s'\n"), m_cycleData->getBirthdayDay().FormatISODate().c_str(), remoteCycleData->getBirthdayDay().FormatISODate().c_str() );
    if ( m_cycleData->getShortestCycleDays() != remoteCycleData->getShortestCycleDays() )
        differences  << wxString::Format( _("'no. of days in shortest cycle' on local card is: '%s', on remote card is: '%s'\n"), m_cycleData->getShortestCycleDays(), remoteCycleData->getShortestCycleDays() );
    if ( m_cycleData->getShortestCycleFromCycles() != remoteCycleData->getShortestCycleFromCycles() )
        differences  << wxString::Format( _("'shortest cycle from last x cycles' card is: '%s', on remote card is: '%s'\n"), m_cycleData->getShortestCycleFromCycles(), remoteCycleData->getShortestCycleFromCycles() );
    return true;
    */
}

/******************************************************************************/

bool IOoperations::runThread(int action, wxString inputData1, wxString inputData2)
{
    wxString serverSyncThreadResponse = wxEmptyString;
    serverOperationsForm *serverOperations = new serverOperationsForm(m_parent, action, m_syncServerName, inputData1, inputData2, serverSyncThreadResponse, m_config, m_cycleData);
    wxLogDebug( _T("[IOoperations] show modal"));
    int retCode = serverOperations->ShowModal();

    // lock it somehow
    m_serverSyncThreadResponse = serverSyncThreadResponse;

    wxLogDebug( wxString::Format( _T("[IOoperations] serverOperationsForm return code = %i"), retCode ) );
    wxLogDebug( wxString::Format( _T("[IOoperations] serverOperationsForm response: '%s'"), m_serverSyncThreadResponse.c_str() ) );
    return (retCode == 0);
}

/******************************************************************************/

bool IOoperations::askForServerCardName(bool fileAlreadyStoredOnServer)
{
    wxString message = _("Type the name you want to use for your cards' set stored on the server.");
    if (fileAlreadyStoredOnServer)
        message = _("Type the name of your cards' set stored on the server.");

    if ( !m_serverCardName.IsEmpty()) {
        // this dialog is fired second time
        if (fileAlreadyStoredOnServer)
            message = _("Type the name of your cards' set stored on the server.");
        else
            message = _("It seems that somehow the combination of the cards' set name and password you've choosen generats the hash which is already in used.\nPlease type another name for your cards' set stored on the server (e.g. add one more letter)");
    }
    m_serverCardName = wxGetTextFromUser(message, _("Card name"), wxEmptyString, m_parent);

    if ( m_serverCardName.IsEmpty() )
        // user didn't provide a server file name so we cancel synchronization
        return false;
    else
        return true;
}

/**
 * If password is not stored in config, then ask user for it.
 * If user press "Cancel' then close the dialog - sync will not be performed.
 */
bool IOoperations::askForPasswordIfNeeded(bool fileAlreadyStoredOnServer)
{
    if ( m_config->password.IsEmpty() ) {
        passwordDialog *dialog = new passwordDialog(m_parent, m_config, fileAlreadyStoredOnServer);
        dialog->ShowModal();

        if (m_config->password.IsEmpty())
            // user didn't provide a password so we cancel synchronization
            return false;
    }

    return true;
}

/*******************************************************************************
********************************************************************************
*******************************************************************************/
