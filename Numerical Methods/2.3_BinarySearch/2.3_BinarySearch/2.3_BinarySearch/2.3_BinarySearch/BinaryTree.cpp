#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
  data = Datum(0,0.0);
  L=NULL;
  R=NULL;
}

BinaryTree::~BinaryTree()
{
  //cout << "Calling destructor" << endl;
  if(L!=NULL)
  { delete L; }
  if(R!=NULL)
  { delete R; }
}

BinaryTree::BinaryTree(Datum d)
{
  data = d;
  //cout << "Calling constructor: " << data.n << " " << data.x << endl;
  L=NULL;
  R=NULL;
}

void BinaryTree::build(BinaryTree *T, std::vector<Datum> a)
{
   int n=a.size();
   int i;
   //cout << "a = ";
   //for(i=0;i<n;i++)
   //{cout << a[i].x << " "; }
   //cout << endl;
   if(n==1)
   {
      // Base case: if array a has length 1 we simply store this item of data at this
      // node
      T->data = a[0];
   }
   else
   {
      // Recursive case: Store the sum of the array a in an item of data at this node
      // then divide the array a into two pieces and pass one to the left
      // child tree and the other to the right child
      int m = floor(n/2);
      double sum=0;
      Datum d;
      std::vector<Datum> aL;
      std::vector<Datum> aR;
      // Calculate the sum of elements of a
      for(i=0;i<n;i++)
      {sum+=a[i].x;
      } 
      T->data = Datum(-1, sum);
      // Now divide the array a into two pieces 
      m = floor(n/2);
      aL.resize(m);
      aR.resize(n-m); 
      //cout << "aL = ";
      for(i=0;i<m;i++)
      {aL[i]=a[i];
       //cout << aL[i].x << " ";
      }
      //cout << endl;
      //cout << "aR = ";
      for(i=m;i<n;i++)
      {aR[i-m]=a[i];
       //cout << aR[i-m].x << " ";
      }
      //cout << endl;
      // Build a new tree on the left child with subarray aL and on the right child
      // with subarray aR
      T->L = new BinaryTree();
      build(T->L, aL);
      T->R = new BinaryTree();
      build(T->R, aR);
   }
   return;
}

void BinaryTree::Traverse() const
{
	if(L) L -> Traverse();
	if(R) R -> Traverse();
	cout << data.n << "\t" << data.x << endl;
	return;
}

Datum BinaryTree::Search(BinaryTree* Tree, double x) const
{
	if (!(Tree->L) && !(Tree->R))
	{
		return Tree->data;
	}
	else
	{
		double dLeftChildSum = (Tree->L->data).x;
		if (x <= dLeftChildSum)
		{
			return Search(Tree->L, x);
		}
		else
		{
			return Search(Tree->R, x - dLeftChildSum);
		}
	}
}
