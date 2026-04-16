#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];
Student temp[MAX_STUDENTS];

void merge(int left, int mid, int right) {
    int r_n = 0, l_n = 0, k = left;

    int n1 = mid - left + 1;
    int n2 = right - mid;

    Student *l = malloc(sizeof(Student) * n1);
    Student *r = malloc(sizeof(Student) * n2);

    for (size_t i = 0; i < n1; i++) {
        l[i] = students[i + left];
    }

    for (size_t i = 0; i < n2; i++) {
        /* code */
        r[i] = students[i + mid + 1];
    }

    while (l_n < n1 && r_n < n2) {
        if (l[l_n].score >= r[r_n].score) {
            students[k] = l[l_n];
            l_n++;
        } else {
            students[k] = r[r_n];
            r_n++;
        }
        k++;
    }

    while (l_n < n1) {
        students[k] = l[l_n];
        l_n++;
        k++;
    }

    while (r_n < n2) {
        students[k] = r[r_n];
        r_n++;
        k++;
    }

    free(l);
    free(r);
}

void merge_sort(int left, int right) {
    if (left < right) {
        int mid = (right + left) / 2;
        merge_sort(left, mid);
        merge_sort(mid + 1, right);

        merge(left, mid, right);
    }
}

int main(void) {
    FILE *file = fopen("02_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 02_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d\n", n);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    merge_sort(0, n - 1);

    printf("\n归并排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}