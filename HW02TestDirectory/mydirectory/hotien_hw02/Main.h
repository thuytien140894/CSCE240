/****************************************************************
 * Rather generic header file that includes the 'Utilities' code.
 *
 * Author/copyright:  Duncan Buell
 * Submitted by: Tien Ho
 * Date: 03 February 2015
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

#include "TrapezoidMethod.h"

class Main
{
public:
  int main();
  virtual ~Main();

private:

};

#endif // MAIN_H
