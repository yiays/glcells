#ifndef GL2D_H
#define GL2D_H

#include <stdlib.h>
#include <GL/glut.h>
#include <FTGL/ftgl.h>

#include "lib/nullable.hpp"

#include "gamemodel.h"

using namespace FTGL;

namespace Draw {
  FTPixmapFont defaultfont = FTGLPixmapFont("fonts/liberation-sans.regular.ttf");

  void setupFont(FTPixmapFont font);

  void square(GameModel::Rect2f rect, Nullable<GameModel::Color3f> col, float opacity = 1.0);
  void square(GameModel::Rect2f rect, Nullable<GameModel::Color3f> col, GameModel::Color3f bordercol, float opacity = 1.0);
  void text(char* string, GameModel::Point2d);
};

#endif