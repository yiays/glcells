#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>

#include "gameengine.cpp"
#include "cellular.cpp"

void display(){
	glClear(GL_COLOR_BUFFER_BIT);

	Automata::GasGrid.draw();

	/*
	glBegin(GL_POLYGON);
		glColor3f(1, 0, 0); glVertex2f(-0.5, -0.5);
		glColor3f(0, 1, 0); glVertex2f(0.5, -0.5);
		glColor3f(0, 0, 1); glVertex2f(0.5, 0.5);
		glColor3f(1, 0, 1); glVertex2f(-0.5, 0.5);
	glEnd();
	*/

	glFlush();
}

int main(int argc, char** argv){
	// Use a single buffered window in RGB mode (as opposed to a double-buffered
	// window or color-index mode).
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Position window at (80,80)-(480,380) and give it a title.
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("GLCells");

	// Change view scale to native resolution
	glOrtho(0, 1280, 720, 0, 0, 200);

	// Tell GLUT that whenever the main window needs to be repainted that it
	// should call the function display().
	glutDisplayFunc(display);

	Automata::init(40, 24);

	// Tell GLUT to start reading and processing events.  This function
	// never returns; the program only exits when the user closes the main
	// window or kills the process.
	glutMainLoop();
}
