#include"block.h"

Block::Block() {
	cellsize = 30; // Set the cell size
	rotationState = 0; // Initialize rotation state
	colors = GetCellColors(); // Get the colors for the cells
	rowOffset = 0; // Initialize row offset
	columnOffset = 0; // Initialize column offset
	id = 0; // Initialize block ID
}

void Block::Draw(int offsetx, int offsety) {
	std::vector<Position> tiles = GetCellPostion(); // Get the current rotation state

	for (Position item : tiles) {
		int x = item.column * cellsize + offsetx; // Calculate x position
		int y = item.row * cellsize + offsety; // Calculate y position
		DrawRectangle(x, y, cellsize - 1, cellsize - 1, colors[id]); // Draw the rectangle
	}
}

void Block::Move(int rows, int colums) {
	rowOffset += rows; // Update row offset
	columnOffset += colums; // Update column offset
}

std::vector<Position> Block::GetCellPostion() {
	std::vector<Position> tiles = cells[rotationState];
	std::vector<Position> movedTiles;
	for (Position item : tiles) {
		Position newPos = Position(item.row + rowOffset, item.column + columnOffset); // Create a new position)
		movedTiles.push_back(newPos); // Add the new position to the moved tiles
	}
	return movedTiles;
}

void Block::Rotate() {
	rotationState++;
	if (rotationState == cells.size()) {
		rotationState = 0; // Reset rotation state
	}
}

void Block::UndoRotation() {
	rotationState--;
	if (rotationState == -1) {
		rotationState = cells.size() - 1; // Reset rotation state
	}
}
