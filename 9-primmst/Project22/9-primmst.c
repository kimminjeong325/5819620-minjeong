#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L  // 무한대 값을 정의하여 연결이 없는 간선을 나타냄

// 그래프 구조체 정의
typedef struct GraphType {
    int n;  // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];  // 가중치 행렬
} GraphType;

// 선택된 정점을 추적하는 배열
int selected[MAX_VERTICES];
// 각 정점까지의 최소 거리 값을 저장하는 배열
int distance[MAX_VERTICES];

// 그래프 초기화 함수
void graph_init(GraphType* g) {
    // 정점 수에 따라 선택 배열과 거리 배열 초기화
    for (int i = 1; i <= g->n; i++) {
        selected[i] = FALSE;  // 모든 정점을 선택되지 않음으로 초기화
        distance[i] = INF;     // 모든 정점까지의 거리를 무한대로 초기화
    }
}

// 최소 거리 정점을 찾는 함수
int get_min_vertex(int n) {
    int v = -1;  // 초기화
    // 선택되지 않은 정점 중 첫 번째 정점을 찾음
    for (int i = 1; i <= n; i++) {
        if (!selected[i]) {
            v = i;
            break;  // 첫 번째 선택되지 않은 정점으로 초기화
        }
    }
    // 최소 거리 값을 가진 정점을 찾음
    for (int i = 1; i <= n; i++) {
        if (!selected[i] && (v == -1 || distance[i] < distance[v])) {
            v = i;  // 최소 거리 값을 가진 정점 찾기
        }
    }
    return v;  // 최소 정점 반환
}

// Prim 알고리즘을 사용하여 최소 신장 트리를 찾는 함수
void FindPrimMST(GraphType* g) {
    int u, v;

    // 모든 정점까지의 거리 배열 초기화
    for (u = 1; u <= g->n; u++)
        distance[u] = INF;  // 거리 초기화

    distance[1] = 0;  // 시작 정점 1로 설정

    printf("Prim MST Algorithm\n");

    // n번의 반복을 통해 최소 신장 트리 구성
    for (int i = 1; i <= g->n; i++) {
        u = get_min_vertex(g->n);  // 최소 정점 찾기
        selected[u] = TRUE;  // 선택된 정점으로 표시
        if (distance[u] == INF) return;  // 연결된 정점이 없으면 종료
        printf("정점 %d 추가\n", u);  // 선택된 정점 출력

        // 선택된 정점과 연결된 모든 정점에 대해 거리 업데이트
        for (v = 1; v <= g->n; v++) {
            if (g->weight[u][v] != INF) {  // 연결된 정점인지 확인
                if (!selected[v] && g->weight[u][v] < distance[v]) {
                    distance[v] = g->weight[u][v];  // 거리 업데이트
                }
            }
        }
    }
}

// 그래프를 생성하고 가중치를 설정하는 함수
void GenerateGraph(GraphType* g) {
    g->n = 10;  // 정점의 개수 설정

    // 가중치 행렬 초기화
    for (int i = 1; i <= g->n; i++)
        for (int j = 1; j <= g->n; j++)
            g->weight[i][j] = INF;  // 기본적으로 모든 간선을 무한대로 초기화

    // 가중치를 삽입 (간선의 가중치 설정)
    g->weight[1][2] = 3;   
    g->weight[1][6] = 11;  
    g->weight[1][7] = 12;  
    g->weight[2][3] = 5;   
    g->weight[2][4] = 4;   
    g->weight[2][5] = 1;   
    g->weight[2][6] = 7;   
    g->weight[2][7] = 8;   
    g->weight[3][4] = 2;   
    g->weight[3][7] = 6;   
    g->weight[3][8] = 5;   
    g->weight[4][5] = 13;  
    g->weight[4][8] = 14;  
    g->weight[4][10] = 16;
    g->weight[5][6] = 9;   
    g->weight[5][9] = 18;  
    g->weight[5][10] = 17; 
    g->weight[7][8] = 13;  
    g->weight[8][10] = 15; 
    g->weight[9][10] = 10; 

    // 양방향 간선으로 설정
    for (int i = 1; i <= g->n; i++)
        for (int j = 1; j <= g->n; j++)
            if (g->weight[i][j] != INF)
                g->weight[j][i] = g->weight[i][j];  // 대칭 관계 설정
}

// 프로그램의 진입점
int main(void) {
    GraphType* g;  // 그래프 구조체 포인터 선언
    g = (GraphType*)malloc(sizeof(GraphType));  // 그래프 구조체 동적 할당
    graph_init(g);  // 그래프 초기화

    GenerateGraph(g); // 그래프 생성 

    FindPrimMST(g);  // 최소 신장 트리 찾기

    free(g);  // 동적으로 할당한 메모리 해제
    return 0;  // 프로그램 종료
}
