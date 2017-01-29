#include "stdafx.h"
#include "DefenceBox.h"
#include "Player.h"
#include "DefenceFunction.h"
#include "Action.h"

DefenceBox::DefenceBox(Player* player1, Player* player2, sfld::Vector2f position,
	EntityManager* entity_manager, ResourceManager<sf::Texture, std::string>* tex_manager,
	ParticleEngine* particle_engine, ActionListener* listener)
	:player1_(player1), player2_(player2), particle_engine_(particle_engine),
	listener_(listener), texture_manager_(tex_manager) {
	entityConstructor(entity_manager, tex_manager, "defencebox", maths::SHAPE_SQUARE, position);
}

void DefenceBox::update(int frame_time) {
	float len1 = sfld::Vector2f(getPosition() - player1_->getPosition()).length();
	float len2 = sfld::Vector2f(getPosition() - player2_->getPosition()).length();
	if (len1 <= 40.0 || len2 <= 40.0) {
		Player* closest;
		Player* other;
		if (len1 < len2) {
			closest = player1_;
			other = player2_;
		}
		else {
			closest = player2_;
			other = player1_;
		}
		std::vector<Action::EMOTION> enemy_counters;
		for (auto& it : *other->getActions()) {
			if (it->getCategory() == Action::CATEGORY_ATTACK) {
				enemy_counters.push_back(it->getCounterEmotion());
			}
		}

		int n = rand() % enemy_counters.size();
		DefenceFunction* defence_function = new DefenceFunction();
		Action* defence_action = new Action(listener_, Action::CATEGORY_DEFENCE, enemy_counters[n],
			enemy_counters[n], defence_function);
		closest->addAction(defence_action);
		destroy();
	}
}