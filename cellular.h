#ifndef CELLULAR_H
#define CELLULAR_H

#include <vector>
#include <string>

#include "gl2d.h"
#include "elements.h"

#define abs0 -273.1;

namespace Cellular{
	Game::Color3f bordercolor = { 20.0, 20.0, 20.0 };

	enum CellState { solid, liquid, gas, vacuum };
  class Cell {
		public:
			struct Elemental::Element* Element;
			float Mass = 0;
			float Temperature = abs0;
			enum CellState State;

      void create();
      void update();
  };

  class CellGrid: public Game::Grid2d{
    public:
			std::vector<Cell*> Cells;

      void setsize(int width, int height);

      void draw();
  };

  class GasGrid: public CellGrid {
		public:
			using CellGrid::Cells;

			void draw();
	};
	class LiquidGrid: public CellGrid {
    public:
			using CellGrid::Cells;
  };
	class SolidGrid: public CellGrid {
    public:
			using CellGrid::Cells;
  };
	class BackgroundGrid: public CellGrid {
    public:
			using CellGrid::Cells;
  };
};

namespace Automata {
	Cellular::GasGrid GasGrid;
	Cellular::LiquidGrid LiquidGrid;
	Cellular::SolidGrid SolidGrid;
	Cellular::BackgroundGrid BackgroundGrid;

  void init(int w, int h);
}

#endif