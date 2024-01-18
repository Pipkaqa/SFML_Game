#include "Star.h"
#include "GameEngine.h"
#include "Projectile.h"

namespace Game
{
	Star::Star() : GameObject(get_image_name())
	{
		start();
	}

	Star::Star(sf::Color color) : GameObject(color, get_image_name())
	{
		start();
	}

	Star::Star(sf::Vector2f pos) : GameObject(pos, get_image_name())
	{
		start();
	}

	Star::Star(sf::Vector2f pos, sf::Color color) : GameObject(pos, color, get_image_name())
	{
		start();
	}

	Star::~Star()
	{
		on_destroy();
	}

	std::string Star::get_type_name()
	{
		return "Star";
	}

	std::string Star::get_object_type_name() const
	{
		return "Star";
	}

	void Star::init(float speed, float extension, sf::Vector2i m_dir)
	{
		move_speed = speed;
		window_bounds_extension = extension;
		move_direction = m_dir;
	}

	void Star::update()
	{
		if (!GameEngine::instance->check_and_move(*this, move_direction, move_speed, window_bounds_extension))
		{
			GameEngine::instance->destroy(this);
		}
	}

	void Star::notify_collision(GameObject& obj)
	{
		auto objname = obj.get_object_type_name();

		if (objname == Player::get_type_name())
		{
			GameEngine::instance->destroy(this);
			GameEngine::instance->destroy(&obj);
		}
	}

	std::string Star::get_image_name()
	{
		return "star.png";
	}

	void Star::start()
	{

	}

	void Star::on_destroy()
	{

	}
}
