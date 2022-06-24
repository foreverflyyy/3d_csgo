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
        void CreateAWP();
        void Shot();
        void DrawShot();

        float currentFrame = 0;
        Clock clock;

	private:

		std::unique_ptr<Camera> m_camera;
        std::unique_ptr<Object> m_object;

        bool shot = false;

        float presentShotX = 1080;
        float presentShotY = 603;
        float time;
        float timer = 0;

		int m_width;
		int m_height;

		std::unique_ptr<sf::RenderWindow> m_window;
		std::unique_ptr<sf::Texture> m_texture;
        std::unique_ptr<sf::Texture> m_texture_2;
        std::unique_ptr<sf::Texture> m_texture_3;
		std::unique_ptr<sf::Sprite> m_sprite;
        std::unique_ptr<sf::Sprite> m_sprite_2;
        std::unique_ptr<sf::Sprite> m_sprite_3;

		Point* m_points = nullptr;
        Pixel* m_pixels = nullptr;

        int score = 0;

        int points = 391942;
	};
}