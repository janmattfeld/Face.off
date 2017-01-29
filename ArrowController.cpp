#include "stdafx.h"
#include "ArrowController.h"

sfld::Vector2f ArrowController::getDirection() const {
	using namespace sf;
	sfld::Vector2f dir(0.0, 0.0);
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		dir.y -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		dir.x -= 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		dir.y += 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		dir.x += 1;
	}
	return dir.normalise();
}