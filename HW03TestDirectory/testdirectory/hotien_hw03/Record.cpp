#include "Record.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Record' for a single phone book record in a tree.
 *
 * This class has the functions to tokenize each phone book items into 
 * properties for each Record instance, to compare the surname and phone
 * numbers of two Record instances used for sorting, and then to return the 
 * formatted output for the Record.  
 *
 * Author: Duncan A. Buell
 *         modifications by Tien Ho
 * Date last modified: 17 February 2015
**/

static const string TAG = "Record: ";

/******************************************************************************
 * Constructor
**/
Record::Record()
{
}

/******************************************************************************
 * Destructor
**/
Record::~Record()
{
}

/******************************************************************************
 * Accessor 'getPhoneNumber' to access the phone number.
 *
 * Parameters: none
 *
 * Output: none
 *
 * Returns: a string indicating the phone number
**/
string Record::getPhoneNumber()
{
    return phoneNumber;
}

/******************************************************************************
 * Accessor 'getSurname' to access the surname.
 *
 * Parameters: none
 * 
 * Output: none
 *
 * Returns: a string indicating the surname
**/
string Record::getSurname()
{
    return surname;
}

/******************************************************************************
 * Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'compareNumber' to compare the phone numbers between two instances.
 * 
 * This function makes the comparison based on the ASCII code.  The one with a 
 * smaller code is supposed to come before the other one.
 *
 * Parameters: a Record instance
 *
 * Output: none
 *
 * Returns: true if the ASCII code of the phone number of the instance is 
 * greater than that of the parameter.
**/
bool Record::compareNumber(Record that)
{
    return (this->phoneNumber > that.phoneNumber);
}

/******************************************************************************
 * Function 'compareName' to compare the surnames between two instances.
 * 
 * This function makes the comparison based on the ASCII code.  The one with a 
 * smaller code is supposed to come before the other one.
 *
 * Parameters: a Record instance
 *
 * Output: none
 *
 * Returns: true if the ASCII code of the surname of the instance is greater 
 * than that of the parameter.
**/
bool Record::compareName(Record that)
{
    return (this->surname > that.surname);
}

/******************************************************************************
 * Function 'readData' to tokenize the data into the class properties.
 *
 * This function takes an argument of a data string and tokenizes it into
 * forename, othername, surname, and phone number using the 'find', 'rfind', 
 * and 'substr' methods of the class 'string'.  In this case, taking into 
 * consideration that the string is delimited by spaces, the first token
 * is the forename; the last token is the phone number; the penultimate token 
 * is the surname; and any intermediate tokens are taken as othername.
 * 
 * The tokens are then used to set the class variables.
 *
 * Parameters: a string of data read from the standard stream
 *
 * Output: none except a Record instance with its properties set to the data
 * tokens
 *
 * Returns: none
**/
void Record::readData(string entry)
{
    string forename = "";
    string othername = "";
    string surname = "";
    string phoneNumber = "";

    int firstSpace = entry.find(" ");
    int lastSpace = entry.rfind(" ");
    int secondLastSpace = entry.rfind(" ", lastSpace - 1);
    forename = entry.substr(0, firstSpace);
    phoneNumber = entry.substr(lastSpace + 1, 8);
    surname = entry.substr(secondLastSpace + 1, 
                           lastSpace - (secondLastSpace + 1));

    if (firstSpace == secondLastSpace)
        othername = "";
    else 
        othername = entry.substr(firstSpace + 1, 
                                 secondLastSpace - (firstSpace + 1));

    this->forename = forename;
    this->othername = othername;
    this->surname = surname;
    this->phoneNumber = phoneNumber;
} 

/******************************************************************************
 * Function 'toString' to return the formatted data in the class.
 *
 * Parameters: none
 *
 * Output: none
 *
 * Returns: a string that lists the forename, othername, surname, and phone
 * number of a Record instance.
**/
string Record::toString()
{
    string s = "";

    s += this->forename;
    if (this->othername != "")
    {
        s += " " + this->othername;
    } 
    s += " " + this->surname;

    s += " " + this->phoneNumber;
    s += "\n";

    return s;
} 
