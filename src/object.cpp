#include <object.hpp>

namespace nu {
    Object::Object(int points) {
        m_points = new Point[points];
        m_pixels = new Pixel[points];
    }
    Object::~Object() {
        if (m_points != nullptr)
            delete[] m_points;
        if (m_pixels != nullptr)
            delete[] m_pixels;
    }

    std::vector<std::string> split(const std::string& s, const char * delim) {
        std::string::size_type size = s.length();
        char * const buffer = new char[size + 1];
        std::vector<std::string> res;

        strcpy(buffer, s.c_str());

        char* p = strtok(buffer, delim);
        while (p){
            res.push_back(std::string(p));
            p = strtok(NULL, delim);
        }

        delete[]buffer;
        return res;
    }

    void Object::Read() {
        m_size = 0;
        std::string line;
        std::ifstream myfile( "points.txt");

        if (myfile){
            while (getline( myfile, line )){
                std::vector<std::string> r = split(line, " ");

                m_points[m_size].x = stod(r[0]) - 467365;
                m_points[m_size].y = stod(r[1]) - 6063510;
                m_points[m_size].z = stod(r[2]) - 52;

                uint8_t red = stoi(r[3]);
                uint8_t green = stoi(r[4]);
                uint8_t blue = stoi(r[5]);

                m_pixels[m_size] = {red, green, blue, 255};

                m_size++;
            }
            myfile.close();
        } else
            std::cout << "fooey\n";
    }

    Point* Object::getPoints() {
        return m_points;
    }
    Pixel* Object::getPixels() {
        return m_pixels;
    }


    /*void Object::Work() {
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
    }*/
}