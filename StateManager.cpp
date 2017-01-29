#include "stdafx.h"
#include "StateManager.h"
#include "BaseState.h"
#include "SFLD.h"

bool StateManager::instantiated_ = false;
StateManager* BaseState::parent_ = NULL;

StateManager::StateManager() {
}

StateManager::StateManager(SFLD* sfld) :sfld_(sfld) {
	assert(!instantiated_ && "StateManager constructor was called when a StateManager already exists! (StateManager should only have once instance)");
	instantiated_ = true;
	popBack_ = false;
	BaseState::parent_ = this;
}

void StateManager::push(BaseState* state) {
	std::unique_ptr<BaseState> smartState;
	smartState.reset(state);

	if (stateStack_.empty()) {
		stateStack_.push_back(std::move(smartState));
		stateStack_.back()->start();
	}
	else {
		pushStack_.push_back(std::move(smartState));
	}
}

void StateManager::pop() {
	//todo: if multiple pop backs in one frame, log warning
	//for now, just cout!
	if (popBack_) {
		std::cout << "WARNING: Attempted to pop back of StateManager more than once in a single frame." << std::endl;
	}
	popBack_ = true;
}

void StateManager::update(int frameTime) {
	stateStack_.back()->update(frameTime);

	stateVector::iterator it;
	for (it = pushStack_.begin(); it != pushStack_.end();) {
		stateStack_.back()->pause();
		stateStack_.push_back(std::move(*it));
		stateStack_.back()->start();
		it = pushStack_.erase(it);
	}

	if (popBack_) {
		popBack_ = false;
		stateStack_.back()->exit();
		stateStack_.pop_back();
		if (!stateStack_.empty()) {
			stateStack_.back()->resume();
		}
		else {
			sfld_->exit();
		}
	}
}

void StateManager::sfmlEvent(const sf::Event& evt) {
	stateStack_.back()->sfmlEvent(evt);
}

void StateManager::render(sf::RenderTarget* target) {
	stateStack_.back()->render(target);
}