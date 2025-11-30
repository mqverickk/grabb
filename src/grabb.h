#ifndef GRABB_H
#define GRABB_H

#include <stddef.h>

#define BASE_URL "https://api.modrinth.com/v2"
#define USER_AGENT "Linux/GrabbCLI/1.2 (mqverickk@github.com)"

typedef enum {
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LOG_SUCCESS
} LogLevel;

struct MemoryStruct {
    char *memory;
    size_t size;
};

void logMessage(LogLevel level, const char *fmt, ...);

char* httpGet(const char* url);
int downloadFile(const char* url, const char* filename);
void searchPlugin(const char* query);
void getStats(const char* targetSlug);
void downloadPlugin(const char* projectId, const char* version, const char* loader);

#endif
