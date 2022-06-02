#pragma once
#include <SFML/Graphics.hpp>
#include <camera.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>

using namespace std;

namespace nu {
    class Object {
    public:
        Object(int points);
        ~Object();
        Pixel* getPixels();
        Point* getPoints();
        void Read();

    private:
        std::unique_ptr<Camera> m_camera;
        Point* m_points = nullptr;
        Pixel* m_pixels = nullptr;
        int m_size = 0;
    };
}