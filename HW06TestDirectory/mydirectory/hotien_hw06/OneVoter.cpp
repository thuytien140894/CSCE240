#include "OneVoter.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'OneVoter' to establish basic voting information for each voter.
 *
 * This is a data payload for the variables of the class. There is nothing
 * here except for accessors and a 'toString', except for two functions that:
 *   assign a machine, start time, etc., to the instance
 *   assign a dummy ending machine number to a voter done voting 
 *
 * Author: Duncan A. Buell
 *         modifications by Tien Ho
 * Date last modified: 13 April 2015
**/

/******************************************************************************
 * Constructor
**/
OneVoter::OneVoter()
{
}

/******************************************************************************
 * Constructor to initialize the basic voting information for a voter.
 *
 * A voter instance has its sequenceNumber, timeArrival, and timeVoteDuration
 * assigned to the values of the corresponding parameters.  The other
 * attributes are assigned to the dummy begin constant to indicate their 
 * not-yet-voting status.
 *
 * Parameters: sequence, arrival, and duration are integers. 
 *             sequence - the voter's ID.
 *             arrival - the arrival time.
 *             duration - the time it takes for a voter to vote.
 * Output: none
 * Returns: none
**/
OneVoter::OneVoter(int sequence, int arrival, int duration)
{
  //the sequence number is always positive because it is determined by
  //the total number of voters.
  this->sequenceNumber = sequence;
  //the arrival time is always positive because it is uniformly 
  //generated from a set of positive integers.
  this->timeArrival = arrival;
  //the voting duration is always positive because it is derived from a 
  //a normal distribution with positive deviation.
  this->timeVoteDuration = duration;
  this->machineNumber = DUMMYBEGIN;
  this->timeStartVoting = DUMMYBEGIN;
  this->timeDoneVoting = DUMMYBEGIN;
  this->timeWaiting = DUMMYBEGIN;
}

/******************************************************************************
 * Destructor
**/
OneVoter::~OneVoter()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * Accessor for 'machineNumber'.
 *
 * Parameters: none
 * Output: none
 * Returns: an integer indicating the machine number
**/
int OneVoter::getMachineNumber()
{
  return this->machineNumber;
}

/******************************************************************************
 * Accessor for 'timeArrival'
 *
 * Parameters: none
 * Output: none
 * Returns: an integer indicating the arrival time
**/
int OneVoter::getTimeArrival()
{
  return this->timeArrival;
}

/******************************************************************************
 * Accessor for 'timeDoneVoting'
 *
 * Parameters: none
 * Output: none
 * Returns: an integer indicating the time that a voter finishes voting
**/
int OneVoter::getTimeDoneVoting()
{
  return this->timeDoneVoting;
}

/******************************************************************************
 * Accessor for 'timeWaiting'
 *
 * Parameters: none
 * Output: none
 * Returns: an integer indicating the waiting time
**/
int OneVoter::getTimeWaiting()
{
  return this->timeWaiting;
}

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'assignMachine' to assign a voter to a voting machine.
 *
 * This function sets the starting time and accordingly determines the waiting 
 * and finish time for a voter instance.
 * 
 * Parameters: machineNumber and startTime are integers.
 *      machineNumber - the machine number assigned to a voter
 *      startTime - the time when a voter is allocated a machine
 * Output: none
 * Returns: none
**/
void OneVoter::assignMachine(int machineNumber, int startTime)
{
  this->machineNumber = machineNumber;
  this->timeStartVoting = startTime;
  //the 'timeStartVoting' will be always greater than or equal to the
  //'timeArrival'.  The function 'runSimulation2' in the Queue class only
  //assigns the machine to a pending voter if the current time step
  //is greater than or equal to the arrival time.  Therefore, the 
  //'timeWaiting' is always positive.
  this->timeWaiting = this->timeStartVoting - this->timeArrival;
  this->timeDoneVoting = this->timeStartVoting + this->timeVoteDuration;
}

/******************************************************************************
 * Function 'doneVoting' to unassign a voter from a voting machine.
 *
 * This function sets the the machine number to the dummy end constant when 
 * a voter is done voting.
 *
 * Parameters: none
 * Output: none
 * Returns: none
**/
void OneVoter::doneVoting()
{
  this->machineNumber = DUMMYEND; 
  
}

/******************************************************************************
 * Function 'toString' to output all the voting information for one voter.
 *
 * This function uses the Utilities class to format the labels and values for 
 * all the voter attributes.
 *
 * Parameters: none
 * Output: none
 * Returns: a string that contains the labels and values for all the voter
 *          attributes.
**/
string OneVoter::toString()
{
  string s = "";

  s += Utils::Format("seq#", 6, "left") 
    + Utils::Format("mach#", 6, "left") + Utils::Format("arr", 6, "left")
    + Utils::Format("start", 6, "left") + Utils::Format("dur", 6, "left")
    + Utils::Format("done", 6, "left") + Utils::Format("wait", 6, "left");

  s += Utils::Format(this->sequenceNumber, 3)
    + Utils::Format(this->machineNumber, 5) 
    + Utils::Format(this->timeArrival, 5)
    + Utils::Format(this->timeStartVoting, 5)
    + Utils::Format(this->timeVoteDuration, 5)
    + Utils::Format(this->timeDoneVoting, 5)
    + Utils::Format(this->timeWaiting, 5);

  s += "\n";
  
  return s;
}
