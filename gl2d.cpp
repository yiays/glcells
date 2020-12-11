#include "gl2d.h"

namespace Draw {
  void square(Game::Rect2f rect, Game::Color3f col){
    glBegin(GL_POLYGON);
      glColor3f(col.getr(),col.getg(),col.getb());
      glVertex2f(rect.x,         rect.y);
      glVertex2f(rect.x+rect.w,  rect.y);
      glVertex2f(rect.x+rect.w,  rect.y+rect.h);
      glVertex2f(rect.x,         rect.y+rect.h);
    glEnd();
  }
  void square(Game::Rect2f rect, Game::Color3f col, Game::Color3f bcol){
    square(rect, col);
    glBegin(GL_LINE_LOOP);
      glColor3f(bcol.getr(),bcol.getg(),bcol.getg());
      glVertex2f(rect.x,         rect.y);
      glVertex2f(rect.x+rect.w,  rect.y);
      glVertex2f(rect.x+rect.w,  rect.y+rect.h);
      glVertex2f(rect.x,         rect.y+rect.h);
    glEnd();
  }
}