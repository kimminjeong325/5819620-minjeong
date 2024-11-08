#include <stdio.h>
#define INF 9999 // ������ ���� ��츦 ��Ÿ���� ���� ū ��
#define MAX_VERTICES 10 // �׷����� �ִ� ���� ��

// �׷����� ��Ÿ���� ����ü ����
typedef struct {
    int n; // ������ ����
    int weight[MAX_VERTICES][MAX_VERTICES]; // ����ġ ���� ���
} GraphType;

// ���ͽ�Ʈ�� �˰����� ����Ͽ� �ִ� ��θ� ã�� �Լ�
void shortest_path(GraphType* g, int start) {
    int distance[MAX_VERTICES]; // ���� �������κ����� �Ÿ� �迭
    int found[MAX_VERTICES];    // �ش� ������ �ִ� �Ÿ��� ã�Ҵ��� ���θ� �����ϴ� �迭
    int found_order[MAX_VERTICES]; // �湮�� ������ ����ϴ� �迭
    int found_count = 0;        // �湮�� ������ ������ ���� ���� ����
    int step = 0;               // �ܰ踦 ǥ���ϱ� ���� ����

    start = start - 1; // ��� ��ȣ�� 1���� �����ϵ��� ���߱� ���� ���������� 0-based�� ��ȯ

    // �ʱ�ȭ: ���� �������� �ٸ� ���������� �Ÿ� ����
    for (int i = 0; i < g->n; i++) {
        distance[i] = g->weight[start][i]; // �ʱ� �Ÿ��� ���� ��Ŀ��� ������
        found[i] = 0;                      // ��� ������ ���� �湮���� ���� ���·� �ʱ�ȭ
    }
    found[start] = 1; // ���� ������ �湮 �Ϸ� ǥ��
    distance[start] = 0; // ���� ���������� �Ÿ��� 0���� ����

    // �ʱ� distance�� found �迭 ���
    printf("Distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF) printf("* ");
        else printf("%d ", distance[i]);
    }
    printf("\nFound: ");
    for (int i = 0; i < g->n; i++) printf("%d ", found[i]);
    printf("\n\n");

    found_order[found_count++] = start + 1; // �湮 ������ ���� ���� �߰�

    // ���ͽ�Ʈ�� �˰����� �ֿ� ����
    for (int i = 0; i < g->n - 1; i++) {
        int min = INF;
        int u = -1;

        // �湮���� ���� ���� �� �ִ� �Ÿ��� ���� ������ ã��
        for (int j = 0; j < g->n; j++) {
            if (!found[j] && distance[j] < min) { // �湮���� ���� ���� �߿���
                min = distance[j];
                u = j;
            }
        }

        if (u == -1) break; // �� �̻� �湮�� ������ ������ ���� ����

        found[u] = 1; // �ִ� �Ÿ� ������ �湮 ǥ��
        found_order[found_count++] = u + 1; // �湮�� ������ �湮 ������ �߰�

        // ������ ������ �������� ������ �������� �ִ� �Ÿ� ����
        for (int w = 0; w < g->n; w++) {
            if (!found[w] && g->weight[u][w] != INF) { // ����� ������ ����
                if (distance[u] + g->weight[u][w] < distance[w]) { // �Ÿ� ���� ����
                    distance[w] = distance[u] + g->weight[u][w];
                }
            }
        }

        // �� �ܰ躰 distance�� found �迭 ���
        printf("Distance: ");
        for (int k = 0; k < g->n; k++) {
            if (distance[k] == INF) printf(" * ");
            else printf("%d ", distance[k]);
        }
        printf("\nFound: ");
        for (int k = 0; k < g->n; k++) printf("%d ", found[k]);
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
    // �׷��� �ʱ�ȭ: ����ġ ���� ��ķ� �׷����� ���� ���¸� ����
    GraphType g = { 10, // ������ ����
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

    int start_vertex = 1; // ���� ���� (1�� ������ �����ϵ��� ����)
    shortest_path(&g, start_vertex); // ���ͽ�Ʈ�� �˰��� ����

    return 0;
}
