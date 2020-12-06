#include "gl2d.h"

namespace Draw {
  void square(Game::Rect2f rect, Game::Color3f col){
    glBegin(GL_POLYGON);
      glColor3f(col.getr(),col.getg(),col.getb()); glVertex2f(rect.x,         rect.y);
      glColor3f(col.getr(),col.getg(),col.getb()); glVertex2f(rect.x+rect.w,  rect.y);
      glColor3f(col.getr(),col.getg(),col.getb()); glVertex2f(rect.x+rect.w,  rect.y+rect.h);
      glColor3f(col.getr(),col.getg(),col.getb()); glVertex2f(rect.x,         rect.y+rect.h);
    glEnd();
  }
}