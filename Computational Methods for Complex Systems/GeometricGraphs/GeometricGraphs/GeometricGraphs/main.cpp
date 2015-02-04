#define _USE_MATH_DEFINES
#include "GeometricGraphs.h"

#include <cmath>
#include <random>
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace Eigen;

int main(int argc, char *argv[])
{
	const int iNumRuns = 1000000;
	const double dTolerance = pow(10,-6);
	const double dDistance = static_cast<double>(M_PI)/5 ;
	GeometricGraphs::MyMatrix xInputMatrix;

	// setting up random number generator engine
	std::mt19937 xEngine(1724); // some deterministic seed
	std::uniform_real_distribution<double> xDistribution(0, 2*M_PI);

	// setting up the output stream
	std::string sFilename = std::string("NumRuns") + std::to_string(iNumRuns) + std::string("_Tolerance") + std::to_string(dTolerance) + ".txt";
	std::ofstream xOutput(sFilename);
	xOutput.precision(10);
	
	for (int i = 1; i <= iNumRuns; i++)
	{
		GeometricGraphs::CreateLaplacian(xInputMatrix, dDistance, xEngine, xDistribution);
		GeometricGraphs::TriDiag(xInputMatrix);
		GeometricGraphs::QRAlgorithm(xInputMatrix, 0, 99, dTolerance);

		for (int j = 0; j <= xInputMatrix.rows() - 1; j++)
		{
			xOutput << xInputMatrix(j,j) << "\t";
		}
		std::cout << i << "\n";
	}
	xOutput.close();
}