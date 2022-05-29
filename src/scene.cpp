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
		Point position = { 0.0, 0.0, 0.0 };
		Angles angles = { 0.0,0.0,0.0 };
		m_camera = std::make_unique<Camera>(m_width, m_height, intrinsic, position, angles);

		m_points = new Point[300000];
	}
	Scene::~Scene() {
		if (m_points != nullptr)
			delete[] m_points;
	}

	void Scene::LifeCycle() {
		//double y0 = 1;

		while (m_window->isOpen()) {
			sf::Event event;
			while (m_window->pollEvent(event))
				if (event.type == sf::Event::Closed)
					m_window->close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				m_camera->dZ(0.05);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				m_camera->dZ(-0.05);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				m_camera->dX(-0.05);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				m_camera->dX(0.05);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				m_camera->dPitch(-0.0125);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				m_camera->dPitch(0.0125);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				m_camera->dRoll(-0.015);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				m_camera->dRoll(0.015);
			}

            //m_object->Work();

            double x, y, z;
            uint8_t red, g, b;
            //std::ifstream in("points.txt");

            const int col_count= 6, row_count=264719; // нужно указать  количество строк и значений для своего файла
            data_t<col_count> data[row_count];  // массив объектов струкуры соответствующего размера

            string filename= "points.txt";  // имя файла
            fstream f(filename.c_str() ); // открываем файл
            if(f){
                for(int i=0;i<row_count;i++){
                    getline(f,data[i].name,':'); // читаем имя (строку до символа-разделителя ":" )
                    for(int j=0;j<col_count;j++)
                        f >> data[i].values[j];
                    f >> x >> y >> z >> red >> g >> b;
                }
            }
            else cerr<<"Не удалось открыть файл";
// Вывод данных в консольном приложении
            for(int i=0;i<row_count;i++){
                cout<<data[i].name<<"\t";
                for(int j=0;j<col_count;j++) cout<<data[i].values[j]<<"\t";
            }



			//y0 += 0.02;
			m_size = 0;
			double r = 1;
			for (double fi = 0; fi < 6.28; fi += 0.01)
				for (double teta = 0; teta < 3.14; teta += 0.01) {
                    in >> x >> y >> z >> red >> g >> b;
                    m_points[m_size].x = x;
                    m_points[m_size].y = y;
                    m_points[m_size].z = z;

//					m_points[m_size].x = r * sin(teta) * cos(fi);
//					//m_points[m_size].y = r * sin(teta) * sin(fi) + y0;
//                    m_points[m_size].y = r * sin(teta) * sin(fi);
//					m_points[m_size].z = r * cos(teta);
					m_size++;
				}

			// Проецирование точек
			for (int i = 0; i < m_size; i++) {
                in >> x >> y >> z >> red >> g >> b;
                m_camera->ProjectPoint(m_points[i], {red, g, b, 255});
                //m_camera->ProjectPoint(m_points[i], {255, 0, 0, 255});
            }

			m_texture->update((uint8_t*)m_camera->Picture(), 1920, 1080, 0, 0);
			m_camera->Clear();


			m_window->clear();
			m_window->draw(*m_sprite);

			m_window->display();

		}
	}
}