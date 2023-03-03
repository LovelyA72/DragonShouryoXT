#include "Shouryo.h"

Shouryo::Shouryo()
{
	setType("shouryo");
}

Shouryo::~Shouryo()
{
}

int Shouryo::eventHandler(const GameEvent* p_e)
{
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
	return 0;
}
