  /**
 * @file MainFrame.h
 * @author Beckham Lee
 *
 * Holds the main frame for the game
 */

#ifndef GAME_MAINFRAME_H
#define GAME_MAINFRAME_H
#include "ids.h"      
#include "LevelView.h"


/**
 * the top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    /// the level view class for this frame
    LevelView *mLevelView;

    void OnExit(wxCommandEvent& event);

    void OnClose(wxCloseEvent& event);

public:
    void Initialize();
};


#endif //GAME_MAINFRAME_H