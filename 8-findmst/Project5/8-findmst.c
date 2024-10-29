#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES + 1]; // 부모 노드를 저장할 배열

// 초기 집합 설정
void set_init(int n) {
    for (int i = 1; i <= n; i++)
        parent[i] = -1; // 각 노드의 부모를 -1로 초기화
}

// 집합 찾기
int set_find(int curr) {
    if (parent[curr] == -1) // 부모가 없으면 현재 노드 반환
        return curr;
    while (parent[curr] != -1) curr = parent[curr]; // 루트를 찾을 때까지 부모를 따라감
    return curr; // 루트 반환
}

// 집합 합치기
void set_union(int a, int b) {
    int root1 = set_find(a); // 첫 번째 노드의 루트 찾기
    int root2 = set_find(b); // 두 번째 노드의 루트 찾기
    if (root1 != root2) // 루트가 다르면 합치기
        parent[root1] = root2; // 첫 번째 노드의 루트를 두 번째 노드의 루트로 설정
}

// 간선 구조체 정의
struct Edge {
    int start, end, weight; // 간선의 시작 정점, 끝 정점, 가중치
};

// 그래프 구조체 정의
typedef struct GraphType {
    int num_vertices;  // 노드의 개수
    int num_edges;     // 간선의 개수
    struct Edge edges[2 * MAX_VERTICES]; // 간선 배열
} GraphType;

// 그래프 초기화
void graph_init(GraphType* g) {
    g->num_vertices = 0; // 노드 수 초기화
    g->num_edges = 0; // 간선 수 초기화
}

// 간선 삽입
void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->num_edges].start = start; // 시작 정점 설정
    g->edges[g->num_edges].end = end; // 끝 정점 설정
    g->edges[g->num_edges].weight = w; // 가중치 설정
    g->num_edges++; // 간선 수 증가
    if (g->num_vertices < start) g->num_vertices = start; // 최대 노드 수 업데이트
    if (g->num_vertices < end) g->num_vertices = end; // 최대 노드 수 업데이트
}

// 간선 비교 함수 (qsort 사용)
int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    if (x->weight == y->weight) {
        if (x->start == y->start)
            return x->end - y->end; // 간선 가중치가 같으면 시작 정점으로 정렬
        return x->start - y->start; // 시작 정점 기준으로 정렬
    }
    return x->weight - y->weight; // 가중치 기준으로 정렬
}

// Quick Kruskal 알고리즘
void QuickKruskal(GraphType* g) {
    int edge_accepted = 0; // 선택된 간선 수
    int uset, vset; // 집합 저장 변수
    struct Edge e; // 간선 변수

    set_init(g->num_vertices); // 집합 초기화
    qsort(g->edges, g->num_edges, sizeof(struct Edge), compare); // 간선 정렬

    printf("Quick Based Kruskal\n");
    int i = 0;
    while (edge_accepted < (g->num_vertices - 1)) { // 최소 신장 트리의 간선 수
        e = g->edges[i]; // 현재 간선 선택
        uset = set_find(e.start); // 시작 정점의 루트 찾기
        vset = set_find(e.end); // 끝 정점의 루트 찾기
        if (uset != vset) { // 두 정점의 루트가 다르면
            printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight); // 간선 선택 출력
            edge_accepted++; // 선택된 간선 수 증가
            set_union(uset, vset); // 두 집합 합치기
        }
        i++;
    }
    printf("\n");
}

// 최소 힙 구조체 정의
typedef struct MinHeap {
    struct Edge* data; // 간선 배열
    int capacity; // 최대 용량
    int size; // 현재 크기
} MinHeap;

// 최소 힙 생성
MinHeap* create_min_heap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap)); // 힙 메모리 할당
    if (heap == NULL) return NULL; // 할당 실패 시 NULL 반환
    heap->data = (struct Edge*)malloc(capacity * sizeof(struct Edge)); // 간선 배열 메모리 할당
    if (heap->data == NULL) {
        free(heap); // 할당 실패 시 힙 메모리 해제
        return NULL; // NULL 반환
    }
    heap->capacity = capacity; // 최대 용량 설정
    heap->size = 0; // 현재 크기 초기화
    return heap; // 생성된 힙 반환
}

