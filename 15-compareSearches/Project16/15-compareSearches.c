#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int compareCount; // 전역 변수로 퀵 정렬 비교 횟수 추적

// 순차 탐색 함수: 배열에서 키를 찾을 때까지 비교하며 탐색
int seq_search2(int key, int low, int high, int list[]) {
    int count = 0;
    for (int i = low; i <= high; i++) {
        count++; // 비교 횟수 증가
        if (list[i] == key) return count; // 키를 찾으면 비교 횟수 반환
    }
    return count; // 키를 찾지 못한 경우 비교 횟수 반환
}

// 이진 탐색 함수: 배열에서 키를 찾을 때까지 반씩 나누어 탐색
int search_binary2(int key, int low, int high, int list[]) {
    int middle, count = 0;
    while (low <= high) {
        count++; // 비교 횟수 증가
        middle = (low + high) / 2;
        if (key == list[middle]) return count; // 키를 찾으면 비교 횟수 반환
        else if (key > list[middle]) low = middle + 1; // 키가 중간 값보다 큰 경우 오른쪽 반 탐색
        else high = middle - 1; // 키가 중간 값보다 작은 경우 왼쪽 반 탐색
    }
    return count; // 키를 찾지 못한 경우 비교 횟수 반환
}

// 배열 출력 함수: 배열의 앞 20개와 뒤 20개 요소를 출력
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) {
        printf("%3d ", array[i]); // 배열의 처음 20개 요소 출력
    }
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%3d ", array[i]); // 배열의 마지막 20개 요소 출력
    }
    printf("\n\n");
}

// 랜덤 배열 생성 함수: 배열을 0~999 사이의 난수로 채움
void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000; // 0에서 999 사이의 난수 생성
    }
}

// 퀵 정렬 파티션 함수: 피벗을 기준으로 배열을 나누고 비교 횟수를 추적
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;
    pivot = list[left]; // 피벗 설정
    low = left;
    high = right + 1;

    do {
        do {
            low++;
            compareCount++; // 조건 비교 횟수 증가
        } while (low <= right && list[low] < pivot);

        do {
            high--;
            compareCount++; // 조건 비교 횟수 증가
        } while (high >= left && list[high] > pivot);

        if (low < high) {
            compareCount++; // 스왑 전 마지막 비교
            SWAP(list[low], list[high], temp); // 값 교환
        }
    } while (low < high);

    compareCount++; // 피벗과의 마지막 비교
    SWAP(list[left], list[high], temp); // 피벗 위치 교환
    return high; // 피벗 위치 반환
}

// 퀵 정렬 함수: 재귀적으로 배열을 정렬
void doQuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right); // 파티션 수행
        doQuickSort(list, left, q - 1); // 왼쪽 부분 배열 정렬
        doQuickSort(list, q + 1, right); // 오른쪽 부분 배열 정렬
    }
}

// 순차 탐색 평균 비교 횟수 계산 함수
float getAverageLinearSearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; // 배열에서 랜덤 키 선택
        totalComparisons += seq_search2(target, 0, SIZE - 1, array); // 탐색 수행 및 비교 횟수 누적
    }
    return totalComparisons / 100.0; // 평균 비교 횟수 반환
}

// 퀵 정렬 비교 횟수 계산 함수
void getQuickSortCompareCount(int list[]) {
    compareCount = 0; // 비교 횟수 초기화
    doQuickSort(list, 0, SIZE - 1); // 정렬 수행 및 비교 횟수 추적
}

// 이진 탐색 평균 비교 횟수 계산 함수
float getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; // 배열에서 랜덤 키 선택
        totalComparisons += search_binary2(target, 0, SIZE - 1, array); // 탐색 수행 및 비교 횟수 누적
    }
    return totalComparisons / 100.0; // 평균 비교 횟수 반환
}

// 메인 함수: 프로그램 실행의 시작점
int main(int argc, char* argv[]) {
    srand(time(NULL)); // 난수 생성기 초기화
    int array[SIZE];

    for (int i = 1; i <= 3; i++) {
        generateRandomArray(array);  // 랜덤 배열 생성

        // 순차 탐색 평균 비교 횟수 출력
        printf("Average Linear Search Compare Count: %.2f\n",
            getAverageLinearSearchCompareCount(array));

        // 퀵 정렬 비교 횟수 계산
        getQuickSortCompareCount(array);
        printf("Quick Sort Compare Count: %d\n", compareCount);

        // 정렬된 배열에 대해 이진 탐색 100회 평균 비교 횟수 출력
        printf("Average Binary Search Compare Count: %.2f\n\n",
            getAverageBinarySearchCompareCount(array));

        // 배열 출력
        printArray(array);

        Sleep(1000); // 1초 대기
    }
    return 0; // 프로그램 종료
}
