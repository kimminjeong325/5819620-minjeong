#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ARRAY_SIZE 100  // �迭 ũ�� ����

// �迭 ��� �Լ�
void print_list(int list[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%02d ", list[i]);  // �� �ڸ� �������� ���
    }
    printf("\n");
}

// Shell Sort���� gap�� ����� ���� ���� ���� �Լ�
void gap_insertion_sort(int list[], int first, int last, int gap, int* comparisonCount, int* moveCount) {
    int i, j, key;

    for (i = first + gap; i <= last; i += gap) {
        key = list[i];
        (*moveCount)++;  // key ���� ������ �̵� ī��Ʈ
        for (j = i - gap; j >= first; j -= gap) {
            (*comparisonCount)++;  // �� ī��Ʈ ����
            if (list[j] > key) {
                list[j + gap] = list[j];  // �� �̵�
                (*moveCount)++;
            }
            else {
                break;  // key���� ������ ����
            }
        }
        list[j + gap] = key;  // key ����
        (*moveCount)++;
    }
}

// �迭�� ���� ���� ����
void generateRandomNumbers(int list[], int n) {
    for (int i = 0; i < n; i++) {
        list[i] = rand() % 1000;  // 0 ~ 999 ������ ���� ���� ����
    }
}

// Shell Sort ���� �� ��� ���
void doShellSort(const int list[], int num, int n, int* avgComparisonCount, int* avgMoveCount) {
    int tempArray[ARRAY_SIZE];  // �ӽ� �迭
    int totalComparisonCount = 0, totalMoveCount = 0;

    // �ʱ� �迭 ����
    for (int i = 0; i < n; i++) {
        tempArray[i] = list[i];
    }

    // Shell Sort ����
    for (int gap = n / num; gap > 0; gap /= num) {
        int comparisonCount = 0, moveCount = 0;

        for (int i = 0; i < gap; i++) {
            // gap ũ�⸶�� ���� ���� ����
            gap_insertion_sort(tempArray, i, n - 1, gap, &comparisonCount, &moveCount);
        }

        // �� gap �ܰ� ��� ��� (�ִ� 20���� ���)
        printf("Sorting with gap = %d:\n", gap);
        for (int i = 0; i < 20 && i < n; i++) {
            printf("%03d ", tempArray[i]);
        }
        if (n > 20) printf("...\n\n");
        else printf("\n\n");
    }

    // ���� ���ĵ� �迭 ���
    printf("Sorted shellArray (gap = %d):\n", num);
    print_list(tempArray, n);
    printf("\n");

    // ��� �� �� �̵� Ƚ�� ��� (20�� �ݺ�)
    for (int repeat = 0; repeat < 20; repeat++) {
        for (int i = 0; i < n; i++) {
            tempArray[i] = list[i];  // ���� �� �ʱ�ȭ
        }

        int comparisonCount = 0, moveCount = 0;

        for (int gap = n / num; gap > 0; gap /= num) {
            for (int j = 0; j < gap; j++) {
                gap_insertion_sort(tempArray, j, n - 1, gap, &comparisonCount, &moveCount);
            }
        }

        totalComparisonCount += comparisonCount;  // �� Ƚ�� ����
        totalMoveCount += moveCount;  // �̵� Ƚ�� ����
    }

    *avgComparisonCount = totalComparisonCount / 20;  // ��� �� Ƚ��
    *avgMoveCount = totalMoveCount / 20;  // ��� �̵� Ƚ��
}

// ���� ���� ���� �� ��� ���
void doInsertionSort(const int list[], int* avgComparisonCount, int* avgMoveCount) {
    int tempArray[ARRAY_SIZE];
    int totalComparisonCount = 0, totalMoveCount = 0;

    // 20�� �ݺ��Ͽ� ��� ���
    for (int repeat = 0; repeat < 20; repeat++) {
        int randomArray[ARRAY_SIZE];
        generateRandomNumbers(randomArray, ARRAY_SIZE);  // ���ο� ���� �迭 ����

        for (int i = 0; i < ARRAY_SIZE; i++) {
            tempArray[i] = randomArray[i];  // ���� �迭 ����
        }

        int comparisonCount = 0, moveCount = 0;

        // ���� ���� ����
        for (int i = 1; i < ARRAY_SIZE; i++) {
            int key = tempArray[i];
            moveCount++;
            int j = i - 1;

            while (j >= 0 && tempArray[j] > key) {
                comparisonCount++;
                tempArray[j + 1] = tempArray[j];
                moveCount++;
                j--;
            }
            if (j >= 0) comparisonCount++;
            tempArray[j + 1] = key;
            moveCount++;
        }

        totalComparisonCount += comparisonCount;  // �� Ƚ�� ����
        totalMoveCount += moveCount;  // �̵� Ƚ�� ����

        // ������ �ݺ����� ���ĵ� �迭 ���
        if (repeat == 19) {
            printf("Sorted Insertion Sort Array:\n");
            print_list(tempArray, ARRAY_SIZE);
        }
    }

    *avgComparisonCount = totalComparisonCount / 20;  // ��� �� Ƚ��
    *avgMoveCount = totalMoveCount / 20;  // ��� �̵� Ƚ��
    printf("\n");
}

// ���α׷� ����
int main() {
    srand(time(NULL));  // ���� �õ� �ʱ�ȭ

    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    generateRandomNumbers(array, ARRAY_SIZE);  // ���� �迭 ����

    // Shell Sort (gap = n/2)
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, ARRAY_SIZE, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Shell Sort (gap = n/3)
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, ARRAY_SIZE, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Insertion Sort
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}

