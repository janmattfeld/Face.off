#pragma once

#include "stdafx.h"

class StateManager;

class BaseState : public sf::NonCopyable {
	friend StateManager;
public:
	virtual void sfmlEvent(sf::Event evt) = 0;

	virtual void start() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
	virtual void exit() = 0;

	virtual void update(int frameTime) = 0;
	virtual void render(sf::RenderTarget* target) = 0;

	StateManager& getParent() const { return *parent_; }
private:
	static StateManager* parent_;
};