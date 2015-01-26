#include <vector>
#include <random>
#include <Eigen/Dense>

using namespace Eigen;

namespace GeometricGraphs
{
	typedef  Matrix<double, 4, 4> MyMatrix;
	typedef Matrix<double, 4, 1> MyVector;

	void CreateLaplacian(MyMatrix& xInputMatrix, double dDistance, std::mt19937& xEngine, std::uniform_real_distribution<double>& xDistribution);

	// a function which takes a symettric matrix and tridiagonalises it
	void TriDiag(MyMatrix& xInputMatrix);
	// function which implements to QR algorithm on a tridiagonal input matrix to find eigenvalues.
	void QRAlgorithm(MyMatrix& xInputMatrix, int iNumiterations, double dEpsilon);
	//function which encodes the distance between two nodes, with a period given by Mod
	double Distance(double dX, double dY, double Mod);
}