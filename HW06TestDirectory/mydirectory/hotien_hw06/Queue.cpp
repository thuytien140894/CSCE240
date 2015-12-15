#include "Queue.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Queue' to run a 'discrete event' simulation for voting that keeps
 * track of the voting progress for a given number of voters and voting 
 * machines.  
 *
 * This class has functions to instantiate the appropriate number of voters 
 * by uniformly and randomly generating the arrival and voting times, 
 * respectively.  Then a voting simulation is implemented to track the voting 
 * progress by moving the voters from the pending multimap through the voting
 * multimap to to done voting multimap provided their arrival and voting 
 * times.  
 * 
 * Author: Duncan A. Buell
 *         modifications by Tien Ho
 * Date last modified: 13 April 2015
**/

/******************************************************************************
 * Constructor
**/
Queue::Queue()
{
}

/******************************************************************************
 * Destructor
**/
Queue::~Queue()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'computeMeanAndDev' to compute the mean and standard deviation 
 * the 'votersDoneVoting' wait times.
 *
 * This function iterates through the 'votersDoneVoting' multimap to first
 * calculate the total wait time.  The mean is computed by:
 *      mean = (total wait time) / (total number of voters)
 *    
 * We perform another iteration through the 'votersDoneVoting' multimap to
 * calculate the total squared difference, which follows:
 *      squared difference = [(individual wait time) - (waiting time mean)]^2
 *
 * The average of all squared differences give the variance, which measures 
 * how spread out the wait times are.  The standard deviation is the 
 * squared root of the variance.
 *
 * Parameters: mean and dev are double passed by reference
 *      mean - the average wait time
 *      dev - the standard deviation of the wait time
 * Output: none
 * Returns: none
**/
void Queue::computeMeanAndDev(double& mean, double& dev)
{
  double totalWaitTime = 0.0;
  double totalSquaredDifference = 0.0;

  cout << "enter computeMeanAndDev" << endl;

  multimap<int, OneVoter>::iterator iter;
  //This loop is safe because it is controlled by the functions of the
  //container.  In this case, the loop is limited between the
  //the beginning and the end of the multimap.
  for (iter = this->votersDoneVoting.begin(); 
       iter != this->votersDoneVoting.end(); ++iter) 
  {
    OneVoter voter = iter->second;
    totalWaitTime += voter.getTimeWaiting();
  }

  //'howManyVoters' is always positive because this condition has 
  //already been verified in the function 'initialize'.  We need
  //to call the function 'initialize' prior to this function.
  //That way, we do not have to worry about the exception of
  //dividing by zero.
  mean = totalWaitTime/(this->howManyVoters);

  //This loop is safe because it is controlled by the functions of the
  //container.  In this case, the loop is limited between the
  //the beginning and the end of the multimap.  This function needs
  //to be called after 'runSimulation2', which populates the
  //'votersDoneVoting'.  Otherwise, this loop would fail.
  for (iter = this->votersDoneVoting.begin(); 
       iter != this->votersDoneVoting.end(); ++iter) 
  {
    OneVoter voter = iter->second;
    //the use of the pow function is not safe because if the base is
    //negative but the exponent is not an integer value, a domain
    //error occurs.  
    totalSquaredDifference += pow((voter.getTimeWaiting() - mean), 2.0);
  }

  //The sqrt function will cause a domain error for a negative argument.
  //In this case the 'totalSquaredDifference' cannot be negative because
  //it is the sum of squared values, which are always positive.  One
  //possible cause of error is when 'howManyVoters' is either negative or 
  //zero.  However, this condition has already been handled in the 
  //'initialize'.  Therefore, we do not have to worry the exceptions
  //of dividing by zero or taking the square root of a negative value.
  dev = sqrt(totalSquaredDifference/this->howManyVoters);

  cout << "leave computeMeanAndDev" << endl;
}

