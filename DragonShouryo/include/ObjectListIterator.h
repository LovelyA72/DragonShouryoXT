#pragma once
///
/// An iterator for ObjectLists
///

#include "DsrObject.h"
#include "ObjectList.h"

namespace dsr {

	class ObjectList;

	class ObjectListIterator {

	private:
		ObjectListIterator();	        ///< Iterator must be given list when created.
		int m_index;			///< Index into list.
		const ObjectList* m_p_list;	///< List iterating over.

	public:
		/// Create iterator, over indicated list.
		__declspec(dllexport) ObjectListIterator(const ObjectList* p_list);

		/// Set iterator to first item in list.
		__declspec(dllexport) void first();

		/// Reset to last object in list.
		__declspec(dllexport) void last();

		/// Set iterator to next item in list.
		__declspec(dllexport) void next();

		/// Return true if at end of list.
		__declspec(dllexport) bool isDone() const;

		/// Return pointer to current item in list, NULL if done/empty.
		__declspec(dllexport) DsrObject* currentObject() const;

		/// Assignment operator.
		//ObjectListIterator& operator=(const ObjectListIterator& rhs);

		/// Set to new List.
		//void setList(const ObjectList* p_list);
	};

} // end of namespace dsr