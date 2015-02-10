#include "Graph.h"
#include <iostream>

int main()
{
	int iN = 10;
	int iNumRuns = pow(10, 6);
	std::cout.precision(10);

	for (double dGamma = 2; dGamma <= 4; dGamma += 0.1)
	{
		int iNumSuccesses = 0;
		Graph xGraph(dGamma, iN);
		for (int i = 1; i <= iNumRuns; i++)
		{
			xGraph.GenerateDegreeSequence();
			bool bSuccess = xGraph.ConstructGraph();
			iNumSuccesses += bSuccess;
		}
		double iFracSuccesses = static_cast<double>(iNumSuccesses) / iNumRuns;
		std::cout << dGamma << "\t" << iFracSuccesses << std::endl;
	}





	return 0;
}