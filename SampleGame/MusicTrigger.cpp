#include "MusicTrigger.h"

MusicTrigger::MusicTrigger() {
    //SM.loadBgm("test.ogg");
}

int MusicTrigger::eventHandler(const GameEvent* p_e)
{
    if (p_e->getType() == dsr::STEP_EVENT) {
        const dsr::EventStep* p_step =
            dynamic_cast <const dsr::EventStep*> (p_e);
        if (p_step->getStepCount() == 5) {
            SM.sayText("Welcome to Dragonfly.",1.4f);
        }
        if (p_step->getStepCount() == 50) {
            //SM.playBgm(1.0f);
            //SM.playMod("./getup2.mod", 0.6f);
            RM.getMusic("lets")->setVolume(0.5);
            RM.getMusic("lets")->play();
        }
        if (p_step->getStepCount() == 70) {
            SM.sayText("Press F to toggle FPS counter. Left click to fire.", 1.5f);
        }
        if (p_step->getStepCount() == 2630) {
            //WM.markForDelete(this);
        }
        return 0;
    }
    return 1;
}

MusicTrigger::~MusicTrigger()
{
    SM.stopAll();
}
