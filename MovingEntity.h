#pragma once

#include "Entity.h"

class MovingEntity : public Entity{
public:
	virtual void move(sfld::Vector2f dir, double mag);
};