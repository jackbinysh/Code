#include "IsingModel.h"
#include "IAC.h"
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
	// put in an integer value of the temp for now
	const double dTemp = atof(argv[2])/10;

	// set up the output
	std::string sFilename = std::string("Size") + argv[1] + std::string("Temp") + argv[2] + std::string(".txt");
	std::ofstream xOutput(sFilename.c_str());

	// some constants
	const int iNumIndependentSamples = std::floor(pow(10, 6)); // number of independent samples we want 
	const int iEquilibrationTime = 10000; // amount of runs code discards before beginning to take data
	const int iTMax = 50000; // the size of the array in computing the IAC

	//
	// okay begin the simulation 
	//
	
	//intialise
	IsingModel IsingModelInstance(iLatticeSize);
	IsingModelInstance.Initialise(dTemp);

	// burn the chain in 
	for (int i = 1; i <= iEquilibrationTime; i++) IsingModelInstance.Sweep();

	// compute the integrated autocorrelation time
	IAC IACInstance(iTMax);
	for (int i = 0; i <= iTMax -1 ; i++)
	{
		static const double dSquare = static_cast<double>(iLatticeSize*iLatticeSize);

		IsingModelInstance.Sweep();
		double dm = IsingModelInstance.getM() / dSquare;
		IACInstance.setm(i, std::abs(dm));
	}
	IACInstance.ComputeTau();

	// now we have tau, so we can run the simulation proper. begin by outputting tau and t into the outout
	xOutput << IACInstance.getTau() << "\t" << dTemp << std::endl;

	int iWaitTime = std::ceil(2*IACInstance.getTau());
	for (int i = 0; i <= iNumIndependentSamples*iWaitTime  ; i++)
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