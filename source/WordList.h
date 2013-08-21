#ifndef _WORDLIST_H_
#define _WORDLIST_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include "Word.h"

namespace ws {
	class WordList {
	public:
		WordList();
		unsigned size();
		void add(const Word& word);
		Word& at(unsigned i);
		bool overWordLimit();
		void sortAscending();
		void sortDescending();
		void clear();
	private:
		static const int MAX_WORD_COUNT = 25;
		std::vector<Word> Words;
	};
	std::ostream& operator<<(std::ostream& os, WordList& words);
}

#endif