#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>

// AVL 트리의 노드 구조체 정의
typedef struct Node {
    int key; // 노드의 값
    struct Node* left, * right; // 왼쪽 및 오른쪽 자식 포인터
    int height; // 현재 노드의 높이
} Node;

int compareCount = 0; // 탐색에서 발생한 비교 횟수
int searchCount = 0;  // 탐색 횟수

// 새로운 AVL 트리 노드를 생성하는 함수
Node* createNode(int key) {
    Node* nptr = (Node*)malloc(sizeof(Node));

    if (nptr == NULL) { // 메모리 할당 실패 시 처리
        printf("Memory allocation failed.\n");
        return NULL; // 메모리 할당 실패 시 NULL 반환
    }
    nptr->key = key; // 노드에 값 저장
    nptr->right = nptr->left = NULL; // 자식 노드는 NULL로 초기화
    nptr->height = 1; // 새 노드의 높이는 1
    return nptr;
}

// 특정 노드의 높이를 반환하는 함수
int getHeight(Node* nptr) {
    if (nptr == NULL) return 0; // NULL 노드의 높이는 0
    else return nptr->height; // 노드의 높이 반환
}

// 특정 노드의 균형 인수(왼쪽 높이 - 오른쪽 높이)를 계산
int getBalance(Node* nptr) {
    return getHeight(nptr->left) - getHeight(nptr->right); // 균형 계산
}

// 오른쪽 회전(Right Rotation)을 수행하여 트리 균형을 맞춤
Node* rotateRight(Node* y) {
    Node* x = y->left; // 새로운 루트가 될 노드
    Node* T3 = x->right; // 이동될 서브트리

    x->right = y; // y를 x의 오른쪽으로 이동
    y->left = T3; // T3를 y의 왼쪽으로 이동

    // 높이를 재계산
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    return x; // 새로운 루트 반환
}

// 왼쪽 회전(Left Rotation)을 수행하여 트리 균형을 맞춤
Node* rotateLeft(Node* y) {
    Node* x = y->right; // 새로운 루트가 될 노드
    Node* T2 = x->left; // 이동될 서브트리

    x->left = y; // y를 x의 왼쪽으로 이동
    y->right = T2; // T2를 y의 오른쪽으로 이동

    // 높이를 재계산
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    return x; // 새로운 루트 반환
}

// AVL 트리에 노드를 삽입하는 함수
Node* insertNode(Node* root, int key) {
    if (root == NULL) return createNode(key); // 트리가 비어있으면 새 노드 생성

    // 삽입 위치를 찾기 위해 재귀적으로 탐색
    if (key < root->key)
        root->left = insertNode(root->left, key); // 왼쪽 서브트리에 삽입
    else if (key > root->key)
        root->right = insertNode(root->right, key); // 오른쪽 서브트리에 삽입
    else
        return root; // 중복된 키는 삽입하지 않음

    // 높이 갱신
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

    // 균형 인수를 계산하여 균형을 맞춤
    int balance = getBalance(root);

    // LL (왼쪽-왼쪽) 케이스
    if (balance > 1 && key < root->left->key)
        return rotateRight(root);

    // LR (왼쪽-오른쪽) 케이스
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left); // 왼쪽 회전
        return rotateRight(root); // 오른쪽 회전
    }

    // RR (오른쪽-오른쪽) 케이스
    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    // RL (오른쪽-왼쪽) 케이스
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right); // 오른쪽 회전
        return rotateLeft(root); // 왼쪽 회전
    }

    return root; // 균형이 맞춰진 루트 반환
}

// 최소값을 가진 노드를 반환하는 함수
Node* getMinValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL) // 가장 왼쪽 노드로 이동
        current = current->left;
    return current;
}

