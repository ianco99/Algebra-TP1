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

void CheckSegmentCollisions(Segment segments[], int totalSegments, vector<Vector2>& collisionPoints);
bool LineLineCollision(Segment segmentA, Segment segmentB);
Vector2 GetCollisionPoints(Segment segmentA, Segment segmentB);
void CreateSides(vector<Vector2> collisionPoints);
void Create4SidedFigure(vector<Segment> sidesCreated);

int main()
{

	vector<Vector2> playerPoints = vector<Vector2>();
	Segment playerSegments[4] = {};

	vector<Vector2> collisionPoints;

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

					segment.distance = Vector2Subtract(segment.p2, segment.p1);
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
			checkCollision = true;

			CheckSegmentCollisions(playerSegments, currentSegment, collisionPoints);
			CreateSides(collisionPoints);
		}
	}

	return 0;
}


void CheckSegmentCollisions(Segment segments[], int totalSegments, vector<Vector2>& collisionPoints)
{
	Segment currSegment;
	Segment nextSegment;

	for (int i = 0; i < totalSegments; i++)
	{
		currSegment = segments[i];

		for (int j = i + 1; j < totalSegments; j++)
		{
			nextSegment = segments[j];

			if (LineLineCollision(currSegment, nextSegment))
			{
				Vector2 point = GetCollisionPoints(currSegment, nextSegment);

				collisionPoints.push_back(point);
			}
		}
	}

	for (int i = 0; i < collisionPoints.size(); i++)
	{
		cout << "POINT NUMBER " << i << ": " << "X: " << collisionPoints[i].x << " , Y: " << collisionPoints[i].y << endl;
	}
}

void CreateSides(vector<Vector2> collisionPoints)
{
	vector<Segment> sidesCreated;

	for (int i = 0; i < collisionPoints.size(); i++)
	{
		for (int j = i + 1; j < collisionPoints.size(); j++)
		{
			bool repeatedSide = false;

			Vector2 currentPoint = collisionPoints[i];
			Vector2 nextPoint = collisionPoints[j];
			Segment side{ currentPoint, nextPoint };

			//for (int k = 0; k < sidesCreated.size(); k++)
			//{
			//	Vector2 createdPointA = sidesCreated[k].p1;
			//	Vector2 createdPointB = sidesCreated[k].p2;
			//
			//	
			//	if (Vector2Equals(side.p1, createdPointA) || Vector2Equals(side.p1, createdPointB))
			//	{
			//		if (Vector2Equals(side.p2, createdPointA) || Vector2Equals(side.p2, createdPointB))
			//		{
			//			repeatedSide = true;
			//		}
			//		
			//	}
			//}

			if (repeatedSide == false)
			{
				sidesCreated.push_back(side);
			}
		}
	}

	for (int i = 0; i < sidesCreated.size(); i++)
	{
		Segment side = sidesCreated[i];

		//cout << "SIDE " << i+1 << " :" << endl;
		//cout << "START : " <<  side.p1.x << " , " << side.p1.y << endl;
		//cout << "END : " <<  side.p2.x << " , " << side.p2.y << endl;
		//cout << endl << endl;
	}

	if (sidesCreated.size() >= 4)
		Create4SidedFigure(sidesCreated);
}

void Create4SidedFigure(vector<Segment> sidesCreated)
{
	Segment figure[4] = {};

	bool foundConnectedSide = false;
	bool foundFigure = true;
	int currentIndex = 0;
	int currentSegmentIndex = 0;
	Segment currentSegment;
	currentSegment = sidesCreated[0];

	while (currentIndex < 4)
	{
		for (int j = 0; j < sidesCreated.size(); j++)
		{
			if (((sidesCreated[j].p1.x == currentSegment.p2.x && sidesCreated[j].p1.y == currentSegment.p2.y)
				|| (sidesCreated[j].p2.x == currentSegment.p1.x && sidesCreated[j].p2.y == currentSegment.p1.y)
				|| (sidesCreated[j].p1.x == currentSegment.p1.x && sidesCreated[j].p1.y == currentSegment.p1.y)
				|| (sidesCreated[j].p2.x == currentSegment.p2.x && sidesCreated[j].p2.y == currentSegment.p2.y))
				&& !foundConnectedSide && j != currentSegmentIndex)
			{
				figure[currentIndex] = sidesCreated[j];
				currentSegment = sidesCreated[j];
				currentSegmentIndex = j;
				currentIndex++;
				foundConnectedSide = true;
			}
		}

		if (!foundConnectedSide)
		{
			cout << "FATAL ERROR";
			foundFigure = false;
			break;
		}

		foundConnectedSide = false;
	}


	if (foundFigure)
	{
		cout << "FIGURE IS:" << endl;

		for (int i = 0; i < 4; i++)
		{
			Segment side = figure[i];

			cout << "SIDE " << i + 1 << " :" << endl;
			cout << "START : " << side.p1.x << " , " << side.p1.y << endl;
			cout << "END : " << side.p2.x << " , " << side.p2.y << endl;
			cout << endl << endl;
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