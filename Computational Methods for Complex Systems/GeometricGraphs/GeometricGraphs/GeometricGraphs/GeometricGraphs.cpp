#include "GeometricGraphs.h"
#include <iostream>

void GeometricGraphs::CreateLaplacian(MyMatrix& xInputMatrix, double dDistance, std::mt19937& xEngine, std::uniform_real_distribution<double>& xDistribution)
{
	static int iN = xInputMatrix.rows();
	static std::vector<double> xPositions(iN);

	//begin by filling the matrix with 0's
	for (int i = 0; i <= iN - 1; i++)
	{
		xInputMatrix(i,i) = 0;
	}

	// loop over the lower triangle
	for (int i = 0; i <= iN - 1; i++)
	{
		// throw down the new point
		xPositions[i] = xDistribution(xEngine);


		// fill in the lower triangle, and its transpose
		for (int j = 0; j < i ; j++)
		{
			if (Distance(xPositions[i], xPositions[j], 2*M_PI) < dDistance )
			{
				// note these are -1, since we are used L = D - A as the laplacian definition.
				xInputMatrix(i,j) = -1;
				xInputMatrix(j,i) = -1;
				//// since we are constructing the laplacian, we add 1 to the on diagonal of both i and j, since they each have a new node
				xInputMatrix(i,i)++;
				xInputMatrix(j,j)++;

			}
			else
			{
				xInputMatrix(i,j) = 0;
				xInputMatrix(j,i) = 0;

			}
		}
	};
return;
}

void GeometricGraphs::TriDiag(MyMatrix& xInputMatrix)
{
	static const int iN = xInputMatrix.rows();
	static MyVector xU; // the vector u, made up of 0's, then the n-1 elements of the column of a
	static MyVector xP; // a vector which will be used jointly for p and q

	for (int i = 0; i <= iN - 3; i++)
	{
		// setting up u
		xU(i) = 0;
		int iLength = (iN - 1) - i;
		xU.tail(iLength) = xInputMatrix.block(i + 1, i, iLength, 1);
		xU(i + 1) += xU.tail(iLength).norm();
		// now U is set up, we work out a series of intermediate quantities
		double dH = 0.5*xU.tail(iLength).squaredNorm();
		if (dH == 0) continue;
		xP = (xInputMatrix.rightCols(iLength)*xU.tail(iLength)) / dH;
		double dK = (xU.dot(xP)) / (2 * dH);
		xP = (xP - dK*xU);
		xInputMatrix = xInputMatrix - xP*xU.transpose() - xU*xP.transpose();
		//std::cout << xInputMatrix << "\n";
	}

	return;
}

void GeometricGraphs::QRAlgorithm(MyMatrix& xInputMatrix, int iLowerBound ,int iUpperBound, double dEpsilon)
{
	//std::cout << xInputMatrix << "\n" << "\n";
	const int iN = iUpperBound - iLowerBound + 1;

	//base cases. For the 2x2 im just going to explicitly calculate them
	if (iN == 1) return;
	if (iN == 2)
	{
		if (abs(xInputMatrix(iLowerBound, iLowerBound + 1)) > dEpsilon)
		{
			double dTr = xInputMatrix(iLowerBound, iLowerBound) + xInputMatrix(iUpperBound, iUpperBound);
			double dDet = (xInputMatrix(iLowerBound, iLowerBound))*(xInputMatrix(iUpperBound, iUpperBound)) - std::pow(xInputMatrix(iLowerBound, iLowerBound + 1),2);
			double dLambdap = 0.5*(dTr + sqrt(std::pow(dTr, 2) - 4 * dDet));
			double dLambdam = 0.5*(dTr - sqrt(std::pow(dTr, 2) - 4 * dDet));
			//assignments
			xInputMatrix(iLowerBound, iLowerBound) = dLambdap;
			xInputMatrix(iUpperBound, iUpperBound) = dLambdam;
			xInputMatrix(iLowerBound, iLowerBound+1) = 0;
			xInputMatrix(iLowerBound+1, iLowerBound) = 0;
		}
		return;
	}

	int i = iLowerBound;
	while (true)
	{
		if (abs(xInputMatrix(i + 1, i)) < dEpsilon)
		{
			break;
		}
		if (i == iUpperBound - 1)
		{
			GeometricGraphs::QRSweep(xInputMatrix, iLowerBound, iUpperBound, dEpsilon);
		};
		i++;
		if (i > iUpperBound - 1) i = i - (iUpperBound-1 - iLowerBound + 1);
	};


	GeometricGraphs::QRAlgorithm(xInputMatrix, iLowerBound, i, dEpsilon);
	GeometricGraphs::QRAlgorithm(xInputMatrix, i + 1, iUpperBound, dEpsilon);
	return;
}


