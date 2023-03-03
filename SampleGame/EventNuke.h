#pragma once
#include "DragonShouryo.h"

const std::string NUKE_EVENT = "dsr::nuke";
class EventNuke : public dsr::Event {
public:
	EventNuke() {
		setType(NUKE_EVENT);
	}
};