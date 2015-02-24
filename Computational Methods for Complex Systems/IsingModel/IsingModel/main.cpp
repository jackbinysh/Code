#include "IsingModel.h"
#include <cstdlib> 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>

int main(int argc, char *argv[])
{
	// read in from command line
	const int iLatticeSize = atoi(argv[1]);
	std::string sLatticeSize = argv[1];
	const int iWaitTime = atoi(argv[2]);
	const double dTemp = atoi(argv[3]);
	std::string sTemp = argv[3];
	// some constants
	const int iNumIndependentSamples = pow(10,6);
	const int iEquilibrationTime = 10000;

	// okay begin the simulation intialise
	IsingModel IsingModelInstance(iLatticeSize);
	IsingModelInstance.Initialise(dTemp);

	// burn the chain in 
	for (int i = 1; i <= iEquilibrationTime; i++) IsingModelInstance.Sweep();

	// output
	std::string sFilename = std::string("Size") + sLatticeSize + std::string("Temp") + sTemp + std::string(".txt");
	std::ofstream xOutput(sFilename.c_str());

	// on the first line, write the temp and the IAC
	xOutput << dTemp << "\t" << iWaitTime << std::endl;

	for (int i = 0; i <= iNumIndependentSamples*(iWaitTime) ; i++)
	{	
		IsingModelInstance.Sweep();
		if (0 == (i % iWaitTime))
		{
			static const double dSquare = static_cast<double>(iLatticeSize*iLatticeSize);
			xOutput << static_cast<double>(IsingModelInstance.getM()) / dSquare << "\t" << static_cast<double>(IsingModelInstance.getE()) / dSquare << std::endl;
		}
	}
	xOutput.close();
	return 0;
}