#include <stdio.h>
#define INF 9999 // 연결이 없는 경우를 나타내기 위한 큰 수
#define MAX_VERTICES 10 // 그래프의 최대 정점 수

// 그래프를 나타내는 구조체 정의
typedef struct {
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES]; // 가중치 인접 행렬
} GraphType;

// 다익스트라 알고리즘을 사용하여 최단 경로를 찾는 함수
void shortest_path(GraphType* g, int start) {
    int distance[MAX_VERTICES]; // 시작 정점으로부터의 거리 배열
    int found[MAX_VERTICES];    // 해당 정점의 최단 거리를 찾았는지 여부를 저장하는 배열
    int found_order[MAX_VERTICES]; // 방문한 순서를 기록하는 배열
    int found_count = 0;        // 방문한 정점의 개수를 세기 위한 변수
    int step = 0;               // 단계를 표시하기 위한 변수

    // 초기화: 시작 정점에서 다른 정점으로의 거리 설정
    for (int i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i]; // 초기 거리를 인접 행렬에서 가져옴
        found[i] = 0;                      // 모든 정점을 아직 방문하지 않은 상태로 초기화
    }
    found[start] = 1; // 시작 정점은 방문 완료 표시
    distance[start] = 0; // 시작 정점까지의 거리는 0으로 설정

    // 초기 distance와 found 배열 출력
    printf("Distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF) printf("* ");
        else printf("%d ", distance[i]);
    }
    printf("\nFound: ");
    for (int i = 0; i < g->n; i++) printf("%d ", found[i]);
    printf("\n\n");

    found_order[found_count++] = start + 1; // 방문 순서에 시작 정점 추가

    // 다익스트라 알고리즘의 주요 루프
    for (int i = 0; i < g->n - 1; i++) {
        int min = INF;
        int u = -1;

        // 방문하지 않은 정점 중 최단 거리를 가진 정점을 찾음
        for (int j = 0; j < g->n; j++) {
            if (!found[j] && distance[j] < min) { // 방문하지 않은 정점 중에서
                min = distance[j];
                u = j;
            }
        }

        if (u == -1) break; // 더 이상 방문할 정점이 없으면 루프 종료

        found[u] = 1; // 최단 거리 정점을 방문 표시
        found_order[found_count++] = u + 1; // 방문한 정점을 방문 순서에 추가

        // 선택한 정점을 기준으로 인접한 정점들의 최단 거리 갱신
        for (int w = 0; w < g->n; w++) {
            if (!found[w] && g->weight[u][w] != INF) { // 연결된 정점에 대해
                if (distance[u] + g->weight[u][w] < distance[w]) { // 거리 갱신 조건
                    distance[w] = distance[u] + g->weight[u][w];
                }
            }
        }

        // 각 단계별 distance와 found 배열 출력
        printf("Distance: ");
        for (int k = 0; k < g->n; k++) {
            if (distance[k] == INF) printf(" * ");
            else printf("%d ", distance[k]);
        }
        printf("\nFound: ");
        for (int k = 0; k < g->n; k++) printf("%d ", found[k]);
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
    // 그래프 초기화: 가중치 인접 행렬로 그래프의 연결 상태를 정의
    GraphType g = { 10, // 정점의 개수
       { { 0, 3, INF, INF, INF, 11, 12, INF, INF, INF }, 
         { 3, 0, 8, 4, 1, 7, 8, INF, INF, INF },        
         { INF, 8, 0, 2, INF, INF, 6, 5, INF, INF },     
         { INF, 4, 2, 0, 13, INF, INF, 14, INF, 16 },    
         { INF, 1, INF, 13, 0, 9, INF, INF, 18, 17 },    
         { 11, 7, INF, INF, 9, 0, INF, INF, INF, INF }, 
         { 12, 8, 6, INF, INF, INF, 0, 13, INF, INF },   
         { INF, INF, 5, 14, INF, INF, 13, 0, INF, 15 },  
         { INF, INF, INF, INF, 18, INF, INF, INF, 0, 10 }, 
         { INF, INF, INF, 16, 17, INF, INF, 15, 10, 0 } }  
    };

    int start_vertex = 0; // 시작 정점 (0번 노드, 즉 1번 노드)
    shortest_path(&g, start_vertex); // 다익스트라 알고리즘 실행

    return 0;
}
