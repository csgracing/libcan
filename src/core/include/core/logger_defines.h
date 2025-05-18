#ifndef CORE_LOGGER_DEFINES_H_
#define CORE_LOGGER_DEFINES_H_

#define LIBCAN_LOG(severity, prefix, ...)                     \
    if (!can::logger::Logger::get()->checkSeverity(severity)) \
    {                                                         \
        ;                                                     \
    }                                                         \
    else                                                      \
        ((*can::logger::Logger::get().get()) += plog::Record(severity, nullptr, 0, nullptr, nullptr, 0).ref() << "[" << LIBCAN_PRODUCT_NAME << "." << prefix << "] " << __VA_ARGS__)

#if LIBCAN_LOG_LEVEL >= LIBCAN_LOG_LEVEL_VERBOSE
#define LIBCAN_LOG_TRACE(loggerName, ...) \
    LIBCAN_LOG(plog::verbose, loggerName, __VA_ARGS__);

#define LIBCAN_LOG_TRACE_BUF(loggerName, bufInp, sizeInp, ...)                 \
    [](auto buf, auto &&size)                                                  \
    {                                                                          \
        std::ostringstream hexData;                                            \
        for (int i = 0; i < size; i++)                                         \
        {                                                                      \
            hexData << std::hex << (int)buf[i];                                \
        };                                                                     \
        LIBCAN_LOG_TRACE(loggerName, fmt::format(__VA_ARGS__, hexData.str())); \
    }(bufInp, sizeInp);
#else
#define LIBCAN_LOG_TRACE(loggerName, ...) (void)0
#define LIBCAN_LOG_TRACE_BUF(loggerName, buf, size, ...) (void)0
#endif

#if LIBCAN_LOG_LEVEL >= LIBCAN_LOG_LEVEL_DEBUG
#define LIBCAN_LOG_DEBUG(loggerName, ...) \
    LIBCAN_LOG(plog::debug, loggerName, __VA_ARGS__);
#else
#define LIBCAN_LOG_DEBUG(loggerName, ...) (void)0
#endif

#if LIBCAN_LOG_LEVEL >= LIBCAN_LOG_LEVEL_INFO
#define LIBCAN_LOG_INFO(loggerName, ...) \
    LIBCAN_LOG(plog::info, loggerName, __VA_ARGS__);
#else
#define LIBCAN_LOG_INFO(loggerName, ...) (void)0
#endif

#if LIBCAN_LOG_LEVEL >= LIBCAN_LOG_LEVEL_WARN
#define LIBCAN_LOG_WARN(loggerName, ...) \
    LIBCAN_LOG(plog::warning, loggerName, __VA_ARGS__);
#else
#define LIBCAN_LOG_WARN(loggerName, ...) (void)0
#endif

#if LIBCAN_LOG_LEVEL >= LIBCAN_LOG_LEVEL_ERROR
#define LIBCAN_LOG_ERROR(loggerName, ...) \
    LIBCAN_LOG(plog::error, loggerName, __VA_ARGS__);
#else
#define LIBCAN_LOG_ERROR(loggerName, ...) (void)0
#endif

#endif /* CORE_LOGGER_DEFINES_H_ */