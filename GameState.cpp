#pragma once
#include "stdafx.h"
#include "GameState.h"
#include "ArrowController.h"
#include "WasdController.h"
#include "EntityManager.h"
#include "Player.h"
#include "ActionListener.h"
#include "Action.h"
#include "AngerFunction.h"
#include "EmotionData.h"
#include "DefenceFunction.h"
#include <sstream>
#include "ParticleEngine.h"
#include <string>
#include "SadFunction.h"
#include "SurprisedFunction.h"
#include "AttackBox.h"
#include "DefenceBox.h"

GameState::GameState() = default;
GameState::~GameState() = default;

void GameState::start() {
	srand(time(NULL));
	using namespace utility;                    // Common utilities like string conversions
	using namespace web;                        // Common features like URIs.
	using namespace web::http;                  // Common HTTP functionality
	using namespace web::http::client;          // HTTP client features
	using namespace concurrency::streams;       // Asynchronous streams
	using namespace web::json;

	http_client_ = std::unique_ptr<http_client>(new http_client(U("http://127.0.0.1:3000/")));
	builder_ = uri_builder(U("/"));
	http_response_ = http_client_->request(methods::GET, builder_.to_string()).then([=](http_response response) {
		auto response_str = utility::conversions::to_utf8string((response.extract_string().get()));
		sendEmotionData(response_str);
		return 0;
	});

	particle_engine_ = std::unique_ptr<ParticleEngine>(new ParticleEngine());

	timer_ = 0;
	entity_manager_ = std::unique_ptr<EntityManager>(new EntityManager());

	loadTextures();

	arrow_controller_ = std::unique_ptr<ArrowController>(new ArrowController());
	wasd_controller_ = std::unique_ptr<WasdController>(new WasdController());

	listener_ = std::unique_ptr<ActionListener>(new ActionListener(entity_manager_.get()));

	player1_ = new Player("player1", wasd_controller_.get(),
		sfld::Vector2f(30, 300), entity_manager_.get(), &tex_manager_,listener_.get(),
		particle_engine_.get());

	player2_ = new Player("player2", arrow_controller_.get(),
		sfld::Vector2f(984, 300), entity_manager_.get(), &tex_manager_, listener_.get(),
		particle_engine_.get());

	ActionFunction* anger_function1 = new AngerFunction(player2_, particle_engine_.get(), 
		entity_manager_.get());
	ActionFunction* defence_function1 = new DefenceFunction();

	ActionFunction* anger_function2 = new AngerFunction(player1_, particle_engine_.get(),
		entity_manager_.get());
	ActionFunction* defence_function2 = new DefenceFunction();

	Action* anger_action1 = new Action(listener_.get(), Action::CATEGORY_ATTACK, Action::EMOTION_ANGER,
		Action::EMOTION_HAPPINESS,anger_function1);

	Action* happy_defence1 = new Action(listener_.get(), Action::CATEGORY_DEFENCE, Action::EMOTION_HAPPINESS,
		Action::EMOTION_HAPPINESS, defence_function1);

	Action* anger_action2 = new Action(listener_.get(), Action::CATEGORY_ATTACK, Action::EMOTION_ANGER,
		Action::EMOTION_HAPPINESS, anger_function2);

	Action* happy_defence2 = new Action(listener_.get(), Action::CATEGORY_DEFENCE, Action::EMOTION_HAPPINESS,
		Action::EMOTION_HAPPINESS, defence_function2);

	player1_->addAction(anger_action1);
	player1_->addAction(happy_defence1);
	player2_->addAction(anger_action2);
	player2_->addAction(happy_defence2);

	entity_manager_->add(player1_);
	entity_manager_->add(player2_);

	p1_ahead.setFont(*entity_manager_->getFont());
	p1_dhead.setFont(*entity_manager_->getFont());
	p1_ahead.setString("Attacks:");
	p1_dhead.setString("Defences:");
	p1_ahead.setPosition(0, 0);
	p1_dhead.setPosition(150, 0);
	p1_ahead.setCharacterSize(24);
	p1_dhead.setCharacterSize(24);

	p2_ahead.setFont(*entity_manager_->getFont());
	p2_dhead.setFont(*entity_manager_->getFont());
	p2_ahead.setString("Attacks:");
	p2_dhead.setString("Defences:");
	p2_ahead.setPosition(512, 0);
	p2_dhead.setPosition(662, 0);
	p2_ahead.setCharacterSize(24);
	p2_dhead.setCharacterSize(24);

	health1.setFont(*entity_manager_->getFont());
	health1.setPosition(10, 700);
	health1.setString("Health");

	health2.setFont(*entity_manager_->getFont());
	health2.setPosition(800, 700);
	health2.setString("Health");

	box_delay_ = rand() % 5000 + 5000;
	box_timer_ = 0;
}

