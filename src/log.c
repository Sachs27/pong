#include <stdio.h>
#include <stdarg.h>

#define s_output_file stdout

static int s_called_func_count = 0;
/*static FILE *s_output_file = 0;*/

/**
 *  static func
 */
static inline void put_space(FILE *file, int count)
{
    int i;

    for(i = count; i > 0; --i) {
        fprintf(file, " ");
    }
    return ;
}

/**
 *  extern func
 */
void log_enter_func(const char *func_name)
{
    put_space(s_output_file, s_called_func_count++ * 2);
    fprintf(s_output_file, "[E]%s:\n", func_name);
    return ;
}

void log_leave_func(const char *func_name)
{
    put_space(s_output_file, --s_called_func_count * 2);
    fprintf(s_output_file, "[L]%s.\n", func_name);
    return ;
}

void log_put_msg_in_func(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    put_space(s_output_file, s_called_func_count * 2);
    vfprintf(s_output_file, format, args);
    va_end(args);
    return ;
}

