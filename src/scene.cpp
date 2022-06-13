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
        m_object_2 = std::make_unique<Object>(points);
	}
	Scene::~Scene() {
		if (m_points != nullptr)
			delete[] m_points;
	}

    void Scene::CreateFence(){
        m_texture2 = std::make_unique<sf::Texture>();
        // m_texture2->create(130, 66);
        //m_sprite = std::make_unique<sf::Sprite>(*m_texture2);

        m_texture2->loadFromFile("img/fnc.png", sf::IntRect(10, 10, 130, 66));
        m_sprite2 = std::make_unique<sf::Sprite>(*m_texture2);
    }
    void Scene::CreateAWP(){
        m_texture3 = std::make_unique<sf::Texture>();
        // m_texture2->create(130, 66);
        //m_sprite = std::make_unique<sf::Sprite>(*m_texture2);

        m_texture3->loadFromFile("img/awp_top.png", sf::IntRect(0, 0, 320, 180));
        m_sprite3 = std::make_unique<sf::Sprite>(*m_texture3);

        m_sprite3->setPosition(sf::Vector2f(1050, 530));
        m_sprite3->scale(sf::Vector2f(3.f, 3.f));

        //m_sprite3->setPosition(sf::Vector2f(1200, 600));
        //m_sprite3->scale(sf::Vector2f(3.f, 3.f));
    }

    void Scene::LifeCycle() {
		//double y0 = 1;

        m_object_2->ReadFile();

        //CreateFence();
        CreateAWP();

        //m_object->randomCicle();
        //m_object->ReadSemiSphere(5.9, -18.8, 7.4);

        //�������� ������
        m_window->setMouseCursorVisible(false);

//        if (!icon->loadFromFile("img/icon.ico"))
//            throw std::runtime_error("Error img icon wops");
//        m_window->setIcon(32, 32, icon->getPixelsPtr());

		while (m_window->isOpen()) {
			sf::Event event;
			while (m_window->pollEvent(event))
				if (event.type == sf::Event::Closed)
					m_window->close();

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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                m_camera->dZ(0.35);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                m_sprite3->setPosition(sf::Vector2f(1150, 630));
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                m_sprite3->setPosition(sf::Vector2f(1050, 530));
            }

            m_object->randomCicle();

            m_points = m_object->getPoints();
            m_pixels = m_object->getPixels();

            m_points_2 = m_object_2->getPoints();
            m_pixels_2 = m_object_2->getPixels();

            for (int i = 0; i < points; i++)
                m_camera->ProjectPoint(m_points[i], { 255, 0 ,0, 255 });

            for (int i = 0; i < points; i++)
                m_camera->ProjectPoint(m_points_2[i], { m_pixels_2[i].r, m_pixels_2[i].g ,m_pixels_2[i].b, 255 });

            //�������� ������ �� �� �� ������ ����
            //if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){}

            m_camera->MouseWork();

            m_texture->update((uint8_t*)m_camera->Picture(), 1920, 1080, 0, 0);
			m_camera->Clear();


			m_window->clear();
			m_window->draw(*m_sprite);
            //m_window->draw(*m_sprite2);
            m_window->draw(*m_sprite3);

			m_window->display();

		}
	}
}

