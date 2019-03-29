#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
#include "SettingsMgr.h"

class SettingsUI
{
private:
	SettingsMgr *settingsPtr;

	CircleShape redBtn;		
	CircleShape greenBtn;
	CircleShape blueBtn;
	CircleShape circleBtn;
	RectangleShape squareBtn;

	void die(string msg)
	{
		cout << msg << endl;
		exit(-1);
	}

public:
	SettingsUI(SettingsMgr *mgr)
	{
		settingsPtr = mgr;

		int radius = 15;

		// Creates initial buttons and sets default settings
		Vector2f pos(75, 75);
		redBtn.setPosition(pos);
		redBtn.setRadius(radius);
		redBtn.setOutlineThickness(2);
		redBtn.setOutlineColor(Color::Red);
		redBtn.setFillColor(Color::Red);	

		pos = { 75, 135 };
		blueBtn.setPosition(pos);
		blueBtn.setRadius(radius);
		blueBtn.setOutlineThickness(2);
		blueBtn.setOutlineColor(Color::Blue);
		blueBtn.setFillColor(Color::Transparent);	// for just an outlined button

		pos = { 75, 195 };
		greenBtn.setPosition(pos);
		greenBtn.setRadius(radius);
		greenBtn.setOutlineThickness(2);
		greenBtn.setOutlineColor(Color::Green);
		greenBtn.setFillColor(Color::Transparent);

		pos = { 75, 345 };
		circleBtn.setPosition(pos);
		circleBtn.setRadius(radius);
		circleBtn.setOutlineThickness(2);
		circleBtn.setOutlineColor(Color::White);
		circleBtn.setFillColor(Color::White);

		Vector2f size(30, 30);
		pos = { 75, 405 };
		squareBtn.setPosition(pos);
		squareBtn.setSize(size);
		squareBtn.setOutlineThickness(2);
		squareBtn.setOutlineColor(Color::White);
		squareBtn.setFillColor(Color::Transparent);
	}

	// If user has clicked on a button, set color or shape and 
	// change color of buttons to indicate selection
	void handleMouseUp(Vector2f mouse)
	{
		if (redBtn.getGlobalBounds().contains(mouse)) // mouse is a vector2f
		{
			redBtn.setFillColor(Color::Red);
			greenBtn.setFillColor(Color::Transparent);
			blueBtn.setFillColor(Color::Transparent);
			settingsPtr->setCurColor(Color::Red);
		}
		else if (greenBtn.getGlobalBounds().contains(mouse))
		{
			redBtn.setFillColor(Color::Transparent);
			greenBtn.setFillColor(Color::Green);
			blueBtn.setFillColor(Color::Transparent);
			settingsPtr->setCurColor(Color::Green);
		}
		else if (blueBtn.getGlobalBounds().contains(mouse))
		{
			redBtn.setFillColor(Color::Transparent);
			greenBtn.setFillColor(Color::Transparent);
			blueBtn.setFillColor(Color::Blue);
			settingsPtr->setCurColor(Color::Blue);
		}
		else if (circleBtn.getGlobalBounds().contains(mouse))
		{
			squareBtn.setFillColor(Color::Transparent);
			circleBtn.setFillColor(Color::White);
			settingsPtr->setCurShape(CIRCLE);
		}
		else if (squareBtn.getGlobalBounds().contains(mouse))
		{
			squareBtn.setFillColor(Color::White);
			circleBtn.setFillColor(Color::Transparent);
			settingsPtr->setCurShape(SQUARE);
		}
	}

	void draw(RenderWindow& win)
	{
		// load font
		Font font;
		if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
			die("couldn't load font");

		// Draw descriptions
		Text selectedColor("Selected Color", font, 18);
		selectedColor.setPosition(30, 25);
		win.draw(selectedColor);

		Text selectedShape("Selected Shape", font, 18);
		selectedShape.setPosition(30, 300);
		win.draw(selectedShape);

		// Draw buttons
		win.draw(redBtn);
		win.draw(blueBtn);		
		win.draw(greenBtn);

		win.draw(circleBtn);
		win.draw(squareBtn);
	}

};
