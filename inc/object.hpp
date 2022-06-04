#pragma once
#include <camera.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <cmath>

using namespace std;

namespace nu {
    class Object {
    public:
        Object(int points);
        ~Object();
        Pixel* getPixels();
        Point* getPoints();
        void ReadFile();
        void ReadSemiSphere(double first, double second, double third);
        void ReadCicle();
        void randomCicle();

    private:
        std::unique_ptr<Camera> m_camera;
        Point* m_points = nullptr;
        Pixel* m_pixels = nullptr;
        int m_size = 0;
    };
}