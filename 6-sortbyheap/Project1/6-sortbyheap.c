#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//�� ������ ���� ��ȯ�ϱ� ���� �Լ�
// �� ������ �����ϰų� ���� �� ��� ���� ���� ��ȯ�ϴ� �� ����ϱ� ���� ����
void swap(int* a, int* b) {
    int temp = *a;//ù��° ������ ���� temp�� ���� 
    *a = *b;//�ι�° ������ ���� ù��° ������ ����
    *b = temp;//�ӽ� ������ ������ ù ��° ������ ���� �� ��° ������ ����
}

// Ư�� ��带 �������� �ִ� ���� �Ӽ��� �����ϱ� ���� ������ �Լ�
//�迭���� Ư�� ��尡 �� ������ �������� ���� ��, �ڽ� ����� ���Ͽ� ��ȯ�� ��
// ��������� �� ������ �����ϱ� ���� ����

void resortHeap(int arr[], int n, int i) {
    int largest = i;// ���� ��带 ���� ū ���̶�� ����
    int left = 2 * i + 1;// ���� �ڽ� ��� �ε���
    int right = 2 * i + 2;// ������ �ڽ� ��� �ε���
    // ���� �ڽ��� ���� ��庸�� ũ��, ���� �ڽ��� ���� ū ���� ����
    if (left < n && arr[left] > arr[largest])
        largest = left;
    // ������ �ڽ��� ���� ���� ū ��庸�� ũ��, ������ �ڽ��� ���� ū ���� ����
    if (right < n && arr[right] > arr[largest])
        largest = right;
    // ���� ���� ū ��尡 ����Ǿ��ٸ�, ��ȯ �� ��������� ���� ��带 ����
    if (largest != i) {
        swap(&arr[i], &arr[largest]);// �θ�� �ڽ� ��� ��ȯ
        resortHeap(arr, n, largest);// ��������� ���� ������
    }
}

//�־��� �迭�� �ִ� ������  ����� ���� �Լ� 
void BuildMaxHeap(int inputData[], int n) {
    // �迭�� ��� ��Ҹ� ��ȸ�ϸ� ���� ����
    for (int i = 0; i < n; i++) { 
        int j = i;
        // ���� ��尡 �θ� ��庸�� ũ��, �θ�� �ڽ��� ��ȯ�Ͽ� �� ������ ����
        while (j > 0 && inputData[(j - 1) / 2] < inputData[j]) {
            swap(&inputData[(j - 1) / 2], &inputData[j]);// �θ�� �ڽ� ��ȯ
            j = (j - 1) / 2; // �θ� ���� �̵��Ͽ� �ٽ� ��
        }

        // �� �ܰ迡���� �迭 ���¸� ���
        for (int k = 0; k <= i; k++) {
            printf("%d ", inputData[k]);
        }
        printf("\n");
    }
}
//�ִ� ���� ������ ��, �� ������ �����ϴ� �Լ�
void BuildMaxHeapAndSort(int inputData[], int n) {
    // �켱 �ִ� ���� ����
    BuildMaxHeap(inputData, n);
    // �� ������ ����
    for (int i = n - 1; i > 0; i--) {
        swap(&inputData[0], &inputData[i]);// ��Ʈ�� ������ ��� ��ȯ
        resortHeap(inputData, i, 0);// ���� �迭�� �ִ� ������ ������

        // ���� ���ĵ� ���¸� ���
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]); 
        }
        printf("\n");
    }
}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };//������ ������ �迭 
    int size = sizeof(inputData) / sizeof(inputData[0]);//�迭 ũ�� ��� 

    printf("<Sort>\n");
    // �� ���� �Լ� ȣ��
    BuildMaxHeapAndSort(inputData, size);
    // ���������� ���ĵ� �迭�� ���
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");
    return 0;
}
