// 인공지능공학부 2312038 김찬란
// [2] 수건 돌리기 게임 (6점) - FirstGame.c - 첫 번째 게임
// 2024.06.01


// [2번째 게임, 3점]
// "01-Kim", "02-Lee", "03-Choi", "04-Yoon", "05-Min", "06-Gwak", "07-Park", "08-Jung", "09-Kang", "10-Cho",
// "11-Jang", "12-Lim", "13-Han", "14-Oh", "15-Seo" "16-Jo", "17-Ha", "18-Cha", "19-Ku", "20-Yu"


#include <stdio.h>
#include <stdlib.h>
#include <time.h> // 난수를 생성하기 위한 include


typedef struct list_node* list_pointer;
// list_node 타입 정의
typedef struct list_node {
    int data; // data 필드
    list_pointer next; // 포인터
} list_node;


// 빈 단순 연결 리스트를 생성하는 함수
list_pointer create() {
    return NULL;
}

// linked list의 노드를 무인도 사람들의 정보가 들어있는 배열의 요소로 초기화하는 함수
list_pointer initializeLinkedList(int numarr[], int size) {
    list_pointer head = NULL;
    list_pointer current = NULL;

    // 배열을 돌면서 배열의 요소로 리스트 초기화
    for (int i = 0; i < size; i++) {
        list_pointer newNode = (list_pointer)malloc(sizeof(list_node));
        newNode->data = numarr[i];
        newNode->next = NULL;

        // 첫 노드일 경우
        if (head == NULL) {
            head = newNode;
            current = head;
        }
        else {
            current->next = newNode;
            current = current->next;
        }
    }
    // 연결리스트를 순환하도록 함
    current->next = head; 

    // 초기화된 리스트를 반환함
    return head;
}



// 단순연결리스트의 노드를 삭제하고, 삭제한 노드에 해당하는 번호와 이름을 출력하고, 다음 노드를 변환하는 함수
list_pointer deleteNode(list_pointer head, list_pointer target, char* namearr[]) {
    list_pointer current = head;
    list_pointer prev = NULL;


    // 리스트의 노드들을 돌면서 data값이 target_number에 해당하는 노드를 삭제
    while (current != target) {
        prev = current;
        current = current->next;
    }

    printf("리스트에서 %d-%s의 사람이 삭제되었습니다.\n", current->data, namearr[current->data - 1]); // 어떤 사람이 삭제되었는지 출력

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

    free(current); // 삭제한 노드를 자유 공간 리스트에 반환
    return head; // 삭제한 리스트를 반환
}



// 연결리스트의 노드 개수를 확인하는 함수
int NodeCount(list_pointer head) {
    if (head == NULL) return 0;

    int count = 0; // 노드 개수 변수 정의
    list_pointer current = head;
    do {
        count++; // 노드 개수 늘리기
        current = current->next;
    } while (current != head);
    return count;
}

// 연결리스트를 출력하는 함수
void printList(list_pointer head, char* namearr[]) {
    if (head == NULL) return;

    list_pointer current = head;
    do {
        printf("%d-%s ", current->data, namearr[current->data - 1]); // 번호와 이름 출력
        current = current->next; // 다음 노드로 이동
    } while (current != head);
    printf("\n");
}



// 메인 함수
int main() {
    // 20명의 무인도 사람들 정보 (번호, 이름)
    int numarr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    char* namearr[] = { "Kim", "Lee", "Choi", "Yoon", "Min", "Gwak", "Park", "Jung", "Kang", "Cho", "Jang", "Lim", "Han", "Oh", "Seo", "Jo", "Ha", "Cha", "Ku", "Yu" };
    int size = sizeof(numarr) / sizeof(numarr[0]);

    // numarr[] 배열의 요소로 리스트를 초기화하여 저장
    list_pointer head = initializeLinkedList(numarr, size);

    // 첫번째 시도(리스트에서 처음으로 삭제될 번호(난수+2)를 하나 뽑고 삭제하기)
    srand(time(NULL)); // 난수 초기화
    int random_number = (rand() % 20) + 1; // 1 ~ 20 사이의 숫자 뽑기
    int target_index = (random_number + 1) % 20;  // 20번을 넘어도 다시 1번으로 돌아가도록
    printf("[1번째 시도]\n제비뽑기로 %d번이 뽑혔으므로 %d번째 사람이 삭제됩니다.\n", random_number, target_index + 1); // 삭제될 사람 출력

    list_pointer start_node = head;
    for (int i = 0; i < target_index; i++) {
        start_node = start_node->next;
    }

    list_pointer current = start_node;
    list_pointer next_node = start_node->next;
    head = deleteNode(head, start_node, namearr);
    printf("1번째 삭제 후의 리스트 : "); 
    printList(head, namearr); // 삭제하고 난 리스트 출력
    printf("리스트에는 %d명의 사람이 남았습니다.\n\n", NodeCount(head)); // 남은 사람의 수 출력

    int try_count = 2;
    // 두번째 시도 ~ 16번째 시도
    while (NodeCount(head) > 4) { // 남은 사람 4명 될 때까지 삭제와 출력 반복하기
        printf("[%d번째 시도]\n", try_count); // 몇 번째 시도인지 출력

        // 오른쪽으로 3번째에 있는 노드 삭제
        for (int i = 0; i < 2; i++) { 
            next_node = next_node->next; // 다음 노드로 이동하기
        }

        list_pointer to_delete = next_node;
        next_node = next_node->next; // 다음 노드 저장하기
        head = deleteNode(head, to_delete, namearr);
        printf("%d번째 삭제 후의 리스트 : ", try_count); 
        printList(head, namearr); // 삭제하고 난 리스트 출력
        printf("리스트에는 %d명의 사람이 남았습니다.\n\n", NodeCount(head)); // 남은 사람의 수 출력

        try_count++; 
    }

    // 최종 4명 출력하기
    printf("최종적으로 수건돌리기에서 살아남은 행운의 4명 : ");
    printList(head, namearr);

    return 0;
}
