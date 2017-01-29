#pragma once

#include "BaseState.h"
#include "ResourceManager.h"

class EntityManager;
class Controller;
class ActionListener;
class Player;
class ParticleEngine;

class GameState : public BaseState {
public:
	GameState();
	~GameState();
	void start();
	void pause();
	void resume();
	void exit();
	void sfmlEvent(sf::Event evt);

	void update(int frame_time);
	void render(sf::RenderTarget* target);
private:
	int box_delay_;
	int box_timer_;

	void sendEmotionData(std::string data);
	void readEmotionData();
	void loadTextures();
	ResourceManager<sf::Texture, std::string> tex_manager_;
	std::unique_ptr<EntityManager> entity_manager_;
	std::unique_ptr<ActionListener> listener_;

	std::unique_ptr<Controller> wasd_controller_;
	std::unique_ptr<Controller> arrow_controller_;

	Player* player1_;
	Player* player2_;

	const int tick_time = 100;
	int timer_;

	std::unique_ptr<web::http::client::http_client> http_client_;
	web::uri_builder builder_;
	pplx::task<int> http_response_;

	std::unique_ptr<ParticleEngine> particle_engine_;

	sf::Text p1_ahead;
	sf::Text p1_dhead;
	std::vector<sf::Text> p1_attacks;
	std::vector<sf::Text> p1_defences;

	sf::Text p2_ahead;
	sf::Text p2_dhead;
	std::vector<sf::Text> p2_attacks;
	std::vector<sf::Text> p2_defences;

	sf::Text health1;
	sf::Text health2;
};