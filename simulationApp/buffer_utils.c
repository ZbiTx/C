#include "buffer_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void clear_buffer () {
    while (1) {
        int c = getc(stdin);
        if (c == EOF || c == '\n') {
            break;
        }
    }
}

void rplcgaps(char* string) { 
    bool modified = 0;
    for (size_t i=0; string[i] != '\0'; i++) {
        if (string[i] == ' ') {
            string[i] = '_';
            modified = 1;
        }
    }
    if (modified) { 
        printf("\033[31mUse of keycode 32 error.\033[0m New String: %s\n", string);
    }
}

