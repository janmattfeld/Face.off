#pragma once

#include "Controller.h"

class WasdController : public Controller{
public:
	sfld::Vector2f getDirection() const;
};
