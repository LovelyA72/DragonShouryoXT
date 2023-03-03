#pragma once
#include "Manager.h"
#include "soloud.h"
#include "soloud_speech.h"
#include "soloud_openmpt.h"
#include "soloud_lofifilter.h"
#include "soloud_tedsid.h"
#include "soloud_wav.h"
#include "soloud_vizsn.h"

#define SM dsr::SynthManager::getInstance()

namespace dsr {
	class SynthManager : public Manager {
	public:
		__declspec(dllexport) static SynthManager& getInstance();
		__declspec(dllexport) void shutDown() override;
		__declspec(dllexport) void stopAll();
		__declspec(dllexport) int playMod(const char* file, float volume = 1.0f);
		__declspec(dllexport) int playSid(const char* file, float volume = 1.0f);
		__declspec(dllexport) int loadBgm(const char* file);
		__declspec(dllexport) int playBgm(float volume = 1.0f);
		__declspec(dllexport) int sayText(const char* text, float volume = 1.0f);
		__declspec(dllexport) SoLoud::Soloud* getDriver();
	private:
		SynthManager();                      // Private (a singleton).
		SynthManager(SynthManager const&);   // No copying.
		void operator=(SynthManager const&); // No assignment.
		bool m_bgmLoaded = false;
		SoLoud::Soloud m_soloud;  // SoLoud engine core
		SoLoud::Openmpt m_mod;
		SoLoud::Wav m_wav;
		SoLoud::Speech m_speech;
		SoLoud::LofiFilter m_speechFilter;
		SoLoud::TedSid m_sid;
		SoLoud::Vizsn m_viz;

	};
}