/**
 * This header files handles all cases of user input for the bottom panel.
 */

case 10: // newline
	// TODO evaluate command
	prompt.clear();
	cursor_pos = 0;  // not necessary, but secure
	break;
case 27: //escape
	prompt.clear();
	cursor_pos = 0;  // not necessary, but secure
	break;
case 127: //backslash
	if(cursor_pos > 0)
		prompt.erase(prompt.begin()+(--cursor_pos));
	break;
case 260: //left arrow key
	if(cursor_pos > 0)
		cursor_pos--;
	break;
case 261: //right arrow key
	if(cursor_pos < prompt.size())
		cursor_pos++;
	break;
case 262: //home
	cursor_pos = 0;
	break;
case 330: //delete
	if(cursor_pos < prompt.size())
		prompt.erase(prompt.begin()+cursor_pos);
	break;
case 360: //end
	cursor_pos = prompt.size();
	break;

/* Ignore these:
 */
case 9: // tabulator
case 265: // F1
case 266: // F2
case 267: // F3
case 268: // F4
case 269: // F5
case 270: // F6
case 271: // F7
case 272: // F8
case 273: // F9
case 274: // F10
case 275: // F11
case 276: // F12
case 258: // down arrow key
case 259: // up arrow key
case 331: // insert
case 338: // page down
case 339: // page up
	break;

default:
	if(prompt.size() < PROMPT_SIZE)
		prompt.insert(prompt.begin()+(cursor_pos++), input);
	break;
