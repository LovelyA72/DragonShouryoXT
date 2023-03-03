#pragma once
#include "Manager.h"
#include "GameSprite.h"
#include "SynthManager.h"
#include "Sound.h"
#include "Music.h"

#include <Shlwapi.h>

#define RM dsr::ResourceManager::getInstance()

namespace dsr {

	const int MAX_SPRITES = 500;
	const int MAX_SFX = 128;
	const int MAX_BGM = 32;

	// The ResourceManager singleton.
	class ResourceManager : public Manager {

	private:
		ResourceManager();
		ResourceManager(ResourceManager const&);
		void operator=(ResourceManager const&);
		GameSprite* p_sprite[MAX_SPRITES];
		Sound* p_sfxs[MAX_SFX+4];
		Music* p_bgms[MAX_BGM+4];
		int sprite_count;
		int sfx_count;
		int bgm_count;
		std::string data_path = "";

	public:
		__declspec(dllexport) ~ResourceManager();
		__declspec(dllexport) std::string getDataPath();
		__declspec(dllexport) static ResourceManager& getInstance();
		__declspec(dllexport) int startUp();
		__declspec(dllexport) void shutDown();
		__declspec(dllexport) int loadMusic(std::string filename, std::string label);
		__declspec(dllexport) int loadSound(std::string filename, std::string label);
		__declspec(dllexport) int loadSprite(std::string filename, std::string label);
		__declspec(dllexport) int unloadSprite(std::string label);
		__declspec(dllexport) GameSprite* getSprite(std::string label) const;
		__declspec(dllexport) Sound* getSound(std::string label) const;
		__declspec(dllexport) Music* getMusic(std::string label) const;
	};
}