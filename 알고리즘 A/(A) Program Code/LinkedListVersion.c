// 인공지능공학부 2312038 김찬란
// [1] 수식 스택 연산 (A) Program Code - LinkedListVersion.c - 연결리스트로 풀기
// 2024.06.01

// 2*(10+15*3-5)+{[30/3-(4/2)*3]+8}+6, 답은 118
// [2점] 2종의 stack을 Linked List로 구조를 잡아서 프로그램
// 괄호의 종류를 확인하고, 이를 해결할 수 있는 프로그램을 작성하시오.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 노드 구조체 정의
typedef struct Node {
    int data; // 데이터 필드
    struct Node* next; // 포인터
} Node;

// 스택 구조체 정의
typedef struct {
    Node* top;
} Stack;

// 스택 초기화 함수
void init(Stack* stack) {
    stack->top = NULL; // top 포인터를 NULL로 핟당
}

// 스택이 비어있는지 확인하는 함수
int isEmpty(Stack* stack) {
    return stack->top == NULL;// top 포인터가 NULL이면 스택이 비어있다고 판단
}

// 스택에 원소 삽입 함수
void push(Stack* stack, int item) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // malloc() 함수를 사용해 새로운 노드 생성
    newNode->data = item;
    newNode->next = stack->top;
    stack->top = newNode;
}

// 스택에서 원소 삭제 후 반환하는 함수
int pop(Stack* stack) {
    if (isEmpty(stack)) { // 스택이 비어있는 경우
        printf("Stack is empty\n"); // 설명 출력 
        exit(1);
    }
    Node* temp = stack->top; // top 노드를 제거
    int data = temp->data;
    stack->top = temp->next;
    free(temp); // 노드를 자유 공간 리스트에 반환
    return data; // 데이터 반환
}

// 스택에서 맨 위 원소를 반환하는 함수
int peek(Stack* stack) {
    if (isEmpty(stack)) { // 스택이 비어있는 경우
        printf("Stack is empty\n"); // 설명 출력
        exit(1);
    }
    return stack->top->data; // top 노드의 데이터를 반환
}

// 연산자 우선순위를 반환하는 함수
int prec(char op) { // +와 -는 1, *와 /는 2, 대괄호와 중괄호는 0 반환
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '[': case ']':
    case '{': case '}':
        return 0;
    default:
        return 0;
    }
}

// 중위표기식을 후위표기식으로 변환하는 함수
char* infix_to_postfix(char* exp) { // exp의 길이를 구하고 스택 초기화 
    int i = 0;
    char ch, top_op;
    int len = strlen(exp);
    Stack s;
    init(&s);
    char* postfix = (char*)malloc(sizeof(char) * (len * 2 + 1)); 
    int idx = 0;

    for (i = 0; i < len; i++) { // exp를 순회하며 각 문자 처리
        ch = exp[i];
        switch (ch) {
            // 연산자의 경우
            // 스택의 맨 위 연산자보다 낮거나 같으면 스택에서 연산자를 꺼내 postfix에 추가
        case '+': case '-': case '*': case '/':
            while (!isEmpty(&s) && (prec(ch) <= prec(peek(&s))))
                postfix[idx++] = pop(&s);
            push(&s, ch);
            break;
            // 여는 괄호를 만나면 스택에 넣고, 닫는 괄호를 만나면 여는 괄호가 나올 때까지 스택에서 연산자를 꺼내 postfix에 추가
            // 대괄호와 중괄호의 경우
        case '[': case '{':
            push(&s, ch);
            break;
        case ']': case '}':
            while ((top_op = pop(&s)) != '[' && top_op != '{')
                postfix[idx++] = top_op;
            break;
            // 소괄호의 경우
        case '(':
            push(&s, ch);
            break;
        case ')':
            while ((top_op = pop(&s)) != '(')
                postfix[idx++] = top_op;
            break;
            // 피연산자의 경우, 연속된 숫자를 하나의 숫자로 결합하여 postfix에 추가
        default:
            // 두 자리 수 이상의 피연산자도 처리 가능하도록
            if (ch >= '0' && ch <= '9') {
                int num = 0;
                while (i < len && exp[i] >= '0' && exp[i] <= '9') {
                    num = num * 10 + (exp[i] - '0');
                    i++;
                }
                i--;
                postfix[idx++] = num + '0'; // 아스키코드와 대응하기 위해
            }
            break;
        }
    }
    while (!isEmpty(&s))
        postfix[idx++] = pop(&s);

    postfix[idx] = '\0'; // postfix의 문자열의 끝에 null 문자를 추가

    return postfix; // postfix 반환
}

// 후위표기식을 계산하는 함수
int post_evaluation(char* exp) { 
    char ch;
    Stack s;
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    init(&s);
    for (i = 0; i < len; i++) {
        ch = exp[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '[' && ch != ']' && ch != '{' && ch != '}') {
            value = ch - '0';
            push(&s, value);
        }
        else {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch) { // 연산자 별 연산 수행
            case '+': push(&s, op1 + op2); break;
            case '-': push(&s, op1 - op2); break;
            case '*': push(&s, op1 * op2); break;
            case '/': push(&s, op1 / op2); break;
            }
        }
    }
    return pop(&s);
}


// 메인 함수
int main() {
    char exp[] = "2*(10+15*3-5)+{[30/3-(4/2)*3]+8}+6"; // 연산할 계산식
    printf("연산할 계산식 : %s\n", exp);

    Stack stack;
    init(&stack); // 스택 초기화
    char* post_sentence = infix_to_postfix(exp); // 중위표기식을 후위표기식으로 변환
    printf("연산 결과 : %d\n", post_evaluation(post_sentence));

    return 0;
}
