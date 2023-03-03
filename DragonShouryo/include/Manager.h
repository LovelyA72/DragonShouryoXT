#pragma once

///
/// The base manager
///

// System includes.
#include <string>

// Engine includes.
#include "Event.h"
#include "DsrObject.h"
#include "ObjectList.h"

namespace dsr {

	const int MAX_EVENTS = 100;	      ///< Max number of different events.

#ifndef DF_REGISTER_INTEREST
#define DF_REGISTER_INTEREST	      // registerInterest() defined.
#endif

	class Manager {

	private:
		std::string m_type;			 ///< Manager type identifier.
		int m_event_count;                     ///< Number of events.
		

		/// Check if event is handled by this Manager.
		/// If handled, return true else false.
		/// (Base Manager always returns false.)
		virtual bool isValid(std::string event_type) const;

	protected:
		/// Set type identifier of Manager.
		void setType(std::string new_type);
		bool m_is_started;                     ///< True if startUp() succeeded
	public:
		__declspec(dllexport) Manager();
		__declspec(dllexport) virtual ~Manager();

		/// Get type identifier of Manager.
		__declspec(dllexport) std::string getType() const;

		/// Startup Manager. 
		/// Return 0 if ok, else negative number.
		__declspec(dllexport) virtual int startUp();

		/// Shutdown Manager.  
		__declspec(dllexport) virtual void shutDown();

		__declspec(dllexport) virtual int onEvent(const Event* p_event) const;

		/// Return status of is_started (true when startUp() was successful).
		__declspec(dllexport) bool isStarted() const;

		/// Indicate interest in event.
		/// Return 0 if ok, else -1.
		/// (Note, doesn't check to see if Object is already registered.)
		__declspec(dllexport) int registerInterest(DsrObject* p_o, std::string event_type);

		/// Indicate no more interest in event. 
		/// Return 0 if ok, else -1.
		__declspec(dllexport) int unregisterInterest(DsrObject* p_o, std::string event_type);

	};

} // end of namespace dsr
