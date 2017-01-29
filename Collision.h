#pragma once

#include "stdafx.h"

struct MTV {
	MTV(double overl, sfld::Vector2f axe) :overlap(overl), axis(axe) {}
	double overlap;
	sfld::Vector2f axis;
	static MTV NONE;
};

class Projection;

class Collision {
public:
	~Collision();
	static sfld::Vector2f rotatePoint(const sfld::Vector2f& point, float angle);
	static sfld::Vector2f rotatePoint(const sfld::Vector2f& point, const sfld::Vector2f& origin, float angle);
	static float minValue(float a, float b, float c, float d);
	static float maxValue(float a, float b, float c, float d);
	static sf::FloatRect getOriginalBoundingBox(const sf::Sprite& sprite);
	static const float SAT_MAX_BOUND;
	struct OBB {
		OBB(const sfld::Vector2f& tl, const sfld::Vector2f& bl, const sfld::Vector2f& tr,
			const sfld::Vector2f& br) :top_left(tl), bot_left(bl), top_right(tr), bot_right(br) {
		}
		sfld::Vector2f top_left;
		sfld::Vector2f bot_left;
		sfld::Vector2f top_right;
		sfld::Vector2f bot_right;
	};

	static MTV getCollision(const sf::Sprite& object1, maths::Shape shape1, const sf::Sprite& object2, maths::Shape shape2);
	static OBB getOBB(const sf::Sprite& object);
	static Projection project(const OBB& box, const sfld::Vector2f& vec);
	static Projection projectCircle(const sfld::Vector2f& centre, float radius, const sfld::Vector2f& axis);
private:
	Collision() {}

};