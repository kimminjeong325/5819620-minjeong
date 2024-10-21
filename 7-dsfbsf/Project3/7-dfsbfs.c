#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50 // 최대 정점 수 정의

// 그래프 노드 구조체 정의
typedef struct GraphNode {
    int vertex; // 정점 번호
    struct GraphNode* link; // 다음 노드를 가리키는 포인터
} GraphNode;

// 그래프 구조체 정의
typedef struct GraphType {
    int n; // 현재 정점 수
    GraphNode* adj_list[MAX_VERTICES]; // 인접 리스트
} GraphType;

int visited[MAX_VERTICES]; // 방문 여부 배열
int visit_count; // 방문한 노드 수

// 그래프 초기화 함수
void init(GraphType* g) {
    g->n = 0; // 정점 수 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj_list[i] = NULL; // 인접 리스트 초기화
    }
}

// 정점 추가 함수
void insert_vertex(GraphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프: 정점의 개수 초과\n"); // 정점 수 초과 오류 메시지
        return;
    }
    g->n++; // 정점 수 증가
}

// 간선 추가 함수
void insert_edge(GraphType* g, int u, int v) {
    GraphNode* node; // 새 노드를 위한 포인터
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류\n"); // 정점 번호 오류 메시지
        return;
    }
    node = (GraphNode*)malloc(sizeof(GraphNode)); // 새 노드 메모리 할당
    node->vertex = v; // 정점 번호 설정
    node->link = g->adj_list[u]; // 기존 인접 노드 연결
    g->adj_list[u] = node; // 인접 리스트에 새 노드 추가
}

// 방문 배열 및 방문한 노드 수 초기화 함수
void reset_visited() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = 0; // 모든 정점을 방문하지 않음으로 초기화
    }
    visit_count = 0; // 방문한 노드 수 초기화
}

// 반복적 깊이 우선 탐색 함수
void dfs_iterative(GraphType* g, int start, int end) {
    int stack[MAX_VERTICES], top = -1; // 스택 초기화
    reset_visited(); // 방문 배열 초기화

    stack[++top] = start; // 시작 정점 스택에 추가
    visited[start] = 1; // 시작 정점 방문 처리
    visit_count++; // 방문한 노드 수 증가

    while (top >= 0) {
        int v = stack[top]; // 스택에서 정점 가져오기
        printf("%d ", v); // 방문한 노드 출력

        if (v == end) {
            printf("\n탐색 성공: %d\n", end); // 성공 메시지 출력
            printf("방문한 노드의 수: %d\n", visit_count); // 방문한 노드 수 출력
            return; // 탐색 성공 시 반환
        }

        GraphNode* w = g->adj_list[v]; // 인접 노드 탐색 시작
        int pushed = 0; // 노드를 스택에 넣었는지 여부 확인

        while (w != NULL) {
            if (!visited[w->vertex]) {
                stack[++top] = w->vertex; // 스택에 추가
                visited[w->vertex] = 1; // 노드 방문 처리
                visit_count++; // 방문한 노드 수 증가
                pushed = 1; // 새로운 노드를 스택에 추가했음을 표시
                break; // 새로운 노드를 스택에 넣었으므로 루프 탈출
            }
            w = w->link; // 다음 인접 노드로 이동
        }

        if (!pushed) {
            // 더 이상 방문할 노드가 없으면 스택에서 pop (백트래킹)
            top--;
        }
    }
    printf("\n탐색 실패: %d\n", end); // 탐색 실패 메시지
}

// 너비 우선 탐색 함수
void bfs(GraphType* g, int start, int end) {
    int queue[MAX_VERTICES], front = -1, rear = -1; // 큐 초기화
    reset_visited(); // 방문 배열 초기화
    queue[++rear] = start; // 시작 정점 큐에 추가
    visited[start] = 1; // 시작 정점 방문 처리

    while (front < rear) {
        front++; // 큐의 앞쪽 증가
        int v = queue[front]; // 큐에서 정점 가져오기
        printf("%d ", v); // 방문한 노드 출력

        if (v == end) {
            printf("\n탐색 성공: %d\n", end); // 성공 메시지 출력
            printf("방문한 노드의 수: %d\n", visit_count); // 방문한 노드 수 출력
            return; // 탐색 성공 시 반환
        }

        GraphNode* w = g->adj_list[v]; // 인접 노드 탐색 시작
        while (w != NULL) {
            if (!visited[w->vertex]) {
                visited[w->vertex] = 1; // 노드 방문 처리
                visit_count++; // 방문한 노드 수 증가
                queue[++rear] = w->vertex; // 큐에 추가
            }
            w = w->link; // 다음 인접 노드로 이동
        }
    }
    printf("\n탐색 실패: %d\n", end); // 탐색 실패 메시지
}

