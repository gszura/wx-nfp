/*******************************************************************************
//
// Name:        serverOperationsForm.h
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/
#ifndef SERVEROPERATIONSFORM_H
#define SERVEROPERATIONSFORM_H

//(*Headers(serverOperationsForm)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/dialog.h>
#include <wx/timer.h>
#include <wx/gauge.h>
//*)

#include "configClass.h"
#include "cyclesData.h"
#include "utilClass.h"
#include "wxHttpThread.h"


class serverOperationsForm: public wxDialog
{
public:

    serverOperationsForm(wxWindow* parent, int action, wxString syncServerName, wxString inputData1, wxString inputData2, wxString &responseMessage, configClass *config, cycleDataClass *cycleData, wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
    virtual ~serverOperationsForm();
    void sync();

    //(*Declarations(serverOperationsForm)
    wxTimer timer;
    wxGauge* gauge;
    wxPanel* Panel1;
    wxStaticText* label1;
    wxStaticText* label2;
    //*)

protected:

    //(*Identifiers(serverOperationsForm)
    static const long ID_label1;
    static const long ID_GAUGE1;
    static const long ID_label2;
    static const long ID_PANEL1;
    static const long ID_TIMER;
    //*)
    static const long ID_TIMERUPDATES;
    static const long ID_thread;

private:
    wxString &m_responseMessage;
    int m_destroying;
    wxWindow *m_parent;
    int m_id;
    int m_action;
    wxString m_syncServerName;
    wxString m_inputData1;
    wxString m_inputData2;
    configClass *m_config;
    cycleDataClass *m_cycleData;
    wxHttpThread *m_thread;
    wxString m_encryptedFile;
    wxString m_serverCardName;
    wxString m_realServerCardName;
    wxString m_serverFileMd5Sum;
    time_t m_serverFileSyncTimestamp;
    utilClass m_util;

    //(*Handlers(serverOperationsForm)
    void updateProgress(wxTimerEvent& event);
    void onInit(wxInitDialogEvent& event);
    //*)

    void CreateGUIControls(wxWindow* parent);

    void runThread();
    void threadOperationDoneEvent( wxCommandEvent& );

    void startProgressMonitor();
    void stopProgressMonitor();

    DECLARE_EVENT_TABLE()
};

#endif
