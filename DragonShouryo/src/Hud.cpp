#include "Hud.h"
#include "EventView.h"
#include "DisplayManager.h"
#include "WorldManager.h"

namespace dsr {
	Hud::Hud()
	{
		setSolidness(SPECTRAL);
		location = Vector2D(2, 2);
	}
	void Hud::draw(int alt, bool important)
	{
		std::string result = "";
		if (value == (int)value) {
			result = view_string + std::to_string((int)value);
		}
		else {
			result = view_string + std::to_string(value);
		}
		if (border) {
			Vector2D pos = location + Vector2D(1, 0);
			DM.drawStr(pos, result, colour);
		}
		else {
			DM.drawStr(location, result, colour);
		}
		if (border) {
			Box box(location, result.length() + 4, 1);
			DM.drawBox(box, 3, colour);
		}
	}
	int Hud::eventHandler(const Event* p_e)
	{
		if (p_e->getType() == VIEW_EVENT) {
			const dsr::EventView* p_view =
				dynamic_cast <const dsr::EventView*> (p_e);
			if (p_view->getTargetId() == getId()) {
				if (p_view->getDelta()) {
					value += p_view->getValue();
				}
				else {
					value = p_view->getValue();
				}
			}
		}
		return 0;
	}
	void Hud::setLocationExact(Vector2D vec) {
		location = vec;
	}
	void Hud::setLocation(HudLocation new_location)
	{
		switch (new_location) {
		case TOP_LEFT:
			location = Vector2D(1,1);
			break;
		case TOP_CENTRE:
			location = Vector2D(40, 1);
			break;
		case TOP_RIGHT:
			location = Vector2D(80, 1);
			break;
		case CENTRE_LEFT:
			location = Vector2D(1, 10);
			break;
		case CENTRE_CENTRE:
			location = Vector2D(40, 10);
			break;
		case CENTRE_RIGHT:
			location = Vector2D(80, 10);
			break;
		case BOTTOM_LEFT:
			location = Vector2D(1, 20);
			break;
		case BOTTOM_CENTRE:
			location = Vector2D(40, 20);
			break;
		case BOTTOM_RIGHT:
			location = Vector2D(80, 20);
			break;
		default:
			break;
		}
	}
	void Hud::setValue(float new_value)
	{
		value = new_value;
	}
	float Hud::getValue() const
	{
		return value;
	}
	void Hud::setBorder(bool new_border)
	{
		border = new_border;
	}
	bool Hud::getBorder()
	{
		return border;
	}
	void Hud::setColour(int new_colour)
	{
		colour = new_colour;
	}
	int Hud::getColour() const
	{
		return colour;
	}
	void Hud::setViewString(std::string new_view_string)
	{
		view_string = new_view_string;
	}
	std::string Hud::getViewString() const
	{
		return view_string;
	}
}