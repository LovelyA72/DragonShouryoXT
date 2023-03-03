// Dragonfly Says.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DragonShouryo.h"
#include "GameLogic.h"
#include "DragonflySprite.h"

void populateWorld() {
	//Spawn cursor
	dsr::DsrObject* cursor = new dsr::DsrObject();
	cursor->setId(555);
	cursor->setName("cursor");
	cursor->setAlt(7);
	cursor->setSprMode(1);
	cursor->setSprite("cursor");
	cursor->setSolidness(dsr::SPECTRAL);
	cursor->setVelocity(dsr::Vector2D(0, 0));
	//Spawn timer
	Timer* tim1 = new Timer();
	tim1->setName("timer1");
	//Spawn title
	dsr::DsrObject* title = new dsr::DsrObject();
	title->setSolidness(dsr::SPECTRAL);
	title->setSprMode(1);
	title->setSprite("title");
	title->setAlt(3);
	title->setPosition(dsr::Vector2D(12, 5));
	title->setId(111);
	//Spawn game over for later
	DsrObject* gameover = new DsrObject();
	gameover->setSolidness(SPECTRAL);
	gameover->setSprMode(1);
	gameover->setSprite("gameover");
	gameover->setAlt(3);
	gameover->setPosition(dsr::Vector2D(23, 7.5));
	gameover->setId(222);
	gameover->setVisibility(false);
	//Spawn buttons
	Button* btnd = new Button(3);
	//btnd->setVisibility(false);
	btnd->setSprite("d");
	btnd->setName("d-btn");
	btnd->setSprMode(1);
	btnd->setPosition(dsr::Vector2D(55, 9));
	btnd->setAlt(4);
	Button* btnw = new Button(0);
	//btnw->setVisibility(false);
	btnw->setSprite("w");
	btnw->setName("w-btn");
	btnw->setSprMode(1);
	btnw->setPosition(dsr::Vector2D(45, 3.5));
	btnw->setAlt(4);
	Button* btna = new Button(1);
	//btna->setVisibility(false);
	btna->setSprite("a");
	btna->setName("a-btn");
	btna->setSprMode(1);
	btna->setPosition(dsr::Vector2D(35, 9));
	btna->setAlt(4);
	Button* btns = new Button(2);
	//btns->setVisibility(false);
	btns->setSprite("s");
	btns->setName("s-btn");
	btns->setSprMode(1);
	btns->setPosition(dsr::Vector2D(45, 9));
	btns->setAlt(4);
	//Spawn mouse buttons for later
	Button* btnl = new Button(4);
	btnl->setSprite("l");
	btnl->setName("l-btn");
	btnl->setSprMode(1);
	btnl->setPosition(dsr::Vector2D(10, 5));
	btnl->setAlt(4);
	btnl->setVisibility(false);
	Button* btnr = new Button(5);
	btnr->setSprite("r");
	btnr->setName("r-btn");
	btnr->setSprMode(1);
	btnr->setPosition(dsr::Vector2D(80, 5));
	btnr->setAlt(4);
	btnr->setVisibility(false);
	//Spawn dragonfly
	DragonflySprite* dragonfly = new DragonflySprite();
	dragonfly->setSprite("dragonfly");
	dragonfly->setName("dragonfly");
	dragonfly->setSprMode(1);
	dragonfly->setPosition(Vector2D(44.5, 15));
	dragonfly->setAlt(4);
	//Hide buttons
	btnw->setVisibility(false);
	btna->setVisibility(false);
	btns->setVisibility(false);
	btnd->setVisibility(false);
	dragonfly->setVisibility(false);
	//Spawn stars
	for (int i = 0; i < 200; i++) {
		Star* starx = new Star();
		starx->setSolidness(dsr::SPECTRAL);
		starx->setId(100000 + (rand() % 100000));
		starx->setSprite(".");
		starx->setVelocity(dsr::Vector2D(-1.0 / (rand() % 10 + 1), 0));
		starx->setAlt(1);
		starx->setPosition(dsr::Vector2D(starx->random(0, 200), starx->random(0, 44)));
	}
	dsr::Hud* hud = new dsr::Hud();
	hud->setViewString("Score: ");
	hud->setId(543);
	hud->setName("scorehud");
	hud->setValue(0);
	hud->setLocation(dsr::TOP_LEFT);
	hud->setBorder(true);
	hud->setColour(0x00FF00FF);
	dsr::Hud* hud2 = new dsr::Hud();
	hud2->setViewString("Level: ");
	hud2->setId(654);
	hud2->setValue(0);
	hud2->setName("levelhud");
	hud2->setLocation(dsr::TOP_RIGHT);
	hud2->setBorder(true);
	hud2->setColour(0xFFFFFFFF);
	dsr::Hud* hud3 = new dsr::Hud();
	hud3->setViewString("Hi (name): ");
	hud3->setId(765);
	hud3->setValue(0);
	hud3->setName("hiscorehud");
	hud3->setLocation(dsr::TOP_CENTRE);
	hud3->setBorder(true);
	hud3->setColour(0xFFFF00FF);
}

int main()
{
    GM.startUp();
    RM.loadSprite("sprites/spr-button-a.ini", "a");
	RM.loadSprite("sprites/spr-button-w.ini", "w");
	RM.loadSprite("sprites/spr-button-s.ini", "s");
	RM.loadSprite("sprites/spr-button-d.ini", "d");
	RM.loadSprite("sprites/spr-button-a-pressed.ini", "A");
	RM.loadSprite("sprites/spr-button-w-pressed.ini", "W");
	RM.loadSprite("sprites/spr-button-s-pressed.ini", "S");
	RM.loadSprite("sprites/spr-button-d-pressed.ini", "D");
	RM.loadSprite("sprites/spr-dragonfly.ini", "dragonfly");
	RM.loadSprite("sprites/spr-dragonflyfast.ini", "fastfly");
	RM.loadSprite("sprites/spr-dragonflylose.ini", "angryfly");
	RM.loadSprite("sprites/spr-button-l.ini", "l");
	RM.loadSprite("sprites/spr-button-l-pressed.ini", "L");
	RM.loadSprite("sprites/spr-button-r.ini", "r");
	RM.loadSprite("sprites/spr-button-r-pressed.ini", "R");
	RM.loadSound("samples/W.ogg", "w");
	RM.loadSound("samples/A.ogg", "a");
	RM.loadSound("samples/S.ogg", "s");
	RM.loadSound("samples/D.ogg", "d");
	RM.loadSound("samples/L.ogg", "l");
	RM.loadSound("samples/R.ogg", "r");
	RM.loadSound("samples/correct.ogg", "correct");
	RM.loadSound("samples/levelup.ogg", "lvup");
	RM.loadSound("samples/gameover.ogg", "over");
	//RM.loadMusic("samples/bgm-loop.ogg", "bgm");
	//RM.loadMusic("samples/bgm-loop2.ogg", "bgm2");
	RM.loadSprite("sprites/spr-title.ini", "title");
	RM.loadSprite("sprites/spr-gameover.ini", "gameover");
    RM.loadSprite("spr-cursor.ini", "cursor");
	populateWorld();
    GameLogic* gm = new GameLogic();
    GM.run();
    GM.shutDown();
}