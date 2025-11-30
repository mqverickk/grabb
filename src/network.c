#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "grabb.h"

static size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (!ptr) {
        logMessage(LOG_ERROR, "Not enough memory to realloc");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

char* httpGet(const char* url) {
    CURL *curlHandle;
    CURLcode res;
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curlHandle = curl_easy_init();

    if (curlHandle) {
        curl_easy_setopt(curlHandle, CURLOPT_URL, url);
        curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curlHandle, CURLOPT_USERAGENT, USER_AGENT);

        res = curl_easy_perform(curlHandle);

        if (res != CURLE_OK) {
            logMessage(LOG_ERROR, "Network request failed: %s", curl_easy_strerror(res));
            free(chunk.memory);
            curl_easy_cleanup(curlHandle);
            return NULL;
        }

        curl_easy_cleanup(curlHandle);
    }
    curl_global_cleanup();
    return chunk.memory;
}

int downloadFile(const char* url, const char* filename) {
    CURL *curl;
    FILE *fp;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(filename, "wb");
        if(!fp) {
            logMessage(LOG_ERROR, "Could not open file %s for writing", filename);
            return 0;
        }

        logMessage(LOG_INFO, "Downloading file: %s", filename);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);

        if(res == CURLE_OK) return 1;

        logMessage(LOG_ERROR, "Download transfer failed: %s", curl_easy_strerror(res));
    }
    return 0;
}
