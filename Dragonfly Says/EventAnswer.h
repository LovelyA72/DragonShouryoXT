#pragma once
#include "DragonShouryo.h"

const std::string EVENT_ANSWER = "dfs-answer";
class EventAnswer :public dsr::Event {
public:
	EventAnswer(int f,bool c) {
		setType(EVENT_ANSWER);
		from = f;
		correct = c;
	}
	int from = -1;
	bool correct = 0;
};