#include<raylib.h>
#include<iostream>
#include<string>
#include<cstdio>
#include"game.h"// Include the game header file
#include"color.h"

double lastUpdateTime = 0;

bool EvenTriggered(double interval) {
	
	double currentTime = GetTime();// Get the current time 
	if(currentTime - lastUpdateTime >= interval) { // Check if the interval has passed
		lastUpdateTime = currentTime; // Update the last update time
		return true; // Return true if the interval has passed
	}
	return false; // Return false if the interval has not passed
}

int main(){
	Color Blue = { 0, 0, 0, 0 };
	InitWindow(500, 620, "raylib Tetris"); // To create screen
	SetTargetFPS(60); // Set the frame rate per second
	Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0); // Load the font
	Game game = Game(); // Create a game object

	while (WindowShouldClose() == false) {
		BeginDrawing();
		ClearBackground(Blue);

		DrawRectangleRounded({ 20, 57, 450, 80 }, (float)0.2, 6, RED);
		DrawTextEx(font, "K0BY... (^_^)", { 60, 70}, 60, 9, WHITE);

		
		DrawTextEx(font, "Welcome.....", { 60, 180 }, 38, 4, WHITE);
		DrawTextEx(font, " Koby..", { 150, 260 }, 40, 4, YELLOW);
		DrawTextEx(font, "      wants to build the Block \n   and try to gain maximum point.\n Please help him rules are simple", { 15, 300 }, 25, 3, WHITE);
		DrawTextEx(font, "Press any key to start...", { 15, 450 }, 35, 3, WHITE);
		DrawTextEx(font, "Developer Aditya", { 220, 580 }, 30, 3, RED);
		int keyPressed = GetKeyPressed();
		if (keyPressed) break;

		EndDrawing();
	}

	
	while(WindowShouldClose() == false){ // Using loop to keep the window open
		UpdateMusicStream(game.music); // Update the audio stream
		game.HandleInput(); // Call the input function of the game object
		if(EvenTriggered(.3)){
			game.MoveBlockDown(); // Move the block down
		}
		BeginDrawing();

		ClearBackground(Blue);// input background color

		DrawTextEx(font, "POINT", {355, 15}, 38, 2, WHITE); // Draw the text
		/*
		SCORE = To show text
		355   = text position from X axis
		15    = text position from Y axis
		38    = text size
		2     = text spacing
		WHITE = text color
		*/
		DrawTextEx(font, "UP NEXT", {360, 175}, 20, 2, yellow);

		if(game.gameOver)
		DrawTextEx(font, " GAME \n OVER", { 330, 450 }, 45, 2, RED);

		DrawRectangleRounded({ 320, 55, 170, 60 }, (float)0.2, 6, WHITE);
		/*
		320   = X axis position
		55	  = Y axis position
		170   = Width(prosth) of the rectangle
		60    = Height(doirgho) of the rectangle
		0.3   = Roundness of the rectangle
		6     = How many parts to divide the rectangle(to adjust value)
		WHITE = color of the rectangle
		*/

		char scoreText[10]; // Create a character array to hold the score text
        sprintf_s(scoreText, sizeof(scoreText), "%d", game.score); // Convert the score to a string safely
		Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2); // Measure the text size

		DrawTextEx(font, scoreText, { 360 + (0 - textSize.x) / 2, 70 }, 30, 2, RED);
		DrawRectangleRounded({ 320, 215, 170, 180 }, (float)0.2, 6, darkGrey);
		DrawTextEx(font, "Developer Aditya", { 320, 580 }, 15, 3, WHITE);
		game.Draw(); // Call the draw function of the game object
		EndDrawing();
	}
	CloseWindow(); // close the window

}
