#ifndef KALMAN_ELECTRONICS_MASTER_V3_LOG_H
#define KALMAN_ELECTRONICS_MASTER_V3_LOG_H

typedef enum {
    LOG_LEVEL_DEBUG   = 0,
    LOG_LEVEL_INFO    = 1,
    LOG_LEVEL_WARNING = 2,
    LOG_LEVEL_ERROR   = 3,
    LOG_LEVEL_NONE    = 4,
} log_level_t;

#define LOG_LEVEL_DEFAULT LOG_LEVEL_INFO

// Current log level
// Set to none to disable logging
#define LOG_LEVEL LOG_LEVEL_DEFAULT

#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define LOG_D(TAG, ...) log_acquire_lock(); printf("\033[37m[%u][D] %s: ", time_us_32(), TAG); printf(__VA_ARGS__); printf("\033[0m"); log_release_lock();
#else
#define LOG_D(TAG, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LOG_I(TAG, ...) log_acquire_lock(); printf(        "[%u][I] %s: ", time_us_32(), TAG); printf(__VA_ARGS__); printf("\033[0m"); log_release_lock();
#else
#define LOG_I(TAG, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARNING
#define LOG_W(TAG, ...) log_acquire_lock(); printf("\033[93m[%u][W] %s: ", time_us_32(), TAG); printf(__VA_ARGS__); printf("\033[0m"); log_release_lock();
#else
#define LOG_W(TAG, ...)
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define LOG_E(TAG, ...) log_acquire_lock(); printf("\033[91m[%u][E] %s: ", time_us_32(), TAG); printf(__VA_ARGS__); printf("\033[0m"); log_release_lock();
#else
#define LOG_E(TAG, ...)
#endif

// Thread safety
void log_init();
void log_acquire_lock();
void log_release_lock();

#endif //KALMAN_ELECTRONICS_MASTER_V3_LOG_H
