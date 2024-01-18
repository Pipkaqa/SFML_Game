#include "GameEngine.h"
#include "Projectile.h"
#include "Star.h"

namespace Game
{
	GameEngine::GameEngine() : Engine()
	{
		instance = this;
	}

	GameEngine::~GameEngine()
	{
		if (!game_finished)
		{
			gll_exit_signal.set_value();
			gll_thread.join();
		}

		for (auto& obj : objects) delete obj;
	}

	const sf::Vector2f GameEngine::get_relative_screen_center(const GameObject& relative_to)
	{
		return sf::Vector2f(window_center.x - relative_to.get_size().x / 1.5f, window_center.y - relative_to.get_size().y / 1.75f);
	}

	void GameEngine::launch(int resolution_x, int resolution_y, std::string window_name, int frame_limit)
	{
		__super::launch(resolution_x, resolution_y, window_name, frame_limit);

		player = instantiate<Player>();
		gll_thread = std::thread(&GameEngine::game_logic_loop, this, std::move(gll_exit_signal.get_future()));

		start_game_loop();
	}

	void GameEngine::destroy(GameObject* to_destroy)
	{
		to_destroy_objects.push(to_destroy);
	}

	bool GameEngine::check_and_move(GameObject& obj, sf::Vector2i dir, float speed, float extension)
	{
		if (speed == 0) return true;

		sf::Vector2f object_position = obj.get_position();
		sf::Vector2f object_size = obj.get_size();

		sf::Vector2f to_pos = sf::Vector2f(object_position.x + speed * dir.x, object_position.y + speed * dir.y);

		if (dir.x != 0)
		{
			while (true)
			{
				if (speed <= 0) return false;

				if (to_pos.x > -3 - extension && to_pos.x < (window_size.x - object_size.x * 1.25f) + extension)
				{
					to_move_objects.push(std::pair<GameObject&, sf::Vector2f>(obj, sf::Vector2f(to_pos.x, object_position.y)));
					return true;
				}
				else
				{
					to_pos = sf::Vector2f(object_position.x + --speed * dir.x, object_position.y + speed * dir.y);
					continue;
				}
			}
		}
		else if (dir.y != 0)
		{
			while (true)
			{
				if (speed <= 0) return false;

				if (to_pos.y > 0 - extension && to_pos.y < (window_size.y - object_size.y * 1.25f) + extension)
				{
					to_move_objects.push(std::pair<GameObject&, sf::Vector2f>(obj, sf::Vector2f(object_position.x, to_pos.y)));
					return true;
				}
				else
				{
					to_pos = sf::Vector2f(object_position.x + --speed * dir.x, object_position.y + speed * dir.y);
					continue;
				}
			}
		}

		return false;
	}

	void GameEngine::init()
	{

	}

	void GameEngine::update()
	{
		destroy_marked_objects();

		for (auto& obj : objects) obj->update();

		update_physics();
	}

	void GameEngine::draw()
	{
		for (auto& obj : objects) window->draw(obj->get_sprite());
	}

	void GameEngine::game_logic_loop(std::future<void> future)
	{
		std::random_device random_device;
		std::mt19937 generator(random_device());
		std::uniform_int_distribution<> distribution(0, window_size.x);

		while (future.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));

			GameEngine::instance->instantiate<Star>(sf::Vector2f(distribution(generator), -50), sf::Color::Yellow)->init();
		}
	}

	void GameEngine::on_mouse_button_pressed(sf::Mouse::Button button)
	{
		if (player) player->receive_mouse_pressed(button);
	}

	void GameEngine::on_mouse_button_released(sf::Mouse::Button button)
	{
		if (player) player->receive_mouse_released(button);
	}

	void GameEngine::on_keyboard_key_pressed(sf::Keyboard::Key key)
	{
		switch (key)
		{
		case sf::Keyboard::Escape:
			window->close();
			return;
		}

		if (player) player->receive_keyboard_pressed(key);
	}

	void GameEngine::on_keyboard_key_released(sf::Keyboard::Key key)
	{
		if (player) player->receive_keyboard_released(key);
	}

	void GameEngine::finish_loop()
	{
		sf::Font font;

		if (!font.loadFromFile(defaults_path + "default.ttf")) return;

		sf::Text text;

		text.setFont(font);
		text.setFillColor(sf::Color::Red);
		text.setString("You loser!");
		text.setPosition(window_center.x - text.getGlobalBounds().width / 2.0f, window_center.y - text.getGlobalBounds().height / 2.0f);

		while (true)
		{
			window->clear();
			window->draw(text);
			window->display();

			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			window->clear();
			window->display();

			std::this_thread::sleep_for(std::chrono::milliseconds(500));

			while (window->pollEvent(ev))
			{
				if (ev.type == sf::Event::KeyPressed)
				{
					if (ev.key.code == sf::Keyboard::Escape)
					{
						window->close();
						goto ret;
					}
				}
			}
		}
	ret:
		return;
	}

	void GameEngine::destroy_marked_objects()
	{
		while (!to_destroy_objects.empty())
		{
			GameObject* to_destroy = to_destroy_objects.front();

			to_destroy_objects.pop();

			for (std::vector<GameObject*>::iterator it = objects.begin(); it < objects.end(); it++)
			{
				if (*it == to_destroy)
				{
					std::string objname = (*it)->get_object_type_name();

					if (to_destroy == player)
					{
						finish_game();
						return;
					}

					delete to_destroy;

					objects.erase(it);

					std::transform(objname.begin(), objname.end(), objname.begin(), [](unsigned char c) { return std::tolower(c); });
					std::cout << "[LOG] Destroyed " << objname << std::endl;

					break;
				}
			}
		}
	}

	void GameEngine::update_physics()
	{
		while (!to_move_objects.empty())
		{
			std::pair<GameObject&, sf::Vector2f> pair = to_move_objects.front();

			to_move_objects.pop();

			pair.first.set_position(pair.second.x, pair.second.y);
		}

		for (auto& current : objects)
		{
			for (auto& other : objects)
			{
				if (current == other) continue;

				if (current->get_sprite().getGlobalBounds().intersects(other->get_sprite().getGlobalBounds()))
				{
					current->notify_collision(*other);
					other->notify_collision(*current);
				}
			}
		}
	}

	void GameEngine::finish_game()
	{
		player = nullptr;

		gll_exit_signal.set_value();
		gll_thread.join();

		while (!to_destroy_objects.empty()) to_destroy_objects.pop();
		for (auto& obj : objects) destroy(obj);

		destroy_marked_objects();

		game_finished = true;

		finish_loop();
	}

	std::string GameEngine::get_file_name_we(std::string file_path)
	{
		auto first = file_path.begin();
		auto last = file_path.end() - 1;

		while (*last != '/' && last != first) last--;

		file_path.erase(first, ++last);
		file_path.erase(file_path.end() - 4, file_path.end());

		return file_path;
	}
}
