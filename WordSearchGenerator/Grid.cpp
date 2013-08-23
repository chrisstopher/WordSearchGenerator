#include "Grid.h"

using namespace ws;

/*
Sets the whole grid to have nothing in it
Creates the 8 different move directions
*/
Grid::Grid() {
	for (int y = 0; y < ROWS; y++) {
		for (int x = 0; x < COLUMNS; x++) {
			grid[y][x] = NOTHING;
		}
	}
	moves[NORTH] = Position(0, -1);
	moves[SOUTH] = Position(0, 1);
	moves[EAST] = Position(1, 0);
	moves[WEST] = Position(-1, 0);
	moves[NORTH_EAST] = Position(1, -1);
	moves[SOUTH_WEST] = Position(-1, 1);
	moves[NORTH_WEST] = Position(-1, -1);
	moves[SOUTH_EAST] = Position(1, 1);
}

unsigned char Grid::at(unsigned x, unsigned y) {
	return grid[y][x];
}

unsigned char Grid::at(Position& position) {
	return grid[position.getY()][position.getX()];
}

/*
Returns true if the word fits into the grid
Returns false if the word would go out of bounds or overwrites a word
Get the move position(direction maps to a specific movement)
See where the word is going to end and if it is out of bounds then return false
Then goes through the whole word and checks to make sure that it does not overwrite a word already in the grid

move depends on the direction... if direction is 0 then move is (0, -1) which is North (see getMovement() function)
wordEndsHere is where the word ends at after adding the size of the word and then times it by the way it moves
Example:
The word 'power' at the position of (0, 0) going in the direction 0 (which is north)
move would = (0, -1)
wordEndsHere would = (0 + 4(length of the word 'power' - 1) * 0(the x value of move),
					  0 + 4(length of the word 'power' - 1) * -1(the y value of move))
so wordEndsHere would be (0, -4)
Which would be thrown out because that is out of bounds


The reason for the length of the word - 1 is because the starting position of the word is already counted as 1
So you have minus one from the length


Another example:
The word 'power' at the position of (0, 0) going in the direction 1 (which is south)
move would = (0, 1)
wordEndsHere would = (0 + 4(length of the word 'power' - 1) * 0(the x value of move),
					  0 + 4(length of the word 'power' - 1) * 1(the y value of move))
so wordEndsHere would be (0, 4)
Which would be okay as long as it does not overwrite another word in the grid because it does not go out of bounds

Example of overwriting...
Just say the word:
1	1	1	grace	-> The word grace starts at (1, 1) and goes south
Is in the grid...
   0 1 2 3 4 5 . . .
0 | | | | | | |
1 | |g| | | | |
2 | |r| | | | |
3 | |a| | | | |
4 | |c| | | | |
5 | |e| | | | |
.
.
.

Then you try to put in the word:
0	0	7	power -> The word power starts at (0, 0) and goes south east
   0 1 2 3 4 5 . . .
0 |p| | | | | |
1 | |g| | | | |
2 | |r| | | | |
3 | |a| | | | |
4 | |c| | | | |
5 | |e| | | | |
.
.
.

It allows the 'p'
But when it gets to (1, 1)
It sees that there is not nothing there and that it is a 'g'
And you are trying to put a 'o' there
so it returns false because the word cannot go there
The 'p' does not stay because it does not get recorded in the grid but just tested to see if it is allowed to be there

The loop starts out at position 1 because the words have to be atleast 2 letters longs
and because it already makes sure the first letter in the word will not overwrite any word in the main algorithm loop

The reason it starts at 1 is because it already checks the first character in the algorithm
And for the charPos = word.getPosition() + move is because it is on the second character in the word and the getposition returns the first position
*/
bool Grid::canHold(Word& word) {
	Position move = moves[word.getDirection()];
	Position wordEndsHere(word.getPosition().getX() + (word.getString().size()-1) * move.getX(),
						  word.getPosition().getY() + (word.getString().size()-1) * move.getY());
	if (outOfBounds(wordEndsHere)) {
		return false;
	}
	Position charPos(word.getPosition() + move);
	for (unsigned i = 1; i < word.getString().size(); i++) {
		if (willOverwriteWord(charPos, word.getString().at(i))) {
			return false;
		}
		charPos += move;
	}
	return true;
}

/*
Has to be called after itFits(...)
It has no checking to see if anything is wrong(out of bounds or overwrite word)
It just places the word into the grid
*/
void Grid::insert(Word& word) {
	Position move = moves[word.getDirection()];
	Position charPos(word.getPosition());
	for (unsigned i = 0; i < word.getString().size(); i++) {
		grid[charPos.getY()][charPos.getX()] = word.getString().at(i);
		charPos += move;
	}
}

Position Grid::getRandomPosition() {
	return Position(rand() % COLUMNS, rand() % ROWS);
}

/*
Returns if the pos is out of bounds on the 2d array
*/
bool Grid::outOfBounds(Position& pos) {
	return (pos.getX() < 0 || pos.getY() < 0 || pos.getX() >= COLUMNS || pos.getY() >= ROWS);
}

/*
charPos - The position you are checking to see if you can put the c there
c       - the character you are trying to put at the charPos
if the character at charPos is not NOTHING and
if the character at charPos is not the c
*/
bool Grid::willOverwriteWord(Position& charPos, char c) {
	return at(charPos) != NOTHING && at(charPos) != c;
}

/*
Prints out the grid in a very nice way
Used for debugging
*/
std::ostream& ws::operator<<(std::ostream& os, Grid& grid) {
	os << "\n   ";
	for (int x = 0; x < COLUMNS; x++) {
		if (x < 10) {
			os << x;
		} else {
			os << static_cast<char>((x - 10) + 'A');
		}
		os << " ";
	}
	os << "\n";
	for (int y = 0; y < ROWS; y++) {
		if (y < 10) {
			os << y;
		} else {
			os << static_cast<char>((y - 10) + 'A');
		}
		os << " |";
		for (int x = 0; x < COLUMNS; x++) {
			os << grid.at(x, y) << "|";
		}
		os << "\n";
	}
	os << "\n";
	return os;
}