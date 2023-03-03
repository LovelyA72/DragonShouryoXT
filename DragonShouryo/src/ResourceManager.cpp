#include "ResourceManager.h"
#include "LogManager.h"
#include <cstdarg>
#include "mini/ini.h"

namespace dsr {
	ResourceManager::ResourceManager()
	{
		char buf[MAX_PATH];
		GetModuleFileNameA(nullptr, buf, MAX_PATH);
		std::string temp = std::string(buf);
		temp = temp.substr(temp.find_last_of("/\\") + 1);
		temp = temp.substr(0, temp.size() - 4);
		data_path = "./" + temp + "_Data/";
#if DEBUG
		printf("Data path: %s\n", data_path.c_str());
#endif
	}
	ResourceManager::~ResourceManager()
	{

	}

	std::string ResourceManager::getDataPath() {
		return data_path;
	}
	ResourceManager& ResourceManager::getInstance()
	{
		static ResourceManager single;
		return single;
	}
	int ResourceManager::startUp()
	{
		//LM.writeLog("ResourceManager starting up...");
		return 0;
	}
	void ResourceManager::shutDown()
	{
		//LM.writeLog("ResourceManager shutting down...");
		bgm_count = 0;
		sfx_count = 0;
		sprite_count = 0;
	}
	inline bool ifFileExists(const std::string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}
	int ResourceManager::loadMusic(std::string filename, std::string label) {
		filename = data_path + filename;
		if (!ifFileExists(filename)) {
			return -1;
		}
		if (bgm_count >= MAX_BGM) {
			return -1;
		}
		Music* mus = new Music();
		if (mus->loadSound(filename) == 0) {
			mus->setLabel(label);
			p_bgms[bgm_count] = mus;
			bgm_count++;
		}
	}
	int ResourceManager::loadSound(std::string filename, std::string label) {
		filename = data_path + filename;
		if (!ifFileExists(filename)) {
			return -1;
		}
		if (sfx_count >= MAX_SFX) {
			return -1;
		}
		Sound* snd = new Sound();
		if (snd->loadSound(filename) == 0) {
			snd->setLabel(label);
			p_sfxs[sfx_count] = snd;
			sfx_count++;
#if DEBUG
			printf("Loaded SFX %s\n",filename.c_str());
#endif
		}
	}
	int ResourceManager::loadSprite(std::string filename, std::string label)
	{
		filename = data_path + filename;
		if (!ifFileExists(filename)) {
			printf("Sprite file %s not found\n", (filename).c_str());
			return -1;
		}
#if DEBUG
		printf("Loading sprite file %s\n", filename.c_str());
#endif
		//FILE *f = _fsopen(filename.c_str(), "r", _SH_DENYWR);
		mINI::INIFile f(filename);
		mINI::INIStructure ini;
		f.read(ini);
		int sprtype = std::stoi(ini["meta"]["type"]);
		int frames = std::stoi(ini["meta"]["frames"]);
		int height = std::stoi(ini["meta"]["height"]);
		int width = std::stoi(ini["meta"]["width"]);
		int slowdown = std::stoi(ini["meta"]["slowdown"]);
#if DEBUG
		printf("Sprite %s has %d frames. Width %d height %d\n", label.c_str(), frames,width,height);
#endif
		GameSprite* sprite = new GameSprite(frames);
		if (sprtype) {
			for (int i = 0; i < frames; i++) {
				Frame* fr = new Frame();
#if DEBUG
				printf("Frame %d:\n", i);
#endif
				fr->setWidth(width);
				std::string spr_file = ini["frame" + std::to_string(i)]["file"];
				fr->loadTexture(data_path + spr_file);
				sprite->addFrame(*fr);
			}
		}
		else {
			int colour = std::stoll(ini["meta"]["colour"], nullptr, 16);
			sprite->setColour(colour);
			for (int i = 0; i < frames; i++) {
				Frame* fr = new Frame();
#if DEBUG
				printf("Frame %d:\n", i);
#endif
				fr->setWidth(width);
				for (int j = 0; j < height; j++) {
					std::string line = (j > 10 ? std::to_string(j) : "0" + std::to_string(j));
					std::string result = ini["frame" + std::to_string(i)][line];
					if ((result.back() != '"') || (result.front() != '"')) {
						printf("Warning: line %d of sprite %s's frame %d is not encased in double quote sign! Leading and ending whitespaces will get removed.\n", j, label.c_str(), i);
					}
					else {
						result.erase(0, 1);
						result.erase(result.size() - 1);
					}
					fr->addLine(result);
#if DEBUG
					printf("%s\n", result.c_str());
#endif
				}
				sprite->addFrame(*fr);
			}
		}
		sprite->setHeight(height);
		sprite->setWidth(width);
		sprite->setLabel(label);
		sprite->setSlowdown(slowdown);
		p_sprite[sprite_count] = sprite;
		sprite_count++;
		return 0;
	}
	int ResourceManager::unloadSprite(std::string label)
	{
		return 0;
	}
	GameSprite* ResourceManager::getSprite(std::string label) const
	{
		for (int i = 0; i < sprite_count; i++) {
			if (p_sprite[i]->getLabel() == label) {
				return p_sprite[i];
			}
		}
		return nullptr;
	}
	Sound* ResourceManager::getSound(std::string label) const
	{
		for (int i = 0; i < sfx_count; i++) {
			if (p_sfxs[i]->getLabel() == label) {
				return p_sfxs[i];
			}
		}
		return nullptr;
	}
	Music* ResourceManager::getMusic(std::string label) const
	{
		for (int i = 0; i < bgm_count; i++) {
			if (p_bgms[i]->getLabel() == label) {
				return p_bgms[i];
			}
		}
		return nullptr;
	}
}