// 힙에 간선 삽입
void min_heap_insert(MinHeap* heap, struct Edge edge) {
    if (heap->size < heap->capacity) { // 힙이 가득 차지 않으면
        heap->data[heap->size] = edge; // 간선 삽입
        int i = heap->size;
        heap->size++; // 크기 증가

        // 부모와 비교하여 힙의 성질 유지
        while (i > 0 && heap->data[i].weight < heap->data[(i - 1) / 2].weight) {
            struct Edge temp = heap->data[i];
            heap->data[i] = heap->data[(i - 1) / 2];
            heap->data[(i - 1) / 2] = temp;
            i = (i - 1) / 2;
        }
    }
}

// 최소 힙에서 최소 간선 추출
struct Edge min_heap_extract_min(MinHeap* heap) {
    struct Edge minEdge = heap->data[0]; // 최소 간선 저장
    heap->data[0] = heap->data[heap->size - 1]; // 마지막 간선을 루트로 이동
    heap->size--; // 크기 감소

    int i = 0;
    // 자식과 비교하여 힙의 성질 유지
    while (i * 2 + 1 < heap->size) {
        int smallest = i;
        if (heap->data[i * 2 + 1].weight < heap->data[smallest].weight) {
            smallest = i * 2 + 1; // 왼쪽 자식이 더 작으면 업데이트
        }
        if (i * 2 + 2 < heap->size && heap->data[i * 2 + 2].weight < heap->data[smallest].weight) {
            smallest = i * 2 + 2; // 오른쪽 자식이 더 작으면 업데이트
        }
        if (smallest != i) { // 가장 작은 자식과 현재 인덱스가 다르면
            struct Edge temp = heap->data[i];
            heap->data[i] = heap->data[smallest];
            heap->data[smallest] = temp; // 두 값 교환
            i = smallest; // 인덱스 업데이트
        }
        else {
            break; // 힙 성질 만족
        }
    }
    return minEdge; // 최소 간선 반환
}

// Min Heap 기반 Kruskal 알고리즘
void MinHeapKruskal(GraphType* g) {
    int edge_accepted = 0; // 선택된 간선 수
    int uset, vset; // 집합 저장 변수

    set_init(g->num_vertices); // 집합 초기화
    MinHeap* heap = create_min_heap(g->num_edges); // 힙 생성
    if (heap == NULL) {
        printf("Heap creation failed!\n"); // 힙 생성 실패 메시지
        return;
    }

    for (int i = 0; i < g->num_edges; i++) {
        min_heap_insert(heap, g->edges[i]); // 모든 간선을 힙에 삽입
    }

    printf("MinHeap Based Kruskal\n");
    while (edge_accepted < (g->num_vertices - 1)) { // 최소 신장 트리의 간선 수
        struct Edge e = min_heap_extract_min(heap); // 최소 간선 추출
        uset = set_find(e.start); // 시작 정점의 루트 찾기
        vset = set_find(e.end); // 끝 정점의 루트 찾기
        if (uset != vset) { // 두 정점의 루트가 다르면
            printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight); // 간선 선택 출력
            edge_accepted++; // 선택된 간선 수 증가
            set_union(uset, vset); // 두 집합 합치기
        }
    }
    printf("\n");
    free(heap->data); // 힙 메모리 해제
    free(heap); // 힙 구조체 메모리 해제
}

void GenerateGraph(GraphType* g) {
    //간선추가 
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
    GraphType* g;// 그래프 타입의 포인터 선언
    g= (GraphType*)malloc(sizeof(GraphType));// 그래프 메모리 동적 할당
    graph_init(g);// 그래프 초기화


    //그래프를 생성하는 함수 
    GenerateGraph(g);

    QuickKruskal(g);  //quick 기반 kruskal
    MinHeapKruskal(g); //minheap 기반 kruskal

    free(g);
    return 0;
}
