#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#pragma warning(disable:4996)
#include <stdlib.h>
#define MAX_SIZE 100
#define true 1
#include <string.h>

// ���� ��Ҹ� ��Ÿ���� ����ü, key ������ ������
typedef struct {
    int key;
} element;

// �� ����ü, heap �迭�� ���� heap_size�� ����
typedef struct {
    element heap[MAX_SIZE];
    int heap_size;
} TreeNode;

// �� ���� �Լ�, ���� �������� �����ϰ� �ʱ�ȭ��
TreeNode* create_heap() {
    TreeNode* h = (TreeNode*)malloc(sizeof(TreeNode));
    if (h == NULL) {
        fprintf(stderr, "�޸� �Ҵ翡 �����߽��ϴ�.\n");
        exit(EXIT_FAILURE);
    }
    h->heap_size = 0; // �� ũ�⸦ 0���� �ʱ�ȭ
    return h;
}

// ���� �ʱ�ȭ�ϴ� �Լ�, heap_size�� 0���� ����
void init_heap(TreeNode* h) {
    h->heap_size = 0;
}

// �� �Ҹ� �Լ�, �������� �Ҵ�� �޸𸮸� ������
void destroy_heap(TreeNode* h) {
    free(h);
}

// ���� ����ִ��� Ȯ���ϴ� �Լ�, heap_size�� 0�̸� true�� ��ȯ
int is_empty_heap(TreeNode* h) {
    return (h->heap_size == 0);
}

// ���� ���� á���� Ȯ���ϴ� �Լ�, heap_size�� MAX_SIZE-1�̸� true�� ��ȯ
int is_full_heap(TreeNode* h) {
    return (h->heap_size == (MAX_SIZE)-1);
}

// ���� ��� ��Ҹ� ����Ʈ �������� ����ϴ� �Լ�
void printHeapList(TreeNode* h) {
    if (is_empty_heap(h)) {  // ���� ����ִٸ� ��� �޽��� ���
        printf("���� ��� �ֽ��ϴ�.\n");
        return;
    }

    for (int i = 1; i <= h->heap_size; i++) {  // heap �迭�� ��Ҹ� ��� ���
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

// ���� �������� ����ϴ� �Լ�, �� �������� ��Ҹ� ���
void printHeapLevel(TreeNode* h) {
    if (is_empty_heap(h)) {  // ���� ����ִٸ� ��� �޽��� ���
        printf("���� ��� �ֽ��ϴ�.\n");
        return;
    }

    int level = 1;               // ���� ������ 1�� ����
    int elements_in_level = 1;   // ���� �������� ����� ����� ����
    int count = 1;               // ù ��° �� ��Һ��� ����

    printf("Ʈ�� ������ ��� :\n");
    while (count <= h->heap_size) {  // count�� heap_size���� �۰ų� ���� ������ �ݺ�
        printf("[%d] ", level);       // ���� ���� �ε��� ���
        for (int i = 0; i < elements_in_level && count <= h->heap_size; i++) {
            printf("%d ", h->heap[count].key);  // heap[count]�� ���� ����
            count++;
        }
        printf("\n");  // �� ���� ��� �� �� �ٲ�
        level++;
        elements_in_level *= 2;  // ���� �������� ����� ����� ������ �� ��� �ø�
    }
}

// �ʱ� �� ���� �� ����ϴ� �Լ�, �߰� �������� ��� ���� ����
void InsertMaxHeapSilent(TreeNode* h, int key) {
    if (is_full_heap(h)) {
        return;  // ���� ���� �� ��� �߰��� �ߴ�
    }

    element item;
    item.key = key;

    int i = ++(h->heap_size);  // �� ũ�⸦ ������Ű�� ������ ��ġ ����

    // ��ify up ����, �θ� ���� ���Ͽ� ��ġ�� ã�ư��� ����
    while ((i > 1) && (h->heap[i / 2].key < item.key)) {
        h->heap[i] = h->heap[i / 2];  // �θ� ��带 �Ʒ��� �̵�
        i = i / 2;
    }
    h->heap[i] = item;  // ���� ��ġ�� ����
}

// ����ڰ� ���� ��带 ������ �� ����ϴ� �Լ�, ������ ��µ�
void InsertMaxHeapTree(TreeNode* h, int key) {
    if (is_full_heap(h)) {
        printf("���� ���� á���ϴ�. �� �̻� �߰��� �� �����ϴ�.\n\n");
        return;
    }

    element item;
    item.key = key;

    int i = ++(h->heap_size);  // �� ũ�� ����
    int move_count = 0; // ��� �̵� Ƚ���� ī��Ʈ

    h->heap[i] = item; // �ϴ� �������� �߰�
    printHeapList(h); // �ʱ� �߰� ���� ���

    // ��ify up ����, �θ�� ���Ͽ� ��ȯ�ϸ� �� ������ ����
    while ((i > 1) && (h->heap[i / 2].key < item.key)) {
        // �θ� ���� ��ȯ
        element temp = h->heap[i / 2];
        h->heap[i / 2] = h->heap[i];
        h->heap[i] = temp;

        i = i / 2;
        printHeapList(h); // �� ���� ���
        move_count++;
    }
    printf("��尡 �̵��� Ƚ��:%d \n\n", move_count);  // ���� �̵� Ƚ�� ���
}

// �ʱ� �� ���� �� ����ϴ� �Լ�, inputData �迭�� ����Ͽ� ���� ����
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = create_heap();

    for (int i = 0; i < size; i++) {
        InsertMaxHeapSilent(root, inputData[i]);  // ������ �迭�� ����� ���� �ʱ�ȭ
    }
    return root;
}

// ������ �ֻ��� ��带 �����ϴ� �Լ�, ������ ������ ��µ�
element delete_heap(TreeNode* h) {
    if (is_empty_heap(h)) {
        printf("���� ��� �־� ������ �� �����ϴ�.\n");
        element empty = { -1 };
        return empty;
    }

    element item, temp;
    int parent, child;
    int move_count = 0; // �̵� Ƚ�� ī��Ʈ

    item = h->heap[1]; // �ֻ��� ��� ����
    temp = h->heap[h->heap_size]; // ������ ��� ����

    (h->heap_size)--;  // �� ũ�⸦ ���ҽ�Ŵ

    parent = 1;
    child = 2;

    printHeapList(h); // ���� �� ���� ���

    // ��ify down ����, �ڽ� ���� ���Ͽ� ��ġ�� ã�ư��� ����
    while (child <= h->heap_size) {
        // �ڽ� ��� �� �� ū ��� ����
        if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
            child++;
        }

        if (temp.key >= h->heap[child].key) {
            break;
        }

        h->heap[parent] = h->heap[child];  // �θ� �ڸ��� �ڽ� ��� �̵�
        parent = child;
        child *= 2;
        move_count++;

        printHeapList(h); // �߰� ���� ���
    }

    h->heap[parent] = temp;  // �������� temp ���� �θ� ��ġ�� ��ġ

    printf("��尡 �̵��� Ƚ��: %d\n", move_count);  // ���� �̵� Ƚ�� ���
    return item;  // ������ ��带 ��ȯ
}

