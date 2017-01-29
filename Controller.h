#pragma once

#include "Vector2.h"

class Controller {
public:
	virtual sfld::Vector2f getDirection() const = 0;
	//and the rest...
};
