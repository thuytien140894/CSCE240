/****************************************************************
 * Header file for a node in a tree.
 *
 * Author/copyright:  Duncan Buell
 *                    Modifications by Tien Ho
 * Date: 05 March 2015
 *
**/

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <vector>
using namespace std;

#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

class Node
{
public:
  Node();
  Node(int sequence);
  Node(string initString);
  virtual ~Node();

  bool getVisited();
  void setVisited(bool visit);
  int getPayoff() const;
  int getSequence() const;
  vector<int> getDownLinks() const;

  string toString() const;

private:
  bool visited;
  int payoff;
  int sequence;

  vector<int> downLinks;
};

#endif
