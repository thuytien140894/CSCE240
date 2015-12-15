#include "Stoplist.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Stoplist' to create a stoplist for the indexing program.  
 *
 * This class is derived from the base class 'SetOfWords'.  It creates 
 * a set of stop words that are not used as index terms.  
 * 
 * Author: Duncan A. Buell
 * Submitted by: Tien Ho
 * Date last modified: 26 March 2015
**/

static string TAG = "Stoplist: ";

/******************************************************************************
 * Constructor
**/
Stoplist::Stoplist() : SetOfWords()
{
}

/******************************************************************************
 * Destructor
**/
Stoplist::~Stoplist()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/
