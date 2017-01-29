#include "stdafx.h"
#include "Particle.h"

Particle::Particle(const std::string& nam, const sf::Vector2f& pos, double lt,
	const sf::Color& colour, float radius, const sf::Vector2f& dir, float sp)
	:last_time(lt), name(nam), direction(dir), speed(sp), livecounter(0), to_destroy(false), mtype(none) {
	init_object(nam, pos, colour, radius);
}

Particle::~Particle() {
	shape.reset();
}


void Particle::setPosition(const sf::Vector2f& pos) {
	position = pos;
	shape->setPosition(position);
}

sf::Vector2f Particle::getPosition() const {
	return position;
}

std::string Particle::getName() const {
	return name;
}

std::shared_ptr<sf::Shape> Particle::getShape() const {
	return shape;
}

void Particle::draw(sf::RenderTarget* texture) {
	texture->draw(*getShape());
}

void Particle::update(double frameTime) {
	livecounter += frameTime;
	sf::Vector2f velocity = direction*speed*(float)frameTime;
	setPosition(getPosition() + velocity);
	if (livecounter > last_time) {
		to_destroy = true;
	}
}

void Particle::init_object(const std::string& nam, const sf::Vector2f& pos, const sf::Color& colour,
	float radius) {
	shape = std::shared_ptr<sf::Shape>(new sf::RectangleShape(sf::Vector2f(radius, radius)));
	shape->setFillColor(colour);
	shape->setOrigin(radius / 2, radius / 2);
	setPosition(pos);
}