/*
public:
    float w, h, dx, dy,x,y, speed;
    int dir, playerScore, health;
    bool life, isMove,isSelect;//�������� ���������� ��������� �������� � ������ �������
    String File;
    Image image;
    Texture texture;
    Sprite sprite;
    Player(String F, float X, float Y, float W, float H){
        dir = 0; speed = 0; playerScore = 0; health = 100; dx = 0; dy = 0;
        life = true; isMove = false; isSelect = false;
        File = F;
        w = W; h = H;
        image.loadFromFile("images/" + File);
        image.createMaskFromColor(Color(0, 0, 255));
        texture.loadFromImage(image);
        sprite.setTexture(texture);

        x = X; y = Y;
        sprite.setTextureRect(IntRect(0, 0, w, h));
        sprite.setOrigin(w / 2, h / 2);
    }
    void update(float time)
    {
        switch (dir)
        {
            case 0: dx = speed; dy = 0; break;
            case 1: dx = -speed; dy = 0; break;
            case 2: dx = 0; dy = speed; break;
            case 3: dx = 0; dy = -speed; break;
        }

        x += dx*time;
        y += dy*time;
        if (!isMove) speed = 0;
        sprite.setPosition(x, y);
        interactionWithMap();
        if (health <= 0){ life = false; }

    }

    float getWidth(){//�������� ������ ������
        return w;
    }
    void setWidth(float width){//���������� ������ �������
        w = width;
    }

    float getHeight(){//����� ������ �������
        return h;
    }
    void setHeight(float height){//������ ������ �������
        h = height;
    }

    float getplayercoordinateX(){
        return x;
    }
    float getplayercoordinateY(){
        return y;
    }


    void moveToCursor(Window window){

    }

    void interactionWithMap()
    {

        for (int i = y / 32; i < (y + h) / 32; i++)
            for (int j = x / 32; j<(x + w) / 32; j++)
            {
                if (TileMap[i][j] == '0')
                {
                    if (dy>0)
                    {
                        y = i * 32 - h;
                    }
                    if (dy<0)
                    {
                        y = i * 32 + 32;
                    }
                    if (dx>0)
                    {
                        x = j * 32 - w;
                    }
                    if (dx < 0)
                    {
                        x = j * 32 + 32;
                    }
                }

                if (TileMap[i][j] == 's') {
                    playerScore++;
                    TileMap[i][j] = ' ';
                }

                if (TileMap[i][j] == 'f') {
                    health -= 40;
                    TileMap[i][j] = ' ';
                }

                if (TileMap[i][j] == 'h') {
                    health += 20;
                    TileMap[i][j] = ' ';
                }

            }
    }

};

class SpriteManager{//��� ����� �� ��������� �����,����� �� �������� �������� �� ��� ���������)
public:
    Image image;
    Texture texture;
    Sprite sprite;
    String name;
    String file;
    int widthOfSprite;
    int heightOfSprite;
    SpriteManager(String File,String Name){
        file = File;
        name = Name;
        image.loadFromFile("images/" + file);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }
};


int main()
{


    RenderWindow window(VideoMode(640, 480), "Lesson 19. kychka-pc.ru");
    view.reset(FloatRect(0, 0, 640, 480));

    Font font;
    font.loadFromFile("CyrilicOld.ttf");
    Text text("", font, 20);
    text.setColor(Color::Black);


    Image map_image;
    map_image.loadFromFile("images/map.png");
    Texture map;
    map.loadFromImage(map_image);
    Sprite s_map;
    s_map.setTexture(map);

    Image quest_image;
    quest_image.loadFromFile("images/missionbg.jpg");
    quest_image.createMaskFromColor(Color(0, 0, 0));
    Texture quest_texture;
    quest_texture.loadFromImage(quest_image);
    Sprite s_quest;
    s_quest.setTexture(quest_texture);
    s_quest.setTextureRect(IntRect(0, 0, 340, 510));
    s_quest.setScale(0.6f, 0.6f);

    SpriteManager playerSprite("hero.png", "Hero");//��� ����� �� ��������� �����,����� �� �������� ��������)

    Player p("heroForRotate.png", 250, 250, 136, 74);

    float currentFrame = 0;
    Clock clock;
    float dX = 0;
    float dY = 0;
    int tempX = 0;//��������� ����� �.������� �� ����� ������� ���� ���� ����
    int tempY = 0;//����� Y
    float distance = 0;//��� ���������� �� ������� �� ���� �������
    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds();

        clock.restart();
        time = time / 800;

        Vector2i pixelPos = Mouse::getPosition(window);//�������� ����� �������
        Vector2f pos = window.mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)


        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
                if (event.key.code == Mouse::Left){//� ������ �����
                    if (p.sprite.getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
                    {
                        p.sprite.setColor(Color::Green);//������ ������ � �������,��� ����� ������ ������,��� �� ������ ��������� � ����� ������� ���
                        p.isSelect = true;
                    }
                }


            if (p.isSelect)//���� ������� ������
                if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
                    if (event.key.code == Mouse::Right){//� ������ ������
                        p.isMove = true;//�� �������� ��������
                        p.isSelect = false;//������ ��� �� ������
                        p.sprite.setColor(Color::White);//���������� ������� ���� �������
                        tempX = pos.x;//�������� ���������� ������� ������� �
                        tempY = pos.y;//� Y

                    }
        }


        if (p.isMove){
            distance = sqrt((tempX - p.x)*(tempX - p.x) + (tempY - p.y)*(tempY - p.y));//������� ��������� (���������� �� ����� � �� ����� �). ��������� ������� ����� �������

            if (distance > 2){//���� �������� ������� �������� �� ����� �������� ������� �������

                p.x += 0.1*time*(tempX - p.x) / distance;//���� �� ���� � ������� ������� �������
                p.y += 0.1*time*(tempY - p.y) / distance;//���� �� ������ ��� ��
            }
            else { p.isMove = false; std::cout << "priehali\n"; }//������� ��� ��� ������ �� ���� � ������� ������� ��������� � �������
        }




        float dX = pos.x - p.x;//������ , ����������� ������, ������� ���������� ������ � ������
        float dY = pos.y - p.y;//�� ��, ���������� y
        float rotation = (atan2(dY, dX)) * 180 / 3.14159265;//�������� ���� � �������� � ��������� ��� � �������
        std::cout << rotation << "\n";//������� �� ������� � ���������
        p.sprite.setRotation(rotation);//������������ ������ �� ��� �������


        ///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
        if (p.life) {
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                p.dir = 1; p.speed = 0.1;
                currentFrame += 0.005*time;
                if (currentFrame > 3) currentFrame -= 3;
                p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 96, 96, 96));
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                p.dir = 0; p.speed = 0.1;
                currentFrame += 0.005*time;
                if (currentFrame > 3) currentFrame -= 3;
                p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 192, 96, 96));
            }

            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                p.dir = 3; p.speed = 0.1;
                currentFrame += 0.005*time;
                if (currentFrame > 3) currentFrame -= 3;
                p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 307, 96, 96));
            }

            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                p.dir = 2; p.speed = 0.1;

                currentFrame += 0.005*time;
                if (currentFrame > 3) currentFrame -= 3;
                p.sprite.setTextureRect(IntRect(96 * int(currentFrame), 0, 96, 96));
            }
            getplayercoordinateforview(p.getplayercoordinateX(), p.getplayercoordinateY());
        }


        p.update(time);


        window.setView(view);
        window.clear();

        window.getSystemHandle();

        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
                if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
                if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
                if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
                if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));
                s_map.setPosition(j * 32, i * 32);

                window.draw(s_map);
            }
        window.draw(p.sprite);
        window.display();
    }
    return 0;
}*/