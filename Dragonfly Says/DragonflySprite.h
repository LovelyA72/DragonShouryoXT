#pragma once
#include "DragonShouryo.h"
#include "EventInputState.h"

using namespace dsr;

class DragonflySprite : public DsrObject {
private:
	bool accepting_input = false;
public:
	DragonflySprite() {

	}
	int eventHandler(const Event* p_e) override {
		if (p_e->getType() == EVENT_INPUTSTATE) {
			const EventInputState* p_eis = dynamic_cast <const EventInputState*> (p_e);
			if (p_eis->type == 1) {
				accepting_input = true;
			}
			else {
				accepting_input = false;
			}
		}
		if (p_e->getType() == dsr::KEYBOARD_EVENT) {
			const dsr::EventKeyboard* p_kbd = dynamic_cast <const dsr::EventKeyboard*> (p_e);
			if (accepting_input) {			
				if (p_kbd->getKeyboardAction() == dsr::KEY_PRESSED) {
					setSprite("fastfly");
				}			
			}
			if (p_kbd->getKeyboardAction() == dsr::KEY_RELEASED) {
				setSprite("dragonfly");
			}		
		}
		if (p_e->getType() == dsr::MSE_EVENT) {
			const dsr::EventMouse* p_mse = dynamic_cast <const dsr::EventMouse*> (p_e);
			if (accepting_input) {				
				if (p_mse->getMouseAction() == dsr::PRESSED) {
					setSprite("fastfly");
				}				
			}
			if (p_mse->getMouseAction() == dsr::RELEASED) {
				setSprite("dragonfly");
			}
		}
		return 0;
	}
};