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

        m_object = std::make_unique<Object>(points);
	}
	Scene::~Scene() {
		if (m_points != nullptr)
			delete[] m_points;
	}

    void Scene::LifeCycle() {
		//double y0 = 1;

        m_object->Read();

		while (m_window->isOpen()) {
			sf::Event event;
			while (m_window->pollEvent(event))
				if (event.type == sf::Event::Closed)
					m_window->close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				m_camera->dZ(0.55);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				m_camera->dZ(-0.55);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				m_camera->dX(-0.55);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				m_camera->dX(0.55);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				m_camera->dPitch(-0.05525);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				m_camera->dPitch(0.05125);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				m_camera->dRoll(-0.05115);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				m_camera->dRoll(0.05115);
			}

            m_points = m_object->getPoints();
            m_pixels = m_object->getPixels();

            for (int i = 0; i < points; i++)
                m_camera->ProjectPoint(m_points[i], { m_pixels[i].r, m_pixels[i].g ,m_pixels[i].b, m_pixels[i].a });


            m_texture->update((uint8_t*)m_camera->Picture(), 1920, 1080, 0, 0);
			m_camera->Clear();


			m_window->clear();
			m_window->draw(*m_sprite);

			m_window->display();

		}
	}
}