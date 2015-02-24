#include <vector>

class IsingModel
{
public:
	IsingModel(int iLatticeSize);
	void Initialise(double dTemp);
	void Sweep();
	const int getE() const { return m_iE; };
	const int getM() const { return m_iM; };
private:
	int NumSpinsDifferent(int i, int j);
	void UpdateStatistics();

	// parameters 
	double m_dTemp;
	int m_iLatticeSize;
	// the current energy and magnetisation
	int m_iE;
	int m_iM;
	//the lattice
	std::vector< std::vector<int> > m_xLattice;
	// stored boltzman factors
	std::vector<double> m_xEnergyFactors;
	// random number generators
	//std::mt19937 m_xEngine;
	//std::uniform_real_distribution<double> m_xSpinFlipProbability;
	//std::uniform_int_distribution<int> m_xLatticeSiteChoice;

};
