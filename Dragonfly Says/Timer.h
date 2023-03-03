#pragma once
#include "DragonShouryo.h"

class Timer : public dsr::DsrObject {
private:
	int time_left = 0;
public:
	Timer() {
		setSolidness(dsr::SPECTRAL);
	}
	void setTimer(int i) {
		time_left = i;
	}
	bool isFinished() {
		return !time_left;
	}
	int eventHandler(const dsr::Event* p_e) override {
		if (p_e->getType() == dsr::STEP_EVENT) {
			if (time_left>0) {
				time_left--;
			}
		}
		return 0;
	}
};