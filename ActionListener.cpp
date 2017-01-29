#include "stdafx.h"
#include "ActionListener.h"
#include "Action.h"
#include "EntityManager.h"

ActionListener::ActionListener(EntityManager* entity_manager):entity_manager_(entity_manager) {
}

void ActionListener::update(int frame_time) {
	for (auto& it = charged_defences_.begin(); it != charged_defences_.end();) {
		it->second += frame_time;
		if (it->second >= Action::DEFENCE_SUSTAIN_TIME) {
			std::cout << "Defence removed" << std::endl;
			it->first->remove();
			it = charged_defences_.erase(it);
		}
		else {
			it++;

			//std::cout << "Defence active" << std::endl;
		}
	}
	for (auto& it = queued_actions_.begin(); it != queued_actions_.end();) {
		Action::EMOTION counter = (*it)->getCounterEmotion();
		bool defended = false;
		std::cout << "Attack added. Number of in-play defences: " << charged_defences_.size() << std::endl;
		for (auto& it : charged_defences_) {
			if (counter == it.first->getEmotion()) {
				defended = true;
				break;
			}
		}
		if (!defended) {
			entity_manager_->displayScrollingMessage(
				Action::enumToString((*it)->getEmotion()) + " activated!", 2000);
			(*it)->doAction();
		}
		else {
			std::cout << "attack defended!" << std::endl;
			entity_manager_->displayScrollingMessage(
				Action::enumToString((*it)->getEmotion()) + " countered with " + 
				Action::enumToString(counter) + "!", 2000);
			entity_manager_->screenShake(0.5f, 500);
		}
		(*it)->remove();
		it = queued_actions_.erase(it);
	}
}

void ActionListener::actionCharged(Action* action) {
	if (action->getCategory() == Action::CATEGORY_DEFENCE) {
		std::cout << "Defence added" << std::endl;
		charged_defences_[action] = 0;
	}
	else if (action->getCategory() == Action::CATEGORY_ATTACK) {
		queued_actions_.push_back(action);
	}
}