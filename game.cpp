#include "game.h"
#include "cellular.cpp"

namespace Game {
  void cGame::New(int w, int h) {
    this->World.Create(w, h);
    this->World.Generate();
  }
  void cGame::Tick() {
    this->World.Tick();
  }
  void cGame::Draw() {
    this->World.Draw();
  }

  void cWorld::Create(int w, int h) {
    this->OverlayGrid.SetSize(w, h);
    this->WorldGrid.SetSize(w, h);
    //this->BackgroundGrid.SetSize(w, h);
  }
  void cWorld::Generate() {
    this->WorldGrid.Generate();
    //this->BackgroundGrid.Generate();
  }
  void cWorld::Tick() {
    this->WorldGrid.Tick();
  }
  void cWorld::Draw() {
    //this->BackgroundGrid.Draw();
    this->WorldGrid.Draw();
    this->OverlayGrid.Draw();
  }
}