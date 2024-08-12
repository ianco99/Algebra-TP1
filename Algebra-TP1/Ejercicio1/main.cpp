#include <iostream>
#include "raylib.h"
#include <vector>

using namespace std;

int main()
{
	vector<Vector2> playerPoints;

	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Algebra - Ejercicio 1");

	while (!WindowShouldClose())
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			playerPoints.push_back(GetMousePosition());


		BeginDrawing();
		for (int i = 0; i < playerPoints.size(); i++)
		{
			DrawCircle(playerPoints[i].x, playerPoints[i].y, 2.0f, RED);
		}
		EndDrawing();
	}

	return 0;
}