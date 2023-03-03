#include "Music.h"

namespace dsr {
	Music::Music()
	{
	}
	int Music::loadSound(std::string filename)
	{
		SoLoud::result loaded = m_wav.load(filename.c_str());
		if (loaded == SoLoud::SO_NO_ERROR) {
			m_wav.setLooping(true);
			m_loaded = 1;
			return 0;
		}
		return -1;
	}
	void Music::setLabel(std::string str)
	{
		m_label = str;
	}

	void Music::setVolume(float f)
	{
		m_wav.setVolume(f);
	}

	std::string Music::getLabel()
	{
		return m_label;
	}

	void Music::play()
	{
		if (m_loaded) {
			SM.getDriver()->play(m_wav);
		}
	}

	void Music::stop()
	{
		m_wav.stop();
	}
}


