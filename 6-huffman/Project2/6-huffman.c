#include<stdio.h>
#include<stdlib.h>
#define MAX_ELEMENT 200 // �ִ� �� ũ�� ����

// ��� ����ü ����
typedef struct Node {
    int weight;        // ����� ����ġ (������ �󵵼�)
    char ch;          // ����
    struct Node* left;  // ���� �ڽ� ��� ������
    struct Node* right; // ������ �ڽ� ��� ������
} Node;

// ���� ��Ҹ� �����ϴ� ����ü
typedef struct {
    Node* ptree;  // ���� ����� ��� ������
    char ch;      // ����
    int key;      // ����ġ (�󵵼�)
} element;

// �� ����ü ����
typedef struct {
    element heap[MAX_ELEMENT]; // �� �迭 (�ּ� �� ����)
    int heap_size;             // ���� �� ũ��
} HeapType;

// ���� �����ϴ� �Լ�
HeapType* create() {
    // HeapType ����ü�� ���� �޸� �Ҵ��Ͽ� �ʱ�ȭ
    return (HeapType*)malloc(sizeof(HeapType));
}

// ���� �ʱ�ȭ�ϴ� �Լ�
void init(HeapType* h) {
    h->heap_size = 0; // �� ũ�⸦ 0���� �ʱ�ȭ
}

// �ּ� ���� ��Ҹ� �����ϱ� ���� �Լ�
void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size); // �� ũ�⸦ ������Ű��, ���ο� ����� �ε����� ����

    // �θ� ���� ���Ͽ� ��ġ�� ã�� ����
    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2]; // �θ� ����� ���� ���� ��ġ�� �̵�
        i /= 2; // �θ� ��� �ε����� �̵�
    }
    h->heap[i] = item; // ���ο� ��� ����
}

// �ּ� ������ �ּ� ��Ҹ� �����ϱ� ���� �Լ�
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h->heap[1]; // ��Ʈ ���(�ּ� ��) ����
    temp = h->heap[(h->heap_size)--]; // ������ ��带 ��Ʈ�� �̵��ϰ� �� ũ�� ����
    parent = 1; // �θ� �ε��� �ʱ�ȭ
    child = 2; // ���� �ڽ� �ε��� �ʱ�ȭ

    // �ڽ� ���� ���Ͽ� �� ������ ����
    while (child <= h->heap_size) {
        // ������ �ڽ��� �����ϰ�, ������ �ڽ��� Ű�� ���� �ڽĺ��� ������ ������ �ڽ� ����
        if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
            child++;

        // ���� ����� Ű�� �ڽ� ����� Ű���� ������ ����
        if (temp.key < h->heap[child].key) break;

        h->heap[parent] = h->heap[child]; // �ڽ� ��带 �θ� ��� ��ġ�� �̵�
        parent = child; // �θ� �ε��� ������Ʈ
        child *= 2; // �ڽ� �ε����� �̵�
    }
    h->heap[parent] = temp; // ���� ���� ���� ��ġ�� ��ġ
    return item; // ������ ��� ��ȯ
}

// ���ο� ��带 �����ϴ� �Լ�
Node* createNode(char ch, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // �޸� �Ҵ�
    if (newNode == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n"); // �޸� �Ҵ� ���� �� ���� �޽��� ���
        exit(1);
    }
    newNode->ch = ch; // ���� ����
    newNode->weight = weight; // ����ġ ����
    newNode->left = newNode->right = NULL; // �ڽ� ���� NULL�� �ʱ�ȭ
    return newNode; // ������ ��� ��ȯ
}

// ������ Ʈ���� �����ϴ� �Լ�
Node* buildHuffmanTree(char characters[], int frequencies[], int size) {
    HeapType* h = create(); // �� ����
    init(h); // �� �ʱ�ȭ

    // �� ���ڿ� ���� ��带 �����ϰ� ���� ����
    for (int i = 0; i < size; i++) {
        element item;
        item.ptree = createNode(characters[i], frequencies[i]); // ���ο� ��� ����
        item.key = frequencies[i]; // ����� ����ġ ����
        insert_min_heap(h, item); // ���� ��� ����

        // ���� �� ���� ���
        for (int j = 1; j <= h->heap_size; j++) {
            printf("%d ", h->heap[j].key); // ���� �� ��� ���
        }
        printf("\n");
    }

    // ������ Ʈ�� ���� ����
    while (h->heap_size > 1) {
        element left = delete_min_heap(h); // �ּ� ��� ���� (���� ���� �� ��带 �����ϱ� ����)
        element right = delete_min_heap(h); // ���� �ּ� ��� ����
        Node* mergedNode = createNode('\0', left.ptree->weight + right.ptree->weight); // ���յ� ��� ����
        mergedNode->left = left.ptree; // ���� �ڽ����� ����
        mergedNode->right = right.ptree; // ������ �ڽ����� ����

        element newElement; // ���ο� �� ��� ����
        newElement.ptree = mergedNode; // ���յ� ��带 ����
        newElement.key = mergedNode->weight; // ���յ� ����� ����ġ ����

        insert_min_heap(h, newElement); // ���ο� ��Ҹ� ���� ����

        // ���� ���� ���
        printf("//%d + %d -> %d\n", left.ptree->weight, right.ptree->weight, mergedNode->weight);
        for (int j = 1; j <= h->heap_size; j++) {
            printf("%d ", h->heap[j].key); // ���� �� ���� ���
        }
        printf("\n");
    }

    return delete_min_heap(h).ptree; // ���� ������ Ʈ�� ��ȯ
}

// ������ �ڵ带 ����ϴ� ��� �Լ�
void printCodes(Node* root, int arr[], int top) {
    // ���� ����Ʈ���� �̵�
    if (root->left) {
        arr[top] = 1; // ���� �̵��� ��Ÿ���� �ڵ� �߰�
        printCodes(root->left, arr, top + 1); // ��� ȣ��
    }

    // ������ ����Ʈ���� �̵�
    if (root->right) {
        arr[top] = 0; // ������ �̵��� ��Ÿ���� �ڵ� �߰�
        printCodes(root->right, arr, top + 1); // ��� ȣ��
    }

    // ���� ��忡 �������� ��� �ڵ� ���
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->ch); // ���ڸ� ���
        for (int i = 0; i < top; i++)
            printf("%d", arr[i]); // �ش� ������ ������ �ڵ� ���
        printf("\n");
    }
}

// ������ �ڵ带 �����ϰ� ����ϴ� �Լ�
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    Node* root = buildHuffmanTree(characters, frequencies, size); // ������ Ʈ�� ����
    int* arr = (int*)malloc(size * sizeof(int)); // ������ �ڵ� ������ ���� �迭 ���� �޸� �Ҵ�
    if (arr == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n"); // �޸� �Ҵ� ���� �� ���� �޽��� ���
        exit(1);
    }

    int top = 0; // ���� ���� �Ǵ� �ε��� �ʱ�ȭ
    printCodes(root, arr, top); // ������ �ڵ� ���

    free(arr); // ���� �޸� ����
}

// ���� �Լ�
int main() {
    // ������ �ڵ带 ������ ���� �迭 �� �� ������ �󵵼� �迭
    char characters[] = { 'a','e','i','o','u','s','t' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 }; // �� ������ �󵵼� �迭
    int size = sizeof(characters) / sizeof(characters[0]); // ������ ���� ���

    GenerateHuffmanCodes(characters, frequencies, size); // ������ �ڵ� ���� �� ���

    return 0; // ���α׷� ����
}