// ������ �ֻ��� ��带 ��ȯ�ϴ� �Լ�, �ܼ� ��ȸ
element find_heap(TreeNode* h) {
    if (is_empty_heap(h)) {
        printf("���� ��� �ֽ��ϴ�.\n");
        element empty = { -1 };
        return empty;
    }
    return h->heap[1];  // �ֻ��� ��带 ��ȯ
}

// ����� �������̽� �Լ�, ����ڰ� �Է��� ��ɿ� ���� ��� �߰�, ����, ��� ���� ó��
void runUserInterface(TreeNode* root) {
    char menu;
    printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
    printf("��      i    :��� �߰�        ��\n");
    printf("��      d    :��� ����        ��\n");
    printf("��      p    :������ ���      ��\n");
    printf("��      c    :����             ��\n");
    printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n\n");

    while (true) {
        printf("�޴� �Է�: ");
        scanf(" %c", &menu);  // �޴��� �Է¹���
        switch (menu) {
        case 'i': {  // ��� �߰�
            int num;
            printf("�߰��� �� �Է�: ");
            scanf("%d", &num);
            InsertMaxHeapTree(root, num);  // �Էµ� ���� ���� �߰�
            break;
        }
        case 'd': {  // ��� ����
            if (is_empty_heap(root)) {
                printf("���� ��� �־� ������ �� �����ϴ�.\n\n");
            }
            else {
                element removed = delete_heap(root);  // �ֻ��� ��带 ����
                printf("\n");
            }
            break;
        }
        case 'p': {  // ������ ���
            printHeapLevel(root);  // ���� �������� ���
            printf("\n");
            break;
        }
        case 'c': {  // ����
            exit(1);  // ���α׷��� ����
        }
        default:
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���.\n\n");  // �߸��� �Է� ó��
            break;
        }
    }
}

// ���� �Լ�, �ʱ� �� ���� �� ����� �������̽� ����
int main() {
    int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };  // �ʱ� ������ �迭
    int size = sizeof(inputData) / sizeof(inputData[0]);

    // �ʱ� �� ���� (��� ����)
    TreeNode* root = generateMaxHeapTree(inputData, size);

    // ����� �������̽� ����
    runUserInterface(root);

    // �� �Ҹ�
    destroy_heap(root);
    return 0;
}
