// �ΰ����ɰ��к� 2312038 ������
// [2] ���� ������ ���� (6��) - FirstGame.c - ù ��° ����
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
    list_pointer next; // ������
} list_node;


// �� �ܼ� ���� ����Ʈ�� �����ϴ� �Լ�
list_pointer create() {
    return NULL;
}

// linked list�� ��带 ���ε� ������� ������ ����ִ� �迭�� ��ҷ� �ʱ�ȭ�ϴ� �Լ�
list_pointer initializeLinkedList(int numarr[], int size) {
    list_pointer head = NULL;
    list_pointer current = NULL;

    // �迭�� ���鼭 �迭�� ��ҷ� ����Ʈ �ʱ�ȭ
    for (int i = 0; i < size; i++) {
        list_pointer newNode = (list_pointer)malloc(sizeof(list_node));
        newNode->data = numarr[i];
        newNode->next = NULL;

        // ù ����� ���
        if (head == NULL) {
            head = newNode;
            current = head;
        }
        else {
            current->next = newNode;
            current = current->next;
        }
    }
    // ���Ḯ��Ʈ�� ��ȯ�ϵ��� ��
    current->next = head; 

    // �ʱ�ȭ�� ����Ʈ�� ��ȯ��
    return head;
}



// �ܼ����Ḯ��Ʈ�� ��带 �����ϰ�, ������ ��忡 �ش��ϴ� ��ȣ�� �̸��� ����ϰ�, ���� ��带 ��ȯ�ϴ� �Լ�
list_pointer deleteNode(list_pointer head, list_pointer target, char* namearr[]) {
    list_pointer current = head;
    list_pointer prev = NULL;


    // ����Ʈ�� ������ ���鼭 data���� target_number�� �ش��ϴ� ��带 ����
    while (current != target) {
        prev = current;
        current = current->next;
    }

    printf("����Ʈ���� %d-%s�� ����� �����Ǿ����ϴ�.\n", current->data, namearr[current->data - 1]); // � ����� �����Ǿ����� ���

    if (current == head) {
        head = current->next;
        list_pointer last = head;
        while (last->next != current) {
            last = last->next;
        }
        last->next = head;
    }
    else {
        prev->next = current->next;
    }

    free(current); // ������ ��带 ���� ���� ����Ʈ�� ��ȯ
    return head; // ������ ����Ʈ�� ��ȯ
}



// ���Ḯ��Ʈ�� ��� ������ Ȯ���ϴ� �Լ�
int NodeCount(list_pointer head) {
    if (head == NULL) return 0;

    int count = 0; // ��� ���� ���� ����
    list_pointer current = head;
    do {
        count++; // ��� ���� �ø���
        current = current->next;
    } while (current != head);
    return count;
}

// ���Ḯ��Ʈ�� ����ϴ� �Լ�
void printList(list_pointer head, char* namearr[]) {
    if (head == NULL) return;

    list_pointer current = head;
    do {
        printf("%d-%s ", current->data, namearr[current->data - 1]); // ��ȣ�� �̸� ���
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
    srand(time(NULL)); // ���� �ʱ�ȭ
    int random_number = (rand() % 20) + 1; // 1 ~ 20 ������ ���� �̱�
    int target_index = (random_number + 1) % 20;  // 20���� �Ѿ �ٽ� 1������ ���ư�����
    printf("[1��° �õ�]\n����̱�� %d���� �������Ƿ� %d��° ����� �����˴ϴ�.\n", random_number, target_index + 1); // ������ ��� ���

    list_pointer start_node = head;
    for (int i = 0; i < target_index; i++) {
        start_node = start_node->next;
    }

    list_pointer current = start_node;
    list_pointer next_node = start_node->next;
    head = deleteNode(head, start_node, namearr);
    printf("1��° ���� ���� ����Ʈ : "); 
    printList(head, namearr); // �����ϰ� �� ����Ʈ ���
    printf("����Ʈ���� %d���� ����� ���ҽ��ϴ�.\n\n", NodeCount(head)); // ���� ����� �� ���

    int try_count = 2;
    // �ι�° �õ� ~ 16��° �õ�
    while (NodeCount(head) > 4) { // ���� ��� 4�� �� ������ ������ ��� �ݺ��ϱ�
        printf("[%d��° �õ�]\n", try_count); // �� ��° �õ����� ���

        // ���������� 3��°�� �ִ� ��� ����
        for (int i = 0; i < 2; i++) { 
            next_node = next_node->next; // ���� ���� �̵��ϱ�
        }

        list_pointer to_delete = next_node;
        next_node = next_node->next; // ���� ��� �����ϱ�
        head = deleteNode(head, to_delete, namearr);
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
