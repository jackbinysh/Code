#include <vector>
#include <random>

namespace GeometricGraphs
{
	void CreateLaplacian(std::vector<std::vector<double>>& xInputMatrix, double dDistance, std::mt19937& xEngine, std::uniform_real_distribution<double>& xDistribution);
	//function which encodes the distance between two nodes, with a period given by Mod
	double Distance(double dX, double dY, double Mod);
}