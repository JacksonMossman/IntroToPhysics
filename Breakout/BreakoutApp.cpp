#include "BreakoutApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm\ext.hpp"
#include <Gizmos.h>

BreakoutApp::BreakoutApp() {

}

BreakoutApp::~BreakoutApp() {

}

bool BreakoutApp::startup() {
	//Initialize the Gizmos singleton class
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void BreakoutApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void BreakoutApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// define the colors
	static const glm::vec4 colors[] = {
		glm::vec4(1,0,0,1), glm::vec4(0,1,0,1),
		glm::vec4(0,0,1,1), glm::vec4(0.8f,0,0.5f,1),
		glm::vec4(0,1,1,1)
	};

	// define the dimensions
	static const int rows = 5;
	static const int columns = 10;
	static const int hSpace = 1;
	static const int vSpace = 1;

	static const glm::vec2 scrExtents(100, 50);
	static const glm::vec2 boxExtents(7, 3);
	static const glm::vec2 startPos(
		-(columns >> 1)*((boxExtents.x * 2) + vSpace) + boxExtents.x + (vSpace/2.0f),
		scrExtents.y - ((boxExtents.y * 2) + hSpace));

	// add the grid of blocks to Gizmos
	glm::vec2 pos;
	for (int y = 0; y < rows; y++) {
		pos = glm::vec2(startPos.x, startPos.y - (y * ((boxExtents.y * 2) + hSpace)));
		for (int x = 0; x < columns; x++) {
			aie::Gizmos::add2DAABBFilled(pos, boxExtents, colors[y]);
			pos.x += (boxExtents.x * 2) + vSpace;
		}
	}

	// add the ball to Gizmos
	aie::Gizmos::add2DCircle(glm::vec2(0, -35), 3, 12, glm::vec4(1, 1, 0, 1));
	// add the paddle to Gizmos
	aie::Gizmos::add2DAABBFilled(
		glm::vec2(0, -40), //center
		glm::vec2(12, 2), //extents
		glm::vec4(1, 0, 1, 1)); //color

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void BreakoutApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16.0f / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100.0f, 100.0f,
		-100.0f / aspectRatio, 100.0f / aspectRatio, -1.0f, 1.0f));
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}