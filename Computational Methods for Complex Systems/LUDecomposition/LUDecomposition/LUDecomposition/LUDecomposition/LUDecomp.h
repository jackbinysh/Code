#include <vector>

class LUDecomp
{
public:
	LUDecomp(std::vector<std::vector<double>>& xA);
private:
	// runs a check for columns of all 0's 
	void ZeroRowCheck();
	// implements pivoting within the decomposition, keeping track of the permutation and its parity.
	// the function also checks if the matrix is singular. if it is, it sets the bool to 1.
	void Pivot(int j);
	// private internal data
	std::vector<std::vector<double>> m_xLUDecomp;

	std::vector<int> m_xPermutation;
	bool m_bIsSingular;
	int m_iN;

	double m_dTolerance;
};