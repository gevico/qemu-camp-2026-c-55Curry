// mytrans.c
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myhash.h"

void trim(char *str) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
    if (str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }
    int j = 0;
    while (isspace(str[j])) {
        j++;
    }
    if (j > 0) {
        memmove(str, str + j, strlen(str + j) + 1);
    }

    int i = strlen(str) - 1;
    while (i > 0 && isspace(str[i])) {
        str[i] = '\0';
        i--;
    }
}

int load_dictionary(const char *filename, HashTable *table, uint64_t *dict_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("无法打开词典文件");
        return -1;
    }

    char line[1024];
    char current_word[100] = {0};
    char current_translation[1024] = {0};
    int in_entry = 0;

    while (fgets(line, sizeof(line), file)) {
        trim(line);
        if (line[0] == '#') {
            strncpy(current_word, line + 1, strlen(line) + 1);
        }

        if (line[0] == 'T') {
            strncpy(current_translation, line + 6, strlen(line) + 1);

            hash_table_insert(table, current_word, current_translation);

            current_word[0] = '\0';
            current_translation[0] = '\0';
            (*dict_count)++;
        }
    }

    fclose(file);
    return 0;
}
