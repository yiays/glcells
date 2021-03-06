#ifndef GAME_H
#define GAME_H

#include "gamemodel.h"
#include "cellular.h"

namespace Game {
	float FPS = 0.0;
  int GameSpeed = 600;

	GameModel::Point2f MousePos = {0, 0};
	GameModel::ButtonState MouseState = {0, 0};

  class cWorld: public GameModel::GameObject{
    public:
      Cellular::CellGrid<Element::cBase> OverlayGrid;
      Cellular::WorldGrid WorldGrid;
      Cellular::BackgroundGrid BackgroundGrid;

      void Create(int w, int h);
      void Generate();
      void Tick();
      void Draw();
  };

	class cGame: public GameModel::GameObject{
    public:
      cWorld World;
      void New(int w, int h);
      void Load();
      void Save();
      void Tick();
      void Draw();
      void Log(const char* string);
  };

  cGame oGame;
}

#endif