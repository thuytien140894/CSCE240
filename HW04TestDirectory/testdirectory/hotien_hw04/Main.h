/****************************************************************
 * Rather generic header file for the main that includes the 
 * 'Utilities' code.
 *
 * Author/copyright:  Duncan Buell
 * Submitted by: Tien Ho
 * Date: 05 March 2015
 *
**/
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
using namespace std;

#include "../../Utilities/Utils.h"
#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

#include "Traversal.h"

class Main
{
public:
  int main();
  virtual ~Main();

private:

};

#endif // MAIN_H
