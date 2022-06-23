#pragma once
#include <SFML/Graphics.hpp>
#include <camera.hpp>
#include <object.hpp>
#include <thread>
#include <chrono>

using namespace std;

namespace nu {
    class FPS {
    public:
        FPS() : mFrame(0), mFps(0) {}
        const unsigned int getFPS() const { return mFps; }

    private:
        unsigned int mFrame;
        unsigned int mFps;
        sf::Clock mClock;

    public:
        void update(){
            if (mClock.getElapsedTime().asSeconds() >= 1.f){
                mFps = mFrame;
                mFrame = 0;
                mClock.restart();
            }

            ++mFrame;
        }
    };

	class Scene {
	public:
		Scene(int width, int height);
		~Scene();
		void LifeCycle();
        void CreateTerror();
        void CreateAWP();

        Clock clock;
        float CurrentFrame = 0;

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

        int score = 0;

        Point* m_points_2 = nullptr;
        Pixel* m_pixels_2 = nullptr;

        int points = 264719;
	};
}