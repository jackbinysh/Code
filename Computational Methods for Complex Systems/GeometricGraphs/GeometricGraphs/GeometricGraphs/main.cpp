#define _USE_MATH_DEFINES
#include "GeometricGraphs.h"

#include <cmath>
#include <random>
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

int main()
{
	const int iNumRuns = 10000;
	const int iNumIterations = 1000;
	const double dDistance = static_cast<double>(M_PI)/2 ;

	GeometricGraphs::MyMatrix xInputMatrix;

	// setting up random number generator engine
	std::mt19937 xEngine(1726); // some deterministic seed
	std::uniform_real_distribution<double> xDistribution(0, 2*M_PI);

	
	for (int i = 1; i <= iNumRuns; i++)
	{
		GeometricGraphs::CreateLaplacian(xInputMatrix, dDistance, xEngine, xDistribution);
		GeometricGraphs::TriDiag(xInputMatrix);
		GeometricGraphs::QRAlgorithm(xInputMatrix, iNumIterations, 0.0001);

		//std::cout << i << "\n";
	}

}