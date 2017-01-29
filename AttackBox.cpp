#include "AttackBox.h"
#include "Player.h"
#include "stdafx.h"
#include "AttackBox.h"
#include "AngerFunction.h"
#include "Action.h"
#include "SadFunction.h"
#include "SurprisedFunction.h"
#include "Player.h"

AttackBox::AttackBox(Player* player1, Player* player2, sfld::Vector2f position,
	EntityManager* entity_manager, ResourceManager<sf::Texture, std::string>* tex_manager,
	ParticleEngine* particle_engine, ActionListener* listener)
	:player1_(player1), player2_(player2), particle_engine_(particle_engine),
	listener_(listener), texture_manager_(tex_manager){
	entityConstructor(entity_manager, tex_manager, "attackbox", maths::SHAPE_SQUARE, position);
}

void AttackBox::update(int frame_time) {
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
		int n = rand() % 3;
		if (n == 0) {
			ActionFunction* anger_function = new AngerFunction(other, particle_engine_,
				getEntityManager());
			Action* anger_action = new Action(listener_, Action::CATEGORY_ATTACK, Action::EMOTION_ANGER,
				Action::EMOTION_HAPPINESS, anger_function);
			closest->addAction(anger_action);
		}
		else if (n == 1) {
			ActionFunction* sad_function = new SadFunction(other, particle_engine_);

			Action* sad_action = new Action(listener_, Action::CATEGORY_ATTACK, Action::EMOTION_SADNESS,
				Action::EMOTION_HAPPINESS, sad_function);
			closest->addAction(sad_action);
		}
		else if (n == 2) {
			ActionFunction* surprised_function = new SurprisedFunction(other, closest, particle_engine_,
				getEntityManager(), texture_manager_);
			Action* surprised_action = new Action(listener_, Action::CATEGORY_ATTACK, Action::EMOTION_SURPRISE,
				Action::EMOTION_SURPRISE, surprised_function);
			closest->addAction(surprised_action);
		}
		destroy();
	}
}