#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

enum ShapeEnum { CIRCLE, SQUARE };

class SettingsMgr
{
private:
	Color color;
	ShapeEnum shape;

public:
	SettingsMgr(Color startingColor, ShapeEnum startingShape )
	{
		color = startingColor;
		shape = startingShape;
	}

	// Returns current color
	Color getCurColor()
	{
		return color;
	}

	// Returns current shape
	ShapeEnum getCurShape()
	{
		return shape;
	}

	// Sets new color
	void setCurColor(Color selectedColor)
	{
		color = selectedColor;
	}
	
	// Sets new shape
	void setCurShape(ShapeEnum selectedShape)
	{
		shape = selectedShape;
	}
};
