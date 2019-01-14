#ifndef ONETWO_DEBUG_H
#define ONETWO_DEBUG_H
#include <stdio.h>

#ifdef DEBUG
#define LOG(args...) fprintf(&log_stream, args)
#define LOG_INIT() debug_init()
#else
#define LOG(args...)
#define LOG_INIT()
#endif

extern FILE log_stream;
void debug_init();

#endif
