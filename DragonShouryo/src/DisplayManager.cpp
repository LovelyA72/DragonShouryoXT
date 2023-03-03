#include "DisplayManager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "GameClock.h"
#include "ResourceManager.h"
#include <math.h>

namespace dsr {
	DisplayManager& DisplayManager::getInstance()
	{
		static DisplayManager single;
		return single;
	}
	void DisplayManager::shutDown()
	{
		
	}
	void DisplayManager::getEvent()
	{
		
	}
	bool DisplayManager::isOpen()
	{
		return p_window->isOpen();
	}
	void DisplayManager::update()
	{
		
			int delta = clock.delta();
			int fpsnow = 0;
			if (delta) {
				fpsnow = 1 / ((float)delta * 0.001f);
			}
			if (fpscount < DM_FPS_AVG) {
				fpstemp += fpsnow;
				fpscount++;
			}
			else {
				fps = fpstemp / DM_FPS_AVG;
				m_displayOverload = m_overload;
				m_overload = false;
				fpscount = 0;
				fpstemp = 0;
			}
		if (m_show_fps) {
			if (m_displayOverload) {
				drawStr(Vector2D(0, 0), "FPS:", dsr::RED);
				drawStr(Vector2D(4, 0), std::to_string(fps), dsr::RED);
			}
			else {
				drawStr(Vector2D(0, 0), "FPS:", dsr::GREEN);
				drawStr(Vector2D(4, 0), std::to_string(fps), dsr::GREEN);
			}
		}
		p_window->display();
		p_window->clear();
	}
	int DisplayManager::drawSprite(sf::Sprite spr) {
		if (p_window == NULL) {
			return 1;
		}
		p_window->draw(spr);
		return 0;
	}
	int DisplayManager::drawCh(Vector2D pos, char ch, int colour, int size)
	{
		if (p_window == NULL) {
			return 1;
		}
		Vector2D pixel_pos = spacesToPixels(pos);

		static sf::RectangleShape rec;
		rec.setSize(sf::Vector2f(charWidth(), charHeight() - 1));
		rec.setFillColor(sf::Color(0x0));
		rec.setPosition(pixel_pos.getX()+charWidth()/10,pixel_pos.getY() + charHeight() / 5);
		p_window->draw(rec);
		static sf::Text text("", m_font);
		text.setString(ch);
		text.setStyle(sf::Text::Bold); // Make bold, since looks better.
		text.setOutlineColor(sf::Color(0));
		if (size) {
			if (charWidth() < charHeight()) {
				text.setCharacterSize(charWidth()*1.5);
			}
			else {
				text.setCharacterSize(charHeight()*1.5);
			}
		}
		else {
			if (charWidth() < charHeight()) {
				text.setCharacterSize(charWidth() * 2);
			}
			else {
				text.setCharacterSize(charHeight() * 2);
			}
		}
		sf::Color coloursf(colour);
		text.setFillColor(coloursf);
		text.setPosition(pixel_pos.getX(), pixel_pos.getY());
		p_window->draw(text);
		return 0;
	}
	int DisplayManager::drawStr(Vector2D pos, std::string str, int colour,char trans,int size)
	{
		for (int i = 0; i < str.length(); i++) {
			Vector2D pos2;
			if (size) {
				pos2 = pos + Vector2D(i*0.75, 0);
			}
			else {
				pos2 = pos + Vector2D(i, 0);
			}
			if (str[i] != trans) {
				drawCh(pos2, str[i], colour, size);
			}
		}
		return 0;
	}
	int DisplayManager::drawBox(Box pos, int outline, int colour, bool fill)
	{
		Vector2D boxsize = spacesToPixels(Vector2D(pos.getLength(), pos.getHeight()));
		sf::Vector2f size = sf::Vector2f(boxsize.getX(), boxsize.getY());
		sf::RectangleShape rec(size);
		sf::Color colorsf(colour);
		sf::Color colortrans(0);
		rec.setFillColor(colortrans);
		if (fill) {
			rec.setFillColor(colorsf);
		}
		rec.setOutlineColor(colorsf);
		rec.setOutlineThickness(outline);
		Vector2D pixel_pos = spacesToPixels(pos.getLocation());
		rec.setPosition(pixel_pos.getX(),pixel_pos.getY());
		p_window->draw(rec);
		return 0;
	}
	sf::RenderWindow* DisplayManager::getWindow() const
	{
		return p_window;
	}
	int DisplayManager::swapBuffers()
	{
		if (p_window != NULL) {
			return 1;
		}
		p_window->display();
		p_window->clear();
		
		return 0;
	}
	int DisplayManager::startUp()
	{
		if (p_window != NULL) {
			return 1;
		}
		p_window = new sf::RenderWindow(sf::VideoMode(getHorizontalPixels(), getVerticalPixels()), "DragonShouryo - World's cutest dragon dechu!", sf::Style::Default, sf::ContextSettings(24, 8, 4));
		p_window->setVerticalSyncEnabled(true);
		p_window->setKeyRepeatEnabled(false);
		p_window->setMouseCursorVisible(false);
		//Load font
		m_font = sf::Font();
		if (!m_font.loadFromFile(RM.getDataPath() + "df-font.ttf")) {
			printf("df-font.ttf not found!");
		}
		clock = GameClock();
		m_is_started = true;
		return 0;
	}
	float DisplayManager::charHeight(void)
	{
		return (getVerticalPixels()/getVertical());
	}
	float DisplayManager::charWidth(void)
	{
		return getHorizontalPixels() / getHorizontal();
	}
	Vector2D DisplayManager::spacesToPixels(Vector2D spaces)
	{
		return Vector2D(spaces.getX() * charWidth(), spaces.getY() * charHeight());
	}
	Vector2D DisplayManager::pixelsToSpaces(Vector2D pixels)
	{
		return Vector2D(pixels.getX() / charWidth(),pixels.getY()/charHeight());
	}
	void DisplayManager::setHorizontal(int new_horizontal)
	{
		m_window_horizontal_chars = new_horizontal;
	}
	void DisplayManager::setCameraPosition(Vector2D vec)
	{
		m_cam_pos = vec;
	}
	Vector2D DisplayManager::getCameraPosition()
	{
		return m_cam_pos;
	}
	int DisplayManager::getHorizontal() const
	{
		return m_window_horizontal_chars;
	}
	void DisplayManager::setVertical(int new_vertical)
	{
		m_window_vertical_chars = new_vertical;
	}
	int DisplayManager::getVertical() const
	{
		return m_window_vertical_chars;
	}
	int DisplayManager::getHorizontalPixels() const
	{
		return m_window_horizontal_pixels;
	}
	int DisplayManager::getVerticalPixels() const
	{
		return m_window_vertical_pixels;
	}
	bool DisplayManager::setBackgroundColor(Colour new_colour)
	{
		//m_window_background_colour = new_colour;
		return true;
	}
	void DisplayManager::setOverload()
	{
		m_overload = true;
	}
	DisplayManager::DisplayManager() {
		m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
		m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
		m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
		m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
		p_window = NULL;
	}
	void DisplayManager::toggleFPS()
	{
		m_show_fps = !m_show_fps;
	}
	void DisplayManager::setShowBox(bool b)
	{
		m_showbox = b;
	}
	bool DisplayManager::getShowBox()
	{
		return m_showbox;
	}
	Box DisplayManager::getCameraBox() {
		camera_box.setLocation(m_cam_pos);
		return camera_box;
	}
}