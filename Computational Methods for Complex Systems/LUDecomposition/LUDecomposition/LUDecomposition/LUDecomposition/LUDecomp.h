#include <vector>

class LUDecomp
{
public:
	// performs an LU Decomposition. returns 0 if the decomposition occured, 1 if the matrix is singular and it did not
	static bool LUDecompose(std::vector<std::vector<double>>& xInputMatrix);
	// runs a check for columns of all 0's
private:
	static bool ZeroRowCheck(std::vector<std::vector<double>>& xInputMatrix);
	// implements pivoting within the decomposition, keeping track of the permutation and its parity.
	// the function also checks if the matrix is singular. if it is, it sets the bool to 1.
	static bool Pivot(int j, std::vector<std::vector<double>>& xInputMatrix);
		
};