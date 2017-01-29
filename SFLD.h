#pragma once

#include "stdafx.h"
#include "StateManager.h"

class SFLD : public sf::NonCopyable {
public:
	SFLD();
	~SFLD();

	void start();
	void exit();
	static std::unique_ptr<sf::RenderWindow> window_;
private:
	void init();
	void runMainLoop();
	void handleSfmlEvents();
	void update(int frameTime);
	void render();

	static const int MS_PER_UPDATE = 1;

	StateManager stateManager_;
	bool exit_;

};