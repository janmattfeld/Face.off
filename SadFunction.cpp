#include "stdafx.h"
#include "SadFunction.h"
#include "Player.h"
#include "ParticleEngine.h"
#include "EntityManager.h"

SadFunction::SadFunction(Player* target, ParticleEngine* particle_engine)
	: target_(target),
	particle_engine_(particle_engine) {
}

void SadFunction::doAction() {
	target_->slowDown(0.1, 3000);
	particle_engine_->generateMiniBlueEffect(target_->getPosition());
}