#define _USE_MATH_DEFINES

#include "GeometricGraphs.h"
#include <algorithm>  
#include <cmath>

void GeometricGraphs::CreateLaplacian(std::vector<std::vector<double>>& xInputMatrix, double dDistance, std::mt19937& xEngine, std::uniform_real_distribution<double>& xDistribution)
{
	int iN = xInputMatrix[0].size();
	std::vector<double> xPositions(iN);

	//begin by filling the matrix with 0's
	for (int i = 0; i <= iN - 1; i++)
	{
		xInputMatrix[i][i] = 0;
	}

	// loop over the lower triangle
	for (int i = 0; i <= iN - 1; i++)
	{
		// throw down the new point
		xPositions[i] = xDistribution(xEngine);

		// fill in the lower triangle, and its transpose
		for (int j = 0; j < i ; j++)
		{
			if (Distance(xPositions[i], xPositions[j], 2*M_PI) < dDistance)
			{
				// note these are -1, since we are used L = D - A as the laplacian definition.
				xInputMatrix[i][j] = -1;
				xInputMatrix[j][i] = -1;
				// since we are constructing the laplacian, we add 1 to the on diagonal of both i and j, since they each have a new node
				xInputMatrix[i][i]++;
				xInputMatrix[j][j]++;

			}
			else
			{
				xInputMatrix[i][j] = 0;
				xInputMatrix[j][i] = 0;
			}
		}
	}
	return;
}

double GeometricGraphs::Distance(double dX, double dY, double dMod)
{
	double dDirectDistance = std::abs(dX - dY);
	return std::min(dDirectDistance, dMod - dDirectDistance);
};