#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES + 1]; // �θ� ��带 ������ �迭

// �ʱ� ���� ����
void set_init(int n) {
    for (int i = 1; i <= n; i++)
        parent[i] = -1; // �� ����� �θ� -1�� �ʱ�ȭ
}

// ���� ã��
int set_find(int curr) {
    if (parent[curr] == -1) // �θ� ������ ���� ��� ��ȯ
        return curr;
    while (parent[curr] != -1) curr = parent[curr]; // ��Ʈ�� ã�� ������ �θ� ����
    return curr; // ��Ʈ ��ȯ
}

// ���� ��ġ��
void set_union(int a, int b) {
    int root1 = set_find(a); // ù ��° ����� ��Ʈ ã��
    int root2 = set_find(b); // �� ��° ����� ��Ʈ ã��
    if (root1 != root2) // ��Ʈ�� �ٸ��� ��ġ��
        parent[root1] = root2; // ù ��° ����� ��Ʈ�� �� ��° ����� ��Ʈ�� ����
}

// ���� ����ü ����
struct Edge {
    int start, end, weight; // ������ ���� ����, �� ����, ����ġ
};

// �׷��� ����ü ����
typedef struct GraphType {
    int num_vertices;  // ����� ����
    int num_edges;     // ������ ����
    struct Edge edges[2 * MAX_VERTICES]; // ���� �迭
} GraphType;

// �׷��� �ʱ�ȭ
void graph_init(GraphType* g) {
    g->num_vertices = 0; // ��� �� �ʱ�ȭ
    g->num_edges = 0; // ���� �� �ʱ�ȭ
}

// ���� ����
void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->num_edges].start = start; // ���� ���� ����
    g->edges[g->num_edges].end = end; // �� ���� ����
    g->edges[g->num_edges].weight = w; // ����ġ ����
    g->num_edges++; // ���� �� ����
    if (g->num_vertices < start) g->num_vertices = start; // �ִ� ��� �� ������Ʈ
    if (g->num_vertices < end) g->num_vertices = end; // �ִ� ��� �� ������Ʈ
}

// ���� �� �Լ� (qsort ���)
int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    if (x->weight == y->weight) {
        if (x->start == y->start)
            return x->end - y->end; // ���� ����ġ�� ������ ���� �������� ����
        return x->start - y->start; // ���� ���� �������� ����
    }
    return x->weight - y->weight; // ����ġ �������� ����
}

// Quick Kruskal �˰���
void QuickKruskal(GraphType* g) {
    int edge_accepted = 0; // ���õ� ���� ��
    int uset, vset; // ���� ���� ����
    struct Edge e; // ���� ����

    set_init(g->num_vertices); // ���� �ʱ�ȭ
    qsort(g->edges, g->num_edges, sizeof(struct Edge), compare); // ���� ����

    printf("Quick Based Kruskal\n");
    int i = 0;
    while (edge_accepted < (g->num_vertices - 1)) { // �ּ� ���� Ʈ���� ���� ��
        e = g->edges[i]; // ���� ���� ����
        uset = set_find(e.start); // ���� ������ ��Ʈ ã��
        vset = set_find(e.end); // �� ������ ��Ʈ ã��
        if (uset != vset) { // �� ������ ��Ʈ�� �ٸ���
            printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight); // ���� ���� ���
            edge_accepted++; // ���õ� ���� �� ����
            set_union(uset, vset); // �� ���� ��ġ��
        }
        i++;
    }
    printf("\n");
}

// �ּ� �� ����ü ����
typedef struct MinHeap {
    struct Edge* data; // ���� �迭
    int capacity; // �ִ� �뷮
    int size; // ���� ũ��
} MinHeap;

// �ּ� �� ����
MinHeap* create_min_heap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap)); // �� �޸� �Ҵ�
    if (heap == NULL) return NULL; // �Ҵ� ���� �� NULL ��ȯ
    heap->data = (struct Edge*)malloc(capacity * sizeof(struct Edge)); // ���� �迭 �޸� �Ҵ�
    if (heap->data == NULL) {
        free(heap); // �Ҵ� ���� �� �� �޸� ����
        return NULL; // NULL ��ȯ
    }
    heap->capacity = capacity; // �ִ� �뷮 ����
    heap->size = 0; // ���� ũ�� �ʱ�ȭ
    return heap; // ������ �� ��ȯ
}

