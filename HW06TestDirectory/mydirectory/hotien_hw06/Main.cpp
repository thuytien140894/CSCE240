#include "Main.h"

/*******************************************************************************
12345678901234567890123456789012345678901234567890123456789012345678901234567890
 * Main program for Homework 2.
 *
 * This program sets up and runs a queueing model simulation of an election.
 * The program creates an instance of 'Queue', initializes the instance from 
 * an input file, echoes the input, and then runs the simulation.
 *
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Submitted by: Tien Ho
 * Date: 13 April 2015
**/

int main(int argc, char *argv[])
{
  int howManyMachinesLower = 0;
  int howManyMachinesUpper = 0;
  int howManyVoters = 0;
  int numberOfTimeSteps = 0;
  double voteTimeMean = 0.0;
  double voteTimeDev = 0.0;

  Queue queue;

  //Here we assume that there will be 6 numbers to be read from the file.
  //The program will crash if there are fewer than 6 numbers in the file.
  cin >> howManyVoters >> howManyMachinesLower >> howManyMachinesUpper
      >> numberOfTimeSteps >> voteTimeMean >> voteTimeDev;

  //When you call the function 'initialize', all the parameters need to be
  //greater than or equal to 0.  Their positivity is checked in the function.
  queue.initialize(howManyVoters, howManyMachinesLower, howManyMachinesUpper,
                   numberOfTimeSteps,
                   voteTimeMean, voteTimeDev);

  cout << "Voters: " << howManyVoters
       << ", timeSteps: " << numberOfTimeSteps
       << ", machines: " << howManyMachinesLower << " to " << howManyMachinesUpper
       << ", mean & dev vote times: " << voteTimeMean << " " << voteTimeDev
       << endl;

  queue.runSimulation();

  return 0;
}

