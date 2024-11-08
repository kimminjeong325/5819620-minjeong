#include <stdio.h>
#include <stdlib.h>
#define INF 9999 // ������ ���� ��츦 ��Ÿ���� ���� ū ��
#define MAX_VERTICES 11 // �׷����� �ִ� ���� �� (��� 1���� 10���� ���)

// ���� ����Ʈ�� ��� ����ü ����
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// �׷����� ��Ÿ���� ����ü ���� (���� ����Ʈ ���)
typedef struct {
    int n; // ������ ����
    Node* adjList[MAX_VERTICES]; // ���� ����Ʈ
} GraphType;

// �ּ� ���� ��� ����ü ����
typedef struct {
    int vertex;
    int distance;
} HeapNode;

// �ּ� �� ����ü ����
typedef struct {
    HeapNode nodes[MAX_VERTICES];
    int size;
} MinHeap;

// �׷��� �ʱ�ȭ �Լ�
void init_graph(GraphType* g, int n) {
    g->n = n;
    for (int i = 1; i <= n; i++) {
        g->adjList[i] = NULL;
    }
}

// ���� �߰� �Լ�
void add_edge(GraphType* g, int u, int v, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = g->adjList[u];
    g->adjList[u] = newNode;
}

// �ּ� �� �ʱ�ȭ �Լ�
void init_min_heap(MinHeap* heap) {
    heap->size = 0;
}

// �ּ� �� ���� �Լ�
void insert_min_heap(MinHeap* heap, int vertex, int distance) {
    int i = heap->size++;
    while (i > 0 && distance < heap->nodes[(i - 1) / 2].distance) {
        heap->nodes[i] = heap->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->nodes[i].vertex = vertex;
    heap->nodes[i].distance = distance;
}

// �ּ� ������ �ּ� ��带 �����ϴ� �Լ�
HeapNode delete_min_heap(MinHeap* heap) {
    HeapNode minNode = heap->nodes[0];
    HeapNode lastNode = heap->nodes[--heap->size];
    int parent = 0, child = 1;
    while (child < heap->size) {
        if (child + 1 < heap->size && heap->nodes[child].distance > heap->nodes[child + 1].distance) {
            child++;
        }
        if (lastNode.distance <= heap->nodes[child].distance) break;
        heap->nodes[parent] = heap->nodes[child];
        parent = child;
        child = 2 * parent + 1;
    }
    heap->nodes[parent] = lastNode;
    return minNode;
}

// ���ͽ�Ʈ�� �˰����� ����Ͽ� �ִ� ��θ� ã�� �Լ�
void shortest_path(GraphType* g, int start) {
    int distance[MAX_VERTICES]; // ���� �������κ����� �Ÿ� �迭
    int found[MAX_VERTICES];    // �� ������ �湮 ���θ� �����ϴ� �迭
    int found_order[MAX_VERTICES]; // �湮�� ������ ����ϴ� �迭
    int found_count = 0;        // �湮�� ������ ������ ���� ���� ����
    MinHeap heap;
    init_min_heap(&heap);

    // �ʱ�ȭ: ���� �������� �ٸ� ���������� �Ÿ� ����
    for (int i = 1; i <= g->n; i++) {
        distance[i] = INF;
        found[i] = 0; // ��� ������ ���� �湮���� ����
    }
    distance[start] = 0;
    insert_min_heap(&heap, start, 0);

    // ���ͽ�Ʈ�� �˰����� �ֿ� ����
    while (heap.size > 0) {
        HeapNode minNode = delete_min_heap(&heap);
        int u = minNode.vertex;
        if (found[u]) continue; // �̹� �湮�� ������ ����

        found[u] = 1; // ���� ������ �湮���� ǥ��
        found_order[found_count++] = u; // �湮�� ������ �湮 ������ �߰�

        // ������ ������ �������� ������ �������� �ִ� �Ÿ� ����
        Node* current = g->adjList[u];
        while (current != NULL) {
            int v = current->vertex;
            int weight = current->weight;
            if (!found[v] && distance[u] + weight < distance[v]) { // �Ÿ� ���� ����
                distance[v] = distance[u] + weight;
                insert_min_heap(&heap, v, distance[v]);
            }
            current = current->next;
        }

        // �� �ܰ躰 distance�� found �迭 ���
        printf("Distance: ");
        for (int k = 1; k <= g->n; k++) {
            if (distance[k] == INF) printf(" * ");
            else printf("%d ", distance[k]);
        }
        printf("\nFound: ");
        for (int k = 1; k <= g->n; k++) {
            printf("%d ", found[k]);
        }
        printf("\n\n");
    }

    // �湮 ���� ���
    printf("Found Order: ");
    for (int i = 0; i < found_count; i++) {
        printf("%d ", found_order[i]);
    }
    printf("\n");
}

int main() {
    GraphType g;
    init_graph(&g, 10); // ������ ���� �ʱ�ȭ

    // ���� �߰�
    add_edge(&g, 1, 2, 3);
    add_edge(&g, 1, 6, 11);
    add_edge(&g, 1, 7, 12);
    add_edge(&g, 2, 3, 8);
    add_edge(&g, 2, 4, 4);
    add_edge(&g, 2, 5, 1);
    add_edge(&g, 3, 4, 2);
    add_edge(&g, 3, 7, 6);
    add_edge(&g, 3, 8, 5);
    add_edge(&g, 4, 5, 13);
    add_edge(&g, 4, 8, 14);
    add_edge(&g, 4, 10, 16);
    add_edge(&g, 5, 6, 9);
    add_edge(&g, 5, 9, 18);
    add_edge(&g, 5, 10, 17);
    add_edge(&g, 7, 8, 13);
    add_edge(&g, 8, 10, 15);
    add_edge(&g, 9, 10, 10);
    add_edge(&g, 10, 4, 16);
    add_edge(&g, 10, 5, 17);
    add_edge(&g, 10, 8, 15);

    int start_vertex = 1; // ���� ���� (1�� ������ �����ϵ��� ����)
    shortest_path(&g, start_vertex); // ���ͽ�Ʈ�� �˰��� ����

    return 0;
}
