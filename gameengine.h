#ifndef GAMEENGINE_H
#define GAMEENGINE_H

namespace Game {

	int IterId;

	float FPS = 0.0;

	class GameObject {
		public:
			int Id;

			void init();
			void create();
			void update();
			void tick();
			void draw();
			void destroy();
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

			float getr();
			float getg();
			float getb();
	};

	class Entity: public GameObject {
		public:
			Rect2f Position;
	};

	struct ButtonState{
		int button;
		int state;
	};

	Point2d MousePos = {0, 0};
	ButtonState MouseState = {0, 0};
	Rect2f view = { 0, 0, 1, 1 };
}

#endif