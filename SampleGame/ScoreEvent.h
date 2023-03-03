#pragma once
#include "DragonShouryo.h"

const std::string SCORE_EVENT = "sampgame::score";
class EventScore : public dsr::Event {
public:
	EventScore() {
		setType(SCORE_EVENT);
	}
};