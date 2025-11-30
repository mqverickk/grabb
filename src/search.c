#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "grabb.h"

void searchPlugin(const char* query) {
    char url[512];
    char *encodedQuery = curl_easy_escape(NULL, query, 0);
    snprintf(url, sizeof(url), "%s/search?query=%s&index=downloads&limit=10", BASE_URL, encodedQuery);
    curl_free(encodedQuery);

    logMessage(LOG_INFO, "Searching Modrinth for '%s'...", query);

    char *response = httpGet(url);
    if (!response) return;

    cJSON *json = cJSON_Parse(response);
    cJSON *hits = cJSON_GetObjectItemCaseSensitive(json, "hits");
    cJSON *hit;

    int i = 0;

    printf("\n %-25s | %-30s | %s\n", "ID (Slug)", "Name", "Author");
    printf("--------------------------------------------------------------------------------\n");

    cJSON_ArrayForEach(hit, hits) {
        cJSON *title = cJSON_GetObjectItemCaseSensitive(hit, "title");
        cJSON *slug = cJSON_GetObjectItemCaseSensitive(hit, "slug");
        cJSON *author = cJSON_GetObjectItemCaseSensitive(hit, "author");

        if (cJSON_IsString(title) && cJSON_IsString(slug)) {
            char safeSlug[25];
            char safeTitle[30];
            char safeAuthor[20];

            snprintf(safeSlug, sizeof(safeSlug), "%s", slug->valuestring);
            snprintf(safeTitle, sizeof(safeTitle), "%s", title->valuestring);
            snprintf(safeAuthor, sizeof(safeAuthor), "%s", author ? author->valuestring : "Unknown");

            printf(" %-25s | %-30s | %s\n", safeSlug, safeTitle, safeAuthor);
        }
        i++;
    }
    printf("--------------------------------------------------------------------------------\n");
    logMessage(LOG_INFO, "Found %d plugins matching '%s'.", i, query);

    cJSON_Delete(json);
    free(response);
}
