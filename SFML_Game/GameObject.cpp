#include "GameObject.h"
#include "GameEngine.h"

namespace Game
{
	GameObject::GameObject(std::string image_name)
	{
		init(image_name);
	}

	GameObject::GameObject(sf::Color color, std::string image_name)
	{
		init(image_name, color);
	}

	GameObject::GameObject(sf::Vector2f pos, std::string image_name)
	{
		init(pos, image_name);
	}

	GameObject::GameObject(sf::Vector2f pos, sf::Color color, std::string image_name)
	{
		init(pos, image_name, color);
	}

	GameObject::~GameObject()
	{

	}

	std::string GameObject::get_type_name()
	{
		return "GameObject";
	}

	std::string GameObject::get_object_type_name() const
	{
		return "GameObject";
	}

	sf::Vector2f GameObject::get_center() const
	{
		return sf::Vector2f(get_position().x + get_size().x / 1.5f, get_position().y - get_size().y / 1.75f);
	}

	sf::Vector2f GameObject::get_position() const
	{
		return sprite.getGlobalBounds().getPosition();
	}

	sf::Vector2f GameObject::get_size() const
	{
		return sprite.getGlobalBounds().getSize() - sf::Vector2f(8, 8);
	}

	const sf::Sprite& GameObject::get_sprite() const
	{
		return sprite;
	}

	void GameObject::set_position(float x_pos, float y_pos)
	{
		sprite.setPosition(x_pos, y_pos);
	}

	void GameObject::set_position(sf::Vector2f pos)
	{
		sprite.setPosition(pos);
	}

	void GameObject::init(std::string image_name, sf::Color color)
	{
		sprite = GameEngine::construct_sprite_ff(this, image_texture, image_name);

		sprite.setPosition(GameEngine::instance->get_relative_screen_center(*this));
		sprite.setColor(color);
	}

	void GameObject::init(sf::Vector2f pos, std::string image_name, sf::Color color)
	{
		sprite = GameEngine::construct_sprite_ff(this, image_texture, image_name);

		sprite.setPosition(pos.x, pos.y);
		sprite.setColor(color);
	}
}
