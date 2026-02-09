/**
 * @file LevelView.cpp
 * @author Beckham Lee
 */

#include "pch.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include "LevelView.h"
#include "Background.h"
#include "ids.h"

/// Frame duration in milliseconds
// const int FrameDuration = 30;
const int FrameDuration = 5;

/// Maximum amount of time to allow for elapsed to prevent tunneling
const double MaxElapsed = 0.05;

/// Level file paths
const std::wstring level0 = L"levels/level0.xml";  ///< path to the level 0 xml file
const std::wstring level1 = L"levels/level1.xml";  ///< path to the level 1 xml file
const std::wstring level2 = L"levels/level2.xml";  ///< path to the level 2 xml file
const std::wstring level3 = L"levels/level3.xml";  ///< path to the level 3 xml file
const std::wstring level4 = L"levels/level4.xml";  ///< path to the level 4 xml file

/**
 * Initialize the game view window.
 * @param mainFrame The main frame of the application
 */
void LevelView::Initialize(wxFrame* mainFrame)
{
    Create(mainFrame, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Bind the paint and timer events
    Bind(wxEVT_PAINT, &LevelView::OnPaint, this);
    Bind(wxEVT_TIMER, &LevelView::OnTimer, this);

    // Bind the menu handler events
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED,&LevelView::OnLevel0,this,ID_LEVEL_0);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED,&LevelView::OnLevel1,this,ID_LEVEL_1);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED,&LevelView::OnLevel2,this,ID_LEVEL_2);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED,&LevelView::OnLevel3,this,ID_LEVEL_3);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED,&LevelView::OnLevel4,this,ID_LEVEL_4);
    // mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED,&LevelView::OnResetLevel,this,ID_RESET);

    // Bind keyboard events
    Bind(wxEVT_KEY_DOWN, &LevelView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &LevelView::OnKeyUp, this);

    // Load level 0 as the initial state.
    // This call also saves the football in mFootball
    mLevelNum = 1;
    LoadLevelN(level1);

    // Start the timer and stopwatch for the game loop
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();
    mTime = mStopWatch.Time();
}

/**
 * The timer event handler. This is the game's heartbeat.
 * @param event The timer event.
 */
