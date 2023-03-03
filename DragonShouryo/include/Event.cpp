#include "Event.h"

dsr::Event::Event()
{
	m_event_type = "df::undefined";
}

dsr::Event::~Event()
{
}

void dsr::Event::setType(std::string new_type)
{
	m_event_type = new_type;
}

std::string dsr::Event::getType() const
{
	return m_event_type;
}
