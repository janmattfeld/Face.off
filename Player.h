#pragma once

#include "MovingEntity.h"
#include <queue>

class Controller;
class ActionListener;
class Action;
class EmotionData;
class ParticleEngine;

typedef std::unique_ptr<Action> ActionPtr;
typedef std::vector<ActionPtr> ActionPtrList;
typedef std::queue<ActionPtr> ActionPtrQueue;

class Player : public MovingEntity {
public:
	Player(std::string tex_name, Controller* controller, sfld::Vector2f position,
		EntityManager* entity_manager, ResourceManager<sf::Texture, std::string>* tex_manager,
		ActionListener* listener, ParticleEngine* particle_engine);
	//TODO: more attributes to distinguish between players

	void addAction(Action* action);
	void update(int frame_time);
	void inputEmotionData(EmotionData* data, int tick_length);
	void slowDown(double newspeed, int time);
	void takeDamage(int damage);
	int getHealth() const;

	ActionPtrList* getActions();
private:
	ActionPtrQueue addaction_q_;
	ActionPtrList actions_;
	
	bool slowed_;
	double old_speed_;
	int slow_duration_;
	int slow_timer_;
	
	double speed_;
	int health_;
	Controller* controller_;
	ActionListener* listener_;
	ParticleEngine* particle_engine_;
};