#include <stdio.h>
#include <stdarg.h>
#include "grabb.h"

#define COLOR_RESET  "\033[0m"
#define COLOR_WHITE  "\033[1;37m"
#define COLOR_GREEN  "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_RED    "\033[1;31m"

void logMessage(LogLevel level, const char *fmt, ...) {
    va_list args;

    printf("%s[%s", COLOR_WHITE, COLOR_RESET);

    switch (level) {
        case LOG_INFO:
            printf("%s info ", COLOR_GREEN);
            break;
        case LOG_SUCCESS:
            printf("%s success ", COLOR_GREEN);
            break;
        case LOG_WARN:
            printf("%s warn ", COLOR_YELLOW);
            break;
        case LOG_ERROR:
            printf("%s error ", COLOR_RED);
            break;
    }

    printf("%s]%s ", COLOR_WHITE, COLOR_RESET);

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    printf("\n");
}
