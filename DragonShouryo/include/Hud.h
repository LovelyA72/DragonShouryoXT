#pragma once
#include "DsrObject.h"
#include "Event.h"

namespace dsr {
	enum HudLocation {
		TOP_LEFT, TOP_CENTRE, TOP_RIGHT,
		CENTRE_LEFT, CENTRE_CENTRE, CENTRE_RIGHT,
		BOTTOM_LEFT, BOTTOM_CENTRE, BOTTOM_RIGHT,
	};

	class Hud : public DsrObject {
	private:
		std::string view_string;     // Label for value (e.g., "Points").
		float value;                   // Value displayed (e.g., points).
		bool border;                 // True if border around display.
		int colour;                 // Colour for text.
		Vector2D location; // Location of ViewObject.	

	public:
		// Object settings: SPECTRAL, max alt.
	   // ViewObject defaults: border, top_centre, default colour.
		__declspec(dllexport) Hud();

		// Draw view string and value.
		__declspec(dllexport) virtual void draw(int alt, bool important) override;
		// Handle `view' event if tag matches view_string (others ignored).
		// Return 0 if ignored, else 1 if handled.
		__declspec(dllexport) virtual int eventHandler(const Event* p_e);

		__declspec(dllexport) void setLocationExact(Vector2D vec);

		// General location of ViewObject on screen.
		__declspec(dllexport) void setLocation(HudLocation new_location);

		// Set/get view value.
		__declspec(dllexport) void setValue(float new_value);
		__declspec(dllexport) float getValue() const;

		// Set/get view border (true = display border).
		__declspec(dllexport) void setBorder(bool new_border);
		__declspec(dllexport) bool getBorder();

		// Set/get view colour.
		__declspec(dllexport) void setColour(int new_colour);
		__declspec(dllexport) int getColour() const;

		// Set/get view display string.
		__declspec(dllexport) void setViewString(std::string new_view_string);
		__declspec(dllexport) std::string getViewString() const;
	};
}