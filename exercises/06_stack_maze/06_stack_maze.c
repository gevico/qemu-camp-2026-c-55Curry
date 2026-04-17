#include <stdbool.h>
#include <stdio.h>
#define MAX_ROW 5
#define MAX_COL 5

typedef struct {
    int r, c;
} Point;

int maze[MAX_ROW][MAX_COL] = {
    0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0,
};

Point stack[MAX_COL * MAX_ROW];
int top = -1;

Point predecessor[MAX_ROW][MAX_COL];

void push(Point p) { stack[top++] = p; }

Point pop() { return stack[top--]; }

bool is_empty() { return top == -1; }

void solve() {
    for (int i = 0; i < MAX_ROW; i++) {
        for (size_t j = 0; j < MAX_COL; j++) {
            /* code */
            predecessor[i][j] = (Point){-1, -1};
        }
    }

    Point start = {0, 0};
    Point end = {4, 4};

    push(start);
    maze[0][0] = 2;

    while (!is_empty()) {
        Point curr = pop();

        if (end.c == curr.c && end.r == curr.r) {
            Point p = end;
            while (p.r != -1) {
                printf("(%d, %d)\n", p.r, p.c);
                p = predecessor[p.r][p.c];
            }
            return;
        }

        int dr[] = {1, 0, -1, 0};
        int dc[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {
            int nr = dr[i] + curr.r;
            int nc = dc[i] + curr.c;

            if (nr >= 0 && nr < MAX_ROW && nc >= 0 && nc < MAX_COL && maze[nr][nc] == 0) {
                /* code */
                maze[nr][nc] = 2;
                push((Point){nr, nc});
                predecessor[nr][nc] = curr;
            }
        }
    }
    printf("No path!\n");
}
int main(void) {
    solve();
    return 0;
}