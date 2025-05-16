#ifndef CORE_LOGGER_DEFINES_H_
#define CORE_LOGGER_DEFINES_H_

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#define LIBCAN_LOG_DEBUG(loggerName, ...) \
    SPDLOG_LOGGER_DEBUG(logger::Logger::get(loggerName), __VA_ARGS__)
#else
#define LIBCAN_LOG_DEBUG(loggerName, ...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_INFO
#define LIBCAN_LOG_INFO(loggerName, ...) \
    SPDLOG_LOGGER_INFO(logger::Logger::get(loggerName), __VA_ARGS__)
#else
#define LIBCAN_LOG_INFO(loggerName, ...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_WARN
#define LIBCAN_LOG_WARN(loggerName, ...) \
    SPDLOG_LOGGER_WARN(logger::Logger::get(loggerName), __VA_ARGS__)
#else
#define LIBCAN_LOG_WARN(loggerName, ...) (void)0
#endif

#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_ERROR
#define LIBCAN_LOG_ERROR(loggerName, ...) \
    SPDLOG_LOGGER_ERROR(logger::Logger::get(loggerName), __VA_ARGS__)
#else
#define LIBCAN_LOG_ERROR(loggerName, ...) (void)0
#endif

#endif /* CORE_LOGGER_DEFINES_H_ */