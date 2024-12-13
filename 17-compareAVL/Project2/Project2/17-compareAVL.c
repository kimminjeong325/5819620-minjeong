#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>

// AVL Ʈ���� ��� ����ü ����
typedef struct Node {
    int key; // ����� ��
    struct Node* left, * right; // ���� �� ������ �ڽ� ������
    int height; // ���� ����� ����
} Node;

int compareCount = 0; // Ž������ �߻��� �� Ƚ��
int searchCount = 0;  // Ž�� Ƚ��

// ���ο� AVL Ʈ�� ��带 �����ϴ� �Լ�
Node* createNode(int key) {
    Node* nptr = (Node*)malloc(sizeof(Node));

    if (nptr == NULL) { // �޸� �Ҵ� ���� �� ó��
        printf("Memory allocation failed.\n");
        return NULL; // �޸� �Ҵ� ���� �� NULL ��ȯ
    }
    nptr->key = key; // ��忡 �� ����
    nptr->right = nptr->left = NULL; // �ڽ� ���� NULL�� �ʱ�ȭ
    nptr->height = 1; // �� ����� ���̴� 1
    return nptr;
}

// Ư�� ����� ���̸� ��ȯ�ϴ� �Լ�
int getHeight(Node* nptr) {
    if (nptr == NULL) return 0; // NULL ����� ���̴� 0
    else return nptr->height; // ����� ���� ��ȯ
}

// Ư�� ����� ���� �μ�(���� ���� - ������ ����)�� ���
int getBalance(Node* nptr) {
    return getHeight(nptr->left) - getHeight(nptr->right); // ���� ���
}

// ������ ȸ��(Right Rotation)�� �����Ͽ� Ʈ�� ������ ����
Node* rotateRight(Node* y) {
    Node* x = y->left; // ���ο� ��Ʈ�� �� ���
    Node* T3 = x->right; // �̵��� ����Ʈ��

    x->right = y; // y�� x�� ���������� �̵�
    y->left = T3; // T3�� y�� �������� �̵�

    // ���̸� ����
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    return x; // ���ο� ��Ʈ ��ȯ
}

// ���� ȸ��(Left Rotation)�� �����Ͽ� Ʈ�� ������ ����
Node* rotateLeft(Node* y) {
    Node* x = y->right; // ���ο� ��Ʈ�� �� ���
    Node* T2 = x->left; // �̵��� ����Ʈ��

    x->left = y; // y�� x�� �������� �̵�
    y->right = T2; // T2�� y�� ���������� �̵�

    // ���̸� ����
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right)) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right)) ? getHeight(x->left) : getHeight(x->right));

    return x; // ���ο� ��Ʈ ��ȯ
}

// AVL Ʈ���� ��带 �����ϴ� �Լ�
Node* insertNode(Node* root, int key) {
    if (root == NULL) return createNode(key); // Ʈ���� ��������� �� ��� ����

    // ���� ��ġ�� ã�� ���� ��������� Ž��
    if (key < root->key)
        root->left = insertNode(root->left, key); // ���� ����Ʈ���� ����
    else if (key > root->key)
        root->right = insertNode(root->right, key); // ������ ����Ʈ���� ����
    else
        return root; // �ߺ��� Ű�� �������� ����

    // ���� ����
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

    // ���� �μ��� ����Ͽ� ������ ����
    int balance = getBalance(root);

    // LL (����-����) ���̽�
    if (balance > 1 && key < root->left->key)
        return rotateRight(root);

    // LR (����-������) ���̽�
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left); // ���� ȸ��
        return rotateRight(root); // ������ ȸ��
    }

    // RR (������-������) ���̽�
    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    // RL (������-����) ���̽�
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right); // ������ ȸ��
        return rotateLeft(root); // ���� ȸ��
    }

    return root; // ������ ������ ��Ʈ ��ȯ
}

// �ּҰ��� ���� ��带 ��ȯ�ϴ� �Լ�
Node* getMinValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL) // ���� ���� ���� �̵�
        current = current->left;
    return current;
}

