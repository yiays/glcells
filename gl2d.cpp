#include "gl2d.h"

namespace Draw {
  // Square
  void square(GameModel::Rect2f rect, GameModel::Color col, float opacity){
    if(col == GameModel::cNone) return;
    glBegin(GL_POLYGON);
      glColor4f((float)col.r / 255,(float)col.g / 255,(float)col.b / 255, opacity);
      glVertex2f(rect.x,         rect.y);
      glVertex2f(rect.x+rect.w,  rect.y);
      glVertex2f(rect.x+rect.w,  rect.y+rect.h);
      glVertex2f(rect.x,         rect.y+rect.h);
    glEnd();
  }
  void square(GameModel::Rect2f rect, GameModel::Color col, GameModel::Color bcol, float opacity){
    square(rect, col);
    if(bcol == GameModel::cNone) return;
    glBegin(GL_LINE_LOOP);
      glColor4f((float)bcol.r / 255,(float)bcol.g / 255,(float)bcol.b / 255, opacity);
      glVertex2f(rect.x,         rect.y);
      glVertex2f(rect.x+rect.w,  rect.y);
      glVertex2f(rect.x+rect.w,  rect.y+rect.h);
      glVertex2f(rect.x,       rect.y+rect.h);
    glEnd();
  }

  // Line
  void line(GameModel::Point2f point1, GameModel::Point2f point2, GameModel::Color col, float opacity){
    glBegin(GL_LINES);
      glColor4f((float)col.r / 255,(float)col.g / 255,(float)col.b / 255, opacity);
      glVertex2f(point1.x, point1.y);
      glVertex2f(point2.x, point2.y);
    glEnd();
  }
  void arrow(GameModel::Point2f point1, GameModel::Point2f point2, GameModel::Color col, float opacity){
    line(point1, point2, col, opacity);
    GameModel::Vector vector = GameModel::lineToVector(point1, point2);
    //vector.vel = std::min(5.0f, vector.vel / 2);
    vector.dir -= 270;
    line(point2, vector.getTarget(point2), col, opacity);
    vector.dir -= 180;
    line(point2, vector.getTarget(point2), col, opacity);
  }

  // Text
  void setupFont(FTPixmapFont font){
    font.CharMap(FT_ENCODING_UNICODE);
  }

  void text(char* string, GameModel::Color col, GameModel::Point2d pos, unsigned int fontsize, float opacity){
    if(defaultfont.Error()) return;

    defaultfont.FaceSize(fontsize);
    glColor4f(col.r / 255, col.g / 255, col.b / 255, opacity);
    defaultfont.Render(string, -1, FTPoint(pos.x, glutGet(GLUT_WINDOW_HEIGHT) - fontsize - pos.y));
  }
}