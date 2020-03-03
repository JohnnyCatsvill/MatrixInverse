
#include <iostream>
#include <fstream>
using namespace std;

int matrixDeterminant3(float m[3][3])
{
	return 
		(
			m[0][0] * m[1][1] * m[2][2] +
			m[0][1] * m[1][2] * m[2][0] +
			m[0][2] * m[1][0] * m[2][1] -
			m[0][0] * m[1][2] * m[2][1] -
			m[0][1] * m[1][0] * m[2][2] -
			m[0][2] * m[1][1] * m[2][0]
		);
}

int matrixOfMinors3(float in[3][3], float out[3][3])
{
	const int minorElements3[2][3][3][4] =
	{
		{
			{
				{1, 1, 2, 2},
				{1, 1, 2, 2},
				{1, 1, 2, 2}
			},
			{
				{0, 0, 2, 2},
				{0, 0, 2, 2},
				{0, 0, 2, 2}
			},
			{
				{0, 0, 1, 1},
				{0, 0, 1, 1},
				{0, 0, 1, 1}
			}
		},
		{
			{
				{1, 2, 1, 2},
				{0, 2, 0, 2},
				{0, 1, 0, 1}
			},
			{
				{1, 2, 1, 2},
				{0, 2, 0, 2},
				{0, 1, 0, 1}
			},
			{
				{1, 2, 1, 2},
				{0, 2, 0, 2},
				{0, 1, 0, 1}
			}
		}
	};

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			out[i][j] = in[minorElements3[0][i][j][0]][minorElements3[1][i][j][0]] *
						in[minorElements3[0][i][j][3]][minorElements3[1][i][j][3]] -
						in[minorElements3[0][i][j][1]][minorElements3[1][i][j][1]] *
						in[minorElements3[0][i][j][2]][minorElements3[1][i][j][2]];
		}
	}
	return 0;
}

int matrixTranspose3(float in[3][3], float out[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			out[i][j] = in[j][i];
		}
	}
	return 0;
}

int matrixOfAlgebraicAdditions3(float in[3][3], float out[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 0 && j == 1 || i == 1 && j == 0 || i == 1 && j == 2 || i == 2 && j == 1)
			{
				out[i][j] = -in[i][j];
			}
			else
			{
				out[i][j] = in[i][j];
			}
		}
	}
	return 0;
}

int matrixInverse3(float in[3][3], float out[3][3])
{
	int determinant = matrixDeterminant3(in);

	if (determinant == 0) {
		return 1;
	}

	float temporalMatrix[3][3];
	matrixOfMinors3(in, temporalMatrix);
	matrixOfAlgebraicAdditions3(temporalMatrix, out);
	matrixTranspose3(out, temporalMatrix);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			out[i][j] = 1/determinant *temporalMatrix[i][j];
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << "1 Arguments required\n";
		return 2;
	}

	string inputFile(argv[1]);
	ifstream fin(inputFile);

	if (!fin.is_open()) {
		cout << "Failed to open Input for reding\n";
		return 2;
	}

	float inputMatrix[3][3];
	float outputMatrix[3][3];

	for (int i = 0; i < 3; i++) 
	{
		for (int j = 0; j < 3; j++)
		{
			fin >> inputMatrix[i][j];
		}
	}

	int error = matrixInverse3(inputMatrix, outputMatrix);

	if (error == 1)
	{
		cout << "Determinant equals 0";
		return 1;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << outputMatrix[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
