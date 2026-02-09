/**
 * @file GameApp.h
 * @author Beckham Lee
 */

#ifndef PROJECT1_GAMEAPP_H
#define PROJECT1_GAMEAPP_H

#include <wx/wx.h>

/**
 * Main application class
 */
class GameApp : public wxApp
{
public:
    bool OnInit() override;
};


#endif //PROJECT1_GAMEAPP_H