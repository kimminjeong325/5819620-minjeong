#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50 // �ִ� ���� �� ����

// �׷��� ��� ����ü ����
typedef struct GraphNode {
    int vertex; // ���� ��ȣ
    struct GraphNode* link; // ���� ��带 ����Ű�� ������
} GraphNode;

// �׷��� ����ü ����
typedef struct GraphType {
    int n; // ���� ���� ��
    GraphNode* adj_list[MAX_VERTICES]; // ���� ����Ʈ
} GraphType;

int visited[MAX_VERTICES]; // �湮 ���� �迭
int visit_count; // �湮�� ��� ��

// �׷��� �ʱ�ȭ �Լ�
void init(GraphType* g) {
    g->n = 0; // ���� �� �ʱ�ȭ
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj_list[i] = NULL; // ���� ����Ʈ �ʱ�ȭ
    }
}

// ���� �߰� �Լ�
void insert_vertex(GraphType* g, int v) {
    if (((g->n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "�׷���: ������ ���� �ʰ�\n"); // ���� �� �ʰ� ���� �޽���
        return;
    }
    g->n++; // ���� �� ����
}

// ���� �߰� �Լ�
void insert_edge(GraphType* g, int u, int v) {
    GraphNode* node; // �� ��带 ���� ������
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "�׷���: ���� ��ȣ ����\n"); // ���� ��ȣ ���� �޽���
        return;
    }
    node = (GraphNode*)malloc(sizeof(GraphNode)); // �� ��� �޸� �Ҵ�
    node->vertex = v; // ���� ��ȣ ����
    node->link = g->adj_list[u]; // ���� ���� ��� ����
    g->adj_list[u] = node; // ���� ����Ʈ�� �� ��� �߰�
}

// �湮 �迭 �� �湮�� ��� �� �ʱ�ȭ �Լ�
void reset_visited() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = 0; // ��� ������ �湮���� �������� �ʱ�ȭ
    }
    visit_count = 0; // �湮�� ��� �� �ʱ�ȭ
}

// �ݺ��� ���� �켱 Ž�� �Լ�
void dfs_iterative(GraphType* g, int start, int end) {
    int stack[MAX_VERTICES], top = -1; // ���� �ʱ�ȭ
    reset_visited(); // �湮 �迭 �ʱ�ȭ

    stack[++top] = start; // ���� ���� ���ÿ� �߰�
    visited[start] = 1; // ���� ���� �湮 ó��
    visit_count++; // �湮�� ��� �� ����

    while (top >= 0) {
        int v = stack[top]; // ���ÿ��� ���� ��������
        printf("%d ", v); // �湮�� ��� ���

        if (v == end) {
            printf("\nŽ�� ����: %d\n", end); // ���� �޽��� ���
            printf("�湮�� ����� ��: %d\n", visit_count); // �湮�� ��� �� ���
            return; // Ž�� ���� �� ��ȯ
        }

        GraphNode* w = g->adj_list[v]; // ���� ��� Ž�� ����
        int pushed = 0; // ��带 ���ÿ� �־����� ���� Ȯ��

        while (w != NULL) {
            if (!visited[w->vertex]) {
                stack[++top] = w->vertex; // ���ÿ� �߰�
                visited[w->vertex] = 1; // ��� �湮 ó��
                visit_count++; // �湮�� ��� �� ����
                pushed = 1; // ���ο� ��带 ���ÿ� �߰������� ǥ��
                break; // ���ο� ��带 ���ÿ� �־����Ƿ� ���� Ż��
            }
            w = w->link; // ���� ���� ���� �̵�
        }

        if (!pushed) {
            // �� �̻� �湮�� ��尡 ������ ���ÿ��� pop (��Ʈ��ŷ)
            top--;
        }
    }
    printf("\nŽ�� ����: %d\n", end); // Ž�� ���� �޽���
}

// �ʺ� �켱 Ž�� �Լ�
void bfs(GraphType* g, int start, int end) {
    int queue[MAX_VERTICES], front = -1, rear = -1; // ť �ʱ�ȭ
    reset_visited(); // �湮 �迭 �ʱ�ȭ
    queue[++rear] = start; // ���� ���� ť�� �߰�
    visited[start] = 1; // ���� ���� �湮 ó��

    while (front < rear) {
        front++; // ť�� ���� ����
        int v = queue[front]; // ť���� ���� ��������
        printf("%d ", v); // �湮�� ��� ���

        if (v == end) {
            printf("\nŽ�� ����: %d\n", end); // ���� �޽��� ���
            printf("�湮�� ����� ��: %d\n", visit_count); // �湮�� ��� �� ���
            return; // Ž�� ���� �� ��ȯ
        }

        GraphNode* w = g->adj_list[v]; // ���� ��� Ž�� ����
        while (w != NULL) {
            if (!visited[w->vertex]) {
                visited[w->vertex] = 1; // ��� �湮 ó��
                visit_count++; // �湮�� ��� �� ����
                queue[++rear] = w->vertex; // ť�� �߰�
            }
            w = w->link; // ���� ���� ���� �̵�
        }
    }
    printf("\nŽ�� ����: %d\n", end); // Ž�� ���� �޽���
}

// �׷��� �޸� ���� �Լ�
void free_graph(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* current = g->adj_list[i]; // ���� ���
        while (current != NULL) {
            GraphNode* temp = current; // ���� ��� �ӽ� ����
            current = current->link; // ���� ���� �̵�
            free(temp); // �� ��� �޸� ����
        }
    }
    free(g); // �׷��� ����ü �޸� ����
}

int main() {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType)); // �׷��� �޸� �Ҵ�
    init(g); // �׷��� �ʱ�ȭ

    // ���� �߰�
    for (int i = 0; i < 11; i++)
        insert_vertex(g, i);

    // ���� �߰�
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

    // �޴� ���
    printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
    printf("|1\t: ���� �켱 Ž��\t|\n");
    printf("|2\t: �ʺ� �켱 Ž��\t|\n");
    printf("|3\t: ����\t\t\t|\n");
    printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");

    while (1) {
        printf("�޴� �Է�: ");
        scanf_s("%d", &menu); // �޴� �Է�

        if (menu == 1) { // ���� �켱 Ž�� ����
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d", &start_vertex); // ���� ���� �Է�
            scanf_s("%d", &end_vertex); // ��ǥ ���� �Է�
            dfs_iterative(g, start_vertex, end_vertex);
            printf("\n");// DFS ȣ��
        }
        else if (menu == 2) { // �ʺ� �켱 Ž�� ����
            printf("���� ��ȣȭ Ž���� �� �Է�: ");
            scanf_s("%d", &start_vertex); // ���� ���� �Է�
            scanf_s("%d", &end_vertex); // ��ǥ ���� �Է�
            bfs(g, start_vertex, end_vertex);// BFS ȣ��
            printf("\n");
        }
        else if (menu == 3) { // ���� ����
            free_graph(g); // �׷��� �޸� ����
            break; // �ݺ� ����
        }
        else {
            printf("��ȿ���� ���� �޴� �����Դϴ�.\n"); // ��ȿ���� ���� ���� �޽���
        }
    }

    return 0; // ���α׷� ����
}
