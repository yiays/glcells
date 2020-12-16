#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

#include "gameengine.cpp"
#include "cellular.cpp"

float testslider = 0.0;

int t = 0, frames = 0;

void onDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);

	Automata::GasGrid.draw();

	Game::Rect2f square = { (float)Game::MousePos.x, (float)Game::MousePos.y, 20.0, 20.0 };
	Draw::square(square.toAbsolute(), Game::Color3f {testslider,testslider,testslider}, Game::Color3f {0,0,255});

	char fpsstring[10];
	snprintf(fpsstring, sizeof fpsstring, "FPS %f", Game::FPS);
	Draw::text(fpsstring, Game::Point2d {0, 0});

	glutSwapBuffers();
}

void updateView(){
	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix

	int width = glutGet(GLUT_WINDOW_WIDTH) * Game::view.w;
	int height = glutGet(GLUT_WINDOW_HEIGHT) * Game::view.h;
	gluOrtho2D(Game::view.x-width/2, Game::view.x+width/2, Game::view.y+height/2, Game::view.y-height/2);
	
	//std::cout << Game::view.x-width/2 << ", " << Game::view.x+width/2 << ", " << Game::view.y+height/2 << ", " << Game::view.y-height/2 << '\n';
}

void onWindowResize(GLsizei width, GLsizei height){
	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	updateView();
}

void onMouseMove(int x, int y) {
	Game::MousePos.x = x;
	Game::MousePos.y = y;
}
void onMouseDrag(int x, int y){
	if(Game::MouseState.button == GLUT_LEFT){
		Game::view.x -= x - Game::MousePos.x;
		Game::view.y -= y - Game::MousePos.y;
		updateView();
	}
	onMouseMove(x, y);
}

void onClick(int button, int state, int x, int y) {
	Game::MousePos.x = x;
	Game::MousePos.y = y;
	Game::MouseState.button = button;
	Game::MouseState.state = state;	

	if(state == GLUT_DOWN){
		if(button == 3){
			Game::view.w += 0.05;
			Game::view.h += 0.05;
			updateView();
		} else if (button == 4) {
			Game::view.w -= 0.05;
			Game::view.h -= 0.05;
			updateView();
		}
	}

	//std::cout << button << ", " << state << '\n';
}

void onIdle() {
	// Tick, once per second
	if(glutGet(GLUT_ELAPSED_TIME) - t >= 1000){
		// Estimate frame rate
		t = glutGet(GLUT_ELAPSED_TIME);
		Game::FPS = frames;
		frames = 0;
		
		// Blink mouse cursor
		testslider = testslider == 0? 255 : 0;
	}

	frames++;

	glutPostRedisplay();
}

int main(int argc, char** argv){
	// Use a single buffered window in RGB mode (as opposed to a double-buffered
	// window or color-index mode).
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Default window size, positioning, and title
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(1280, 720);
	glEnable(GL_VIEWPORT);
	glViewport(0, 0, 1280, 720);
	glutCreateWindow("GLCells");

	// Other GL settings
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Events
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onWindowResize);
	glutMouseFunc(onClick);
	glutPassiveMotionFunc(onMouseMove);
	glutMotionFunc(onMouseDrag);
	glutIdleFunc(onIdle);

	Automata::init(40, 24);

	// Tell GLUT to start reading and processing events.  This function
	// never returns; the program only exits when the user closes the main
	// window or kills the process.
	glutMainLoop();
	return 0;
}