// ���� ���� ����
void min_heap_insert(MinHeap* heap, struct Edge edge) {
    if (heap->size < heap->capacity) { // ���� ���� ���� ������
        heap->data[heap->size] = edge; // ���� ����
        int i = heap->size;
        heap->size++; // ũ�� ����

        // �θ�� ���Ͽ� ���� ���� ����
        while (i > 0 && heap->data[i].weight < heap->data[(i - 1) / 2].weight) {
            struct Edge temp = heap->data[i];
            heap->data[i] = heap->data[(i - 1) / 2];
            heap->data[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
    }
}

// �ּ� ������ �ּ� ���� ����
struct Edge min_heap_extract_min(MinHeap* heap) {
    struct Edge minEdge = heap->data[0]; // �ּ� ���� ����
    heap->data[0] = heap->data[heap->size - 1]; // ������ ������ ��Ʈ�� �̵�
    heap->size--; // ũ�� ����

    int i = 0;
    // �ڽİ� ���Ͽ� ���� ���� ����
    while (i * 2 + 1 < heap->size) {
        int smallest = i;
        if (heap->data[i * 2 + 1].weight < heap->data[smallest].weight) {
            smallest = i * 2 + 1; // ���� �ڽ��� �� ������ ������Ʈ
        }
        if (i * 2 + 2 < heap->size && heap->data[i * 2 + 2].weight < heap->data[smallest].weight) {
            smallest = i * 2 + 2; // ������ �ڽ��� �� ������ ������Ʈ
        }
        if (smallest != i) { // ���� ���� �ڽİ� ���� �ε����� �ٸ���
            struct Edge temp = heap->data[i];
            heap->data[i] = heap->data[smallest];
            heap->data[smallest] = temp; // �� �� ��ȯ
            i = smallest; // �ε��� ������Ʈ
        }
        else {
            break; // �� ���� ����
        }
    }
    return minEdge; // �ּ� ���� ��ȯ
}

// Min Heap ��� Kruskal �˰���
void MinHeapKruskal(GraphType* g) {
    int edge_accepted = 0; // ���õ� ���� ��
    int uset, vset; // ���� ���� ����

    set_init(g->num_vertices); // ���� �ʱ�ȭ
    MinHeap* heap = create_min_heap(g->num_edges); // �� ����
    if (heap == NULL) {
        printf("Heap creation failed!\n"); // �� ���� ���� �޽���
        return;
    }

    for (int i = 0; i < g->num_edges; i++) {
        min_heap_insert(heap, g->edges[i]); // ��� ������ ���� ����
    }

    printf("MinHeap Based Kruskal\n");
    while (edge_accepted < (g->num_vertices - 1)) { // �ּ� ���� Ʈ���� ���� ��
        struct Edge e = min_heap_extract_min(heap); // �ּ� ���� ����
        uset = set_find(e.start); // ���� ������ ��Ʈ ã��
        vset = set_find(e.end); // �� ������ ��Ʈ ã��
        if (uset != vset) { // �� ������ ��Ʈ�� �ٸ���
            printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight); // ���� ���� ���
            edge_accepted++; // ���õ� ���� �� ����
            set_union(uset, vset); // �� ���� ��ġ��
        }
    }
    printf("\n");
    free(heap->data); // �� �޸� ����
    free(heap); // �� ����ü �޸� ����
}

void GenerateGraph(GraphType* g) {
    //�����߰� 
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}

int main() {
    GraphType* g;// �׷��� Ÿ���� ������ ����
    g= (GraphType*)malloc(sizeof(GraphType));// �׷��� �޸� ���� �Ҵ�
    graph_init(g);// �׷��� �ʱ�ȭ


    //�׷����� �����ϴ� �Լ� 
    GenerateGraph(g);

    QuickKruskal(g);  //quick ��� kruskal
    MinHeapKruskal(g); //minheap ��� kruskal

    free(g);
    return 0;
}
