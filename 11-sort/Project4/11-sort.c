#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

void print_list(int list[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n");
}

// ���� ���� �Լ� - ���� ���� �� 10��°���� 20��° ��������, �׸��� ������ �ܰ迡�� �߰� ��� ���
void selection_sort(int list[], int n)
{
    int i, j, least, temp;
    for (i = 0; i < n - 1; i++)
    {
        least = i;
        for (j = i + 1; j < n; j++)
            if (list[j] < list[least])
                least = j;
        SWAP(list[i], list[least], temp);

        // ���� ���� ��� ����: 10��°���� �����ؼ� 20������ ���, ������ �ܰ� ���
        if ((i + 1) >= 10 && (i + 1 - 10) % 20 == 0 || i == n - 2) {
            printf("Step %d: ", i + 1);
            print_list(list, n);
            printf("\n");
        }
    }
}

// ���� ���� �Լ� - �� Ƚ�� ������ ���� count ������ ���
void insertion_sort(int list[], int n, int* count)
{
    int i = 0, j, key;
    *count = 0; // �� Ƚ���� �����ϱ� ���� �Ź� �ʱ�ȭ
    for (i = 1; i < n; i++)
    {
        key = list[i];
        for (j = i - 1; j >= 0; j--)
        {
            (*count)++; // �� Ƚ�� ����
            if (list[j] > key) list[j + 1] = list[j];
            else break;
        }
        list[j + 1] = key;
    }
}

// ���� ���� �Լ� - �̵� Ƚ�� ������ ���� move_count ������ ���
void bubble_sort(int list[], int n, int* move_count)
{
    int i, j, temp;
    int flag;
    *move_count = 0; // �̵� Ƚ���� �����ϱ� ���� �Ź� �ʱ�ȭ

    for (i = n - 1; i > 0; i--)
    {
        flag = 0;
        for (j = 0; j < i; j++)
        {
            if (list[j] > list[j + 1])
            {
                SWAP(list[j], list[j + 1], temp);
                *move_count += 3; // �� swap���� ���� �̵��� 3ȸ�� ����
                flag = 1;
            }
        }
        if (flag == 0) break; // �� �̻� ��ȯ�� ������ ���� ����
    }
}

// ���� �����͸� �����ϴ� �Լ� - 0���� 999������ ���� ����Ʈ�� ä��
void generateRandomData(int list[], int n)
{
    for (int i = 0; i < n; i++)
    {
        list[i] = rand() % 1000; // 0���� 999 ������ ���� �� ����
    }
}

// ���� ���� ���� �� ��� ��� �Լ�
void doSelectionSort(int list[], int n)
{
    int copiedList[SIZE];
    for (int i = 0; i < n; i++)
    {
        copiedList[i] = list[i]; // ���� ����Ʈ�� �����Ͽ� ���
    }
    printf("\nSelection Sort:\n");
    selection_sort(copiedList, n); // ���� ���� ����
}

// ���� ���� 20ȸ �ݺ� �� ��� �� Ƚ���� ���� ���� ���� ��� ��� �Լ�
void doInsertionSort(int list[], int n)
{
    int copiedList[SIZE];
    int count, total_count = 0;

    // ���� ���� 20ȸ �ݺ� �� ��� �� Ƚ�� ��� (�߰� ��� ��� ����)
    for (int i = 0; i < 20; i++)
    {
        generateRandomData(copiedList, n); // ���ο� ���� �����͸� �����Ͽ� ���� ���� ����
        insertion_sort(copiedList, n, &count);
        total_count += count; // �� ȸ���� �� Ƚ���� ����
    }
    printf("Insertion Sort Compare Average: %d\n", total_count / 20); // ��� �� Ƚ�� ���

    // ���� ���� ���� ���� �� ��� ���
    for (int i = 0; i < n; i++)
    {
        copiedList[i] = list[i]; // ���� ����Ʈ�� �����Ͽ� ���
    }
    insertion_sort(copiedList, n, &count); // ���� ���� ���� ����
    printf("Insertion Sort Result:\n");
    print_list(copiedList, n); // ���ĵ� ����Ʈ ���

    printf("\n");
}

// ���� ���� 20ȸ �ݺ� �� ��� �̵� Ƚ���� ���� ���� ���� ��� ��� �Լ�
void doBubbleSort(int list[], int n)
{
    int copiedList[SIZE];
    int move_count, total_move_count = 0;

    // ���� ���� 20ȸ �ݺ� �� ��� �̵� Ƚ�� ��� (�߰� ��� ��� ����)
    for (int i = 0; i < 20; i++)
    {
        generateRandomData(copiedList, n); // ���ο� ���� �����͸� �����Ͽ� ���� ���� ����
        bubble_sort(copiedList, n, &move_count);
        total_move_count += move_count; // �� ȸ���� �̵� Ƚ���� ����
    }
    printf("Bubble Sort Move Average: %d\n", total_move_count / 20); // ��� �̵� Ƚ�� ���

    // ���� ���� ���� ���� �� ��� ���
    for (int i = 0; i < n; i++)
    {
        copiedList[i] = list[i]; // ���� ����Ʈ�� �����Ͽ� ���
    }
    bubble_sort(copiedList, n, &move_count); // ���� ���� ���� ����
    printf("Bubble Sort Result:\n");
    print_list(copiedList, n); // ���ĵ� ����Ʈ ���
}

// ���� �Լ� - ���� ���� �õ� �ʱ�ȭ �� ���� �Լ� ȣ��
int main()
{
    srand(time(NULL)); // ���� ���� �õ� �ʱ�ȭ (���� �ð��� �������� ����)
    int randomData[SIZE];
    generateRandomData(randomData, SIZE); // ���� ������ ����

    doSelectionSort(randomData, SIZE); // ���� ���� ����
    doInsertionSort(randomData, SIZE); // ���� ���� ����
    doBubbleSort(randomData, SIZE); // ���� ���� ����

    return 0;
}
