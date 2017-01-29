#pragma once

#include "ActionFunction.h"
#include "ResourceManager.h"

class Player;
class ParticleEngine;
class EntityManager;

class SurprisedFunction : public ActionFunction {
public:
	SurprisedFunction(Player* origin,Player* target, ParticleEngine* particle_engine,
		EntityManager* entity_manager, ResourceManager<sf::Texture, std::string>* tex_manager);
	void doAction();
private:
	Player* origin_;
	Player* target_;
	ParticleEngine* particle_engine_;
	EntityManager* entity_manager_;
	ResourceManager<sf::Texture, std::string>* tex_manager_;
};
