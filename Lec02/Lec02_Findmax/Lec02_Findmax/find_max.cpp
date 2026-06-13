#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define MAX_ELEMENTS 100

int score[MAX_ELEMENTS];

int find_max_score(int n) {
    int i, tmp;
    tmp = score[0];
    for (i = 1; i < n; i++) {
        if (score[i] > tmp) {
            tmp = score[i];
        }
    }
    return tmp;
}

int main() {
    int n;
    printf("원소 개수 입력: ");
    scanf("%d", &n);
    printf("%d개의 점수 입력: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &score[i]);
    printf("최대값 = %d\n", find_max_score(n));
    return 0;
}
