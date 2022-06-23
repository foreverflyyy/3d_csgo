#include <camera.hpp>
#include <matrix.hpp>

namespace nu {
	using nu::math::Mat33d;
	using nu::math::Vec3d;

	Camera::Camera(int width, int height, Intrinsic intrinsic, Point position, Angles angles) {
		m_height = height;
		m_width = width;
		m_intrinsic = intrinsic;
		m_picture = new Pixel[m_width * m_height];
		m_position = position;
		m_angles = angles;

		Clear();
	}

	Camera::~Camera() {
		delete[] m_picture;
	}

	Pixel* Camera::Picture() { return m_picture; }

	void Camera::Fill(Pixel pixel) {
		for (int i = 0; i < m_height; i++)
			for (int j = 0; j < m_width; j++)
				m_picture[i * m_width + j] = pixel;
	}

    void Camera::Aim() {
        for (int i = 0; i < m_height; i++)
            for (int j = 0; j < m_width; j++) {
                if(((i <= (m_height/2)+8) && ((m_height/2)-8 <= i)) && ((j <= (m_width/2)+0.5) && ((m_width/2)-0.5 <= j)) ||
                    ((i <= (m_height/2)+0.5) && ((m_height/2)-0.5 <= i)) && ((j <= (m_width/2)+8) && ((m_width/2)-8 <= j)))
                    m_picture[i * m_width + j] = {0, 255, 0, 255};
            }
    }

	void Camera::Clear() {
        Fill({ 0,0,0, 255});
        Aim();
	}

//    void Camera::MouseWork(){
//        int xPos = GET_X_LPARAM(lParam);
//        int yPos = GET_Y_LPARAM(lParam);
//    }

    void Camera::MouseWork(float time){

        sf::Vector2i globalPosition = sf::Mouse::getPosition();
        //std::cout << "X: " << globalPosition.x << "; Y: " << globalPosition.y << std::endl;

        //float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее врем€ в микросекундах
        //clock.restart(); //перезагружает врем€
        //time = time/800; //скорость игры

        //-0,1 это скорость, умножаем еЄ на наше врем€ и получаем пройденное рассто€ние
        //m_sprite->move(0, -0.1*time); m_angles.pitch = (globalPosition.x * 0.003 - 350) + 0.005 * time;

        if(global_x != globalPosition.x || global_y != globalPosition.y){
            m_angles.pitch = (globalPosition.x * 0.003 - 350);
            m_angles.roll = (globalPosition.y * 0.003 + 250);
        }
        global_x = globalPosition.x;
        global_y = globalPosition.y;

        // если будет заходить куда не надо можем установить сами расположение
        //sf::Mouse::setPosition(sf::Vector2i(10, 50));
        //sf::Mouse::setPosition(sf::Vector2i(10, 50), window); // window is a sf::Window
    }

	void Camera::ProjectPoint(Point p, Pixel c) {
		// Ќаклон камеры на 90 градусов
		double X = p.y ;
		double Y = -p.z;
		double Z = p.x;

		double a = m_angles.roll;
		double b = m_angles.pitch;
		double g = m_angles.yaw;

		double cosa = cos(a);
		double cosb = cos(b);
		double sina = sin(a);
		double sinb = sin(b);

		Mat33d R({ {
						  {cosb, 0, -sinb},
						  {-sina * sinb, cosa, -sina * cosb},
						  {cosa * sinb, sina, cosa * cosb}
				  } });

		Vec3d P({ {
						 {X - m_position.x},
						 {Y - m_position.y},
						 {Z - m_position.z}
				 } });

		Vec3d P_res;

		P_res = R * P;

		double x = P_res.get(0, 0);
		double y = P_res.get(1, 0);
		double z = P_res.get(2, 0);

		// объект находитс€ за камерой
		if (z <= 0)
			return;

		// ѕерспективна€ проекци€ (3D->2D)
		double u = x / z;
		double v = y / z;

		// ѕрименение внутренних параметров камеры
		u = u * m_intrinsic.fu + m_intrinsic.du;
		v = v * m_intrinsic.fv + m_intrinsic.dv;

		if (u >= 0 && u < m_width && v >= 0 && v < m_height) {
			m_picture[(int)v * m_width + (int)u] = c;
		}
	}

	void Camera::dX(double d) {
		m_position.x += d * cos(-m_angles.pitch);
		m_position.y += 0;
		m_position.z += d * sin(-m_angles.pitch);
    }

	void Camera::dZ(double d) {
		m_position.x += d * sin(m_angles.pitch);
		//m_position.y += d * sin(m_angles.roll);
		m_position.z += d * cos(m_angles.pitch);
	}

	void Camera::dRoll(double droll) {
		m_angles.roll += droll;
	}

	void Camera::dPitch(double dpitch){
		m_angles.pitch += dpitch;
	}
}