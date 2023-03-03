#pragma once
// System includes.
#include <string>

// Engine includes.
#include "Frame.h"

namespace dsr {

	class GameSprite {

	private:
		int m_width = 0;           ///< Sprite width.
		int m_height = 0;          ///< Sprite height.
		int m_max_frame_count = 0; ///< Maximum number of frames sprite can have.
		int m_frame_count = 0;     ///< Actual number of frames sprite has.
		int m_colour = 0;	 ///< Optional colour for entire sprite.
		int m_slowdown = 0;        ///< Animation slowdown (1 = no slowdown, 0 = stop).
		char m_transparency = 0;   ///< Sprite transparent character (0 if none).
		Frame* m_frame;        ///< Array of frames.
		std::string m_label = "";	 ///< Text label to identify sprite.
		GameSprite();              ///< Sprite always has one arg, the frame count.

	public:
		/// Delete sprite, removing any allocated frames.
		__declspec(dllexport) ~GameSprite();

		/// Create sprite with indicated maximum number of frames.
		__declspec(dllexport) GameSprite(int max_frames);

		/// Set width of sprite.
		__declspec(dllexport) void setWidth(int new_width);

		/// Get width of sprite.
		__declspec(dllexport) int getWidth() const;

		/// Set height of sprite.
		__declspec(dllexport) void setHeight(int new_height);

		/// Get height of sprite.
		__declspec(dllexport) int getHeight() const;

		/// Set sprite colour.
		__declspec(dllexport) void setColour(int new_colour);

		/// Get sprite colour.
		__declspec(dllexport) int getColour() const;

		/// Get total count of frames in sprite.
		__declspec(dllexport) int getFrameCount() const;

		/// Add frame to sprite.
		/// Return -1 if frame array full, else 0.
		__declspec(dllexport) int addFrame(Frame new_frame);

		/// Get next sprite frame indicated by number.
		/// Return empty frame if out of range [0, m_frame_count-1].
		__declspec(dllexport) Frame getFrame(int frame_number) const;

		/// Set label associated with sprite.
		__declspec(dllexport) void setLabel(std::string new_label);

		/// Get label associated with sprite.
		__declspec(dllexport) std::string getLabel() const;

		/// Set animation slowdown value.
		/// Value in multiples of GameManager frame time.
		__declspec(dllexport) void setSlowdown(int new_sprite_slowdown);

		// Get animation slowdown value.
		// Value in multiples of GameManager frame time.
		__declspec(dllexport) int getSlowdown() const;

		/// Set Sprite transparency character (0 means none).
		__declspec(dllexport) void setTransparency(char new_transparency);

		/// Get Sprite transparency character (0 means none).
		__declspec(dllexport) char getTransparency() const;

		/// Draw indicated frame centered at position (x,y).
		/// Don't draw transparent characters (0 means none).
		/// Return 0 if ok, else -1.
		/// Note: top-left coordinate is (0,0).
		__declspec(dllexport) int draw(int frame_number, Vector2D position);
	};

}