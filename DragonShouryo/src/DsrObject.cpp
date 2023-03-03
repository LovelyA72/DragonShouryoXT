#include "DsrObject.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "GameManager.h"
#include <cassert>

namespace dsr {
	DsrObject::DsrObject()
	{
		m_solidness = HARD;
		m_colour = Colour::WHITE;
		WM.insertObject(this);
	}
	DsrObject::~DsrObject()
	{
		WM.removeObject(this);
	}
	void DsrObject::setId(int new_id)
	{
		m_id = new_id;
	} 
	void DsrObject::setDirection(Vector2D new_direction)
	{
		m_direction = new_direction;
	}
	float DsrObject::getSpeed() const
	{
		return m_speed;
	}
	void DsrObject::setSpeed(float speed)
	{
		m_speed = speed;
	}
	Vector2D DsrObject::getDirection() const
	{
		return m_direction;
	}
	int DsrObject::getId() const
	{
		return m_id;
	}
	void DsrObject::setType(std::string new_type)
	{
		m_type = new_type;
	}
	std::string DsrObject::getType() const
	{
		return m_type;
	}
	int DsrObject::setPosition(Vector2D new_position)
	{
		m_position.setX(new_position.getX());
		m_position.setY(new_position.getY());
		return 0;
	}
	Vector2D DsrObject::getPosition() const
	{
		return m_position;
	}
	void DsrObject::markDelete()
	{
		m_delete = true;
	}
	void DsrObject::setColour(int colour)
	{
		m_colour = colour;
	}
	Vector2D DsrObject::getVelocity() const
	{
		return m_direction * m_speed;
	}
	void DsrObject::setVelocity(Vector2D vec)
	{
		m_speed = vec.getMagnitude();
		vec.normalize();
		m_direction = vec;
	}
	void DsrObject::setDrawId(bool b)
	{
		m_draw_id = b;
	}
	Box DsrObject::getBoundingBox()
	{
		//return Box(m_position,m_sprite.length(), 1);
		return m_box;
	}
	Vector2D DsrObject::predictPosition()
	{
		// Add velocity to position.
		Vector2D new_pos = m_position + getVelocity();
		// Return new position.
		return new_pos;
	}
	void DsrObject::setSolidness(Solidness s)
	{
		m_solidness = s;
	}
	Solidness DsrObject::getSolidness() const
	{
		return m_solidness;
	}
	bool DsrObject::isSolid() const
	{
		return (m_solidness == HARD || m_solidness == SOFT);
	}
	void DsrObject::setSprite(std::string str)
	{
		m_sprite = str;
		updateBox();
	}
	std::string DsrObject::getSprite() const
	{
		return m_sprite;
	}
	void DsrObject::setAlt(int a)
	{
		m_altitude = a;
	}
	void DsrObject::setSprMode(int i) {
		m_sprite_mode = i;
		updateBox();
	}
	int DsrObject::getSprMode() {
		return m_sprite_mode;
	}
	void DsrObject::setVisibility(bool b) {
		m_visible = b;
	}
	bool DsrObject::getVisibility() {
		return m_visible;
	}
	void DsrObject::setName(std::string b)
	{
		m_name = b;
	}
	std::string DsrObject::getName()
	{
		return m_name;
	}
	void DsrObject::updateBox()
	{
		if (m_sprite_mode&&(m_sprite!="")) {
			m_box.setLength(RM.getSprite(m_sprite)->getWidth());
			m_box.setHeight(RM.getSprite(m_sprite)->getHeight());
		}
		else {
			m_box.setLength(m_sprite.length());
			m_box.setHeight(1);
		}
		m_box.setLocation(m_position);
	}
	int DsrObject::getAlt()
	{
		return m_altitude;
	}
	void DsrObject::draw(int alt,bool important)
	{
		//if not visible, don't draw
		if (!m_visible) {
			return;
		}
		//If it's outside camera, don't draw
		if (!WM.boxIntersectsBox(this->getBoundingBox(), DM.getCameraBox())) {
			return;
		}
		//Draw stuff
		if (alt == m_altitude || important) {
			if (m_sprite_mode) {
				if (GM.getFrameCounter() % RM.getSprite(m_sprite)->getSlowdown() == 0) {
					m_current_frame++;
					if (RM.getSprite(m_sprite)->getFrameCount() == m_current_frame) {
						m_current_frame = 0;
					}
				}
				RM.getSprite(m_sprite)->draw(m_current_frame, m_position - DM.getCameraPosition());
			}
			else {
				DM.drawStr(m_position-DM.getCameraPosition(), m_sprite, WHITE);
			}
		}
		if (DM.getShowBox()) {
			Box nbox(m_box.getLocation()-DM.getCameraPosition(), m_box.getLength(), m_box.getHeight());
			DM.drawBox(nbox,1,GREEN);
		}
		if (m_draw_id) {
			DM.drawStr(Vector2D(m_position.getX() + m_box.getLength() - DM.getCameraPosition().getX(), m_position.getY() + m_box.getHeight() - DM.getCameraPosition().getY()), std::to_string(getId()), WHITE, 0, 1);
		}
	}
	void DsrObject::update()
	{
		m_box.setLocation(m_position);
		bool doMove = true;
		if (isSolid()) {
			//Do collison detection
			ObjectList list = WM.getCollisions(this);
			if (list.getCount()) {
				ObjectListIterator li(&list);
				while (!li.isDone()) {
					if (li.currentObject() != this) {
						//assert(this->getId() != li.currentObject()->getId());
						DsrObject* obj = li.currentObject();
						EventCollision col(this, obj, this->getPosition());
						this->eventHandler(&col);
						obj->eventHandler(&col);
						if ((this->getSolidness() == HARD) && (obj->getSolidness() == HARD)) {
							doMove = false;
						}
						li.next();
					}
				}
			}
		}
		//Move object
		bool isOut = false;
		if (!WM.isOutOfBound(m_position) and WM.isOutOfBound(predictPosition())) {
			isOut = true;
		}
		if (doMove) {
			m_position = predictPosition();
			m_box.setLocation(m_position);
		}
		
		//Check out of bound
		if (isOut) {
			EventOut e;
			eventHandler(&e);
		}
	}
	int DsrObject::eventHandler(const Event* p_e)
	{
		return 0;
	}
}
