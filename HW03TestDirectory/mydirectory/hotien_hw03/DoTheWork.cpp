#include "DoTheWork.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Homework 3 'DoTheWork' application class.
 *
 * This class has the functions to read data from the standard stream into 
 * a vector of Record instances and sort the Records either by surname or 
 * by phone number.  
 *
 * Author: Duncan A. Buell
 *         modifications by Tien Ho
 * Date last modified: 17 February 2015
**/

static const string TAG = "DoTheWork: ";

/******************************************************************************
 * Constructor
**/
DoTheWork::DoTheWork()
{
}

/******************************************************************************
 * Destructor
**/
DoTheWork::~DoTheWork()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'readData' to read data from standard input.
 *
 * In this case, the given input data is a list of phone number items, one 
 * item per line.  Each line of data is passed into the function 'readData'
 * of the class Record.  The data is read line by line into a vector of 
 * Record instances.  
 *
 * Parameters: a data stream of type Scanner passed by reference
 *
 * Output: none except for a vector of Record instances
 *
 * Returns: none
**/
void DoTheWork::readData(Scanner& dataStream)
{
    string entry = "";

#ifdef EBUG
    cout << TAG << "enter readData\n"; 
#endif
 
    while (dataStream.hasNext())
    {
    	Record person;
        entry = dataStream.nextLine();
        person.readData(entry);

       	this->theData.push_back(person);
    }

#ifdef EBUG
    cout << TAG << "leave readData\n"; 
#endif
}

/******************************************************************************
 * Function 'sortRecords' to sort the data by surname and by phone number.
 *
 * In this case, the sorting is accomplished using the bubble sorting
 * algorithm  which repeatedly traverses through the vector of Records and 
 * compares each pair of adjacent items according to either their surnames or 
 * their phone numbers using the ASCII code. The two items that are in the 
 * wrong order are swapped.  The pass through the list is repeated until all 
 * the items are in order and no more swaps are needed.  The sorting is 
 * optimized by reducing the number of items to compare by one for each
 * succeeding traversal because the n-th pass puts the n-th largest element 
 * at its right place.  
 *
 * Parameters: a string indicating whether to sort by surname or by phone 
 * number.
 * 
 * Output: none except for a sorted vector of Records.
 *
 * Returns: none
**/
void DoTheWork::sortRecords(string howSort)
{
    int numberOfRecords = static_cast<int>(this->theData.size()); 

#ifdef EBUG
    cout << TAG << "enter sortRecords\n"; 
#endif
    
    if (howSort == "surname") 
    {    
        while (numberOfRecords >= 0)
        {
            for (int i = 0; i < numberOfRecords - 1; i++)
	    {
                if (this->theData[i].compareName(this->theData[i+1]))
                {
                    Record temp = this->theData[i];
                    this->theData[i] = this->theData[i+1];
                    this->theData[i+1] = temp;
                }
	    }   
 
	    numberOfRecords -= 1;
        } 
    }

    else if (howSort == "phone number")
    {
    	while (numberOfRecords >= 0)
        {
            for (int i = 0; i < numberOfRecords - 1; i++)
	    {
                if (this->theData[i].compareNumber(this->theData[i+1]))
                {
                    Record temp = this->theData[i];
                    this->theData[i] = this->theData[i+1];
                    this->theData[i+1] = temp;
                }
	    }   
 
	    numberOfRecords -= 1;
        } 
    }

#ifdef EBUG
    cout << TAG << "leave sortRecords\n"; 
#endif
}

/******************************************************************************
 * Function 'toString' to output all the Record instances in the vector.
 *
 * We traverse through all the Record instances stored in the vector and 
 * display their forenames, othernames, surnames, and phone numbers.
 *
 * The Utilities class is used to format the output.
 *
 * Parameters: none
 *
 * Output: none
 *
 * Returns: a string with all the Record instances.
**/
string DoTheWork::toString()
{
    string output = "";

#ifdef EBUG
    cout << TAG << "enter toString\n"; 
#endif

    for (UINT i = 0; i < this->theData.size(); i++) 
    {
        output += "Record" + Utils::Format(i,4) + ": ";
        output += this->theData[i].toString();
        output += "\n";
    } 

    output += "\n";

#ifdef EBUG
    cout << TAG << "leave toString\n"; 
#endif

    return output;
}

/******************************************************************************
 * Function 'toStringByName' to output the data sorted by surname.
 *
 * This function invokes the function 'sortRecords' with the parameter of
 * "surname" to sort the Record instances in the vector by surname using 
 * bubble sort.
 *
 * Parameters: none
 *
 * Output: none
 *
 * Returns: a string that lists all the properties for each Record instance.
**/
string DoTheWork::toStringByName()
{ 
#ifdef EBUG
    cout << TAG << "enter toStringByName\n"; 
#endif
  
    sortRecords("surname");

#ifdef EBUG
    cout << TAG << "leave toStringByName\n"; 
#endif

    return toString();
}

/******************************************************************************
 * Function 'toStringByNumber' to output the data sorted by phone number.
 *
 * This function invokes the function 'sortRecords' with the parameter of 
 * "phone number" to sort the Record instances by phone number.
 *
 * Parameters: none
 *
 * Output: none
 *
 * Returns: a string that lists all the properties for each Record instance.
**/
string DoTheWork::toStringByNumber()
{
#ifdef EBUG
    cout << TAG << "enter toStringByNumber\n"; 
#endif
  
    sortRecords("phone number");

#ifdef EBUG
    cout << TAG << "leave toStringByNumber\n"; 
#endif
  
    return toString();
}
