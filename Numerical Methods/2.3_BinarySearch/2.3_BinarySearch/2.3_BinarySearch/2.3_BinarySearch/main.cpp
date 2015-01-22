using namespace std;

#define _USE_MATH_DEFINES 

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>
#include <iomanip>

#include "Datum.h"
#include "BinaryTree.h" 

// This program takes an array of (int, double) pairs (k,x)
// and stores the list of partial sums of the x's and corresponding 
// indices in a binary search tree (Fenwick tree). 
// To run the command type
//
// binaryTree n 
//

double GenerateData(int n, vector<Datum>& data);
void TraverseTree();

int main(int argc, char **argv)
{
	srand(time(NULL)); // Im just going to use the standard random number generator.

	//begin by building a traversing trees of size 8 and 10
	cout << "Traversing trees of size 8 and 10" << endl;
	TraverseTree();
	cout << "Done traversing" << endl;

	// Read in the value of iNmax from the command line and generate the array
	int iNmax = atoi(argv[1]);

	ofstream xOutput("Results.txt");
	for (int n = 1; n <= iNmax; n = 2*n)
	{
		vector<Datum> data(n);
		//generate data
		double dSum = GenerateData(n, data);

		// build the tree
		BinaryTree* T = new BinaryTree();
		T->build(T, data);

		//generate the random number we are searching the tree for
		double dy = rand() % static_cast<int>(floor(dSum));

		//time the search, run it 10^6 times.
		clock_t t1 = clock();
		for (int i = 1; i <= 1000000; i++)
		{
			Datum output = T->Search(T, dy);
		}
		clock_t t2 = clock();
		float fElapsedTimes = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;

		// output the data
		xOutput.precision(10);
		cout.precision(10);

		cout << n << "\t" << fElapsedTimes << "\n";
	0

		delete T;

		// a bit of code used to generate sample output
		//for (i = 1; i <= 110; i++)
		//{
		//	Datum output = T->Search(T, i);
		//	float fpartialsum = 0.5*(output.n + 1)*(output.n + 2)*M_PI;
		//	xOutput << i << "\t" << output.n + 1 << "\t" << fpartialsum << "\t" << output.x << "\n";
		//}
	}
	xOutput.close();
	return 0;
}

double GenerateData(int n, vector<Datum>& data)
{
	double dRunningSum = 0.0;
	for (int i = 0; i < n; ++i)
	{
		double y = (i + 1)*M_PI;
		data[i] = Datum(i, y);
		dRunningSum += y;
	}
	return dRunningSum;
}

void TraverseTree()
{
	for (int n = 8; n <= 10; n = n + 2) //inserthackshere
	{
		vector<Datum> data(n);
		//generate data
		double dSum = GenerateData(n, data);

		// build the tree
		BinaryTree* T = new BinaryTree();
		T->build(T, data);
		T->Traverse();
	}
	return;
}