void GameState::exit() {

}

void GameState::resume() {

}

void GameState::pause() {

}

void GameState::sfmlEvent(sf::Event evt) {

}

void GameState::readEmotionData() {
	using namespace sf;
	//temporary
	/*EmotionData data1(
		Keyboard::isKeyPressed(Keyboard::Num1) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Num2) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Num3) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Num4) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Num5) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Num6) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Num7) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Num8) ? 1.f : 0.f
	);

	EmotionData data2(
		Keyboard::isKeyPressed(Keyboard::Numpad1) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Numpad2) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Numpad3) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Numpad4) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Numpad5) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Numpad6) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Numpad7) ? 1.f : 0.f,
		Keyboard::isKeyPressed(Keyboard::Numpad8) ? 1.f : 0.f
	);

	player1_->inputEmotionData(&data1, tick_time);
	player2_->inputEmotionData(&data2, tick_time);*/

	using namespace utility;                    // Common utilities like string conversions
	using namespace web;                        // Common features like URIs.
	using namespace web::http;                  // Common HTTP functionality
	using namespace web::http::client;          // HTTP client features
	using namespace concurrency::streams;       // Asynchronous streams
	using namespace web::json;

	if (http_response_.is_done()) {
		http_response_ = http_client_->request(methods::GET, builder_.to_string()).then([=](http_response response) {
			auto response_str = utility::conversions::to_utf8string((response.extract_string().get()));
			sendEmotionData(response_str);
			timer_ = 0;
			return 0;
		});
	}
}

void GameState::sendEmotionData(std::string data) {
	using namespace std;
	std::cout << "DATA SENT: " << data << endl;
	vector<pair<int, EmotionData>> datas;
	istringstream iss(data);
	string word;
	Action::EMOTION next;
	bool wordnext = true;
	bool left = false;
	while (iss >> word) {
		if(wordnext){
			if (word == "left") {
				left = true;
			}
			else if (word == "anger") {
				next = Action::EMOTION_ANGER;
			}
			else if (word == "contempt") {
				next = Action::EMOTION_CONTEMPT;
			}
			else if (word == "disgust") {
				next = Action::EMOTION_DISGUST;
			}
			else if (word == "fear") {
				next = Action::EMOTION_FEAR;
			}
			else if (word == "happiness") {
				next = Action::EMOTION_HAPPINESS;
			}
			else if (word == "neutral") {
				next = Action::EMOTION_NEUTRAL;
			}
			else if (word == "sadness") {
				next = Action::EMOTION_SADNESS;
			}
			else if (word == "surprise") {
				next = Action::EMOTION_SURPRISE;
			}
			wordnext = false;
		}
		else {
			if (left) {
				datas.push_back(make_pair(stoi(word), EmotionData()));
				left = false;
			}
			else{
				datas.back().second.setData(next, stof(word));
			}
			wordnext = true;
		}
	}
	if (datas.size() >= 2) {
		if (datas[0].first > datas[1].first) {
			player1_->inputEmotionData(&datas[0].second, timer_);
			player2_->inputEmotionData(&datas[1].second, timer_);
		}
		else {
			player1_->inputEmotionData(&datas[1].second, timer_);
			player2_->inputEmotionData(&datas[0].second, timer_);
		}
	}
	else if(datas.size() == 1){
		using namespace sf;
		//only for testing
		player1_->inputEmotionData(&datas[0].second, timer_);
		EmotionData data2(
			Keyboard::isKeyPressed(Keyboard::Numpad1) ? 1.f : 0.f,
			Keyboard::isKeyPressed(Keyboard::Numpad2) ? 1.f : 0.f,
			Keyboard::isKeyPressed(Keyboard::Numpad3) ? 1.f : 0.f,
			Keyboard::isKeyPressed(Keyboard::Numpad4) ? 1.f : 0.f,
			Keyboard::isKeyPressed(Keyboard::Numpad5) ? 1.f : 0.f,
			Keyboard::isKeyPressed(Keyboard::Numpad6) ? 1.f : 0.f,
			Keyboard::isKeyPressed(Keyboard::Numpad7) ? 1.f : 0.f,
			Keyboard::isKeyPressed(Keyboard::Numpad8) ? 1.f : 0.f
		);
		player2_->inputEmotionData(&data2, timer_);
	}
}

