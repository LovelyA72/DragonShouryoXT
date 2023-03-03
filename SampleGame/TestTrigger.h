#pragma once
#include "DragonShouryo.h"
#include "ScoreEvent.h"
#include "Saucer.h"

class TestTrigger :public dsr::DsrObject {
private:
	int m_lyric_index = 0;
	int m_direction = 0;
	int score = 0;
	sf::Sprite spr;
	sf::Texture tex;
	float m_marquee_x = 1.0f;
	dsr::Vector2D m_cur_loc = dsr::Vector2D(0, 0);
	double rgbwheel = 0;
	dsr::Vector2D fbkloc = DM.spacesToPixels(dsr::Vector2D(60, 10));
	int m_timeframe[23] = { };
	std::string m_lyric[24] = {
		"Stop asking I don't watch Hololive(or any other VTuber)." };

	int rgb(double ratio)
	{
		//From stackoverflow...
		//Because RGB is pretty
		int normalized = int(ratio * 256 * 6);
		int region = normalized / 256;
		int x = normalized % 256;
		uint8_t r = 0, g = 0, b = 0;
		switch (region)
		{
		case 0: r = 255; g = 0;   b = 0;   g += x; break;
		case 1: r = 255; g = 255; b = 0;   r -= x; break;
		case 2: r = 0;   g = 255; b = 0;   b += x; break;
		case 3: r = 0;   g = 255; b = 255; g -= x; break;
		case 4: r = 0;   g = 0;   b = 255; r += x; break;
		case 5: r = 255; g = 0;   b = 255; b -= x; break;
		}
		return (255 + (b << 8) + (g << 16)+ (r << 24));
	}
public:
	TestTrigger() {
		tex.loadFromFile("./SampleGame_Data/fukutsu.png");
		tex.setSmooth(true);
		spr.setTexture(tex);
		spr.setScale(sf::Vector2f(0.4f, 0.4f));
		spr.setPosition(fbkloc.getX(), fbkloc.getY());
		setAlt(6);
	};
	int eventHandler(const dsr::Event* p_e) override {
		if (p_e->getType() == dsr::MSE_EVENT) {
			const dsr::EventMouse* p_mouse =
				dynamic_cast <const dsr::EventMouse*> (p_e);
			if (p_mouse->getMouseAction() == dsr::MOVED) {
				dsr::Vector2D loc = DM.pixelsToSpaces(dsr::Vector2D(p_mouse->getMousePosition().getX(), p_mouse->getMousePosition().getY()));
				m_cur_loc = loc;
			}
			else if (p_mouse->getMouseAction() == dsr::PRESSED) {
				if (p_mouse->getMouseButton() == dsr::Mouse::LEFT) {
					printf("Mouse left clicked!\n");
					RM.getSound("fire")->play();
					Bullet* b = new Bullet();
					b->setPosition(m_cur_loc+ DM.getCameraPosition());
				}
				if (p_mouse->getMouseButton() == dsr::Mouse::RIGHT) {
					printf("Mouse right clicked!\n");
				}
			}
			else if (p_mouse->getMouseAction() == dsr::RELEASED) {
				if (p_mouse->getMouseButton() == dsr::Mouse::LEFT) {
					printf("Mouse left released!\n");
				}
				if (p_mouse->getMouseButton() == dsr::Mouse::RIGHT) {
					printf("Mouse right released!\n");
				}
			}
		}
		if (p_e->getType() == dsr::KEYBOARD_EVENT) {
			const dsr::EventKeyboard* p_kbd =
				dynamic_cast <const dsr::EventKeyboard*> (p_e);
			if (p_kbd->getKeyboardAction() == dsr::KEY_PRESSED) {
				if (p_kbd->getKey() == dsr::Keyboard::F) {
					DM.toggleFPS();
				}
				if (p_kbd->getKey() == dsr::Keyboard::M) {
					LM.writeLogNoNL(",%d", GM.getFrameCounter());
				}
				if (p_kbd->getKey() == dsr::Keyboard::Q) {
					GM.setGameOver(true);
				}
				if (p_kbd->getKey() == dsr::Keyboard::C) {
					DM.setShowBox(!DM.getShowBox());
				}
				if (p_kbd->getKey() == dsr::Keyboard::SPACE) {
					//Hud *nukehud = 
					const dsr::Hud* p_hudnuke =
						dynamic_cast <const dsr::Hud*> (WM.getObjectById(345));
					if (p_hudnuke->getValue() > 0) {
						dsr::EventView* ev = new dsr::EventView();
						ev->setDelta(true);
						ev->setValue(-1);
						ev->setTargetId(345);
						WM.onEvent(ev);
						RM.getSound("nuke")->play();
						EventNuke* en = new EventNuke();
						WM.onEvent(en);
					}
				}
				//AWSD
				if (p_kbd->getKey() == dsr::Keyboard::A) {
					DM.setCameraPosition(DM.getCameraPosition()+dsr::Vector2D(-4,0));
				}
				if (p_kbd->getKey() == dsr::Keyboard::W) {
					DM.setCameraPosition(DM.getCameraPosition() + dsr::Vector2D(0, -2));
				}
				if (p_kbd->getKey() == dsr::Keyboard::S) {
					DM.setCameraPosition(DM.getCameraPosition() + dsr::Vector2D(0, 2));
				}
				if (p_kbd->getKey() == dsr::Keyboard::D) {
					DM.setCameraPosition(DM.getCameraPosition() + dsr::Vector2D(4, 0));
				}
			}
		}
		if (p_e->getType() == dsr::STEP_EVENT) {
			const dsr::EventStep* p_step =
				dynamic_cast <const dsr::EventStep*> (p_e);
			if (p_step->getStepCount() == 1) {
				DM.getWindow()->setTitle("DragonShouryo Sample Game");
				Shouryo* ship = new Shouryo();
				ship->setId(555);
				ship->setAlt(7);
				ship->setSprMode(1);
				ship->setSprite("cursor");
				ship->setPosition(m_cur_loc);
				ship->setSolidness(dsr::SPECTRAL);
				ship->setVelocity(dsr::Vector2D(0, 0));
			}
			if ((p_step->getStepCount() % 50)==0) {
				Saucer* ship = new Saucer();
				ship->setId(200000 + (rand() % 100000));
				ship->setAlt(6);
				ship->setSprMode(1);
				ship->setSprite("ship");
				ship->setPosition(dsr::Vector2D(-10, 10));
				ship->setSolidness(dsr::HARD);
				ship->setVelocity(dsr::Vector2D(1, 0));
			}
			if ((p_step->getStepCount() % 50) == 0) {
				Saucer* ship = new Saucer();
				ship->setId(200000 + (rand() % 100000));
				ship->setAlt(6);
				ship->setSprMode(1);
				ship->setSprite("saucer");
				ship->setPosition(dsr::Vector2D(120, 12));
				ship->setSolidness(dsr::HARD);
				ship->setVelocity(dsr::Vector2D(-1, 0));
			}
		}
		return 1;
	};
	void draw(int alt,bool important) override {
		if (alt == getAlt()) {
			char eol = '\0';
			int frameNow = GM.getFrameCounter();
			if (frameNow == 1) {
				for (int i = 0; i < 200; i++) {
					Star* starx = new Star();
					starx->setSolidness(dsr::SPECTRAL);
					starx->setId(100000 + (rand() % 100000));
					starx->setSprite(".");
					starx->setVelocity(dsr::Vector2D(-1.0 / (rand() % 10 + 1), 0));
					starx->setAlt(1);
					starx->setPosition(dsr::Vector2D(starx->random(0, 200), starx->random(0, 44)));
				}
			}
			if (frameNow % 80 == 0) {
				Shouryo* s1 = new Shouryo();
				s1->setId(60000 + (rand() % 100000));
				s1->setPosition(dsr::Vector2D(3, 6));
				s1->setSprite("L5");
				s1->setAlt(5);
				s1->setSolidness(dsr::HARD);
				s1->setVelocity(dsr::Vector2D(0.3, 0));
			}
			if (frameNow % 80 == 0) {
				Shouryo* s1 = new Shouryo();
				s1->setId(70000 + (rand() % 100000));
				s1->setPosition(dsr::Vector2D(80, 6));
				s1->setSprite("L4");
				s1->setAlt(4);
				s1->setSolidness(dsr::HARD);
				s1->setVelocity(dsr::Vector2D(-0.5, 0));
			}
			//Soft test
			if (frameNow % 75 == 0) {
				Shouryo* s1 = new Shouryo();
				s1->setId(60000 + (rand() % 100000));
				s1->setPosition(dsr::Vector2D(3, 8));
				s1->setSprite("SOFT1");
				s1->setAlt(5);
				s1->setSolidness(dsr::SOFT);
				s1->setVelocity(dsr::Vector2D(0.3, 0));
			}
			if (frameNow % 92 == 0) {
				Shouryo* s1 = new Shouryo();
				s1->setId(70000 + (rand() % 100000));
				s1->setPosition(dsr::Vector2D(80, 8));
				s1->setSprite("SOFT2");
				s1->setAlt(6);
				s1->setSolidness(dsr::SOFT);
				s1->setVelocity(dsr::Vector2D(-0.2, 0));
			}
			if (frameNow > 1) {
				if (m_marquee_x >= 10) {
					m_direction = 0;
				}
				if (m_marquee_x <= 1) {
					m_direction = 1;
				}
				if (m_direction) {
					m_marquee_x += 0.2;
				}
				else {
					m_marquee_x -= 0.2;
				}
				rgbwheel += 0.01;
				DM.drawCh(dsr::Vector2D(m_marquee_x, 1.0f) - DM.getCameraPosition(), 'P', rgb(fmod(rgbwheel ,1.0f)));
				DM.drawStr(dsr::Vector2D(1.0f, 2.0f) - DM.getCameraPosition(), "Welcome to DragonShouryo! Let's sing!", dsr::RED);
				//Sleep(300);
			}
			if (frameNow > 3) {
				DM.drawStr(dsr::Vector2D(1.0f, 3.0f) - DM.getCameraPosition(), "Press F to toggle FPS counter. C to toggle box(slow!). Q to quit. Left click to fire!", dsr::GREEN,' ');
			}
			if (frameNow > 5) {
				DM.drawStr(dsr::Vector2D(1.0f, 4.0f) - DM.getCameraPosition(), "If FPS counter is RED, the engine can't keep up. If it's GREEN, it's running fine!", dsr::CYAN);
			}
			for (int i : m_timeframe) {
				if (i == frameNow) {
					m_lyric_index++;
					printf("%d:%s\n", frameNow, m_lyric[m_lyric_index].c_str());
				}
			}
			DM.drawStr(dsr::Vector2D(1.0f, 7.0f) - DM.getCameraPosition(), m_lyric[m_lyric_index], dsr::YELLOW);
			if (frameNow == 20) {
				printf("Testing the 'can't keep up' warning\n");
				Sleep(40);
			}
			DM.drawBox(dsr::Box(dsr::Vector2D(1, 7)-DM.getCameraPosition(), 80, 1), 5, rgb(fmod(rgbwheel + 0.5f, 1.0f)));
			fbkloc = DM.spacesToPixels(dsr::Vector2D(60+m_marquee_x, 10));
			fbkloc = fbkloc - DM.spacesToPixels(DM.getCameraPosition());
			spr.setPosition(fbkloc.getX(),fbkloc.getY());
			DM.drawSprite(spr);
		}
		WM.getObjectById(555)->setPosition(m_cur_loc + DM.getCameraPosition());
		WM.getObjectById(555)->draw(alt);
	}
};