#include "stdafx.h"
#include "Action.h"
#include "EmotionData.h"
#include "ActionListener.h"
#include "ActionFunction.h"
#include "AngerFunction.h"

const int Action::ATTACK_CHARGE_TIME = 2000;
const int Action::DEFENCE_SUSTAIN_TIME = (int)(Action::ATTACK_CHARGE_TIME / 1.5);
const int Action::DEFENCE_CHARGE_TIME = (int)(Action::ATTACK_CHARGE_TIME / 2);



Action::Action(ActionListener* listener, Action::ACTION_CATEGORY category,
	Action::EMOTION emotion, Action::EMOTION counter_emotion, ActionFunction* function)
	: listener_(listener), category_(category), emotion_(emotion),
	time_charging_(0), counter_emotion_(counter_emotion), active_(true) {
	function_ = std::unique_ptr<ActionFunction>(function);
}

Action::~Action() = default;

Action::EMOTION Action::getEmotion() const {
	return emotion_;
}

void Action::doAction() {
	function_->doAction();
}

std::string Action::enumToString(Action::EMOTION emotion) {
	std::string str = "";
	switch (emotion) {
	case EMOTION_ANGER:
		str = "ANGER";
		break;
	case EMOTION_CONTEMPT:
		str = "CONTEMPT";
		break;
	case EMOTION_DISGUST:
		str = "DISGUST";
		break;
	case EMOTION_FEAR:
		str = "FEAR";
		break;
	case EMOTION_HAPPINESS:
		str = "HAPPINESS";
		break;
	case EMOTION_NEUTRAL:
		str = "NEUTRAL";
		break;
	case EMOTION_SADNESS:
		str = "SADNESS";
		break;
	case EMOTION_SURPRISE:
		str = "SURPRISE";
		break;
	}
	return str;
}

Action::EMOTION Action::getCounterEmotion() const {
	return counter_emotion_;
}

Action::ACTION_CATEGORY Action::getCategory() const {
	return category_;
}

void Action::inputData(EmotionData* data, int tick_length) {
	//TODO: this function will need to be adjusted
	//based on results from emotion API
	if (active_) {
		if (emotion_ == Action::EMOTION_ANGER && data->getData(emotion_) >= 0.4f
			|| emotion_ == Action::EMOTION_SADNESS && data->getData(emotion_) >= 0.4f
			|| emotion_ == Action::EMOTION_SURPRISE && data->getData(emotion_) >= 0.6f
			|| emotion_ == Action::EMOTION_HAPPINESS && data->getData(emotion_) >= 0.7f) {
			time_charging_ += tick_length;
		}
		else {
			time_charging_ = 0;
		}

		if ((category_ == CATEGORY_DEFENCE && time_charging_ >= DEFENCE_CHARGE_TIME)
			|| (category_ == CATEGORY_ATTACK && time_charging_ >= ATTACK_CHARGE_TIME)) {
			listener_->actionCharged(this);
			active_ = false;
		}
	}
}

void Action::remove() {
	removed_ = true;
}

bool Action::getRemoved() const {
	return removed_;
}