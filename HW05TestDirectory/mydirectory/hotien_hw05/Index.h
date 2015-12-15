/****************************************************************
 * Header file for the application class for the indexing program.
 *
 * Author/copyright:  Duncan Buell
 * Submitted by: Tien Ho
 * Date: 26 March 2015
 *
**/

#ifndef INDEX_H
#define INDEX_H

#include <iostream>
#include <map>
#include <set>
using namespace std;

#include "../../Utilities/Utils.h"
#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

#include "Dictionary.h"
#include "Stoplist.h"

class Index
{
public:
    Index();
    virtual ~Index();

    void initialize();
    void createIndex(Scanner& inStream, Dictionary& dictionary,
                                      const Stoplist& stoplist);
    string toString();
    string toStringLocalStoplist();

    friend const ostream& operator <<(ostream& outputStream, const Index& theIndex);

private:
    set<string> localStoplist;

    map<string, set<int> > theIndex;

    void parseLine(int lineCounter, ScanLine& scanLine, Dictionary& dictionary,
                                                      const Stoplist& stoplist);
    bool tokenIsNumeric(string token);
};

#endif
