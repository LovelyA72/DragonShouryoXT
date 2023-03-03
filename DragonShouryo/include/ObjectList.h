#pragma once
///
/// A list of Objects
///

#include "DsrObject.h"
#include "ObjectListIterator.h"

namespace dsr {

	class ObjectListIterator;
	const int OBJLST_SIZE = 2000;
	class ObjectList {

	private:
		int m_count;                ///< Count of objects in list.
		int m_max_count;            ///< Maximum objects in list (variable).
		DsrObject* p_item[OBJLST_SIZE];            ///< Array of pointers to objects.

	public:
		__declspec(dllexport) friend class ObjectListIterator;           ///< Iterators can access.
		__declspec(dllexport) ObjectList();
		__declspec(dllexport) ~ObjectList();

		/// Copy contructor (does deep copy).
		__declspec(dllexport) ObjectList(const ObjectList& other);

		/// Assignment operator (does deep copy).
		__declspec(dllexport) ObjectList& operator=(const ObjectList& rhs);

		/// Insert object pointer in list.
		/// Return 0 if ok, else -1.
		__declspec(dllexport) int insert(DsrObject* p_o);

		/// Remove object pointer from list,
		/// Return 0 if found, else -1.
		__declspec(dllexport) int remove(DsrObject* p_o);

		/// Clear list (setting count to 0).
		__declspec(dllexport) void clear();

		/// Return count of number of objects in list.
		__declspec(dllexport) int getCount() const;

		/// Return true if list is empty, else false.
		__declspec(dllexport) bool isEmpty() const;

		/// Return true if list is full, else false.
		__declspec(dllexport) bool isFull() const;

		/// Compare two lists.
		__declspec(dllexport) bool operator==(const ObjectList& other) const;

		/// Compare two lists.
		__declspec(dllexport) bool operator!=(const ObjectList& other) const;

		/// Index into list.
		__declspec(dllexport) DsrObject*& operator[](int index);
	};

} // end of namespace dsr
