#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

#include "gamemodel.cpp"
#include "gl2d.cpp"
#include "game.cpp"

bool blinker = false;

int secondtick, gametick, frames = 0;

void onDisplay(){
	glClear(GL_COLOR_BUFFER_BIT);

	Game::oGame.Draw();

	Draw::arrow(Game::MousePos.toAbsolute(), Game::MousePos.toAbsolute()+GameModel::Point2f{20,20}, GameModel::Color {(int)blinker*255,(int)blinker*255,255});

	GameModel::Vector mousedir = GameModel::lineToVector(Game::MousePos.toAbsolute(), Game::MousePos.toAbsolute()+GameModel::Point2f{20,20});

	char fpsstring[100];
	snprintf(fpsstring, sizeof fpsstring, "FPS: %f\nLengthdir: %f,%f", Game::FPS, mousedir.vel, mousedir.dir);
	Draw::text(fpsstring, GameModel::Color {200, 200, 200}, GameModel::Point2d {0, 0}, 14);

	glutSwapBuffers();
}

void updateView(){
	// Set the aspect ratio of the clipping area to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset the projection matrix

	int width = glutGet(GLUT_WINDOW_WIDTH) * GameModel::View.w;
	int height = glutGet(GLUT_WINDOW_HEIGHT) * GameModel::View.h;
	gluOrtho2D(GameModel::View.x-width/2, GameModel::View.x+width/2, GameModel::View.y+height/2, GameModel::View.y-height/2);
	
	//std::cout << GameModel::View.x-width/2 << ", " << GameModel::View.x+width/2 << ", " << GameModel::View.y+height/2 << ", " << GameModel::View.y-height/2 << '\n';
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
		GameModel::View.x -= (x - Game::MousePos.x) * GameModel::View.w;
		GameModel::View.y -= (y - Game::MousePos.y) * GameModel::View.h;
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
		if(button == 4){
			GameModel::View.w += 0.05;
			GameModel::View.h += 0.05;
			updateView();
		} else if (button == 3) {
			GameModel::View.w -= 0.05;
			GameModel::View.h -= 0.05;
			updateView();
		}
	}

	//std::cout << button << ", " << state << '\n';
}

void onIdle() {
	// Tick, once per second
	if(glutGet(GLUT_ELAPSED_TIME) - secondtick >= 1000){
		secondtick += 1000;
		int catchup = 0;
		while(glutGet(GLUT_ELAPSED_TIME) - secondtick >= 1000){
			// Catch up for dropped frames
			secondtick += 1000;
			catchup++;
			
			// Run only essential functions
		}
		if(catchup > 0){
			std::cout << "Fell behind by " << catchup << " second(s)! Catching up...\n";
		}

		// Calculate fps
		Game::FPS = frames;
		frames = 0;
	}

	// Tick, 10 times a second
	if(glutGet(GLUT_ELAPSED_TIME) - gametick >= Game::GameSpeed){
		gametick += Game::GameSpeed;
		int catchup = 0;
		while(glutGet(GLUT_ELAPSED_TIME) - gametick >= Game::GameSpeed){
			// Catch up for dropped frames
			gametick += Game::GameSpeed;
			catchup++;
			
			// Run only essential functions
			Game::oGame.Tick();
		}
		if(catchup > 0){
			std::cout << "Fell behind by " << catchup << " tick(s)! Catching up...\n";
		}
		
		// In-game tick
		Game::oGame.Tick();
		
		// Blink mouse cursor
		blinker = !blinker;
	}

	frames++;

	glutPostRedisplay();
}

int main(int argc, char** argv){
	Game::oGame.Log("GLCells indev v0.0.1\n");

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

	// Start game view centred in simulation
	GameModel::View.x = 320;
	GameModel::View.y = 384;

	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Events
	glutDisplayFunc(onDisplay);
	glutReshapeFunc(onWindowResize);
	glutMouseFunc(onClick);
	glutPassiveMotionFunc(onMouseMove);
	glutMotionFunc(onMouseDrag);
	glutIdleFunc(onIdle);

	// Start tick timers
	secondtick = glutGet(GLUT_ELAPSED_TIME);
	gametick = glutGet(GLUT_ELAPSED_TIME);

	// Generate world
	Game::oGame.New(40, 24);

	// Tell GLUT to start reading and processing events.  This function
	// never returns; the program only exits when the user closes the main
	// window or kills the process.
	glutMainLoop();
	return 0;
}
