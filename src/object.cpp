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

    void Object::ReadFile() {
        m_size = 0;
        std::string line;
        std::ifstream myfile( "points.txt");

        if (myfile){
            while (getline( myfile, line )){
                std::vector<std::string> r = split(line, " ");

                m_points[m_size].x = stod(r[0]) - 467365;
                m_points[m_size].y = stod(r[1]) - 6063520;
                m_points[m_size].z = stod(r[2]) - 49.5;

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
    void Object::ReadSemiSphere(double first, double second, double third) {
        m_size = 0;
        //double y0 = 1;
        //y0 += 0.02;
        double r = 0.3;
        double r_2 = 0.2;
        for (double fi = 0; fi < 3.14; fi += 0.03)
            for (double teta = 0; teta < 6.28; teta += 0.03) {
                m_points[m_size].x = r * sin(teta) * cos(fi) + first;
                m_points[m_size].y = r_2 * sin(teta) * sin(fi) + second;
                m_points[m_size].z = r * cos(teta) + third;
                m_size++;
            }
    }

    void Object::ReadCicle() {
        m_size = 0;
        //double y0 = 1;
        //y0 += 0.02;
        double r = 1;
        for (double fi = 0; fi < 6.28; fi += 0.001) {
            m_points[m_size].x = r * cos(fi);
            m_points[m_size].y = r * sin(fi);
            m_size++;
        }
    }

    void Object::randomCicle(){
        srand(time(0));
        int random = rand() % 6 +1;

        if(random == 1){
            ReadSemiSphere(11.3, 1.3, 7.2);
        } else if(random == 2){
            ReadSemiSphere(12.3, 7, 7);
        } else if(random == 3){
            ReadSemiSphere(10, -4.5, 7.3);
        } else if(random == 4){
            ReadSemiSphere(9.2, -7.3, 7.4);
        } else if(random == 5){
            ReadSemiSphere(7.5, -13, 7.4);
        } else if(random == 6){
            ReadSemiSphere(5.9, -18.8, 7.4);
        }
    }

    Point* Object::getPoints() {
        return m_points;
    }
    Pixel* Object::getPixels() {
        return m_pixels;
    }
}