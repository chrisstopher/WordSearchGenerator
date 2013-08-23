#include "StringList.h"

using namespace ws;
/*
returns an lowercase string
*/
struct {
	std::string& operator() (std::string& word) {
		std::transform(word.begin(), word.end(), word.begin(), tolower);
		return word;
	}
} toLower;

/*
Used to check every character of a string to make sure it is alphabetical
Is called after all the words have been lower cased
*/
struct {
	bool operator() (char c) {
		return c < 'a' || c > 'z';
	}
} notAlphabetical;

/*
Checks a string to see if the length of it is too long or too short or that the string is not alphabetical
Returning true means the word is ignored
Returning false means the word is kept
Also alerts the user of any word that does not meet the criteria just in case they actually care...
Example:
supercalifragilisticexpialidocious -> returns true because too long of word
a                                  -> returns true because too short of a word
1337sp3ak                          -> returns true because the word does not contain only letters in the alphabet
power                              -> returns false to not ignore the word because it is satisfies the criteria
*/
struct {
	bool operator() (std::string& s) {
		if (s.size() > MAX_STRING_LENGTH) {
			std::cout << "The word " << s << " is longer than " << MAX_STRING_LENGTH << " characters disgarding it.\n";
		} else if (s.size() < MIN_STRING_LENGTH) {
			std::cout << "The word " << s << " is smaller than " << MIN_STRING_LENGTH << " characters disgarding it.\n";
		}
		if (std::find_if(s.begin(), s.end(), notAlphabetical) != s.end()) {
			std::cout << "The word " << s << " is not a word.\n";
			return true;
		}
		return (s.size() > MAX_STRING_LENGTH) || (s.size() < MIN_STRING_LENGTH);
	}
} tooLongOrTooShortOrNotAlphabetical;

StringList::StringList() {

}

/*
Populates the vector with the strings seperated by white space or tabs
Makes sure there is atleast one word in the file
Then converts words to the correct format and checks words for a size and alphabetical
Makes sure atleast one word is actually usable in the strings
*/
bool StringList::populate(std::string& relativePath) {
	std::ifstream file(relativePath.c_str());
	if (!file) {
		std::cout << relativePath << " does not exist!";
		return false;
	}
	std::string word;
	while (file >> word) {
		Strings.push_back(word);
	}
	file.close();
	if (Strings.empty()) {
		std::cout << "There are no words in the file \"" << relativePath << "\"\n";
		return false;
	}
	unsigned int wordsInFile = Strings.size();
	convertAndCheckWords();
	if (Strings.empty()) {
		std::cout << "There are no useable words in the file \"" << relativePath << "\"\n";
		return false;
	}
	std::cout << "\nThere are a total of " << Strings.size() << " usable words out of " << wordsInFile << " words in the file.\n\n";
	return true;
}

bool StringList::empty() const {
	return Strings.empty();
}

std::string& StringList::at(unsigned i) {
	return Strings.at(i);
}

void StringList::remove(std::string& str) {
	Strings.erase(std::remove(Strings.begin(), Strings.end(), str), Strings.end());
}

std::string& StringList::getRandomString() {
	return Strings[rand() % Strings.size()];
}

void StringList::clear() {
	Strings.clear();
}

/*
Should get called only after the string list is filled
Converts every string to lower case
Removes any strings that are too long (length > 16), too short (length < 2), or not alphabetical (h3lp, etc...)
Sorts the strings
Then removes the consecutive duplicates (had to sort the string first, so it will remove all duplicates);
Then resizes the vector
Alerts the user there were duplicates
*/
void StringList::convertAndCheckWords() {
	std::transform(Strings.begin(), Strings.end(), Strings.begin(), toLower);
	Strings.erase(std::remove_if(Strings.begin(), Strings.end(), tooLongOrTooShortOrNotAlphabetical), Strings.end());
	std::sort(Strings.begin(), Strings.end());
	std::vector<std::string>::iterator it = std::unique(Strings.begin(), Strings.end());
	int beforeResize = Strings.size();
	Strings.resize(std::distance(Strings.begin(), it));
	int duplicatedWordCount = beforeResize - Strings.size();
	if (duplicatedWordCount) {
		std::cout << "\nYou have " << duplicatedWordCount << " duplicated word" << (duplicatedWordCount > 1 ? "s" : "") << " in your file, disregarded them all.\n";
	}
}