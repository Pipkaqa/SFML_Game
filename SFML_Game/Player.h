#pragma once

#include <iostream>
#include "GameObject.h"

namespace Game
{
	class Player : public GameObject
	{
	public:
		Player();
		Player(sf::Color color);
		Player(sf::Vector2f pos);
		Player(sf::Vector2f pos, sf::Color color);
		~Player();

		static std::string get_type_name();
		std::string get_object_type_name() const;

		void update();
		void receive_mouse_pressed(sf::Mouse::Button button);
		void receive_mouse_released(sf::Mouse::Button button);
		void receive_keyboard_pressed(sf::Keyboard::Key key);
		void receive_keyboard_released(sf::Keyboard::Key key);
		void notify_collision(GameObject& obj);

	protected:
		std::string get_image_name();

	private:
		sf::Vector2i movement_dir;
		const float speed = 5;

		void start();
		void on_destroy();
	};
}
