#include <algorithm>
#include <tgmath.h>

#include "cellular.h"

namespace Cellular {
	template<class T>
	void Cell<T>::Create() {
		return;
	}

	template<>
	void Cell<Element::cElement>::Update() {
		// Check if element should in fact be a vacuum
		if(this->Mass <= 0) {
			this->Element = &Element::Vacuum;
			this->State = VACUUM;
			this->Temperature = abs0;
			return;
		}

		// Check if state should be updated to reflect temperature
		if(this->Element == &Element::Vacuum) {
			this->State = VACUUM;
			return;
		}
		if (this->Temperature < this->Element->StateTransitions[0]) { this->State = SOLID; }
		else if (this->Temperature < this->Element->StateTransitions[1]) { this->State = LIQUID; }
		else { this->State = GAS; }
	};
	template <class T>
	void Cell<T>::Update() {
		return;
	}

	template <class T>
	void CellGrid<T>::Create(int width, int height) {
		this->w = width;
		this->h = height;

		for (auto c: this->Cells){
			delete c;
		}
		this->Cells.clear();
		for(int x=0; x<width; x++){
			for(int y=0; y<height; y++){
				this->Cells.push_back(new Cell<T>());
				(*this->Cells.back()).Create();
			}
		}
	}
	template <class T>
	void CellGrid<T>::Delete() {
		for (auto c: this->Cells){
			delete c;
		}
		this->Cells.clear();
		delete *this->Cells;
	}
	template <class T>
	Cell<T>* CellGrid<T>::GetCell(int x, int y){
		int i = x+y*this->w;
		if(i >= 0 && x < this->w && y < this->h) {
			return this->Cells[i];
		} else {
			return nullptr;
		}
	}
	template <class T>
	void CellGrid<T>::SetCell(int x, int y, Cell<T>* value){
		int i = x+y*this->w;
		if(i >= 0 && x < this->w && y < this->h) {
			this->Cells[i] = value;
		}
	}
	template<>
	void CellGrid<Element::cElement>::PushCell(int x, int y, int dir) {
		Cell<Element::cElement>* cell = this->GetCell(x,y);
		if(cell == nullptr || cell->lock) return;

		cell->lock = true;
		for(int m=pMERGE; m<pOVERMERGE+1; m++){
			for(int dx=dir&GameModel::LEFT?-1:0; dx<dir&GameModel::RIGHT?2:1; dx+=1){
				for(int dy=dir&GameModel::UP?-1:0; dy<dir&GameModel::DOWN?2:1; dy+=1){
					if(dx==0 and dy==0) continue;
					Cell<Element::cElement>* neighbour = this->GetCell(dx, dy);
					if(neighbour == nullptr || neighbour->lock) continue;
					switch(m){
						case pMERGE:
							if(neighbour->Element != cell->Element) continue;
							// Terminal mass check
							if(neighbour->Mass < sqrt(neighbour->Element->Weight)*1000){
								neighbour->Mass += cell->Mass/(3-dx-dy);
								cell->Mass			-= cell->Mass/(3-dx-dy);
								// 3-x-y results in roughly even distribution between all neigbouring cells with a bias towards the right and down
								// Produces this sequence of numbers; 5,4,3,4,3,2,3,2,1
							}
						break;
						case pCASCADE:
							if(neighbour->Element == cell->Element) continue;
							if(neighbour->Element == &Element::Vacuum) {
								this->SetCell(dx, dy, cell);
								this->SetCell(x, y, new Cell<Element::cElement>());
								break;
							}
							this->PushCell(dx, dy, 0b001111);
						break;
						case pOVERMERGE:
							if(neighbour->Element != cell->Element) continue;
							// Skip terminal mass check
							neighbour->Mass += cell->Mass/(3-x-y);
							cell->Mass			-= cell->Mass/(3-x-y);
							// 3-x-y results in roughly even distribution between all neigbouring cells with a bias towards the right and up
							// Produces this sequence of numbers; 5,4,3,4,3,2,3,2,1
						break;
					}

					// Wrap things up as soon as the cell has been vacated
					if(cell->Mass <= 0){
						cell->lastx = x;
						cell->lasty = y;
						cell->Update();
						return;
					}
				}
			}
		}
		// Failed to clear space, give up. (The function caller can either give up or overwrite this cell)
		cell->lock = false;
		return;
	}
	template <class T>
	void CellGrid<T>::SwapCell(int x1, int y1, int x2, int y2) {
		if(x1 >= 0 && y1 >= 0 && x1 < this->w && y1 < this->h && x2 >= 0 && y2 >= 0 && x2 < this->w && y2 < this->h) {
			Cell<T>* tmp1 = this->GetCell(x1, y1);
			if(tmp1->lock) return;
			Cell<T>* tmp2 = this->GetCell(x2, y2);
			if(tmp2->lock) return;

			tmp1->lock = true;
			tmp2->lock = true;
			tmp1->lastx = x1;
			tmp1->lasty = y1;
			tmp2->lastx = x2;
			tmp2->lasty = y2;
			
			this->SetCell(x1, y1, tmp2);
			this->SetCell(x2, y2, tmp1);
		}
	}
	template <class T>
	void CellGrid<T>::Draw() {
		for(int x=0; x<w; x++){
			for(int y=0; y<h; y++){
				Draw::square(GameModel::Rect2f{ (float)x*32, (float)y*32, 32, 32 }, GameModel::cNone, bordercolor);
			}
		}
	}

