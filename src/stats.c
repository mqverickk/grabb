#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "grabb.h"

void getStats(const char* targetSlug) {
    char url[512];

    char *encodedQuery = curl_easy_escape(NULL, targetSlug, 0);
    snprintf(url, sizeof(url), "%s/search?query=%s", BASE_URL, encodedQuery);
    curl_free(encodedQuery);

    logMessage(LOG_INFO, "Fetching statistics for '%s'...", targetSlug);

    char *response = httpGet(url);
    if (!response) return;

    cJSON *json = cJSON_Parse(response);
    cJSON *hits = cJSON_GetObjectItemCaseSensitive(json, "hits");
    cJSON *hit;

    int found = 0;

    cJSON_ArrayForEach(hit, hits) {
        cJSON *slugJson = cJSON_GetObjectItemCaseSensitive(hit, "slug");

        if (cJSON_IsString(slugJson) && strcmp(slugJson->valuestring, targetSlug) == 0) {
            cJSON *title = cJSON_GetObjectItemCaseSensitive(hit, "title");
            cJSON *author = cJSON_GetObjectItemCaseSensitive(hit, "author");
            cJSON *downloads = cJSON_GetObjectItemCaseSensitive(hit, "downloads");
            cJSON *followers = cJSON_GetObjectItemCaseSensitive(hit, "follows");
            cJSON *desc = cJSON_GetObjectItemCaseSensitive(hit, "description");

            printf("\n");
            printf("  \033[1;36m%s\033[0m\n", title->valuestring); // Cyan title
            printf("  ------------------------\n");
            printf("  Author      : %s\n", author ? author->valuestring : "Unknown");
            printf("  Downloads   : %d\n", downloads ? downloads->valueint : 0);
            printf("  Followers   : %d\n", followers ? followers->valueint : 0);
            printf("  Description : %s\n", desc ? desc->valuestring : "No description");
            printf("\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        logMessage(LOG_WARN, "Plugin '%s' not found. Check the spelling or try searching via -f.", targetSlug);
    }

    cJSON_Delete(json);
    free(response);
}
