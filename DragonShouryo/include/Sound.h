#pragma once
#include "SynthManager.h"

namespace dsr {
	class Sound {
	private:
		SoLoud::Wav m_wav;
		bool m_loaded = false;
		std::string m_label = "";
	public:
		__declspec(dllexport) Sound();
		__declspec(dllexport) int loadSound(std::string filename);
		__declspec(dllexport) void setLabel(std::string str);
		__declspec(dllexport) void setVolume(float f);
		__declspec(dllexport) std::string getLabel();
		__declspec(dllexport) void play();
		__declspec(dllexport) void stop();
	};
}