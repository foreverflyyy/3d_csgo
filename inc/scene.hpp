#pragma once
#include <SFML/Graphics.hpp>
#include <camera.hpp>
#include <object.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <sstream>

using namespace std;

namespace nu {
	class Scene {
	public:
		Scene(int width, int height);
		~Scene();
		void LifeCycle();
	private:

		std::unique_ptr<Camera> m_camera;
        std::unique_ptr<Object> m_object;

		int m_width;
		int m_height;

		std::unique_ptr<sf::RenderWindow> m_window;
		std::unique_ptr<sf::Texture> m_texture;
		std::unique_ptr<sf::Sprite> m_sprite;

		Point* m_points = nullptr;
		int m_size = 0;
	};
}