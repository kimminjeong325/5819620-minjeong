#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define SIZE 1000
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

int compareCount; // ���� ������ �� ���� �� Ƚ�� ����

// ���� Ž�� �Լ�: �迭���� Ű�� ã�� ������ ���ϸ� Ž��
int seq_search2(int key, int low, int high, int list[]) {
    int count = 0;
    for (int i = low; i <= high; i++) {
        count++; // �� Ƚ�� ����
        if (list[i] == key) return count; // Ű�� ã���� �� Ƚ�� ��ȯ
    }
    return count; // Ű�� ã�� ���� ��� �� Ƚ�� ��ȯ
}

// ���� Ž�� �Լ�: �迭���� Ű�� ã�� ������ �ݾ� ������ Ž��
int search_binary2(int key, int low, int high, int list[]) {
    int middle, count = 0;
    while (low <= high) {
        count++; // �� Ƚ�� ����
        middle = (low + high) / 2;
        if (key == list[middle]) return count; // Ű�� ã���� �� Ƚ�� ��ȯ
        else if (key > list[middle]) low = middle + 1; // Ű�� �߰� ������ ū ��� ������ �� Ž��
        else high = middle - 1; // Ű�� �߰� ������ ���� ��� ���� �� Ž��
    }
    return count; // Ű�� ã�� ���� ��� �� Ƚ�� ��ȯ
}

// �迭 ��� �Լ�: �迭�� �� 20���� �� 20�� ��Ҹ� ���
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) {
        printf("%3d ", array[i]); // �迭�� ó�� 20�� ��� ���
    }
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%3d ", array[i]); // �迭�� ������ 20�� ��� ���
    }
    printf("\n\n");
}

// ���� �迭 ���� �Լ�: �迭�� 0~999 ������ ������ ä��
void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000; // 0���� 999 ������ ���� ����
    }
}

// �� ���� ��Ƽ�� �Լ�: �ǹ��� �������� �迭�� ������ �� Ƚ���� ����
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;
    pivot = list[left]; // �ǹ� ����
    low = left;
    high = right + 1;

    do {
        do {
            low++;
            compareCount++; // ���� �� Ƚ�� ����
        } while (low <= right && list[low] < pivot);

        do {
            high--;
            compareCount++; // ���� �� Ƚ�� ����
        } while (high >= left && list[high] > pivot);

        if (low < high) {
            compareCount++; // ���� �� ������ ��
            SWAP(list[low], list[high], temp); // �� ��ȯ
        }
    } while (low < high);

    compareCount++; // �ǹ����� ������ ��
    SWAP(list[left], list[high], temp); // �ǹ� ��ġ ��ȯ
    return high; // �ǹ� ��ġ ��ȯ
}

// �� ���� �Լ�: ��������� �迭�� ����
void doQuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right); // ��Ƽ�� ����
        doQuickSort(list, left, q - 1); // ���� �κ� �迭 ����
        doQuickSort(list, q + 1, right); // ������ �κ� �迭 ����
    }
}

// ���� Ž�� ��� �� Ƚ�� ��� �Լ�
float getAverageLinearSearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; // �迭���� ���� Ű ����
        totalComparisons += seq_search2(target, 0, SIZE - 1, array); // Ž�� ���� �� �� Ƚ�� ����
    }
    return totalComparisons / 100.0; // ��� �� Ƚ�� ��ȯ
}

// �� ���� �� Ƚ�� ��� �Լ�
void getQuickSortCompareCount(int list[]) {
    compareCount = 0; // �� Ƚ�� �ʱ�ȭ
    doQuickSort(list, 0, SIZE - 1); // ���� ���� �� �� Ƚ�� ����
}

// ���� Ž�� ��� �� Ƚ�� ��� �Լ�
float getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;
    for (int i = 0; i < 100; i++) {
        int target = array[rand() % SIZE]; // �迭���� ���� Ű ����
        totalComparisons += search_binary2(target, 0, SIZE - 1, array); // Ž�� ���� �� �� Ƚ�� ����
    }
    return totalComparisons / 100.0; // ��� �� Ƚ�� ��ȯ
}

// ���� �Լ�: ���α׷� ������ ������
int main(int argc, char* argv[]) {
    srand(time(NULL)); // ���� ������ �ʱ�ȭ
    int array[SIZE];

    for (int i = 1; i <= 3; i++) {
        generateRandomArray(array);  // ���� �迭 ����

        // ���� Ž�� ��� �� Ƚ�� ���
        printf("Average Linear Search Compare Count: %.2f\n",
            getAverageLinearSearchCompareCount(array));

        // �� ���� �� Ƚ�� ���
        getQuickSortCompareCount(array);
        printf("Quick Sort Compare Count: %d\n", compareCount);

        // ���ĵ� �迭�� ���� ���� Ž�� 100ȸ ��� �� Ƚ�� ���
        printf("Average Binary Search Compare Count: %.2f\n\n",
            getAverageBinarySearchCompareCount(array));

        // �迭 ���
        printArray(array);

        Sleep(1000); // 1�� ���
    }
    return 0; // ���α׷� ����
}
