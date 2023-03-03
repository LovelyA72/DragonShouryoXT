#include "ObjectListIterator.h"
namespace dsr {
	ObjectListIterator::ObjectListIterator(const ObjectList* p_list)
	{
		m_p_list = p_list;
	}
	void ObjectListIterator::first()
	{
		m_index = 0;
	}
	void ObjectListIterator::last()
	{
		m_index = m_p_list->m_count - 1;
	}
	void ObjectListIterator::next()
	{
		if (m_index < m_p_list->m_count) {
			m_index++;
		}
	}
	bool ObjectListIterator::isDone() const
	{
		return (m_index >= m_p_list->m_count);
	}
	DsrObject* ObjectListIterator::currentObject() const
	{
		if (isDone()) {
			return 0;
		}

		return m_p_list->p_item[m_index];
	}
}

