#pragma once

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "ResourceManager.h"

class EntityManager;

class Entity {
public:
	virtual void update(int frame_time) = 0;
	virtual void render(sf::RenderTarget* target);

	bool isDestroyed() const;

	void setPosition(sfld::Vector2f position);
	sfld::Vector2f getPosition() const;
	maths::Shape getShape() const;
	sf::Sprite* getSprite();

	void destroy();
protected:
	void centreOrigin();

	virtual void entityConstructor(
		EntityManager* entity_manager,
		ResourceManager<sf::Texture, std::string>* tex_manager_,
		std::string tex_name,
		maths::Shape shape,
		sfld::Vector2f position
	);

	EntityManager* getEntityManager();

private:
	bool destroyed_;

	maths::Shape shape_;
	sf::Sprite sprite_;
	sfld::Vector2f position_;
	EntityManager* entity_manager_;
	ResourceManager<sf::Texture, std::string>* tex_manager_;
};
