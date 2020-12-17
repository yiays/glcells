#ifndef CELLULAR_H
#define CELLULAR_H

#include <vector>
#include <string>

#include "gl2d.h"
#include "elements.h"

#define abs0 -273.1f;

namespace Cellular{
	const GameModel::Color3f bordercolor = { 50.0, 50.0, 50.0 };
	enum CellState { SOLID, LIQUID, GAS, VACUUM };
	enum PushMethods { pMERGE=0, pCASCADE=1, pOVERMERGE=2 };

  class Cell {
		public:
			struct Element::cElement* Element = &Element::Vacuum;
			float Mass = 0;
			float Temperature = abs0;
			enum CellState State = VACUUM;
			bool beingpushed = false;

      void Create();
      void Update();
  };

  class CellGrid: public GameModel::Grid2d{
    public:
			std::vector<Cell*> Cells;

      void SetSize(int width, int height);

			Cell* GetCell(int x, int y);
			void SetCell(Cell* oldcell, Cell* newcell);
			void PushCell(Cell* cell, int dir);
			void SwapCell(Cell* oldcell, Cell* newcell);

      void Draw();
  };

  class WorldGrid: public CellGrid {
		public:
			using CellGrid::Cells;
			using CellGrid::w;
			using CellGrid::h;

			void Generate();
			void Tick();
			void Draw();
	};
	class BackgroundGrid: public CellGrid {
    public:
			using CellGrid::Cells;
  };
};

#endif