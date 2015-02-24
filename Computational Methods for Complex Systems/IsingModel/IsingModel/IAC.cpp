#include "IAC.h"

IAC::IAC(int iTMax)
{
	m_iTMax = iTMax;
	m_xAbsm = std::vector<double>(m_iTMax);
	m_dTau = 0;
}

void IAC::ComputeTau()
{
	double dChiZero = chi(0);
	for (int it = 0; it <= 1000; it++)
	{
		double dChiT = chi(it);
		if (dChiT / dChiZero < pow(10, -3))
		{
			break;
		}
		m_dTau += (dChiT / dChiZero);
	}
}

double IAC::chi(int it)
{
	double iFirstTerm = 0;
	for (int itprime = 0; itprime <= m_iTMax - it -1 ; itprime++)
	{
		iFirstTerm += m_xAbsm[itprime] * m_xAbsm[itprime + it];
	};
	iFirstTerm *= (1 / (static_cast<double>(m_iTMax) - it));

	double iSecondTerm = 0;
	for (int itprime = 0; itprime <= m_iTMax - it -1 ; itprime++)
	{
		iSecondTerm += m_xAbsm[itprime];
	};
	iSecondTerm *= 1 / (static_cast<double>(m_iTMax)-it);

	double iThirdTerm = 0;
	for (int itprime = 0; itprime <= m_iTMax - it -1 ; itprime++)
	{
		iThirdTerm += m_xAbsm[itprime + it];
	};
	iThirdTerm *= 1 / (static_cast<double>(m_iTMax)-it);

	return ( iFirstTerm - (iSecondTerm*iThirdTerm) );
}