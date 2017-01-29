#include "stdafx.h"
#include "SFLD.h"
#include "GameState.h"

std::unique_ptr<sf::RenderWindow> SFLD::window_ = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow());

SFLD::SFLD() :stateManager_(this) {
}

void SFLD::start() {
	init();
	runMainLoop();
}

SFLD::~SFLD() {

}

void SFLD::exit() {
	exit_ = true;
}

void SFLD::init() {
	srand((unsigned)time(NULL));
	exit_ = false;
	sf::VideoMode vm(1024, 768);
	window_->create(vm, "Recurse");
	stateManager_.push(new GameState());
}


void SFLD::runMainLoop() {
	sf::Clock clock;
	int previous = clock.getElapsedTime().asMilliseconds();
	int lag = 0;

	while (!exit_) {
		int current = clock.getElapsedTime().asMilliseconds();
		int elapsed = current - previous;
		previous = current;
		lag += elapsed;

		handleSfmlEvents();

		while (lag >= MS_PER_UPDATE && !exit_) {
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}

		render();
	}
}

void SFLD::handleSfmlEvents() {
	sf::Event evt;
	while (window_->pollEvent(evt)) {
		//handle application-wide sfml events...

		//don't allow resize!
		if (evt.type == sf::Event::Resized) {
			window_->setSize(sf::Vector2u(1024, 768));
		}
		bool pressed = false;
		stateManager_.sfmlEvent(evt);
	}
}

void SFLD::update(int frameTime) {
	//application-wide per frame things...
//	SoundManager::update(frameTime);
	stateManager_.update(frameTime);
}

void SFLD::render() {
	if (!exit_) {
		window_->clear(sf::Color::Black);
		//application-wide rendering effects...
		stateManager_.render(window_.get());
		window_->display();
	}
}