#include "gameengine.h"

namespace Game {
	void GameObject::init() {
		Id = IterId++;
	}

	Rect2f::Rect2f(float xr, float yr, float wr, float hr){
		x=xr;
		y=yr;
		w=wr;
		h=hr;
	}
	Rect2d::Rect2d(int xr, int yr, int wr, int hr){
		x=xr;
		y=yr;
		w=wr;
		h=hr;
	}

	float Color3f::getr() { return r / 255; };
	float Color3f::getg() { return g / 255; };
	float Color3f::getb() { return b / 255; };
}