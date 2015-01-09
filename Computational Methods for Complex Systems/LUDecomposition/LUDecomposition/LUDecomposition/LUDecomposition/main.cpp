#include "LUDecomp.h"
#include <time.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>

// a function which takes in an empty matrix, and fills it in with an ERGraph
void CreateERGraph(std::vector<std::vector<double>>& xEmptyMatrix, int iN, double dP, std::mt19937& xEngine, std::uniform_real_distribution<double>& xDistribution);

int main()
{
	// setting the initial parameters
	int N = 100;
	int iNumRuns = pow(10, 4);
	double dInitialp = 0.1 ;
	double dFinalp = 0.1;
	double dStep = 0.05;

	// setting up random number generator engine
	std::mt19937 xEngine(1729); // some deterministic seed
	std::uniform_real_distribution<double> xDistribution(0,1.0);

	// constructing two arrays we will use over and over 
	std::vector<std::vector<double>>  Results((((dFinalp - dInitialp)/ dStep) +2), std::vector<double>(2));
	std::vector<std::vector<double>> xERGraph(N, std::vector<double>(N));

	int iCounter = 0;
	for (double p = dInitialp; p <= dFinalp + pow(10,-6); p += dStep)
	{
		int iSum = 0;
		for (int i = 1; i <= iNumRuns; i++)
		{

			//CreateERGraph(xERGraph, N, p, xEngine, xDistribution);
			std::vector<std::vector<double>> xERGraph({ { 2, 1, 4, 1 }, { 1, 1, 0, 1 }, { 1, 2, -3, 1 }, {1,1,1,1} });
			bool bIsSingular = LUDecomp::LUDecompose(xERGraph);
			iSum += bIsSingular;
			//std::cout << i << "\n";
		}
		double dFrac = static_cast<double>(iSum) / iNumRuns;
		Results[iCounter][0] = p;
		Results[iCounter][1] = dFrac;
		std::cout << iCounter << "\n";
		iCounter++;
	}

	//writing results to a file
	std::ofstream xOutput("Results.txt");
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