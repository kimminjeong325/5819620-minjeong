#include <stdio.h>
#include <stdlib.h>
#define INF 9999 // 연결이 없는 경우를 나타내기 위한 큰 수
#define MAX_VERTICES 11 // 그래프의 최대 정점 수 (노드 1부터 10까지 사용)

// 연결 리스트의 노드 구조체 정의
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// 그래프를 나타내는 구조체 정의 (연결 리스트 사용)
typedef struct {
    int n; // 정점의 개수
    Node* adjList[MAX_VERTICES]; // 인접 리스트
} GraphType;

// 최소 힙의 노드 구조체 정의
typedef struct {
    int vertex;
    int distance;
} HeapNode;

// 최소 힙 구조체 정의
typedef struct {
    HeapNode nodes[MAX_VERTICES];
    int size;
} MinHeap;

// 그래프 초기화 함수
void init_graph(GraphType* g, int n) {
    g->n = n;
    for (int i = 1; i <= n; i++) {
        g->adjList[i] = NULL;
    }
}

// 간선 추가 함수
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

// 최소 힙 초기화 함수
void init_min_heap(MinHeap* heap) {
    heap->size = 0;
}

// 최소 힙 삽입 함수
void insert_min_heap(MinHeap* heap, int vertex, int distance) {
    int i = heap->size++;
    while (i > 0 && distance < heap->nodes[(i - 1) / 2].distance) {
        heap->nodes[i] = heap->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->nodes[i].vertex = vertex;
    heap->nodes[i].distance = distance;
}

// 최소 힙에서 최소 노드를 제거하는 함수
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

// 다익스트라 알고리즘을 사용하여 최단 경로를 찾는 함수
void shortest_path(GraphType* g, int start) {
    int distance[MAX_VERTICES]; // 시작 정점으로부터의 거리 배열
    int found[MAX_VERTICES];    // 각 정점의 방문 여부를 저장하는 배열
    int found_order[MAX_VERTICES]; // 방문한 순서를 기록하는 배열
    int found_count = 0;        // 방문한 정점의 개수를 세기 위한 변수
    MinHeap heap;
    init_min_heap(&heap);

    // 초기화: 시작 정점에서 다른 정점으로의 거리 설정
    for (int i = 1; i <= g->n; i++) {
        distance[i] = INF;
        found[i] = 0; // 모든 정점은 아직 방문되지 않음
    }
    distance[start] = 0;
    insert_min_heap(&heap, start, 0);

    // 다익스트라 알고리즘의 주요 루프
    while (heap.size > 0) {
        HeapNode minNode = delete_min_heap(&heap);
        int u = minNode.vertex;
        if (found[u]) continue; // 이미 방문한 정점은 무시

        found[u] = 1; // 현재 정점을 방문으로 표시
        found_order[found_count++] = u; // 방문한 정점을 방문 순서에 추가

        // 선택한 정점을 기준으로 인접한 정점들의 최단 거리 갱신
        Node* current = g->adjList[u];
        while (current != NULL) {
            int v = current->vertex;
            int weight = current->weight;
            if (!found[v] && distance[u] + weight < distance[v]) { // 거리 갱신 조건
                distance[v] = distance[u] + weight;
                insert_min_heap(&heap, v, distance[v]);
            }
            current = current->next;
        }

        // 각 단계별 distance와 found 배열 출력
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

    // 방문 순서 출력
    printf("Found Order: ");
    for (int i = 0; i < found_count; i++) {
        printf("%d ", found_order[i]);
    }
    printf("\n");
}

int main() {
    GraphType g;
    init_graph(&g, 10); // 정점의 개수 초기화

    // 간선 추가
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

    int start_vertex = 1; // 시작 정점 (1번 노드부터 시작하도록 설정)
    shortest_path(&g, start_vertex); // 다익스트라 알고리즘 실행

    return 0;
}
