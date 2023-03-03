#pragma once
#include "DragonShouryo.h"

class Star :public dsr::DsrObject {
public:
	Star() {
	}
	int eventHandler(const GameEvent* p_e) override {
		if (p_e->getType() == dsr::OUT_EVENT) {
			const dsr::EventOut* p_out =
				dynamic_cast <const dsr::EventOut*> (p_e);
			if (getPosition().getX() < 10) {
				setVelocity(dsr::Vector2D(-1.0 / (rand() % 10 + 1), 0));
				setPosition(dsr::Vector2D(200, random(0, 44)));
			}
			return 0;
		}
		return 1;
	}
	int random(int min, int max) //range : [min, max]
	{
		static bool first = true;
		if (first)
		{
			srand(time(NULL)); //seeding for the first time only!
			first = false;
		}
		return min + rand() % ((max + 1) - min);
	}
private:

};