// AVL 트리에서 노드를 삭제하는 함수
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root; // 트리가 비어있으면 NULL 반환

    // 삭제할 노드를 탐색
    if (key < root->key)
        root->left = deleteNode(root->left, key); // 왼쪽 서브트리 탐색
    else if (key > root->key)
        root->right = deleteNode(root->right, key); // 오른쪽 서브트리 탐색
    else {
        // 삭제할 노드를 찾았을 경우
        if (root->left == NULL) { // 왼쪽 자식이 없는 경우
            Node* temp = root->right;
            free(root); // 현재 노드 삭제
            return temp;
        }
        else if (root->right == NULL) { // 오른쪽 자식이 없는 경우
            Node* temp = root->left;
            free(root); // 현재 노드 삭제
            return temp;
        }

        // 왼쪽과 오른쪽 자식이 모두 있는 경우
        Node* temp = getMinValueNode(root->right); // 오른쪽 서브트리의 최소값을 가져옴
        root->key = temp->key; // 최소값을 현재 노드로 복사
        root->right = deleteNode(root->right, temp->key); // 복사된 노드를 삭제
    }

    if (root == NULL) return root; // 루트가 NULL일 경우 반환

    // 높이 갱신
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

    // 균형 인수를 계산하여 균형을 맞춤
    int balance = getBalance(root);

    // LL 케이스
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    // LR 케이스
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RR 케이스
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    // RL 케이스
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root; // 균형이 맞춰진 루트 반환
}

// AVL 트리 전체를 메모리에서 해제하는 함수
void freeTree(Node* root) {
    if (root == NULL) return; // 트리가 비어있으면 종료
    freeTree(root->left); // 왼쪽 서브트리 해제
    freeTree(root->right); // 오른쪽 서브트리 해제
    free(root); // 현재 노드 해제
}

// AVL 트리에서 특정 키를 탐색하는 함수
Node* searchNode(Node* root, int key) {
    if (root == NULL) return NULL; // 노드가 NULL이면 탐색 실패

    compareCount++;  // 탐색 시 비교 횟수 증가
    if (key == root->key) return root; // 키가 일치하면 노드 반환
    else if (key < root->key) return searchNode(root->left, key); // 왼쪽 서브트리로 이동
    else return searchNode(root->right, key); // 오른쪽 서브트리로 이동
}

// AVL 트리에서 랜덤한 작업(삽입, 삭제, 탐색)을 수행하는 함수
void doAVLBatch(Node* root) {
    compareCount = 0; // 비교 횟수 초기화
    searchCount = 0;  // 탐색 횟수 초기화

    for (int i = 0; i < 2000; i++) { // 2,000번 반복
        int A = rand() % 3;   // 작업 선택 (0: 삽입, 1: 삭제, 2: 탐색)
        int B = rand() % 1000; // 랜덤 키 생성 (0~999)

        if (A == 0) {
            root = insertNode(root, B);  // 삽입
        }
        else if (A == 1) {
            root = deleteNode(root, B);  // 삭제
        }
        else if (A == 2) {
            Node* result = searchNode(root, B);  // 탐색
            if (result != NULL) {
                searchCount++;  // 탐색 성공 시 횟수 증가
            }
        }
    }
}

// 이진 탐색 트리(BST) 관련 구조체 정의 및 함수들
typedef struct TreeNode {
    int key; // 노드 값
    struct TreeNode* left, * right; // 왼쪽 및 오른쪽 자식 포인터
} TreeNode;

// BST에 노드를 삽입하는 함수
TreeNode* insertBinaryNode(TreeNode* root, int key) {
    if (root == NULL) { // 트리가 비어있으면 새 노드 생성
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));

        if (newNode == NULL) { // 메모리 할당 실패 시 처리
            printf("Memory allocation failed.\n");
            return NULL;  // 메모리 할당 실패 시 NULL 반환
        }
        newNode->key = key; // 노드 값 저장
        newNode->left = newNode->right = NULL; // 자식 노드는 NULL로 초기화
        return newNode;
    }

    // 삽입 위치 탐색
    if (key < root->key)
        root->left = insertBinaryNode(root->left, key); // 왼쪽 서브트리에 삽입
    else if (key > root->key)
        root->right = insertBinaryNode(root->right, key); // 오른쪽 서브트리에 삽입

    return root; // 삽입 후 루트 반환
}

