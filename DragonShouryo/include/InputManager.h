#pragma once
#include "Manager.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"


#define IM dsr::InputManager::getInstance()
namespace dsr {
	class InputManager : public Manager {

	private:
		sf::RenderWindow* p_window;
		InputManager();
		InputManager(InputManager const&);
		void operator=(InputManager const&);

	public:
		// Get the one and only instance of the InputManager.
		__declspec(dllexport) static InputManager& getInstance();

		// Get terminal ready to capture input.
		// Return 0 if ok, else return -1.
		__declspec(dllexport) int startUp();

		// Revert back to normal terminal mode.
		__declspec(dllexport) void shutDown();

		// Get input from the keyboard and mouse.
		// Pass event along to all Objects.
		__declspec(dllexport) void getInput();

		__declspec(dllexport) Keyboard::Key sfmlToDsrKey(sf::Event* p_event);
	};
}