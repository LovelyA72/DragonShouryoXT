#include "Sound.h"

namespace dsr {
	Sound::Sound()
	{
	}
	int Sound::loadSound(std::string filename)
	{
		SoLoud::result loaded = m_wav.load(filename.c_str());
		if (loaded == SoLoud::SO_NO_ERROR) {
			m_loaded = 1;
			m_wav.setLooping(false);
			return 0;
		}
		return -1;
	}

	void Sound::setLabel(std::string str)
	{
		m_label = str;
	}

	void Sound::setVolume(float f)
	{
		m_wav.setVolume(f);
	}

	std::string Sound::getLabel()
	{
		return m_label;
	}

	void Sound::play()
	{
		if (m_loaded) {
			SM.getDriver()->play(m_wav);
		}
	}

	void Sound::stop()
	{
		if (m_loaded) {
			m_wav.stop();
		}
	}
}