void LevelView::OnTimer(wxTimerEvent& event)
{
    // Calculate elapsed time since the last frame
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    // Prevent tunneling by ensuring elapsed does not exceed MaxElapsed
    while (elapsed > MaxElapsed)
    {
        mLevel.Update(MaxElapsed);
        elapsed -= MaxElapsed;
    }

    // Consume any remaining time
    if (elapsed > 0)
    {
        mLevel.Update(elapsed);
    }

    // Trigger a redraw of the window
    Refresh();
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void LevelView::OnPaint(wxPaintEvent& event)
{
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context from the DC
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    //
    // Automatic Scaling
    //
    auto size = GetClientSize();
    mScale = double(size.GetHeight()) / double(Height);
    graphics->Scale(mScale, mScale);

    auto virtualWidth = (double)size.GetWidth() / mScale;
    auto virtualHeight = (double)size.GetHeight() / mScale;

    //
    // Scrolling
    //
    // Compute the amount to scroll in the X dimension
    auto xOffset = -mFootball->GetX() + virtualWidth / 2.0;

    // Push the current state and apply the scroll translation
    graphics->PushState();
    graphics->Translate(xOffset, 0);

    // Draw all scrolling game items
    mLevel.Draw(graphics);

    // Pop the scrolled state
    graphics->PopState();

    //
    // Draw the non-scrolling Scorecard
    //
    mLevel.GetScorecard().Draw(graphics, static_cast<int>(virtualWidth), static_cast<int>(virtualHeight));
}


/**
 * Handle key down events
 * @param event The key event
 */
void LevelView::OnKeyDown(wxKeyEvent& event)
{
    // ignore inputs when the level is frozen or starting up
    if (mLevel.GetFreeze() || mLevel.GetGracePeriod())
    {
        return;
    }

    if (mFootball != nullptr) {
        mFootball->OnKeyDown(event);
    }
}

/**
 * Handle key up events
 * @param event The key event
 */
void LevelView::OnKeyUp(wxKeyEvent& event)
{
    // ignore inputs when the level is frozen or starting up
    if (mLevel.GetFreeze() || mLevel.GetGracePeriod())
    {
        return;
    }

    if (mFootball != nullptr) {
        mFootball->OnKeyUp(event);
    }
}

/**
 * Stop the game timer.
 */
void LevelView::Stop()
{
    mTimer.Stop();
}

/**
 * Handle the Level 0 menu selection in the Levels tab of the mainframe
 * @param event Menu event
 */
void LevelView::OnLevel0(wxCommandEvent& event)
{
    mLevelNum = 0;
    LoadLevelN(level0);
}

/**
 * Handle the Level 1 menu selection in the Levels tab of the mainframe
 * @param event Menu event
 */
void LevelView::OnLevel1(wxCommandEvent& event)
{
    mLevelNum = 1;
    LoadLevelN(level1);
}

/**
 * Handle the Level 2 menu selection in the Levels tab of the mainframe
 * @param event Menu event
 */
void LevelView::OnLevel2(wxCommandEvent& event)
{
    mLevelNum = 2;
    LoadLevelN(level2);
}

/**
 * Handle the Level 3 menu selection in the Levels tab of the mainframe
 * @param event Menu event
 */
void LevelView::OnLevel3(wxCommandEvent& event)
{
    mLevelNum = 3;
    LoadLevelN(level3);
}

/**
 * Handle the Level 4 menu selection in the Levels tab of the mainframe
 * @param event Menu event
 */
void LevelView::OnLevel4(wxCommandEvent& event)
{
    mLevelNum = 4;
    LoadLevelN(level4);
}

/**
 * Load the xml file containing the information for a level
 * @param filename Xml file to load
 */
void LevelView::LoadLevelN(std::wstring filename)
{
    auto football = mLevel.Load(filename, this);
    if (football == nullptr)
    {
        // xml file reading failed
        // THIS SHOULD NEVER OCCUR, because we have the level xml files in the "levels" directory
        std::cerr << L"file \"levelN.xml\" could not be read in function LevelView::OnLeveN()" << std::endl;
    }
    else
    {
        mFootball = football;
        mCurrentLevel = filename;
        mLevel.ResetFreeze();

        // Reset the scorecard's time
        Scorecard& scorecard = mLevel.GetScorecard();
        scorecard.ResetTime();
        scorecard.ResetScore();
        scorecard.SetLevelNum(mLevelNum);
        scorecard.SetStartGrace(true);
    }
    Refresh();
}

/**
 * Load the current level to its starting state
 */
void LevelView::ResetLevel()
{
    LoadLevelN(mCurrentLevel);
}

/**
 * Load the next level in sequence
 * Progresses from level1 -> level2 -> level3 -> level3 (cycles)
 */
void LevelView::LoadNextLevel()
{
    if (mCurrentLevel == level0)
    {
        mLevelNum = 1;
        LoadLevelN(level1);
    }
    else if (mCurrentLevel == level1)
    {
        mLevelNum = 2;
        LoadLevelN(level2);
    }
    else if (mCurrentLevel == level2)
    {
        mLevelNum = 3;
        LoadLevelN(level3);
    }
    else if (mCurrentLevel == level3)
    {
        mLevelNum = 4;
        LoadLevelN(level4);
    }
    else if (mCurrentLevel == level4)
    {
        mLevelNum = 3;
        // After completing level 4, cycle back to level 3
        LoadLevelN(level3);
    }
    else
    {
        mLevelNum = 0;
        // If we're in an unknown level state, default to level 0
        LoadLevelN(level0);
    }
}