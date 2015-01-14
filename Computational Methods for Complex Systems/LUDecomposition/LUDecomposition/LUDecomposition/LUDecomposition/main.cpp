#include "LUDecomp.h"
#include <time.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>
#include <string>
#include <cstdlib>

// a function which takes in an empty matrix, and fills it in with an ERGraph
void CreateERGraph(std::vector<std::vector<double>>& xEmptyMatrix, int iN, double dP, std::mt19937& xEngine, std::uniform_real_distribution<double>& xDistribution);

int main(int argc, char *argv[])
{
	// setting the initial parameters
	int iN = atoi(argv[1]);
	int iNumRuns = atoi(argv[2]);
	double dInitialp = atof(argv[3]);
	double dFinalp = atof(argv[4]);
	double dStep = atof(argv[5]);

	// setting up random number generator engine
	std::mt19937 xEngine(1729); // some deterministic seed
	std::uniform_real_distribution<double> xDistribution(0,1.0);

	// constructing two arrays we will use over and over 
	std::vector<std::vector<double>>  Results((((dFinalp - dInitialp)/ dStep) +2), std::vector<double>(2));
	std::vector<std::vector<double>> xERGraph(iN, std::vector<double>(iN));

	int iCounter = 0;
	for (double p = dInitialp; p <= dFinalp + pow(10,-6); p += dStep)
	{
		int iSum = 0;
		for (int i = 1; i <= iNumRuns; i++)
		{
			CreateERGraph(xERGraph, iN, p, xEngine, xDistribution);
			bool bIsSingular = LUDecomp::LUDecompose(xERGraph);
			iSum += bIsSingular;
		}
		double dFrac = static_cast<double>(iSum) / iNumRuns;
		Results[iCounter][0] = p;
		Results[iCounter][1] = dFrac;
		std::cout << iCounter << "\n";
		iCounter++;
	}

	//writing results to a file
	std::string sFilename = std::string("Results")  + "Size" + std::to_string(iN) + "Initialp" + std::to_string(dInitialp) + "Finalp" + std::to_string(dFinalp) + ".txt" ;
	std::ofstream xOutput(sFilename);
	xOutput.precision(10);
	for (int i = 0; i <= ((dFinalp - dInitialp) / dStep) ; i++)
	{
		xOutput << Results[i][0] << "\t" << Results[i][1] << "\n";
	}
	xOutput.close();
	return 0;
}

void CreateERGraph(std::vector<std::vector<double>>& xEmptyMatrix, int iN, double dP, std::mt19937& xEngine, std::uniform_real_distribution<double>& xDistribution)
{
	for (int i = 0; i <= iN - 1; i++)
	{
		for (int j = 0; j < i; j++)
		{
			double dRandomNumber = xDistribution(xEngine);
			if (dRandomNumber < dP)
			{
				xEmptyMatrix[i][j] = 1;
				xEmptyMatrix[j][i] = 1;
			}
			else
			{
				xEmptyMatrix[i][j] = 0;
				xEmptyMatrix[j][i] = 0;
			}				
		}
	}
	for (int i = 0; i <= iN - 1; i++)
	{
		xEmptyMatrix[i][i] = 0;
	}
	return;
}