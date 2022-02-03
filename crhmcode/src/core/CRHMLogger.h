#pragma once

#define SPDLOG_ACTIVE_LEVEL ACTIVE_LOG_LEVEL

#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "CRHMException.h"

class CRHMLogger
{

	std::shared_ptr<spdlog::logger> runLogger;

	std::shared_ptr<spdlog::logger> consoleLogger;

	static CRHMLogger* s_instance;

	CRHMLogger();

public:

	static CRHMLogger* instance();

	std::shared_ptr<spdlog::logger> get_run_logger();

	void log_to_console(std::string msg);

	void log_run_error(CRHMException exception);

	void log_run_message(std::string msg);

	void log_run_debug_message(std::string msg);

};