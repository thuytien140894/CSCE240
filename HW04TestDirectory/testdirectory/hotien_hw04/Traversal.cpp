#include "Traversal.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Traversal' to calculate the total payoff values from all the leaf
 * nodes by performing a depth-first traversal.
 *
 * This class contains methods to create a tree from the standard data input, 
 * to traverse the tree recursively and compute the total payoff value of 
 * the leaf nodes, and to output all the data of the tree.
 *
 * Author: Duncan A. Buell
 *         Modifications by Tien Ho
 * Date last modified: 05 March 2015
**/

static const string TAG = "Traversal: ";

/******************************************************************************
 * Default constructor that initializes the totalPayoff to 0.
**/
Traversal::Traversal()
{
    totalPayoff = 0;
}

/******************************************************************************
 * Destructor
**/
Traversal::~Traversal()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'initialize' to create a tree from a standard data input.
 *
 * This function stores the tree nodes into a map<int, Node> with the keys
 * set to the sequence values.  We use the Node class first to create parent
 * nodes with their corresponding downlinks.  Then we loop through the 
 * sequence numbers to add the leaf nodes into the map.  The map is
 * automatically sorted by the sequence numbers.
 *
 * Parameters: a standard stream in which each line of the data contains the 
 *             parent number followed by a list of its children nodes.
 *
 * Output: a map of nodes that are identified by their sequence values.
 *
 * Returns: none
**/
void Traversal::initialize(Scanner& inStream)
{
#ifdef EBUG
  Utils::logStream << TAG << "enter initialize\n"; 
#endif

    while (inStream.hasNext())
    {
      string nextLine = inStream.nextLine();
      Node newNode = Node(nextLine);
      this->theNodes[newNode.getSequence()] = newNode;
    }  

    int minSeq = (this->theNodes.begin())->first;
    int maxSeq = (this->theNodes.rbegin())->first; //last element

    for (map<int, Node>::iterator iter = this->theNodes.begin();
                                iter != this->theNodes.end(); ++iter)
    {
        vector<int> theLinks = (iter->second).getDownLinks();
        for (vector<int>::iterator iter2 = theLinks.begin();
                               iter2 != theLinks.end(); ++iter2)
        {
            if ((*iter2) > maxSeq)
            {
                maxSeq = (*iter2);
            }  
        }
    }  

    for (int seq = minSeq; seq <= maxSeq; ++seq)
    {
        if (0 == this->theNodes.count(seq))
        {
            Node newNode = Node(seq);
            this->theNodes[seq] = newNode;
        }
    }  

#ifdef EBUG
  Utils::logStream << TAG << "leave initialize\n"; 
#endif
}

/******************************************************************************
 * Function 'traverse' to traverse through the map.
 *
 * This function invokes the recursive method traverseInner to perform an 
 * depth-first search through the map.
 *
 * Parameters: none
 *
 * Output: none
 *
 * Returns: the total payoff values of all the leaf nodes
**/
int Traversal::traverse()
{
    int level = 0;

#ifdef EBUG
  Utils::logStream << TAG << "enter traverse\n"; 
#endif

    headNode = this->theNodes.begin()->second;
    totalPayoff = traverseInner(level, headNode);

#ifdef EBUG
  Utils::logStream << TAG << "leave traverse\n"; 
#endif

    return this->totalPayoff;
}

/******************************************************************************
 * Function 'traverserInner' to perform a recursive search through the map.
 *
 * This function performs a recursive depth-first search through the map by
 * visiting each node and its children first before backtracking to the node 
 * at the same level.  The base condition for this recursive method applies
 * when the search reaches a leaf and its payoff value is added to the 
 * totalPayoff.  
 * 
 * In order to prevent re-visiting a node and detecting a cycle, the visited
 * flag is set each time a node is visited.
 * 
 * Parameters: an integer indicating the level of each visited node
 *             a tree node to check for downlinks
 *             both parameters are passed by reference.
 *
 * Output: none
 *
 * Returns: the total payoff values of all the leaf nodes.
**/
int Traversal::traverseInner(int& level, Node& node)
{
    int aLevel = level;

#ifdef EBUG
  Utils::logStream << TAG << "enter traverseInner" << node.toString() << endl; 
#endif

    if (node.getDownLinks().size() == 0)
    {
        totalPayoff += node.getPayoff();
        return totalPayoff;
    }  

    node.setVisited(true);
    ++aLevel;
    vector<int> theLinks = node.getDownLinks();

    for (vector<int>::iterator iter = theLinks.begin();
                               iter != theLinks.end(); ++iter)
    {
        int sequence = *iter;
        Node temp = this->theNodes[sequence];
        if (temp.getVisited() == false)
        totalPayoff = traverseInner(aLevel, temp);
    }

#ifdef EBUG
  Utils::logStream << TAG << "leave traverseInner\n"; 
#endif

    return totalPayoff;
}

/******************************************************************************
 * Function 'toString' to print out all the nodes in the map.
 *
 * This function iterates through all the nodes in the map and invoke their
 * 'toString' method, which prints out their sequence number, their payoff,
 * and their downlinks.
 *
 * Parameters: none
 *
 * Output: none
 *
 * Returns: a string that contains the data of all the nodes
**/
string Traversal::toString() const
{
    string output = "";

#ifdef EBUG
  Utils::logStream << TAG << "enter toString\n"; 
#endif

    output = "ALL NODES\n";

    for (map<int, Node>::const_iterator iter = this->theNodes.begin();
                                iter != this->theNodes.end(); ++iter)
    {
        output += iter->second.toString() + "\n";
    }

#ifdef EBUG
  Utils::logStream << TAG << "leave toString\n"; 
#endif

    return output;
}

