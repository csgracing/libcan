#ifndef CORE_LOGGER_H_
#define CORE_LOGGER_H_

// these two includes should be first (ie before spdlog) and in this order
#include "core/configure/config.h" // cmake created config header
#include "core/logger_defines.h"   // defines for logging, based on config header

#if LIBCAN_LOG_LEVEL > LIBCAN_LOG_LEVEL_NONE
#include <fmt/format.h>
#endif

#ifdef LIBCAN_LOG_TRACE_BUF
#include <sstream> // std::ostringstream
#endif

// Create and return a shared_ptr to a multithreaded console logger.

#include <unordered_map>
#include <mutex>   // std::once_flag
#include <memory>  // std::<[unique|shared]_ptr
#include <iomanip> // std::setw, setFill

#include <plog/Log.h>
#include <plog/Logger.h>

namespace can::logger
{

    class Logger
    {
    private:
        static std::once_flag flag;
        static void bootstrap();

        static std::string prefix;

        static std::shared_ptr<plog::IAppender> g_appender;
        static std::shared_ptr<plog::Logger<PLOG_DEFAULT_INSTANCE_ID>> g_logger;

    public:
        static void ensure();
        static std::shared_ptr<plog::Logger<PLOG_DEFAULT_INSTANCE_ID>> get();
        static void log(plog::Severity sev, void (*lambda)(std::shared_ptr<plog::Logger<PLOG_DEFAULT_INSTANCE_ID>>));
    };

    // based on TxtFormatter from plog
    class Formatter
    {
    public:
        static plog::util::nstring header()
        {
            return plog::util::nstring();
        }

        static plog::util::nstring format(const plog::Record &record)
        {
            plog::util::nostringstream ss;
            ss << std::setfill(PLOG_NSTR(' ')) << std::setw(5) << std::left << plog::severityToString(record.getSeverity()) << PLOG_NSTR(" ");
            ss << record.getMessage() << PLOG_NSTR("\n");

            return ss.str();
        }
    };
};

#endif /* CORE_LOGGER_H_ */