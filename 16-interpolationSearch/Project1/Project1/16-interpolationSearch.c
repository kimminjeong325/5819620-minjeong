#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<windows.h>  // Windows���� Sleep �Լ� ����� ���� ��� ����

#define SIZE 1000  // �迭 ũ�� ����
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))  // �� �� ��ȯ ��ũ��

// �迭�� ó�� 20���� �� 20�� ���Ҹ� ����ϴ� �Լ�
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++)  // �迭�� ó�� 20�� ���� ���
        printf("%4d ", array[i]);
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++)  // �迭�� �� 20�� ���� ���
        printf("%4d ", array[i]);
    printf("\n\n");
}

// ������ �迭�� �����ϴ� �Լ�
void generateRandomArray(int list[]) {
    Sleep(100);  // ���� ���� ���� ��� ��� (�ùķ��̼�)

    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 10000;  // 0~9999 ������ ���� ������ �迭 ä���
    }
}

// �����Ŀ��� ����ϴ� ��Ƽ�� �Լ�
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high;
    pivot = list[left];  // �ǹ��� �迭�� ù ��° ��
    low = left;
    high = right + 1;

    do {
        // �ǹ����� ū ���� ã�� ������ low�� ����
        do
            low++;
        while (low <= right && list[low] < pivot);

        // �ǹ����� ���� ���� ã�� ������ high�� ����
        do
            high--;
        while (list[high] > pivot);

        // low�� high���� ������, �� ���� ��ȯ
        if (low < high) SWAP(list[low], list[high], temp);
    } while (low < high);  // low�� high���� ������ �ݺ�

    SWAP(list[left], list[high], temp);  // �ǹ��� ������ ��ġ�� �̵�
    return high;  // �ǹ��� ��ġ�� �ε����� ��ȯ
}

// ������ �Լ�
void QuickSort(int list[], int left, int right) {
    if (left < right) {
        int q = partition(list, left, right);  // ��Ƽ�� ����
        QuickSort(list, left, q - 1);  // ���� �κ��� ��������� ����
        QuickSort(list, q + 1, right);  // ������ �κ��� ��������� ����
    }
}

// ���� Ž�� �Լ� (�� Ƚ���� ����)
int search_binary2(int key, int low, int high, int list[], int* comparisonCount) {
    int middle;
    while (low <= high) {
        (*comparisonCount)++;  // low�� high ��: ������ ��ȿ���� ��
        middle = (low + high) / 2;  // �߰� �ε��� ���

        (*comparisonCount)++;  // �߰����� key ��
        if (key == list[middle]) {  // key�� �߰����� ��ġ�ϸ� ����
            return middle;
        }
        else if (key > list[middle]) {  // key�� �߰������� ũ�� ������ �κ� Ž��
            low = middle + 1;
        }
        else {  // key�� �߰������� ������ ���� �κ� Ž��
            high = middle - 1;
        }
    }
    return -1;  // key�� ã�� ���� ���
}

// ���� Ž���� ��� �� Ƚ�� ��� �Լ�
float getAverageBinarySearchCompareCount(int array[]) {
    int totalComparisons = 0;  // ��ü �� Ƚ�� �ʱ�ȭ
    for (int i = 0; i < SIZE; i++) {
        int target = array[rand() % SIZE];  // ������ Ÿ�� �� ����
        int comparisonCount = 0;  // �ش� Ž���� ���� �� Ƚ�� �ʱ�ȭ
        search_binary2(target, 0, SIZE - 1, array, &comparisonCount);  // ���� Ž�� ����
        totalComparisons += comparisonCount;  // �� Ƚ�� �ջ�
    }
    return (float)totalComparisons / SIZE;  // ��� �� Ƚ�� ��ȯ
}

// ���� Ž�� �Լ� (�� Ƚ���� ����)
int interpol_search(int key, int n, int list[], int* comparisonCount) {
    int low = 0, high = n - 1, j;

    while (low <= high && key >= list[low] && key <= list[high]) {  // ������ ��ȿ���� Ȯ��
        (*comparisonCount)++;  // low, high, key ��

        if (list[high] == list[low]) {  // low�� high�� �����ϸ� ������ ������
            if (list[low] == key) {  // key�� ��ġ�ϸ� ã�� ��
                (*comparisonCount)++;  // key == list[low] ��
                return low;
            }
            else {
                return -1;  // key�� ã�� ����
            }
        }

        // ���� �������� �߰� ��ġ ���
        j = low + ((double)(key - list[low]) / (list[high] - list[low])) * (high - low);

        if (j < low || j > high) {  // �߰� ��ġ�� ��ȿ���� ������ ����
            break;
        }

        if (key == list[j]) {  // key�� ��ġ�ϸ� ã�� ��
            return j;
        }
        else if (key < list[j]) {  // key�� �߰������� ������ ���� ���� Ž��
            high = j - 1;
        }
        else {  // key�� �߰������� ũ�� ������ ���� Ž��
            low = j + 1;
        }
    }

    return -1;  // key�� ã�� ����
}

// ���� Ž���� ��� �� Ƚ�� ��� �Լ�
float getAverageInterpolationSearchCompareCount(int array[]) {
    int totalComparisons = 0;  // ��ü �� Ƚ�� �ʱ�ȭ
    for (int i = 0; i < SIZE; i++) {
        int target = array[rand() % SIZE];  // ������ Ÿ�� �� ����
        int comparisonCount = 0;  // �ش� Ž���� ���� �� Ƚ�� �ʱ�ȭ
        interpol_search(target, SIZE, array, &comparisonCount);  // ���� Ž�� ����
        totalComparisons += comparisonCount;  // �� Ƚ�� �ջ�
    }
    return (float)totalComparisons / SIZE;  // ��� �� Ƚ�� ��ȯ
}

// ���� �Լ�
int main(int argc, char* argv[]) {
    srand(time(NULL));  // ���� �õ� �ʱ�ȭ

    int array[SIZE];  // �迭 ����

    // 3���� ���� ����
    for (int i = 1; i <= 3; i++) {
        generateRandomArray(array);  // ���� �迭 ����
        QuickSort(array, 0, SIZE - 1);  // �迭 ������ ����
        printArray(array);  // ���ĵ� �迭 ���

        // ���� Ž���� ��� �� Ƚ�� ���
        printf("Average Compare Count of Binary Search: %.2f\n",
            getAverageBinarySearchCompareCount(array));

        // ���� Ž���� ��� �� Ƚ�� ���
        printf("Average Compare Count of Interpolation Search: %.2f\n\n",
            getAverageInterpolationSearchCompareCount(array));

        Sleep(1000);  // 1�� ��� (���� ���� ��)
    }

    return 0;  // ���α׷� ����
}
