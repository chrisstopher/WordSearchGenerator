#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
#include "Constants.h"
#include "StringList.h"
#include "Grid.h"
#include "WordList.h"
#include "FileNames.h"

static const char* SORT_IN_ASCENDING_ORDER = "-sa";
static const char* SORT_IN_DESCENDING_ORDER = "-sd";
static const char* FILE_EXT = ".ws";
const int MAX_DIRECTIONS = 8;
bool userSpecifiedFlag(int argc);
bool userTypedWrong(int argc, char* argv[]);
char* getFilename(int argc, char* argv[]);
void sortIfSpecified(int argc, char* argv[], ws::WordList& words);
void createFileFormatForGame(std::string& relativePath, ws::WordList& words, ws::Grid& grid);

/*
Makes sure the arguments are correct
Create the relative path to the filename the user specified in the arguments
Populate strings list with the useable words in the file
Create the grid, wordlist, and testword
do this algorithm
	set the testwords position, direction, and string
	Make sure the first letter of test word is in an open space in the grid or on the same letter in the grid so no overwrite
	Test the word if it fits in the grid then
		insert the test word into the grid
		add the testword into the wordslist
		remove the testword from stringslist
while the word count does not go over the maximum the game can handle and stringlist is not empty
	There can be atleast 1 word to MAX_WORD_COUNT(See Constants.h) words in the format.
Then sorts if the user specified the flag too
Then creates the file format for the game to use
*/
int main(int argc, char* argv[]) {
	if (userTypedWrong(argc, argv)) {
		return 0;
	}
	std::string relativePath(FILE_PATH);
	relativePath += getFilename(argc, argv);
	srand(static_cast<unsigned int>(time(NULL)));
	ws::StringList strings;
	if (!strings.populate(relativePath)) {
		return 0;
	}
	ws::Grid grid;
	ws::WordList words;
	ws::Word testWord;
	do {
		testWord.set(grid.getRandomPosition(), rand() % MAX_DIRECTIONS, strings.getRandomString());
		while (grid.willOverwriteWord(testWord.getPosition(), testWord.getFirstLetter())) {
			testWord.getPosition().set(grid.getRandomPosition());
		}
		if (grid.canHold(testWord)) {
			grid.insert(testWord);
			words.add(testWord);
			strings.remove(testWord.getString());
		}
	} while (!words.overWordLimit() && !strings.empty());
	sortIfSpecified(argc, argv, words);
	createFileFormatForGame(relativePath, words, grid);
	strings.clear();
	words.clear();
	return 0;
}

/*
if argc < 2 then all the user typed in was the name of the program
if argc == 2 then the user typed in the name of the program and the file they want to format
if argc > 2 then the user specified 3 or more arguments and the one at argv[1] is suppose to be the flag
*/
bool userSpecifiedFlag(int argc) {
	return argc > 2;
}

/*
If you just type the name of the program then it shows the help for it
If have one argument then it is treated at the name of the file
If more than one argument then that means the the first argument is the flag and the second is the filename
SORT_IN_ASCENDING_ORDER(See Constants.h) sorts ascending alphabetically after the algorithm is done
SORT_IN_DESCENDING_ORDER(See Constants.h) sorts descending alphabetically after the algorithm is done
The filename you specify has to be under the FILE_PATH(See Constants.h)
Also checks to make sure the flags you typed in are correct
*/
bool userTypedWrong(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "\nType: (without the quotes)\n"
				  << "\t\"WordSearchGenerator.exe filename\"\n"
				  << "\t\"WordSearchGenerator.exe " << SORT_IN_ASCENDING_ORDER << " filename\" sorts the words in ascending order.\n"
				  << "\t\"WordSearchGenerator.exe " << SORT_IN_DESCENDING_ORDER << " filename\" sorts the words in decending order.\n\n"
				  << "The file has to be under the directory of " << FILE_PATH << "\n";
		return true;
	}
	if (userSpecifiedFlag(argc)) {
		if (strcmp(argv[1], SORT_IN_ASCENDING_ORDER) != 0 && strcmp(argv[1], SORT_IN_DESCENDING_ORDER) != 0) {
			std::cout << argv[1] << " is not a valid flag.\n\n"
					  << SORT_IN_ASCENDING_ORDER << " for sorting in ascending order.\n"
					  << SORT_IN_DESCENDING_ORDER << " for sorting in descending order.\n";
			return true;
		}
	}
	return false;
}

/*
Should always be called after userTypedWrong(...)
Returns the argument that should be the filename
If the user specified a flag then the filename should be the third argument[2]
if the use did not specify a flag then the filename should be the second argument[1]
*/
char* getFilename(int argc, char* argv[]) {
	if (userSpecifiedFlag(argc)) {
		return argv[2];
	}
	return argv[1];
}

/*
Checks to see if the user specified to sort either ascending or descending
*/
void sortIfSpecified(int argc, char* argv[], ws::WordList& words) {
	if (userSpecifiedFlag(argc)) {
		if (strcmp(argv[1], SORT_IN_ASCENDING_ORDER) == 0) {
			std::cout << "Sorting in ascending order.\n\n";
			words.sortAscending();
		} else if (strcmp(argv[1], SORT_IN_DESCENDING_ORDER) == 0) {
			std::cout << "Sorting in descending order.\n\n";
			words.sortDescending();
		}
	}
}

/*
Gets the relative path without the extension
makes the whole relative path lower cased
adds on the FILE_EXT(See Constants.h) which is the file extension I picked for this format
Then tries to open the file
If it opens the file then it asks you if you want to overwrite the file then if you type 'y' it will
If it does not open the file then it creates it
Puts all the words in there that fit into the grid - which is what the game takes in
Puts the grid in there too for no reason other than debug - the game does not use the grid
*/
void createFileFormatForGame(std::string& relativePath, ws::WordList& words, ws::Grid& grid) {
	relativePath = getFilePathWithoutExt(relativePath);
	std::transform(relativePath.begin(), relativePath.end(), relativePath.begin(), tolower);
	relativePath += FILE_EXT;
	bool createFile = true;
	std::string filename = getFileNameWithExt(relativePath);
	std::string filepath = getFilePathOnly(relativePath);
	std::ifstream file(relativePath.c_str());
	if (file) {
		file.close();
		char input;
		std::cout << "The file: " << filename << " already exists in \"" << filepath << "\".\n"
				  << "Do you want to overwrite the file? Y/N ";
		std::cin >> input;
		input = toupper(input);
		if (input != 'Y') {
			std::cout << "\nThe file: " << filename << " was not overwritten.\n";
			createFile = false;
		}
	}
	if (createFile) {
		std::ofstream outFile(relativePath.c_str());
		outFile << words;
		outFile.close();
		std::cout << "\nThe file: " << filename << " has been created in \"" << filepath << "\".\n";
	}
}