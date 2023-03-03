#include "Manager.h"
#include "WorldManager.h"
#include "EventStep.h"


namespace dsr {
	void Manager::setType(std::string type)
	{
		m_type = type;
	}

	Manager::Manager()
	{
		m_is_started = false;
	}

	Manager::~Manager()
	{
	}

	std::string Manager::getType() const
	{
		return m_type;
	}

	int Manager::startUp()
	{
		m_is_started = true;
		return 0;
	}

	void Manager::shutDown()
	{
		m_is_started = false;
	}

	int Manager::onEvent(const Event* p_event) const
	{
		int counter = 0;
		ObjectList tempList = WM.getAllObjects();
		ObjectListIterator li(&tempList);
		while (not li.isDone()) {
			li.currentObject()->eventHandler(p_event);
			li.next();
		}
		return 0;
	}

	bool Manager::isStarted() const
	{
		return m_is_started;
	}

}
