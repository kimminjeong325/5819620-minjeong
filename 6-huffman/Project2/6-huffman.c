#include<stdio.h>
#include<stdlib.h>
#define MAX_ELEMENT 200 // 최대 힙 크기 정의

// 노드 구조체 정의
typedef struct Node {
    int weight;        // 노드의 가중치 (문자의 빈도수)
    char ch;          // 문자
    struct Node* left;  // 왼쪽 자식 노드 포인터
    struct Node* right; // 오른쪽 자식 노드 포인터
} Node;

// 힙의 요소를 정의하는 구조체
typedef struct {
    Node* ptree;  // 힙에 저장된 노드 포인터
    char ch;      // 문자
    int key;      // 가중치 (빈도수)
} element;

// 힙 구조체 정의
typedef struct {
    element heap[MAX_ELEMENT]; // 힙 배열 (최소 힙 구조)
    int heap_size;             // 현재 힙 크기
} HeapType;

// 힙을 생성하는 함수
HeapType* create() {
    // HeapType 구조체를 동적 메모리 할당하여 초기화
    return (HeapType*)malloc(sizeof(HeapType));
}

// 힙을 초기화하는 함수
void init(HeapType* h) {
    h->heap_size = 0; // 힙 크기를 0으로 초기화
}

// 최소 힙에 요소를 삽입하기 위한 함수
void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size); // 힙 크기를 증가시키고, 새로운 요소의 인덱스를 설정

    // 부모 노드와 비교하여 위치를 찾는 과정
    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2]; // 부모 노드의 값을 현재 위치로 이동
        i /= 2; // 부모 노드 인덱스로 이동
    }
    h->heap[i] = item; // 새로운 요소 삽입
}

// 최소 힙에서 최소 요소를 삭제하기 위한 함수
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1]; // 루트 노드(최소 값) 저장
    temp = h->heap[(h->heap_size)--]; // 마지막 노드를 루트로 이동하고 힙 크기 감소
    parent = 1; // 부모 인덱스 초기화
    child = 2; // 왼쪽 자식 인덱스 초기화

    // 자식 노드와 비교하여 힙 구조를 유지
    while (child <= h->heap_size) {
        // 오른쪽 자식이 존재하고, 오른쪽 자식의 키가 왼쪽 자식보다 작으면 오른쪽 자식 선택
        if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
            child++;

        // 현재 노드의 키가 자식 노드의 키보다 작으면 종료
        if (temp.key < h->heap[child].key) break;

        h->heap[parent] = h->heap[child]; // 자식 노드를 부모 노드 위치로 이동
        parent = child; // 부모 인덱스 업데이트
        child *= 2; // 자식 인덱스로 이동
    }
    h->heap[parent] = temp; // 남은 값을 최종 위치에 배치
    return item; // 삭제된 요소 반환
}

// 새로운 노드를 생성하는 함수
Node* createNode(char ch, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // 메모리 할당
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 실패\n"); // 메모리 할당 실패 시 에러 메시지 출력
        exit(1);
    }
    newNode->ch = ch; // 문자 설정
    newNode->weight = weight; // 가중치 설정
    newNode->left = newNode->right = NULL; // 자식 노드는 NULL로 초기화
    return newNode; // 생성된 노드 반환
}

// 허프만 트리를 생성하는 함수
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    HeapType* h = create(); // 힙 생성
    init(h); // 힙 초기화

    // 각 문자에 대한 노드를 생성하고 힙에 삽입
    for (int i = 0; i < size; i++) {
        element item;
        item.ptree = createNode(characters[i], frequencies[i]); // 새로운 노드 생성
        item.key = frequencies[i]; // 노드의 가중치 설정
        insert_min_heap(h, item); // 힙에 노드 삽입

        // 현재 힙 상태 출력
        for (int j = 1; j <= h->heap_size; j++) {
            printf("%d ", h->heap[j].key); // 힙의 각 요소 출력
        }
        printf("\n");
    }

    // 허프만 트리 생성 과정
    while (h->heap_size > 1) {
        element left = delete_min_heap(h); // 최소 요소 삭제 (가장 작은 두 노드를 병합하기 위함)
        element right = delete_min_heap(h); // 다음 최소 요소 삭제
        Node* mergedNode = createNode('\0', left.ptree->weight + right.ptree->weight); // 병합된 노드 생성
        mergedNode->left = left.ptree; // 왼쪽 자식으로 설정
        mergedNode->right = right.ptree; // 오른쪽 자식으로 설정

        element newElement; // 새로운 힙 요소 정의
        newElement.ptree = mergedNode; // 병합된 노드를 저장
        newElement.key = mergedNode->weight; // 병합된 노드의 가중치 저장

        insert_min_heap(h, newElement); // 새로운 요소를 힙에 삽입

        // 병합 과정 출력
        printf("//%d + %d -> %d\n", left.ptree->weight, right.ptree->weight, mergedNode->weight);
        for (int j = 1; j <= h->heap_size; j++) {
            printf("%d ", h->heap[j].key); // 현재 힙 상태 출력
        }
        printf("\n");
    }

    return delete_min_heap(h).ptree; // 최종 허프만 트리 반환
}

// 허프만 코드를 출력하는 재귀 함수
void printCodes(Node* root, int arr[], int top) {
    // 왼쪽 서브트리로 이동
    if (root->left) {
        arr[top] = 1; // 왼쪽 이동을 나타내는 코드 추가
        printCodes(root->left, arr, top + 1); // 재귀 호출
    }

    // 오른쪽 서브트리로 이동
    if (root->right) {
        arr[top] = 0; // 오른쪽 이동을 나타내는 코드 추가
        printCodes(root->right, arr, top + 1); // 재귀 호출
    }

    // 리프 노드에 도달했을 경우 코드 출력
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->ch); // 문자를 출력
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]); // 해당 문자의 허프만 코드 출력
        printf("\n");
    }
}

// 허프만 코드를 생성하고 출력하는 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size); // 허프만 트리 생성
    int* arr = (int*)malloc(size * sizeof(int)); // 허프만 코드 저장을 위한 배열 동적 메모리 할당
    if (arr == NULL) {
        fprintf(stderr, "메모리 할당 실패\n"); // 메모리 할당 실패 시 에러 메시지 출력
        exit(1);
    }

    int top = 0; // 현재 깊이 또는 인덱스 초기화
    printCodes(root, arr, top); // 허프만 코드 출력

    free(arr); // 동적 메모리 해제
}

// 메인 함수
int main() {
    // 허프만 코드를 생성할 문자 배열 및 각 문자의 빈도수 배열
    char characters[] = { 'a','e','i','o','u','s','t' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 }; // 각 문자의 빈도수 배열
    int size = sizeof(characters) / sizeof(characters[0]); // 문자의 개수 계산

    GenerateHuffmanCodes(characters, frequencies, size); // 허프만 코드 생성 및 출력

    return 0; // 프로그램 종료
}
