// �ΰ����ɰ��к� 2312038 ������
// [3] ���� ����Ʈ ���� �˻� (A) Program Code - SelectionSorting.c - ����
// 2024.06.01

//  31���� ���� �Է����� �޾�, �̸� ���� ����(selection sort)�� ���� �Ͻÿ�.
/*  (66, 2, 67, 69, 8, 11, 43, 49, 5, 6, 70, 71, 73, 75, 48, 12, 14, 7, 15, 24, 26, 42,
51, 55, 56, 59, 1, 3, 80, 96, 99) */

#include <stdio.h>
#include <stdlib.h> // malloc �Լ��� ���� include

typedef struct list_node* list_pointer;

typedef struct list_node {
    int data; // data �ʵ�
    list_pointer link; // ������
} list_node;

// �� ���� ����Ʈ�� �����ϴ� �Լ�
list_pointer create() {
    return NULL;
}

// �־��� ��� �ڿ� ��带 �����ϴ� �Լ�
void insert(list_pointer* head, int data) {
    list_pointer node = (list_pointer)malloc(sizeof(list_node));
    if (node == NULL) {
        printf("�޸� �Ҵ� ����\n");
        return;
    }
    node->data = data;
    node->link = NULL;

    if (*head == NULL) {
        *head = node; // ����Ʈ�� ����ִٸ� head�� ���ο� ���� ����
    }
    else { // ����Ʈ�� ������� ���� ���
        list_pointer current = *head; 
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = node; // ����Ʈ�� ���� ���ο� ��带 ����
    }
}


// ���� ����Ʈ�� ����ϴ� �Լ�
void printList(list_pointer head) {
    list_pointer current = head;
    while (current != NULL) { // ����Ʈ�� �� ��� ��ȸ
        printf("%d ", current->data); /// data ���
        current = current->link;
    }
    printf("\n");
}

// ���� ���� �Լ�
void selectionSort(list_pointer head) {
    list_pointer current = head;
    while (current != NULL) { // current�� null�� �ƴ� ������
        list_pointer min = current;
        list_pointer temp = current->link;
        while (temp != NULL) { // temp �����͸� ����Ͽ� �ּڰ� ã��
            if (temp->data < min->data) {
                min = temp;
            }
            temp = temp->link; 
        }
        // ���� ���� �ּڰ��� ������ ��� ��ȯ
        int tempData = current->data;
        current->data = min->data;
        min->data = tempData;
        current = current->link; // current �����͸� ���� ���� �̵�
    }
}

int main() {
    list_pointer head = create(); // �� ���Ḯ��Ʈ ����

    // ������ ���ڵ�
    int numarr[] = { 66, 2, 67, 69, 8, 11, 43, 49, 5, 6, 70, 71, 73, 75, 48, 12, 14, 7, 15, 24, 26, 42, 51, 55, 56, 59, 1, 3, 80, 96, 99 };

    // �迭 numarr[]�� ��Ҹ� ����Ʈ�� �����ϱ�
    for (int i = 0; i < sizeof(numarr) / sizeof(numarr[0]); i++) {
        insert(&head, numarr[i]);
    }

    // ���� �� ����Ʈ ���
    printf("���� ����Ʈ: ");
    printList(head);

    // ���� ������ ����Ͽ� ����Ʈ ����
    selectionSort(head);

    // ���� �� ����Ʈ ���
    printf("���ĵ� ����Ʈ: ");
    printList(head);

    return 0;
}