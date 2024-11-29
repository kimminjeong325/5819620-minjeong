#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

float totalComparisons = 0.0;
float totalMoveCount = 0.0;
int isFirst = 0;
int comparisonCount = 0;
int moveCount = 0;
int rounds = 0;

void printArray(int list[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
}

int partition(int list[], int left, int right) {
    int pivot, temp;
    int low = left, high = right + 1;

    pivot = list[left];

    do {
        // low �ε����� pivot���� ū ���� ã�� ������ �ݺ�
        do {
            low++;
            comparisonCount++;  // �� Ƚ�� ����
        } while (low <= right && list[low] < pivot);

        // high �ε����� pivot���� ���� ���� ã�� ������ �ݺ�
        do {
            high--;
            comparisonCount++;  // �� Ƚ�� ����
        } while (high >= left && list[high] > pivot);

        // low�� high�� �������� ������ �� ��ȯ
        if (low < high) {
            SWAP(list[low], list[high], temp);
            moveCount += 3;  // x�� y�� ��ȯ + temp ��� (3�� �̵�)
        }
    } while (low < high);  // low�� high�� �����ϱ� ������ �ݺ�

    // pivot�� ��Ȯ�� ��ġ�� ��ȯ
    SWAP(list[left], list[high], temp);
    moveCount += 3;  // x�� y�� ��ȯ + temp ��� (3�� �̵�)
    return high;
}

void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000;  // 0~999�� ���� ���� ����
    }
}

void doQuickSort(int* array, int left, int right) {
    int stack[SIZE];  // ������ �̿��� �ݺ��� ó��
    int top = -1;
    stack[++top] = left;  // ó�� ���� �ε����� ���ÿ� Ǫ��
    stack[++top] = right;  // ó�� ������ �ε����� ���ÿ� Ǫ��

    while (top >= 0) {
        right = stack[top--];  // ������ �ε��� ������
        left = stack[top--];   // ���� �ε��� ������

        if (left < right) {
            int q = partition(array, left, right);  // pivot�� �������� ����

            // ���ҵ� ���� �κ��� ���ÿ� Ǫ��
            stack[++top] = left;
            stack[++top] = q - 1;

            // ���ҵ� ������ �κ��� ���ÿ� Ǫ��
            stack[++top] = q + 1;
            stack[++top] = right;
        }

        // rounds���� �߰� ��� ��� (ù ��° ���࿡����)
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++)
                printf("%d ", array[i]);
            printf("\n\n");
        }
        rounds++;  // rounds ����
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);  // ���ο� ���� ������ ����
        comparisonCount = 0;  // �� Ƚ�� �ʱ�ȭ
        moveCount = 0;        // �̵� Ƚ�� �ʱ�ȭ

        if (i == 0) {
            printf("Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1);  // ù ��° ���� ����
            printf("Result\n");
            printArray(array, SIZE);  // ��� ���
            isFirst++;  // ù ��° ����� �Ϸ�Ǿ����Ƿ� isFirst ����
        }
        else {
            doQuickSort(array, 0, SIZE - 1);  // ���� ���� ����
        }

        // ��ü �� Ƚ���� �̵� Ƚ���� ���ϱ�
        totalComparisons += comparisonCount;  // ��ü �� Ƚ���� ���ϱ�
        totalMoveCount += moveCount;          // ��ü �̵� Ƚ���� ���ϱ�
    }

    // ��� �� Ƚ���� �̵� Ƚ�� ���
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}
