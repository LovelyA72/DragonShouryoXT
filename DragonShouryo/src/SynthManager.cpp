#include "SynthManager.h"

namespace dsr {

	SynthManager::SynthManager() {
		m_speechFilter.setParams(6000,4);
		m_soloud.init();
		m_speech.setFilter(0,&m_speechFilter);
	}

	SynthManager& SynthManager::getInstance()
	{
		static SynthManager single;
		return single;
	}
	void SynthManager::shutDown()
	{
		m_is_started = false;
		m_soloud.deinit();
	}
	void SynthManager::stopAll()
	{
		m_soloud.stopAll();
	}
	int SynthManager::playMod(const char* file,float volume)
	{
		SoLoud::result loaded = m_mod.load(file);
		if (loaded == SoLoud::SO_NO_ERROR) {
			m_mod.stop();
			m_mod.setVolume(volume);
			m_mod.setLooping(true);
			m_mod.setLoopPoint(0);
			m_soloud.play(m_mod);
			return 0;
		}
		return -1;
	}
	int SynthManager::playSid(const char* file, float volume)
	{
		SoLoud::result loaded = m_sid.load(file);
		if (loaded == SoLoud::SO_NO_ERROR) {
			m_sid.stop();
			m_sid.setVolume(volume);
			m_soloud.play(m_sid);
			return 0;
		}
		return -1;
	}
	int SynthManager::loadBgm(const char* file)
	{
		m_wav.stop();
		SoLoud::result loaded = m_wav.load(file);
		if (loaded == SoLoud::SO_NO_ERROR) {
			m_bgmLoaded = true;
		}
		return 0;
	}
	int SynthManager::playBgm(float volume)
	{
		if (m_bgmLoaded) {
			m_wav.stop();
			m_wav.setVolume(volume);
			m_wav.setLooping(true);
			m_wav.setLoopPoint(0);
			m_soloud.play(m_wav);
		}
		return 0;
	}
	int SynthManager::sayText(const char* text, float volume)
	{
		m_speech.stop();
		m_speech.setVolume(volume*1.0f);
		m_speech.setText(text);
		m_soloud.play(m_speech);
		return 0;
	}
	SoLoud::Soloud* SynthManager::getDriver()
	{
		return &m_soloud;
	}
}