#pragma once

#include "ActionFunction.h"

class Player;
class ParticleEngine;
class EntityManager;

class AngerFunction : public ActionFunction {
public:
	AngerFunction(Player* target, ParticleEngine* particle_engine,
		EntityManager* entity_manager_);
	void doAction();
private:
	Player* target_;
	ParticleEngine* particle_engine_;
	EntityManager* entity_manager_;
};
