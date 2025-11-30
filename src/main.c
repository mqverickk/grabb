/*
Grabb is a tools to grab your needed plugins for your Minecraft server just from the terminal.
Github: https://github.com/mqverickk
*/

#include <stdio.h>
#include <string.h>
#include "grabb.h"

#define ASCII_ART \
"                  _     _     \n" \
"                 | |   | |    \n" \
"   __ _ _ __ __ _| |__ | |__  \n" \
"  / _` | '__/ _` | '_ \\| '_ \\ \n" \
" | (_| | | | (_| | |_) | |_) |\n" \
"  \\__, |_|  \\__,_|_.__/|_.__/ \n" \
"   __/ |                      \n" \
"  |___/                       \n" \
" Grabb - A tools to grab your plugins\n" \
" Github: https://github.com/mqverickk" \
""

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("%s\n", ASCII_ART);
        printf("\nUsage:\n");
        printf("  grabb -f <query>              Search for plugins\n");
        printf("  grabb -stats <slug>           Show plugin stats\n");
        printf("  grabb -p <slug> -v <ver> -s <loader>  Download plugin\n");
        return 1;
    }

    if (strcmp(argv[1], "-f") == 0) {
        if (argc >= 3) {
            searchPlugin(argv[2]);
        } else {
            logMessage(LOG_ERROR, "Missing search query. Usage: grabb -f <query>");
        }
    }
    else if (strcmp(argv[1], "-stats") == 0) {
        if (argc >= 3) {
            getStats(argv[2]);
        } else {
             logMessage(LOG_ERROR, "Missing slug. Usage: grabb -stats <slug>");
        }
    }
    else if (strcmp(argv[1], "-p") == 0) {
        char *slug = NULL;
        char *version = NULL;
        char *loader = NULL;

        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-p") == 0 && i+1 < argc) slug = argv[i+1];
            if (strcmp(argv[i], "-v") == 0 && i+1 < argc) version = argv[i+1];
            if (strcmp(argv[i], "-s") == 0 && i+1 < argc) loader = argv[i+1];
        }

        if (slug && version && loader) {
            downloadPlugin(slug, version, loader);
        } else {
            logMessage(LOG_ERROR, "Missing arguments. Required: -p <slug> -v <version> -s <loader>");
        }
    } else {
        logMessage(LOG_ERROR, "Unknown command: %s", argv[1]);
    }

    return 0;
}
