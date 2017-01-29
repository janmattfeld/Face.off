#include "stdafx.h"
#include "TargettedMissile.h"
#include "Player.h"
#include "EntityManager.h"
#include "ParticleEngine.h"

TargettedMissile::TargettedMissile(sfld::Vector2f position, EntityManager* entity_manager,
	ParticleEngine* particle_engine, ResourceManager<sf::Texture, std::string>* tex_manager,
	Player* target)
	:timer_(0), target_(target), particle_engine_(particle_engine){
	entityConstructor(entity_manager, tex_manager, "missile", maths::SHAPE_CIRCLE, position);
}

void TargettedMissile::update(int frame_time) {
	sfld::Vector2f dir = sfld::Vector2f(target_->getPosition() - getPosition()).normalise();
	move(dir, 0.25);
	timer_ += frame_time;

	if (timer_ >= 10000) {
		destroy();
	}

	if (sfld::Vector2f(getPosition() - target_->getPosition()).length() <= 35.0) {
		getEntityManager()->screenShake(0.3f, 500);
		particle_engine_->generateMiniExplosionEffect(getPosition());
		target_->takeDamage(20);
		destroy();
	}
}