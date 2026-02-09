/**
 * @file LevelView.h
 * @author Beckham Lee
 *
 * Class that implements the child window our program draws in.
 * The window is a child of the mian frame, holds this window,
 * the menu bar, and the status bar.
 */

#ifndef GAME_LEVELVIEW_H
#define GAME_LEVELVIEW_H
#include "Level.h"
#include "Football.h"

// previous assignments did not have these includes
// so as we develop this we might want to remove these
// they may become redundant
#include <wx/timer.h>

/**
 * Class that holds the level window and its menu elements
 */
class LevelView : public wxWindow
{
private:

    /// The current scaling factor for virtual pixels
    double mScale = 1.0;

    /// Game area height in virtual pixels
    const static int Height = 1024;

    /// The Level object, containing all game elements
    Level mLevel;

    /// Current level number
    int mLevelNum = 0;

    /// The main timer for the game loop
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time between frames
    wxStopWatch mStopWatch;

    /// The last stopwatch time, used to calculate elapsed time
    long mTime = 0;

    /// A pointer to the football, for easy access (e.g., for scrolling)
    std::shared_ptr<Football> mFootball;

    /// The scrolling offset for implementing virtual pixels
    double mScrollX = 0;

    /// Keep track of the currently selected level number
    std::wstring mCurrentLevel;

    void OnPaint(wxPaintEvent& event);
    void OnTimer(wxTimerEvent& event);

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);

    void OnLevel0(wxCommandEvent& event);
    void OnLevel1(wxCommandEvent& event);
    void OnLevel2(wxCommandEvent& event);
    void OnLevel3(wxCommandEvent& event);
    void OnLevel4(wxCommandEvent& event);

public:
    void Initialize(wxFrame* mainFrame);

    void ResetLevel();
    void LoadNextLevel();
    void LoadLevelN(std::wstring filename);

    /**
     * Get the name of the currently loaded level file
     * @return wstring name of the currently loaded level
     */
    std::wstring& GetCurrentLevel() { return mCurrentLevel; }

    /**
     * Set the current level number
     * @param levelNum The level number to set
     */
    void SetLevelNum(int levelNum) { mLevelNum = levelNum; }

    void Stop();
};


#endif //GAME_LEVELVIEW_H