#pragma once

#include "stdafx.h"

class Particle {
public:
	enum type {
		none,
		blood,
	};
	Particle(const std::string& name, const sf::Vector2f& pos, double last_time, const sf::Color& colour,
		float radius, const sf::Vector2f& direction, float speed);
	~Particle();

	void update(double frameTime);
	void draw(sf::RenderTarget* target);

	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition() const;
	std::string getName() const;
	std::shared_ptr<sf::Shape> getShape() const;
	bool to_destroy;
	type mtype;
private:
	double livecounter;
	std::shared_ptr<sf::Shape> shape;
	std::string name;
	sf::Vector2f position;
	void init_object(const std::string& name, const sf::Vector2f& pos, const sf::Color& colour, float radius);
	double last_time;
	sf::Vector2f direction;
	float speed;
};