#include "core/logger.h"

#include <fmt/core.h>

#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Formatters/MessageOnlyFormatter.h>

namespace can::logger
{
    std::once_flag Logger::flag;

    std::string Logger::prefix(LIBCAN_PRODUCT_NAME);

    std::shared_ptr<plog::IAppender> Logger::g_appender = nullptr;
    std::shared_ptr<plog::Logger<PLOG_DEFAULT_INSTANCE_ID>> Logger::g_logger = nullptr;

    void Logger::ensure()
    {
        std::call_once(flag, bootstrap);
    };

    void Logger::bootstrap()
    {
        g_appender = std::make_shared<plog::ConsoleAppender<Formatter>>();
        g_logger = std::make_shared<plog::Logger<PLOG_DEFAULT_INSTANCE_ID>>(plog::verbose);
        g_logger->addAppender(g_appender.get());
    };

    std::shared_ptr<plog::Logger<PLOG_DEFAULT_INSTANCE_ID>> Logger::get()
    {
        ensure();
        return g_logger;
    }

    void Logger::log(plog::Severity sev, void (*lambda)(std::shared_ptr<plog::Logger<PLOG_DEFAULT_INSTANCE_ID>>))
    {
        ensure();

        if (g_logger->checkSeverity(sev))
        {
            lambda(g_logger);
        }
    }
}