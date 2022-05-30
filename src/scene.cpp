#include <scene.hpp>

namespace nu {
	Scene::Scene(int width, int height) {
		m_width = width;
		m_height = height;
		m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_width, m_height), "3D Engine");
		m_texture = std::make_unique<sf::Texture>();
		m_texture->create(m_width, m_height);
		m_sprite = std::make_unique<sf::Sprite>(*m_texture);

		Intrinsic intrinsic = { 960.0, 540.0, 960.0, 540.0 };
		Point position = { 0.0, 0, 0.0 };
		Angles angles = { 0.0,0.0,0.0 };
		m_camera = std::make_unique<Camera>(m_width, m_height, intrinsic, position, angles);

		m_points = new Point[264719];
	}
	Scene::~Scene() {
		if (m_points != nullptr)
			delete[] m_points;
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

    void Scene::LifeCycle() {
		//double y0 = 1;

		while (m_window->isOpen()) {
			sf::Event event;
			while (m_window->pollEvent(event))
				if (event.type == sf::Event::Closed)
					m_window->close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				m_camera->dZ(20.05);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				m_camera->dZ(-20.05);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				m_camera->dX(-20.05);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				m_camera->dX(20.05);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				m_camera->dPitch(-20.0125);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				m_camera->dPitch(20.0125);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				m_camera->dRoll(-20.015);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				m_camera->dRoll(20.015);
			}

            //m_object->Work();
            //double x, y, z;
            //uint8_t red, g, b;
            m_size = 0;
            string line;
            ifstream myfile( "points.txt");
            if (myfile){
                while (getline( myfile, line )){
                    //std::cout << "Source string: " << line << std::endl;
                    std::vector<std::string> r = split(line, " ");
                    m_points[m_size].x = stod(r[0]) - 467365;
                    m_points[m_size].y = stod(r[1]) - 6063510;
                    m_points[m_size].z = stod(r[2]) - 52;
                    //m_camera->ProjectPoint(m_points[m_size], {255, 0, 0, 255});
                    std::vector<uint8_t> red_r(r[3].begin(), r[3].end());
                    uint8_t red = red_r[0];
                    std::vector<uint8_t> green_g(r[4].begin(), r[4].end());
                    uint8_t green = green_g[0];
                    std::vector<uint8_t> blue_b(r[5].begin(), r[5].end());
                    uint8_t blue = blue_b[0];
                    m_camera->ProjectPoint(m_points[m_size], {red, green, blue, 255});
                    //cout << "First: " << m_points[m_size].x  << " ; Second: " << m_points[m_size].y  << " ; Third: " << m_points[m_size].z << endl;
                    m_size++;
                }
                myfile.close();
            } else
                cout << "fooey\n";

			m_texture->update((uint8_t*)m_camera->Picture(), 1920, 1080, 0, 0);
			m_camera->Clear();


			m_window->clear();
			m_window->draw(*m_sprite);

			m_window->display();

		}
	}
}