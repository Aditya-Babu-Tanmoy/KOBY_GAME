#pragma once
#include<vector>
#include<map>
#include"position.h"
#include"color.h"

class Block {
public:
	Block();
	void Draw(int offsetx, int offsety);
	void Move(int rows, int colums);
	std::vector<Position> GetCellPostion();
	void Rotate();
	void UndoRotation();
	int id;
	std::map<int, std::vector<Position>> cells;


private:
	int cellsize;
	int rotationState;
	std::vector<Color> colors;
	int rowOffset;
	int columnOffset;


};
