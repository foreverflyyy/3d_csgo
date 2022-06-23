#pragma once
#include <iostream>
#include <matrix.hpp>
#include <cmath>
//#include <windows.h>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace nu {
	struct Point {
		double x, y, z;
	};

	struct Angles {
		double roll, pitch, yaw;
	};

	struct Pixel{
        uint8_t r, g, b, a;
	};

	struct Intrinsic{
		double fu, fv;
		double du, dv;
	};

	class Camera{
	public:
		Camera(int width, int height, Intrinsic intrinsic, Point position, Angles angles);
		~Camera();

		Pixel* Picture();
		void Fill(Pixel pixel);
        void Aim();
		void Clear();
		void ProjectPoint(Point p, Pixel c);
		void dX(double d);
		void dZ(double d);
		void dRoll(double droll);
		void dPitch(double dpitch);
        void MouseWork(float time);

	private:
		int m_width;
		int m_height;
		Pixel* m_picture;
		Intrinsic m_intrinsic;

        int global_y;
        int global_x;

        //управляем временем
        Clock clock;

		Point m_position;
		Angles m_angles;
	};
}