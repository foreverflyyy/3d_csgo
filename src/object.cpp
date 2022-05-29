#include <object.hpp>

namespace nu {
    Object::Object() {}
    Object::~Object() {
        if (m_points != nullptr)
            delete[] m_points;
    }

    void Object::Work() {
        //double y0 = 1;
        m_points = new Point[200000];
        //y0 += 0.02;
        m_size = 0;
        double r = 1;
        for (double fi = 0; fi < 6.28; fi += 0.01)
            for (double teta = 0; teta < 1.57; teta += 0.01) {
                m_points[m_size].x = r * sin(teta) * cos(fi);
                //m_points[m_size].y = r * sin(teta) * sin(fi) + y0;
                m_points[m_size].y = r * sin(teta) * sin(fi);
                m_points[m_size].z = r * cos(teta);
                std::cout << "X: " << m_points[m_size].x << "Y: " << m_points[m_size].y << "Z: " << m_points[m_size].z;
                m_size++;
            }
    }
}