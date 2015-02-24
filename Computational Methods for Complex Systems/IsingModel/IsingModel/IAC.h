#include <vector>

class IAC
{
public:
	IAC(int iTMax);
	void ComputeTau();

	void setm( int iIndex, double dvalue){m_xAbsm[iIndex] = dvalue;}
	double getTau() const { return m_dTau; }
private:
	// internal function to give x
	double chi(int it);
	//the data
	std::vector< double> m_xAbsm;
	int m_iTMax;
	// the running total
	double m_dTau;
};