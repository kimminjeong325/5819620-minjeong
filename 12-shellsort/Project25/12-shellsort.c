#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ARRAY_SIZE 100  // 배열 크기 정의

// 배열 출력 함수
void print_list(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%02d ", list[i]);  // 세 자리 형식으로 출력
    }
    printf("\n");
}

// Shell Sort에서 gap을 사용한 삽입 정렬 수행 함수
void gap_insertion_sort(int list[], int first, int last, int gap, int* comparisonCount, int* moveCount) {
    int i, j, key;

    for (i = first + gap; i <= last; i += gap) {
        key = list[i];
        (*moveCount)++;  // key 값을 복사한 이동 카운트
        for (j = i - gap; j >= first; j -= gap) {
            (*comparisonCount)++;  // 비교 카운트 증가
            if (list[j] > key) {
                list[j + gap] = list[j];  // 값 이동
                (*moveCount)++;
            }
            else {
                break;  // key보다 작으면 종료
            }
        }
        list[j + gap] = key;  // key 삽입
        (*moveCount)++;
    }
}

// 배열에 랜덤 숫자 생성
void generateRandomNumbers(int list[], int n) {
    for (int i = 0; i < n; i++) {
        list[i] = rand() % 1000;  // 0 ~ 999 사이의 랜덤 숫자 생성
    }
}

// Shell Sort 수행 및 결과 출력
void doShellSort(const int list[], int num, int n, int* avgComparisonCount, int* avgMoveCount) {
    int tempArray[ARRAY_SIZE];  // 임시 배열
    int totalComparisonCount = 0, totalMoveCount = 0;

    // 초기 배열 복사
    for (int i = 0; i < n; i++) {
        tempArray[i] = list[i];
    }

    // Shell Sort 과정
    for (int gap = n / num; gap > 0; gap /= num) {
        int comparisonCount = 0, moveCount = 0;

        for (int i = 0; i < gap; i++) {
            // gap 크기마다 삽입 정렬 수행
            gap_insertion_sort(tempArray, i, n - 1, gap, &comparisonCount, &moveCount);
        }

        // 각 gap 단계 결과 출력 (최대 20개만 출력)
        printf("Sorting with gap = %d:\n", gap);
        for (int i = 0; i < 20 && i < n; i++) {
            printf("%03d ", tempArray[i]);
        }
        if (n > 20) printf("...\n\n");
        else printf("\n\n");
    }

    // 최종 정렬된 배열 출력
    printf("Sorted shellArray (gap = %d):\n", num);
    print_list(tempArray, n);
    printf("\n");

    // 평균 비교 및 이동 횟수 계산 (20번 반복)
    for (int repeat = 0; repeat < 20; repeat++) {
        for (int i = 0; i < n; i++) {
            tempArray[i] = list[i];  // 정렬 전 초기화
        }

        int comparisonCount = 0, moveCount = 0;

        for (int gap = n / num; gap > 0; gap /= num) {
            for (int j = 0; j < gap; j++) {
                gap_insertion_sort(tempArray, j, n - 1, gap, &comparisonCount, &moveCount);
            }
        }

        totalComparisonCount += comparisonCount;  // 비교 횟수 누적
        totalMoveCount += moveCount;  // 이동 횟수 누적
    }

    *avgComparisonCount = totalComparisonCount / 20;  // 평균 비교 횟수
    *avgMoveCount = totalMoveCount / 20;  // 평균 이동 횟수
}

// 삽입 정렬 수행 및 결과 출력
void doInsertionSort(const int list[], int* avgComparisonCount, int* avgMoveCount) {
    int tempArray[ARRAY_SIZE];
    int totalComparisonCount = 0, totalMoveCount = 0;

    // 20번 반복하여 평균 계산
    for (int repeat = 0; repeat < 20; repeat++) {
        int randomArray[ARRAY_SIZE];
        generateRandomNumbers(randomArray, ARRAY_SIZE);  // 새로운 랜덤 배열 생성

        for (int i = 0; i < ARRAY_SIZE; i++) {
            tempArray[i] = randomArray[i];  // 랜덤 배열 복사
        }

        int comparisonCount = 0, moveCount = 0;

        // 삽입 정렬 수행
        for (int i = 1; i < ARRAY_SIZE; i++) {
            int key = tempArray[i];
            moveCount++;
            int j = i - 1;

            while (j >= 0 && tempArray[j] > key) {
                comparisonCount++;
                tempArray[j + 1] = tempArray[j];
                moveCount++;
                j--;
            }
            if (j >= 0) comparisonCount++;
            tempArray[j + 1] = key;
            moveCount++;
        }

        totalComparisonCount += comparisonCount;  // 비교 횟수 누적
        totalMoveCount += moveCount;  // 이동 횟수 누적

        // 마지막 반복에서 정렬된 배열 출력
        if (repeat == 19) {
            printf("Sorted Insertion Sort Array:\n");
            print_list(tempArray, ARRAY_SIZE);
        }
    }

    *avgComparisonCount = totalComparisonCount / 20;  // 평균 비교 횟수
    *avgMoveCount = totalMoveCount / 20;  // 평균 이동 횟수
    printf("\n");
}

// 프로그램 시작
int main() {
    srand(time(NULL));  // 랜덤 시드 초기화

    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    generateRandomNumbers(array, ARRAY_SIZE);  // 랜덤 배열 생성

    // Shell Sort (gap = n/2)
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, ARRAY_SIZE, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Shell Sort (gap = n/3)
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, ARRAY_SIZE, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Insertion Sort
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}

