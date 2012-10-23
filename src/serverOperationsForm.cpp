/*******************************************************************************
//
// Name:        serverOperationsForm.cpp
// Author:      Grzegorz Szura
// Description:
//
*******************************************************************************/
#include "serverOperationsForm.h"

#include <wx/tokenzr.h>
#include "../data/xpm/wx_nfp.xpm"

//(*InternalHeaders(serverOperationsForm)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(serverOperationsForm)
const long serverOperationsForm::ID_label1 = wxNewId();
const long serverOperationsForm::ID_GAUGE1 = wxNewId();
const long serverOperationsForm::ID_label2 = wxNewId();
const long serverOperationsForm::ID_PANEL1 = wxNewId();
const long serverOperationsForm::ID_TIMER = wxNewId();
//*)
const long serverOperationsForm::ID_thread = wxNewId();


BEGIN_EVENT_TABLE(serverOperationsForm,wxDialog)
    EVT_COMMAND( THREAD_EVENT, wxEVT_SYNC_OPERATION_DONE_EVENT, serverOperationsForm::threadOperationDoneEvent )

    //(*EventTable(serverOperationsForm)
    //*)
END_EVENT_TABLE()

/******************************************************************************/

serverOperationsForm::serverOperationsForm(wxWindow* parent, int action, wxString syncServerName, wxString inputData1, wxString inputData2, wxString &responseMessage, configClass *config, cycleDataClass *cycleData, wxWindowID id,const wxPoint& pos,const wxSize& size)
    : m_responseMessage (responseMessage)
{
    m_parent = parent;
    m_id = id;
    m_action = action;
    m_syncServerName = syncServerName;
    m_inputData1 = inputData1;
    m_inputData2 = inputData2;
    m_config = config;
    m_cycleData = cycleData;
    m_thread = NULL;
    m_destroying = 0;

    CreateGUIControls(parent);

    wxString label = _("Synchronization with server is performed.\nPlease wait...");

    switch (action) {
    case ACTION_IS_SERVER_ALIVE: {
        label = _("Checking is server is accessible.\nPlease wait...");
        break;
    }
    case ACTION_CHECK_USER_DATA_FILE: {
        label = _("Checking if synchronization is needed.\nPlease wait...");
        break;
    }
    case ACTION_DOWNLOAD_USER_DATA_FILE: {
        label = _("Downloading file with your cycles data from the server.\nPlease wait...");
        break;
    }
    case ACTION_UPLOAD_USER_DATA_FILE: {
        label = _("Uploading file with your cycles data to the server.\nPlease wait...");
        break;
    }
    case ACTION_REMOVE_USER_DATA_FILE: {
        label = _("Removing file with your cycles data and all backups from the server.\nPlease wait...");
        break;
    }
    default: {
        label = wxString::Format( _("Error - unknown operation"), action);
        Close();
    }
    }

    label1->SetLabel(label);
}

/**
 *
 */
void serverOperationsForm::CreateGUIControls( wxWindow* parent )
{
    //(*Initialize(serverOperationsForm)
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer1;

    Create(parent, wxID_ANY, _("NFP - synchronizig data with server"), wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    label1 = new wxStaticText(Panel1, ID_label1, _("Synchronization with server is performed. Synchronization with server is performed.\nPlease wait..."), wxDefaultPosition, wxDefaultSize, 0, _T("ID_label1"));
    BoxSizer2->Add(label1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    gauge = new wxGauge(Panel1, ID_GAUGE1, 100, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_GAUGE1"));
    BoxSizer2->Add(gauge, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    label2 = new wxStaticText(Panel1, ID_label2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_label2"));
    BoxSizer2->Add(label2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    timer.SetOwner(this, ID_TIMER);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_TIMER,wxEVT_TIMER,(wxObjectEventFunction)&serverOperationsForm::updateProgress);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&serverOperationsForm::onInit);
    //*)

    CentreOnParent();
    wxIcon wx_nfp_ICON( wx_nfp_xpm );
    SetIcon( wx_nfp_ICON );
}

serverOperationsForm::~serverOperationsForm()
{
    stopProgressMonitor();

    wxDELETE(m_thread);

    //(*Destroy(serverOperationsForm)
    //*)getCardsCount()
}

/******************************************************************************/

void serverOperationsForm::onInit(wxInitDialogEvent& event)
{
    wxLogDebug( _T("[serverOpForm] on init fired") );
    runThread();
    event.Skip();
}

/******************************************************************************/

void serverOperationsForm::runThread()
{
    wxLogDebug( wxString::Format( _T("[serverOpForm] starting thread, action: '%i', server: '%s', params: '%s', '%s'"), m_action, m_syncServerName.c_str(), m_inputData1.c_str(), m_inputData2.c_str()) );

    m_thread = new wxHttpThread( this, m_action, m_syncServerName, m_inputData1, m_inputData2, m_config, wxTHREAD_JOINABLE );
    if ( m_thread->Create() != wxTHREAD_NO_ERROR ) {
        wxMessageBox( _( "Error occured while creating thread.. cannot sync data with server"), _( "Error" ), wxOK | wxICON_ERROR, this );
        // TODO, is that ok?
        Close();
    }

    if ( m_thread->Run() != wxTHREAD_NO_ERROR ) {
        wxMessageBox( _( "Error occured while running thread.. cannot sync data with server"), _( "Error" ), wxOK | wxICON_ERROR, this );
        // TODO, is that ok?
        Close();
    }
    startProgressMonitor();
}

/**
 * Operation finished.
 */
void serverOperationsForm::threadOperationDoneEvent( wxCommandEvent& event )
{
    stopProgressMonitor();
    gauge->SetValue(100);

    wxLogDebug( wxString::Format( _T("[serverOpForm] thread finished: ('%i) '%s'"), event.GetInt(), event.GetString().c_str()) );
    m_responseMessage = event.GetString();
    size_t ret = (size_t)m_thread->Wait();
    wxLogDebug( wxString::Format( _T("[serverOpForm] thread return code: %i"), ret) );
    //m_thread->Delete();
    //return (ret == 0);
    EndModal(ret);
}

/******************************************************************************/

void serverOperationsForm::startProgressMonitor()
{
    timer.Start( 200 );
}

void serverOperationsForm::stopProgressMonitor()
{
    timer.Stop();
}

/**
 * Update gauge to show the upload progress
 */
void serverOperationsForm::updateProgress(wxTimerEvent& event)
{
    label2->SetLabel( m_thread->getCurrentAction() );

    int range = m_thread->getUploadDownloadSize();
    if (range < 0) {
        gauge->Pulse();
        return;
    }

    int value = m_thread->getUploadedDownloadedSoFar();
    value = value * 100 / range;
    if (value < 0) value = 0;
    if (value > 100) value = 100;
    wxLogDebug( wxString::Format( _T("[serverOpForm] %i %%"), value) );
    gauge->SetValue( value );
}

/******************************************************************************/
