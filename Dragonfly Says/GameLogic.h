#pragma once
#include "DragonShouryo.h"
#include "Move.h"
#include "Star.h"
#include "Button.h"
#include "Timer.h"
#include "EventInputState.h"
#include "soloud.h"
#include "soloud_wav.h"

class GameLogic : public dsr::DsrObject {
private:
	int state = 0;
	//Game state
	//0: show sequence
	//1: player input
	//2: result
	int gamestate = 0;
	int level = 0;
	Move moves[20];
	int currentMoves = 0;
	int playerMoves = 0;
	int showingStep = 0;
	int correctCount = 0;
	int maxMoves = 0;
	std::string hiname = "KSR";
	int score = 0;
	int hiscore = 0;
	bool w_pressed = 0;
	bool s_pressed = 0;
	bool a_pressed = 0;
	bool d_pressed = 0;
	bool show_pressed = 0;
	SoLoud::Soloud m_soloud;
	SoLoud::Wav bgm1;
	SoLoud::Wav bgm2;
	SoLoud::handle h1;
	SoLoud::handle h2;
	Timer* timer1;
	dsr::Hud* scoreHud;
	dsr::Hud* hiscoreHud;
	dsr::Hud* levelHud;
	dsr::Vector2D m_cur_loc = dsr::Vector2D(0, 0);
	std::string namein[3] = {"_","_","_"};
	int nameindex = 0;
public:
	GameLogic() {
		//setSolidness(dsr::SPECTRAL);
		m_soloud.init();
		bgm1.load("./DragonflySays_Data/samples/bgm-loop.ogg");
		bgm2.load("./DragonflySays_Data/samples/bgm-loop2.ogg");
		bgm1.setLooping(true);
		bgm2.setLooping(true);
		timer1 = dynamic_cast <Timer*> (WM.getObjectByName("timer1"));
		scoreHud = dynamic_cast <dsr::Hud*> (WM.getObjectByName("scorehud"));
		hiscoreHud = dynamic_cast <dsr::Hud*> (WM.getObjectByName("hiscorehud"));
		levelHud = dynamic_cast <dsr::Hud*> (WM.getObjectByName("levelhud"));
	};

