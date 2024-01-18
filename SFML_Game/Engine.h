#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace Base
{
	class Engine
	{
	public:
		Engine();
		virtual ~Engine();

		static inline Engine* instance;

		static inline sf::Vector2f window_size;
		static inline sf::Vector2f window_center;
		static inline sf::Vector2i mouse_pos;

		const bool running() const;

		virtual void launch(int resolution_x, int resolution_y, std::string window_name, int frame_limit);

	protected:
		sf::RenderWindow* window = nullptr;
		sf::Event ev;

		virtual void update() = 0;
		virtual void draw() = 0;

		virtual void on_mouse_button_pressed(sf::Mouse::Button button) = 0;
		virtual void on_mouse_button_released(sf::Mouse::Button button) = 0;
		virtual void on_keyboard_key_pressed(sf::Keyboard::Key key) = 0;
		virtual void on_keyboard_key_released(sf::Keyboard::Key key) = 0;

		virtual void init();
		void start_game_loop();
		

	private:
		void render();
		void update_mouse_position();
		void poll_events();

		sf::RenderWindow* instantiate_window(int resolution_x, int resolution_y, std::string window_name, int frame_limit);
	};
}
