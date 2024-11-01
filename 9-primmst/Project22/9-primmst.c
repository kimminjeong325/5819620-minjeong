#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L  // ���Ѵ� ���� �����Ͽ� ������ ���� ������ ��Ÿ��

// �׷��� ����ü ����
typedef struct GraphType {
    int n;  // ������ ����
    int weight[MAX_VERTICES][MAX_VERTICES];  // ����ġ ���
} GraphType;

// ���õ� ������ �����ϴ� �迭
int selected[MAX_VERTICES];
// �� ���������� �ּ� �Ÿ� ���� �����ϴ� �迭
int distance[MAX_VERTICES];

// �׷��� �ʱ�ȭ �Լ�
void graph_init(GraphType* g) {
    // ���� ���� ���� ���� �迭�� �Ÿ� �迭 �ʱ�ȭ
    for (int i = 1; i <= g->n; i++) {
        selected[i] = FALSE;  // ��� ������ ���õ��� �������� �ʱ�ȭ
        distance[i] = INF;     // ��� ���������� �Ÿ��� ���Ѵ�� �ʱ�ȭ
    }
}

// �ּ� �Ÿ� ������ ã�� �Լ�
int get_min_vertex(int n) {
    int v = -1;  // �ʱ�ȭ
    // ���õ��� ���� ���� �� ù ��° ������ ã��
    for (int i = 1; i <= n; i++) {
        if (!selected[i]) {
            v = i;
            break;  // ù ��° ���õ��� ���� �������� �ʱ�ȭ
        }
    }
    // �ּ� �Ÿ� ���� ���� ������ ã��
    for (int i = 1; i <= n; i++) {
        if (!selected[i] && (v == -1 || distance[i] < distance[v])) {
            v = i;  // �ּ� �Ÿ� ���� ���� ���� ã��
        }
    }
    return v;  // �ּ� ���� ��ȯ
}

// Prim �˰����� ����Ͽ� �ּ� ���� Ʈ���� ã�� �Լ�
void FindPrimMST(GraphType* g) {
    int u, v;

    // ��� ���������� �Ÿ� �迭 �ʱ�ȭ
    for (u = 1; u <= g->n; u++)
        distance[u] = INF;  // �Ÿ� �ʱ�ȭ

    distance[1] = 0;  // ���� ���� 1�� ����

    printf("Prim MST Algorithm\n");

    // n���� �ݺ��� ���� �ּ� ���� Ʈ�� ����
    for (int i = 1; i <= g->n; i++) {
        u = get_min_vertex(g->n);  // �ּ� ���� ã��
        selected[u] = TRUE;  // ���õ� �������� ǥ��
        if (distance[u] == INF) return;  // ����� ������ ������ ����
        printf("���� %d �߰�\n", u);  // ���õ� ���� ���

        // ���õ� ������ ����� ��� ������ ���� �Ÿ� ������Ʈ
        for (v = 1; v <= g->n; v++) {
            if (g->weight[u][v] != INF) {  // ����� �������� Ȯ��
                if (!selected[v] && g->weight[u][v] < distance[v]) {
                    distance[v] = g->weight[u][v];  // �Ÿ� ������Ʈ
                }
            }
        }
    }
}

// �׷����� �����ϰ� ����ġ�� �����ϴ� �Լ�
void GenerateGraph(GraphType* g) {
    g->n = 10;  // ������ ���� ����

    // ����ġ ��� �ʱ�ȭ
    for (int i = 1; i <= g->n; i++)
        for (int j = 1; j <= g->n; j++)
            g->weight[i][j] = INF;  // �⺻������ ��� ������ ���Ѵ�� �ʱ�ȭ

    // ����ġ�� ���� (������ ����ġ ����)
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

    // ����� �������� ����
    for (int i = 1; i <= g->n; i++)
        for (int j = 1; j <= g->n; j++)
            if (g->weight[i][j] != INF)
                g->weight[j][i] = g->weight[i][j];  // ��Ī ���� ����
}

// ���α׷��� ������
int main(void) {
    GraphType* g;  // �׷��� ����ü ������ ����
    g = (GraphType*)malloc(sizeof(GraphType));  // �׷��� ����ü ���� �Ҵ�
    graph_init(g);  // �׷��� �ʱ�ȭ

    GenerateGraph(g); // �׷��� ���� 

    FindPrimMST(g);  // �ּ� ���� Ʈ�� ã��

    free(g);  // �������� �Ҵ��� �޸� ����
    return 0;  // ���α׷� ����
}
