#include "GeometricGraphs.h"
#include <iostream>

void GeometricGraphs::CreateLaplacian(Matrix4d& xInputMatrix, double dDistance, std::mt19937& xEngine, std::uniform_real_distribution<double>& xDistribution)
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
	std::cout << xInputMatrix << std::endl;
return;
}

void GeometricGraphs::QRAlgorithm(Matrix4d& xInputMatrix, int iNumruns)
{
	// we begin by putting the matrix in tridiagonal form

	int iN = xInputMatrix.rows();
	VectorXd xu(iN); // the vector u, made up of 0's, then the n-1 elements of the column of a
	VectorXd xp(iN); // a vector which will be used jointly for p and q

	for (int i = 0; i <= iN-3; i++)
	{
		// setting up u
		xu(i) = 0;
		xu.tail((iN - 1) - i) = xInputMatrix.block(i + 1, i, (iN - 1) - i,1);
		xu(i + 1) += xu.norm();
		// now U is set up, we work out a series of intermediate quantities
		double dH = 0.5*xu.squaredNorm();
		xp = (xInputMatrix*xu) / dH;
		double dK = (xu.dot(xp)) / (2 * dH);
		xp = (xp - dK*xu);
		xInputMatrix = xInputMatrix - xp*xu.transpose() - xu*xp.transpose();
		std::cout << xInputMatrix << std::endl;
	}
	std::cout << xInputMatrix << std::endl << "\n";
	// the matrix is now in tridiagonal form. We will now apply the QR algorithm

	Vector4d xU = Vector4d::Zero();
	Vector3d xUEdge = Vector3d::Zero();
	Vector4d xP = Vector4d::Zero();
	Vector3d xPEdge = Vector3d::Zero();

	for (int k = 1; k <= iNumruns; k++)
	{
		// okay the first nasty edge case, i =0
		xUEdge(0) = xInputMatrix(0, 0);
		xUEdge(1) = xInputMatrix(1, 0);
		xUEdge(0) += xUEdge.norm();
		double dH = 0.5*xUEdge.squaredNorm();
		xPEdge = (1 / dH)*xInputMatrix.block(0, 0, 3, 3)*xUEdge;
		double dK = (xUEdge.dot(xPEdge)) / (2 * dH);
		xPEdge = (xPEdge - dK*xUEdge);
		xInputMatrix.block(0,0, 3, 3) = xInputMatrix.block(0,0, 3, 3) - xPEdge*xUEdge.transpose() - xUEdge*xPEdge.transpose();
		xUEdge.setZero();
		std::cout << xInputMatrix << std::endl;
		// okay now the nice generic loop
		for (int i = 1; i <= iN - 3; i++)
		{
			// fill the middle two in
			xU(1) = xInputMatrix(i, i);
			xU(2) = xInputMatrix(i + 1, i);

			xU(1) += xU.norm();
			dH = 0.5*xU.squaredNorm();

			xP = (1 / dH)*xInputMatrix.block(i-1, i-1, 4, 4)*xU;
			dK = (xU.dot(xP)) / (2 * dH);
			xP = (xP - dK*xU);
			xInputMatrix.block(i-1, i-1, 4, 4) = xInputMatrix.block(i-1, i-1, 4, 4) - xP*xU.transpose() - xU*xP.transpose();
			std::cout << xInputMatrix << std::endl;
		}
		// okay now the nasty other edge case,iN-2
		xUEdge(1) = xInputMatrix(iN-2,iN-2);
		xUEdge(2) = xInputMatrix(iN - 1, iN-2);
		xUEdge(1) += xUEdge.norm();
		dH = 0.5*xUEdge.squaredNorm();
		xPEdge = (1 / dH)*xInputMatrix.block(iN - 3, iN - 3, 3, 3)*(xUEdge);
		dK = (xUEdge.dot(xPEdge)) / (2 * dH);
		xPEdge = (xPEdge - dK*xUEdge);
		xInputMatrix.block(iN - 3, iN - 3, 3, 3) = xInputMatrix.block(iN - 3, iN - 3, 3, 3) - xPEdge*xUEdge.transpose() - xUEdge*xPEdge.transpose();
		xUEdge.setZero();
		std::cout << xInputMatrix << std::endl;
	}

}

double GeometricGraphs::Distance(double dX, double dY, double dMod)
{
	double dDirectDistance = std::abs(dX - dY);
	return std::min(dDirectDistance, dMod - dDirectDistance);
};

