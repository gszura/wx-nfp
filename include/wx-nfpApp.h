//---------------------------------------------------------------------------
//
// Name:        wx-nfpApp.h
// Author:      enkeli
// Created:     2006-06-13 22:42:38
// Description:
//
//---------------------------------------------------------------------------

#ifndef __WX_NFP_APP__
#define __WX_NFP_APP__

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#else
#include <wx/wxprec.h>
#endif

#include "translationHelper.h"
#include "configClass.h"


class nfpMainFrameApp : public wxApp {
protected:
     translationHelper * m_translationHelper;
     configClass *m_config;

public:
     bool OnInit();
     int OnExit();
     void RecreateGUI();
     translationHelper * getTranslationHelper();
};

DECLARE_APP(nfpMainFrameApp)

#endif
