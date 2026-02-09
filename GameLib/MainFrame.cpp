/**
 * @file MainFrame.cpp
 * @author Beckham Lee
 */

#include "pch.h"

#include "MainFrame.h"
#include "LevelView.h"

/**
 *Initialize the MainFrame window
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Game",
        wxDefaultPosition, wxSize(1000, 800));

    auto sizer = new wxBoxSizer( wxVERTICAL );

    mLevelView = new LevelView();
    mLevelView->Initialize(this);

    sizer->Add(mLevelView, 1, wxEXPAND | wxALL, 0);

    SetSizer( sizer );
    Layout();

    CreateStatusBar();

    auto menuBar = new wxMenuBar( );

    // add menus
    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();


    // add options to menus
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    levelMenu->Append(ID_LEVEL_0, L"Level 0", L"Load Level 0");
    levelMenu->Append(ID_LEVEL_1, L"Level 1", L"Load Level 1");
    levelMenu->Append(ID_LEVEL_2, L"Level 2", L"Load Level 2");
    levelMenu->Append(ID_LEVEL_3, L"Level 3", L"Load Level 3");
    levelMenu->Append(ID_LEVEL_4, L"Level 4", L"Load Level 4");

    // bind events to functions
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

    SetMenuBar(menuBar);

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Levels");
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Handle the window close event.
 * @param event The close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    // Tell the LevelView to stop its timer before we close
    mLevelView->Stop();

    // Important: Allow the window to be destroyed
    Destroy();
}

