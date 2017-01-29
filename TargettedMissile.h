#pragma once

#include "MovingEntity.h"

class ParticleEngine;
class Player;

class TargettedMissile : public MovingEntity {
public:
	TargettedMissile(sfld::Vector2f position, EntityManager* entity_manager,
		ParticleEngine* particle_engine, ResourceManager<sf::Texture, std::string>* tex_manager,
		Player* target);

	void update(int frame_time);
private:
	ParticleEngine* particle_engine_;
	Player* target_;
	Player* origin_;
	int timer_;
};