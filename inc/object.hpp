#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <camera.hpp>
#include <fstream>

namespace nu {
    class Object {
    public:
        Object();
        ~Object();
        void Work();

    private:
        std::unique_ptr<Camera> m_camera;
        Point* m_points = nullptr;
        int m_size = 0;
    };
}