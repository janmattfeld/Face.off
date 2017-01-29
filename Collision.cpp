#include "stdafx.h"
#include "Collision.h"
#include "Projection.h"
#include "maths.h"

MTV MTV::NONE = MTV(0, sfld::Vector2f(0, 0));
const float Collision::SAT_MAX_BOUND = 50.0f;

Collision::~Collision() {
}

sfld::Vector2f Collision::rotatePoint(const sfld::Vector2f& point, float angle) {
	angle = maths::toRadians(-angle);
	sfld::Vector2f rotated_point;
	rotated_point.x = point.x * cos(angle) + point.y * sin(angle);
	rotated_point.y = -point.x * sin(angle) + point.y * cos(angle);
	return rotated_point;
}

sfld::Vector2f Collision::rotatePoint(const sfld::Vector2f& point, const sfld::Vector2f& origin, float angle) {
	angle = maths::toRadians(-angle);
	sfld::Vector2f dif = point - origin;
	sfld::Vector2f rotated_point;
	rotated_point.x = dif.x * cos(angle) + dif.y * sin(angle);
	rotated_point.y = -dif.x * sin(angle) + dif.y * cos(angle);
	return rotated_point;
}

float Collision::minValue(float a, float b, float c, float d) {
	float min = a;
	min = (b < min ? b : min);
	min = (c < min ? c : min);
	min = (d < min ? d : min);
	return min;
}

float Collision::maxValue(float a, float b, float c, float d) {
	float max = a;
	max = (b > max ? b : max);
	max = (c > max ? c : max);
	max = (c > max ? c : max);
	return max;
}


