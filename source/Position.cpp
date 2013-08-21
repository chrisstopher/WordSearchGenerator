#include "Position.h"

Position::Position(int nx, int ny) : x(nx), y(ny) {

}

int Position::getX() const {
	return x;
}

int Position::getY() const {
	return y;
}

void Position::setX(int newX) {
	x = newX;
}

void Position::setY(int newY) {
	y = newY;
}

void Position::set(int newX, int newY) {
	setX(newX);
	setY(newY);
}

void Position::set(Position& pos) {
	setX(pos.getX());
	setY(pos.getY());
}

Position& Position::operator+=(Position& p) {
	x += p.x;
	y += p.y;
	return *this;
}

Position operator+(Position& p1, Position& p2) {
	Position result = p1;
	result += p2;
	return result;
}

std::ostream& operator<<(std::ostream& os, Position& pos) {
	os << pos.getX() << "\t" << pos.getY();
	return os;
}