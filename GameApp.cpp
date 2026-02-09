/**
 * @file GameApp.cpp
 * @author Beckham Lee
 */
#include "pch.h"

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif



#include "GameApp.h"
#include <MainFrame.h>
#include <wx/log.h>

/**
 * initialize the application
 * @return bool that indicates a successful initiation of the game main frame
 */
bool GameApp::OnInit()
{
#ifdef WIN32
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
    if (!wxApp::OnInit())
        return false;
    
    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();

    frame->SetFocus();
    frame->Raise();
    frame->Show(true);

    return true;
}