MTV Collision::getCollision(const sf::Sprite& object1, maths::Shape shape1, const sf::Sprite& object2, maths::Shape shape2) {

	OBB obb1 = getOBB(object1);
	OBB obb2 = getOBB(object2);
	float rot = object1.getRotation();
	//SAT

	double overlap = LONG_MAX;
	sfld::Vector2f smallest(0, 0);

	std::vector<sfld::Vector2f> axis1;
	std::vector<sfld::Vector2f> axis2;

	sfld::Vector2f circleCentre1;
	sfld::Vector2f circleCentre2;
	//get axis to check with SAT
	//as we are using rectangles and do not need to check parallels, only have 2 axis for each rectangle

	if (shape1 == maths::SHAPE_CIRCLE && shape2 == maths::SHAPE_CIRCLE) {
		circleCentre1 = sfld::Vector2f(object1.getGlobalBounds().left + object1.getGlobalBounds().width / 2, object1.getGlobalBounds().top + object1.getGlobalBounds().height / 2);
		circleCentre2 = sfld::Vector2f(object2.getGlobalBounds().left + object2.getGlobalBounds().width / 2, object2.getGlobalBounds().top + object2.getGlobalBounds().height / 2);
		axis1.push_back(sfld::Vector2f(circleCentre1 - circleCentre2).normalise());
	}
	else if (shape1 != shape2) {
		sfld::Vector2f circleCentre;
		sf::FloatRect squareRect;
		float rotation;
		if (shape1 == maths::SHAPE_CIRCLE) {
			circleCentre = sfld::Vector2f(object1.getGlobalBounds().left + object1.getGlobalBounds().width / 2, object1.getGlobalBounds().top + object1.getGlobalBounds().height / 2);
			circleCentre1 = circleCentre;
			squareRect = getOriginalBoundingBox(object2);
			rotation = object2.getRotation();
		}
		else if (shape2 == maths::SHAPE_CIRCLE) {
			circleCentre = sfld::Vector2f(object2.getGlobalBounds().left + object2.getGlobalBounds().width / 2, object2.getGlobalBounds().top + object2.getGlobalBounds().height / 2);
			circleCentre2 = circleCentre;
			squareRect = getOriginalBoundingBox(object1);
			rotation = object1.getRotation();
		}
		sfld::Vector2f squareCentre(squareRect.left + squareRect.width / 2, squareRect.top + squareRect.height / 2);
		OBB* square = (shape1 == maths::SHAPE_SQUARE ? &obb1 : &obb2);
		sfld::Vector2f relativeCircleCentre = rotatePoint(circleCentre, squareCentre, -rotation);
		bool vertice = false;
		sfld::Vector2f axis;

		sfld::Vector2f topLeft(squareRect.left, squareRect.top);
		sfld::Vector2f topRight(squareRect.left + squareRect.width, squareRect.top);
		sfld::Vector2f botLeft(squareRect.left, squareRect.top + squareRect.height);
		sfld::Vector2f botRight(squareRect.left + squareRect.width, squareRect.top + squareRect.height);

		//get axis to check
		if (circleCentre.x < topLeft.x) {
			if (circleCentre.y < topLeft.y) {
				vertice = true;
				axis = topLeft;
			}
			else if (circleCentre.y >  botLeft.y) {
				vertice = true;
				axis = botLeft;
			}
			else {
				axis = sfld::Vector2f(topLeft - botLeft).normalise();
			}
		}
		else if (circleCentre.x > topRight.x) {
			if (circleCentre.y < topLeft.y) {
				vertice = true;
				axis = topRight;
			}
			else if (circleCentre.y >  botLeft.y) {
				vertice = true;
				axis = botRight;
			}
			else {
				axis = sfld::Vector2f(topRight - botRight).normalise();
			}
		}
		else {
			if (circleCentre.y < topLeft.y) {
				axis = sfld::Vector2f(topRight - topLeft).normalise();
			}
			else if (circleCentre.y >  botLeft.y) {
				axis = sfld::Vector2f(botLeft - botRight).normalise();
			}
			else {
				//contains point!
			}
		}

		if (vertice) {
			axis1.push_back(sfld::Vector2f(circleCentre - axis).normalise());
		}
		else {
			axis1.push_back(sfld::Vector2f(topRight - topLeft).normalise());
			axis1.push_back(sfld::Vector2f(topRight - botRight).normalise());
		}


		/*
		//get closest vertex on square to centre of circle
		sfld::Vector2f closest = square->bot_left;
		float distance = maths::getLength(closest - circleCentre);

		float newdistance = maths::getLength(square->bot_right - closest);
		if(newdistance < distance){
		distance = newdistance;
		closest = square->bot_right;
		}

		newdistance = maths::getLength(square->top_left - closest);
		if(newdistance < distance){
		distance = newdistance;
		closest = square->top_left;
		}

		newdistance = maths::getLength(square->top_right - closest);
		if(newdistance < distance){
		distance = newdistance;
		closest = square->top_right;
		}

		axis1.push_back(maths::normalise(circleCentre - closest));*/
	}
	else {
		//get side vectors
		sfld::Vector2f Xside1(obb1.bot_left - obb1.bot_right);
		sfld::Vector2f Yside1(obb1.top_left - obb1.bot_left);
		sfld::Vector2f Xside2(obb2.bot_left - obb2.bot_right);
		sfld::Vector2f Yside2(obb2.top_left - obb2.bot_left);

		//get normalised normal (normal is perpendicular, perp function normalises for greater accuracy)
		//and add them into axis list
		axis1.push_back(Xside1.perpendicular());
		axis1.push_back(Yside1.perpendicular());
		axis2.push_back(Xside2.perpendicular());
		axis2.push_back(Yside2.perpendicular());
	}

	for (unsigned int i = 0; i<axis1.size(); i++) {
		sfld::Vector2f axis = axis1[i];
		Projection projection1 = project(obb1, axis);
		if (shape1 == maths::SHAPE_CIRCLE) {
			float radius = object1.getGlobalBounds().width / 2;
			projection1 = projectCircle(circleCentre1, radius, axis);
		}
		Projection projection2 = project(obb2, axis);
		if (shape2 == maths::SHAPE_CIRCLE) {
			float radius = object2.getGlobalBounds().width / 2;
			projection2 = projectCircle(circleCentre2, radius, axis);
		}

		if (!projection1.overlap(projection2)) { //we can be sure it is not colliding
			return MTV::NONE;
		}
		else {
			double o = projection1.getOverlap(projection2);
			if (o < overlap) {
				overlap = o;
				smallest = axis;
			}
		}
	}

	for (unsigned int i = 0; i<axis2.size(); i++) {
		sfld::Vector2f axis = axis2[i];
		Projection projection1 = project(obb1, axis);
		if (shape1 == maths::SHAPE_CIRCLE) {
			float radius = object1.getGlobalBounds().width / 2;
			projection1 = projectCircle(circleCentre1, radius, axis);
		}
		Projection projection2 = project(obb2, axis);
		if (shape2 == maths::SHAPE_CIRCLE) {
			float radius = object2.getGlobalBounds().width / 2;
			projection2 = projectCircle(circleCentre2, radius, axis);
		}

		if (!projection1.overlap(projection2)) {
			return MTV::NONE;
		}
		else {
			double o = projection1.getOverlap(projection2);
			if (o < overlap) {
				overlap = o;
				smallest = axis;
			}
		}
	}
	sf::FloatRect bounds1 = object1.getGlobalBounds();
	sf::FloatRect bounds2 = object2.getGlobalBounds();
	sfld::Vector2f c1 = sfld::Vector2f(bounds1.left + bounds1.width / 2, bounds1.top + bounds1.height / 2);
	sfld::Vector2f c2 = sfld::Vector2f(bounds2.left + bounds2.width / 2, bounds2.top + bounds2.height / 2);
	sfld::Vector2f c1c2 = c1 - c2;
	if (c1c2.dot(smallest) < 0) {
		smallest = -smallest;
	}
	MTV mtv(overlap, smallest);
	return mtv;
}

