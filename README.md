## Word Search Generator

## Requirements
User creates a file with any words they want to find.  
The file has to be created under **resources/files/**

##How to use

### CLI only:
Navigate to the directory the file is in  
Assuming you named the executable file  WordSearchGenerator.exe  
To Show the help/options:

    WordSearchGenerator.exe

To convert a file:

    WordSearchGenerator.exe filename

To convert a file and sort it in ascending order:

    WordSearchGenerator.exe -sa filename

To convert a file and sort it in descending order:

    WordSearchGenerator.exe -sd filename

##How it works
Takes the words from the file the user specifies  
Puts the useable words into the grid  
Creates between 1 and 25 words  
Outputs the words into the file the user specifies with the extension of .ws

##To do
* Allow the user to chain together arguments from the command line

>Example:

>     WordSearchGenerator.exe file1 file2 file3 ...

>Would allow the program to make formats for all files specified.

>Another Example:

>     WordSearchGenerator.exe file1 -sa file2 -sd file3 ...

>Would allow the program to make formats for all files specified and sort them if specified.  

* Allow the user to overwrite the specified file typed in if there are any duplicated/unusable words.  
* Allow the user to specify how many words they want in the grid ranging between 1 and 25 inclusive.

##Bugs
If the words in the file that the user specified are just long enough to fit into the grid, but there are a lot of them it might go into an infinite loop because the words will not be able to be placed into the grid.  
Some long words are okay just keep them at a minimum.  
**To combat this:**  
The smaller the words the faster the algorithm will be and less likely the chance of it going into an infinite loop.  
The more variety of words you have in the file means less chance of an infinite loop too.  
e.g. If the user is going to have 25 words in the grid then its best to add 30 or more so the algorithm has more words to pick from.

**Sort of a bug:**  
The algorithm allows words to be inside words.  
Example:  
Say the word 'awesome' is in the grid like this.
<table>
    <tr>
        <td> </td>
        <td>0</td>
        <td>1</td>
        <td>2</td>
        <td>3</td>
    </tr>
    <tr>
        <td>0</td>
        <td>a</td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
    <tr>
        <td>2</td>
        <td>w</td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
    <tr>
        <td>3</td>
        <td>e</td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
    <tr>
        <td>4</td>
        <td>s</td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
    <tr>
        <td>5</td>
        <td>o</td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
    <tr>
        <td>6</td>
        <td>m</td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
    <tr>
        <td>7</td>
        <td>e</td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
</table>
Then the generator picks the word 'some' and it starts at 0, 4 going south.  
The generator makes sure if there is a character there it does not overwrite it with a different one and allows the word to be put there because they are the same letters.  
<table>
    <tr>
        <td> </td>
        <td>0</td>
        <td>1</td>
        <td>2</td>
        <td>3</td>
    </tr>
    <tr>
        <td>0</td>
        <td>a</td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
    <tr>
        <td>2</td>
        <td>w</td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
    <tr>
        <td>3</td>
        <td>e</td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
    <tr>
        <td>4</td>
        <td><b>s</b></td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
    <tr>
        <td>5</td>
        <td><b>o</b></td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
    <tr>
        <td>6</td>
        <td><b>m</b></td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
    <tr>
        <td>7</td>
        <td><b>e</b></td>
        <td> </td>
        <td> </td>
        <td> </td>
    </tr>
</table>
As you can see the word 'some' will fit perfectly at that position.  
So when the user plays the game, some words might be inside of other words.

