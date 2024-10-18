#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//두 변수의 값을 교환하기 위한 함수
// 힙 구조를 유지하거나 정렬 시 노드 간의 값을 교환하는 데 사용하기 위해 구현
void swap(int* a, int* b) {
    int temp = *a;//첫번째 변수의 값을 temp에 저장 
    *a = *b;//두번째 변수의 값을 첫번째 변수에 대입
    *b = temp;//임시 변수에 저장한 첫 번째 변수의 값을 두 번째 변수에 대입
}

// 특정 노드를 기준으로 최대 힙의 속성을 유지하기 위한 재정렬 함수
//배열에서 특정 노드가 힙 구조를 만족하지 않을 때, 자식 노드들과 비교하여 교환한 후
// 재귀적으로 힙 구조를 복구하기 위해 구현

void resortHeap(int arr[], int n, int i) {
    int largest = i;// 현재 노드를 가장 큰 값이라고 가정
    int left = 2 * i + 1;// 왼쪽 자식 노드 인덱스
    int right = 2 * i + 2;// 오른쪽 자식 노드 인덱스
    // 왼쪽 자식이 현재 노드보다 크면, 왼쪽 자식을 가장 큰 노드로 설정
    if (left < n && arr[left] > arr[largest])
        largest = left;
    // 오른쪽 자식이 현재 가장 큰 노드보다 크면, 오른쪽 자식을 가장 큰 노드로 설정
    if (right < n && arr[right] > arr[largest])
        largest = right;
    // 만약 가장 큰 노드가 변경되었다면, 교환 후 재귀적으로 하위 노드를 정렬
    if (largest != i) {
        swap(&arr[i], &arr[largest]);// 부모와 자식 노드 교환
        resortHeap(arr, n, largest);// 재귀적으로 힙을 재정렬
    }
}

//주어진 배열을 최대 힙으로  만들기 위한 함수 
void BuildMaxHeap(int inputData[], int n) {
    // 배열의 모든 요소를 순회하며 힙을 구성
    for (int i = 0; i < n; i++) { 
        int j = i;
        // 현재 노드가 부모 노드보다 크면, 부모와 자식을 교환하여 힙 구조를 유지
        while (j > 0 && inputData[(j - 1) / 2] < inputData[j]) {
            swap(&inputData[(j - 1) / 2], &inputData[j]);// 부모와 자식 교환
            j = (j - 1) / 2; // 부모 노드로 이동하여 다시 비교
        }

        // 각 단계에서의 배열 상태를 출력
        for (int k = 0; k <= i; k++) {
            printf("%d ", inputData[k]);
        }
        printf("\n");
    }
}
//최대 힙을 구성한 후, 힙 정렬을 수행하는 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    // 우선 최대 힙을 구성
    BuildMaxHeap(inputData, n);
    // 힙 정렬을 수행
    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]);// 루트와 마지막 요소 교환
        resortHeap(inputData, i, 0);// 남은 배열을 최대 힙으로 재정렬

        // 현재 정렬된 상태를 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]); 
        }
        printf("\n");
    }
}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };//정렬할 데이터 배열 
    int size = sizeof(inputData) / sizeof(inputData[0]);//배열 크기 계산 

    printf("<Sort>\n");
    // 힙 정렬 함수 호출
    BuildMaxHeapAndSort(inputData, size);
    // 최종적으로 정렬된 배열을 출력
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");
    return 0;
}
