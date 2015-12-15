/****************************************************************
 * Header file for the class to traverse a tree recursively.
 *
 * Author/copyright:  Duncan Buell
 * Submitted by: Tien Ho
 * Date: 05 March 2015
 *
**/

#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include "Node.h"

#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

class Traversal
{
public:
  Traversal();
  virtual ~Traversal();

  void initialize(Scanner& inStream);
  string toString() const;
  int traverse();

private:
  int totalPayoff;

  Node headNode;

  map<int, Node> theNodes;

  int traverseInner(int& level, Node& node);
};

#endif
