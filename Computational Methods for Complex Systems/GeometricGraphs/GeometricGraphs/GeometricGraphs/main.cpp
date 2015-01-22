#define _USE_MATH_DEFINES
#include "GeometricGraphs.h"

#include <cmath>
#include <random>
#include <Eigen/Dense>

using namespace Eigen;

int main()
{
	const int iNumRuns = 100;
	const int iN = 4;
	const double dDistance = static_cast<double>(M_PI)/1.5 ;


	Matrix4d xInputMatrix(iN, iN);

	// setting up random number generator engine
	std::mt19937 xEngine(1726); // some deterministic seed
	std::uniform_real_distribution<double> xDistribution(0, 2*M_PI);

	
	for (int i = 1; i <= iNumRuns; i++)
	{
		GeometricGraphs::CreateLaplacian(xInputMatrix, dDistance, xEngine, xDistribution);
		GeometricGraphs::QRAlgorithm(xInputMatrix, iNumRuns);
		int x = 1;

	}

}