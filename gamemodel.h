#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <algorithm>
#include <GL/glut.h>

namespace GameModel {
	int IterId;
	const int UP 		=	0x001000;
	const int DOWN	=	0x000100;
	const int LEFT	=	0x000010;
	const int RIGHT	=	0x000001;
	const int TO		=	0x100000;
	const int FROM	=	0x010000;

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
	};
	struct Point2d {
		public:
			int x = 0;
			int y = 0;

			Point2d toAbsolute();
			Point2d toRelative();
	};
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

	class Color3f { // Color expects rgb color values ranging from 0-255
		public:
			float r = 0.0;
			float g = 0.0;
			float b = 0.0;

			void round() {
				this->r = std::max(std::min(this->r,255.0f),0.0f);
				this->g = std::max(std::min(this->g,255.0f),0.0f);
				this->b = std::max(std::min(this->b,255.0f),0.0f);
			}
			Color3f operator-(float n) {
				this->r -= n;
				this->g -= n;
				this->g -= n;
				this->round();
			}
			Color3f operator+(float n) {
				this->r += n;
				this->g += n;
				this->g += n;
				this->round();
			}
			Color3f operator*(float n) {
				this->r *= n;
				this->g *= n;
				this->g *= n;
				this->round();
			}
			Color3f operator/(float n) {
				this->r /= n;
				this->g /= n;
				this->g /= n;
				this->round();
			}
	};

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