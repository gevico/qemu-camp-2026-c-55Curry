#include <stdio.h>

int main() {
    char str[] = "Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    int inWord = 0;

    for (size_t i = 0; str[i] != '.'; i++) {
        /* code */
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '.') {
            inWord = 0;
        } else if (inWord == 0) {
            inWord = 1;
            wordCount++;
        }
    }

    printf("单词数量: %d\n", wordCount);
    return 0;
}