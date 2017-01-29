#include "stdafx.h"
#include "EmotionData.h"

EmotionData::EmotionData( //temporary
	float anger,
	float contempt,
	float disgust,
	float fear,
	float happiness,
	float neutral,
	float sadness,
	float surprise
) {
	data_[Action::EMOTION_ANGER] = anger;
	data_[Action::EMOTION_CONTEMPT] = contempt;
	data_[Action::EMOTION_DISGUST] = disgust;
	data_[Action::EMOTION_FEAR] = fear;
	data_[Action::EMOTION_HAPPINESS] = happiness;
	data_[Action::EMOTION_NEUTRAL] = neutral;
	data_[Action::EMOTION_SADNESS] = sadness;
	data_[Action::EMOTION_SURPRISE] = surprise;
}

EmotionData::EmotionData() {
	data_[Action::EMOTION_ANGER] = 0.f;
	data_[Action::EMOTION_CONTEMPT] = 0.f;
	data_[Action::EMOTION_DISGUST] = 0.f;
	data_[Action::EMOTION_FEAR] = 0.f;
	data_[Action::EMOTION_HAPPINESS] = 0.f;
	data_[Action::EMOTION_NEUTRAL] = 0.f;
	data_[Action::EMOTION_SADNESS] = 0.f;
	data_[Action::EMOTION_SURPRISE] = 0.f;
}

void EmotionData::setData(Action::EMOTION emotion, float value) {
	data_[emotion] = value;
}

float EmotionData::getData(Action::EMOTION emotion) const {
	return data_.at(emotion);
}