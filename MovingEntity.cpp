#include "stdafx.h"
#include "MovingEntity.h"
#include "EntityManager.h"
#include "Collision.h"

void MovingEntity::move(sfld::Vector2f dir, double mag) {
	EntityPtrList* entities = getEntityManager()->getEntities();
	for (auto& ent : *entities) {
		if (ent.get() != this) {
			float d = sfld::Vector2f(ent->getPosition() - getPosition()).length();
			if (d < Collision::SAT_MAX_BOUND) {
				MTV mtv(Collision::getCollision(*getSprite(), getShape(),
					*ent->getSprite(), ent->getShape()));
				if (mtv.axis != MTV::NONE.axis && mtv.overlap != MTV::NONE.overlap) {
					//collision detected
					sfld::Vector2f n = mtv.axis;
					sfld::Vector2f u(0.0f, 0.0f);
					if (dir.dot(n) < 0 && n != sfld::Vector2f(0, 0)) {
						u = n * (dir.dot(n) / n.dot(n));
					}
					dir = dir - u;
				}
			}
		}
	}

	//Rotate based on direction
	if (dir != sf::Vector2f(0, 0)) {
		getSprite()->setRotation(maths::toDegrees(atan2(dir.y, dir.x)));
	}
	sfld::Vector2f newpos = getPosition() + dir*(float)mag;
	if (newpos.x > 16 && newpos.x < 1008 && newpos.y > 16 && newpos.y < 752) {
		setPosition(newpos);
	}
}