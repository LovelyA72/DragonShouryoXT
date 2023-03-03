#pragma once
///
/// The game manager
///
#include "SFML/Graphics.hpp"
#include "Manager.h"

#define DF_VERSION 4.16		/// Dragonfly version
const std::string DSR_VERSION = "1.2";		/// DragonShouryo version

// Two-letter acronym for easier access to manager.
#define GM dsr::GameManager::getInstance()

namespace dsr {

	/// Default DragonShouryo cofiguration file.
	/// Override with DSR_CONFIG environment variable.
	const std::string CONFIG_FILENAME = "dsr-config.ini";

	/// Default frame time (game loop time) in milliseconds (33 ms == 30 f/s).
	const int FRAME_TIME_DEFAULT = 33;

	class GameManager : public Manager {

	private:
		GameManager();                      // Private (a singleton).
		GameManager(GameManager const&);   // No copying.
		void operator=(GameManager const&); // No assignment.
		bool m_game_over;       // True, then game loop should stop.
		int m_frame_counter;
		int m_frame_time_spent;

	public:
		// Get the singleton instance of the GameManager.
		__declspec(dllexport) static GameManager& getInstance();
		// Startup all GameManager services.
		__declspec(dllexport) int startUp();

		// Shut down GameManager services.
		__declspec(dllexport) void shutDown();

		// Run game loop.
		__declspec(dllexport) void run();

		// Set game over status to indicated value.
		// If true (the default), will stop game loop.
		__declspec(dllexport) void setGameOver(bool game_over = true);

		// Get game over status.
		__declspec(dllexport) bool getGameOver() const;

		// Get game over status.
		__declspec(dllexport) int getFrameCounter() const;

		// Return frame time.
		// Frame time is target time for game loop, in milliseconds.
		__declspec(dllexport) int getFrameTime() const;
	};

} // end of namespace dsr
