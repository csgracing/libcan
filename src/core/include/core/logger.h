#ifndef CORE_LOGGER_H_
#define CORE_LOGGER_H_

// these two includes should be first (ie before spdlog) and in this order
#include "core/configure/config.h" // cmake created config header
#include "core/logger_defines.h"   // defines for logging, based on config header

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_CRITICAL
#define LIBCAN_LOG_CRITICAL(loggerName, ...) \
    SPDLOG_LOGGER_CRITICAL(logger::Logger::get(loggerName), __VA_ARGS__)
#else
#define LIBCAN_LOG_CRITICAL(loggerName, ...) (void)0
#endif

// Create and return a shared_ptr to a multithreaded console logger.

#include <unordered_map>

#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_sinks.h>

#include <spdlog/spdlog.h> // defines

namespace can::logger
{

    class Logger
    {
    private:
        static std::once_flag flag;
        static void bootstrap();

        static std::string prefix;

        static std::shared_ptr<spdlog::sinks::sink> sink;
        static std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<spdlog::logger>>> loggers;

    public:
        static void ensure();
        static std::shared_ptr<spdlog::logger> get(std::string name);
    };
};

#endif /* CORE_LOGGER_H_ */