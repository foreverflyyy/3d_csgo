#pragma once
#include <SFML/Graphics.hpp>
#include <camera.hpp>
#include <object.hpp>

#include <thread>
#include <chrono>

using namespace std;

namespace nu {
	class Scene {
	public:
		Scene(int width, int height);
		~Scene();
		void LifeCycle();
        void CreateFence();
        void CreateAWP();

	private:

		std::unique_ptr<Camera> m_camera;
        std::unique_ptr<Object> m_object;
        std::unique_ptr<Object> m_object_2;

		int m_width;
		int m_height;

		std::unique_ptr<sf::RenderWindow> m_window;
        std::unique_ptr<sf::Image> icon;
		std::unique_ptr<sf::Texture> m_texture;
        std::unique_ptr<sf::Texture> m_texture2;
        std::unique_ptr<sf::Texture> m_texture3;
		std::unique_ptr<sf::Sprite> m_sprite;
        std::unique_ptr<sf::Sprite> m_sprite2;
        std::unique_ptr<sf::Sprite> m_sprite3;

		Point* m_points = nullptr;
        Pixel* m_pixels = nullptr;

        Point* m_points_2 = nullptr;
        Pixel* m_pixels_2 = nullptr;

        int points = 264719;
	};
}