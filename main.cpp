#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

#include "gameengine.cpp"
#include "cellular.cpp"

Game::Rect2d lastview = { 0, 0, 1280, 720 };
float testslider = 0.0;

void onDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);

	Automata::GasGrid.draw();

	Draw::square(Game::Rect2f { (float)Game::MousePos.x, (float)Game::MousePos.y, 20.0, 20.0 }, Game::Color3f {testslider,testslider,testslider}, Game::Color3f {0,0,255});

	glutSwapBuffers();
}
void onDisplay(int x, int y){
	onDisplay();
}

void onWindowResize(GLsizei width, GLsizei height){
	// Compute aspect ratio of the new window
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix

	gluOrtho2D(0.0, width, height, 0.0);
}

void onClick(int button, int state, int x, int y) {
	return;
}

void onMouseMove(int x, int y) {
	Game::MousePos.x = x;
	Game::MousePos.y = y;
}

void onIdle() {
	if(testslider < 255){
		testslider++;
	}else{
		testslider = 0;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv){
	// Use a single buffered window in RGB mode (as opposed to a double-buffered
	// window or color-index mode).
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Default window size, positioning, and title
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(lastview.w, lastview.h);
	glEnable(GL_VIEWPORT);
	glViewport(lastview.x, lastview.y, lastview.w, lastview.h);
	glutCreateWindow("GLCells");

	// Other GL settings
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	

	// Events
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onWindowResize);
	glutMouseFunc(onClick);
	glutPassiveMotionFunc(onMouseMove);
	glutIdleFunc(onIdle);

	Automata::init(40, 24);

	// Tell GLUT to start reading and processing events.  This function
	// never returns; the program only exits when the user closes the main
	// window or kills the process.
	glutMainLoop();
	return 0;
}
