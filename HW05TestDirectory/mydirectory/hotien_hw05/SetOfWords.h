/****************************************************************
 * Header file for the 'SetOfWords' class.
 *
 * Author/copyright:  Duncan Buell
 * Submitted by: Tien Ho
 * Date: 26 March 2015
 *
**/

#ifndef SETOFWORDS_H
#define SETOFWORDS_H

#include <iostream>
#include <set>
using namespace std;

#include "../../Utilities/Utils.h"
#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

class SetOfWords
{
public:
    SetOfWords();
    virtual ~SetOfWords();

    set<string> getTheWords();
    void initialize(const string& fileName);
    bool addWord(const string& word);
    bool containsWord(const string& word) const;
    string toString() const;

    friend const ostream& operator <<(ostream& outputStream, const SetOfWords& theSet);

private:
    set<string> theWords;
};

#endif
