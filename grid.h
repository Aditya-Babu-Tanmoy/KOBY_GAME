#pragma once
#include<vector>
#include<raylib.h>

// User Define HEader File
class Grid {
public:
	Grid();
	void Initialize();
	void Print();
	void Draw();
	bool CellOutside(int row, int column);
	bool IsCellEmpty(int row, int column);// To struct the block one by one
	int ClearFullRows();
	int grid[20][10];


private:
	bool IsRowfull(int row);
	void ClearRow(int row);
	void MoveRowDown(int row, int numRows);
	int num_Rows;
	int num_Cols;
	int cell_Size;
	std::vector<Color> colors;
};

