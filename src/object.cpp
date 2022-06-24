#include <object.hpp>

namespace nu {
    Object::Object(int points) {
        m_points = new Point[points];
        m_pixels = new Pixel[points];
    }
    Object::~Object() {
        /*if (m_points != nullptr) {
            for(int i=0; i < 391942; i++){
                delete& m_points[i].x;
                delete& m_points[i].y;
                delete& m_points[i].z;
            }
            delete[] m_points;
        }
        if (m_pixels != nullptr) {
            for(int i=0; i < 391942; i++){
                delete& m_pixels[i].r;
                delete& m_pixels[i].g;
                delete& m_pixels[i].b;
            }
            delete[] m_pixels;
        }*/
        delete[]m_points;
        delete[]m_pixels;
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
    void Object::ReadTerror() {
        m_size = 0;
        std::string line;
        std::ifstream myfile( "img/variant.xyz");

        /*Mat33d rotateZ({ {
                                {cos(3.14), -sin(3.14), 0},
                                {sin(3.14),cos(3.14), 0},
                                {0, 0, 1}
                        } });*/

        /*Mat33d rotateX({ {
                                {1, 0, 0},
                                {0,cos(3.14), -sin(3.14)},
                                {0, sin(3.14), cos(3.14)}
                        } });*/

        /*Mat33d rotateY({ {
                                {cos(3.14), 0, sin(3.14)},
                                {0,1, 0},
                                {-sin(3.14), 0, cos(3.14)}
                        } });*/

        Mat33d rotateXZ({ {
                                 {cosc, -sinc, 0},
                                 {sinc*cosb,cosc*cosb, sinb},
                                 {-sinb*cosb, -sinb*cosc, cosb}
                         } });

        if (myfile){
            while (getline( myfile, line )){
                std::vector<std::string> r = split(line, " ");

                m_points[m_size + 264719].x = stod(r[0])+40;
                m_points[m_size + 264719].y = stod(r[1])+10; //+ - отдаляем от дом: - приближаем
                m_points[m_size + 264719].z = stod(r[2])-50;

                Vec13d value({m_points[m_size + 264719].x, m_points[m_size + 264719].y, m_points[m_size + 264719].z});

                Vec13d P_res = value*rotateXZ;

                m_points[m_size + 264719].x = P_res.get(0, 0);
                m_points[m_size + 264719].y = P_res.get(0, 1);
                m_points[m_size + 264719].z = P_res.get(0, 2);

                m_pixels[m_size + 264719] = {255, 0, 0, 255};

                m_size++;
            }
            myfile.close();
        } else
            std::cout << "fooey\n";
    }
    void Object::ReadSmallTerror() {
        m_size = 0;
        std::string line;
        std::ifstream myfile( "img/variant.xyz");

        Mat33d rotateX({ {
                                 {1, 0, 0},
                                 {0,cosb, sinb},
                                 {0, -sinb, cosb}
                         } });
        Mat33d rotateZ({ {
                                 {cosb, -sinb, 0},
                                 {sinb,cosb, 0},
                                 {0, 0, 1}
                         } });

        if (myfile){
            while (getline( myfile, line )){
                std::vector<std::string> r = split(line, " ");

                m_points[m_size + 328331].x = stod(r[0])/25;
                m_points[m_size + 328331].y = stod(r[1])/25+20;
                m_points[m_size + 328331].z = stod(r[2])/25-20;

                Vec13d value({m_points[m_size + 328331].x, m_points[m_size + 328331].y, m_points[m_size + 328331].z});

                Vec13d P_res = value*rotateX*rotateZ;

                m_points[m_size + 328331].x = P_res.get(0, 0);
                m_points[m_size + 328331].y = P_res.get(0, 1);
                m_points[m_size + 328331].z = P_res.get(0, 2);

                m_pixels[m_size + 328331] = {128, 128, 128, 255};

                m_size++;
            }
            myfile.close();
        } else
            std::cout << "fooey\n";
    }

    /*void Object::ReadSemiSphere(double first, double second, double third) {
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
    }*/

    /*void Object::ReadCicle() {
        m_size = 0;
        //double y0 = 1;
        //y0 += 0.02;
        double r = 1;
        for (double fi = 0; fi < 6.28; fi += 0.001) {
            m_points[m_size].x = r * cos(fi);
            m_points[m_size].y = r * sin(fi);
            m_size++;
        }
    }*/

    Point* Object::randomTerror(){


        /*srand(time(0));
        int random = rand() % 6 +1;
        if(random == 1){
            for(int i = 0; i < 508; i++){
                m_points->x += 11.3;
                m_points->y += 1.3;
                m_points->z += 7.2;
            }
        } else if(random == 2){
            for(int i = 0; i < 508; i++){
                m_points->x += 12.3;
                m_points->y += 7;
                m_points->z += 7;
            }
        } else if(random == 3){
            for(int i = 0; i < 508; i++){
                m_points->x += 10;
                m_points->y += -4.5;
                m_points->z += 7.3;
            }
        } else if(random == 4){
            for(int i = 0; i < 508; i++){
                m_points->x += 9.2;
                m_points->y += -7.3;
                m_points->z += 7.4;
            }
        } else if(random == 5){
            for(int i = 0; i < 508; i++){
                m_points->x += 7.5;
                m_points->y += -13;
                m_points->z += 7.4;
            }
        } else if(random == 6){
            for(int i = 0; i < 508; i++){
                m_points->x += 5.9;
                m_points->y += -18.8;
                m_points->z += 7.4;
            }
        }*/
        return m_points;
    }

    Point* Object::getPoints() {
        return m_points;
    }
    Pixel* Object::getPixels() {
        return m_pixels;
    }
}