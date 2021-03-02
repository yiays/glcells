#ifndef CELLULAR_H
#define CELLULAR_H

#include <vector>
#include <string>

#include "gl2d.h"
#include "elements.h"

#define abs0 -273.1f;

namespace Cellular{
	const GameModel::Color bordercolor = { 50, 50, 50 };
	enum CellState { SOLID, LIQUID, GAS, VACUUM };
	enum PushMethods { pMERGE=0, pCASCADE=1, pOVERMERGE=2 };

	template <class T>
  class Cell {
		public:
			T* Element;
			float Mass = 0;
			float Temperature = abs0;
			enum CellState State = VACUUM;
			bool lock = false;

			int lastx = -1;
			int lasty = -1;

      void Create();
      void Update();
  };

	template <class T>
  class CellGrid: public GameModel::Grid2d{
    public:
			std::vector<Cell<T>*> Cells;

			Cell<T>* GetCell(int x, int y);
			void SetCell(int x, int y, Cell<T>* value);
			void PushCell(int x, int y, int dir);
			void SwapCell(int x1, int y1, int x2, int y2);

      void Create(int width, int height);
      void Draw();
			void Delete();
  };

  class WorldGrid: public CellGrid<Element::cElement> {
		public:
			void Generate();
			void Tick();
			void Draw();
	};
	class BackgroundGrid: public CellGrid<Element::cBiome> {
    public:
			void Generate();
			void Draw();
  };
};

#endif