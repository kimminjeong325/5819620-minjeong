#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

float totalComparisons = 0.0;
float totalMoveCount = 0.0;
int isFirst = 0;
int comparisonCount = 0;
int moveCount = 0;
int rounds = 0;

void printArray(int list[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
}

int partition(int list[], int left, int right) {
    int pivot, temp;
    int low = left, high = right + 1;

    pivot = list[left];

    do {
        // low 인덱스가 pivot보다 큰 값을 찾을 때까지 반복
        do {
            low++;
            comparisonCount++;  // 비교 횟수 증가
        } while (low <= right && list[low] < pivot);

        // high 인덱스가 pivot보다 작은 값을 찾을 때까지 반복
        do {
            high--;
            comparisonCount++;  // 비교 횟수 증가
        } while (high >= left && list[high] > pivot);

        // low와 high가 교차하지 않으면 값 교환
        if (low < high) {
            SWAP(list[low], list[high], temp);
            moveCount += 3;  // x와 y의 교환 + temp 사용 (3번 이동)
        }
    } while (low < high);  // low와 high가 교차하기 전까지 반복

    // pivot을 정확한 위치로 교환
    SWAP(list[left], list[high], temp);
    moveCount += 3;  // x와 y의 교환 + temp 사용 (3번 이동)
    return high;
}

void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000;  // 0~999의 랜덤 숫자 생성
    }
}

void doQuickSort(int* array, int left, int right) {
    int stack[SIZE];  // 스택을 이용한 반복문 처리
    int top = -1;
    stack[++top] = left;  // 처음 왼쪽 인덱스를 스택에 푸시
    stack[++top] = right;  // 처음 오른쪽 인덱스를 스택에 푸시

    while (top >= 0) {
        right = stack[top--];  // 오른쪽 인덱스 꺼내기
        left = stack[top--];   // 왼쪽 인덱스 꺼내기

        if (left < right) {
            int q = partition(array, left, right);  // pivot을 기준으로 분할

            // 분할된 왼쪽 부분을 스택에 푸시
            stack[++top] = left;
            stack[++top] = q - 1;

            // 분할된 오른쪽 부분을 스택에 푸시
            stack[++top] = q + 1;
            stack[++top] = right;
        }

        // rounds마다 중간 결과 출력 (첫 번째 실행에서만)
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++)
                printf("%d ", array[i]);
            printf("\n\n");
        }
        rounds++;  // rounds 증가
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);  // 새로운 랜덤 데이터 생성
        comparisonCount = 0;  // 비교 횟수 초기화
        moveCount = 0;        // 이동 횟수 초기화

        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);  // 첫 번째 정렬 수행
            printf("Result\n");
            printArray(array, SIZE);  // 결과 출력
            isFirst++;  // 첫 번째 출력이 완료되었으므로 isFirst 증가
        }
        else {
            doQuickSort(array, 0, SIZE - 1);  // 이후 정렬 수행
        }

        // 전체 비교 횟수와 이동 횟수에 더하기
        totalComparisons += comparisonCount;  // 전체 비교 횟수에 더하기
        totalMoveCount += moveCount;          // 전체 이동 횟수에 더하기
    }

    // 평균 비교 횟수와 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
