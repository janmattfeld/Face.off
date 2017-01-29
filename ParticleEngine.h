#pragma once

#include "stdafx.h"

class Particle;

class ParticleEngine {
public:
	ParticleEngine();
	~ParticleEngine();

	void update(double frameTime);
	void renderParticles(sf::RenderTarget* target);
	void renderStatics(sf::RenderTarget* target);

	void clear();

	std::shared_ptr<Particle> generateParticle(const sf::Vector2f& pos, double last_time, const sf::Color& colour,
		float radius, const sf::Vector2f& direction, float speed);
	std::shared_ptr<Particle> generateStatic(const sf::Vector2f& pos, const sf::Color& colour, float radius);

	void generateBloodEffect(const sf::Vector2f& position);
	void generateExplosionEffect(const sf::Vector2f& position);
	void generateMiniExplosionEffect(const sf::Vector2f& position);
	void generateMiniBlueEffect(const sf::Vector2f& position);



	std::map<std::string, std::shared_ptr<Particle>> getParticles();
	std::map<std::string, std::shared_ptr<Particle>> getStatics();
private:
	int staticcounter;
	int particlecounter;
	std::map<std::string, std::shared_ptr<Particle>> particles;
	std::map<std::string, std::shared_ptr<Particle>> statics;
};