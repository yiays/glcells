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

  void square(GameModel::Rect2f rect, GameModel::Color col = GameModel::cWhite, float opacity = 1.0);
  void square(GameModel::Rect2f rect, GameModel::Color col, GameModel::Color bordercol, float opacity = 1.0);
  void line(GameModel::Point2f point1, GameModel::Point2f point2, GameModel::Color col = GameModel::cWhite, float opacity = 1.0);
  void arrow(GameModel::Point2f point1, GameModel::Point2f point2, GameModel::Color col = GameModel::cWhite, float opacity = 1.0);
  void text(char* string, GameModel::Color col, GameModel::Point2d pos, unsigned int fontsize = 18, float opacity = 1.0);
};

#endif