Projection Collision::project(const OBB& box, const sfld::Vector2f& axis) {
	std::vector<sfld::Vector2f> vertices;
	vertices.push_back(box.top_left); vertices.push_back(box.top_right);
	vertices.push_back(box.bot_left); vertices.push_back(box.bot_right);

	double min = vertices[0].dot(axis);
	double max = min;
	for (unsigned int i = 1; i < vertices.size(); i++) {
		double p = vertices[i].dot(axis);
		if (p < min) {
			min = p;
		}
		else if (p > max) {
			max = p;
		}
	}
	return Projection(min, max);
}

Projection Collision::projectCircle(const sfld::Vector2f& centre, float radius, const sfld::Vector2f& axis) {
	double p = centre.dot(axis);
	double min = p - radius;
	double max = p + radius;

	return Projection(min, max);
}

Collision::OBB Collision::getOBB(const sf::Sprite& object) {
	sf::FloatRect box(object.getLocalBounds());
	sfld::Vector2f TL, BR, TR, BL;
	sfld::Vector2f norotTL, norotBR, norotTR, norotBL;
	float rot = object.getRotation();
	norotTL = object.getPosition() - object.getOrigin() + sfld::Vector2f(box.left, box.top);
	norotBR = object.getPosition() - object.getOrigin() + sfld::Vector2f(box.left + box.width, box.top + box.height);
	norotTR = object.getPosition() - object.getOrigin() + sfld::Vector2f(box.left + box.width, box.top);
	norotBL = object.getPosition() - object.getOrigin() + sfld::Vector2f(box.left, box.top + box.height);

	TL = object.getPosition() + rotatePoint(sfld::Vector2f(box.left, box.top), object.getOrigin(), object.getRotation());
	BR = object.getPosition() + rotatePoint(sfld::Vector2f(box.left + box.width, box.top + box.height), object.getOrigin(), object.getRotation());
	TR = object.getPosition() + rotatePoint(sfld::Vector2f(box.left + box.width, box.top), object.getOrigin(), object.getRotation());
	BL = object.getPosition() + rotatePoint(sfld::Vector2f(box.left, box.top + box.height), object.getOrigin(), object.getRotation());

	OBB obb(TL, BL, TR, BR);

	return obb;
}

sf::FloatRect Collision::getOriginalBoundingBox(const sf::Sprite& object) {
	sf::FloatRect rect = object.getLocalBounds();
	sfld::Vector2f tl = object.getPosition() - object.getOrigin() + sfld::Vector2f(rect.left, rect.top);
	return sf::FloatRect(tl.x, tl.y, rect.width, rect.height);
}