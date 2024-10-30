// 인공지능공학부 2312038 김찬란
// [3] 연결 리스트 정렬 검색 (A) Program Code - SelectionSorting.c - 정렬
// 2024.06.01

//  31개의 수를 입력으로 받아, 이를 선택 정렬(selection sort)로 정렬 하시오.
/*  (66, 2, 67, 69, 8, 11, 43, 49, 5, 6, 70, 71, 73, 75, 48, 12, 14, 7, 15, 24, 26, 42,
51, 55, 56, 59, 1, 3, 80, 96, 99) */

#include <stdio.h>
#include <stdlib.h> // malloc 함수를 위한 include

typedef struct list_node* list_pointer;

typedef struct list_node {
    int data; // data 필드
    list_pointer link; // 포인터
} list_node;

// 빈 연결 리스트를 생성하는 함수
list_pointer create() {
    return NULL;
}

// 주어진 노드 뒤에 노드를 삽입하는 함수
void insert(list_pointer* head, int data) {
    list_pointer node = (list_pointer)malloc(sizeof(list_node));
    if (node == NULL) {
        printf("메모리 할당 오류\n");
        return;
    }
    node->data = data;
    node->link = NULL;

    if (*head == NULL) {
        *head = node; // 리스트가 비어있다면 head를 새로운 노드로 설정
    }
    else { // 리스트가 비어있지 않은 경우
        list_pointer current = *head; 
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = node; // 리스트의 끝에 새로운 노드를 연결
    }
}


// 연결 리스트를 출력하는 함수
void printList(list_pointer head) {
    list_pointer current = head;
    while (current != NULL) { // 리스트의 각 노드 순회
        printf("%d ", current->data); /// data 출력
        current = current->link;
    }
    printf("\n");
}

// 선택 정렬 함수
void selectionSort(list_pointer head) {
    list_pointer current = head;
    while (current != NULL) { // current가 null이 아닐 때까지
        list_pointer min = current;
        list_pointer temp = current->link;
        while (temp != NULL) { // temp 포인터를 사용하여 최솟값 찾기
            if (temp->data < min->data) {
                min = temp;
            }
            temp = temp->link; 
        }
        // 현재 노드와 최솟값을 가지는 노드 교환
        int tempData = current->data;
        current->data = min->data;
        min->data = tempData;
        current = current->link; // current 포인터를 다음 노드로 이동
    }
}

int main() {
    list_pointer head = create(); // 빈 연결리스트 생성

    // 정렬할 숫자들
    int numarr[] = { 66, 2, 67, 69, 8, 11, 43, 49, 5, 6, 70, 71, 73, 75, 48, 12, 14, 7, 15, 24, 26, 42, 51, 55, 56, 59, 1, 3, 80, 96, 99 };

    // 배열 numarr[]의 요소를 리스트에 삽입하기
    for (int i = 0; i < sizeof(numarr) / sizeof(numarr[0]); i++) {
        insert(&head, numarr[i]);
    }

    // 삽입 후 리스트 출력
    printf("기존 리스트: ");
    printList(head);

    // 선택 정렬을 사용하여 리스트 정렬
    selectionSort(head);

    // 정렬 후 리스트 출력
    printf("정렬된 리스트: ");
    printList(head);

    return 0;
}