void GeometricGraphs::QRSweep(MyMatrix& xInputMatrix, int iLowerBound, int iUpperBound, double dEpsilon)
{
	//some initilisation
	double dK(0), dH(0), dSigma(0);

	static Vector4d xU = Vector4d::Zero();
	static Vector3d xUEdge = Vector3d::Zero();
	static Vector4d xP = Vector4d::Zero();
	static Vector3d xPEdge = Vector3d::Zero();
	int iN = iUpperBound - iLowerBound + 1;

	xU.setZero();
	xUEdge.setZero();
	xP.setZero();
	xPEdge.setZero();

	{
		// okay the first nasty edge case, i =0
		xUEdge(0) = xInputMatrix(iLowerBound, iLowerBound);
		xUEdge(1) = xInputMatrix(iLowerBound+ 1, iLowerBound);
		dSigma = xUEdge.norm();
		if (dSigma)
		{
			if(signbit(dSigma) != signbit(xUEdge(0))) xUEdge(0) -= dSigma;
			else  xUEdge(0) += dSigma;

			dH = 0.5*xUEdge.squaredNorm();
			xPEdge = (1 / dH)*xInputMatrix.block(iLowerBound, iLowerBound, 3, 3)*xUEdge;
			dK = (xUEdge.dot(xPEdge)) / (2 * dH);
			xPEdge = (xPEdge - dK*xUEdge);
			xInputMatrix.block(iLowerBound, iLowerBound, 3, 3) = xInputMatrix.block(iLowerBound, iLowerBound, 3, 3) - xPEdge*xUEdge.transpose() - xUEdge*xPEdge.transpose();
			xUEdge.setZero();
		}

		// okay now the nice generic loop
		for (int i = iLowerBound + 1 ; i <= iUpperBound - 2; i++)
		{
			// fill the middle two in
			xU(1) = xInputMatrix(i, i);
			xU(2) = xInputMatrix(i + 1, i);

			dSigma = xUEdge.norm();

			if (dSigma)
			{
				if (signbit(dSigma) != signbit(xUEdge(0))) xU(1) -= dSigma;
				else  xU(1) += dSigma;

				dH = 0.5*xU.squaredNorm();

				xP = (1 / dH)*xInputMatrix.block(i - 1, i - 1, 4, 4)*xU;
				dK = (xU.dot(xP)) / (2 * dH);
				xP = (xP - dK*xU);
				xInputMatrix.block(i - 1, i - 1, 4, 4) = xInputMatrix.block(i - 1, i - 1, 4, 4) - xP*xU.transpose() - xU*xP.transpose();

			}

		}
		// okay now the nasty other edge case,iN-2
		xUEdge(1) = xInputMatrix(iUpperBound - 1, iUpperBound - 1);
		xUEdge(2) = xInputMatrix(iUpperBound, iUpperBound -1 );

		dSigma = xUEdge.norm();
		if (dSigma)
		{
			if (signbit(dSigma) != signbit(xUEdge(0))) xUEdge(1) -= dSigma;
			else  xUEdge(1) += dSigma;

			dH = 0.5*xUEdge.squaredNorm();
			xPEdge = (1 / dH)*xInputMatrix.block(iUpperBound - 2, iUpperBound - 2, 3, 3)*(xUEdge);
			dK = (xUEdge.dot(xPEdge)) / (2 * dH);
			xPEdge = (xPEdge - dK*xUEdge);
			xInputMatrix.block(iUpperBound - 2, iUpperBound - 2, 3, 3) = xInputMatrix.block(iUpperBound - 2, iUpperBound - 2, 3, 3) - xPEdge*xUEdge.transpose() - xUEdge*xPEdge.transpose();
		}
		xUEdge.setZero();
	};
};

double GeometricGraphs::Distance(double dX, double dY, double dMod)
{
	double dDirectDistance = std::abs(dX - dY);
	return std::min(dDirectDistance, dMod - dDirectDistance);
};

