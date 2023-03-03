#pragma once
#include "DragonShouryo.h"
#include "ScoreEvent.h"

class Bullet :public dsr::DsrObject {
public:
	Bullet() {
		setSprite("bullet");
		setSprMode(1);
		setVelocity(dsr::Vector2D(2, 0));
		setAlt(7);
		setType("bullet");
	}
	int eventHandler(const dsr::Event* p_e) override {
		if (p_e->getType() == dsr::OUT_EVENT || p_e->getType() == dsr::COLLISION_EVENT) {
			if (p_e->getType() == dsr::COLLISION_EVENT) {
				const dsr::EventCollision* p_c =
					dynamic_cast <const dsr::EventCollision*> (p_e);
				if ((p_c->getObject2()->getType() == "shouryo")|| p_c->getObject2()->getType() == "saucer") {
					RM.getSound("explode")->play();
					dsr::EventView e;
					e.setDelta(true);
					e.setValue(1);
					e.setTargetId(543);
					WM.onEvent(&e);
				}
			}
			WM.markForDelete(this);
			return 0;
		}
		return 1;
	}
};