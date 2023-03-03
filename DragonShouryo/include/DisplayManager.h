#pragma once
#include "SFML/Graphics.hpp"
#include "Manager.h"
#include "Colour.h"
#include "GameClock.h"

#define DM dsr::DisplayManager::getInstance()

const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1280;
const int WINDOW_VERTICAL_PIXELS_DEFAULT = 704;
const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 100;
const int WINDOW_VERTICAL_CHARS_DEFAULT = 22;
const int DM_FPS_AVG = 15;

namespace dsr {
	class DisplayManager :public Manager {
	public:
		__declspec(dllexport) static DisplayManager& getInstance();
		__declspec(dllexport) void shutDown();
		__declspec(dllexport) void getEvent();

		//check if window open
		__declspec(dllexport) bool isOpen();

		//Update display manager
		__declspec(dllexport) void update();

		__declspec(dllexport) int drawSprite(sf::Sprite spr);

		//Draw character, very important for us.
		//POS IS NOT PIXEL!! IS CHARACTER LOCATION!!!
		__declspec(dllexport) int drawCh(Vector2D pos, char ch, int colour, int size = 0);

		//Draw string, very important for us.
		//POS IS NOT PIXEL!! IS CHARACTER LOCATION!!!
		__declspec(dllexport) int drawStr(Vector2D pos, std::string str, int colour, char trans = 0, int size = 0);

		//Draw string, very important for us.
		//POS IS NOT PIXEL!! IS CHARACTER LOCATION!!!
		__declspec(dllexport) int drawBox(Box pos, int outline, int colour, bool fill = false);

		//In case someone wanna do something fancy with the window...
		__declspec(dllexport) sf::RenderWindow* getWindow() const;

		//Swap out buffers
		__declspec(dllexport) int swapBuffers();

		//Start up function
		__declspec(dllexport) int startUp();
		/// Compute character height, based on window size and font.
		__declspec(dllexport) float charHeight(void);

		/// Compute character width, based on window size and font.
		__declspec(dllexport) float charWidth(void);

		/// Convert ASCII spaces (x,y) to window pixels (x,y).
		__declspec(dllexport) Vector2D spacesToPixels(Vector2D spaces);

		/// Convert window pixels (x,y) to ASCII spaces (x,y).
		__declspec(dllexport) Vector2D pixelsToSpaces(Vector2D pixels);

		/// Set window's horizontal maximum (in characters).
		__declspec(dllexport) void setHorizontal(int new_horizontal);

		__declspec(dllexport) void setCameraPosition(Vector2D vec);

		__declspec(dllexport) Vector2D getCameraPosition();

		/// Return window's horizontal maximum (in characters).
		__declspec(dllexport) int getHorizontal() const;

		/// Set window's vertical maximum (in characters).
		__declspec(dllexport) void setVertical(int new_vertical);

		/// Return window's vertical maximum (in characters).
		__declspec(dllexport) int getVertical() const;

		/// Return window's horizontal maximum (in pixels).
		__declspec(dllexport) int getHorizontalPixels() const;

		/// Return window's vertical maximum (in pixels).
		__declspec(dllexport) int getVerticalPixels() const;

		/// Set window's background colour.
		/// Return true if ok, else false.
		__declspec(dllexport) bool setBackgroundColor(Colour new_colour);

		__declspec(dllexport) void setOverload();

		// Toggle FPS display
		__declspec(dllexport) void toggleFPS();

		__declspec(dllexport) void setShowBox(bool b);

		__declspec(dllexport) bool getShowBox();
		__declspec(dllexport) Box getCameraBox();
	private:
		DisplayManager();                      ///< Private since a singleton.
		DisplayManager(DisplayManager const&); ///< Don't allow copy.
		void operator=(DisplayManager const&); ///< Don't allow assignment.
		sf::Font m_font;		  ///< Font used for ASCII graphics.
		sf::RenderWindow* p_window;	  ///< Pointer to SFML window.
		int m_window_horizontal_pixels; ///< Horizontal pixels in window.
		int m_window_vertical_pixels;   ///< Vertical pixels in window.
		int m_window_horizontal_chars;  ///< Horizontal ASCII spaces in window.
		int m_window_vertical_chars;    ///< Vertical ASCII spaces in window.
		sf::RectangleShape* m_p_rectangle;    ///< Backing rectangle for under text.
		sf::Color m_window_background_colour;  ///< Background colour of window.
		sf::Text* m_p_text;                   ///< ASCII character to draw.
		int m_shake_duration;		        ///< Time left to shake (frames).
		int m_shake_scale_x, m_shake_scale_y; ///< Severity of shake (pixels).
		int m_shake_x, m_shake_y;		///< Shake (this frame).
		bool m_show_fps = true;
		int fps = 0;
		int fpstemp = 0;
		int fpscount = 0;
		bool m_overload = false;
		bool m_displayOverload = false;
		bool m_showbox = false;
		Box camera_box = Box(Vector2D(0, 0), WINDOW_HORIZONTAL_CHARS_DEFAULT, WINDOW_VERTICAL_CHARS_DEFAULT);
		Vector2D m_cam_pos = Vector2D(0,0);
		GameClock clock;
	};
}