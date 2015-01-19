#define _USE_MATH_DEFINES
#include "GeometricGraphs.h"

#include <cmath>
#include <random>

int main()
{
	int iNumRuns = 1000000;
	int iN = 100;
	double dDistance = static_cast<double>(M_PI) / 5;

	std::vector<std::vector<double>>  xInputMatrix(iN, std::vector<double>(iN));

	// setting up random number generator engine
	std::mt19937 xEngine(1729); // some deterministic seed
	std::uniform_real_distribution<double> xDistribution(0, 2*M_PI);

	
	for (int i = 1; i <= iNumRuns; i++)
	{
		GeometricGraphs::CreateLaplacian(xInputMatrix, dDistance, xEngine, xDistribution);
	}

}