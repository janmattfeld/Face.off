#include "stdafx.h"
#include "Player.h"
#include "Controller.h"
#include "Action.h"
#include "ParticleEngine.h"

Player::Player(std::string tex_name, Controller* controller, sfld::Vector2f position,
	EntityManager* entity_manager, ResourceManager<sf::Texture, std::string>* tex_manager,
	ActionListener* listener, ParticleEngine* particle_engine)
	: controller_(controller), speed_(0.4), listener_(listener),
	particle_engine_(particle_engine), health_(100),slowed_(false),
	old_speed_(0.0), slow_duration_(0), slow_timer_(0){
	entityConstructor(
		entity_manager,
		tex_manager,
		tex_name,
		maths::SHAPE_SQUARE,
		position
	);
}

int Player::getHealth() const {
	return health_;
}

ActionPtrList* Player::getActions() {
	return &actions_;
}

void Player::slowDown(double newspeed, int time) {
	old_speed_ = speed_;
	speed_ = newspeed;
	slow_timer_ = 0;
	slow_duration_ = time;
	slowed_ = true;
}

void Player::takeDamage(int damage) {
	health_ -= damage;
	std::cout << "player took" << damage << " damage" << std::endl;
	std::cout << health_ << " health remaining" << std::endl;
	particle_engine_->generateBloodEffect(getPosition());
}

void Player::update(int frame_time) {
	sfld::Vector2f dir = controller_->getDirection();
	move(dir, speed_);

	if (slowed_) {
		slow_timer_ += frame_time;
		if (slow_timer_ > slow_duration_) {
			speed_ = old_speed_;
			slowed_ = false;
		}
	}

	while (!addaction_q_.empty()) {
		actions_.push_back(std::move(addaction_q_.front()));
		addaction_q_.pop();
	}
	for (auto& it = actions_.begin(); it != actions_.end();) {
		if (!(*it)->getRemoved()) {
			it++;
		}
		else {
			it = actions_.erase(it);
		}
	}
}

void Player::inputEmotionData(EmotionData* data, int tick_length) {
	for (auto& it : actions_) {
		it->inputData(data, tick_length);
	}
}

void Player::addAction(Action* action) {
	addaction_q_.push(ActionPtr(action));
}