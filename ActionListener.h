#pragma once

#include <vector>
#include <map>

class Action;
class EntityManager;

class ActionListener {
public:
	ActionListener(EntityManager* entity_manager);
	void update(int frame_time);
	void actionCharged(Action* action);
private:
	std::map<Action*, int> charged_defences_;
	std::vector<Action*> queued_actions_;
	EntityManager* entity_manager_;
};

/*
-Action
--Attack
--Defence

-Feed EmotionData once per emotion_tick into player
-Player passes it to actions
-Actions then charge
-Actions call relevant function in ActionListener when charged
-ActionListener decides whether to activate the action
-Action gets deleted
*/