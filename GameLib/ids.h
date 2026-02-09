/**
* @file ids.h
 * @author Hamin Paik
 *
 * Defines IDs for the menu items and other events in the application.
 */

#ifndef GAME_IDS_H
#define GAME_IDS_H

/**
 * IDs for menu items
 */
enum IDs {
    // Start IDs after the highest wxWidgets reserved ID
    ID_LEVEL_0 = wxID_HIGHEST + 1,
    ID_LEVEL_1,
    ID_LEVEL_2,
    ID_LEVEL_3,
    ID_LEVEL_4
};

#endif //GAME_IDS_H