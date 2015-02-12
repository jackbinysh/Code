#include <vector>
#include <random>
#include <ctime>
#include <algorithm> 

class Graph
{
public:
	Graph(double dGamma, int iN);
	void GenerateDegreeSequence();
	bool ConstructGraph();
private:
	void ResetGraph();
	void ConstructNormalisedCDF();
	int GenerateNodeDegree();
	double LogSum(double a, double b);
	
	int m_iN;
	double m_dGamma;

	std::vector<int> m_xDegreeSequence;
	std::vector<int> m_xStubSequence;
	std::vector<std::vector<int>> m_xAdjacencyMatrix;
	std::vector<double> m_xCDF;

	std::mt19937 m_xEngine;
	std::uniform_real_distribution<double> m_xDistribution;
};



