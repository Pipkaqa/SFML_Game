#include "Projectile.h"
#include "GameEngine.h"
#include "Star.h"

namespace Game
{
	Projectile::Projectile() : GameObject(get_image_name())
	{
		start();
	}

	Projectile::Projectile(sf::Color color) : GameObject(color, get_image_name())
	{
		start();
	}

	Projectile::Projectile(sf::Vector2f pos) : GameObject(pos, get_image_name())
	{
		start();
	}

	Projectile::Projectile(sf::Vector2f pos, sf::Color color) : GameObject(pos, color, get_image_name())
	{
		start();
	}

	Projectile::~Projectile()
	{
		on_destroy();
	}

	std::string Projectile::get_type_name()
	{
		return "Projectile";
	}

	std::string Projectile::get_object_type_name() const
	{
		return "Projectile";
	}

	void Projectile::init(GameObject* owner, float speed, float extension, sf::Vector2i m_dir)
	{
		owner = owner;
		move_speed = speed;
		window_bounds_extension = extension;
		move_direction = m_dir;
	}

	void Game::Projectile::update()
	{
		if (!GameEngine::instance->check_and_move(*this, move_direction, move_speed, window_bounds_extension))
		{
			GameEngine::instance->destroy(this);
		}
	}

	void Game::Projectile::notify_collision(GameObject& obj)
	{
		auto objname = obj.get_object_type_name();

		if (objname == Star::get_type_name())
		{
			GameEngine::instance->destroy(this);
			GameEngine::instance->destroy(&obj);
		}
	}

	std::string Projectile::get_image_name()
	{
		return "projectile.png";
	}

	void Game::Projectile::start()
	{

	}

	void Game::Projectile::on_destroy()
	{

	}
}
