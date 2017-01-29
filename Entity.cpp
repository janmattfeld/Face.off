#include "stdafx.h"
#include "Entity.h"

bool Entity::isDestroyed() const {
	return destroyed_;
}

sfld::Vector2f Entity::getPosition() const {
	return position_;
}

sf::Sprite* Entity::getSprite(){
	return &sprite_;
}

EntityManager* Entity::getEntityManager() {
	return entity_manager_;
}

void Entity::render(sf::RenderTarget* target) {
	target->draw(sprite_);
}

void Entity::setPosition(sfld::Vector2f position) {
	position_ = position;
	sprite_.setPosition(position);
}

void Entity::centreOrigin() {
	sprite_.setOrigin(
		sprite_.getLocalBounds().width / 2.f,
		sprite_.getLocalBounds().height / 2.f
	);
}

void Entity::entityConstructor(
	EntityManager* entity_manager,
	ResourceManager<sf::Texture, std::string>* tex_manager,
	std::string tex_name,
	maths::Shape shape,
	sfld::Vector2f position
) { 
	entity_manager_ = entity_manager;
	shape_ = shape;
	tex_manager_ = tex_manager;
	sprite_.setTexture(tex_manager->get(tex_name));
	centreOrigin();
	setPosition(position);
}

maths::Shape Entity::getShape() const {
	return shape_;
}

void Entity::destroy() {
	destroyed_ = true;
}