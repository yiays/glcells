#include <algorithm>
#include <tgmath.h>

#include "cellular.h"

namespace Cellular {
	void Cell::Create() {
		// Does nothing for now
	}
	void Cell::Update() {
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

	void CellGrid::SetSize(int width, int height) {
		this->w = width;
		this->h = height;

		for(int x=0; x<width; x++){
			for(int y=0; y<height; y++){
				this->Cells.push_back(new Cell());
				(*this->Cells.back()).Create();
			}
		}
	}
	Cell* CellGrid::GetCell(int x, int y){
		int i = x+y*this->w;
		if(i >= 0 && x < this->w && y < this->h) {
			return this->Cells[i];
		} else {
			return nullptr;
		}
	}
	void CellGrid::SetCell(Cell* cell, Cell* refcell){
		cell->Element = refcell->Element;
		cell->Mass = refcell->Mass;
		cell->State = refcell->State;
		cell->Temperature = refcell->Temperature;
	}
	void CellGrid::PushCell(Cell* cell, int dir = 0x001111) {
		if(cell->beingpushed) return;
		else cell->beingpushed = true;
		for(int m=pMERGE; m<pOVERMERGE+1; m++){
			for(int x=dir&GameModel::LEFT?-1:0; x<dir&GameModel::RIGHT?2:1; x+=1){
				for(int y=dir&GameModel::UP?-1:0; y<dir&GameModel::DOWN?2:1; y+=1){
					if(x==0 and y==0) continue;
					Cell* neighbour = this->GetCell(x, y);
					if(neighbour == nullptr) continue;
					switch(m){
						case pMERGE:
							if(neighbour->Element != cell->Element) continue;
							// Terminal mass check
							if(neighbour->Mass < sqrt(neighbour->Element->Weight)*1000){
								neighbour->Mass += cell->Mass/(3-x-y);
								cell->Mass			-= cell->Mass/(3-x-y);
								// 3-x-y results in roughly even distribution between all neigbouring cells with a bias towards the right and down
								// Produces this sequence of numbers; 5,4,3,4,3,2,3,2,1
							}
						break;
						case pCASCADE:
							if(neighbour->Element == cell->Element) continue;
							this->PushCell(neighbour);
							if(neighbour->Element == &Element::Vacuum) {
								this->SetCell(neighbour, cell);
								cell->Mass = 0;
							}
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
						cell->beingpushed = false;
						cell->Update();
						return;
					}
				}
			}
		}
		// Failed to clear space, give up. (The function caller can either give up or overwrite this cell)
		cell->beingpushed = false;
		return;
	}
	void CellGrid::SwapCell(Cell* oldcell, Cell* newcell) {
		Cell tmpcell = *oldcell;
		this->SetCell(oldcell, newcell);
		this->SetCell(newcell, &tmpcell);
	}
	void CellGrid::Draw() {
		for(int x=0; x<w; x++){
			for(int y=0; y<h; y++){
				Draw::square(GameModel::Rect2f{ (float)x*32, (float)y*32, 32, 32 }, nullptr, bordercolor);
			}
		}
	}

	void WorldGrid::Generate() {
		for(int x=0; x<this->w; x++){
			for(int y=0; y<this->h; y++){
				Cell* cell = this->GetCell(x, y);
				cell->Element = (x%2==0 ^ y%2==0) ? &Element::Oxygen : &Element::Hydrogen;
				cell->Mass = 500;
				cell->Temperature = 20;
				cell->Update();
			}
		}
	}
	void WorldGrid::Tick() {
		for(int x=0; x<this->w; x++){
			for(int y=0; y<this->h; y++){
				Cell* cell = this->GetCell(x, y);
				// Ignore missing cells (this shouldn't happen)
				if(cell == nullptr) return;
				// Ignore vacuums
				if(cell->State == VACUUM) return;

				// CellState State Machine
				Cell* up = this->GetCell(x,y-1);
				Cell* down = this->GetCell(x,y+1);
				switch(cell->State) {
					case GAS: // Gas: Flow freely and bubble up through liquids
					{
						if(up != nullptr && up->State == LIQUID){
							this->SwapCell(cell, up);
						}else{
							// Randomly float left or right
							if(rand() % 10 == 0){
								// Also, check if the gasses above and below are lighter/heavier
								int yy=0;
								if(up != nullptr && up->State == GAS && up->Mass * up->Element->Weight > cell->Mass * cell->Element->Weight) {
									this->SwapCell(cell, up);
								}else if(down != nullptr && down->State == GAS && down->Mass * down->Element->Weight < cell->Mass * cell->Element->Weight) {
									this->SwapCell(cell, down);
								}else{
									Cell* swapper = this->GetCell(x+(rand()%2==0?1:-1), y);
									if(swapper != nullptr) this->SwapCell(cell, swapper);
								}
							}
						}
					}
					case LIQUID: // Liquid: Flow down and out
					{
						if(cell->State == LIQUID){
							Cell* down = this->GetCell(x, y+1);
							if(down != nullptr && down->State != SOLID){
								this->PushCell(cell, GameModel::DOWN);
							}else{
								this->PushCell(cell, GameModel::DOWN|GameModel::LEFT|GameModel::RIGHT);
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
				Cell* cell = this->GetCell(x, y);
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
							GameModel::Color3f {0, 0, 0},
							1.0
						);
					break;
				}
			}
		}
	}
}
