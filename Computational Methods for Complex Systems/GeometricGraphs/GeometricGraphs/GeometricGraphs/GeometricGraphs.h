#include <vector>
#include <random>
#include <Eigen/Dense>

using namespace Eigen;

namespace GeometricGraphs
{
	void CreateLaplacian(Matrix4d& xInputMatrix, double dDistance, std::mt19937& xEngine, std::uniform_real_distribution<double>& xDistribution);
	// function which implements to QR algorithm on a tridiagonal matrix to find eigenvalues.
	void QRAlgorithm(Matrix4d& xInputMatrix, int iNumruns);
	//function which encodes the distance between two nodes, with a period given by Mod
	double Distance(double dX, double dY, double Mod);
}