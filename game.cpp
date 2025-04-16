#include"game.h"
#include"grid.h"
#include<random>


Game::Game() {
	grid = Grid();
	blocks = GetAllBlocks(); // Initialize the blocks
	currentBlocks = GetRandomBlock(); // Get a random block
	nextBlocks = GetRandomBlock(); // Get the next random block
	gameOver = false; // Initialize game over state
	score = 0; // Initialize score
	InitAudioDevice(); // Initialize audio device
	music = LoadMusicStream("Sound/Game_title.mp3"); // Load the music
	PlayMusicStream(music); // Play the music
}
Game::~Game() {
	UnloadMusicStream(music); // Unload the music
	CloseAudioDevice(); // Close audio device
}

Block Game::GetRandomBlock() {
	if(blocks.empty()){
		blocks = GetAllBlocks(); // Reset the blocks if empty
	}
	int randomIndex = rand() % blocks.size(); // Generate a random index
	Block Block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
	return Block;
}

std::vector <Block> Game:: GetAllBlocks() {
	return {Lblock(), Jblock(), Iblock(), Oblock(), Sblock(), Tblock(), Zblock()};
}

void Game::Draw() {
	grid.Draw(); // Draw the grid
	currentBlocks.Draw(11, 11); // Draw the current block
	switch (nextBlocks.id) {
	case 3:
		nextBlocks.Draw(255, 290);
		break;
	case 4:
		nextBlocks.Draw(255, 280);
		break;
	default:
		nextBlocks.Draw(270, 270);
		break;	

	}
}
void Game::HandleInput() {
	int keyPressed = GetKeyPressed(); // Get the key pressed
	if (gameOver && keyPressed != 0) { // If the game is over and a key is pressed
		gameOver = false; 
		Reset();
	}
	switch (keyPressed) {
	case KEY_LEFT:
		MoveBlockLeft(); // Move the block left
		break;
	case KEY_RIGHT:
		MoveBlockRight(); // Move the block right
		break;
	case KEY_DOWN:
		MoveBlockDown(); // Move the block down
		UpdateScore(0, 1); // Update the score
		break;
	case KEY_UP:
		RotateBlock(); // Rotate the block
		break;

	}
}
void Game::MoveBlockLeft() {
	if (!gameOver) {

		currentBlocks.Move(0, -1); // Move the block left
		if (BLockOutside() || !BlockFits()) { // Check if the block is outside
			currentBlocks.Move(0, 1); // Move it back to the right
		}
	}
}
void Game::MoveBlockRight() {
	if (!gameOver) {

		currentBlocks.Move(0, 1); // Move the block left
		if (BLockOutside() || !BlockFits()) { // Check if the block is outside
			currentBlocks.Move(0, -1); // Move it back to the left
		}
	}
}
void Game::MoveBlockDown() {
	if (!gameOver) {
		currentBlocks.Move(1, 0); // Move the block down
		if (BLockOutside() || !BlockFits()) { // Check if the block is outside
			currentBlocks.Move(-1, 0); // Move it back up
			LockBlock(); // Lock the block to not to move in the Downwith
		}
	}
}
bool Game::BLockOutside() {
	std::vector<Position> tiles = currentBlocks.GetCellPostion(); // Get the current position of the block
	for (Position item : tiles) {
		if(grid.CellOutside(item.row, item.column)) { // Check if the block is outside the grid
			return true; // Block is outside
		}
	}
	return false; // Block is inside
}

void Game::RotateBlock() {
	if (!gameOver) {

		currentBlocks.Rotate(); // Rotate the block
		if (BLockOutside() || !BlockFits()) { // Check if the block is outside
			currentBlocks.UndoRotation(); // Undo the rotation
		}
	}

}

void Game::LockBlock() {
	std::vector<Position> tiles = currentBlocks.GetCellPostion();
	for (Position item : tiles) {
		grid.grid[item.row][item.column] = currentBlocks.id;
	}
	currentBlocks = nextBlocks; // Set the current block to the next block
	if (!BlockFits()) {
		gameOver = true;// Set game over if the block doesn't fit
	}

	nextBlocks = GetRandomBlock(); // Get a new random block	
	int rowsCleared = grid.ClearFullRows(); // Clear the full rows
	UpdateScore(rowsCleared, 0);
}

bool Game::BlockFits(){
	std::vector<Position> tiles = currentBlocks.GetCellPostion(); // Get the current position of the block
	for (Position item : tiles) {
		if (grid.IsCellEmpty(item.row, item.column) == false) { // Check if the block is outside the grid
			return false; // Block is outside
		}
	}
	return true; // Block fits in the grid
}
void Game::Reset() {
	grid.Initialize(); // Initialize the grid
	blocks = GetAllBlocks(); // Initialize the blocks
	currentBlocks = GetRandomBlock(); // Get a random block
	nextBlocks = GetRandomBlock(); // Get the next random block	
	score = 0; // Reset the score
}

void Game::UpdateScore(int line_Clear, int moveDownPoints)// count the score
{
	switch (line_Clear)
	{
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	case 4:
		score += 700;
		break;
	case 5:
		score += 1000;
		break;
	default:
		break;
	}
	score += moveDownPoints;
}

