/****************************************************************
 * Header file for the application class for the numerical
 * integration program.
 *
 * Author/copyright:  Duncan Buell
 * Submitted by: Tien Ho
 * Date: 03 February 2015
 *
**/

#ifndef TRAPEZOIDRULE_H
#define TRAPEZOIDRULE_H

#include <iostream>
using namespace std;

#include "../../Utilities/Utils.h"

#include "Function.h"

class TrapezoidMethod
{
public:
  TrapezoidMethod();
  virtual ~TrapezoidMethod();

  double computeArea();
  void readData();
  string toString();

private:
  int numberOfTraps;
  double leftPoint;
  double rightPoint;
};

#endif
