#include "InputManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

namespace dsr {
	Keyboard::Key InputManager::sfmlToDsrKey(sf::Event* p_event)
	{
		switch (p_event->key.code) {
		case sf::Keyboard::A:
			return Keyboard::A;
		case sf::Keyboard::B:
			return Keyboard::B;
		case sf::Keyboard::C:
			return Keyboard::C;
		case sf::Keyboard::D:
			return Keyboard::D;
		case sf::Keyboard::E:
			return Keyboard::E;
		case sf::Keyboard::F:
			return Keyboard::F;
		case sf::Keyboard::G:
			return Keyboard::G;
		case sf::Keyboard::H:
			return Keyboard::H;
		case sf::Keyboard::I:
			return Keyboard::I;
		case sf::Keyboard::J:
			return Keyboard::J;
		case sf::Keyboard::K:
			return Keyboard::K;
		case sf::Keyboard::L:
			return Keyboard::L;
		case sf::Keyboard::M:
			return Keyboard::M;
		case sf::Keyboard::N:
			return Keyboard::N;
		case sf::Keyboard::O:
			return Keyboard::O;
		case sf::Keyboard::P:
			return Keyboard::P;
		case sf::Keyboard::Q:
			return Keyboard::Q;
		case sf::Keyboard::R:
			return Keyboard::R;
		case sf::Keyboard::S:
			return Keyboard::S;
		case sf::Keyboard::T:
			return Keyboard::T;
		case sf::Keyboard::U:
			return Keyboard::U;
		case sf::Keyboard::V:
			return Keyboard::V;
		case sf::Keyboard::W:
			return Keyboard::W;
		case sf::Keyboard::X:
			return Keyboard::X;
		case sf::Keyboard::Y:
			return Keyboard::Y;
		case sf::Keyboard::Z:
			return Keyboard::Z;
		case sf::Keyboard::Space:
			return Keyboard::SPACE;
		case sf::Keyboard::Return:
			return Keyboard::RETURN;
		case sf::Keyboard::Up:
			return Keyboard::UPARROW;
		case sf::Keyboard::Down:
			return Keyboard::DOWNARROW;
		case sf::Keyboard::Left:
			return Keyboard::LEFTARROW;
		case sf::Keyboard::Right:
			return Keyboard::RIGHTARROW;
		default:
			return Keyboard::UNDEFINED_KEY;
		};
	}
	InputManager& InputManager::getInstance()
	{
		static InputManager single;
		return single;
	}
	InputManager::InputManager() {
	}
	int InputManager::startUp()
	{
		if (!DM.isStarted()) {
			return -1;
		}
		p_window = DM.getWindow();
		m_is_started = true;
		return 0;
	}
	void InputManager::shutDown()
	{
		m_is_started = false;
	}
	void InputManager::getInput()
	{
		if (!p_window) {
			return;
		}
		sf::Event event;
		while (p_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				GM.setGameOver(true);
			}
			else if (event.type == sf::Event::KeyPressed) {
				EventKeyboard kbd;
				kbd.setKey(sfmlToDsrKey(&event));
				kbd.setKeyboardAction(KEY_PRESSED);
				onEvent(&kbd);
			}
			else if (event.type == sf::Event::KeyReleased) {
				EventKeyboard kbd;
				kbd.setKey(sfmlToDsrKey(&event));
				kbd.setKeyboardAction(KEY_RELEASED);
				onEvent(&kbd);
			}
			else if (event.type == sf::Event::MouseMoved) {
				EventMouse mouse;
				Vector2D mseloc = Vector2D(event.mouseMove.x, event.mouseMove.y);
				mouse.setMouseAction(MOVED);
				mouse.setMousePosition(mseloc);
				onEvent(&mouse);
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				EventMouse mouse;
				//Vector2D mseloc = Vector2D(event.mouseMove.x, event.mouseMove.y);
				mouse.setMouseAction(PRESSED);
				if (event.mouseButton.button == sf::Mouse::Left) {
					mouse.setMouseButton(Mouse::LEFT);
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					mouse.setMouseButton(Mouse::RIGHT);
				}
				//mouse.setMousePosition(mseloc);
				onEvent(&mouse);
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				EventMouse mouse;
				//Vector2D mseloc = Vector2D(event.mouseMove.x, event.mouseMove.y);
				mouse.setMouseAction(RELEASED);
				if (event.mouseButton.button == sf::Mouse::Left) {
					mouse.setMouseButton(Mouse::LEFT);
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					mouse.setMouseButton(Mouse::RIGHT);
				}
				//mouse.setMousePosition(mseloc);
				onEvent(&mouse);
			}
		};
	}
}