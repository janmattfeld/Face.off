#pragma once

#include "Entity.h"

class Player;
class ParticleEngine;
class ActionListener;

class DefenceBox : public Entity {
public:
	DefenceBox(Player* player1, Player* player2, sfld::Vector2f position,
		EntityManager* entity_manager, ResourceManager<sf::Texture, std::string>* tex_manager,
		ParticleEngine* particle_engine, ActionListener* listener);

	void update(int frame_time);
private:
	ResourceManager<sf::Texture, std::string>* texture_manager_;
	Player* player1_;
	Player* player2_;
	ParticleEngine* particle_engine_;
	ActionListener* listener_;
};