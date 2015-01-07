#include <math.h>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	float afX[41][5] = { 0 }; // I'll just leave the 0 indexed bit blank
	double adX[41][5] = { 0 };

	for (int i = 1; i <= 40; i++)
	{
		// floats
		float fEpsilon = pow(static_cast<float>(3)/2, static_cast<float>( -i ));

		// float x+, methods 8 and 9
		afX[i][1] = (static_cast<float>(3) / 2) * (1 + sqrt(1 - fEpsilon));
		afX[i][2] = (static_cast<float>(3) / 2) * fEpsilon * (1 / (1 - sqrt(1 - fEpsilon)));
		// float x-, methods 8 and 9
		afX[i][3] = (static_cast<float>(3) / 2) * (1 - sqrt(1 - fEpsilon));
		afX[i][4] = (static_cast<float>(3) / 2) * fEpsilon * (1 / (1 + sqrt(1 - fEpsilon)));

		// doubles
		double dEpsilon = pow(static_cast<double>(3)/2, static_cast<double>( -i ));

		// double x+, methods 8 and 9
		adX[i][1] = (static_cast<float>(3) / 2) * (1 + sqrt(1 - dEpsilon));
		adX[i][2] = (static_cast<float>(3) / 2) * dEpsilon * (1 / (1 - sqrt(1 - dEpsilon)));
		// double x-, methods 8 and 9
		adX[i][3] = (static_cast<float>(3) / 2) * (1 - sqrt(1 - dEpsilon));
		adX[i][4] = (static_cast<float>(3) / 2) * dEpsilon * (1 / (1 + sqrt(1 - dEpsilon)));
	}

	// output

	ofstream xFloatOutput("FloatResults.txt");

	if (xFloatOutput.is_open())
	{
		for (int i = 1; i <= 40; i++)
		{
			xFloatOutput << afX[i][1] << "\t" << afX[i][2] << "\t" << afX[i][3] << "\t" << afX[i][4] << "\n";
		}
	}

	xFloatOutput.close();

	ofstream xDoubleOutput("DoubleResults.txt");

	if (xDoubleOutput.is_open())
	{
		for (int i = 1; i <= 40; i++)
		{
			xDoubleOutput << adX[i][1] << "\t" << adX[i][2] << "\t" << adX[i][3] << "\t" << adX[i][4] << "\n";
		}
	}

	xDoubleOutput.close();
	return 0;
}