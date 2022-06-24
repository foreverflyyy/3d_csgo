#include <scene.hpp>

namespace nu {
	Scene::Scene(int width, int height) {
		m_width = width;
		m_height = height;
		m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(m_width, m_height), "CS 2.0");
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

    void Scene::CreateAWP(){
        m_texture_2 = std::make_unique<sf::Texture>();

        m_texture_2->loadFromFile("img/awp_top.png", sf::IntRect(0, 0, 320, 180));
        m_sprite_2 = std::make_unique<sf::Sprite>(*m_texture_2);

        m_sprite_2->setPosition(sf::Vector2f(1050, 530));
        m_sprite_2->scale(sf::Vector2f(3.f, 3.f));
    }
    void Scene::Shot(){
        shot = true;
        presentShotX = 1080;
        presentShotY = 610;
        DrawShot();

        //float newX = 948;
        //float newY = 520;

        presentShotX += 0.005*time; //служит дл€ прохождени€ по "кадрам". переменна€ доходит до трех суммиру€ произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
        if (presentShotX > 3) presentShotX -= 3;
        m_sprite_3->setTextureRect(IntRect(96 * int(presentShotX), 96, 96, 96)); //проходимс€ по координатам ’. получаетс€ начинаем рисование с координаты ’ равной 0,96,96*2, и оп€ть 0
        m_sprite_3->move(-0.1*time, 0);//происходит само движение персонажа влево

        shot = false;

        //m_sprite_3->setPosition(sf::Vector2f(1080, 610));
        //m_sprite_3->setPosition(sf::Vector2f(948, 520));
    }

    void Scene::DrawShot(){
        m_texture_3 = std::make_unique<sf::Texture>();

        m_texture_3->loadFromFile("img/shot.png", sf::IntRect(0, 0, 130, 130));
        m_sprite_3 = std::make_unique<sf::Sprite>(*m_texture_3);

        m_sprite_3->setPosition(sf::Vector2f(presentShotX-timer, presentShotY-timer*0.68));
        m_sprite_3->scale(sf::Vector2f(1/2.f, 1/2.f));
    }

    void Scene::LifeCycle() {


        m_object->ReadFile();
        m_object->ReadTerror();
        m_object->ReadSmallTerror();

        //вз€ть в руки авп
        CreateAWP();

        //скрывает курсор
        m_window->setMouseCursorVisible(false);

        //добавл€ем текст
        FPS fps;
        sf::Font font;
        if (!font.loadFromFile("fonts/arial.ttf")){
            throw std::runtime_error("ERROR: font was not loaded.");
        }
        sf::Text text_fps;
        text_fps.setFont(font);
        text_fps.setCharacterSize(24);
        text_fps.setPosition(10, 950);
        text_fps.setFillColor(sf::Color::White);

        sf::Text text_score;
        text_score.setFont(font);
        text_score.setCharacterSize(24);
        text_score.setPosition(10, 10);
        text_score.setFillColor(sf::Color::White);

		while (m_window->isOpen()) {
			sf::Event event;
			while (m_window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    m_window->close();
            }

            if(timer>=1){
                timer+=24;
                m_sprite_3->setPosition(sf::Vector2f(presentShotX-timer, presentShotY-timer*0.68));
                m_sprite_2->setPosition(sf::Vector2f(1150-timer, 630-timer*0.68));
            }
            if(timer >= 132){
                timer = 0;
                shot = false;
            }

            //врем€ считаем
            time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                m_camera->dZ(0.35);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                m_camera->dZ(-0.35);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                m_camera->dX(-0.35);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                m_camera->dX(0.35);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    shot = true;
                    DrawShot();
                    timer = 1;
            }

            //фпс рисуем
            fps.update();
            std::ostringstream ss;
            ss << fps.getFPS();
            text_fps.setString(ss.str());

            //счЄтчик рисуем
            text_score.setString(std::string("Score: ") + std::to_string(score));

            m_points = m_object->getPoints();
            m_pixels = m_object->getPixels();

            for (int i = 0; i < points; i++)
                m_camera->ProjectPoint(m_points[i], { m_pixels[i].r, m_pixels[i].g ,m_pixels[i].b, 255 });

            m_camera->MouseWork();

            m_texture->update((uint8_t*)m_camera->Picture(), 1920, 1080, 0, 0);
			m_camera->Clear();


			m_window->clear();
			m_window->draw(*m_sprite);
            m_window->draw(*m_sprite_2);
            if(shot) m_window->draw(*m_sprite_3);
            m_window->draw(text_fps);
            m_window->draw(text_score);

			m_window->display();


		}
	}
}

/*
// ѕроверка столкновени€
for (int i = 0; i < gribs.size(); i++) {
int X = mario->GetX();
int Y = mario->GetY();
float R = mario->GetR();

int x = gribs[i]->GetX();
int y = gribs[i]->GetY();
float r = gribs[i]->GetR();

float d = sqrt((X - x) * (X - x) + (Y - y) * (Y - y));

if (R + r >= d) {
lose = true;
//                    std::cout << "You loser!";
//window.close();
//                delete gribs[i];
//                gribs.erase(gribs.begin() + i);
//                i--;
}
}*/