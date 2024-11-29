#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int sorted[SIZE];
int comparisonCount;
int moveCount;
float totalComparisons = 0.0;
float totalMoves = 0.0;
int isFirst = 0;
int rounds = 0;

void printArray(int* array, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

void merge(int list[], int left, int mid, int right) {
    int i, j, k, l;
    i = left; j = mid + 1; k = left;

    // 분할 정렬된 list의 합병
    while (i <= mid && j <= right) {
        comparisonCount++;  // 비교 횟수 증가

        if (list[i] <= list[j]) {
            moveCount++;
            sorted[k++] = list[i++];
        }
        else {
            sorted[k++] = list[j++];
        }
        moveCount++;
    }


    if (i > mid) {    // 남아 있는 레코드의 일괄 복사
        for (l = j; l <= right; l++) {
            sorted[k++] = list[l];
            moveCount++;  // 이동 횟수 증가
        }
    }
    else {    // 남아 있는 레코드의 일괄 복사
        for (l = i; l <= mid; l++) {
            sorted[k++] = list[l];
            moveCount++;  // 이동 횟수 증가
        }
    }

    // 배열 sorted[]의 리스트를 배열 list[]로 복사
    for (l = left; l <= right; l++) {
        list[l] = sorted[l];
        moveCount++;  // 이동 횟수 증가 (배열을 list로 복사할 때)
    }

    rounds++; // 병합 라운드 증가

    if (rounds % 10 == 0 && isFirst == 0) { // 10번에 한번만 출력
        for (int i = 0; i < 10; i++) // 처음 10개 요소 출력
            printf("%3d ", list[i]);
        printf("| ");
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) // 중앙 근처의 10개 요소 출력
            printf("%3d ", list[i]);
        printf("\n\n");
    }
}

void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0 ~ 999 범위의 랜덤 숫자 생성
    }
}

// 반복적 방법으로 합병정렬 구현
void doMergeSort(int* array, int left, int right) {
    int size, i, leftStart, mid, rightEnd;

    // 반복적으로 병합할 크기(1부터 시작하여 2배씩 늘어남)
    for (size = 1; size < SIZE; size = size * 2) {
        // 병합 작업
        for (leftStart = 0; leftStart < SIZE; leftStart += 2 * size) {
            mid = leftStart + size - 1;
            rightEnd = (leftStart + 2 * size - 1) < SIZE ? leftStart + 2 * size - 1 : SIZE - 1;

            // mid가 배열의 범위 내에 있을 경우 병합
            if (mid < SIZE) {
                merge(array, leftStart, mid, rightEnd);  // 병합 작업 호출
            }
        }
    }
}

int main() {
    srand(time(NULL));

    int array[SIZE];

    // 20번 반복
    for (int i = 0; i < 20; i++) {
        // 랜덤 배열 생성
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        // 첫 번째 실행에서만 Merge Sort Run 출력
        if (i == 0) {
            printf("Merge Sort Run\n");
            doMergeSort(array, 0, SIZE - 1);

            // 첫 번째 실행 결과 출력
            printf("Result\n");
            printArray(array, SIZE);
            isFirst++; // 첫 번째 실행 완료
        }
        else {
            // 그 이후에는 그냥 병합 정렬만 수행
            doMergeSort(array, 0, SIZE - 1);
        }

        // 비교 횟수와 이동 횟수를 전체 합산
        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    // 평균 비교 횟수와 평균 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
