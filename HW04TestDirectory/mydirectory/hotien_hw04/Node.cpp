#include "Node.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Node' for a single node in a tree.
 *
 * This class has the functions to create a single node in a tree with the 
 * payoff value and a vector of its leaf nodes.
 *
 * Author: Duncan A. Buell
 *         Modifications by Tien Ho
 * Date last modified: 05 March 2015
**/

static const string TAG = "Node: ";

/******************************************************************************
 * Default constructor
**/
Node::Node()
{
}

/******************************************************************************
 * This alternative constructor is used for leaf nodes with no downlinks.
 *
 * Parameters: an integer indicating the value of a node.
 * 
 * Output: a node that has its value set to the input sequence and its payoff 
 *         set to the square of the input sequence.
**/
Node::Node(int sequence)
{
    this->visited = false;
    this->sequence = sequence;
    this->payoff = (this->sequence)*(this->sequence);
}

/******************************************************************************
 * This alternative constructor is used for the parent nodes.
 *
 * An entire line of input data is read into a parent node and a vector of its
 * leaf nodes.
 *
 * Parameters: a string with a parent number followed by a list of child nodes.
 *
 * Output: a parent node with a vector of its child nodes.
**/
Node::Node(string initString)
{
    ScanLine input;
    input.openString(initString);

    while (input.hasNext())
    {
        downLinks.push_back(input.nextInt());
    }

    this->visited = false;
    this->sequence = downLinks[0];
    payoff = (this->sequence)*(this->sequence);
    downLinks.erase(downLinks.begin());
}

/******************************************************************************
 * Destructor
**/
Node::~Node()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * Accessor 'getVisited'.
 *
 * Returns: the visited condition of this node
**/
bool Node::getVisited()
{
    return this->visited;
}

/******************************************************************************
 * Mutator 'setVisited' to set the visited condition of the node.
 *
 * Parameters: a boolean indicating whether the node is visited during 
 *             traversal
**/
void Node::setVisited(bool visit)
{
    this->visited = visit;
}

/******************************************************************************
 * Accessor 'getPayoff'.
 *
 * Returns: the payoff value of this node
**/
int Node::getPayoff() const
{
    return this->payoff;
}

/******************************************************************************
 * Accessor 'getSequence'.
 *
 * Returns: the sequence number of this node
**/
int Node::getSequence() const
{
    return this->sequence;
}

/******************************************************************************
 * Accessor 'getDownLinks'.
 *
 * Returns: the 'vector<int>' of the 'downLinks'
**/
vector<int> Node::getDownLinks() const
{
    return this->downLinks;
}

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'toString' to output the data for each node.
 * 
 * This function cannot modify the member variables of the node class.  The 
 * Utilities class is used to format the output data.
 *
 * Parameters: none
 *
 * Output: none
 *
 * Returns: a string that contains the sequence value, the payoff, and the 
 *          downlinks of the node.
**/
string Node::toString() const
{
    string output = "";
    output += Utils::Format(this->sequence, 5);
    output += Utils::Format(this->payoff, 5);
    output += " F:";

    if (this->downLinks.size() != 0)
    {
        output += Utils::Format(downLinks[0], 6);
        for (UINT i = 1; i < this->downLinks.size(); i++)
        {
	    output += Utils::Format(downLinks[i], 5);
	}
    }

    return output;
}