// 그래프 메모리 해제 함수
void free_graph(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* current = g->adj_list[i]; // 현재 노드
        while (current != NULL) {
            GraphNode* temp = current; // 현재 노드 임시 저장
            current = current->link; // 다음 노드로 이동
            free(temp); // 각 노드 메모리 해제
        }
    }
    free(g); // 그래프 구조체 메모리 해제
}

int main() {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType)); // 그래프 메모리 할당
    init(g); // 그래프 초기화

    // 정점 추가
    for (int i = 0; i < 11; i++)
        insert_vertex(g, i);

    // 간선 추가
    insert_edge(g, 10, 1);
    insert_edge(g, 1, 10);
    insert_edge(g, 7, 10);
    insert_edge(g, 10, 7);
    insert_edge(g, 8, 10);
    insert_edge(g, 10, 8);
    insert_edge(g, 6, 8);
    insert_edge(g, 8, 6);
    insert_edge(g, 6, 7);
    insert_edge(g, 7, 6);
    insert_edge(g, 4, 7);
    insert_edge(g, 7, 4);
    insert_edge(g, 4, 6);
    insert_edge(g, 6, 4);
    insert_edge(g, 3, 5);
    insert_edge(g, 5, 3);
    insert_edge(g, 4, 5);
    insert_edge(g, 5, 4);
    insert_edge(g, 3, 4);
    insert_edge(g, 4, 3);
    insert_edge(g, 2, 4);
    insert_edge(g, 4, 2);
    insert_edge(g, 2, 3);
    insert_edge(g, 3, 2);
    insert_edge(g, 1, 7);
    insert_edge(g, 7, 1);
    insert_edge(g, 1, 5);
    insert_edge(g, 5, 1);
    insert_edge(g, 1, 4);
    insert_edge(g, 4, 1);
    insert_edge(g, 9, 0);
    insert_edge(g, 0, 9);
    insert_edge(g, 6, 0);
    insert_edge(g, 0, 6);
    insert_edge(g, 5, 0);
    insert_edge(g, 0, 5);
    insert_edge(g, 4, 0);
    insert_edge(g, 0, 4);
    insert_edge(g, 2, 0);
    insert_edge(g, 0, 2);

    int menu, start_vertex, end_vertex;

    // 메뉴 출력
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    printf("|1\t: 깊이 우선 탐색\t|\n");
    printf("|2\t: 너비 우선 탐색\t|\n");
    printf("|3\t: 종료\t\t\t|\n");
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");

    while (1) {
        printf("메뉴 입력: ");
        scanf_s("%d", &menu); // 메뉴 입력

        if (menu == 1) { // 깊이 우선 탐색 선택
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d", &start_vertex); // 시작 정점 입력
            scanf_s("%d", &end_vertex); // 목표 정점 입력
            dfs_iterative(g, start_vertex, end_vertex);
            printf("\n");// DFS 호출
        }
        else if (menu == 2) { // 너비 우선 탐색 선택
            printf("시작 번호화 탐색할 값 입력: ");
            scanf_s("%d", &start_vertex); // 시작 정점 입력
            scanf_s("%d", &end_vertex); // 목표 정점 입력
            bfs(g, start_vertex, end_vertex);// BFS 호출
            printf("\n");
        }
        else if (menu == 3) { // 종료 선택
            free_graph(g); // 그래프 메모리 해제
            break; // 반복 종료
        }
        else {
            printf("유효하지 않은 메뉴 선택입니다.\n"); // 유효하지 않은 선택 메시지
        }
    }

    return 0; // 프로그램 종료
}
