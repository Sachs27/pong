/**
 * log.h
 *
 * TODO:
 *   [ ]增加向文件输出的功能。
 */

#ifndef LOG_H
#define LOG_H

void log_enter_func(const char *func_name);
void log_leave_func(const char *func_name);
void log_put_msg_in_func(const char *format, ...);

#endif
