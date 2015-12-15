/****************************************************************
 * Header file for the phone book record for homework 3.
 *
 * Author/copyright:  Duncan Buell
 *                    modifications by Tien Ho
 * Date: 17 February 2015
 *
**/

#ifndef RECORD_H
#define RECORD_H

#include <iostream>
using namespace std;

#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

class Record
{
public:
    Record();
    virtual ~Record();

    bool compareName(Record that);
    bool compareNumber(Record that);
    string getSurname();
    string getPhoneNumber();
    void readData(string entry);
    string toString();

private:
    string forename;
    string othername;
    string surname;
    string phoneNumber;
};

#endif
