#include "Index.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Index' to index all the words in the input file by line numbers.
 *
 * This class contains functions to reads the input text line by line,
 * tokenizes each line, and then index each token by line numbers.  The class
 * also has the function to format and output the indexed map.
 *
 * Author: Duncan A. Buell
 *   	   modifications by Tien Ho
 * Date last modified: 26 March 2015
**/

static string TAG = "Index: ";

/******************************************************************************
 * Constructor
**/
Index::Index()
{
}

/******************************************************************************
 * Destructor
**/
Index::~Index()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'createIndex' to index a standard file.
 *
 * This function reads the input text line by line and then invokes the 
 * private function 'parseLine' to tokenize the line and index all the words.
 *
 * Parameters: a standard text, a dictionary, and a stoplist, all of which 
 *             are passed by reference.  The stoplist cannot be modified
 *             inside this function.
 *
 * Output: a map that contains all the indexed words in the input text
 *
 * Returns: none
**/
void Index::createIndex(Scanner& inStream, Dictionary& dictionary,
                                           const Stoplist& stoplist)
{
    int lineCounter = -1;

    while(inStream.hasNext())
    {
        ScanLine inputLine;
        string line = inStream.nextLine();
        inputLine.openString(line);

        lineCounter++;
		
        parseLine(lineCounter, inputLine, dictionary, stoplist);
    }
}

/******************************************************************************
 * Function 'parseLine' to parse each line and index each token.
 *
 * This function skips all the tokens found between << and >>, including the 
 * the brackets themselves, assuming that the two brackets are on the same 
 * line.  A token to be indexed has to be non-numeric.  Any token consisting
 * of entirely digits 0 through 9 as well as the decimal point is skipped.  
 * Also, all the words that are found in the stoplist are not to be indexed.  
 *
 * A token is first added to the dictionary given that it is not a plural of 
 * a word that is already present in the dictionary.  If the plural of a word
 * not in the dictionary is encountered prior to its singular, then both 
 * the plural and the singular of a word are added to the dictionary.  
 *
 * If the token is already indexed, then the new line number is added to its 
 * indexed set.  Otherwise, the token is inserted into the map along with its
 * first indexed line number.
 *
 * Parameters: lineCounter is an integer indicating the line number.
 *	       scanLine (a ScanLine instance representing a line of the 
 *	       text), a dictionary, and a stoplist are passed by reference.
 *             The stoplist instance cannot be modified inside this function.
 *
 * Output: a map that contains all the indexed words in a line.
 *
 * Returns: none
**/
void Index::parseLine(int lineCounter, ScanLine& scanLine,
                      Dictionary& dictionary, const Stoplist& stoplist)
{
    while (scanLine.hasNext())
    {
        string token = scanLine.next();

        while (token == "<<") 
        {
            while (token != ">>")
            {
                token = scanLine.next();
            }

            token = scanLine.next();
            lineCounter++;
        }

        bool condition1 = !tokenIsNumeric(token);
        bool condition2 = (!stoplist.containsWord(token));
        if (condition1 && condition2) 
        {
            token = dictionary.addWord(token);

            map<string, set<int> >::const_iterator iter = 
									
            this->theIndex.find(token);
            if (iter != this->theIndex.end())
            {
                set<int> lines = iter->second;
                lines.insert(lineCounter);
                this->theIndex[token] = lines;
            }
            else 
            {
                set<int> setOfLines;
                setOfLines.insert(lineCounter);
                this->theIndex.insert(std::pair<string, 
                set<int> >(token, setOfLines));
            }		
        }
    }
}

/******************************************************************************
 * Function 'tokenIsNumeric' to check whether a token is entirely numeric.  
 *
 * This function uses one of the string methods to search for characters in 
 * in the token that does not match with any of the digits from 0-9 as well as
 * the decimal point.  The token is determined non numeric if this method
 * returns string::npos.
 *
 * Parameters: a string indicating a token
 *
 * Output: none
 *
 * Returns: true if no numeric character and decimal points are found.
 *
**/
bool Index::tokenIsNumeric(string token)
{
    std::size_t nonNumber = token.find_first_not_of("0123456789.");
    return (nonNumber == std::string::npos);
}


/******************************************************************************
 * Function 'toString' to format the output of the indexed list.
 *
 * This function loops through the map that stores all indexed words and their
 * corresponding set of line numbers.  The Utilities class is utilized 
 * to format the output so that the indexed words appear on the left-hand side
 * followed by all the line numbers in which they are found.
 *
 * Parameters: none
 *
 * Output: none
 *
 * Returns: a string that contains all the indexed words and their line 
 * numbers.
 *
**/
string Index::toString()
{
    string output = "";

    map<string, set<int> >::const_iterator iter;
    for (iter = this->theIndex.begin(); 
		iter != this->theIndex.end(); ++iter)
    {
        string word = iter->first;
        set<int> setOfLines = iter->second;
        output += Utils::Format(word, 30, "left");

        set<int>::const_iterator iter2;
        for (iter2 = setOfLines.begin(); iter2 != setOfLines.end(); ++iter2)
        {
            output += Utils::Format((*iter2), 5);
        }

        output += '\n';
    }

    return output;
}
