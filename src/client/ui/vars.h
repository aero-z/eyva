/**
 * This header file provides UI-widely used variables and enums.
 */

#ifndef _UI_VARS_H_
#define _UI_VARS_H_

/**
 * Window definition.
 * The windows are arranged as follows:
 *
 * +---------------+---------------+---------------+
 * |               |               |               |
 * |               |  NAVIGATION   |               |
 * |               |               |               |
 * +---------------+---------------+---------------+
 * |               |               |               |
 * |   CHARACTER   |     GAME      |    SOCIAL     |
 * |               |               |               |
 * +---------------+---------------+---------------+
 * |               |               |               |
 * |               |     MENU      |    OPTIONS    |
 * |               |               |               |
 * +---------------+---------------+---------------+
 * |               |               |               |
 * |               |     LOGIN     |               |
 * |               |               |               |
 * +---------------+---------------+---------------+
 */

enum WindowName {
	WINDOW_LOGIN,          //         login window
	WINDOW_MENU,           // [ESC]   main menu, containing
	WINDOW_OPTIONS,        //         - options
	WINDOW_GAME,           // contains further windows:
		WINDOW_PLAYGROUND,     //         where you play the game
		WINDOW_PROMPT,         // [ENTER] prompt (also "fast chat")
		WINDOW_PROMPT_COMMAND, // [':']   prompt with a preceding ':'
		WINDOW_INFOBAR,        //         top panel, showing information
		WINDOW_ACTIONBAR,      //         bottom panel, showing actions and info
		WINDOW_INVENTORY,      // ['b']   character inventory
	WINDOW_CHARACTER,      // ['c']   ingame character settings
	WINDOW_SOCIAL,         // [TAB]   ingame chat, online stats, etc.
	WINDOW_NAVIGATION,     // ['m']   minimap and orientation tools

	WINDOW_IDENTITY,       // (virtual) currently focused window
	WINDOW_TERM            // (virtual) indicates program shutdown
};

#endif

