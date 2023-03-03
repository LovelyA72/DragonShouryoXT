#include "SFML/Graphics.hpp"
#include <iostream>
#include <windows.h>
#include <sstream>
#include "DragonShouryo.h"
#include "Shouryo.h"
#include "MusicTrigger.h"
#include "Star.h"
#include "Bullet.h"
#include "TestTrigger.h"

using namespace dsr;

void exiting() {
    SM.shutDown();
}

int main()
{
    std::atexit(exiting);
    GM.startUp();
    
    std::cout << std::endl << "  _                _  "<<std::endl;
    std::cout << " / | __  _  _  _ / _`/_ _     _   _  " << std::endl;
    std::cout << "/_.'//_|/_//_// /._// //_//_///_//_/ " << std::endl;
    std::cout << "       _ /                   _ / " << std::endl;
    std::cout << "Hello World!\nDragonfly is loading...\n";
    // Configure sound source
    // initialize SoLoud.
    //SM.playMod("lhs_brd4.xm");
    //Vector2D vector = Vector2D(1, 2);
    //vector.scale(2);
    //printf("I have a Vector2D %s\n",vector.toString().c_str());
    //Testing LogManager
    LM.setFlush(true);
    //LM.writeLog("Hello world!");
    //LM.writeLog("My lucky number is %s", vector.toString().c_str());
    //Testing DsrObject operation
    MusicTrigger* mt = new MusicTrigger();
    mt->setId(111);
    mt->setSolidness(dsr::SPECTRAL);
    RM.loadSprite("spr-ship.ini", "ship");
    RM.loadSprite("spr-bullet.ini", "bullet");
    RM.loadSprite("spr-shiprev.ini","shipr");
    RM.loadSprite("spr-cursor.ini", "cursor");
    RM.loadSprite("spr-saucer.ini", "saucer");
    RM.getSprite("ship")->setTransparency(' ');
    RM.getSprite("saucer")->setTransparency(' ');
    RM.loadSound("fire.ogg","fire");
    RM.loadSound("explode.wav", "explode");
    RM.loadSound("nuke.wav", "nuke");
    RM.loadMusic("test.ogg","lets");
    TestTrigger* tt = new TestTrigger();
    tt->setId(12345);
    tt->setSolidness(dsr::SPECTRAL);
    Hud* hud = new Hud();
    hud->setViewString("Score: ");
    hud->setId(543);
    hud->setValue(0);
    hud->setLocation(dsr::TOP_CENTRE);
    hud->setBorder(true);
    hud->setColour(0xFFFFFFFF);
    Hud* hud2 = new Hud();
    hud2->setViewString("Nuke: ");
    hud2->setId(345);
    hud2->setValue(1);
    hud2->setLocation(dsr::TOP_RIGHT);
    hud2->setBorder(true);
    hud2->setColour(0xFFFF00FF);
    GM.run();
    GM.shutDown();
    LM.shutDown();
    return 0;
}
