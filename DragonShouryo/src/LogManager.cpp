#include "LogManager.h"
#include <cstdarg>


namespace dsr {
	void LogManager::writeLog(const char* fmt, ...) {
		if (m_p_f == 0) {
			return;
		}
		va_list args;
		va_start(args, fmt);
		fprintf(m_p_f,"Message: ");
		vfprintf(m_p_f, fmt, args);
		fprintf(m_p_f, "\n");
		va_end(args);
		if (m_do_flush) {
			fflush(m_p_f);
		}
	}
	void LogManager::writeLogNoNL(const char* fmt, ...)
	{
		if (m_p_f == 0) {
			return;
		}
		va_list args;
		va_start(args, fmt);
		vfprintf(m_p_f, fmt, args);
		va_end(args);
		if (m_do_flush) {
			fflush(m_p_f);
		}
	}
	LogManager::LogManager() {
		m_p_f = NULL;
		m_do_flush = false;
	}
	void LogManager::operator=(LogManager const&)
	{
	}
	bool Manager::isValid(std::string event_type)const {
		return true;
	}
	LogManager::~LogManager()
	{
	}
	LogManager& LogManager::getInstance()
	{
		static LogManager single;
		return single;
	}
	inline bool ifFileExists(const std::string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}
	int LogManager::startUp()
	{
		if (ifFileExists(LOGFILE_NAME)) {
			remove(LOGFILE_NAME.c_str());
		}
		m_p_f = _fsopen(LOGFILE_NAME.c_str(), "a", _SH_DENYWR);
		m_is_started = true;
		return 0;
	}
	void LogManager::shutDown()
	{
		m_is_started = false;
		fclose(m_p_f);
	}
	void LogManager::setFlush(bool do_flush)
	{
		m_do_flush = do_flush;
	}
}