// AVL Ʈ������ ��带 �����ϴ� �Լ�
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root; // Ʈ���� ��������� NULL ��ȯ

    // ������ ��带 Ž��
    if (key < root->key)
        root->left = deleteNode(root->left, key); // ���� ����Ʈ�� Ž��
    else if (key > root->key)
        root->right = deleteNode(root->right, key); // ������ ����Ʈ�� Ž��
    else {
        // ������ ��带 ã���� ���
        if (root->left == NULL) { // ���� �ڽ��� ���� ���
            Node* temp = root->right;
            free(root); // ���� ��� ����
            return temp;
        }
        else if (root->right == NULL) { // ������ �ڽ��� ���� ���
            Node* temp = root->left;
            free(root); // ���� ��� ����
            return temp;
        }

        // ���ʰ� ������ �ڽ��� ��� �ִ� ���
        Node* temp = getMinValueNode(root->right); // ������ ����Ʈ���� �ּҰ��� ������
        root->key = temp->key; // �ּҰ��� ���� ���� ����
        root->right = deleteNode(root->right, temp->key); // ����� ��带 ����
    }

    if (root == NULL) return root; // ��Ʈ�� NULL�� ��� ��ȯ

    // ���� ����
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right)) ? getHeight(root->left) : getHeight(root->right));

    // ���� �μ��� ����Ͽ� ������ ����
    int balance = getBalance(root);

    // LL ���̽�
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    // LR ���̽�
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RR ���̽�
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    // RL ���̽�
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root; // ������ ������ ��Ʈ ��ȯ
}

// AVL Ʈ�� ��ü�� �޸𸮿��� �����ϴ� �Լ�
void freeTree(Node* root) {
    if (root == NULL) return; // Ʈ���� ��������� ����
    freeTree(root->left); // ���� ����Ʈ�� ����
    freeTree(root->right); // ������ ����Ʈ�� ����
    free(root); // ���� ��� ����
}

// AVL Ʈ������ Ư�� Ű�� Ž���ϴ� �Լ�
Node* searchNode(Node* root, int key) {
    if (root == NULL) return NULL; // ��尡 NULL�̸� Ž�� ����

    compareCount++;  // Ž�� �� �� Ƚ�� ����
    if (key == root->key) return root; // Ű�� ��ġ�ϸ� ��� ��ȯ
    else if (key < root->key) return searchNode(root->left, key); // ���� ����Ʈ���� �̵�
    else return searchNode(root->right, key); // ������ ����Ʈ���� �̵�
}

// AVL Ʈ������ ������ �۾�(����, ����, Ž��)�� �����ϴ� �Լ�
void doAVLBatch(Node* root) {
    compareCount = 0; // �� Ƚ�� �ʱ�ȭ
    searchCount = 0;  // Ž�� Ƚ�� �ʱ�ȭ

    for (int i = 0; i < 2000; i++) { // 2,000�� �ݺ�
        int A = rand() % 3;   // �۾� ���� (0: ����, 1: ����, 2: Ž��)
        int B = rand() % 1000; // ���� Ű ���� (0~999)

        if (A == 0) {
            root = insertNode(root, B);  // ����
        }
        else if (A == 1) {
            root = deleteNode(root, B);  // ����
        }
        else if (A == 2) {
            Node* result = searchNode(root, B);  // Ž��
            if (result != NULL) {
                searchCount++;  // Ž�� ���� �� Ƚ�� ����
            }
        }
    }
}

// ���� Ž�� Ʈ��(BST) ���� ����ü ���� �� �Լ���
typedef struct TreeNode {
    int key; // ��� ��
    struct TreeNode* left, * right; // ���� �� ������ �ڽ� ������
} TreeNode;

// BST�� ��带 �����ϴ� �Լ�
TreeNode* insertBinaryNode(TreeNode* root, int key) {
    if (root == NULL) { // Ʈ���� ��������� �� ��� ����
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));

        if (newNode == NULL) { // �޸� �Ҵ� ���� �� ó��
            printf("Memory allocation failed.\n");
            return NULL;  // �޸� �Ҵ� ���� �� NULL ��ȯ
        }
        newNode->key = key; // ��� �� ����
        newNode->left = newNode->right = NULL; // �ڽ� ���� NULL�� �ʱ�ȭ
        return newNode;
    }

    // ���� ��ġ Ž��
    if (key < root->key)
        root->left = insertBinaryNode(root->left, key); // ���� ����Ʈ���� ����
    else if (key > root->key)
        root->right = insertBinaryNode(root->right, key); // ������ ����Ʈ���� ����

    return root; // ���� �� ��Ʈ ��ȯ
}

