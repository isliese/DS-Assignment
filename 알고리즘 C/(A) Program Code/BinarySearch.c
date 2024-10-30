// 인공지능공학부 2312038 김찬란
// [3] 연결 리스트 정렬 검색 (A) Program Code - BinarySearch.c - 이진 탐색
// 2024.06.01

//  31개의 수를 입력으로 받아, 이를 선택 정렬(selection sort)로 정렬 한 후 이진 탐색(binary search)하시오.


#include <stdio.h>
#include <stdlib.h>

typedef struct list_node* list_pointer; // list_pointer 타입 정의

typedef struct list_node { // list_node struct 정의
    int data;
    list_pointer link;
} list_node;

// 빈 연결 리스트를 생성하는 함수
list_pointer create() {
    return NULL;
}

// 주어진 노드 뒤에 노드를 삽입하는 함수
void insert(list_pointer* head, int data) {
    list_pointer node = (list_pointer)malloc(sizeof(list_node)); // 새로운 노드 생성
    if (node == NULL) {
        printf("메모리 할당 오류\n");
        return;
    }
    node->data = data;
    node->link = NULL;

    if (*head == NULL) {
        *head = node; // 리스트가 비어있다면 샤로운 노드로 head를 설정
    }
    else {
        list_pointer current = *head;
        while (current->link != NULL) {
            current = current->link;
        }
        current->link = node; // 리스트의 먄 끝에 새로 삽입하는 노드를 연결
    }
}

// 연결 리스트를 출력하는 함수
void printList(list_pointer head) {
    list_pointer current = head;
    while (current != NULL) { // 현재 노드가 NULL이 아닐 때까지 노드 돌기
        printf("%d ", current->data);
        current = current->link; // 다음 노드로 이동하기
    }
    printf("\n");
}

// 선택 정렬 함수
void selectionSort(list_pointer head) {
    list_pointer current = head;
    while (current != NULL) { // 노드를 순회하며 최솟값을 찾음
        list_pointer min = current;
        list_pointer temp = current->link;
        while (temp != NULL) { 
            if (temp->data < min->data) {
                min = temp;
            }
            temp = temp->link;
        }
        // 현재 노드와 최솟값을 가지는 노드의 데이터 교환
        int tempData = current->data;
        current->data = min->data;
        min->data = tempData;
        current = current->link; // current 포인터를 다음 노드로 이동
    }
}

// 연결 리스트의 크기를 반환하는 함수
int listSize(list_pointer head) {
    int count = 0; // 크기 정의 및 초기화
    list_pointer current = head;
    while (current != NULL) {
        count++; // 크기 늘리기
        current = current->link;
    }
    return count;
}

// 이진 탐색 함수 (리스트 내에 숫자가 있는 경우 해당 노드의 위치를 반환, 없으면 -1 반환)
int do_BinarySearch(list_pointer head, int key) {
    // left와 right를 양 끝으로 설정
    int left = 0; 
    int right = listSize(head) - 1;

    while (left <= right) { 
        int mid = left + (right - left) / 2;

        list_pointer current = head;
        for (int i = 0; i < mid; i++) {
            current = current->link;
        }

        if (current->data == key) // 만약 키를 찾게 되면 
            return mid; // mid 반환
        else if (current->data < key)
            left = mid + 1; // left를 mid + 1로 설정
        else
            right = mid - 1; // left를 mid - 1로 설정
    }
    return -1;
}

int main() {
    // key로 주어진 31개의 값
    int numarr[] = { 66, 2, 67, 69, 8, 11, 43, 49, 5, 6, 70, 71, 73, 75, 48, 12, 14, 7, 15, 24, 26, 42, 51, 55, 56, 59, 1, 3, 80, 96, 99 };
    int size = sizeof(numarr) / sizeof(numarr[0]);

    // 정렬하기 전의 리스트 출력하기
    printf("기존 리스트: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numarr[i]);
    }
    printf("\n");

    // 주어진 배열을 연결 리스트로 변환
    list_pointer head = create();
    for (int i = 0; i < size; i++) { // numarr의 요소들을 head에 삽입하기
        insert(&head, numarr[i]);
    }

    // 선택 정렬을 사용하여 리스트를 정렬
    selectionSort(head);

    // 정렬 후 리스트 출력
    printf("정렬된 리스트: ");
    printList(head);
    printf("\n\n");

    // 10가지의 검색 문제 수행
    int search_items[10] = { 3, 97, 96, 111, 15, 9, 66, 120, 99, 59 }; // 10개의 검색 문제들
    for (int i = 0; i < 10; i++) { // 검색할 item 리스트를 돌기
        int result = do_BinarySearch(head, search_items[i]);
        printf("[\'%d\'에 대한 검색 문제 수행]\n", search_items[i]); // 어떤 숫자에 대한 검색 문제인지 출력

        if (result == -1) { // 검색 문제가 list에 없을 경우
            printf("False\n");
            printf("No Result in List\n\n");
        }
        else { // 검색 문제가 list에 있을 경우
            printf("True\n");
            printf("%d는 %d번째에 존재합니다.\n\n", search_items[i], result + 1); // 어떤 숫자가 몇 번째에 있는 지 출력
        }
    }

    return 0;
}
