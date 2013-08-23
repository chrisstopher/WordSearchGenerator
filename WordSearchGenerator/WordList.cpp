#include "WordList.h"

using namespace ws;

/*
Used for sorting the words after the algorithm is done and you want to put them in file
*/
struct {
	bool operator() (Word& w1, Word& w2) {
		return w1.getString() < w2.getString();
	}
} alphabetically;

WordList::WordList() {

}

unsigned WordList::size() {
	return Words.size();
}

void WordList::add(const Word& word) {
	Words.push_back(word);
}

Word& WordList::at(unsigned i) {
	return Words.at(i);
}

bool WordList::overWordLimit() {
	return Words.size() >= MAX_WORD_COUNT;
}

void WordList::sortAscending() {
	std::sort(Words.begin(), Words.end(), alphabetically);
}

void WordList::sortDescending() {
	std::sort(Words.rbegin(), Words.rend(), alphabetically);
}

void WordList::clear() {
	Words.clear();
}

/*
Used for debugging
Also prints each word into the file
This is the format portion of the file for the game
*/
std::ostream& ws::operator<<(std::ostream& os, WordList& words) {
	for (unsigned i = 0; i < words.size(); i++) {
		os << words.at(i);
	}
	return os;
}