void GameState::update(int frame_time) {
	entity_manager_->update(frame_time);
	particle_engine_->update(frame_time);

	health1.setString("Health: " + std::to_string(player1_->getHealth()));
	health2.setString("Health: " + std::to_string(player2_->getHealth()));

	timer_ += frame_time;
	box_timer_ += frame_time;
	readEmotionData();

	if (box_timer_ >= box_delay_) {
		box_timer_ = 0;
		int x = rand() % 800 + 100;
		int y = rand() & 400 + 100;
		int n = rand() % 2;
		if (n == 0) {
			entity_manager_->add(new AttackBox(
				player1_,
				player2_,
				sfld::Vector2f((float)x, (float)y),
				entity_manager_.get(),
				&tex_manager_,
				particle_engine_.get(),
				listener_.get()
			));
		}
		else if (n == 1) {
			entity_manager_->add(new DefenceBox(
				player1_,
				player2_,
				sfld::Vector2f((float)x, (float)y),
				entity_manager_.get(),
				&tex_manager_,
				particle_engine_.get(),
				listener_.get()
			));
		}
	}

	listener_->update(frame_time);

	ActionPtrList* actions1 = player1_->getActions();
	ActionPtrList* actions2 = player2_->getActions();


	p1_attacks.clear();
	p1_defences.clear();

	p2_attacks.clear();
	p2_defences.clear();
	for (auto& it : *actions1) {
		std::string name = Action::enumToString(it->getEmotion());
		sf::Text tex;
		tex.setFont(*entity_manager_->getFont());
		tex.setCharacterSize(16);
		if (it->getCategory() == Action::CATEGORY_ATTACK) {
			tex.setString(name);
			tex.setPosition(0, 30 + 20 * p1_attacks.size());
			p1_attacks.push_back(tex);
		}else if (it->getCategory() == Action::CATEGORY_DEFENCE) {
			std::string counter = "";
			for (auto& it2 : *actions2) {
				if (it2->getCategory() == Action::CATEGORY_ATTACK && it2->getCounterEmotion() == it->getEmotion()) {
					counter = Action::enumToString(it2->getEmotion());
				}
			}
			if (counter != "") {
				std::string s = "Counter " + counter + " with " + name;
				tex.setString(s);
				tex.setPosition(150, 30 + 20 * p1_defences.size());
				p1_defences.push_back(tex);
			}
		}
	}
	for (auto& it : *actions2) {
		std::string name = Action::enumToString(it->getEmotion());
		sf::Text tex;
		tex.setFont(*entity_manager_->getFont());
		tex.setCharacterSize(16);
		if (it->getCategory() == Action::CATEGORY_ATTACK) {
			tex.setString(name);
			tex.setPosition(512, 30 + 20 * p2_attacks.size());
			p2_attacks.push_back(tex);
		}
		else if (it->getCategory() == Action::CATEGORY_DEFENCE) {
			std::string counter = "";
			for (auto& it2 : *actions1) {
				if (it2->getCategory() == Action::CATEGORY_ATTACK && it2->getCounterEmotion() == it->getEmotion()) {
					counter = Action::enumToString(it2->getEmotion());
				}
			}
			if (counter != "") {
				std::string s = "Counter " + counter + " with " + name;
				tex.setString(s);
				tex.setPosition(662, 30 + 20 * p2_defences.size());
				p2_defences.push_back(tex);
			}
		}
	}
	
}

void GameState::render(sf::RenderTarget* target) {
	particle_engine_->renderStatics(target);
	entity_manager_->render(target);
	particle_engine_->renderParticles(target);

	target->draw(p1_ahead);
	target->draw(p1_dhead);
	for (auto& it : p1_attacks) {
		target->draw(it);
	}
	for (auto& it : p1_defences) {
		target->draw(it);
	}

	target->draw(p2_ahead);
	target->draw(p2_dhead);
	for (auto& it : p2_attacks) {
		target->draw(it);
	}
	for (auto& it : p2_defences) {
		target->draw(it);
	}
	target->draw(health1);
	target->draw(health2);
	entity_manager_->renderFront(target);
}

void GameState::loadTextures() {
	tex_manager_.setDirectory("media/images/");
	tex_manager_.load("player1", "player1.png");
	tex_manager_.load("player2", "player2.png");
	tex_manager_.load("missile", "missile.png");
	tex_manager_.load("attackbox", "attackbox.png");
	tex_manager_.load("defencebox", "defencebox.png");

}