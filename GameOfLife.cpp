
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const int needArguments = 1;
const int missingInput = 2;

void printTable(std::ostream &fout, int height, int width, vector<vector<char> > inputMatrix)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (inputMatrix[i][j] != '*')
			{
				int neighbours = 0;
				if (inputMatrix[i - 1][j - 1] == '#') { neighbours++; }
				if (inputMatrix[i - 1][j] == '#') { neighbours++; }
				if (inputMatrix[i - 1][j + 1] == '#') { neighbours++; }
				if (inputMatrix[i][j - 1] == '#') { neighbours++; }
				if (inputMatrix[i][j + 1] == '#') { neighbours++; }
				if (inputMatrix[i + 1][j - 1] == '#') { neighbours++; }
				if (inputMatrix[i + 1][j] == '#') { neighbours++; }
				if (inputMatrix[i + 1][j + 1] == '#') { neighbours++; }
				if (2 <= neighbours and neighbours <= 3 and inputMatrix[i][j] == '#')
				{
					fout << '#';
				}
				else if (neighbours == 3 and inputMatrix[i][j] == ' ')
				{
					fout << '#';
				}
				else
				{
					fout << ' ';
				}
			}
			else
			{
				fout << '*';
			}
		}
		fout << endl;
	}
}

int main(int argc, char* argv[])
{
	if (argc < 2) 
	{
		cout << "At least 1 argument required\n";
		return needArguments;
	}

	string inputFile(argv[1]);
	ifstream fin(inputFile);

	string outputFile;

	if (argc == 3)
	{
		outputFile = argv[2];
	}

	ofstream fout(outputFile);
	

	if (!fin.is_open()) 
	{
		cout << "Failed to open Input for reading\n";
		return missingInput;
	}

	vector<vector<char> > inputMatrix(256, vector<char>(256));

	int height = 0;
	int width = 0;

	string inputLine;

	while (getline(fin, inputLine))
	{
		char ch = ' ';
		width = 0;

		while (!inputLine.empty() and (ch == '*' || ch == '#' || ch == ' '))
		{
			ch = inputLine.front();
			inputLine.erase(0, 1);
			inputMatrix[height][width] = ch;
			width++;
		}
		height++;
	}

	if (argc == 3)
	{
		printTable(fout, height, width, inputMatrix);
	}
	else
	{
		printTable(cout, height, width, inputMatrix);
	}
	return 0;
}