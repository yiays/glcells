#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <cmath>
#include <algorithm>
#include <GL/glut.h>

namespace GameModel {
	int IterId;

	const int UP 		=	0b001000;
	const int DOWN	=	0b000100;
	const int LEFT	=	0b000010;
	const int RIGHT	=	0b000001;
	const int TO		=	0b100000;
	const int FROM	=	0b010000;

	const float PI 	= 3.141592;

	class GameObject {
		public:
			int Id;

			GameObject();
			void Create();
			void Update();
			void Tick();
			void Draw();
			void Destroy();
	};

	struct Point2f {
		public:
			float x = 0.0;
			float y = 0.0;

			Point2f toAbsolute();
			Point2f toRelative();

			Point2f operator-(Point2f b);
			Point2f operator+(Point2f b);
	};
	struct Point2d {
		public:
			int x = 0;
			int y = 0;

			Point2d toAbsolute();
			Point2d toRelative();

			Point2d operator-(Point2d b);
			Point2d operator+(Point2d b);
	};
	struct Vector {
		public:
			float dir = 0.0;
			float vel = 0.0;

			Point2f getTarget(Point2f origin);
	};
	Vector lineToVector(Point2f point1, Point2f point2);
	struct Rect2f: public Point2f {
		public:
			float w = 5.0;
			float h = 5.0;

			Rect2f(float xr, float yr, float wr, float hr);

			Rect2f toAbsolute();
			Rect2f toRelative();
	};
	struct Rect2d: public Point2d {
		public:
			int w = 5;
			int h = 5;

			Rect2d(int xr, int yr, int wr, int hr);

			Rect2d toAbsolute();
			Rect2d toRelative();
	};

	struct Grid2d: public GameObject {
		public:
			int w;
			int h;
			Rect2f tilesize { 0, 0, 5, 5 };
	};

	class Color { // Color expects rgb color values ranging from 0-255
		public:
			int r = 0.0;
			int g = 0.0;
			int b = 0.0;

			void round() {
				this->r = std::max(std::min(this->r,255),0);
				this->g = std::max(std::min(this->g,255),0);
				this->b = std::max(std::min(this->b,255),0);
			}
			Color operator-(int n) {
				Color res = *this;
				res.r = this->r - n;
				res.g = this->g - n;
				res.b = this->g - n;
				res.round();
				return res;
			}
			Color operator+(int n) {
				Color res = *this;
				res.r = this->r + n;
				res.g = this->g + n;
				res.b = this->g + n;
				res.round();
				return res;
			}
			Color operator*(int n) {
				Color res = *this;
				res.r = this->r * n;
				res.g = this->g * n;
				res.b = this->g * n;
				res.round();
				return res;
			}
			Color operator/(int n) {
				Color res = *this;
				res.r = this->r / n;
				res.g = this->g / n;
				res.b = this->g / n;
				res.round();
				return res;
			}
			bool operator==(Color c){
				return this->r==c.r && this->g==c.g && this->b==c.b;
			}
	};
	Color cNone = {-1, -1, -1};
	Color cWhite = {255, 255, 255};
	Color cGrey = {128, 128, 128};
	Color cBlack = {0, 0, 0};
	Color cRed = {255, 0, 0};
	Color cGreen = {0, 255, 0};
	Color cBlue = {0, 0, 255};
	Color cPink = {255, 128, 128};
	Color cPurple = {196, 0, 0};

	class Entity: public GameObject {
		public:
			Rect2f Position;
	};

	struct ButtonState{
		int button;
		int state;
	};

	Rect2f View = { 0, 0, 1, 1 };
}

#endif