	~GameLogic() {

	};
	int roll(int min, int max)
	{
		double x = rand() / static_cast<double>(RAND_MAX + 1);

		int that = min + static_cast<int>(x * (max - min));

		return that;
	}
	void addStep() {
		if (level < 1) {
			moves[currentMoves] = Move(0, roll(0, 4), roll(0, 4));
		}
		else {
			//if two numbers are the same while type is 1, it will be a single button move
			moves[currentMoves] = Move(0, roll(0, 6), roll(0, 6));
			WM.getObjectByName("l-btn")->setVisibility(true);
			WM.getObjectByName("r-btn")->setVisibility(true);
		}
		currentMoves++;
	}
	void gameover() {
		gamestate = 0;
		currentMoves = 0;
		playerMoves = 0;
		showingStep = 0;
		WM.getObjectByName("w-btn")->setVisibility(false);
		WM.getObjectByName("a-btn")->setVisibility(false);
		WM.getObjectByName("s-btn")->setVisibility(false);
		WM.getObjectByName("d-btn")->setVisibility(false);
		WM.getObjectByName("l-btn")->setVisibility(false);
		WM.getObjectByName("r-btn")->setVisibility(false);
		m_soloud.fadeVolume(h1, 0.8, 1.5);
		m_soloud.fadeVolume(h2, 0.8, 1.5);
		if (score > hiscore) {
			WM.getObjectByName("dragonfly")->setVisibility(false);
			WM.getObjectByName("dragonfly")->setSprite("dragonfly");
			SM.sayText("High score. Enter your name", 2.0f);
			state = 3;
		}
		else {
			WM.getObjectById(222)->setVisibility(true);
			SM.sayText("Game over. Better luck next time.", 2.0f);
			state = 2;
			WM.getObjectByName("dragonfly")->setSprite("angryfly");
		}
	}
	int eventHandler(const dsr::Event* p_e) override {
		if (p_e->getType() == dsr::MSE_EVENT) {
			const dsr::EventMouse* p_mouse =
				dynamic_cast <const dsr::EventMouse*> (p_e);
			if (p_mouse->getMouseAction() == dsr::MOVED) {
				dsr::Vector2D loc = DM.pixelsToSpaces(dsr::Vector2D(p_mouse->getMousePosition().getX(), p_mouse->getMousePosition().getY()));
				m_cur_loc = loc;
			}
		}
		if (p_e->getType() == EVENT_ANSWER) {
			const EventAnswer* p_ans =
				dynamic_cast <const EventAnswer*> (p_e);
			if (p_ans->correct) {
				if (moves[playerMoves].type) {

				}
				playerMoves++;
				if (playerMoves == currentMoves) {
					if (currentMoves < maxMoves) {
						printf("correct!\n");
						RM.getSound("correct")->play();
						playerMoves = 0;
						showingStep = 0;
						addStep();
						timer1->setTimer(30);
						dsr::EventView e;
						e.setDelta(true);
						e.setValue(1);
						e.setTargetId(543);
						score++;
						WM.onEvent(&e);
					}
					else {
						RM.getSound("lvup")->play();
						currentMoves = 0;
						playerMoves = 0;
						showingStep = 0;
						if (maxMoves < 20) {
							maxMoves++;
						}
						level++;
						printf("Level %d\n", level);
						addStep();
						timer1->setTimer(60);
						score += 11;
						dsr::EventView e;
						e.setDelta(true);
						e.setValue(11);
						e.setTargetId(543);
						WM.onEvent(&e);
						dsr::EventView e2;
						e2.setDelta(true);
						e2.setValue(1);
						e2.setTargetId(654);
						WM.onEvent(&e2);
					}
					EventInputState eis(0, moves[playerMoves]);
					WM.onEvent(&eis);
					gamestate = 0;
					return 0;
				}
				EventInputState eis(1, moves[playerMoves]);
				WM.onEvent(&eis);
			}
			else {
				EventInputState eis(0, moves[playerMoves]);
				WM.onEvent(&eis);
				currentMoves = 0;
				playerMoves = 0;
				showingStep = 0;
				maxMoves = 5;
				level = 0;
				RM.getSound("over")->play();
				printf("incorrect!\n");
				gamestate = 0;
				//timer1->setTimer(60);
				dsr::EventView e2;
				e2.setDelta(false);
				e2.setValue(0);
				e2.setTargetId(654);
				WM.onEvent(&e2);
				gameover();
			}
		}
		if (p_e->getType() == dsr::STEP_EVENT) {
			const dsr::EventStep* p_step = dynamic_cast <const dsr::EventStep*> (p_e);
			if (p_step->getStepCount() == 1) {
				DM.getWindow()->setTitle("Dragonfly Says!");
				bgm1.setVolume(0.8f);
				bgm2.setVolume(0.8f);
				h1 = m_soloud.play(bgm1);
				h2 = m_soloud.play(bgm2);
				SM.sayText("Welcome to Dragonfly Says. Press P to play.", 2.0f);
				hiscoreHud->setViewString("TOP: " + hiname + " ");
				hiscoreHud->setValue(hiscore);
			}
			//Do regular update
			switch (state) {
			case 0: //main menu
				break;
			case 1:
				switch (gamestate) {
				case 0:// show sequence
					if (timer1->isFinished()) {
						//show next step and reset timer or enter player input state
						if (showingStep < currentMoves) {
							if (show_pressed) {
								//release all buttons
								WM.getObjectByName("w-btn")->setSprite("w");
								WM.getObjectByName("a-btn")->setSprite("a");
								WM.getObjectByName("s-btn")->setSprite("s");
								WM.getObjectByName("d-btn")->setSprite("d");
								WM.getObjectByName("l-btn")->setSprite("l");
								WM.getObjectByName("r-btn")->setSprite("r");
								show_pressed = 0;
								timer1->setTimer(7);
							}
							else {
								//Show move
								if (moves[showingStep].type) {
									//double button

								}
								else {
									//single button
									//press next button
									switch (moves[showingStep].move[0]) {
									case 0:
										WM.getObjectByName("w-btn")->setSprite("W");
										RM.getSound("w")->play();
										break;
									case 1:
										WM.getObjectByName("a-btn")->setSprite("A");
										RM.getSound("a")->play();
										break;
									case 2:
										WM.getObjectByName("s-btn")->setSprite("S");
										RM.getSound("s")->play();
										break;
									case 3:
										WM.getObjectByName("d-btn")->setSprite("D");
										RM.getSound("d")->play();
										break;
									case 4:
										WM.getObjectByName("l-btn")->setSprite("L");
										RM.getSound("l")->play();
										break;
									case 5:
										WM.getObjectByName("r-btn")->setSprite("R");
										RM.getSound("r")->play();
									}
								}
								show_pressed = 1;
								showingStep++;
								timer1->setTimer(20);
							}
						}
						else {
							//enter player input state
							WM.getObjectByName("w-btn")->setSprite("w");
							WM.getObjectByName("a-btn")->setSprite("a");
							WM.getObjectByName("s-btn")->setSprite("s");
							WM.getObjectByName("d-btn")->setSprite("d");
							WM.getObjectByName("l-btn")->setSprite("l");
							WM.getObjectByName("r-btn")->setSprite("r");
							show_pressed = 0;
							gamestate = 1;
							EventInputState eis(1, moves[playerMoves]);
							WM.onEvent(&eis);
						}
					}
					break;
				case 1:
					//player input

					break;
				default:
					break;
				}
				break;
			case 2:
				WM.getObjectByName("dragonfly")->setSprite("angryfly");
				break;
			case 3:
				//high score
				if (nameindex == 3) {
					hiname = namein[0] + namein[1] + namein[2];
					nameindex = 0;
					namein[0] = "_";
					namein[1] = "_";
					namein[2] = "_";
					hiscore = score;
					hiscoreHud->setViewString("TOP: " + hiname + " ");
					hiscoreHud->setValue(hiscore);
					WM.getObjectById(111)->setVisibility(true);
					state = 0;
				}
				break;
			default:
				break;
			}
		}
		if (p_e->getType() == dsr::KEYBOARD_EVENT) {
			const dsr::EventKeyboard* p_kbd =
				dynamic_cast <const dsr::EventKeyboard*> (p_e);
			if (p_kbd->getKeyboardAction() == dsr::KEY_PRESSED) {
				if (p_kbd->getKey() == dsr::Keyboard::Q) {
					if (state != 3) {
						GM.setGameOver(true);
					}
				}
			}
			switch (state) {
			case 0: //main menu
				if (p_kbd->getKeyboardAction() == dsr::KEY_PRESSED) {
					if (p_kbd->getKey() == dsr::Keyboard::P) {
						printf("Starting game...\n");
						m_soloud.fadeVolume(h1, 0.6, 1.5);
						m_soloud.fadeVolume(h2, 0.0, 1.5);
						maxMoves = 5;
						score = 0;
						WM.getObjectById(111)->setVisibility(false);
						addStep();
						WM.getObjectByName("w-btn")->setVisibility(true);
						WM.getObjectByName("a-btn")->setVisibility(true);
						WM.getObjectByName("s-btn")->setVisibility(true);
						WM.getObjectByName("d-btn")->setVisibility(true);
						WM.getObjectByName("dragonfly")->setVisibility(true);
						dsr::EventView e;
						e.setDelta(false);
						e.setValue(0);
						e.setTargetId(543);
						WM.onEvent(&e);
						timer1->setTimer(30);
						state = 1;
					}
				}
				break;
			case 1: //in game
				break;
			case 2: //game over screen
				if (p_kbd->getKeyboardAction() == dsr::KEY_PRESSED) {
					if (p_kbd->getKey() == dsr::Keyboard::SPACE) {
						WM.getObjectById(111)->setVisibility(true);
						WM.getObjectById(222)->setVisibility(false);
						WM.getObjectByName("dragonfly")->setVisibility(false);
						WM.getObjectByName("dragonfly")->setSprite("dragonfly");
						m_soloud.fadeVolume(h1, 0.8,1.5);
						m_soloud.fadeVolume(h2, 0.8,1.5);
						state = 0;
						SM.sayText("Welcome to Dragonfly Says. Press P to play.", 2.0f);
					}
				}
				break;
			case 3:
				//score input
				if ((p_kbd->getKeyboardAction() == dsr::KEY_PRESSED)&&(p_kbd->getChar() != NULL)) {
					if (nameindex < 3) {
						namein[nameindex] = p_kbd->getChar();
						nameindex++;
						if (nameindex == 3) {
							std::string s = std::string(1, p_kbd->getChar());
							s += ". Great job ";
							s += namein[0];
							s += " ";
							s += namein[1];
							s += " ";
							s += namein[2];
							s += ". Welcome to Dragonfly Says. Press P to play.";
							SM.sayText(s.c_str(), 2.0f);
						}
						else {
							std::string s = std::string(1,p_kbd->getChar());
							SM.sayText(s.c_str(), 2.0f);
						}
					}
				}
				break;
			default:
				break;
			}
		}
		return 0;
	};

	void draw(int alt, bool important) override {
		switch (state) {
		case 0: //main menu
			break;
		case 1: //in game
			break;
		case 3:
			DM.drawStr(dsr::Vector2D(45, 8), "GREAT JOB!!", 0xFFFF00FF);
			DM.drawStr(dsr::Vector2D(43, 9), "INPUT YOUR NAME", 0xFFFFFFFF);
			DM.drawStr(dsr::Vector2D(47, 10), namein[0], 0xFFFFFFFF);
			DM.drawStr(dsr::Vector2D(49, 10), namein[1], 0xFFFFFFFF);
			DM.drawStr(dsr::Vector2D(51, 10), namein[2], 0xFFFFFFFF);
			break;
		default:
			break;
		}
		DM.drawStr(dsr::Vector2D(90, 21), "Dragonfly Says", 0xFFFFFFFF);
		DM.drawStr(dsr::Vector2D(1, 21), "FREE PLAY", 0xFFFFFFFF);
		WM.getObjectByName("cursor")->setPosition(m_cur_loc + DM.getCameraPosition());
		WM.getObjectByName("cursor")->draw(alt);
	};

};