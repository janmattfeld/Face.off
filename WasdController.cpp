#include "stdafx.h"
#include "WasdController.h"

sfld::Vector2f WasdController::getDirection() const{
	using namespace sf;
	sfld::Vector2f dir(0.0, 0.0);
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		dir.y -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		dir.x -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		dir.y += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		dir.x += 1;
	}
	return dir.normalise();
}