// �ΰ����ɰ��к� 2312038 ������
// [2] ���� ������ ���� (6��) - SecondGame.c - �� ��° ����
// 2024.06.01


// [2��° ����, 3��]
// "01-Kim", "02-Lee", "03-Choi", "04-Yoon", "05-Min", "06-Gwak", "07-Park", "08-Jung", "09-Kang", "10-Cho",
// "11-Jang", "12-Lim", "13-Han", "14-Oh", "15-Seo" "16-Jo", "17-Ha", "18-Cha", "19-Ku", "20-Yu"


#include <stdio.h>
#include <stdlib.h> 
#include <time.h> // ������ �����ϱ� ���� include

typedef struct list_node* list_pointer;
// list_node Ÿ�� ���� 
typedef struct list_node {
    int data; // data �ʵ�
    list_pointer next; // ���� ��带 ����Ű�� ������
    list_pointer prev; // ���� ��带 ����Ű�� ������
} list_node;


// �� ���� ���� ����Ʈ�� �����ϴ� �Լ� 
list_pointer create() {
    return NULL;
}


// linked list�� ��带 ���ε� ������� ������ ����ִ� �迭�� ��ҷ� �ʱ�ȭ�ϴ� �Լ�
list_pointer initializeLinkedList(int numarr[], int size) {
    list_pointer head = NULL;
    list_pointer tail = NULL;
       

    // �迭�� ���鼭 �迭�� ��ҷ� ����Ʈ �ʱ�ȭ
    for (int i = 0; i < size; i++) {
        list_pointer newNode = (list_pointer)malloc(sizeof(list_node));
        newNode->data = numarr[i];
        newNode->next = NULL;
        newNode->prev = NULL;

        // ù ����� ���
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        }
        else { // ù ��尡 �ƴ� ���
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    // ���Ḯ��Ʈ�� ������ ������ ������
    head->prev = tail;
    tail->next = head;
    
    // �ʱ�ȭ�� ����Ʈ�� ��ȯ��
    return head;
}


// ���߿��Ḯ��Ʈ�� ��带 �����ϰ�, ������ ��忡 �ش��ϴ� ��ȣ�� �̸��� ����ϰ�, ���� ��带 ��ȯ�ϴ� �Լ�
list_pointer deleteNode(list_pointer head, int target_number, char* namearr[]) {
    list_pointer current = head;

    // ����Ʈ�� ������ ���鼭 data���� target_number�� �ش��ϴ� ��带 ����
    while (current->data != target_number) { 
        current = current->next;
    }

    printf("����Ʈ���� %d-%s�� ����� �����Ǿ����ϴ�.\n", current->data, namearr[current->data - 1]); // � ����� �����Ǿ����� ���

    current->prev->next = current->next;
    current->next->prev = current->prev;

    if (current == head) {
        head = current->next;
    }

    list_pointer next_node = current->next; // ���� ��� ����
    free(current); // ������ ��带 ���� ���� ����Ʈ�� ��ȯ

    return next_node; // ���� ��带 ��ȯ
}


// ���Ḯ��Ʈ�� ��� ������ Ȯ���ϴ� �Լ�
int NodeCount(list_pointer head) {
    int count = 0; // ��� ���� ���� ���� �� �ʱ�ȭ
    list_pointer current = head;
    do {
        count++; // ��� ���� �ø���
        current = current->next;
    }while (current != head);
    return count; // ��� ���� ��ȯ
}

// ���Ḯ��Ʈ�� ����ϴ� �Լ�
void printList(list_pointer head, char* namearr[]) {
    list_pointer current = head;
    do {
        printf("%d-%s ", current->data, namearr[current->data - 1]);  // ��ȣ�� �̸� ���
        current = current->next; // ���� ���� �̵�
    } while (current != head);
    printf("\n");
}

// ���� �Լ�
int main() {
    // 20���� ���ε� ����� ���� (��ȣ, �̸�)
    int numarr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    char* namearr[] = { "Kim", "Lee", "Choi", "Yoon", "Min", "Gwak", "Park", "Jung", "Kang", "Cho", "Jang", "Lim", "Han", "Oh", "Seo", "Jo", "Ha", "Cha", "Ku", "Yu" };
    int size = sizeof(numarr) / sizeof(numarr[0]);

    // numarr[] �迭�� ��ҷ� ����Ʈ�� �ʱ�ȭ�Ͽ� ����
    list_pointer head = initializeLinkedList(numarr, size);

    // ù��° �õ�(����Ʈ���� ó������ ������ ��ȣ(����+2)�� �ϳ� �̰� �����ϱ�)
    srand(time(NULL)); // �Ѽ� �ʱ�ȭ
    int random_number = (rand() % 20) + 1; // 1 ~ 20 ������ ���� �̱�
    int target_number = random_number; // 20���� �Ѿ �ٽ� 1������ ���ư�����
    printf("[1��° �õ�]\n����̱�� %d���� �������Ƿ� %d��° ����� �����˴ϴ�.\n", random_number, (target_number + 1) % 20 + 1); // ������ ����� ���� ���

    head = deleteNode(head, (target_number + 1) % 20 + 1, namearr); // (����+2)�� �ش��ϴ� data�� ���� ��� ����
    printf("1��° ���� ���� ����Ʈ : ");
    printList(head, namearr); // �����ϰ� �� ����Ʈ ���
    printf("����Ʈ���� 19���� ����� ���ҽ��ϴ�.\n\n");

    int try_count = 2;
    // �ι�° �õ� ~ 16��° �õ�
    while (NodeCount(head) > 4) {  // ���� ��� 4�� �� ������ ������ ��� �ݺ��ϱ�
        list_pointer current = head;
        printf("[%d��° �õ�]\n", try_count); // �� ��° �õ����� ���

        if (try_count % 2 == 0) { // ¦����° �õ��� ��� ���� �������� 8��° ��� ����
            for (int i = 0; i < 8; i++) {
                current = current->prev; // ���� ���� �̵�
            }
        }
        else { // Ȧ����° �õ��� ��� ������ �������� 3��° ��� ����
            for (int i = 0; i < 2; i++) {
                current = current->next; // ���� ���� �̵�
            }
        }

        target_number = current->data;

        head = deleteNode(head, target_number, namearr);
        printf("%d��° ���� ���� ����Ʈ : ", try_count);
        printList(head, namearr); // �����ϰ� �� ����Ʈ ���
        printf("����Ʈ���� %d���� ����� ���ҽ��ϴ�.\n\n", NodeCount(head)); // ���� ����� �� ���

        try_count++;
    }

    
    // ���� 4�� ����ϱ�
    printf("���������� ���ǵ����⿡�� ��Ƴ��� ����� 4�� : ");
    printList(head, namearr);

    return 0;
}
