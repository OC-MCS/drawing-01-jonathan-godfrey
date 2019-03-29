#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
#include "ShapeMgr.h"

class DrawingUI
{
private:
	RectangleShape drawingArea;

public:
	DrawingUI(Vector2f p)
	{
		RectangleShape rect(p);
		drawingArea = rect;

		drawingArea.setFillColor(Color(0, 0, 0));
		drawingArea.setOutlineThickness(3.f);
		drawingArea.setOutlineColor(sf::Color(250, 250, 250));
		drawingArea.setPosition(200, 3);
	}

	// Draws shapes
	void draw(RenderWindow& win, ShapeMgr *mgr)
	{
		win.draw(drawingArea);
		for (int i = 0; i < mgr->getVectorPtr()->size(); i++)
		{
			mgr->getVectorPtr()->operator[](i)->draw(win);
		}
	}
	
	// Returns true if mouse is on canvas
	bool isMouseInCanvas(Vector2f mousePos)
	{
		bool onCanvas = false;
		if (drawingArea.getGlobalBounds().contains(mousePos))
			onCanvas = true;
		else
			onCanvas = false;

		return onCanvas;
	}
};

