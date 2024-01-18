#pragma once

#include "GameObject.h"

namespace Game
{
	class Projectile : public GameObject
	{
	public:
		Projectile();
		Projectile(sf::Color color);
		Projectile(sf::Vector2f pos);
		Projectile(sf::Vector2f pos, sf::Color color);
		~Projectile();

		static std::string get_type_name();
		std::string get_object_type_name() const;

		void init(GameObject* owner, float speed = 3, float extension = 50, sf::Vector2i m_dir = sf::Vector2i(0, -1));
		void update();
		void notify_collision(GameObject& obj);

	protected:
		std::string get_image_name();

	private:
		GameObject* owner;
		sf::Vector2i move_direction;
		float move_speed;
		float window_bounds_extension;

		void start();
		void on_destroy();
	};
}
