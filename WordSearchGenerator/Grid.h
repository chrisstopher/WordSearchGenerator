#ifndef _GRID_H_
#define _GRID_H_

#include <iostream>
#include "Constants.h"
#include "Word.h"
#include "Position.h"

namespace ws {
	class Grid {
	public:
		Grid();
		unsigned char at(unsigned x, unsigned y);
		bool canHold(Word& word);
		void insert(Word& word);
		Position getRandomPosition();
		bool willOverwriteWord(Position& charPos, char c);
	private:
		enum DIRECTIONS {
			NORTH = 0, SOUTH, EAST, WEST, NORTH_EAST, SOUTH_WEST, NORTH_WEST, SOUTH_EAST, NUM_OF_DIRECTION, 
		};
		static const char NOTHING = ' ';
		unsigned char grid[ROWS][COLUMNS];
		Position moves[NUM_OF_DIRECTION];
		unsigned char at(Position& position);
		bool outOfBounds(Position& pos);
	};
	std::ostream& operator<<(std::ostream& os, Grid& grid);
}

#endif