/******************************************************************************
 * Function 'doStatistics'.
 * This does stats on the voter queue 'votersDoneVoting'.
 *
 * We plot a histogram of the wait times and we compute the mean and deviation
 * of the wait times from that voter queue.
 *
 * Parameters: none
 * Output: none
 * Returns: none
**/
void Queue::doStatistics()
{
  double mean;
  double dev;
  map<int, int> waitTimeMap;

  cout << "enter doStatistics" << endl;

  multimap<int, OneVoter>::iterator iterMultimap;
  //This loop is safe because it is controlled by the functions of the
  //container.  In this case, the loop is limited between the
  //the beginning and the end of the multimap.
  for (iterMultimap = this->votersDoneVoting.begin();
       iterMultimap != this->votersDoneVoting.end(); ++iterMultimap)
  {
    OneVoter voter = iterMultimap->second;
    int waitTime = voter.getTimeWaiting();
    waitTimeMap[waitTime] = waitTimeMap[waitTime] + 1;
  }

  int timeLower = (waitTimeMap.begin())->first;
  int timeUpper = (waitTimeMap.rbegin())->first;

  //Even though this loop is run on subscript, the 'timeUpper' cannot be 
  //smaller than the 'timeLower' because these values are obtained from 
  //the beginning and the end of the container.  Since the key values
  //in the multimap are automatically sorted, the beginning element 
  //('timeLower') is always smaller or equal to to the ending element
  //('timeUpper').
  for (int time = timeLower; time <= timeUpper; ++time)
  {
    int count = waitTimeMap[time];
    cout << Utils::Format(time, 6) << ": "
         << Utils::Format(count, 6) << ": ";
    cout << string(count, '*') << endl;
  }
  cout << endl << endl;

  //mean and dev are passed into the function 'computeMeanAndDev' by reference 
  //and are not declared const.  Therefore, their values can be modified within
  //this function.
  computeMeanAndDev(mean, dev);
  cout << "mean and deviation of wait time are " << mean << ", " << dev << endl;

  waitTimeMap.clear();

  cout << "leave doStatistics" << endl;
}

/******************************************************************************
 * Function 'initialize'.
 * This initializes the voter queue.
 *
 * Note that the number of time steps is the minimum number of time steps to 
 * simulate. It is possible we simulate more because we keep going until the
 * queue of pending voters is totally drained.
 *
 * We load the voters into a backup 'multimap' that we copy with each
 * simulation to the 'multimap' that the simulation will use.
 *
 * Parameters:
 *   howManyVoters - the number of voters to simulate
 *   howManyMachinesLower - the lower bound of machines
 *   howManyMachinesUpper - the upper bound (inclusive) of machines
 *   numberOfTimeSteps - the number of time steps to simulate
 *   voteTimeMean - the mean of the voting time
 *   voteTimeDev - the deviation of the voting time
**/
void Queue::initialize(int howManyVoters,
                       int howManyMachinesLower, int howManyMachinesUpper,
                       int numberOfTimeSteps,
                       double voteTimeMean, double voteTimeDev)
{
  cout << "enter initialize" << endl;

  //This ensures that 'howManyMachinesLower' is less than or equal to
  //'howManyMachinesUpper'.  The program will exit gracefully otherwise.
  assert(howManyMachinesLower <= howManyMachinesUpper);

  //The number of voting machines needs to be positive.
  if (howManyMachinesLower <= 0 || howManyMachinesUpper <= 0)
  {
    cout << "The number of voting machines is invalid." << endl;
  }
  this->howManyMachinesLower = howManyMachinesLower;
  this->howManyMachinesUpper = howManyMachinesUpper;

  //The number of voters needs to positive.
  if (howManyVoters <= 0)
  {
    cout << "The number of voters is invalid." << endl;
  }
  this->howManyVoters = howManyVoters;

  //This loop is valid because 'this->howManyVoters' would be greater than 0
  //by this point.
  for (int i = 0; i < this->howManyVoters; ++i)
  {
    //When you call the function 'randomUniformInt', 'numberOfTimeSteps'
    //needs to be greater than 0 (the lower bound).
    int arrival = this->random.randomUniformInt(0, numberOfTimeSteps);

    //When you call the function 'randomNormal', 'voteTimeDev' needs to be
    //positive.  This condition is already checked inside the function itself. 
    //'voteTimeMean' needs to be greater than or equal to 0. 
    if (voteTimeMean < 0)
    {
      cout << "Invalid mean" << endl;
    }
    int duration = int(this->random.randomNormal(voteTimeMean, voteTimeDev));
    OneVoter oneVoter(i, arrival, duration);
    this->votersBackup.insert(std::pair<int, OneVoter>(arrival, oneVoter));
  }

  cout << "leave initialize" << endl;
}


