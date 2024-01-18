#include "Player.h"
#include "GameEngine.h"
#include "Projectile.h"
#include "Star.h"

namespace Game
{
	Player::Player() : GameObject(get_image_name())
	{
		start();
	}

	Player::Player(sf::Color color) : GameObject(color, get_image_name())
	{
		start();
	}

	Player::Player(sf::Vector2f pos) : GameObject(pos, get_image_name())
	{
		start();
	}

	Player::Player(sf::Vector2f pos, sf::Color color) : GameObject(pos, color, get_image_name())
	{
		start();
	}

	Player::~Player()
	{
		on_destroy();
	}

	std::string Player::get_type_name()
	{
		return "Player";
	}

	std::string Player::get_object_type_name() const
	{
		return "Player";
	}

	void Player::update()
	{
		GameEngine::instance->check_and_move(*this, movement_dir, speed);
	}

	void Player::receive_mouse_pressed(sf::Mouse::Button button)
	{
		switch (button)
		{
		case sf::Mouse::Left:
			GameEngine::instance->instantiate<Projectile>(get_center())->init(this, 7, 50, sf::Vector2i(0, -1));
			break;
		}
	}

	void Player::receive_mouse_released(sf::Mouse::Button button)
	{

	}

	void Player::receive_keyboard_pressed(sf::Keyboard::Key key)
	{
		switch (key)
		{
		case sf::Keyboard::W:
			movement_dir = sf::Vector2i(0, -1);
			break;
		case sf::Keyboard::A:
			movement_dir = sf::Vector2i(-1, 0);
			break;
		case sf::Keyboard::S:
			movement_dir = sf::Vector2i(0, 1);
			break;
		case sf::Keyboard::D:
			movement_dir = sf::Vector2i(1, 0);
			break;
		}
	}

	void Player::receive_keyboard_released(sf::Keyboard::Key key)
	{
		movement_dir = sf::Vector2i(0, 0);
	}

	void Player::notify_collision(GameObject& obj)
	{

	}

	std::string Player::get_image_name()
	{
		return "player.png";
	}

	void Player::start()
	{

	}

	void Player::on_destroy()
	{
		std::cout << "You loser!\n";
	}
}
