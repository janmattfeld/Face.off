#pragma once

#include "ActionFunction.h"

class Player;
class ParticleEngine;
class EntityManager;

class SadFunction : public ActionFunction {
public:
	SadFunction(Player* target, ParticleEngine* particle_engine);
	void doAction();
private:
	Player* target_;
	ParticleEngine* particle_engine_;
};
