#pragma once
#include <map>
#include "Action.h"

class EmotionData {
public:
	EmotionData(
		float anger,
		float contempt,
		float disgust,
		float fear,
		float happiness,
		float neutral,
		float sadness,
		float surprise
	);
	EmotionData();
	void setData(Action::EMOTION emotion, float value);
	float getData(Action::EMOTION emotion) const;
private:
	std::map<Action::EMOTION, float> data_;
};