/******************************************************************************
 * Function 'runSimulation' to run the actual voting simulation.
 *
 * This is the outer loop of the simulation.  We first iterates through
 * a range of the numbers of the voting machines and then runs a different 
 * simulation for each possible number of voting machines through the 
 * invocation of the 'runSimulation2' function.  
 *
 * This function first clears all the data structures used for each simulation,
 * including the 'votersDoneVoting' multimap and the 'freeMachines' vectors.
 * The 'votersPending' and 'votersVoting' multimaps will be cleared by 
 * the end of each 'runSimulation2' and therefore are not taken into
 * consideration.  Then, all the voters from 'votersBackup' are moved to the 
 * 'votersPending' multimap to prepare for each simulation.  The 
 * 'freeMachines' vector is also populated with the appropriate number 
 * of voting machines.
 *
 * The 'doStatistics' function is called to histograms the wait times for
 * the voters when they are all finished (when the 'runSimulation2' 
 * is completed).
 * 
 * Parameters: none
 * Output: none
 * Returns: none 
**/
void Queue::runSimulation()
{
  cout << "enter runSimulation" << endl;

  //This loop is run on subscripts.  However, 'howManyMachineUpper' cannot
  //be less than 'howManyMachinesLower' because this condition is already
  //verified in the function 'initialize'.
  for (int i = this->howManyMachinesLower; 
                 i <= this->howManyMachinesUpper; ++i)
  {
    this->freeMachines.clear();
    this->votersDoneVoting.clear();

    multimap<int, OneVoter>::iterator iter;
    //This loop is safe because it is controlled by the functions of the
    //container.  In this case, the loop is limited between the
    //the beginning and the end of the multimap.  The function 'initialize'
    //needs to be called prior to this function in order to populate the
    //'votersBackup'. Otherwise, this loop would fail.
    for (iter = this->votersBackup.begin();
         iter != this->votersBackup.end(); ++iter)
    {
      int arrivalTime = iter->first;
      OneVoter voter = iter->second;
      this->votersPending.insert(std::pair<int, OneVoter>(arrivalTime, voter));
    }

    cout << "run simulation for " << i << " machines" << endl;

    //This loop is run on subscripts. i, or 'howManyMachinesLower', is always
    //greater than 0 since this condition has already been checked for the 
    //parameter.  
    for (int j = 0; j < i; ++j) 
    {
      this->freeMachines.push_back(j); 
    }

    //When you call the function 'runSimulation2', i needs to be greater 
    //than 0.  Otherwise, there would be no voting machines for which to run
    //the inner simulation.  This condition has already been checked for the 
    //parameter.
    runSimulation2(i);
    doStatistics();
  }

  cout << "leave runSimulation" << endl;
}

