#include "stdafx.h"
#include "SurprisedFunction.h"
#include "TargettedMissile.h"
#include "Player.h"
#include "EntityManager.h"

SurprisedFunction::SurprisedFunction(Player* origin,
	Player* target, ParticleEngine* particle_engine, EntityManager* entity_manager,
	ResourceManager<sf::Texture, std::string>* tex_manager) :
	target_(target), particle_engine_(particle_engine),origin_(origin), 
entity_manager_(entity_manager), tex_manager_(tex_manager){
}

void SurprisedFunction::doAction() {
	TargettedMissile* missile = new TargettedMissile(origin_->getPosition(),
		entity_manager_, particle_engine_, tex_manager_, target_);
	entity_manager_->add(missile);
}