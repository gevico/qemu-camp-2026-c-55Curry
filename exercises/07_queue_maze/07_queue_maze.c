#include <stdbool.h>
#include <stdio.h>
#define MAX_ROW 5
#define MAX_COL 5
typedef struct {
    int r, c;
    int pre;
} Point;

int maze[MAX_ROW][MAX_COL] = {
    0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0,
};

int visited[MAX_ROW][MAX_COL] = {0};

Point queue[MAX_COL * MAX_ROW];
int head = 0;
int tail = 0;

void enqueue(Point p) { queue[tail++] = p; }

Point dequeue() { queue[head++]; }

bool is_empty() { return head == tail; }

bool is_vail(int c, int r) { return (c >= 0 && c < MAX_COL && r >= 0 && r < MAX_ROW && visited[r][c] == 0); }

void printf_path(int index) {
    if (queue[index].pre != -1) {
        printf_path(queue[index].pre);
    }

    printf("(%d, %d)\n", queue[index].r, queue[index].c);
}

void solve() {
    Point start = {0, 0, -1};
    Point end = {4, 4, -1};
    enqueue(start);
    visited[0][0] = 1;

    int dr[] = {1, 0, -1, 0};
    int dc[] = {0, 1, 0, -1};

    int found = 0;
    while (!is_empty()) {
        int current_index = head;
        Point cur = dequeue();

        if (cur.c == end.c && cur.r == end.r) {
            found = 1;
            printf_path(current_index);
            break;
        }

        for (size_t i = 0; i < 4; i++) {
            /* code */
            int next_r = cur.r + dr[i];
            int next_c = cur.c + dc[i];

            if (is_vail(next_c, next_r)) {
                visited[next_r][next_c] == 1;
                Point next_p = {next_r, next_c, current_index};
                enqueue(next_p);
            }
        }
    }
    if (!found) printf("没有可行路径。\n");
    return 0;
}

int main(void) {
    // TODO: 在这里添加你的代码
    // I AM NOT DONE
    solve();
    return 0;
}