#pragma once
#include <stdio.h>
#include <string>
#include "Manager.h"
namespace dsr {
	const std::string LOGFILE_NAME = "dragonshouryo.log";

#define LM dsr::LogManager::getInstance() // Two-letter acronym 

		class LogManager : public Manager {
		private:
			LogManager();                      // Private (a singleton).
			LogManager(LogManager const&);    // No copying.
			void operator=(LogManager const&); // No assignment.
			bool m_do_flush;                   // True if fflush after each write.
			FILE* m_p_f;                       // Pointer to logfile structure.
		public:
			// If logfile is open, close it.
			__declspec(dllexport) ~LogManager();

			// Get the one and only instance of the LogManager.
			__declspec(dllexport) static LogManager& getInstance();

			// Start up the LogManager (open logfile "dragonfly.log").
			__declspec(dllexport) int startUp();

			// Shut down the LogManager (close logfile).
			__declspec(dllexport) void shutDown();

			// Set flush of logfile after each write.
			__declspec(dllexport) void setFlush(bool do_flush = true);

			// Write to logfile. Supports printf() formatting.
			// Return number of bytes written, -1 if error.
			__declspec(dllexport) void writeLog(const char* fmt, ...);

			// Write to logfile. Supports printf() formatting.
			// Return number of bytes written, -1 if error.
			__declspec(dllexport) void writeLogNoNL(const char* fmt, ...);
	};
} // end of namespace df