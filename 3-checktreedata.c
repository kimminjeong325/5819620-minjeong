#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* node;
    int depth; 
} StackItem;

typedef struct {
    StackItem data[STACK_SIZE];
    int top;
} StackType;

void Init(StackType* s) {
    s->top = -1;
}

int IsEmpty(StackType* s) {
    return (s->top == -1);
}

int IsFull(StackType* s) {
    return (s->top >= STACK_SIZE - 1);
}

void Push(StackType* s, TreeNode* p, int depth) {
    if (IsFull(s)) {
        printf("The stack is full\n");
        exit(1);
    }
    else {
        s->data[++(s->top)].node = p;
        s->data[s->top].depth = depth; 
    }
}

StackItem Pop(StackType* s) {
    if (IsEmpty(s)) {
        printf("The stack is empty\n");
        exit(1);
    }
    else {
        return s->data[(s->top)--];
    }
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
        node->left = newNode;
    }
    else if (direction == 1) {
        node->right = newNode;
    }
}

void GenerateLinkTree(TreeNode* root) {
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

void GetSumOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    StackType stack;
    Init(&stack);
    Push(&stack, root, 1);

    int sum = 0;
    while (!IsEmpty(&stack)) {
        StackItem item = Pop(&stack);
        TreeNode* node = item.node;
        sum += node->data;

        if (node->right) Push(&stack, node->right, item.depth + 1);
        if (node->left) Push(&stack, node->left, item.depth + 1);
    }
    printf("Sum of nodes: %d\n", sum);


}

void GetNumberOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    StackType stack;
    Init(&stack);
    Push(&stack, root, 1);

    int count = 0;
    while (!IsEmpty(&stack)) {
        StackItem item = Pop(&stack);
        TreeNode* node = item.node;
        count++;

        if (node->right) Push(&stack, node->right, item.depth + 1);
        if (node->left) Push(&stack, node->left, item.depth + 1);
    }
    printf("Number of nodes: %d\n", count);

}

void GetHeightOfTree(TreeNode* root) {
    if (root == NULL) return 0;

    StackType stack;
    Init(&stack);
    Push(&stack, root, 1); 

    int height = 0;

    while (!IsEmpty(&stack)) {
        StackItem item = Pop(&stack);
        TreeNode* node = item.node;
        int currentDepth = item.depth;

        
        if (currentDepth > height) {
            height = currentDepth;
        }

     
        if (node->right) {
            Push(&stack, node->right, currentDepth + 1);
        }
        if (node->left) {
            Push(&stack, node->left, currentDepth + 1);
        }
    }

    printf("Height of Tree: %d\n", height);
}

void GetNumberOfLeafNodes(TreeNode* root) {
    if (root == NULL) return 0;

    StackType stack;
    Init(&stack);
    Push(&stack, root, 1);

    int leafCount = 0;
    while (!IsEmpty(&stack)) {
        StackItem item = Pop(&stack);
        TreeNode* node = item.node;

        if (!node->left && !node->right) {
            leafCount++;
        }
        if (node->right) Push(&stack, node->right, item.depth + 1);
        if (node->left) Push(&stack, node->left, item.depth + 1);
    }


    printf("Number of leaf nodes: %d\n", leafCount);

}


int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateLinkTree(root);
    GetSumOfNodes(root);
    GetNumberOfNodes(root);
    GetHeightOfTree(root);
    GetNumberOfLeafNodes(root);

    return 0;
}