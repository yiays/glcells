#include "gl2d.h"

namespace Draw {
  // Square
  void square(GameModel::Rect2f rect, Nullable<GameModel::Color3f> col, float opacity){
    if(col == nullptr) return;
    glBegin(GL_POLYGON);
      glColor4f(col.Value->r / 255,col.Value->g / 255,col.Value->b / 255, opacity);
      glVertex2f(rect.x,         rect.y);
      glVertex2f(rect.x+rect.w,  rect.y);
      glVertex2f(rect.x+rect.w,  rect.y+rect.h);
      glVertex2f(rect.x,         rect.y+rect.h);
    glEnd();
  }
  void square(GameModel::Rect2f rect, Nullable<GameModel::Color3f> col, GameModel::Color3f bcol, float opacity){
    square(rect, col);
    glBegin(GL_LINE_LOOP);
      glColor4f(bcol.r / 255, bcol.g / 255, bcol.b / 255, opacity);
      glVertex2f(rect.x,         rect.y);
      glVertex2f(rect.x+rect.w,  rect.y);
      glVertex2f(rect.x+rect.w,  rect.y+rect.h);
      glVertex2f(rect.x,       rect.y+rect.h);
    glEnd();
  }

  // Text
  void setupFont(FTPixmapFont font){
    font.CharMap(FT_ENCODING_UNICODE);
  }

  void text(char* string, GameModel::Point2d pos){
    if(defaultfont.Error()) return;

    defaultfont.FaceSize(18);
    defaultfont.Render(string, -1, FTPoint(pos.x, glutGet(GLUT_WINDOW_HEIGHT) - 18 - pos.y));
  }
}