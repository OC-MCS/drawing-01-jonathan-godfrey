//================================================
// Jonathan Godfrey 
//================================================
#include <iostream>
#include <fstream>
using namespace std;
#include <SFML\Graphics.hpp>
#include "SettingsMgr.h"
#include "ShapeMgr.h"
#include "SettingsUI.h"
#include "DrawingUI.h"
using namespace sf;

struct prevSettings {
	Color color;
	ShapeEnum shape;
};
struct saveShapes {
	ShapeEnum shape;
	Color color;
	Vector2f pos;
};

void readFile(SettingsMgr &stgsMgr, ShapeMgr &shpMgr);
void writeFile(SettingsMgr&, ShapeMgr&);

int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Drawing");
	window.setFramerateLimit(60);

	SettingsMgr settingsMgr(Color::Red, ShapeEnum::CIRCLE);
	SettingsUI  settingsUI(&settingsMgr); 
	ShapeMgr    shapeMgr;
	DrawingUI   drawingUI(Vector2f(597, 594));
	
	// Reads file to show previous drawing
	readFile(settingsMgr, shapeMgr);

	while (window.isOpen()) 
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				// Saves drawing and settings to file
				writeFile(settingsMgr, shapeMgr);
			}
			else if (event.type == Event::MouseButtonReleased)
			{
				// maybe they just clicked on one of the settings "buttons"
				// check for this and handle it.
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				settingsUI.handleMouseUp(mousePos);
			}
			else if (event.type == Event::MouseMoved && Mouse::isButtonPressed(Mouse::Button::Left))
			{
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				// check to see if mouse is in the drawing area
				if (drawingUI.isMouseInCanvas(mousePos))
				{
					// add a shape to the list based on current settings
					shapeMgr.addShape(mousePos, settingsMgr.getCurShape(), settingsMgr.getCurColor());
				}
			}
		}

		// The remainder of the body of the loop draws one frame of the animation
		window.clear();

		// this should draw the left hand side of the window (all of the settings info)
		settingsUI.draw(window);
		
		// this should draw the rectangle that encloses the drawing area, then draw the
		// shapes. This is passed the shapeMgr so that the drawingUI can get the shapes
		// in order to draw them. This redraws *all* of the shapes every frame.
		drawingUI.draw(window, &shapeMgr);

		window.display();
	} // end body of animation loop

	return 0;
}

// reads settings and shapes stored in shapes.bin if that file exists
// if the file doesn't exist it is created
void readFile(SettingsMgr& settingsMgr, ShapeMgr& shapeMgr) {

	prevSettings settings;
	saveShapes shapes;
	ifstream file;

	file.open("shapes.bin", ios::binary | ios::in);

	// Reads last used settings from previous time
	file.read(reinterpret_cast<char*>(&settings), sizeof(prevSettings));

	// Sets color and shape to previous settings
	settingsMgr.setCurColor(settings.color);
	settingsMgr.setCurShape(settings.shape);

	// Reads file to vector to be drawn on canvas
	while (file.read(reinterpret_cast<char*>(&shapes), sizeof(saveShapes))) 
	{
		if (shapes.shape == CIRCLE) 
		{
			Circle* circlePtr = new Circle(shapes.pos, shapes.shape, shapes.color);
			shapeMgr.getVectorPtr()->push_back(circlePtr);
		}
		else 
		{
			Square* squarePtr = new Square(shapes.pos, shapes.shape, shapes.color);
			shapeMgr.getVectorPtr()->push_back(squarePtr);
		}
	}

	file.close();
}

// Writes all the shapes and settings to file
void writeFile(SettingsMgr& settingsMgr, ShapeMgr& shapeMgr) 
{
	// Stores current settings in struct
	prevSettings settings = { settingsMgr.getCurColor(), settingsMgr.getCurShape() };
	ofstream file;
	file.open("shapes.bin", ios::binary | ios::out);

	// Writes settings struct to file
	file.write(reinterpret_cast<char*>(&settings), sizeof(prevSettings));
	saveShapes shapes;

	// Writes shapes vector to file
	for (int i = 0; i < shapeMgr.getVectorPtr()->size(); i++) 
	{
		shapes = { shapeMgr.getVectorPtr()->operator[](i)->getShape(), shapeMgr.getVectorPtr()->operator[](i)->getColor(), shapeMgr.getVectorPtr()->operator[](i)->getPos() };
		file.write(reinterpret_cast<char*>(&shapes), sizeof(saveShapes));
	}

	file.close();
}
