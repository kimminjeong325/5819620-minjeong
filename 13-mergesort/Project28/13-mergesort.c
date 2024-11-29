#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int sorted[SIZE];
int comparisonCount;
int moveCount;
float totalComparisons = 0.0;
float totalMoves = 0.0;
int isFirst = 0;
int rounds = 0;

void printArray(int* array, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

void merge(int list[], int left, int mid, int right) {
    int i, j, k, l;
    i = left; j = mid + 1; k = left;

    // ���� ���ĵ� list�� �պ�
    while (i <= mid && j <= right) {
        comparisonCount++;  // �� Ƚ�� ����

        if (list[i] <= list[j]) {
            moveCount++;
            sorted[k++] = list[i++];
        }
        else {
            sorted[k++] = list[j++];
        }
        moveCount++;
    }


    if (i > mid) {    // ���� �ִ� ���ڵ��� �ϰ� ����
        for (l = j; l <= right; l++) {
            sorted[k++] = list[l];
            moveCount++;  // �̵� Ƚ�� ����
        }
    }
    else {    // ���� �ִ� ���ڵ��� �ϰ� ����
        for (l = i; l <= mid; l++) {
            sorted[k++] = list[l];
            moveCount++;  // �̵� Ƚ�� ����
        }
    }

    // �迭 sorted[]�� ����Ʈ�� �迭 list[]�� ����
    for (l = left; l <= right; l++) {
        list[l] = sorted[l];
        moveCount++;  // �̵� Ƚ�� ���� (�迭�� list�� ������ ��)
    }

    rounds++; // ���� ���� ����

    if (rounds % 10 == 0 && isFirst == 0) { // 10���� �ѹ��� ���
        for (int i = 0; i < 10; i++) // ó�� 10�� ��� ���
            printf("%3d ", list[i]);
        printf("| ");
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) // �߾� ��ó�� 10�� ��� ���
            printf("%3d ", list[i]);
        printf("\n\n");
    }
}

void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;  // 0 ~ 999 ������ ���� ���� ����
    }
}

// �ݺ��� ������� �պ����� ����
void doMergeSort(int* array, int left, int right) {
    int size, i, leftStart, mid, rightEnd;

    // �ݺ������� ������ ũ��(1���� �����Ͽ� 2�辿 �þ)
    for (size = 1; size < SIZE; size = size * 2) {
        // ���� �۾�
        for (leftStart = 0; leftStart < SIZE; leftStart += 2 * size) {
            mid = leftStart + size - 1;
            rightEnd = (leftStart + 2 * size - 1) < SIZE ? leftStart + 2 * size - 1 : SIZE - 1;

            // mid�� �迭�� ���� ���� ���� ��� ����
            if (mid < SIZE) {
                merge(array, leftStart, mid, rightEnd);  // ���� �۾� ȣ��
            }
        }
    }
}

int main() {
    srand(time(NULL));

    int array[SIZE];

    // 20�� �ݺ�
    for (int i = 0; i < 20; i++) {
        // ���� �迭 ����
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        // ù ��° ���࿡���� Merge Sort Run ���
        if (i == 0) {
            printf("Merge Sort Run\n");
            doMergeSort(array, 0, SIZE - 1);

            // ù ��° ���� ��� ���
            printf("Result\n");
            printArray(array, SIZE);
            isFirst++; // ù ��° ���� �Ϸ�
        }
        else {
            // �� ���Ŀ��� �׳� ���� ���ĸ� ����
            doMergeSort(array, 0, SIZE - 1);
        }

        // �� Ƚ���� �̵� Ƚ���� ��ü �ջ�
        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    // ��� �� Ƚ���� ��� �̵� Ƚ�� ���
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
