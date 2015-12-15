#include "SetOfWords.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Operators' to overload the operator '<<' for the classes Index and 
 * SetOfWords.  
 *
 * Author: Duncan A. Buell
 * 		   modifications by Tien Ho
 * Date last modified: 26 March 2015
**/

static string TAG = "Operators: ";

/******************************************************************************
 * Overloaded operator '<<' for 'SetOfWords' instances.
 *
 * This invokes the 'toString' function in the 'SetOfWords' class.
 *
 * Parameters: a standard stream and a 'SetOfWords' instance both passed by 
 *             reference.  The 'SetOfWords' instance cannot be changed inside  
 *             the function.
 *
 * Output: none
 *
 * Returns: a stream with all the words from the set.
**/
ostream& operator <<(ostream& outputStream, const SetOfWords& theSet)
{
    outputStream << theSet.toString();
    return outputStream;
}

/******************************************************************************
 * Overloaded operator '<<' for 'Index' instances.
 *
 * This invokes the 'toString' function in the 'Index' class.
 *
 * Parameters: a standard stream and an 'Index' instance both passed by 
 *             reference.  The 'Index' instance cannot be changed inside the 
 *             function.
 *
 * Output: none
 *
 * Returns: a stream with all the indexed word from the Index class.
**/
ostream& operator <<(ostream& outputStream, const Index& theIndex)
{
    outputStream << theIndex.toString();
    return outputStream;
}
