#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 배열 기반 트리 생성
void GenerateArrayTree(int* tree) {
    int list[15] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };
    for (int i = 0; i < 15; i++) {
        tree[i] = list[i];
    }
    for (int i = 0; i < 15; i++) { // 전체 배열 출력
        printf("%d ", tree[i]);
    }
    printf("\n");
}

// 배열 기반 트리 전위 순회
void ArrayPreOrder(int* tree, int index) {
    if (index >= 15)return;
    printf("%d ", tree[index]);
    ArrayPreOrder(tree, 2 * index + 1); // 왼쪽 자식
    ArrayPreOrder(tree, 2 * index + 2); // 오른쪽 자식
}

// 배열 기반 트리 중위 순회
void ArrayInOrder(int* tree, int index) {
    if (index >= 15)
        return;

    ArrayInOrder(tree, 2 * index + 1); // 왼쪽 자식
    printf("%d ", tree[index]);
    ArrayInOrder(tree, 2 * index + 2); // 오른쪽 자식
}

// 배열 기반 트리 후위 순회
void ArrayPostOrder(int* tree, int index) {
    if (index >= 15)
        return;

    ArrayPostOrder(tree, 2 * index + 1); // 왼쪽 자식
    ArrayPostOrder(tree, 2 * index + 2); // 오른쪽 자식
    printf("%d ", tree[index]);
}

// 배열 기반 트리 순회 출력
void ArrayOrders(int* tree) {
    
    ArrayPreOrder(tree, 0); // 인덱스 0부터 시작 (루트는 인덱스 0)
    printf("\n");

   
    ArrayInOrder(tree, 0);  // 인덱스 0부터 시작 (루트는 인덱스 0)
    printf("\n");

  
    ArrayPostOrder(tree, 0); // 인덱스 0부터 시작 (루트는 인덱스 0)
    printf("\n");
}

void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode; // 왼쪽 자식
    }
    else if (direction == 1) {
        node->right = newNode; // 오른쪽 자식
    }
}

// 연결 리스트 기반 트리 생성 (중첩 함수 포함)
void GenerateLinkTree(TreeNode* root) {

    // 트리 구조 설정
    PlaceNode(root, 0, 2);     
    PlaceNode(root, 1, 9);    

    PlaceNode(root->left, 0, 3); 
    PlaceNode(root->left, 1, 5); 

    PlaceNode(root->left->left, 0, 4); 
    PlaceNode(root->left->left, 1, 6);

    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);

    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);

    PlaceNode(root->right->left, 0, 11); 
    PlaceNode(root->right->left, 1, 12);


    PlaceNode(root->right->right, 0, 14); 
    PlaceNode(root->right->right, 1, 15);
    
   
}


// 연결 리스트 기반 트리 전위 순회
void LinkPreOrder(TreeNode* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    LinkPreOrder(root->left);
    LinkPreOrder(root->right);
}

// 연결 리스트 기반 트리 중위 순회
void LinkInOrder(TreeNode* root) {
    if (root == NULL)
        return;
    LinkInOrder(root->left);
    printf("%d ", root->data);
    LinkInOrder(root->right);
}

// 연결 리스트 기반 트리 후위 순회
void LinkPostOrder(TreeNode* root) {
    if (root == NULL)
        return;
    LinkPostOrder(root->left);
    LinkPostOrder(root->right);
    printf("%d ", root->data);
}

// 연결 리스트 기반 트리 순회 출력
void LinkOrders(TreeNode* root) {
    
    LinkPreOrder(root);
    printf("\n");

   
    LinkInOrder(root);
    printf("\n");

    
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    int arr[15];
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateArrayTree(arr);
    GenerateLinkTree(root);
    printf("\n");
    ArrayOrders(arr);
    printf("\n");
    LinkOrders(root);
   

    return 0;
}