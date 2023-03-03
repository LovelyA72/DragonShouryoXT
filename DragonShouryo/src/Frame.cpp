#include "Frame.h"
#include "DisplayManager.h"

namespace dsr{
	Frame::Frame()
	{
		m_linecount = 0;
		m_frame_str = new std::string[128];
	}
	void Frame::setWidth(int new_width)
	{
		m_width = new_width;
	}
	int Frame::getWidth() const
	{
		return m_width;
	}
	int Frame::getHeight() const
	{
		return m_linecount;
	}
	int Frame::getLineCount()
	{
		return m_linecount;
	}
	void Frame::loadTexture(std::string path)
	{
		if (m_graphical_texture.loadFromFile(path)) {
			m_graphical = 1;
			m_graphical_texture.setSmooth(true);
			m_graphical_sprite.setTexture(m_graphical_texture);
		}
		else {
			m_graphical = 0;
		}
	}
	void Frame::addLine(std::string new_frame_str)
	{
		m_frame_str[m_linecount] = new_frame_str;
		m_linecount++;
	}
	std::string Frame::getLine(int i) const
	{
		return m_frame_str[i];
	}
	int Frame::draw(Vector2D position, int colour, char transparency) const
	{
		sf::Sprite spr = m_graphical_sprite;
		Vector2D pixpos = DM.spacesToPixels(position);
		spr.setPosition(pixpos.getX(), pixpos.getY());
		if (m_graphical) {
			DM.drawSprite(spr);
		}
		else {
			for (int i = 0; i < m_linecount; i++) {
				Vector2D vec(position.getX(), position.getY() + i);
				DM.drawStr(vec, m_frame_str[i], colour, transparency);
			}
		}
		return 0;
	}
}