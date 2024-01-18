#pragma once

#include "GameObject.h"

namespace Game
{
	class Star : public GameObject
	{
	public:
		Star();
		Star(sf::Color color);
		Star(sf::Vector2f pos);
		Star(sf::Vector2f pos, sf::Color color);
		~Star();

		static std::string get_type_name();
		std::string get_object_type_name() const;

		void init(float speed = 3, float extension = 50, sf::Vector2i m_dir = sf::Vector2i(0, 1));
		void update();
		void notify_collision(GameObject& obj);

	protected:
		std::string get_image_name();

	private:
		sf::Vector2i move_direction;
		float move_speed;
		float window_bounds_extension;

		void start();
		void on_destroy();
	};
}