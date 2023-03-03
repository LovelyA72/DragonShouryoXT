#pragma once
// System includes.
#include <string>
#include "SFML/Graphics.hpp"

// Engine includes.
#include "Vector2D.h"

namespace dsr {

	class Frame {

	private:
		int m_width;             ///< Width of frame
		int m_linecount = 0;
		int m_graphical = 0;
		sf::Texture m_graphical_texture;
		sf::Sprite m_graphical_sprite;
		std::string* m_frame_str; ///< All frame characters stored as string.

	public:
		/// Create empty frame.
		__declspec(dllexport) Frame();

		/// Create frame of indicated width and height with string.
		__declspec(dllexport) Frame(int new_width);

		/// Set width of frame.
		__declspec(dllexport) void setWidth(int new_width);

		/// Get width of frame.
		__declspec(dllexport) int getWidth() const;

		/// Get height of frame.
		__declspec(dllexport) int getHeight() const;

		/// Set frame characters (stored as string).
		__declspec(dllexport) int getLineCount();

		__declspec(dllexport) void loadTexture(std::string path);

		/// Set frame characters (stored as string).
		__declspec(dllexport) void addLine(std::string new_frame_str);

		/// Get frame characters (stored as string).
		__declspec(dllexport) std::string getLine(int i) const;

		/// Draw self, centered at position (x,y) with color.
		/// Don't draw transparent characters (0 means none).
		/// Return 0 if ok, else -1.
		/// Note: top-left coordinate is (0,0).
		__declspec(dllexport) int draw(Vector2D position, int color, char transparency) const;
	};

}