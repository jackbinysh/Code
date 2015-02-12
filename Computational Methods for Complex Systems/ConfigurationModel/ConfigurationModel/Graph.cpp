#define _USE_MATH_DEFINES
#include "Graph.h"

Graph::Graph(double dGamma, int iN)
{
	m_iN = iN;
	m_dGamma = dGamma;

	// initialise the mersenne twister with a random seed
	std::random_device rd;
	m_xEngine = std::mt19937(std::time(NULL));
	m_xDistribution = std::uniform_real_distribution<double>(0, 1);

	//
	m_xDegreeSequence = std::vector<int>(iN);
	m_xCDF = std::vector<double>(iN);
	m_xAdjacencyMatrix = std::vector<std::vector<int>>(iN, std::vector<int>(iN));

	ConstructNormalisedCDF();
}

//// this is the  version not using log sums
//void Graph::ConstructNormalisedCDF()
//{
//	int iKMin = 1;
//	int iKMax = m_iN - 1;
//
//	// compute the normalisation
//	double dNormalisation = 0;
//	for (int k = iKMin; k <= iKMax; k++)
//	{
//		dNormalisation += pow(k, -m_dGamma);
//	}
//
//	for (int k = iKMin; k <= iKMax; k++)
//	{
//		m_xCDF[k] = m_xCDF[k - 1] + (pow(k, -m_dGamma)/dNormalisation);
//	}
//}

// this uses log sums
void Graph::ConstructNormalisedCDF()
{
	int iKMin = 1;
	int iKMax = m_iN - 1;

	// compute the normalisation
	double dLogNormalisation = 0;
	for (int k = iKMin+1; k <= iKMax; k++)
	{
		dLogNormalisation += log1p( exp(-abs(dLogNormalisation + m_dGamma*log(k))) );
	}

	for (int k = iKMin; k <= iKMax; k++)
	{
		double x = m_xCDF[k - 1];
		double y = -m_dGamma*log(k) - dLogNormalisation;
		m_xCDF[k] = std::max(x, y) + log1p(exp(-abs(x - y)));
	}
}


void Graph::GenerateDegreeSequence()
{
	int iSum = 0;
	while (true)
	{
		iSum = 0;
		for (int n = 0; n <= m_iN - 1; n++)
		{
			m_xDegreeSequence[n] = GenerateNodeDegree();
			iSum += m_xDegreeSequence[n];
		}
		if (0 == iSum % 2) break;
	}
	// now build the stub sequence for easy sampling
	m_xStubSequence = std::vector<int>(iSum);
	int iCounter = 0;
	for (int n = 0; n <= m_iN - 1; n++)
	{
		int iNumReps = m_xDegreeSequence[n];
		for (int i = 0; i <= iNumReps-1; i++)
		{
			m_xStubSequence[iCounter] = n;
			iCounter++;
		}
	}
	return;
}

bool Graph::ConstructGraph()
{
	std::uniform_int_distribution<int> xStubDistribution(0, m_xStubSequence.size() - 1);

	int iMistakeCounter = 0;
	bool bExit = false;
	bool bSuccess = false;
	while (!bExit)
	{
		int iFirstStubLocation = xStubDistribution(m_xEngine);
		int iFirstStub = m_xStubSequence[iFirstStubLocation];
		int iSecondStubLocation = xStubDistribution(m_xEngine);
		int iSecondStub = m_xStubSequence[iSecondStubLocation];


		if ( (iFirstStub != iSecondStub) && (0 == m_xAdjacencyMatrix[iFirstStub][iSecondStub]) )
		{
			if (m_xStubSequence.size() > 2)
			{
				// success, assign adjacency matrix, reset mistake counter, fiddle degree sequence
				m_xAdjacencyMatrix[iFirstStub][iSecondStub] = 1;
				m_xAdjacencyMatrix[iSecondStub][iFirstStub] = 1;
				// we now  remove these elements from the list, 
				m_xStubSequence.erase(m_xStubSequence.begin() + iFirstStubLocation);
				m_xStubSequence.erase(m_xStubSequence.begin() + ((iSecondStubLocation>iFirstStubLocation)? iSecondStubLocation-1:iSecondStubLocation));
				// decrease the upper bound of the random number generator by 2
				xStubDistribution.param(std::uniform_int_distribution<int>::param_type(0, xStubDistribution.b() - 2));
				iMistakeCounter = 0;
			}
			else
			{
				bExit = true;
				bSuccess = true;
			}

		}
		else
		{
			iMistakeCounter++;
			if (10 == iMistakeCounter) bExit = true;
		}
	}
	// cleanup
	for (int i = 0; i <= m_xAdjacencyMatrix.size() - 1; i++)
	{
		for (int j = 0; j <= m_xAdjacencyMatrix.size() - 1; j++)
		{
			m_xAdjacencyMatrix[i][j] = 0;
		}
	}
	return bSuccess;
}

int Graph::GenerateNodeDegree()
{
	double dUniformRV = m_xDistribution(m_xEngine);
	int x = 0;
	while (m_xCDF[x] <= log1p(dUniformRV)) x++;
	return x;
}

// not log sums
//int Graph::GenerateNodeDegree()
//{
//	double dUniformRV = m_xDistribution(m_xEngine);
//	int x = 0;
//	while (m_xCDF[x] <= dUniformRV) x++;
//	return x;
//}

