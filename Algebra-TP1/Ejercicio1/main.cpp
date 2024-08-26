#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include <vector>

using namespace std;

struct Segment
{
	Vector2 p1;
	Vector2 p2;
	Vector2 distance;
};

void CheckSegmentCollisions(Segment segments[], int totalSegments);
bool LineLineCollision(Segment segmentA, Segment segmentB);
Vector2 GetCollisionPoints(Segment segmentA, Segment segmentB);

int main()
{
	
	vector<Vector2> playerPoints = vector<Vector2>();
	Segment playerSegments[4] = {};

	const int screenWidth = 800;
	const int screenHeight = 450;
	bool drawSegment = false;
	bool checkCollision = false;

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
					cout << playerPoints.size() << endl;
					Segment segment;
					int last = playerPoints.size() - 1;

					segment.p1 = playerPoints[last - 1];
					segment.p2 = playerPoints[last];

					cout << segment.p1.x << ", " << segment.p1.y << endl;
					cout << segment.p2.x << ", " << segment.p2.y << endl;

					segment.distance = Vector2Subtract(segment.p2,segment.p1);
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
		
		if (currentSegment > 3 && !checkCollision)
		{
			CheckSegmentCollisions(playerSegments, currentSegment);
			checkCollision = true;
		}
	}

	return 0;
}


void CheckSegmentCollisions(Segment segments[], int totalSegments)
{
	Segment currSegment;
	Segment nextSegment;

	for (int i = 0; i < totalSegments; i++)
	{
		currSegment = segments[i];

		for (int j = i+1; j < totalSegments; j++)
		{
			nextSegment = segments[j];

			if (LineLineCollision(currSegment, nextSegment))
			{
				Vector2 point = GetCollisionPoints(currSegment, nextSegment);
				cout << "COLLISION LINE" << endl;
				cout << "X: " << point.x << " , Y: " << point.y << endl;
			}
			else
			{
			}
		}
	}
}

//https://www.jeffreythompson.org/collision-detection/line-line.php
bool LineLineCollision(Segment segmentA, Segment segmentB)
{
	float x1 = segmentA.p1.x;
	float x2 = segmentA.p2.x;
	float x3 = segmentB.p1.x;
	float x4 = segmentB.p2.x;
	float y1 = segmentA.p1.y;
	float y2 = segmentA.p2.y;
	float y3 = segmentB.p1.y;
	float y4 = segmentB.p2.y;

	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	return uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1;
}

Vector2 GetCollisionPoints(Segment segmentA, Segment segmentB)
{
	float x1 = segmentA.p1.x;
	float x2 = segmentA.p2.x;
	float x3 = segmentB.p1.x;
	float x4 = segmentB.p2.x;
	float y1 = segmentA.p1.y;
	float y2 = segmentA.p2.y;
	float y3 = segmentB.p1.y;
	float y4 = segmentB.p2.y;

	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		float intersectionX = x1 + (uA * (x2 - x1));
		float intersectionY = y1 + (uA * (y2 - y1));

		return Vector2{ intersectionX, intersectionY };
	}

	return { 0,0 };
}