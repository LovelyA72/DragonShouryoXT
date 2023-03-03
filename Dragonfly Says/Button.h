#pragma once
#include "DragonShouryo.h"
#include "EventInputState.h"
#include "EventAnswer.h"

class Button : public dsr::DsrObject {
private:
	bool accepting_input = false;
	bool correct_answer = 0;
	int this_button = 0;
	std::string dbgletters[6] = {"w","a","s","d","l","r"};
public:
	Button(int t = 0) {
		this_button = t;
	}
	int eventHandler(const dsr::Event* p_e) override {
		if (p_e->getType() == EVENT_INPUTSTATE) {
			const EventInputState* p_eis =
				dynamic_cast <const EventInputState*> (p_e);
			if (p_eis->type == 1) {
				accepting_input = true;
			}
			else {
				//printf("btn%d stop accepting input\n", this_button);
				accepting_input = false;
			}
			if (accepting_input) {
				//printf("btn%d accepting input. Correct ans is %s\n", this_button, dbgletters[p_eis->move.move[0]].c_str());
				correct_answer = (p_eis->move.move[0] == this_button);
				accepting_input = true;
			}
		}
		if (p_e->getType() == dsr::KEYBOARD_EVENT) {
			if (accepting_input) {
				const dsr::EventKeyboard* p_kbd = dynamic_cast <const dsr::EventKeyboard*> (p_e);
				if (p_kbd->getKeyboardAction() == dsr::KEY_PRESSED) {
					switch (this_button)
					{
					case 0:
						if (p_kbd->getKey() == dsr::Keyboard::W) {
							setSprite("W");
							RM.getSound("w")->play();
						}
						break;
					case 1:
						if (p_kbd->getKey() == dsr::Keyboard::A) {
							setSprite("A");
							RM.getSound("a")->play();
						}
						break;
					case 2:
						if (p_kbd->getKey() == dsr::Keyboard::S) {
							setSprite("S");
							RM.getSound("s")->play();
						}
						break;
					case 3:
						if (p_kbd->getKey() == dsr::Keyboard::D) {
							setSprite("D");
							RM.getSound("d")->play();
						}
						break;
					default:
						break;
					}
				}
				if (p_kbd->getKeyboardAction() == dsr::KEY_RELEASED) {
					switch (this_button)
					{
					case 0:
						if (p_kbd->getKey() == dsr::Keyboard::W) {
							setSprite("w");
							if (correct_answer) {
								EventAnswer ea(this_button, true);
								WM.onEvent(&ea);								
							}
							else {
								EventAnswer ea(this_button, false);
								WM.onEvent(&ea);								
							}
						}
						break;
					case 1:
						if (p_kbd->getKey() == dsr::Keyboard::A) {
							setSprite("a");
							if (correct_answer) {
								EventAnswer ea(this_button, true);
								WM.onEvent(&ea);								
							}
							else {
								EventAnswer ea(this_button, false);
								WM.onEvent(&ea);								
							}
						}
						break;
					case 2:
						if (p_kbd->getKey() == dsr::Keyboard::S) {
							setSprite("s");
							if (correct_answer) {
								EventAnswer ea(this_button, true);
								WM.onEvent(&ea);								
							}
							else {
								EventAnswer ea(this_button, false);
								WM.onEvent(&ea);								
							}
						}
						break;
					case 3:
						if (p_kbd->getKey() == dsr::Keyboard::D) {
							setSprite("d");
							if (correct_answer) {
								EventAnswer ea(this_button, true);
								WM.onEvent(&ea);								
							}
							else {
								EventAnswer ea(this_button, false);
								WM.onEvent(&ea);								
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}
		if (p_e->getType() == dsr::MSE_EVENT) {
			if (accepting_input) {
				const dsr::EventMouse* p_mse = dynamic_cast <const dsr::EventMouse*> (p_e);
				if (p_mse->getMouseAction() == dsr::PRESSED) {
					switch (this_button)
					{
					case 4:
						if (p_mse->getMouseButton() == dsr::Mouse::LEFT) {
							setSprite("L");
							RM.getSound("l")->play();
						}
						break;
					case 5:
						if (p_mse->getMouseButton() == dsr::Mouse::RIGHT) {
							setSprite("R");
							RM.getSound("r")->play();
						}
						break;
					default:
						break;
					}
				}
				if (p_mse->getMouseAction() == dsr::RELEASED) {
					switch (this_button)
					{
					case 4:
						if (p_mse->getMouseButton() == dsr::Mouse::LEFT) {
							setSprite("l");
							if (correct_answer) {
								EventAnswer ea(this_button, true);
								WM.onEvent(&ea);
							}
							else {
								EventAnswer ea(this_button, false);
								WM.onEvent(&ea);
							}
						}
						break;
					case 5:
						if (p_mse->getMouseButton() == dsr::Mouse::RIGHT) {
							setSprite("r");
							if (correct_answer) {
								EventAnswer ea(this_button, true);
								WM.onEvent(&ea);
							}
							else {
								EventAnswer ea(this_button, false);
								WM.onEvent(&ea);
							}
						}
						break;
					default:
						break;
					}
				}
			}
		}
		return 0;
	}
};