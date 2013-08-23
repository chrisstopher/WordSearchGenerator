#include "Word.h"

using namespace ws;

Word::Word() {
			
}

void Word::set(Position& pos, unsigned dir, std::string& str) {
	position = pos;
	direction = dir;
	string = str;
}

unsigned int Word::getDirection() const {
	return direction;
}

std::string& Word::getString() {
	return string;
}

Position& Word::getPosition() {
	return position;
}

char Word::getFirstLetter() {
	return string.at(0);
}

/*
This is the format portion of the file for the game that gets put into the file

Example:
0	2	1	power
Means that the word power is going to start at position (0, 2) and going in the direction 1 (which is south)(See Constants.h for the enum of directions)
                                                        (x, y)
*/
std::ostream& ws::operator<<(std::ostream& os, Word& word) {
	os << word.getPosition().getX() << "\t" << word.getPosition().getY() << "\t" << word.getDirection() << "\t" << word.getString() << "\n";
	return os;
}