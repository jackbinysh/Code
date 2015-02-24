#include "IsingModel.h"
#include "mtwist.h"
#include <ctime>
#include <cmath>

void IsingModel::Sweep()
{
	for (int iMove = 1; iMove <= m_iLatticeSize* m_iLatticeSize; iMove++)
	{
		//choose a random lattice site
		int i = std::floor(m_iLatticeSize*mt_drand());
		int j = std::floor(m_iLatticeSize*mt_drand());
		//int i = m_xLatticeSiteChoice(m_xEngine);
		//int j = m_xLatticeSiteChoice(m_xEngine);

		int iNumSpinsDifferent = NumSpinsDifferent(i, j);
		if (/*m_xSpinFlipProbability(m_xEngine)*/mt_drand() < m_xEnergyFactors[iNumSpinsDifferent])
		{
			// flip the spin
			m_xLattice[i][j] *= -1;
			m_iM += (2 * m_xLattice[i][j]);
			m_iE += 4 * (2 - iNumSpinsDifferent);

		}
	}
}

IsingModel::IsingModel(int iLatticeSize)
{
	// variable initialisation
	m_iLatticeSize = iLatticeSize;
	m_xLattice = std::vector< std::vector<int> >(m_iLatticeSize, std::vector<int>(m_iLatticeSize));	
	m_xEnergyFactors = std::vector<double>(5);

	// random number generator intilisation and seeding
	mt_seed();
	//m_xEngine = std::mt19937(std::time(NULL));
	//m_xLatticeSiteChoice = std::uniform_int_distribution<int>(0, m_iLatticeSize -1);
	//m_xSpinFlipProbability = std::uniform_real_distribution<double>(0, 1);
}

void IsingModel::Initialise(double dTemp)
{
	m_dTemp = dTemp;

	// set the boltzman factors
	m_xEnergyFactors[0] = exp(-8.0 / m_dTemp); // All spins are equal to the one seeded	DeltaE =  8
	m_xEnergyFactors[1] = exp(-4.0 / m_dTemp); // 1 spin  is  different			DeltaE =  4
	m_xEnergyFactors[2] = 1.0;		    // 2 spins are different			DeltaE =  0
	m_xEnergyFactors[3] = exp(4.0 / m_dTemp);  // 3 spins are different			DeltaE = -4
	m_xEnergyFactors[4] = exp(8.0 / m_dTemp);  // All spins are different			DeltaE = -8
	
	// initialise the lattice to a random state
	for (int i = 0; i <= m_iLatticeSize - 1; i++)
	{
		for (int j = 0; j <= m_iLatticeSize - 1; j++)
		{
			m_xLattice[i][j] = ( mt_drand()>0.5 )? 1:-1;
			//m_xLattice[i][j] = ( m_xSpinFlipProbability(m_xEngine)>0.5 )? 1:-1;
			//m_xLattice[i][j] = 1;
		}
	}
	//Initial M
	m_iM = 0;
	for (int i = 0; i <= m_iLatticeSize - 1; i++)
	{
		for (int j = 0; j <= m_iLatticeSize - 1; j++)
		{
			m_iM += m_xLattice[i][j] ;
		}
	}
	//initial E
	m_iE = 0;
	for (int i = 0; i <= (m_iLatticeSize - 1); i++)
	{
		for (int j = 0; j <= (m_iLatticeSize - 1); j++)
		{
			m_iE -= m_xLattice[i][j] * m_xLattice[i == (m_iLatticeSize - 1) ? 0 : i + 1][j];
			m_iE -= m_xLattice[i][j] * m_xLattice[i][j == (m_iLatticeSize - 1) ? 0 : j + 1];
		}
	}
}

int IsingModel::NumSpinsDifferent(int i, int j)
{
	int iCentreSpin = m_xLattice[i][j];
	int iDiff = 0;

	if (m_xLattice[i == 0 ? m_iLatticeSize - 1 : i - 1][j] != iCentreSpin) iDiff++;
	if (m_xLattice[i == m_iLatticeSize - 1 ? 0 : i + 1][j] != iCentreSpin) iDiff++;
	if (m_xLattice[i][j == 0 ? m_iLatticeSize - 1 : j - 1] != iCentreSpin) iDiff++;
	if (m_xLattice[i][j == m_iLatticeSize - 1 ? 0 : j + 1] != iCentreSpin) iDiff++;

	return iDiff;
}