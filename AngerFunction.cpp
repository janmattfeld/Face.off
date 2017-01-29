#include "stdafx.h"
#include "AngerFunction.h"
#include "Player.h"
#include "ParticleEngine.h"
#include "EntityManager.h"

AngerFunction::AngerFunction(Player* target, ParticleEngine* particle_engine,
	EntityManager* entity_manager) : target_(target), entity_manager_(entity_manager),
	particle_engine_(particle_engine){
}

void AngerFunction::doAction() {
	target_->takeDamage(20);
	particle_engine_->generateExplosionEffect(target_->getPosition());
	entity_manager_->screenShake(1.f, 1000);
}