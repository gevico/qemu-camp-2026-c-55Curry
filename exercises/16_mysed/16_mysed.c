#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    char* buffer = strdup(cmd + 2);
    if (buffer == NULL) {
        return -1;
    }

    char* first = strtok(buffer, "/");
    if (first == NULL) {
        free(buffer);
        return -1;
    }
    *old_str = strdup(first);

    char* second = strtok(NULL, "/");
    if (second == NULL) {
        free(buffer);
        free(first);
        return -1;
    }

    *new_str = strdup(second);
    free(buffer);

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    char* index = strstr(str, old);
    if (index == NULL) {
        return;
    }

    int oldLen = strlen(old);
    int newLen = strlen(new);

    int tail = strlen(index + oldLen) + 1;

    memmove(index + newLen, index + oldLen, tail);

    memcpy(index, new, newLen);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;

    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
