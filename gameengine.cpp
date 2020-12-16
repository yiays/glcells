#include "gameengine.h"

namespace Game {
	void GameObject::init() {
		Id = IterId++;
	}

	Point2f Point2f::toAbsolute(){
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);

		Point2f result;
		result.x = (this->x + view.x - width/2) * view.w;
		result.y = (this->y + view.y - height/2) * view.h;

		return result;
	}
	Point2d Point2d::toAbsolute(){
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);

		Point2d result;
		result.x = (this->x + view.x - width/2) * view.w;
		result.y = (this->y + view.y - height/2) * view.h;

		return result;
	}

	Rect2f::Rect2f(float xr, float yr, float wr, float hr){
		x=xr;
		y=yr;
		w=wr;
		h=hr;
	}
	Rect2f Rect2f::toAbsolute(){
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);

		Rect2f result(0,0,0,0);

		result.x = (this->x) * (1/view.w) + view.x - width/2;
		result.y = (this->y) * (1/view.h) + view.y - height/2;
		result.w = this->w * view.w;
		result.h = this->h * view.h;

		return result;
	}
	Rect2d::Rect2d(int xr, int yr, int wr, int hr){
		x=xr;
		y=yr;
		w=wr;
		h=hr;
	}
	Rect2d Rect2d::toAbsolute(){
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);

		Rect2d result(0,0,0,0);

		result.x = (this->x + view.x - width/2) * view.w;
		result.y = (this->y + view.y - height/2) * view.h;
		result.w = this->w * view.w;
		result.h = this->h * view.h;

		return result;
	}

	float Color3f::getr() { return r / 255; };
	float Color3f::getg() { return g / 255; };
	float Color3f::getb() { return b / 255; };
}