// �ΰ����ɰ��к� 2312038 ������
// [4] �̷� Ż�� ���α׷� - escapingMaze.c
// 2024.06.01

//�̷ο� ���� ���㰡 �ⱸ�� ã�� ����


#include <stdio.h>
#define STACK_SIZE 100 // ������ ũ�� ����

// ���� Ÿ�� ����
typedef struct Stack {
    int row;
    int col;
    int direction;
} Stack;

// ���� ���� �� �ʱ�ȭ
Stack stack[STACK_SIZE];
int top = -1;




// �⺻���� ���� ��� �Լ�

// ������ ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty() {
    return top == -1;
}

// ������ ���� á���� Ȯ���ϴ� �Լ�
int isFull() {
    return top >= STACK_SIZE - 1;
}

// ���ÿ� push�ϴ� �Լ�
void push(Stack item) {
    if (isFull()) { // ������ �� á�� ��� ó��
        printf("Stack is full\n");
        return;
    }
    stack[++top] = item;

    // ���� ��� ���� ��� (����)
    printf("< %d, %d, %d >�� ���ÿ� �����Ͽ����ϴ�.\n", item.row, item.col, item.direction);
}

// ���ÿ��� pop�ϴ� �Լ�
Stack pop() {
    if (isEmpty()) { // ������ ������� ��� ó��
        printf("Stack is empty\n");
        Stack empty = { -1, -1, -1 };
        return empty;
    }
    Stack item = stack[top--];

    // ���� ��� ���� ��� (����)
    printf("< %d, %d, %d >�� ���ÿ��� �����Ͽ����ϴ�.\n", item.row, item.col, item.direction);
    return item;
}




// �㰡 Ż���ؾ� �ϴ� �̷�(10x10)�� ��Ÿ���� array
// 2���� �迭�� ���� // 1�� ��, 0�� ���, 2�� �ⱸ ��Ÿ����.
// ������� : maze[1][0], �������� : maze[8][9] 
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

// �̷θ� ����ϴ� �Լ�
void printMaze() {
    printf("[�㰡 Ż���ؾ� �ϴ� �̷�]\n");
    printf("& : ��� ����, ! : ���� ���� \n");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (maze[i][j] == 0) // �� (�㰡 �̵��� �� ����)
                printf("  ");
            else if (maze[i][j] == 1) // �� (�㰡 �̵��� �� ����)
                printf("* ");
            else if (maze[i][j] == 2) // �����
                printf("& ");
            else if (maze[i][j] == 3) // ������
                printf("! ");
        }
        printf("\n");
    }
    printf("\n\n");
}

// ���� �������� ��Ÿ���� array
int mouseMove[4][2] = {
    { -1, 0 }, // �������� �� ĭ �̵�
    { 0, 1 },  // ���������� �� ĭ �̵�
    { 1, 0 },  // �Ʒ������� �� ĭ �̵�
    { 0, -1 }  // �������� �� ĭ �̵�
};

// �㰡 �̵��� ��θ� ǥ���ϴ� array
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



// �㰡 �̷θ� Ż���ϵ��� �����ϴ� �Լ�
void escapingMaze() {

    // ������ �� ������ ����
    while (!isEmpty()) {
        Stack current = pop(); // ���ÿ��� ���� ��ġ�� ������ pop ���� ����

        int row = current.row;
        int col = current.col;
        int direction = current.direction;

        while (direction < 4) {
            int next_row = row + mouseMove[direction][0]; // ���� ��ġ�� ����Ѵ�
            int next_col = col + mouseMove[direction][1];

            // �ⱸ�� ������ ���
            if (next_row == 8 && next_col == 9) { 
                // �ⱸ�� ���������� ����Ѵ�
                printf("\n\n[�ⱸ�� �����ϱ������ ����]:\n");
                printf("");
                for (int i = 0; i <= top; i++) {
                    // ���ÿ��� pop�� ������� ���� �̵� ��� ���
                    printf("�㰡 %d, %d�� ��ǥ�� �̵��Ͽ����ϴ�.\n", stack[i].row, stack[i].col, stack[i].direction);
                }
                printf("�㰡 %d, %d�� ��ǥ�� �̵��Ͽ����ϴ�.\n\n", next_row, next_col);
                printf("�㰡 �ⱸ�� �����߽��ϴ�!\n\n");
                return;
            }

            // �㰡 ���� ��ġ�� �̵��� ������ ���
            if (pathOfMouse[next_row][next_col] == 0 && maze[next_row][next_col] == 0) {
                pathOfMouse[next_row][next_col] = 1; // �㰡 �̵��� ��θ� pathOfMouse�� ǥ��
                Stack next = { row, col, direction + 1 };
                push(next);
                row = next_row; // ���� ��ġ�� �̵�
                col = next_col;
                direction = 0;
            }
            // �㰡 ���� ��ġ�� �̵��� �� ���� ���
            else {
                direction++; // ���� ������ ����
                printf("�㰡 ������ �ٲپ����ϴ�.\n"); // �㰡 ������ ���������� ���
            }
        }
    }
    // �㰡 �ⱸ�� �������� ���� ���
    printf("��θ� ã�� �� �����ϴ�.\n");
}



// ���� �Լ� 
int main() {
    printMaze();

    // ���� �ʱ� ����
    Stack start = { 1, 0, 0 };

    printf("\n[���� ��� ����]\n"); // ���� ��� ������ ���
    push(start);
    pathOfMouse[1][0] = 1;

    escapingMaze(); // �㰡 �̷θ� Ż���ϴ� �Լ� ȣ��
    return 0;
}
