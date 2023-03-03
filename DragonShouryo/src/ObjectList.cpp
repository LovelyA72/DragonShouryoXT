#include "ObjectList.h"
namespace dsr {
	dsr::ObjectList::ObjectList()
	{
		m_max_count = OBJLST_SIZE;
		m_count = 0;
	}
	ObjectList::~ObjectList()
	{

	}
	ObjectList::ObjectList(const ObjectList& other)
	{
		m_max_count = OBJLST_SIZE;
		m_count = 0;
		int osize = other.getCount();
		for (int i = 0; i < osize; i++) {
			p_item[m_count + i] = other.p_item[i];
		}
		m_count += osize;
	}
	ObjectList& ObjectList::operator=(const ObjectList& rhs)
	{
		m_count = rhs.m_count;
		for (int i = 0; i < m_count; i++) {
			p_item[i] = rhs.p_item[i];
		}
		return *this;
	}
	int ObjectList::insert(DsrObject* p_o)
	{
		if (m_count >= OBJLST_SIZE) {
			return -1;
		}
		p_item[m_count++] = p_o;
		return 0;
	}
	int ObjectList::remove(DsrObject* p_o)
	{
		for (int i = 0; i < m_count; i++) {
			if (p_item[i] == p_o) {
				for (int j = i; j < m_count - 1; j++)
					p_item[j] = p_item[j + 1];
				m_count--;
				return true;
			}
		}
		return -1;
	}
	void ObjectList::clear()
	{
		m_count = 0;
	}
	int ObjectList::getCount() const
	{
		return m_count;
	}
	bool ObjectList::isEmpty() const
	{
		return !m_count;
	}
	bool ObjectList::isFull() const
	{
		return m_count==m_max_count;
	}
	bool ObjectList::operator==(const ObjectList& other) const
	{
		if (m_count != other.m_count) {
			return false;
		}
		for (int i = 0; i < m_count; i++) {
			if (p_item[i] != other.p_item[i]) {
				return false;
			}
		}
		return true;
	}
	bool ObjectList::operator!=(const ObjectList& other) const
	{
		if (m_count != other.m_count) {
			return true;
		}
		for (int i = 0; i < m_count; i++) {
			if (p_item[i] != other.p_item[i]) {
				return true;
			}
		}
		return false;
	}
	DsrObject*& ObjectList::operator[](int index)
	{
		return p_item[index];
	}
}

