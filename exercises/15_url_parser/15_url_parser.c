#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char *url) {
    int err = 0;

    const char *pair = strchr(url, '?');
    if (pair == NULL) {
        return -1;
    }

    pair++;

    char buffer[1024];

    strncpy(buffer, pair, sizeof(buffer) - 1);

    char *token = strtok(buffer, "&");

    while (token != NULL) {
        char *index = strchr(token, '=');
        if (index) {
            *index = '\0';
            char *key = token;
            char *value = index + 1;

            printf("%s : %s \n", key, value);
        }
        token = strtok(NULL, "&");
    }
exit:
    return err;
}

int main() {
    const char *test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}