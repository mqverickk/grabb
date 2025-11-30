#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "grabb.h"

void downloadPlugin(const char* projectId, const char* version, const char* loader) {
    char url[512];
    snprintf(url, sizeof(url), "%s/project/%s/version", BASE_URL, projectId);

    logMessage(LOG_INFO, "Resolving version for '%s' (v%s, %s)...", projectId, version, loader);

    char *response = httpGet(url);
    if (!response) {
        logMessage(LOG_ERROR, "Failed to connect to version endpoint.");
        return;
    }

    cJSON *versionsArray = cJSON_Parse(response);
    if (!versionsArray) {
         logMessage(LOG_ERROR, "Failed to parse API response.");
         free(response);
         return;
    }

    cJSON *verObj;
    int found = 0;

    cJSON_ArrayForEach(verObj, versionsArray) {
        cJSON *loaders = cJSON_GetObjectItemCaseSensitive(verObj, "loaders");
        cJSON *gameVersions = cJSON_GetObjectItemCaseSensitive(verObj, "game_versions");
        int loaderMatch = 0;
        int versionMatch = 0;

        cJSON *l;
        cJSON_ArrayForEach(l, loaders) {
            if (strcmp(l->valuestring, loader) == 0) loaderMatch = 1;
        }

        cJSON *v;
        cJSON_ArrayForEach(v, gameVersions) {
            if (strcmp(v->valuestring, version) == 0) versionMatch = 1;
        }

        if (loaderMatch && versionMatch) {
            cJSON *files = cJSON_GetObjectItemCaseSensitive(verObj, "files");
            cJSON *primaryFile = cJSON_GetArrayItem(files, 0);

            if (primaryFile) {
                cJSON *fileUrl = cJSON_GetObjectItemCaseSensitive(primaryFile, "url");
                cJSON *filename = cJSON_GetObjectItemCaseSensitive(primaryFile, "filename");

                if (downloadFile(fileUrl->valuestring, filename->valuestring)) {
                    logMessage(LOG_SUCCESS, "Saved as %s", filename->valuestring);
                } else {
                    logMessage(LOG_ERROR, "Download operation failed.");
                }
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        logMessage(LOG_WARN, "No version found matching: Project: %s | Game: %s | Loader: %s", projectId, version, loader);
        logMessage(LOG_INFO, "Try checking the available versions on the Modrinth website.");
    }

    cJSON_Delete(versionsArray);
    free(response);
}
