#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

int quantifyRow (char rowC)
{
	if (rowC < 90)
		return rowC - 64;
	return rowC - 96;
}

bool boxCheck (int grid[9][9], int & numEmpty)
{
	bool isNumAdded = false;
	for (int startColumn = 0; startColumn <= 6; startColumn +=3)
	{
		for (int startRow = 0; startRow <= 6; startRow +=3)
		{
			for (int currentNum = 1; currentNum <= 9; currentNum++)
			{
				bool isFound = false;
				bool possible [3][3];
				for (int i=0; i < 3; i++)
					for (int j=0; j < 3; j++)
						possible [i][j] = true;
				int numPossible = 9;
				for (int currentRow = startRow; currentRow < startRow + 3; currentRow++)
				{
					for (int currentColumn = startColumn; currentColumn < startColumn + 3; currentColumn++)
					{
						if (grid[currentRow][currentColumn] != 0)
						{
							possible [currentRow-startRow][currentColumn-startColumn] = false;
							numPossible--;
						}
						if (grid[currentRow][currentColumn] == currentNum)
							isFound = true;
					}
				}
				if (!isFound && numPossible > 1)
				{
					int cluesFound = 0, clueRow1, clueRow2;
					for (int scanRow = startRow; scanRow <= startRow + 2; scanRow++)
					{
						for (int scanColumn = 0; scanColumn < 9; scanColumn++)
						{
							if (grid[scanRow][scanColumn] == currentNum && cluesFound == 1)
							{
								cluesFound++;
								clueRow2 = scanRow - startRow;
							}
							if (grid[scanRow][scanColumn] == currentNum && cluesFound == 0)
							{
								cluesFound++;
								clueRow1 = scanRow - startRow;
							}	
						}
					}
					if (cluesFound > 0)
					{
						for (int j=0; j<3; j++)
						{
							numPossible -= possible [clueRow1][j];
							possible [clueRow1][j] = false;
						}
						if (cluesFound == 2)
						{
							for (int j=0; j<3; j++)
							{
								numPossible -= possible [clueRow2][j];
								possible [clueRow2][j] = false;
							}
						}
					}
					cluesFound = 0;
					int clueColumn1, clueColumn2;
					for (int scanColumn = startColumn; scanColumn <= startColumn + 2; scanColumn++)
					{
						for (int scanRow = 0; scanRow < 9; scanRow++)
						{
							if (grid[scanRow][scanColumn] == currentNum && cluesFound == 1)
							{
								cluesFound++;
								clueColumn2 = scanColumn - startColumn;
							}
							if (grid[scanRow][scanColumn] == currentNum && cluesFound == 0)
							{
								cluesFound++;
								clueColumn1 = scanColumn - startColumn;
							}
						}
					}
					if (cluesFound > 0)
					{
						for (int i=0; i<3; i++)
						{
							numPossible -= possible [i][clueColumn1];
							possible [i][clueColumn1] = false;
						}
						if (cluesFound == 2)
						{
							for (int i=0; i<3; i++)
							{
								numPossible -= possible [i][clueColumn2];
								possible [i][clueColumn2] = false;
							}
						}
					}	
				}
				if (!isFound && numPossible == 1)
				{
					for (int i=0; i<3; i++)
						for (int j=0; j<3; j++)
							if (possible [i][j])
								grid [startRow + i][startColumn + j] = currentNum;
					numEmpty--;
					isNumAdded = true;					
				}
			}
		}
	}
	return isNumAdded;
}

bool rowCheck (int grid[9][9], int & numEmpty)
{
	bool isNumAdded = false, isFound = false;
	bool possible [9];
	for (int row = 0; row < 9; row++)
	{
		for (int currentNum = 1; currentNum <= 9; currentNum++)
		{
			isFound = false;
			for (int i=0; i < 9; i++)
				possible [i] = true;
			int numPossible = 9;
			for (int i=0; i<9; i++)
			{
				if (grid [row][i] != 0)
				{
					possible [i] = false;
					numPossible--;
				}
				if (grid [row][i] == currentNum)
					isFound = true;
			}
			for (int i=0; i<9; i++)
				for (int j=0; j<9; j++)
					if (grid [i][j] == currentNum)
					{
						numPossible -= possible [j];
						possible [j] = false;
					}
			int startRow = (row/3)*3;
			for (int rowCheck = startRow; rowCheck <= startRow + 2; rowCheck++)
			{
				for (int i=0; i<3; i++)
					if (grid [rowCheck][i] == currentNum)
						for (int j=0; j<3; j++)
						{
							numPossible -= possible [j];
							possible [j] = false;
						}
				for (int i=3; i<6; i++)
					if (grid [rowCheck][i] == currentNum)
						for (int j=3; j<6; j++)
						{
							numPossible -= possible [j];
							possible [j] = false;
						}
				for (int i=6; i<9; i++)
					if (grid [rowCheck][i] == currentNum)
						for (int j=6; j<9; j++)
						{
							numPossible -= possible [j];
							possible [j] = false;
						}
			}
			if (!isFound && numPossible == 1)
			{
				for (int i=0; i<9; i++)
					if (possible [i])
						grid [row][i] = currentNum;
				numEmpty--;
				isNumAdded = true;
			}
		}
	}
	return isNumAdded;
}

