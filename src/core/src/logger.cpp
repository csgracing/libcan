#include "core/logger.h"

#include <fmt/core.h>

namespace can::logger
{
    std::once_flag Logger::flag;

    std::string Logger::prefix(LIBCAN_PRODUCT_NAME);

    std::shared_ptr<spdlog::sinks::sink> Logger::sink = nullptr;
    std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<spdlog::logger>>> Logger::loggers = nullptr;

    void Logger::ensure()
    {
        std::call_once(flag, bootstrap);
    };

    void Logger::bootstrap()
    {
        sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
        sink->set_level(spdlog::level::trace);
        loggers = std::make_shared<std::unordered_map<std::string, std::shared_ptr<spdlog::logger>>>();
    };

    std::shared_ptr<spdlog::logger> Logger::get(std::string name)
    {
        ensure();

        if (loggers->find(name) != loggers->end())
        {
            return loggers->at(name);
        }
        else
        {
            auto logger = std::make_shared<spdlog::logger>(fmt::format("{}.{}", prefix, name), sink);
            logger->set_level(sink->level());
            loggers->insert({name, logger});
            return logger;
        }
    }
}