#include "Engine.h"

namespace Base
{
	Engine::Engine()
	{
		instance = this;
	}

	Engine::~Engine()
	{
		delete window;
	}

	const bool Engine::running() const
	{
		return window->isOpen();
	}

	void Engine::launch(int resolution_x, int resolution_y, std::string window_name, int frame_limit)
	{
		window = instantiate_window(resolution_x, resolution_y, window_name, frame_limit);
		window->setFramerateLimit(frame_limit);

		window_size = sf::Vector2f(static_cast<float>(resolution_x), static_cast<float>(resolution_y));
		window_center = sf::Vector2f(static_cast<float>(resolution_x) / 2, static_cast<float>(resolution_y) / 2);
	}

	void Engine::init()
	{

	}

	void Engine::start_game_loop()
	{
		init();

		while (running())
		{
			update_mouse_position();
			poll_events();
			update();
			render();
		}
	}

	void Engine::render()
	{
		window->clear();
		draw();
		window->display();
	}

	void Engine::update_mouse_position()
	{
		mouse_pos = sf::Mouse::getPosition(*window);
	}

	void Engine::poll_events()
	{
		while (window->pollEvent(ev))
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::MouseButtonPressed:
				on_mouse_button_pressed(ev.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:
				on_mouse_button_released(ev.mouseButton.button);
				break;
			case sf::Event::KeyPressed:
				on_keyboard_key_pressed(ev.key.code);
				break;
			case sf::Event::KeyReleased:
				on_keyboard_key_released(ev.key.code);
				break;
			}
		}
	}

	sf::RenderWindow* Engine::instantiate_window(int resolution_x, int resolution_y, std::string window_name, int frame_limit)
	{
		return new sf::RenderWindow(sf::VideoMode(resolution_x, resolution_y), window_name, sf::Style::Titlebar | sf::Style::Close);
	}
}
