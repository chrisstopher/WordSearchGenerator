#ifndef _WORD_H_
#define _WORD_H_

#include <iostream>
#include <string>
#include "Position.h"

namespace ws {
	class Word {
	public:
		Word();
		void set(Position& pos, unsigned dir, std::string& str);
		unsigned int getDirection() const;
		std::string& getString();
		Position& getPosition();
		char getFirstLetter();
	private:
		Position position;
		unsigned int direction;
		std::string string;
	};
	std::ostream& operator<<(std::ostream& os, Word& word);
}

#endif