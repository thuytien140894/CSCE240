#include "SetOfWords.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'SetOfWords' to create a set of words.
 *
 * This class has the function to create a set of words from an input file, 
 * to insert a word, to check whether a word is in the set, and to output 
 * all the words from the set.  
 *
 * Author: Duncan A. Buell
 *         modifications by Tien Ho
 * Date last modified: 26 March 2015
**/

static string TAG = "SetOfWords: ";

/******************************************************************************
 * Constructor
**/
SetOfWords::SetOfWords()
{
}

/******************************************************************************
 * Destructor
**/
SetOfWords::~SetOfWords()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'containsWord' to check for the presence of a word in the set.
 *
 * This function is declared constant and therefore is not allowed to modify
 * any class member variables.
 *
 * Parameters: a string representing a word passed by constant reference. 
 *             This string cannot be modified inside the function.
 *
 * Output: none
 *
 * Returns: true if the input word is found in the set.
**/
bool SetOfWords::containsWord(const string& word) const
{
    return (this->theWords.find(word) != this->theWords.end());
}

/******************************************************************************
 * Function 'addWord' to insert a word into the set.
 *
 * The set only inserts words that are not yet present in it.  
 *
 * Parameters: a string representing a word passed by constant reference.
 *             This string cannot be modified inside the function.
 *
 * Output: none
 *
 * Returns: true if the word is new and added.
**/
bool SetOfWords::addWord(const string& word)
{
    this->theWords.insert(word);
    
    return (!containsWord(word));
}

/******************************************************************************
 * Function 'initialize' to create a set of words from an input file.
 *
 * This function assumes that the file contains one word per line.
 *
 * Parameters: a string indicating the name of the input file.  This string 
 *             is passed by reference and cannot be changed inside the 
 *             function.
 *
 * Output: a set of words
 *
 * Returns: none
**/
void SetOfWords::initialize(const string& fileName)
{
    Scanner inStream;
    inStream.openFile(fileName);

    while(inStream.hasNext()) 
    {
        string word = inStream.next();
        this->theWords.insert(word);
    }
}

/******************************************************************************
 * Function 'toString' to output the set of words.
 *
 * This function is declared constance and therefore cannot modified any of 
 * the class variables.
 *
 * Parameters: none
 *
 * Output: none
 *
 * Returns: a string that contains all the words in the text.
**/
string SetOfWords::toString() const
{
    string output = "";

    for (set<string>::const_iterator iter = this->theWords.begin();
        iter != this->theWords.end(); ++iter)
    {
        output += (*iter) + "\n";
    }

    return output;
}
