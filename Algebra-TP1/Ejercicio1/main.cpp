#include <iostream>
#include "raylib.h"
#include <vector>

using namespace std;

struct Segment
{
	Vector2 p1;
	Vector2 p2;
};

int main()
{
	
	vector<Vector2> playerPoints = vector<Vector2>();
	Segment playerSegments[4] = {};

	const int screenWidth = 800;
	const int screenHeight = 450;
	bool drawSegment = false;

	int currentSegment = 0;

	InitWindow(screenWidth, screenHeight, "Algebra - Ejercicio 1");

	//userloop
	while (!WindowShouldClose())
	{
		if (playerPoints.size() < 8)
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				playerPoints.push_back(GetMousePosition());

				if (playerPoints.size() % 2 == 0 && playerPoints.size() > 0)
				{
					cout << playerPoints.size();
					Segment segment;
					int last = playerPoints.size() - 1;

					segment.p1 = playerPoints[last - 1];
					segment.p2 = playerPoints[last];
					playerSegments[currentSegment] = segment;
					currentSegment++;
				}

			}
		}


		BeginDrawing();

		for (int i = 0; i < currentSegment; i++)
		{
			DrawLine(playerSegments[i].p1.x, playerSegments[i].p1.y, playerSegments[i].p2.x, playerSegments[i].p2.y, BLUE);
		}

		for (int i = 0; i < playerPoints.size(); i++)
		{
			DrawCircle(playerPoints[i].x, playerPoints[i].y, 2.0f, RED);
		}
		EndDrawing();
	}

	return 0;
}