/******************************************************************************
 * Function 'runSimulation2' to run the voting simulation for a fixed number
 * of voters and voting machines.
 *
 * This function iterates through each time step and process any voting
 * events that happen at a specific time step.  If a voter is finished, then 
 * a free machine is pushed into the 'freeMachines' vector and the voter
 * is moved to the 'votersDoneVoting' multimap.  As long as there are free
 * machines and pending voters arrive before or right at the time step,
 * they are assigned to a machine number and get moved to the 'votersVoting'
 * multimap.  The machine that is returned first by a finished voter will
 * be assigned first, which means the elements in the 'freeMachines' vector
 * are removed from the beginning of the vector. 
 *
 * Since we are to move a voter to another mutlimap, we need to remove that 
 * voter from the previous multimap.  In order to prevent the situation that 
 * we ignore one element when trying to erase an iterator while 
 * looping, we set the eraseElement flag and only increment the iterator
 * when the eraseElement is false.
 *
 * This iteration runs until there are no longer any pending and voting 
 * voters.
 *
 * This function also calls the 'toString' method to output the 
 * 'votersPending' multimap.
 * 
 *
 * Parameters: howManyMachine is an integer that indicates a fixed number of 
 *             voting machines
 * Output: none
 * Returns: none
**/
void Queue::runSimulation2(int howManyMachines)
{
  cout << "enter runSimulation2 for machine count:" 
       << Utils::Format(howManyMachines, 6) << endl;

  cout << toString(); //outputs the 'votersPending' multimap

  cout << endl;
  cout << "VOTING VOTERS" << endl << endl;
  cout << "DONE VOTERS VOTING" << endl << endl;

  for (int i = 0; i < 6; ++i)
  {
    cout << string(10, '*') << " ";
  }

  cout << endl << endl;

  int t = 0; //time step

  //The loop conditions are safe because they are controlled by the functions of
  //the container. 
  while (this->votersPending.size() != 0 || this->votersVoting.size() != 0)
  {
    cout << Utils::Format("TIME", 11, "left") << Utils::Format(t, 4)
         << Utils::Format(static_cast<int>(this->freeMachines.size()), 5) << endl;

    if (this->votersVoting.size() != 0)
    {
      multimap<int, OneVoter>::iterator iter2 = this->votersVoting.begin(); 
      //This loop is safe because it is controlled by the functions of the
      //container.  In this case, the loop is limited between the
      //the beginning and the end of the multimap.
      //Also, because we are trying to remove iterator while iterating, there
      //is a possibility that we skip elements that follow the erased ones and
      //step out of the bound.  In order to avoid that possibility, we set up a
      //flag that only allows for incrementing the iterator if there is no
      //erasure for each iteration.
      while(iter2 != this->votersVoting.end())
      {
        bool eraseElement = false;
        int arrivalTime = iter2->first;
        OneVoter votingVoter = iter2->second;

        if (t == votingVoter.getTimeDoneVoting())
        {
          this->freeMachines.push_back(votingVoter.getMachineNumber());
          this->votersDoneVoting.insert(
            std::pair<int, OneVoter>(arrivalTime, votingVoter));

          this->votersVoting.erase(iter2);
          eraseElement = true;
          iter2 = this->votersVoting.begin();

          cout << "VOTER DONE" << Utils::Format(t, 6) 
                               << ": " << votingVoter.toString();

          votingVoter.doneVoting();
        }

        if (eraseElement == false)
        {
          ++iter2; 
        }
      }
    }

    if (this->votersPending.size() != 0)
    {
      int arrivalTime = (this->votersPending.begin())->first;
      OneVoter pendingVoter = (this->votersPending.begin())->second;

      //Since the arrival time is randomly generated from a set
      //of positive integers and therefore is positive, the first condition
      //is safe.  The second condition uses the function of the container  
      //and is also safe.  Therefore, the loop is safe.
      while (t >= pendingVoter.getTimeArrival() 
                            && this->freeMachines.size() != 0)
      {
        int nextAvailableMachine = *(this->freeMachines.begin());
        this->freeMachines.erase(this->freeMachines.begin());
        pendingVoter.assignMachine(nextAvailableMachine, t);

        this->votersVoting.insert(
          std::pair<int, OneVoter>(arrivalTime, pendingVoter));
        //given the condition that 'votersPending' is not empty,
        //there is always at least one element in this multimap and 
        //thus it is safe to try to erase an iterator pointing
        //to the first element.
        this->votersPending.erase(this->votersPending.begin());

        cout << "ASSIGNED" << Utils::Format(t, 8) 
                           << ": " << pendingVoter.toString();
        
        arrivalTime = (this->votersPending.begin())->first;
        pendingVoter = (this->votersPending.begin())->second;
      }
    }

    ++t; //increment the time step
  }

  cout << "leave runSimulation2" << endl;
}

/******************************************************************************
 * Function 'toString' to output all the pending voters.
 *
 * This function loops through the 'votersPending' multimap and invokes the 
 * 'toString' method of each voter instance to output the voters' attributes.
 * 
 * Parameters: none
 * Output: none
 * Returns: none
**/
string Queue::toString()
{
  string s = "";

  s = "PENDING VOTERS\n";

  multimap<int, OneVoter>::iterator iter;
  //This loop is safe because it is controlled by the functions of the
  //container.  In this case, the loop is limited between the
  //the beginning and the end of the multimap.
  for (iter = this->votersPending.begin(); 
       iter != this->votersPending.end(); ++iter)
  {
    OneVoter voter = iter->second;
    s += voter.toString();
  }

  return s;
}
