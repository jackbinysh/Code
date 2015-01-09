#include "LUDecomp.h"
#include <cmath>
#include <iostream>


bool LUDecomp::LUDecompose(std::vector<std::vector<double>>& xInputMatrix)
{
	int iN = xInputMatrix[0].size();
	bool bIsSingular = false;
	
	bIsSingular = ZeroRowCheck(xInputMatrix);
	if (bIsSingular) return true;

	for (int j = 0; j <= iN - 1; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			double dtemp = 0;
			for (int k = 0; k <= i - 1; k++)
			{
				dtemp += xInputMatrix[i][k] * xInputMatrix[k][j];
			}
			xInputMatrix[i][j] = xInputMatrix[i][j] - dtemp;
		}
		for (int i = j+1; i <= iN-1; i++)
		{
			double dtemp = 0;
			for (int k = 0; k <= j - 1; k++)
			{
				dtemp += xInputMatrix[i][k] * xInputMatrix[k][j];
			}
			//we implement pivoting, so we don't do the division here
			xInputMatrix[i][j] = xInputMatrix[i][j] - dtemp;
		}
		bIsSingular = Pivot(j, xInputMatrix);
		if (bIsSingular) return true;
		// divide all of the others by our new diagonal element
		for (int i = j + 1; i <= iN - 1; i++)
		{
			xInputMatrix[i][j] = xInputMatrix[i][j] / xInputMatrix[j][j];
		}
	}
	return false;
}

bool LUDecomp::Pivot(int j, std::vector<std::vector<double>>& xInputMatrix)
{
	double dLargestValue = 0.0;
	double dTolerance = pow(10, -10);

	int iLargestIndex = j;
	int iN = xInputMatrix[0].size();

	for (int i = j; i <= iN - 1; i++)
	{
		double dTemp = abs(xInputMatrix[i][j]);
		if (dTemp > dLargestValue)
		{
			dLargestValue = dTemp;
			iLargestIndex = i;
		}
	}
	// if the pivoting returns a largest magnitude of 0, the matrix is singular.
	if (abs(dLargestValue) - dTolerance < 0)
	{
		return true;
	}
	// if we need to pivot rows, do so
	if (iLargestIndex != j)
	{
		for (int k = j; k <= iN - 1; k++)
		{
			double temp = xInputMatrix[j][k];
			xInputMatrix[j][k] = xInputMatrix[iLargestIndex][k];
			xInputMatrix[iLargestIndex][k] = temp;
		}
	}
	return false;
}

bool LUDecomp::ZeroRowCheck(std::vector<std::vector<double>>& xInputMatrix)
{
	int iN = xInputMatrix[0].size();
	for (int i = 0; i <= iN - 1; i++)
	{
		for (int j = 0; j <= iN - 1; j++)
		{
			if (xInputMatrix[i][j])
			{
				break;
			}
			if (j == iN - 1)
			{
				return true;
			}
		}
	}
	return false;
}