	void WorldGrid::Generate() {
		for(int x=0; x<this->w; x++){
			for(int y=0; y<this->h; y++){
				Cell<Element::cElement>* cell = this->GetCell(x, y);
				cell->Element = (x%2==0 ^ y%2==0) ? &Element::Oxygen : &Element::Hydrogen;
				cell->Mass = 4000;
				cell->Temperature = 20;
				cell->Update();
			}
		}
	}
	void WorldGrid::Tick() {
		for(int x=0; x<this->w; x++){
			for(int y=0; y<this->h; y++){
				Cell<Element::cElement>* cell = this->GetCell(x, y);
				// Ignore missing cells (this shouldn't happen)
				if(cell == nullptr) return;
				// Ignore vacuums
				if(cell->State == VACUUM) return;

				cell->lastx = x;
				cell->lasty = y;
				cell->lock = false; // Unlocks all locked cells from last iteration

				// CellState State Machine
				Cell<Element::cElement>* up = this->GetCell(x,y-1);
				Cell<Element::cElement>* down = this->GetCell(x,y+1);
				switch(cell->State) {
					case GAS: // Gas: Flow freely and bubble up through liquids
					{
						if(up != nullptr && up->State == LIQUID){
							this->SwapCell(x, y, x, y-1);
						}else{
							// Randomly float left or right
							if(rand() % 5 == 0){
								// Also, check if the gasses above and below are lighter/heavier
								if(up != nullptr && up->State == GAS && up->Mass * up->Element->Weight > cell->Mass * cell->Element->Weight) {
									this->SwapCell(x, y, x, y-1);
								}else if(down != nullptr && down->State == GAS && down->Mass * down->Element->Weight < cell->Mass * cell->Element->Weight) {
									this->SwapCell(x, y, x, y+1);
								}else{
									this->SwapCell(x, y, x+(rand()%2==0?1:-1), y);
								}
							}
						}
					}
					case LIQUID: // Liquid: Flow down and out
					{
						if(cell->State == LIQUID){
							Cell<Element::cElement>* down = this->GetCell(x, y+1);
							if(down != nullptr && down->State != SOLID){
								this->PushCell(x, y+1, GameModel::DOWN);
							}else{
								this->PushCell(x, y+1, GameModel::DOWN|GameModel::LEFT|GameModel::RIGHT);
							}
						}
					}
					case SOLID: // Spread temperature
						// TODO: temperature
					break;
				}
			}
		}
	}
	void WorldGrid::Draw() {
		for(int x=0; x<this->w; x++){
			for(int y=0; y<this->h; y++){
				Cell<Element::cElement>* cell = this->GetCell(x, y);
				switch (cell->State)
				{
					case GAS:
						Draw::square(
							GameModel::Rect2f{ (float)x*32, (float)y*32, 32, 32 },
							cell->Element->Color,
							std::max(std::min(cell->Mass/4000.0f, 1.0f), 0.1f)
						);
					break;
					case LIQUID:
						Draw::square(
							GameModel::Rect2f{ (float)x*32, (float)y*32, 32, 16 },
							cell->Element->Color,
							0.2
						);
						Draw::square(
							GameModel::Rect2f{ (float)x*32, (float)y*32+16, 32, 16 },
							cell->Element->Color,
							cell->Element->Color - 50,
							0.7
						);
					break;
					case SOLID:
						Draw::square(
							GameModel::Rect2f{ (float)x*32, (float)y*32, 32, 32 },
							cell->Element->Color,
							GameModel::Color {0, 0, 0},
							1.0
						);
					break;
				}
			}
		}
		for(int x=0; x<this->w; x++){
			for(int y=0; y<this->h; y++){
				Cell<Element::cElement>* cell = this->GetCell(x, y);
				if(cell->lastx != x || cell->lasty != y){
					if(cell->lastx == -1 && cell->lasty == -1)
						Draw::square({(float)x*32, (float)y*32, 32, 32}, GameModel::cNone, GameModel::cGrey);
					else
						Draw::line({(float)x*32+16,(float)y*32+16}, {(float)cell->lastx*32+16,(float)cell->lasty*32+16});
				}
			}
		}
	}

	void BackgroundGrid::Generate() {
		for(int x=0; x<this->w; x++){
			for(int y=0; y<this->h; y++){
				Cell<Element::cBiome>* cell = this->GetCell(x, y);
				cell->Element = &Element::Marsh;
			}
		}
	}
	void BackgroundGrid::Draw() {
		for(int x=0; x<this->w; x++){
			for(int y=0; y<this->h; y++){
				Cell<Element::cBiome>* cell = this->GetCell(x, y);
				Draw::square(
					GameModel::Rect2f{ (float)x*32, (float)y*32, 32, 32 },
					cell->Element->Color
				);
			}
		}
	}
}
