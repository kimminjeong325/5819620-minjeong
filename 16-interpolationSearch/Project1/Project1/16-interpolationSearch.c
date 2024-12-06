#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<windows.h>  // Windows에서 Sleep 함수 사용을 위한 헤더 파일

#define SIZE 1000  // 배열 크기 정의
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))  // 두 값 교환 매크로

// 배열의 처음 20개와 끝 20개 원소를 출력하는 함수
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)  // 배열의 처음 20개 원소 출력
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)  // 배열의 끝 20개 원소 출력
        printf("%4d ", array[i]);
    printf("\n\n");
}

// 랜덤한 배열을 생성하는 함수
void generateRandomArray(int list[]) {
    Sleep(100);  // 난수 생성 전에 잠시 대기 (시뮬레이션)

    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 10000;  // 0~9999 범위의 랜덤 값으로 배열 채우기
    }
}

// 퀵정렬에서 사용하는 파티션 함수
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;
    pivot = list[left];  // 피벗은 배열의 첫 번째 값
    low = left;
    high = right + 1;

    do {
        // 피벗보다 큰 값을 찾을 때까지 low를 증가
        do
            low++;
        while (low <= right && list[low] < pivot);

        // 피벗보다 작은 값을 찾을 때까지 high를 감소
        do
            high--;
        while (list[high] > pivot);

        // low가 high보다 작으면, 두 값을 교환
        if (low < high) SWAP(list[low], list[high], temp);
    } while (low < high);  // low가 high보다 작으면 반복

    SWAP(list[left], list[high], temp);  // 피벗을 적절한 위치로 이동
    return high;  // 피벗이 위치한 인덱스를 반환
}

// 퀵정렬 함수
void QuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);  // 파티션 수행
        QuickSort(list, left, q - 1);  // 왼쪽 부분을 재귀적으로 정렬
        QuickSort(list, q + 1, right);  // 오른쪽 부분을 재귀적으로 정렬
    }
}

// 이진 탐색 함수 (비교 횟수를 추적)
int search_binary2(int key, int low, int high, int list[], int* comparisonCount) {
    int middle;
    while (low <= high) {
        (*comparisonCount)++;  // low와 high 비교: 범위가 유효한지 비교
        middle = (low + high) / 2;  // 중간 인덱스 계산

        (*comparisonCount)++;  // 중간값과 key 비교
        if (key == list[middle]) {  // key가 중간값과 일치하면 성공
            return middle;
        }
        else if (key > list[middle]) {  // key가 중간값보다 크면 오른쪽 부분 탐색
            low = middle + 1;
        }
        else {  // key가 중간값보다 작으면 왼쪽 부분 탐색
            high = middle - 1;
        }
    }
    return -1;  // key를 찾지 못한 경우
}

// 이진 탐색의 평균 비교 횟수 계산 함수
float getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;  // 전체 비교 횟수 초기화
    for (int i = 0; i < SIZE; i++) {
        int target = array[rand() % SIZE];  // 랜덤한 타겟 값 선택
        int comparisonCount = 0;  // 해당 탐색에 대한 비교 횟수 초기화
        search_binary2(target, 0, SIZE - 1, array, &comparisonCount);  // 이진 탐색 수행
        totalComparisons += comparisonCount;  // 비교 횟수 합산
    }
    return (float)totalComparisons / SIZE;  // 평균 비교 횟수 반환
}

// 보간 탐색 함수 (비교 횟수를 추적)
int interpol_search(int key, int n, int list[], int* comparisonCount) {
    int low = 0, high = n - 1, j;

    while (low <= high && key >= list[low] && key <= list[high]) {  // 범위가 유효한지 확인
        (*comparisonCount)++;  // low, high, key 비교

        if (list[high] == list[low]) {  // low와 high가 동일하면 범위가 좁혀짐
            if (list[low] == key) {  // key가 일치하면 찾은 것
                (*comparisonCount)++;  // key == list[low] 비교
                return low;
            }
            else {
                return -1;  // key를 찾지 못함
            }
        }

        // 보간 공식으로 중간 위치 계산
        j = low + ((double)(key - list[low]) / (list[high] - list[low])) * (high - low);

        if (j < low || j > high) {  // 중간 위치가 유효하지 않으면 종료
            break;
        }

        if (key == list[j]) {  // key와 일치하면 찾은 것
            return j;
        }
        else if (key < list[j]) {  // key가 중간값보다 작으면 왼쪽 범위 탐색
            high = j - 1;
        }
        else {  // key가 중간값보다 크면 오른쪽 범위 탐색
            low = j + 1;
        }
    }

    return -1;  // key를 찾지 못함
}

// 보간 탐색의 평균 비교 횟수 계산 함수
float getAverageInterpolationSearchCompareCount(int array[]) {
    int totalComparisons = 0;  // 전체 비교 횟수 초기화
    for (int i = 0; i < SIZE; i++) {
        int target = array[rand() % SIZE];  // 랜덤한 타겟 값 선택
        int comparisonCount = 0;  // 해당 탐색에 대한 비교 횟수 초기화
        interpol_search(target, SIZE, array, &comparisonCount);  // 보간 탐색 수행
        totalComparisons += comparisonCount;  // 비교 횟수 합산
    }
    return (float)totalComparisons / SIZE;  // 평균 비교 횟수 반환
}

// 메인 함수
int main(int argc, char* argv[]) {
    srand(time(NULL));  // 난수 시드 초기화

    int array[SIZE];  // 배열 선언

    // 3번의 실험 수행
    for (int i = 1; i <= 3; i++) {
        generateRandomArray(array);  // 랜덤 배열 생성
        QuickSort(array, 0, SIZE - 1);  // 배열 퀵정렬 수행
        printArray(array);  // 정렬된 배열 출력

        // 이진 탐색의 평균 비교 횟수 출력
        printf("Average Compare Count of Binary Search: %.2f\n",
            getAverageBinarySearchCompareCount(array));

        // 보간 탐색의 평균 비교 횟수 출력
        printf("Average Compare Count of Interpolation Search: %.2f\n\n",
            getAverageInterpolationSearchCompareCount(array));

        Sleep(1000);  // 1초 대기 (다음 실험 전)
    }

    return 0;  // 프로그램 종료
}
