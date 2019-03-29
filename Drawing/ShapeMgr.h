#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Shape.h"

using namespace std;
using namespace sf;

class ShapeMgr
{
private:
	vector<DrawingShape*> shapes;
public:
	ShapeMgr()
	{
		
	}

	// Adds shapes to vector
	void addShape(Vector2f pos, ShapeEnum shape, Color color)
	{
		if (shape == CIRCLE)
		{
			Circle *circPtr = new Circle(pos, shape, color);
			shapes.push_back(circPtr);
		}
		else
		{
			Square *sqrPtr = new Square(pos, shape, color);
			shapes.push_back(sqrPtr);
		}
	}

	// Returns pointer to vector that holds drawn shapes
	vector<DrawingShape*>* getVectorPtr()
	{
		return &shapes;
	}

};
