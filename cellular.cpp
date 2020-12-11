#include "cellular.h"
#include "gl2d.cpp"

namespace Cellular {
	void CellGrid::setsize(int width, int height) {
		this->w = width;
		this->h = height;

		for(int x=0; x<width; x++){
			for(int y=0; y<height; y++){
				this->Cells.push_back(new Cell());
				(*this->Cells.back()).create();
			}
		}
	}

	void GasGrid::draw() {
		for(int x=0; x<w; x++){
			for(int y=0; y<h; y++){
				Draw::square(Game::Rect2f{ (float)x*32, (float)y*32, 32, 32 }, (*this->Cells[x+(y*w)]).Element->Color, bordercolor);
			}
		}
	}
	
	void Cell::create() {
		this->Element = &Elemental::Vacuum;
		update();
	}
	void Cell::update() {
		if(Element == &Elemental::Vacuum) {
			this->State = vacuum;
			return;
		}
		if (this->Temperature < this->Element->StateTransitions[0]) { this->State = solid; }
		else if (this->Temperature < this->Element->StateTransitions[1]) { this->State = liquid; }
		else { this->State = gas; }
	};
}

namespace Automata {
	void init(int w, int h) {
		GasGrid.setsize(w, h);
		//LiquidGrid->setsize(w, h);
		//SolidGrid->setsize(w, h);
		//BackgroundGrid->setsize(w, h);

		for(int x=0; x<w; x++){
			for(int y=0; y<h; y++){
				(*GasGrid.Cells[x+y*w]).Element = (x<w/2) ? &Elemental::Oxygen : &Elemental::Hydrogen;
				(*GasGrid.Cells[x+y*w]).update();
			}
		}
	}
}
