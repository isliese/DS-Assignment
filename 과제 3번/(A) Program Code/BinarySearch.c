// �ΰ����ɰ��к� 2312038 ������
// [3] ���� ����Ʈ ���� �˻� (A) Program Code - BinarySearch.c - ���� Ž��
// 2024.06.01

//  31���� ���� �Է����� �޾�, �̸� ���� ����(selection sort)�� ���� �� �� ���� Ž��(binary search)�Ͻÿ�.


#include <stdio.h>
#include <stdlib.h>

typedef struct list_node* list_pointer; // list_pointer Ÿ�� ����

typedef struct list_node { // list_node struct ����
    int data;
    list_pointer link;
} list_node;

// �� ���� ����Ʈ�� �����ϴ� �Լ�
list_pointer create() {
    return NULL;
}

// �־��� ��� �ڿ� ��带 �����ϴ� �Լ�
void insert(list_pointer* head, int data) {
    list_pointer node = (list_pointer)malloc(sizeof(list_node)); // ���ο� ��� ����
    if (node == NULL) {
        printf("�޸� �Ҵ� ����\n");
        return;
    }
    node->data = data;
    node->link = NULL;

    if (*head == NULL) {
        *head = node; // ����Ʈ�� ����ִٸ� ���ο� ���� head�� ����
    }
    else {
        list_pointer current = *head;
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = node; // ����Ʈ�� �� ���� ���� �����ϴ� ��带 ����
    }
}

// ���� ����Ʈ�� ����ϴ� �Լ�
void printList(list_pointer head) {
    list_pointer current = head;
    while (current != NULL) { // ���� ��尡 NULL�� �ƴ� ������ ��� ����
        printf("%d ", current->data);
        current = current->link; // ���� ���� �̵��ϱ�
    }
    printf("\n");
}

// ���� ���� �Լ�
void selectionSort(list_pointer head) {
    list_pointer current = head;
    while (current != NULL) { // ��带 ��ȸ�ϸ� �ּڰ��� ã��
        list_pointer min = current;
        list_pointer temp = current->link;
        while (temp != NULL) { 
            if (temp->data < min->data) {
                min = temp;
            }
            temp = temp->link;
        }
        // ���� ���� �ּڰ��� ������ ����� ������ ��ȯ
        int tempData = current->data;
        current->data = min->data;
        min->data = tempData;
        current = current->link; // current �����͸� ���� ���� �̵�
    }
}

// ���� ����Ʈ�� ũ�⸦ ��ȯ�ϴ� �Լ�
int listSize(list_pointer head) {
    int count = 0; // ũ�� ���� �� �ʱ�ȭ
    list_pointer current = head;
    while (current != NULL) {
        count++; // ũ�� �ø���
        current = current->link;
    }
    return count;
}

// ���� Ž�� �Լ� (����Ʈ ���� ���ڰ� �ִ� ��� �ش� ����� ��ġ�� ��ȯ, ������ -1 ��ȯ)
int do_BinarySearch(list_pointer head, int key) {
    // left�� right�� �� ������ ����
    int left = 0; 
    int right = listSize(head) - 1;

    while (left <= right) { 
        int mid = left + (right - left) / 2;

        list_pointer current = head;
        for (int i = 0; i < mid; i++) {
            current = current->link;
        }

        if (current->data == key) // ���� Ű�� ã�� �Ǹ� 
            return mid; // mid ��ȯ
        else if (current->data < key)
            left = mid + 1; // left�� mid + 1�� ����
        else
            right = mid - 1; // left�� mid - 1�� ����
    }
    return -1;
}

int main() {
    // key�� �־��� 31���� ��
    int numarr[] = { 66, 2, 67, 69, 8, 11, 43, 49, 5, 6, 70, 71, 73, 75, 48, 12, 14, 7, 15, 24, 26, 42, 51, 55, 56, 59, 1, 3, 80, 96, 99 };
    int size = sizeof(numarr) / sizeof(numarr[0]);

    // �����ϱ� ���� ����Ʈ ����ϱ�
    printf("���� ����Ʈ: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numarr[i]);
    }
    printf("\n");

    // �־��� �迭�� ���� ����Ʈ�� ��ȯ
    list_pointer head = create();
    for (int i = 0; i < size; i++) { // numarr�� ��ҵ��� head�� �����ϱ�
        insert(&head, numarr[i]);
    }

    // ���� ������ ����Ͽ� ����Ʈ�� ����
    selectionSort(head);

    // ���� �� ����Ʈ ���
    printf("���ĵ� ����Ʈ: ");
    printList(head);
    printf("\n\n");

    // 10������ �˻� ���� ����
    int search_items[10] = { 3, 97, 96, 111, 15, 9, 66, 120, 99, 59 }; // 10���� �˻� ������
    for (int i = 0; i < 10; i++) { // �˻��� item ����Ʈ�� ����
        int result = do_BinarySearch(head, search_items[i]);
        printf("[\'%d\'�� ���� �˻� ���� ����]\n", search_items[i]); // � ���ڿ� ���� �˻� �������� ���

        if (result == -1) { // �˻� ������ list�� ���� ���
            printf("False\n");
            printf("No Result in List\n\n");
        }
        else { // �˻� ������ list�� ���� ���
            printf("True\n");
            printf("%d�� %d��°�� �����մϴ�.\n\n", search_items[i], result + 1); // � ���ڰ� �� ��°�� �ִ� �� ���
        }
    }

    return 0;
}
