#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#pragma warning(disable:4996)
#include <stdlib.h>
#define MAX_SIZE 100
#define true 1
#include <string.h>

// 힙의 요소를 나타내는 구조체, key 값만을 저장함
typedef struct {
    int key;
} element;

// 힙 구조체, heap 배열과 현재 heap_size를 관리
typedef struct {
    element heap[MAX_SIZE];
    int heap_size;
} TreeNode;

// 힙 생성 함수, 힙을 동적으로 생성하고 초기화함
TreeNode* create_heap() {
    TreeNode* h = (TreeNode*)malloc(sizeof(TreeNode));
    if (h == NULL) {
        fprintf(stderr, "메모리 할당에 실패했습니다.\n");
        exit(EXIT_FAILURE);
    }
    h->heap_size = 0; // 힙 크기를 0으로 초기화
    return h;
}

// 힙을 초기화하는 함수, heap_size만 0으로 설정
void init_heap(TreeNode* h) {
    h->heap_size = 0;
}

// 힙 소멸 함수, 동적으로 할당된 메모리를 해제함
void destroy_heap(TreeNode* h) {
    free(h);
}

// 힙이 비어있는지 확인하는 함수, heap_size가 0이면 true를 반환
int is_empty_heap(TreeNode* h) {
    return (h->heap_size == 0);
}

// 힙이 가득 찼는지 확인하는 함수, heap_size가 MAX_SIZE-1이면 true를 반환
int is_full_heap(TreeNode* h) {
    return (h->heap_size == (MAX_SIZE)-1);
}

// 힙의 모든 요소를 리스트 형식으로 출력하는 함수
void printHeapList(TreeNode* h) {
    if (is_empty_heap(h)) {  // 힙이 비어있다면 경고 메시지 출력
        printf("힙이 비어 있습니다.\n");
        return;
    }

    for (int i = 1; i <= h->heap_size; i++) {  // heap 배열의 요소를 모두 출력
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

// 힙을 레벨별로 출력하는 함수, 각 레벨별로 요소를 출력
void printHeapLevel(TreeNode* h) {
    if (is_empty_heap(h)) {  // 힙이 비어있다면 경고 메시지 출력
        printf("힙이 비어 있습니다.\n");
        return;
    }

    int level = 1;               // 현재 레벨을 1로 시작
    int elements_in_level = 1;   // 현재 레벨에서 출력할 요소의 개수
    int count = 1;               // 첫 번째 힙 요소부터 시작

    printf("트리 레벨별 출력 :\n");
    while (count <= h->heap_size) {  // count가 heap_size보다 작거나 같을 때까지 반복
        printf("[%d] ", level);       // 현재 레벨 인덱스 출력
        for (int i = 0; i < elements_in_level && count <= h->heap_size; i++) {
            printf("%d ", h->heap[count].key);  // heap[count]로 직접 접근
            count++;
        }
        printf("\n");  // 각 레벨 출력 후 줄 바꿈
        level++;
        elements_in_level *= 2;  // 다음 레벨에서 출력할 요소의 개수를 두 배로 늘림
    }
}

// 초기 힙 빌딩 시 사용하는 함수, 추가 과정에서 출력 없이 동작
void InsertMaxHeapSilent(TreeNode* h, int key) {
    if (is_full_heap(h)) {
        return;  // 힙이 가득 찬 경우 추가를 중단
    }

    element item;
    item.key = key;

    int i = ++(h->heap_size);  // 힙 크기를 증가시키며 삽입할 위치 설정

    // 힙ify up 과정, 부모 노드와 비교하여 위치를 찾아가는 과정
    while ((i > 1) && (h->heap[i / 2].key < item.key)) {
        h->heap[i] = h->heap[i / 2];  // 부모 노드를 아래로 이동
        i = i / 2;
    }
    h->heap[i] = item;  // 최종 위치에 삽입
}

// 사용자가 직접 노드를 삽입할 때 사용하는 함수, 과정이 출력됨
void InsertMaxHeapTree(TreeNode* h, int key) {
    if (is_full_heap(h)) {
        printf("힙이 가득 찼습니다. 더 이상 추가할 수 없습니다.\n\n");
        return;
    }

    element item;
    item.key = key;

    int i = ++(h->heap_size);  // 힙 크기 증가
    int move_count = 0; // 노드 이동 횟수를 카운트

    h->heap[i] = item; // 일단 마지막에 추가
    printHeapList(h); // 초기 추가 상태 출력

    // 힙ify up 과정, 부모와 비교하여 교환하며 힙 구조를 유지
    while ((i > 1) && (h->heap[i / 2].key < item.key)) {
        // 부모 노드와 교환
        element temp = h->heap[i / 2];
        h->heap[i / 2] = h->heap[i];
        h->heap[i] = temp;

        i = i / 2;
        printHeapList(h); // 힙 상태 출력
        move_count++;
    }
    printf("노드가 이동된 횟수:%d \n\n", move_count);  // 최종 이동 횟수 출력
}

// 초기 힙 빌딩 시 사용하는 함수, inputData 배열을 사용하여 힙을 생성
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = create_heap();

    for (int i = 0; i < size; i++) {
        InsertMaxHeapSilent(root, inputData[i]);  // 데이터 배열을 사용해 힙을 초기화
    }
    return root;
}

// 힙에서 최상위 노드를 삭제하는 함수, 삭제된 과정이 출력됨
element delete_heap(TreeNode* h) {
    if (is_empty_heap(h)) {
        printf("힙이 비어 있어 삭제할 수 없습니다.\n");
        element empty = { -1 };
        return empty;
    }

    element item, temp;
    int parent, child;
    int move_count = 0; // 이동 횟수 카운트

    item = h->heap[1]; // 최상위 노드 저장
    temp = h->heap[h->heap_size]; // 마지막 노드 저장

    (h->heap_size)--;  // 힙 크기를 감소시킴

    parent = 1;
    child = 2;

    printHeapList(h); // 현재 힙 상태 출력

    // 힙ify down 과정, 자식 노드와 비교하여 위치를 찾아가는 과정
    while (child <= h->heap_size) {
        // 자식 노드 중 더 큰 노드 선택
        if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
            child++;
        }

        if (temp.key >= h->heap[child].key) {
            break;
        }

        h->heap[parent] = h->heap[child];  // 부모 자리에 자식 노드 이동
        parent = child;
        child *= 2;
        move_count++;

        printHeapList(h); // 중간 과정 출력
    }

    h->heap[parent] = temp;  // 마지막에 temp 값을 부모 위치에 배치

    printf("노드가 이동된 횟수: %d\n", move_count);  // 최종 이동 횟수 출력
    return item;  // 삭제된 노드를 반환
}

