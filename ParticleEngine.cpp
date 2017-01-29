#include "stdafx.h"
#include "ParticleEngine.h"
#include "Particle.h"
#include "maths.h"

ParticleEngine::ParticleEngine() :particlecounter(0), staticcounter(0) {
}

ParticleEngine::~ParticleEngine() {
	particles.clear();
}

void ParticleEngine::clear() {
	particlecounter = 0;
	staticcounter = 0;
	particles.clear();
	statics.clear();
}

void ParticleEngine::update(double frameTime) {
	std::map<std::string, std::shared_ptr<Particle>>::iterator it;
	for (it = particles.begin(); it != particles.end();) {
		if (!it->second->to_destroy) {
			it->second->update(frameTime);
			it++;
		}
		else {
			if (it->second->mtype == Particle::blood) {
				statics[it->second->getName()] = it->second;
			}
			it = particles.erase(it);
			if (it == particles.end()) {
				break;
			}
		}
	}
}

std::shared_ptr<Particle> ParticleEngine::generateParticle(const sf::Vector2f& pos, double last_time, const sf::Color& colour,
	float radius, const sf::Vector2f& direction, float speed) {
	std::shared_ptr<Particle> particle;
	std::string staticname = "particle" + std::to_string((long long)particlecounter);
	particle = std::shared_ptr<Particle>(new Particle(staticname, pos, last_time, colour, radius, direction, speed));
	particles[staticname] = particle;
	particlecounter++;
	return particle;
}

std::shared_ptr<Particle> ParticleEngine::generateStatic(const sf::Vector2f& pos, const sf::Color& colour, float radius) {
	std::shared_ptr<Particle> particle;
	std::string staticname = "static_particle" + std::to_string((long long)staticcounter);
	particle = std::shared_ptr<Particle>(new Particle(staticname, pos, 0, colour, radius, sf::Vector2f(0, 0), 0));
	statics[staticname] = particle;
	staticcounter++;
	return particle;
}

void ParticleEngine::generateBloodEffect(const sf::Vector2f& position) {
	//generate static particles to remain
	for (int i = 1; i <= 40; i++) {
		float radius = (float)(rand() % 4 + 1);
		sf::Color colour(rand() % 50 + 150, 0, 0);
		sf::Vector2f pos = sf::Vector2f((float)(rand() % 50 - 25), (float)(rand() % 40 - 25)) + position;
		generateStatic(pos, colour, radius);
	}
	for (float x = -1; x <= 1;) {
		for (float y = -1; y <= 1;) {
			float radius = (float)(rand() % 5 + 3);
			sf::Color colour(rand() % 50 + 150, 0, 0);
			sf::Vector2f pos = sf::Vector2f((float)(rand() % 50 - 25), (float)(rand() % 40 - 25)) + position;
			sf::Vector2f direction = sfld::Vector2f(x, y).normalise();
			float r = (float)(rand() % 4 + 1) / 10.0f;
			std::shared_ptr<Particle> particle = generateParticle(pos, rand() % 250 + 50, colour, radius, direction, r);
			particle->mtype = Particle::blood;
			y += 0.2f;
		}
		x += 0.2f;
	}
	/*for(float x=0;x>=1;){
	for(float y= 1;y <= 0;){
	float radius = 1;
	sf::Color colour(rand() % 50 + 150,0,0);
	sf::Vector2f pos = sf::Vector2f(rand() % 50 - 25,rand() % 40 - 25) + position;
	sf::Vector2f direction = maths::normalise(sf::Vector2f(x,y));
	generateParticle(pos,1000,colour,radius,direction,0.1);
	y -= 0.1;
	}
	x+=0.1;
	}*/

}

void ParticleEngine::generateMiniExplosionEffect(const sf::Vector2f& position) {
	for (float x = -0.3f; x <= 0.3f;) {
		for (float y = -0.3f; y <= 0.3f;) {
			float radius = (float)(rand() % 5 + 5);
			sf::Color colour(255, rand() % 150 + 50, rand() % 50);
			sf::Vector2f pos = sf::Vector2f((float)(rand() % 20 - 10), (float)(rand() % 20 - 10)) + position;
			sf::Vector2f direction = sfld::Vector2f(x, y).normalise();
			float r = (float)(rand() % 2 + 1) / 10.0f;
			std::shared_ptr<Particle> particle = generateParticle(pos, rand() % 250 + 50, colour, radius, direction, r);
			y += 0.1f;
		}
		x += 0.1f;
	}
}

void ParticleEngine::generateMiniBlueEffect(const sf::Vector2f& position) {
	for (float x = -0.6f; x <= 0.6f;) {
		for (float y = -0.6f; y <= 0.6f;) {
			float radius = (float)(rand() % 5 + 5);
			sf::Color colour(rand() % 150 + 50, rand() % 150 + 50, rand() % 150 + 100);
			sf::Vector2f pos = sf::Vector2f((float)(rand() % 20 - 10), (float)(rand() % 20 - 10)) + position;
			sf::Vector2f direction = sfld::Vector2f(x, y).normalise();
			float r = (float)(rand() % 2 + 1) / 10.0f;
			std::shared_ptr<Particle> particle = generateParticle(pos, rand() % 250 + 50, colour, radius, direction, r);
			y += 0.1f;
		}
		x += 0.1f;
	}
}

void ParticleEngine::generateExplosionEffect(const sf::Vector2f& position) {
	for (float x = -1.0f; x <= 1.0f;) {
		for (float y = -1.0f; y <= 1.0f;) {
			float radius = (float)(rand() % 5 + 5);
			sf::Color colour(255, rand() % 150 + 50, rand() % 50);
			sf::Vector2f pos = sf::Vector2f((float)(rand() % 50 - 25), (float)(rand() % 40 - 25)) + position;
			sf::Vector2f direction = sfld::Vector2f(x, y).normalise();
			float r = (float)(rand() % 4 + 1) / 10.0f;
			std::shared_ptr<Particle> particle = generateParticle(pos, rand() % 250 + 50, colour, radius, direction, r);
			y += 0.1f;
		}
		x += 0.1f;
	}
}

void ParticleEngine::renderParticles(sf::RenderTarget* target) {

	std::map<std::string, std::shared_ptr<Particle>>::iterator it;
	for (it = particles.begin(); it != particles.end(); it++) {
		it->second->draw(target);
	}
}

void ParticleEngine::renderStatics(sf::RenderTarget* target) {

	std::map<std::string, std::shared_ptr<Particle>>::iterator it;
	for (it = statics.begin(); it != statics.end(); it++) {
		it->second->draw(target);
	}
}