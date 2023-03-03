#pragma once
#include "DragonShouryo.h"

class Shouryo : public dsr::DsrObject {

public:
    Shouryo();
    ~Shouryo();
    int eventHandler(const GameEvent* p_e) override;
};