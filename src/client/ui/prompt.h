/*
 * `eyva'
 * Copyright (C) 2011 ayekat (martin.weber@epfl.ch)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _UI_PROMPT_H_
#define _UI_PROMPT_H_

// Parent class:
#include "window.h"

// Client:
#include "../pipe.h"

// Others:
#include <vector>

#define PROMPT_SIZE 80

class
WinPrompt : public Window
{
	public:
		WinPrompt(Pipe* pipe);
		~WinPrompt(void);
		/*virtual*/ WindowName process(int input);
		/*virtual*/ void focus(void);
		/*virtual*/ bool unfocus(void);
		/*virtual*/ void repaint(void);
	
	private:
		WindowName evaluate(void);
		bool cmdcmp(char const* keyword);
		int argcount(void);
		size_t argfetch(char* buffer, int pos);

		Pipe* pipe;
		std::vector<int> prompt;
		unsigned int cursor_pos;
};

#endif

