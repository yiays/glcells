#ifndef GL2D_H
#define GL2D_H

#include <GL/glut.h>

#include "gameengine.h"

namespace Draw {
  void square(Game::Rect2f rect, Game::Color3f col);
  void square(Game::Rect2f rect, Game::Color3f col, Game::Color3f bordercol);
};

#endif