// 힙에서 최상위 노드를 반환하는 함수, 단순 조회
element find_heap(TreeNode* h) {
    if (is_empty_heap(h)) {
        printf("힙이 비어 있습니다.\n");
        element empty = { -1 };
        return empty;
    }
    return h->heap[1];  // 최상위 노드를 반환
}

// 사용자 인터페이스 함수, 사용자가 입력한 명령에 따라 노드 추가, 삭제, 출력 등을 처리
void runUserInterface(TreeNode* root) {
    char menu;
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    printf("ㅣ      i    :노드 추가        ㅣ\n");
    printf("ㅣ      d    :노드 삭제        ㅣ\n");
    printf("ㅣ      p    :레벨별 출력      ㅣ\n");
    printf("ㅣ      c    :종료             ㅣ\n");
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n");

    while (true) {
        printf("메뉴 입력: ");
        scanf(" %c", &menu);  // 메뉴를 입력받음
        switch (menu) {
        case 'i': {  // 노드 추가
            int num;
            printf("추가할 값 입력: ");
            scanf("%d", &num);
            InsertMaxHeapTree(root, num);  // 입력된 값을 힙에 추가
            break;
        }
        case 'd': {  // 노드 삭제
            if (is_empty_heap(root)) {
                printf("힙이 비어 있어 삭제할 수 없습니다.\n\n");
            }
            else {
                element removed = delete_heap(root);  // 최상위 노드를 삭제
                printf("\n");
            }
            break;
        }
        case 'p': {  // 레벨별 출력
            printHeapLevel(root);  // 힙을 레벨별로 출력
            printf("\n");
            break;
        }
        case 'c': {  // 종료
            exit(1);  // 프로그램을 종료
        }
        default:
            printf("잘못된 입력입니다. 다시 시도해주세요.\n\n");  // 잘못된 입력 처리
            break;
        }
    }
}

// 메인 함수, 초기 힙 빌딩 후 사용자 인터페이스 실행
int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };  // 초기 데이터 배열
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // 초기 힙 빌딩 (출력 없이)
    TreeNode* root = generateMaxHeapTree(inputData, size);

    // 사용자 인터페이스 실행
    runUserInterface(root);

    // 힙 소멸
    destroy_heap(root);
    return 0;
}
