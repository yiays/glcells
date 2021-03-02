#include "gamemodel.h"

namespace GameModel {
	GameObject::GameObject() {
		Id = IterId++;
	}

	Point2f Point2f::toAbsolute(){
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);

		Point2f result;
		result.x = (this->x + View.x - width/2) * View.w;
		result.y = (this->y + View.y - height/2) * View.h;

		return result;
	}
	Point2f Point2f::operator-(Point2f b){
		return { this->x - b.x, this->y - b.y };
	}
	Point2f Point2f::operator+(Point2f b){
		return { this->x + b.x, this->y + b.y };
	}

	Point2d Point2d::toAbsolute(){
		int width = glutGet(GLUT_WINDOW_WIDTH);
		int height = glutGet(GLUT_WINDOW_HEIGHT);

		Point2d result;
		result.x = (this->x + View.x - width/2) * View.w;
		result.y = (this->y + View.y - height/2) * View.h;

		return result;
	}
	Point2d Point2d::operator-(Point2d b){
		return { this->x - b.x, this->y - b.y };
	}
	Point2d Point2d::operator+(Point2d b){
		return { this->x + b.x, this->y + b.y };
	}

	Point2f Vector::getTarget(Point2f origin) {
		return { origin.x+std::cos((-this->dir)*PI)*this->vel, origin.y+std::sin((-this->dir)*PI)*this->vel };
	}

	Vector lineToVector(Point2f point1, Point2f point2) {
		Point2f diff = point2 - point1;
		return { std::atan2(diff.y, diff.x), std::hypotf(diff.x, diff.y) };
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

		result.x = (this->x) * (1/View.w) + View.x - width/2;
		result.y = (this->y) * (1/View.h) + View.y - height/2;
		result.w = this->w * View.w;
		result.h = this->h * View.h;

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

		result.x = (this->x + View.x - width/2) * View.w;
		result.y = (this->y + View.y - height/2) * View.h;
		result.w = this->w * View.w;
		result.h = this->h * View.h;

		return result;
	}
}