// BST���� ��带 �����ϴ� �Լ�
TreeNode* deleteBinaryNode(TreeNode* root, int key) {
    if (root == NULL) return root; // Ʈ���� ��������� NULL ��ȯ

    // ������ ��带 Ž��
    if (key < root->key)
        root->left = deleteBinaryNode(root->left, key); // ���� ����Ʈ���� �̵�
    else if (key > root->key)
        root->right = deleteBinaryNode(root->right, key); // ������ ����Ʈ���� �̵�
    else {
        // ������ ��带 ã�� ���
        if (root->left == NULL) { // ���� �ڽ��� ���� ���
            TreeNode* temp = root->right;
            free(root); // ���� ��� ����
            return temp;
        }
        else if (root->right == NULL) { // ������ �ڽ��� ���� ���
            TreeNode* temp = root->left;
            free(root); // ���� ��� ����
            return temp;
        }

        // ���ʰ� ������ �ڽ��� ��� �ִ� ���
        TreeNode* temp = root->right; // ������ ����Ʈ������ ���� ���� �� ã��
        while (temp && temp->left != NULL)
            temp = temp->left;

        root->key = temp->key; // �ּҰ��� ���� ��忡 ����
        root->right = deleteBinaryNode(root->right, temp->key); // ����� ��带 ����
    }

    return root; // ���� �� ��Ʈ ��ȯ
}

// BST���� Ư�� Ű�� Ž���ϴ� �Լ�
TreeNode* searchBinaryNode(TreeNode* root, int key) {
    if (root == NULL) return NULL; // ��尡 NULL�̸� Ž�� ����

    compareCount++;  // Ž�� �� �� Ƚ�� ����
    if (key == root->key) return root; // Ű�� ��ġ�ϸ� ��� ��ȯ
    else if (key < root->key) return searchBinaryNode(root->left, key); // ���� ����Ʈ���� �̵�
    else return searchBinaryNode(root->right, key); // ������ ����Ʈ���� �̵�
}

// BST���� ������ �۾�(����, ����, Ž��)�� �����ϴ� �Լ�
void doBinaryBatch(TreeNode* root) {
    compareCount = 0; // �� Ƚ�� �ʱ�ȭ
    searchCount = 0;  // Ž�� Ƚ�� �ʱ�ȭ

    for (int i = 0; i < 2000; i++) { // 2,000�� �ݺ�
        int A = rand() % 3;   // �۾� ���� (0: ����, 1: ����, 2: Ž��)
        int B = rand() % 1000; // ���� Ű ���� (0~999)

        if (A == 0) {
            root = insertBinaryNode(root, B);  // ����
        }
        else if (A == 1) {
            root = deleteBinaryNode(root, B);  // ����
        }
        else if (A == 2) {
            TreeNode* result = searchBinaryNode(root, B);  // Ž��
            if (result != NULL) {
                searchCount++;  // Ž�� ���� �� Ƚ�� ����
            }
        }
    }
}

// ���� �Լ�: AVL Ʈ���� BST�� ���� ��
int main(int argc, char* argv[]) {
    Node* root = NULL; // AVL Ʈ�� ��Ʈ �ʱ�ȭ
    srand(time(NULL)); // ���� ������ �ʱ�ȭ

    for (int i = 1; i <= 3; i++) { // ���� �񱳸� 3�� �ݺ�
        Sleep(1000); // 1�� ���

        float allCount = 0.0; // ��� �� Ƚ���� �����ϴ� ����

        // AVL Ʈ�� ���� �׽�Ʈ
        doAVLBatch(root); // AVL Ʈ������ 2,000���� ���� �۾� ����
        allCount = (float)compareCount / searchCount; // ��� �� Ƚ�� ���
        printf("\naverage AVL compare count: %.2f\n", allCount);

        freeTree(root); // AVL Ʈ�� �޸� ����
        root = NULL; // ��Ʈ �ʱ�ȭ
        compareCount = allCount = 0; // ���� �ʱ�ȭ

        // BST ���� �׽�Ʈ
        doBinaryBatch(root); // BST���� 2,000���� ���� �۾� ����
        allCount = (float)compareCount / searchCount; // ��� �� Ƚ�� ���
        printf("average Bin compare count: %.2f\n", allCount);
        freeTree(root); // BST �޸� ����
    }

    return 0; // ���α׷� ����
}
