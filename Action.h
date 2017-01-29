#pragma once

class EmotionData;
class ActionListener;
class ActionFunction;
class EntityManager;

class Action {
public:
	enum ACTION_CATEGORY {
		CATEGORY_ATTACK,
		CATEGORY_DEFENCE
	};
	enum EMOTION {
		EMOTION_ANGER,
		EMOTION_CONTEMPT,
		EMOTION_DISGUST,
		EMOTION_FEAR,
		EMOTION_HAPPINESS,
		EMOTION_NEUTRAL,
		EMOTION_SADNESS,
		EMOTION_SURPRISE
	};
	Action(ActionListener* listener, ACTION_CATEGORY category, 
		EMOTION emotion, EMOTION counter_emotion, ActionFunction* function);
	void inputData(EmotionData* data, int tick_length);
	~Action();
	void doAction();
	static const int ATTACK_CHARGE_TIME;
	static const int DEFENCE_CHARGE_TIME;
	static const int DEFENCE_SUSTAIN_TIME;
	static std::string enumToString(EMOTION emotion);
	void remove();
	bool getRemoved() const;
	ACTION_CATEGORY getCategory() const;
	EMOTION getCounterEmotion() const;
	EMOTION getEmotion() const;
private:
	std::unique_ptr<ActionFunction> function_;
	ActionListener* listener_;
	ACTION_CATEGORY category_;
	EMOTION emotion_;
	EMOTION counter_emotion_;
	bool removed_;
	int time_charging_;
	bool active_;
};
