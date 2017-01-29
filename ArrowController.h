#pragma once

#include "Controller.h"

class ArrowController : public Controller {
public:
	sfld::Vector2f getDirection() const;
};
