// 인공지능공학부 2312038 김찬란
// [4] 미로 탈출 프로그램 - escapingMaze.c
// 2024.06.01

//미로에 갇힌 생쥐가 출구를 찾는 문제


#include <stdio.h>
#define STACK_SIZE 100 // 스택의 크기 정의

// 스택 타입 정의
typedef struct Stack {
    int row;
    int col;
    int direction;
} Stack;

// 스택 생성 후 초기화
Stack stack[STACK_SIZE];
int top = -1;




// 기본적인 스택 사용 함수

// 스택이 비어있는지 확인하는 함수
int isEmpty() {
    return top == -1;
}

// 스택이 가득 찼는지 확인하는 함수
int isFull() {
    return top >= STACK_SIZE - 1;
}

// 스택에 push하는 함수
void push(Stack item) {
    if (isFull()) { // 스택이 꽉 찼을 경우 처리
        printf("Stack is full\n");
        return;
    }
    stack[++top] = item;

    // 스택 사용 과정 출력 (삽입)
    printf("< %d, %d, %d >를 스택에 삽입하였습니다.\n", item.row, item.col, item.direction);
}

// 스택에서 pop하는 함수
Stack pop() {
    if (isEmpty()) { // 스택이 비어있을 경우 처리
        printf("Stack is empty\n");
        Stack empty = { -1, -1, -1 };
        return empty;
    }
    Stack item = stack[top--];

    // 스택 사용 과정 출력 (제거)
    printf("< %d, %d, %d >를 스택에서 제거하였습니다.\n", item.row, item.col, item.direction);
    return item;
}




// 쥐가 탈출해야 하는 미로(10x10)를 나타내는 array
// 2차원 배열로 생성 // 1은 벽, 0은 통로, 2는 출구 나타낸다.
// 출발지점 : maze[1][0], 도착지점 : maze[8][9] 
int maze[10][10] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 2, 0, 1, 1, 1, 1, 1, 1, 1, 1},
    { 1, 0, 1, 0, 0, 0, 1, 1, 1, 1},
    { 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    { 1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
    { 1, 0, 0, 0, 1, 0, 1, 1, 1, 1},
    { 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
    { 1, 0, 1, 1, 1, 0, 0, 0, 1, 1},
    { 1, 0, 1, 1, 1, 1, 1, 0, 0, 3},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// 미로를 출력하는 함수
void printMaze() {
    printf("[쥐가 탈출해야 하는 미로]\n");
    printf("& : 출발 지점, ! : 도착 지점 \n");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (maze[i][j] == 0) // 길 (쥐가 이동할 수 있음)
                printf("  ");
            else if (maze[i][j] == 1) // 벽 (쥐가 이동할 수 없음)
                printf("* ");
            else if (maze[i][j] == 2) // 출발점
                printf("& ");
            else if (maze[i][j] == 3) // 도착점
                printf("! ");
        }
        printf("\n");
    }
    printf("\n\n");
}

// 쥐의 움직임을 나타내는 array
int mouseMove[4][2] = {
    { -1, 0 }, // 위쪽으로 한 칸 이동
    { 0, 1 },  // 오른쪽으로 한 칸 이동
    { 1, 0 },  // 아래쪽으로 한 칸 이동
    { 0, -1 }  // 왼쪽으로 한 칸 이동
};

// 쥐가 이동한 경로를 표시하는 array
int pathOfMouse[10][10] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    { 0, 0, 1, 1, 0, 1, 1, 1, 1, 1},
    { 1, 0, 1, 0, 0, 0, 1, 1, 1, 1},
    { 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
    { 1, 0, 1, 0, 1, 0, 1, 1, 1, 1},
    { 1, 0, 0, 0, 1, 0, 1, 1, 1, 1},
    { 1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
    { 1, 0, 1, 1, 1, 0, 0, 0, 1, 1},
    { 1, 0, 1, 1, 1, 1, 1, 0, 0, 2},
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};



// 쥐가 미로를 탈출하도록 지시하는 함수
void escapingMaze() {

    // 스택이 빌 때까지 수행
    while (!isEmpty()) {
        Stack current = pop(); // 스택에서 현재 위치와 방향을 pop 연산 수행

        int row = current.row;
        int col = current.col;
        int direction = current.direction;

        while (direction < 4) {
            int next_row = row + mouseMove[direction][0]; // 다음 위치를 계산한다
            int next_col = col + mouseMove[direction][1];

            // 출구에 도달한 경우
            if (next_row == 8 && next_col == 9) { 
                // 출구에 도착했음을 출력한다
                printf("\n\n[출구에 도달하기까지의 과정]:\n");
                printf("");
                for (int i = 0; i <= top; i++) {
                    // 스택에서 pop된 순서대로 쥐의 이동 경로 출력
                    printf("쥐가 %d, %d의 좌표로 이동하였습니다.\n", stack[i].row, stack[i].col, stack[i].direction);
                }
                printf("쥐가 %d, %d의 좌표로 이동하였습니다.\n\n", next_row, next_col);
                printf("쥐가 출구에 도착했습니다!\n\n");
                return;
            }

            // 쥐가 다음 위치로 이동이 가능한 경우
            if (pathOfMouse[next_row][next_col] == 0 && maze[next_row][next_col] == 0) {
                pathOfMouse[next_row][next_col] = 1; // 쥐가 이동한 경로를 pathOfMouse에 표시
                Stack next = { row, col, direction + 1 };
                push(next);
                row = next_row; // 다음 위치로 이동
                col = next_col;
                direction = 0;
            }
            // 쥐가 다음 위치로 이동할 수 없는 경우
            else {
                direction++; // 쥐의 방향을 변경
                printf("쥐가 방향을 바꾸었습니다.\n"); // 쥐가 방향을 변경했음을 출력
            }
        }
    }
    // 쥐가 출구에 도달하지 못한 경우
    printf("경로를 찾을 수 없습니다.\n");
}



// 메인 함수 
int main() {
    printMaze();

    // 스택 초기 설정
    Stack start = { 1, 0, 0 };

    printf("\n[스택 사용 과정]\n"); // 스택 사용 과정을 출력
    push(start);
    pathOfMouse[1][0] = 1;

    escapingMaze(); // 쥐가 미로를 탈출하는 함수 호출
    return 0;
}
