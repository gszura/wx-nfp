/*******************************************************************************
//
// Name:        IOoperations.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/
#ifndef IOoperations_H
#define IOoperations_H

#include "configClass.h"
#include "cyclesData.h"
#include "utilClass.h"
#include "wxHttpThread.h"

/*******************************************************************************/

#define ACTION_SYNC       1
#define ACTION_READ       2
//#define ACTION_FORCE_READ 3
#define ACTION_WRITE      3
#define ACTION_REMOVE     4

/*******************************************************************************/

class IOoperations
{
public:
    IOoperations(wxWindow* parent, configClass *config, cycleDataClass *cycleData, wxString syncServerName);
    virtual ~IOoperations() {
    }


public:
    bool readCard();
    bool saveCard(bool forceNewFile, bool cancelAllowed, int syncType = ACTION_WRITE);
    bool removeCardFromServer();

private:
    bool readSyncDetailsFromFile();
    bool readCardFromFile();

    bool saveCardToFile();

    void prepareNewFileName();
    bool askIfCreateNewServerCard();

    bool syncWithServer(int);

    bool isServerAlive();
    bool checkName();
    void checkNameEvent(wxCommandEvent &);

    bool removeFile();
    bool uploadFile();
    bool downloadFile(bool compareFiles = false);
    cycleDataClass *tryToReadDownloadedCards(wxString);
    bool compareRemoteAndLocalFiles(cycleDataClass*);

    bool runThread(int action, wxString inputData1, wxString inputData2 = wxEmptyString);

    bool askForServerCardName(bool);
    bool askForPasswordIfNeeded(bool);


private:
    wxWindow *m_parent;
    configClass *m_config;
    cycleDataClass *m_cycleData;
    utilClass m_util;
    wxString m_syncServerName;

    // sync with server
    wxHttpThread *m_serverSyncThread;
    int m_syncActionType;
    //int m_syncDownloadOrUpload;
    wxString m_encryptedFile;
    wxString m_serverCardName;
    wxString m_realServerCardName;
    wxString m_serverFileMd5Sum;
    time_t m_serverFileSyncTimestamp;
    wxString m_serverSyncThreadResponse;
};

#endif // IOoperations_H

/*******************************************************************************/
