#include "grid.h"
#include "color.h"
#include <iostream>

Grid :: Grid() {
	 num_Rows = 20;
	 num_Cols = 10;
	 cell_Size = 30;
	 Initialize(); // Call Initialize to set up the grid
	 colors = GetCellColors(); // Get the colors for the cells
}

void Grid::Initialize() {
	for(int r = 0; r < num_Rows; r++){
		for (int c = 0; c < num_Cols; c++) {
			grid[r][c] = 0; // Initialize all cells to 0
		}
	}
}

void Grid::Print() {
	for (int r = 0; r < num_Rows; r++) {
		for (int c = 0; c < num_Cols; c++) {
			std::cout << grid[r][c] << " "; // Print each cell value
		}
		std::cout << "\n"; // New line after each row
	}
}


void Grid::Draw() {

	for (int r = 0; r < num_Rows; r++) {
		for (int c = 0; c < num_Cols; c++) {
			int cellValue = grid[r][c];
			DrawRectangle(c * cell_Size+11, r * cell_Size+11, cell_Size-1, cell_Size-1, colors[cellValue]);

		}
	}
}

bool Grid::CellOutside(int row, int column) {
	if (row >= 0 && row < num_Rows && column >= 0 && column < num_Cols) {
		return false; // Cell is outside the grid
	}
	return true; // Cell is inside the grid
}

bool Grid::IsCellEmpty(int row, int column) {
	if (grid[row][column] == 0) {
		return true; // Cell is empty
	}
	return false; // Cell is not empty
}

int Grid::ClearFullRows() {
	int com = 0;
	for(int row = num_Rows - 1; row >= 0; row--) {
		if (IsRowfull(row)) {
			ClearRow(row); // Clear the full row
			com++; // Increment the completed rows count
			
		}
		else if(com > 0)
			MoveRowDown(row, 1); // Move the rows down
	}
	return com;
}

bool Grid::IsRowfull(int row) {
	for (int column = 0; column < num_Cols; column++) {
		if (grid[row][column] == 0) {
			return false; // Row is not full
		}
	}
	return true; // Row is full
}

void Grid::ClearRow(int row) {
	for (int column = 0; column < num_Cols; column++) {
		grid[row][column] = 0; // Clear the row
	}
}

void Grid::MoveRowDown(int row, int numRows) {
	for (int column = 0; column < num_Cols; column++) {
		grid[row + numRows][column] = grid[row][column]; // Move the row down
		grid[row][column] = 0; // Clear the original row
	}
}

