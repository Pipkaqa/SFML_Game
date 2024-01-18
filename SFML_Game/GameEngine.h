#pragma once

#include <iostream>
#include <queue>
#include <thread>
#include <future>
#include <random>
#include "Engine.h"
#include "Player.h"

namespace Game
{
	class GameEngine : public Base::Engine
	{
	public:
		GameEngine();
		~GameEngine();

		static inline GameEngine* instance;

		static inline sf::Sprite construct_sprite_ff(GameObject* owner, sf::Texture& source, std::string file_name)
		{
			if (!source.loadFromFile(instance->images_path + file_name))
			{
				GameEngine::instance->destroy(owner);
			}

			return sf::Sprite(source);
		}

		const sf::Vector2f get_relative_screen_center(const GameObject& relative_to);

		template<typename T>
		T* instantiate()
		{
			return inst_event(new T());
		}

		template<typename T>
		T* instantiate(sf::Vector2f pos)
		{
			return inst_event(new T(pos));
		}

		template<typename T>
		T* instantiate(sf::Color color)
		{
			return inst_event(new T(color));
		}

		template<typename T>
		T* instantiate(sf::Vector2f pos, sf::Color color)
		{
			return inst_event(new T(pos, color));
		}
		
		void launch(int resolution_x, int resolution_y, std::string window_name, int frame_limit);

		void destroy(GameObject* to_destroy);

		bool check_and_move(GameObject& obj, sf::Vector2i dir, float speed, float extension = 0);

	protected:
		std::vector<GameObject*> objects;

		void init();
		void update();
		void draw();

		virtual void game_logic_loop(std::future<void> future);

		void on_mouse_button_pressed(sf::Mouse::Button button);
		void on_mouse_button_released(sf::Mouse::Button button);
		void on_keyboard_key_pressed(sf::Keyboard::Key key);
		void on_keyboard_key_released(sf::Keyboard::Key key);

		virtual void finish_loop();

	private:
		const std::string images_path = "images/";
		const std::string defaults_path = "default/";

		Player* player = nullptr;

		std::queue<std::pair<GameObject&, sf::Vector2f>> to_move_objects;
		std::queue<GameObject*> to_destroy_objects;

		std::promise<void> gll_exit_signal;
		std::thread gll_thread;

		bool game_finished = false;

		void destroy_marked_objects();
		void update_physics();
		void finish_game();

		std::string get_file_name_we(std::string file_path);

		template<typename T>
		T* inst_event(T* obj)
		{
			objects.push_back(obj);

			std::string objname = obj->get_object_type_name();

			std::transform(objname.begin(), objname.end(), objname.begin(), [](unsigned char c) { return std::tolower(c); });
			std::cout << "[LOG] Created " << objname << std::endl;

			return obj;
		}
	};
}
