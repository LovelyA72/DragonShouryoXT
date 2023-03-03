#pragma once
#include "DragonShouryo.h"
#include "EventNuke.h"

class Saucer : public dsr::DsrObject {
public:
	Saucer() {
		setType("saucer");
	}
	int eventHandler(const GameEvent* p_e) override{
		if (p_e->getType() == NUKE_EVENT) {
			dsr::EventView e;
			e.setDelta(true);
			e.setValue(1);
			e.setTargetId(543);
			WM.onEvent(&e);
			WM.markForDelete(this);
		}
		if (p_e->getType() == dsr::COLLISION_EVENT) {
			const dsr::EventCollision* p_c =
				dynamic_cast <const dsr::EventCollision*> (p_e);
			if (getSolidness() == dsr::HARD) {
				WM.markForDelete(this);
				return 0;
			}
			if ((p_c->getObject2()->getType() == "bullet")) {
				WM.markForDelete(this);
				return 0;
			}

		}
		if (p_e->getType() == dsr::OUT_EVENT) {
			WM.markForDelete(this);
		}
	}
};