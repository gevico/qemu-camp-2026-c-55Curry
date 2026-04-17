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
    int l_n = mid - left + 1;
    int r_n = right - mid;

    Student *l = malloc(sizeof(Student) * l_n);
    Student *r = malloc(sizeof(Student) * r_n);

    for (size_t i = 0; i < l_n; i++) {
        /* code */
        l[i] = students[left + i];
    }

    for (size_t i = 0; i < r_n; i++) {
        /* code */
        r[i] = students[mid + i + 1];
    }

    int n = 0, m = 0, k = left;

    while (n < l_n && m < r_n) {
        if (l[n].score >= r[m].score) {
            students[k] = l[n];
            n++;
        } else {
            students[k] = r[m];
            m++;
        }
        k++;
    }

    while (n < l_n) {
        /* code */
        students[k] = l[n];
        k++;
        n++;
    }

    while (m < r_n) {
        /* code */
        students[k] = r[m];
        k++;
        m++;
    }

    free(l);
    free(r);
}

void merge_sort(int left, int right) {
    if (left >= right) {
        /* code */
        return;
    }

    int mid = (left + right) / 2;

    merge_sort(left, mid);
    merge_sort(mid + 1, right);

    merge(left, mid, right);
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