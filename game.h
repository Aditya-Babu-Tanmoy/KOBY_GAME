#pragma once
#include"grid.h"
#include"blocks_child.cpp"

class Game {
public:
	Game();
	~Game();
	int score;
	void Draw();
	void HandleInput();
	void MoveBlockDown();
	bool gameOver;
	Music music;
	
private:
	Grid grid;
	void MoveBlockLeft();
	void MoveBlockRight();
	void RotateBlock();
	void LockBlock();
	void Reset();
	void UpdateScore(int line_Clear, int moveDownPoints);
	bool BLockOutside();
	bool BlockFits();
	std::vector<Block> GetAllBlocks();
	std::vector<Block> blocks;
	Block GetRandomBlock();
	Block currentBlocks;
	Block nextBlocks;
	Sound Rotatesound;
	Sound clearsound;
};
