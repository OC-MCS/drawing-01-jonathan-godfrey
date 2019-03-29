#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;

struct shapeData {
	Vector2f pos;
	ShapeEnum shape;
	int color;
};

// DrawingShape should be an abstract base class 
// for Circle and Square
class DrawingShape 
{
private:
	Vector2f pos;
	ShapeEnum shape;
	Color color;

public:
	DrawingShape(Vector2f p, ShapeEnum s, Color c)
	{
		shape = s;
		color = c;
		pos = p;
	}
	Vector2f getPos()
	{
		return pos;
	}
	ShapeEnum getShape()
	{
		return shape;
	}
	Color getColor()
	{
		return color;
	}

	virtual void draw(RenderWindow& w) = 0;
};

class Circle : public DrawingShape
{
private:
	float radius = 20.0;
public:
	CircleShape circle;
	Circle(Vector2f p, ShapeEnum s, Color c) : DrawingShape(p, s, c)
	{
		circle.setPosition(getPos());
		circle.setRadius(radius);
		circle.setOutlineThickness(2);
		circle.setOutlineColor(getColor());
		circle.setFillColor(getColor());
	}

	void draw(RenderWindow& win)
	{
		win.draw(circle);
	}

};

class Square : public DrawingShape
{
private:
	Vector2f size = { 40, 40 };
public:

	RectangleShape square;
	Square(Vector2f p, ShapeEnum s, Color c) : DrawingShape(p, s, c)
	{
		square.setPosition(getPos());
		square.setSize(size);
		square.setOutlineThickness(2);
		square.setOutlineColor(getColor());
		square.setFillColor(getColor());
	}

	void draw(RenderWindow& win)
	{
		win.draw(square);
	}

};