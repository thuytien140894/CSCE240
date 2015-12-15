/****************************************************************
 * Header file for the application class for the queueing
 * theory program.
 *
 * Author/copyright:  Duncan Buell
 * Submitted by: Tien Ho
 * Date: 13 April 2015
 *
**/

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <random>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

#include "../../Utilities/Utils.h"

#include "OneVoter.h"
#include "MyRandom.h"

class Queue
{
public:
  Queue();
  virtual ~Queue();

  void initialize(int howManyVoters,
                  int howManyMachinesLower, int howManyMachinesUpper,
                  int numberOfTimeSteps,
                  double voteTimeMean, double voteTimeDev);
  void runSimulation();
  string toString();

private:
  int howManyVoters;
  int howManyMachinesLower;
  int howManyMachinesUpper;

  vector<int> freeMachines;

  multimap<int, OneVoter> votersBackup;
  multimap<int, OneVoter> votersPending;
  multimap<int, OneVoter> votersVoting;
  multimap<int, OneVoter> votersDoneVoting;

  MyRandom random;

  void computeMeanAndDev(double& mean, double& dev);
  void doStatistics();
  void runSimulation2(int howManyMachines);
};

#endif
