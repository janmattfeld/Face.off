#include "stdafx.h"
#include "EntityManager.h"
#include "Entity.h"
#include "SFLD.h"

EntityManager::EntityManager() :is_scrolling_(false), in_shake_(false){
	font_.loadFromFile("media/victor-pixel.ttf");
	scroll_text_.setFont(font_);
	scroll_text_.setCharacterSize(50);
	//background_.
}

void EntityManager::add(Entity* entity) {
	newent_q_.push(std::unique_ptr<Entity>(entity));
}

void EntityManager::renderFront(sf::RenderTarget* target) {
	for (auto& it : render_fronts_) {
		target->draw(it);
	}
	if (is_scrolling_) {
		target->draw(scroll_text_);
	}
}

void EntityManager::displayScrollingMessage(std::string string, int time) {
	is_scrolling_ = true;
	scroll_timer_ = 0;
	scroll_duration_ = time;
	scroll_text_.setString(string);
	scroll_text_.setPosition(1024 / 2 - scroll_text_.getLocalBounds().width / 2,
		768 / 2 - scroll_text_.getLocalBounds().height / 2);
}

EntityPtrList* EntityManager::getEntities() {
	return &entities_;
}

sf::Font* EntityManager::getFont() {
	return &font_;
}

void EntityManager::update(int frame_time) {
	if (is_scrolling_) {
		scroll_timer_ += frame_time;
		if (scroll_timer_ > scroll_duration_) {
			scroll_text_.setPosition(scroll_text_.getPosition().x,
				scroll_text_.getPosition().y - 0.5f);
			if (scroll_timer_ > scroll_duration_ + 2000) {
				is_scrolling_ = false;
			}
		}
	}
	while (!newent_q_.empty()) {
		entities_.push_back(std::move(newent_q_.front()));
		newent_q_.pop();
	}
	for (auto& it = entities_.begin(); it != entities_.end();) {
		if (!(*it)->isDestroyed()) {
			it++;
		}
		else {
			it = entities_.erase(it);
		}
	}
	for (auto& it : entities_) {
		it->update(frame_time);
	}
	if (in_shake_) {
		float xdisp = (rand() % 21 - 10) / 10.0f;
		float ydisp = (rand() % 21 - 10) / 10.0f;
		view_.setCenter(SFLD::window_->getDefaultView().getCenter() + sfld::Vector2f(xdisp*shake_magnitude_, ydisp*shake_magnitude_));
		SFLD::window_->setView(view_);
		shake_timer_ += frame_time;
		if (shake_timer_ >= shake_length_) {
			shake_timer_ = 0;
			view_ = SFLD::window_->getDefaultView();
			SFLD::window_->setView(view_);
			in_shake_ = false;
		}
	}
}

void EntityManager::render(sf::RenderTarget* target) {
	for (auto& it : entities_) {
		it->render(target);
	}
}

void EntityManager::screenShake(float magnitude, int time) {
	in_shake_ = true;
	shake_magnitude_ = magnitude;
	shake_length_ = time;
	shake_timer_ = 0;
}