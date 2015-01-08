#include "LUDecomp.h"

LUDecomp::LUDecomp(std::vector<std::vector<double>>& xA)
{
	m_iN = xA[0].size();
	m_bIsSingular = false;
	m_xLUDecomp = xA;
	m_dTolerance = 10 ^ -9;
	
	m_xPermutation.resize(m_iN);
	for (int i = 0; i <= m_iN - 1; i++)
	{
		m_xPermutation[i] = i;
	}

	ZeroRowCheck();

	for (int j = 0; j <= m_iN - 1; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			double dtemp = 0;
			for (int k = 0; k <= j - 1; k++)
			{
				dtemp += m_xLUDecomp[i][k] * m_xLUDecomp[k][j];
			}
			m_xLUDecomp[i][j] = m_xLUDecomp[i][j] - dtemp;
		}
		for (int i = j+1; i <= m_iN-1; i++)
		{
			double dtemp = 0;
			for (int k = 0; k <= j - 1; k++)
			{
				dtemp += m_xLUDecomp[i][k] * m_xLUDecomp[k][j];
			}
			//we implement pivoting, so we don't do the division here
			m_xLUDecomp[i][j] = m_xLUDecomp[i][j] - dtemp;
		}
		Pivot(j);
		// divide all of the others by our new diagonal element
		for (int i = j + 1; i <= m_iN - 1; i++)
		{
			m_xLUDecomp[i][j] = m_xLUDecomp[i][j] / m_xLUDecomp[j][j];
		}

	}
}

void LUDecomp::Pivot(int j)
{
	double dLargestValue = 0.0;
	int iLargestIndex = j;
	for (int i = j; i <= m_iN - 1; i++)
	{
		double dTemp = abs(m_xLUDecomp[i][j]);
		if (dTemp > dLargestValue)
		{
			dLargestValue = dTemp;
			iLargestIndex = i;
		}
	}
	// if the pivoting returns a largest magnitude of 0, the matrix is singular. we set the bool and return
	if (abs(dLargestValue) - m_dTolerance < 0)
	{
		m_bIsSingular = 1;
		return;
	}
	// if we need to pivot rows, do so
	if (iLargestIndex != j)
	{
		for (int k = j; k <= m_iN - 1; k++)
		{
			double temp = m_xLUDecomp[j][k];
			m_xLUDecomp[j][k] = m_xLUDecomp[iLargestIndex][k];
			m_xLUDecomp[iLargestIndex][k] = temp;
		}
	}
	return;
}

void LUDecomp::ZeroRowCheck()
{
	for (int i = 0; i <= m_iN - 1; i++)
	{
		for (int j = 0; j <= m_iN - 1; j++)
		{
			if (m_xLUDecomp[i][j])
			{
				break;
			}
		}
		m_bIsSingular = true;
		return;
	}
	return;
}