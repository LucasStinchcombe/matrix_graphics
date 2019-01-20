#ifndef MATRIX_GRAPHICS_DEBUG_H
#define MATRIX_GRAPHICS_DEBUG_H
#include <stdio.h>

#ifdef DEBUG
#define LOG(args...) fprintf(&log_stream, args)
#define LOG_INIT() debug_init()
#else
#define LOG(args...)
#define LOG_INIT()
#endif

#if DEBUG > 2
#define TRACE_DLEVEL
#define TRACE_LOG(args...) fprintf(&log_stream, "TRACE: " args)
#else
#define TRACE_LOG(args...)
#endif

#if DEBUG > 1
#define DEBUG_DLEVEL
#define DEBUG_LOG(args...) fprintf(&log_stream, "DEBUG: " args)
#else
#define DEBUG_LOG(args...)
#endif

#if DEBUG > 0
#define INFO_DLEVEL
#define INFO_LOG(args...) fprintf(&log_stream, "INFO: " args)
#else
#define INFO_LOG(args...)
#endif

extern FILE log_stream;
void debug_init();

#endif
