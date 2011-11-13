/**
 * This header file provides UI-widely used variables and enums.
 */

#ifndef _VARS_H_
#define _VARS_H_

enum WindowName {
	PLAYGROUND,     //         where you play the game
	PROMPT,         // [ENTER] prompt (also "fast chat")
	PROMPT_COMMAND, // [':']   prompt with a preceding ':'
	INFOBAR,        //         top panel, showing information
	ACTIONBAR,      //         bottom panel, showing actions and information
	LOGIN,          //         login window
	MENU,           // [ESC]   main menu, containing
	OPTIONS,        //         - options
	NAVIGATION,     // ['m']   minimap and orientation tools
	SOCIAL,         // [TAB]   ingame chat, online stats, etc.
	CHARACTER,      // ['c']   ingame character settings
	INVENTORY,      // ['b']   character inventory

	IDENTITY        // (virtual) currently focused window
};

#endif

