/****************************************************************
 * Header file for the random number generator for the queueing
 * theory program.
 *
 * Author/copyright:  Duncan Buell
 * Submitted by: Tien Ho
 * Date: 13 April 2015
 *
**/

#ifndef MYRANDOM_H
#define MYRANDOM_H

#include <iostream>
#include <random>
#include <cassert>
using namespace std;

#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

#undef NDEBUG

class MyRandom
{
public:
  MyRandom();
  virtual ~MyRandom();

  double randomNormal(double mean, double dev);
  double randomUniformDouble(double lower, double upper);
  int randomUniformInt(int lower, int upper);

private:
  std::default_random_engine generator;
};

#endif
