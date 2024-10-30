// 인공지능공학부 2312038 김찬란
// [1] 수식 스택 연산 (A) Program Code - ArrayVersion.c 배열로 풀기
// 2024.06.01

// 3*(20+10)-{20/5+[4*2]/2}+8, 답은 90
// [2점] 2종의 stack을 Linked List로 구조를 잡아서 프로그램
// 괄호의 종류를 확인하고, 이를 해결할 수 있는 프로그램을 작성하시오.
// 제가 작성한 모든 프로그램은 VS 2022에서 작성되었으며, 제 VS 2022에서는 모든 파일이 잘 실행됩니다.


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STACK_SIZE 200 // 스택 사이즈 정의

typedef struct { // IntStack 정의
    int items[STACK_SIZE];
    int top;
} IntStack;

typedef struct { // CharStack 정의 
    char items[STACK_SIZE];
    int top;
} CharStack;

// 스택 초기화 함수
void initIntStack(IntStack* stack) { // IntStack 스택 초기화 
    stack->top = -1;
}

void initCharStack(CharStack* stack) { // CharStack 스택 초기화 
    stack->top = -1;
}

// 스택에 원소 삽입 함수
void pushInt(IntStack* stack, int item) {
    if (stack->top >= STACK_SIZE - 1) { // 스택이 꽉 찼을 경우 
        printf("Stack is full\n"); // 설명 출력 
        exit(1);
    }
    else {
        stack->items[++(stack->top)] = item; // 원소 삽입
    }
}

void pushChar(CharStack* stack, char item) { 
    if (stack->top >= STACK_SIZE - 1) { // 스택이 꽉 찼을 경우
        printf("Stack is full\n"); // 설명 출력
        exit(1);
    }
    else {
        stack->items[++(stack->top)] = item; // 원소 삽입
    }
}

// 스택에서 원소 삭제 함수
int popInt(IntStack* stack) {
    if (stack->top == -1) { // 스택이 비었을 경우
        printf("Stack is empty\n"); // 설명 출력
        exit(1);
    }
    else {
        return stack->items[(stack->top)--]; // 원소 삭제
    }
}

char popChar(CharStack* stack) {
    if (stack->top == -1) { // 스택이 비었을 경우
        printf("Stack is empty\n"); // 설명 출력
        exit(1);
    }
    else {
        return stack->items[(stack->top)--]; // 원소 삭제
    }
}

// peek 함수 (스택의 맨 위 원소 조회) 
int peekInt(IntStack* stack) {
    if (stack->top == -1) { // 스택이 비었을경우
        printf("Stack is empty\n"); // 설명 출력
        exit(1);
    }
    else {
        return stack->items[stack->top]; // 원소 조회
    }
}

char peekChar(CharStack* stack) {
    if (stack->top == -1) { // 스택이 비었을 경우
        printf("Stack is empty\n"); // 설명 출력
        exit(1);
    }
    else {
        return stack->items[stack->top]; // 원소 조회
    }
}

// 스택이 비어있는지 확인하는 함수
bool isEmptyInt(IntStack* stack) { //IntStack 스택이 비었는지 확인
    return stack->top == -1;
}

bool isEmptyChar(CharStack* stack) { // CharStack 스택이 비었는지 확인
    return stack->top == -1;
}

// 연산자 우선순위를 반환하는 함수
int prec(char op) {
    switch (op) {
    case '+': // +, -의 경우 1 반환
    case '-':
        return 1;
    case '*': // *, /의 경우 2 반환
    case '/':
        return 2;
    default: // 피연산자의 경우 0 반환
        return 0; 
    }
}

// 중위표기식을 후위표기식으로 변환하는 함수
char* infix_to_postfix(char* exp) {
    int i = 0; // i를 0으로 설정
    char ch, top_op;
    int len = strlen(exp);
    CharStack s;
    initCharStack(&s);
    char* postfix = (char*)malloc(sizeof(char) * (len * 2 + 1));
    int idx = 0;

    for (i = 0; i < len; i++) {
        ch = exp[i];
        switch (ch) {
            // 연산자의 경우
        case '+': case '-': case '*': case '/':
            while (!isEmptyChar(&s) && (prec(ch) <= prec(peekChar(&s))))
                postfix[idx++] = popChar(&s);
            pushChar(&s, ch);
            break;
            // 괄호의 경우
        case '(': // 소괄호 처리
            pushChar(&s, ch);
            break;
        case ')':
            while ((top_op = popChar(&s)) != '(')
                postfix[idx++] = top_op;
            break;
        case '{': // 중괄호 처리
            pushChar(&s, ch);
            break;
        case '}':
            while ((top_op = popChar(&s)) != '{')
                postfix[idx++] = top_op;
            break;
        case '[': // 대괄호 처리
            pushChar(&s, ch);
            break;
        case ']':
            while ((top_op = popChar(&s)) != '[')
                postfix[idx++] = top_op;
            break;
            // 피연산자의 경우
        default:
            if (ch >= '0' && ch <= '9') {
                while (i < len && exp[i] >= '0' && exp[i] <= '9') {
                    postfix[idx++] = exp[i];
                    i++;
                }
                i--;
                postfix[idx++] = ' '; // 두 자리 숫자 공백으로 구별
            }
            break;
        }
    }
    while (!isEmptyChar(&s)) 
        postfix[idx++] = popChar(&s);

    postfix[idx] = '\0';

    return postfix;
}

// 후위표기식을 계산하는 함수
int post_evaluation(char* exp) {
    // 계산에 필요한 변수 정의
    char ch;
    IntStack s;
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    initIntStack(&s); // 피연산자 스택 초기화

    for (i = 0; i < len; i++) {
        ch = exp[i];
        if (ch >= '0' && ch <= '9') { // ch가 0보다 크고 9보다 작을 경우
            value = 0;
            while (ch >= '0' && ch <= '9') {
                value = value * 10 + (ch - '0');
                ch = exp[++i];
            }
            i--;  // 숫자가 끝난 위치로 인덱스를 조정
            pushInt(&s, value);
        }
        else if (ch != ' ') {// ch가 공백이 아닐 경우
            // 연산을 수행할 피연산자 정의
            op2 = popInt(&s);
            op1 = popInt(&s);
            // 연산자를 보고, 그에 맞는 연산 수행
            switch (ch) {
            case '+': pushInt(&s, op1 + op2); break;
            case '-': pushInt(&s, op1 - op2); break;
            case '*': pushInt(&s, op1 * op2); break;
            case '/': pushInt(&s, op1 / op2); break;
            }
        }
    }
    return popInt(&s);
}

// 메인 함수
int main() {
    char exp[] = "3*(20+10)-{20/5+[4*2]/2}+8"; // 연산할 계산식 출력
    printf("연산할 계산식 : %s\n", exp);
    char* post_sentence = infix_to_postfix(exp);
    printf("연산 결과 : %d\n", post_evaluation(post_sentence)); // 연산 결과 출력
    free(post_sentence);
    return 0;
}
