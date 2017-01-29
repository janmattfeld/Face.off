#pragma once

#include "stdafx.h"

class BaseState;
class SFLD;

typedef std::vector<std::unique_ptr<BaseState>> stateVector;

class StateManager : public sf::NonCopyable {
public:
	StateManager();
	explicit StateManager(SFLD* sfld);
	void push(BaseState* state);
	void pop();
	void update(int frameTime);
	void render(sf::RenderTarget* target);
	void sfmlEvent(const sf::Event& evt);
private:
	SFLD* sfld_;
	stateVector stateStack_;
	stateVector pushStack_;
	bool popBack_;

	static bool instantiated_;
};