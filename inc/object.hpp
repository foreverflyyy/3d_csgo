#pragma once
#include <camera.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <cmath>

using namespace std;
using nu::math::Mat33d;
using nu::math::Vec13d;

namespace nu {
    class Object {
    public:
        Object(int points);
        ~Object();
        Pixel* getPixels();
        Point* getPoints();
        void ReadFile();
        //void ReadSemiSphere(double first, double second, double third);
        //void ReadCicle();
        void ReadTerror();
        Point* randomTerror();
        void ReadSmallTerror();

        double cosa = cos(3.14);
        double sina = sin(3.14);
        double cosb = cos(3.14/2);
        double sinb = sin(3.14/2);
        double cosc = cos(3*3.14/4);
        double sinc = sin(3*3.14/4);

    private:
        std::unique_ptr<Camera> m_camera;
        Point* m_points = nullptr;
        Pixel* m_pixels = nullptr;
        int m_size = 0;
    };
}