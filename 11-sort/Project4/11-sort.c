#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void print_list(int list[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
}

// 선택 정렬 함수 - 정렬 과정 중 10번째부터 20번째 간격으로, 그리고 마지막 단계에서 중간 결과 출력
void selection_sort(int list[], int n)
{
    int i, j, least, temp;
    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[least])
                least = j;
        SWAP(list[i], list[least], temp);

        // 정렬 과정 출력 조건: 10번째부터 시작해서 20단위로 출력, 마지막 단계 출력
        if ((i + 1) >= 10 && (i + 1 - 10) % 20 == 0 || i == n - 2) {
            printf("Step %d: ", i + 1);
            print_list(list, n);
            printf("\n");
        }
    }
}

// 삽입 정렬 함수 - 비교 횟수 추적을 위해 count 포인터 사용
void insertion_sort(int list[], int n, int* count)
{
    int i = 0, j, key;
    *count = 0; // 비교 횟수를 추적하기 위해 매번 초기화
    for (i = 1; i < n; i++)
    {
        key = list[i];
        for (j = i - 1; j >= 0; j--)
        {
            (*count)++; // 비교 횟수 증가
            if (list[j] > key) list[j + 1] = list[j];
            else break;
        }
        list[j + 1] = key;
    }
}

// 버블 정렬 함수 - 이동 횟수 추적을 위해 move_count 포인터 사용
void bubble_sort(int list[], int n, int* move_count)
{
    int i, j, temp;
    int flag;
    *move_count = 0; // 이동 횟수를 추적하기 위해 매번 초기화

    for (i = n - 1; i > 0; i--)
    {
        flag = 0;
        for (j = 0; j < i; j++)
        {
            if (list[j] > list[j + 1])
            {
                SWAP(list[j], list[j + 1], temp);
                *move_count += 3; // 각 swap마다 값의 이동을 3회로 생각
                flag = 1;
            }
        }
        if (flag == 0) break; // 더 이상 교환이 없으면 정렬 종료
    }
}

// 랜덤 데이터를 생성하는 함수 - 0부터 999까지의 값을 리스트에 채움
void generateRandomData(int list[], int n)
{
    for (int i = 0; i < n; i++)
    {
        list[i] = rand() % 1000; // 0부터 999 사이의 랜덤 값 생성
    }
}

// 선택 정렬 수행 및 결과 출력 함수
void doSelectionSort(int list[], int n)
{
    int copiedList[SIZE];
    for (int i = 0; i < n; i++)
    {
        copiedList[i] = list[i]; // 원본 리스트를 복사하여 사용
    }
    printf("\nSelection Sort:\n");
    selection_sort(copiedList, n); // 선택 정렬 수행
}

// 삽입 정렬 20회 반복 후 평균 비교 횟수와 단일 삽입 정렬 결과 출력 함수
void doInsertionSort(int list[], int n)
{
    int copiedList[SIZE];
    int count, total_count = 0;

    // 삽입 정렬 20회 반복 및 평균 비교 횟수 계산 (중간 결과 출력 생략)
    for (int i = 0; i < 20; i++)
    {
        generateRandomData(copiedList, n); // 새로운 랜덤 데이터를 생성하여 삽입 정렬 수행
        insertion_sort(copiedList, n, &count);
        total_count += count; // 각 회차의 비교 횟수를 누적
    }
    printf("Insertion Sort Compare Average: %d\n", total_count / 20); // 평균 비교 횟수 출력

    // 단일 삽입 정렬 수행 및 결과 출력
    for (int i = 0; i < n; i++)
    {
        copiedList[i] = list[i]; // 원본 리스트를 복사하여 사용
    }
    insertion_sort(copiedList, n, &count); // 단일 삽입 정렬 수행
    printf("Insertion Sort Result:\n");
    print_list(copiedList, n); // 정렬된 리스트 출력

    printf("\n");
}

// 버블 정렬 20회 반복 후 평균 이동 횟수와 단일 버블 정렬 결과 출력 함수
void doBubbleSort(int list[], int n)
{
    int copiedList[SIZE];
    int move_count, total_move_count = 0;

    // 버블 정렬 20회 반복 및 평균 이동 횟수 계산 (중간 결과 출력 생략)
    for (int i = 0; i < 20; i++)
    {
        generateRandomData(copiedList, n); // 새로운 랜덤 데이터를 생성하여 버블 정렬 수행
        bubble_sort(copiedList, n, &move_count);
        total_move_count += move_count; // 각 회차의 이동 횟수를 누적
    }
    printf("Bubble Sort Move Average: %d\n", total_move_count / 20); // 평균 이동 횟수 출력

    // 단일 버블 정렬 수행 및 결과 출력
    for (int i = 0; i < n; i++)
    {
        copiedList[i] = list[i]; // 원본 리스트를 복사하여 사용
    }
    bubble_sort(copiedList, n, &move_count); // 단일 버블 정렬 수행
    printf("Bubble Sort Result:\n");
    print_list(copiedList, n); // 정렬된 리스트 출력
}

// 메인 함수 - 난수 생성 시드 초기화 및 정렬 함수 호출
int main()
{
    srand(time(NULL)); // 난수 생성 시드 초기화 (현재 시간을 기준으로 설정)
    int randomData[SIZE];
    generateRandomData(randomData, SIZE); // 랜덤 데이터 생성

    doSelectionSort(randomData, SIZE); // 선택 정렬 수행
    doInsertionSort(randomData, SIZE); // 삽입 정렬 수행
    doBubbleSort(randomData, SIZE); // 버블 정렬 수행

    return 0;
}
