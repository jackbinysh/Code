#include "LUDecomp.h"
#include <time.h>

std::vector<std::vector<double>> ERGraph(int iN, double dP);

int main()
{
	srand(time(0));

	//std::vector<std::vector<double>> xA = { { 1, 2, -3 }, { 2, 1, 4 }, { 1, 1, 0 } };
	//std::vector<std::vector<double>> xA = { { 0,0,1 }, { 1,0,0 }, { 0,1,0 } };
	std::vector<std::vector<double>>  xA = ERGraph(100, 0.3);
	LUDecomp x = LUDecomp(xA);
	return 0;
}

std::vector<std::vector<double>> ERGraph(int iN, double dP)
{
	std::vector<std::vector<double>> x(iN, std::vector<double>(iN));
	for (int i = 0; i <= iN - 1; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if ((static_cast<double>(rand()) / RAND_MAX) < dP)
			{
				x[i][j] = 1;
				x[j][i] = 1;
			}
			else
			{
				x[i][j] = 0;
				x[j][i] = 0;
			}				
		}
	}
	for (int i = 0; i <= iN - 1; i++)
	{
		x[i][i] = 0;
	}
	return x;
}