// BST에서 노드를 삭제하는 함수
TreeNode* deleteBinaryNode(TreeNode* root, int key) {
    if (root == NULL) return root; // 트리가 비어있으면 NULL 반환

    // 삭제할 노드를 탐색
    if (key < root->key)
        root->left = deleteBinaryNode(root->left, key); // 왼쪽 서브트리로 이동
    else if (key > root->key)
        root->right = deleteBinaryNode(root->right, key); // 오른쪽 서브트리로 이동
    else {
        // 삭제할 노드를 찾은 경우
        if (root->left == NULL) { // 왼쪽 자식이 없는 경우
            TreeNode* temp = root->right;
            free(root); // 현재 노드 삭제
            return temp;
        }
        else if (root->right == NULL) { // 오른쪽 자식이 없는 경우
            TreeNode* temp = root->left;
            free(root); // 현재 노드 삭제
            return temp;
        }

        // 왼쪽과 오른쪽 자식이 모두 있는 경우
        TreeNode* temp = root->right; // 오른쪽 서브트리에서 가장 작은 값 찾기
        while (temp && temp->left != NULL)
            temp = temp->left;

        root->key = temp->key; // 최소값을 현재 노드에 복사
        root->right = deleteBinaryNode(root->right, temp->key); // 복사된 노드를 삭제
    }

    return root; // 삭제 후 루트 반환
}

// BST에서 특정 키를 탐색하는 함수
TreeNode* searchBinaryNode(TreeNode* root, int key) {
    if (root == NULL) return NULL; // 노드가 NULL이면 탐색 실패

    compareCount++;  // 탐색 시 비교 횟수 증가
    if (key == root->key) return root; // 키가 일치하면 노드 반환
    else if (key < root->key) return searchBinaryNode(root->left, key); // 왼쪽 서브트리로 이동
    else return searchBinaryNode(root->right, key); // 오른쪽 서브트리로 이동
}

// BST에서 랜덤한 작업(삽입, 삭제, 탐색)을 수행하는 함수
void doBinaryBatch(TreeNode* root) {
    compareCount = 0; // 비교 횟수 초기화
    searchCount = 0;  // 탐색 횟수 초기화

    for (int i = 0; i < 2000; i++) { // 2,000번 반복
        int A = rand() % 3;   // 작업 선택 (0: 삽입, 1: 삭제, 2: 탐색)
        int B = rand() % 1000; // 랜덤 키 생성 (0~999)

        if (A == 0) {
            root = insertBinaryNode(root, B);  // 삽입
        }
        else if (A == 1) {
            root = deleteBinaryNode(root, B);  // 삭제
        }
        else if (A == 2) {
            TreeNode* result = searchBinaryNode(root, B);  // 탐색
            if (result != NULL) {
                searchCount++;  // 탐색 성공 시 횟수 증가
            }
        }
    }
}

// 메인 함수: AVL 트리와 BST의 성능 비교
int main(int argc, char* argv[]) {
    Node* root = NULL; // AVL 트리 루트 초기화
    srand(time(NULL)); // 난수 생성기 초기화

    for (int i = 1; i <= 3; i++) { // 성능 비교를 3번 반복
        Sleep(1000); // 1초 대기

        float allCount = 0.0; // 평균 비교 횟수를 저장하는 변수

        // AVL 트리 성능 테스트
        doAVLBatch(root); // AVL 트리에서 2,000번의 랜덤 작업 수행
        allCount = (float)compareCount / searchCount; // 평균 비교 횟수 계산
        printf("\naverage AVL compare count: %.2f\n", allCount);

        freeTree(root); // AVL 트리 메모리 해제
        root = NULL; // 루트 초기화
        compareCount = allCount = 0; // 변수 초기화

        // BST 성능 테스트
        doBinaryBatch(root); // BST에서 2,000번의 랜덤 작업 수행
        allCount = (float)compareCount / searchCount; // 평균 비교 횟수 계산
        printf("average Bin compare count: %.2f\n", allCount);
        freeTree(root); // BST 메모리 해제
    }

    return 0; // 프로그램 종료
}
