#ifndef _POSITION_H_
#define _POSITION_H_
#include <iostream>
//
//Position class to have an x and y so I can make the code look cleaner
//
class Position {
public:
	Position(int nx = 0, int ny = 0);
	int getX() const;
	int getY() const;
	void setX(int newX);
	void setY(int newY);
	void set(int newX, int newY);
	void set(Position& pos);
	Position& operator+=(Position& p);
private:
	int x, y;
};
Position operator+(Position& p1, Position& p2);
std::ostream& operator<<(std::ostream& os, Position& pos);

#endif