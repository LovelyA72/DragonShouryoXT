#include "WorldManager.h"

namespace dsr {
	WorldManager::WorldManager() {
	}
	WorldManager& WorldManager::getInstance()
	{
		static WorldManager single;
		return single;
	}
	int dsr::WorldManager::startUp()
	{
		m_is_started = true;
		m_updates.clear();
		return 0;
	}
	bool WorldManager::isOutOfBound(Vector2D vec) const
	{
		if (vec.getX() < 0 || vec.getX() > WORLD_HORIZONTAL_CHARS_DEFAULT) {
			return true;
		}
		if (vec.getY() < 0 || vec.getY() > WORLD_VERTICAL_CHARS_DEFAULT) {
			return true;
		}
		return false;
	}
	void WorldManager::shutDown()
	{
		m_is_started = false;
		m_updates.clear();
	}
	int WorldManager::insertObject(DsrObject* p_o)
	{
		return m_updates.insert(p_o);
	}
	void WorldManager::update()
	{
		//Detect collision
		//Move objects
		ObjectList tempList = WM.getAllObjects();
		ObjectListIterator li(&tempList);
		li.first();
		while (not li.isDone()) {
			li.currentObject()->update();
			li.next();
		}
		draw();
		ObjectListIterator li2(& m_deletions);
		while (not li2.isDone())
		{
			delete li2.currentObject();
			li2.next();
		}
		m_deletions.clear();
	}
	int WorldManager::removeObject(DsrObject* p_o)
	{
		m_updates.remove(p_o);
		return 0;
	}

	ObjectList WorldManager::getAllObjects() const
	{
		return m_updates;
	}

	DsrObject* WorldManager::getObjectById(int id) {
		for (int i = 0; i < m_updates.getCount(); i++) {
			if (m_updates[i]->getId() == id) {
				return m_updates[i];
			}
		}
		return nullptr;
	}

	DsrObject* WorldManager::getObjectByName(std::string name)
	{
		for (int i = 0; i < m_updates.getCount(); i++) {
			if (m_updates[i]->getName() == name) {
				return m_updates[i];
			}
		}
		return nullptr;
	}

	int WorldManager::markForDelete(DsrObject* p_o)
	{
		ObjectListIterator li(&m_deletions);
		while (not li.isDone()) {
			if (li.currentObject() == p_o) {
				return 0;
			}
			li.next();
		}
		m_deletions.insert(p_o);
		return 0;
	}
	bool WorldManager::positionIntersect(Vector2D p1, Vector2D p2)
	{
		return((abs(p1.getX() - p2.getX()) < 1) and (abs(p1.getY() - p2.getY()) < 1));
	}
	bool WorldManager::boxIntersectsBox(Box A, Box B)
	{
		bool x_ol = false;
		bool y_ol = false;
		float ax1 = A.getLocation().getX();
		float ax2 = ax1+A.getLength();
		float ay1 = A.getLocation().getY();
		float ay2 = ay1+A.getHeight();
		float bx1 = B.getLocation().getX();
		float bx2 = bx1+B.getLength();
		float by1 = B.getLocation().getY();
		float by2 = by1+B.getHeight();
		// Test horizontal overlap (x_overlap).
		x_ol = ((bx1 <= ax1)&&(ax1 <= bx2)) || ((ax1 <= bx1)&&(bx1 <= ax2));
		y_ol = ((by1 <= ay1) && (ay1 <= by2)) || ((ay1 <= by1) && (by1 <= ay2));
		// Test vertical overlap (y_overlap).
		return x_ol and y_ol;
	}
	ObjectList WorldManager::getCollisions(DsrObject* p_o)
	{
		ObjectList result;
		ObjectListIterator i(&m_updates);
		while (!i.isDone()) {
			DsrObject* obj = i.currentObject();
			if (obj != p_o) {
				if (obj->isSolid() && boxIntersectsBox(obj->getBoundingBox(), p_o->getBoundingBox())) {
					result.insert(obj);
				}
			}
			i.next();
		}
		return result;
	}
	void WorldManager::draw()
	{
		ObjectList tempList = WM.getAllObjects();
		ObjectListIterator li(&tempList);
		for (int i = 0; i < 8; i++) {
			li.first();
			while (not li.isDone()) {
				li.currentObject()->draw(i);
				li.next();
			}
		}
	}
}