#include "EventKeyboard.h"
#include "SFML/Graphics.hpp"

namespace dsr {
    EventKeyboard::EventKeyboard()
    {
        setType(KEYBOARD_EVENT);
    }
    void EventKeyboard::setKey(Keyboard::Key new_key)
    {
        m_key_val = new_key;
    }

    Keyboard::Key EventKeyboard::getKey() const
    {
        return m_key_val;
    }

    void EventKeyboard::setKeyboardAction(EventKeyboardAction new_action)
    {
        m_keyboard_action = new_action;
    }

    EventKeyboardAction EventKeyboard::getKeyboardAction() const
    {
        return m_keyboard_action;
    }

    char EventKeyboard::getChar() const
    {
		switch (m_key_val) {
		case Keyboard::A:
			return 'A';
		case Keyboard::B:
			return 'B';
		case Keyboard::C:
			return 'C';
		case Keyboard::D:
			return 'D';
		case Keyboard::E:
			return 'E';
		case Keyboard::F:
			return 'F';
		case Keyboard::G:
			return 'G';
		case Keyboard::H:
			return 'H';
		case Keyboard::I:
			return 'I';
		case Keyboard::J:
			return 'J';
		case Keyboard::K:
			return 'K';
		case Keyboard::L:
			return 'L';
		case Keyboard::M:
			return 'M';
		case Keyboard::N:
			return 'N';
		case Keyboard::O:
			return 'O';
		case Keyboard::P:
			return 'P';
		case Keyboard::Q:
			return 'Q';
		case Keyboard::R:
			return 'R';
		case Keyboard::S:
			return 'S';
		case Keyboard::T:
			return 'T';
		case Keyboard::U:
			return 'U';
		case Keyboard::V:
			return 'V';
		case Keyboard::W:
			return 'W';
		case Keyboard::X:
			return 'X';
		case Keyboard::Y:
			return 'Y';
		case Keyboard::Z:
			return 'Z';
		case Keyboard::SPACE:
			return ' ';
		default:
			return NULL;
		};
    }
}