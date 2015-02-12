#include "Graph.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

int main(int argc, char *argv[])
{
	// read in from command line
	int iN = atoi(argv[1]);
	int iNumRuns = atoi(argv[2]);
	// some initial in/out settings
	std::string sFilename = std::string("Size") + std::to_string(iN) + std::string("NumRuns") + std::to_string(iNumRuns);
	std::ofstream xOutput(sFilename);
	xOutput.precision(10);

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
		std::cout << dGamma << std::endl;
		xOutput << dGamma << "\t" << iFracSuccesses << std::endl;
	}
	return 0;
}