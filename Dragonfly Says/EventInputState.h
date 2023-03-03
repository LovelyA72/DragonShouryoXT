#pragma once
#include "DragonShouryo.h"
#include "Move.h"

const std::string EVENT_INPUTSTATE = "dfs-inputstate";
class EventInputState : public dsr::Event {
public:
	//Type 0: start input, 1 stop input
	int type = 0;
	Move move;
	EventInputState(int t, Move m = Move()) {
		setType(EVENT_INPUTSTATE);
		move = m;
		type = t;
	}
};