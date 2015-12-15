#include "Dictionary.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Dictionary' to create a dictionary for the indexing program.
 *
 * This class is derived from the base class 'SetOfWords'.  It creates 
 * a dictionary and has the method to add new words to the dictionary given 
 * that the word is a not a plural of a word that already exists in the 
 * dictionary.
 *
 * Author: Duncan A. Buell
 *         modifications by Tien Ho
 * Date last modified: 26 March 2015
**/

static string TAG = "Dictionary: ";

/******************************************************************************
 * Constructor
**/
Dictionary::Dictionary() : SetOfWords()
{
}

/******************************************************************************
 * Destructor
**/
Dictionary::~Dictionary()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'addWord' to add new words to the dictionary.
 *
 * This function redefines the function in the base class and only adds the 
 * word if it is not the plural of a word already present in the dictionary.
 * If the plural form of a word that is not in the dictionray is encountered 
 * first, then both its plural and singular forms are added.  
 *
 * Parameters: a string indicating a word to be added
 *
 * Output: none
 *
 * Returns: the input word
**/
string Dictionary::addWord(string word)
{
    if (!tokenIsPlural(word))
    {
        SetOfWords::addWord(word);
    }

    return word;
}

/******************************************************************************
 * Function 'tokenIsPlural' to check whether a word is plural.  
 *
 * This function assumes that plural words end with an 's'.  We first remove 
 * the ending 's' and then checks whether the reduced word appears in the 
 * dictionary.  If it does, then the word is considered plural.  If not, 
 * the word is considered not plural and therefore is eligible to be added to
 * the dictionary. 
 *
 * Parameters: a string
 *
 * Output: none
 *
 * Returns: true if the word is plural.
**/
bool Dictionary::tokenIsPlural(string token) 
{
    string lastCharacter = "";
    string word = "";

    lastCharacter = *(token.rbegin());

    if (lastCharacter == "s") 
    {
        word = token.substr(0, token.length()-1);
    }

    return (containsWord(word));
}
