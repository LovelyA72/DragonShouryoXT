#include "GameSprite.h"

namespace dsr {
	GameSprite::~GameSprite()
	{
	}
	GameSprite::GameSprite(int max_frames)
	{
		m_frame = new Frame[64];
		m_width = 0;
	}
	void GameSprite::setWidth(int new_width)
	{
		m_width = new_width;
	}
	int GameSprite::getWidth() const
	{
		return m_width;
	}
	void GameSprite::setHeight(int new_height)
	{
		m_height = new_height;
	}
	int GameSprite::getHeight() const
	{
		return m_height;
	}
	void GameSprite::setColour(int new_colour)
	{
		m_colour = new_colour;
	}
	int GameSprite::getColour() const
	{
		return m_colour;
	}
	int GameSprite::getFrameCount() const
	{
		return m_frame_count;
	}
	int GameSprite::addFrame(Frame new_frame)
	{
		m_frame[m_frame_count] = new_frame;
		m_frame_count++;
		return 0;
	}
	Frame GameSprite::getFrame(int frame_number) const
	{
		return m_frame[frame_number];
	}
	void GameSprite::setLabel(std::string new_label)
	{
		m_label = new_label;
	}
	std::string GameSprite::getLabel() const
	{
		return m_label;
	}
	void GameSprite::setSlowdown(int new_sprite_slowdown)
	{
		m_slowdown = new_sprite_slowdown;
	}
	int GameSprite::getSlowdown() const
	{
		return m_slowdown;
	}
	void GameSprite::setTransparency(char new_transparency)
	{
		m_transparency = new_transparency;
	}
	char GameSprite::getTransparency() const
	{
		return m_transparency;
	}
	int GameSprite::draw(int frame_number, Vector2D position)
	{
		if (frame_number > m_frame_count) {
			return -1;
		}
		m_frame[frame_number].draw(position,m_colour,m_transparency);
		return 0;
	}
}