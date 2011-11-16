#ifndef _CHARACTER_H_
#define _CHARACTER_H_

class
Character
{
	public:
		Character(int session_id, int character_id);
		~Character(void);
		int getSessionID(void);
		int getCharacterID(void);
		unsigned int getLevel(void);
		char const* getName(void);
	
	private:
		int session_id;
		int character_id;
		char* name;
		unsigned int level;
};

#endif

