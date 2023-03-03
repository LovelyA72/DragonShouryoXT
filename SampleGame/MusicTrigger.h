#pragma once
#include "DragonShouryo.h"

class MusicTrigger :public dsr::DsrObject {
public:
	MusicTrigger();
	~MusicTrigger();
	int eventHandler(const GameEvent *p_e) override;
};