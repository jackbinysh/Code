#include <vector>
#include <random>
#include <Eigen/Dense>

using namespace Eigen;

namespace GeometricGraphs
{
	typedef  Matrix<double, 100, 100> MyMatrix;
	typedef Matrix<double, 100, 1> MyVector;

	void CreateLaplacian(MyMatrix& xInputMatrix, double dDistance, std::mt19937& xEngine, std::uniform_real_distribution<double>& xDistribution);

	// a function which takes a symettric matrix and tridiagonalises it
	void TriDiag(MyMatrix& xInputMatrix);
	// function which implements to QR algorithm on a tridiagonal input matrix to find eigenvalues.
	void QRAlgorithm(MyMatrix& xInputMatrix, int iLowerBound, int iUpperBound, double dEpsilon);
	// a single transformation in the QR algorithm
	void QRSweep(MyMatrix& xInputMatrix, int iLowerBound, int iUpperBound, double dEpsilon);
	//function which encodes the distance between two nodes, with a period given by Mod
	double Distance(double dX, double dY, double Mod);
}