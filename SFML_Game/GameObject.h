#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Object.h"

namespace Game
{
	class GameObject : public Base::Object
	{
	public:
		GameObject(std::string image_name);
		GameObject(sf::Color color, std::string image_name);
		GameObject(sf::Vector2f pos, std::string image_name);
		GameObject(sf::Vector2f pos, sf::Color color, std::string image_name);
		~GameObject();

		static std::string get_type_name();
		std::string get_object_type_name() const;

		sf::Vector2f get_center() const;
		sf::Vector2f get_position() const;
		sf::Vector2f get_size() const;
		const sf::Sprite& get_sprite() const;

		virtual void update() = 0;
		virtual void notify_collision(GameObject& obj) = 0;

		void set_position(float x_pos, float y_pos);
		void set_position(sf::Vector2f pos);

	protected:
		virtual void start() = 0;
		virtual void on_destroy() = 0;
		virtual std::string get_image_name() = 0;

	private:
		void init(std::string image_name, sf::Color color = sf::Color::White);
		void init(sf::Vector2f pos, std::string image_name, sf::Color color = sf::Color::White);

		sf::Texture image_texture;
		sf::Sprite sprite;
	};
}