bool columnCheck (int grid[9][9], int & numEmpty)
{
	bool isNumAdded = false, isFound = false;
	bool possible [9];
	for (int column = 0; column < 9; column++)
	{
		for (int currentNum = 1; currentNum <= 9; currentNum++)
		{
			isFound = false;
			for (int i=0; i < 9; i++)
				possible [i] = true;
			int numPossible = 9;
			for (int i=0; i<9; i++)
			{
				if (grid [i][column] != 0)
				{
					possible [i] = false;
					numPossible--;
				}
				if (grid [i][column] == currentNum)
					isFound = true;
			}
			for (int i=0; i<9; i++)
				for (int j=0; j<9; j++)
					if (grid [i][j] == currentNum)
					{
						numPossible -= possible [i];
						possible [i] = false;
					}
			int startColumn = (column/3)*3;
			for (int columnCheck = startColumn; columnCheck <= startColumn + 2; columnCheck++)
			{
				for (int i=0; i<3; i++)
					if (grid [i][columnCheck] == currentNum)
						for (int j=0; j<3; j++)
						{
							numPossible -= possible [j];
							possible [j] = false;
						}
				for (int i=3; i<6; i++)
					if (grid [i][columnCheck] == currentNum)
						for (int j=3; j<6; j++)
						{
							numPossible -= possible [j];
							possible [j] = false;
						}
				for (int i=6; i<9; i++)
					if (grid [i][columnCheck] == currentNum)
						for (int j=6; j<9; j++)
						{
							numPossible -= possible [j];
							possible [j] = false;
						}
			}
			if (!isFound && numPossible == 1)
			{
				for (int i=0; i<9; i++)
					if (possible [i])
						grid [i][column] = currentNum;
				numEmpty--;
				isNumAdded = true;
			}
		}
	}
	return isNumAdded;
}

bool notCheck (int grid[9][9], int & numEmpty)
{
	bool isNumAdded = false;
	bool possible [9];
	int numPossible = 9;
	for (int row=0; row<9; row++)
		for (int column=0; column<9; column++)
			if (grid [row][column] == 0)
			{
				for (int i=0; i<9; i++)
					possible [i] = true;
				numPossible = 9;
				for (int rowScan=0; rowScan < 9; rowScan++)
					if (grid [rowScan][column] != 0)
					{
						numPossible -= possible [grid [rowScan][column] - 1];
						possible [grid [rowScan][column] - 1] =  false;
					}
				for (int columnScan=0; columnScan < 9; columnScan++)
					if (grid [row][columnScan] != 0)
					{
						numPossible -= possible [grid [row][columnScan] - 1];
						possible [grid [row][columnScan] - 1] = false;
					}
				int rowStart =(row/3)*3, columnStart =(column/3)*3; 
				for (int rowBox = rowStart; rowBox <= rowStart + 2; rowBox++)
					for (int columnBox = columnStart; columnBox <= columnStart + 2; columnBox++)
						if (grid [rowBox][columnBox] != 0)
						{
							numPossible -= possible [grid [rowBox][columnBox] - 1];
							possible [grid [rowBox][columnBox] - 1] = false;
						}
				if (numPossible == 1)
				{
					for (int i=0; i<9; i++)
						if (possible [i])
							grid [row][column] = i + 1;
					numEmpty--;
					isNumAdded = true;							
				}
			}
	return isNumAdded;
}

int main ()
{
	int grid[9][9];
	for (int i=0; i < 9; i++)
		for (int j=0; j < 9; j++)
			grid[i][j] = 0;
	ifstream fin ("givens_medium.txt");
	char rowC;
	int rowI, column, given, numEmpty = 81;
	while (fin >> rowC >> column >> given)
	{
		rowI = quantifyRow (rowC);
		if (rowI < 1 || rowI > 9)
		{
			cout << "Invalid row entry" << endl;
			return EXIT_FAILURE;
		}
		if (column < 1 || column > 9)
		{
			cout << "Invalid column entry" << endl;
			return EXIT_FAILURE;
		}
		grid[rowI-1][column-1] = given;
		numEmpty--;
	}
	bool isNumAdded = true;
	while (isNumAdded)
	{
		isNumAdded = boxCheck (grid, numEmpty) || rowCheck (grid, numEmpty) || columnCheck (grid, numEmpty) || notCheck (grid, numEmpty);
	}
	for (int i=0; i < 9; i++)
	{
		for (int j=0; j < 9; j++)
			 cout << grid[i][j] << " ";
		cout << endl;
	}
	cout << endl << numEmpty << endl;
	return EXIT_SUCCESS;
}