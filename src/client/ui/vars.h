/**
 * This header file provides UI-widely used variables and enums.
 */

#ifndef _VARS_H_
#define _VARS_H_

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
	LOGIN,          //         login window
	MENU,           // [ESC]   main menu, containing
	OPTIONS,        //         - options
	GAME,           // contains further windows:
		PLAYGROUND,     //         where you play the game
		PROMPT,         // [ENTER] prompt (also "fast chat")
		PROMPT_COMMAND, // [':']   prompt with a preceding ':'
		INFOBAR,        //         top panel, showing information
		ACTIONBAR,      //         bottom panel, showing actions and information
		INVENTORY,      // ['b']   character inventory
	CHARACTER,      // ['c']   ingame character settings
	SOCIAL,         // [TAB]   ingame chat, online stats, etc.
	NAVIGATION,     // ['m']   minimap and orientation tools

	IDENTITY,       // (virtual) currently focused window
	TERM            // (virtual) indicates program shutdown
};

#endif

