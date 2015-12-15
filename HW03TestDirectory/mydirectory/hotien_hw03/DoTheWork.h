/****************************************************************
 * Homework 3 header file for the application class.
 *
 * Author/copyright:  Duncan Buell
 * Submitted by: Tien Ho
 * Date: 17 February 2015
 *
**/

#ifndef DOTHEWORK_H
#define DOTHEWORK_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "../../Utilities/Utils.h"
#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

#include "Record.h"

class DoTheWork
{
public:
    DoTheWork();
    virtual ~DoTheWork();

    void readData(Scanner& dataStream);
    string toString();
    string toStringByName();
    string toStringByNumber();

private:
    vector<Record> theData;

    void sortRecords(string howSort);
};

#endif
