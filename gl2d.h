#ifndef GL2D_H
#define GL2D_H

#include <stdlib.h>
#include <GL/glut.h>
#include <FTGL/ftgl.h>
#include <stdlib.h>

#include "gameengine.h"

using namespace FTGL;

namespace Draw {
  FTPixmapFont defaultfont = FTGLPixmapFont("fonts/liberation-sans.regular.ttf");

  void setupFont(FTPixmapFont font);

  void square(Game::Rect2f rect, Game::Color3f col);
  void square(Game::Rect2f rect, Game::Color3f col, Game::Color3f bordercol);
  void text(char* string, Game::Point2d);
};

#endif