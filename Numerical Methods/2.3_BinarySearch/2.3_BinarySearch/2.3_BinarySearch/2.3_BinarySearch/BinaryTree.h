#ifndef _BINARYTREE
#define _BINARYTREE
using namespace std;

#include <iostream>
#include <vector>
#include <math.h>
#include "Datum.h"

class BinaryTree
{
  Datum data;

public:
  BinaryTree *L;
  BinaryTree *R;
  BinaryTree();
  BinaryTree(Datum d);
  ~BinaryTree();
  void build(BinaryTree *T, vector<Datum> a);
  void Traverse() const;
  Datum Search(BinaryTree* Tree, double x) const;
};

#endif

