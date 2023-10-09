#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct ListNode
{
    struct ListNode *next;
    int val;
};

typedef struct ListNode ListNode;

/* Print a linked list */
static void printLinkedList(ListNode *node) {
    assert(node);
    int i = 0;
    while(node) {
        printf("node[%d] = %d, ", i, node->val);
        node = node->next;
        i++;
    }
    printf("\n");
}

/* 基于链表实现的栈 */
struct linkListStack {
    ListNode *top; // 将头节点作为栈顶
    int size;      // 栈的长度
};

typedef struct linkListStack linkListStack;

/* 构造函数 */
linkListStack *newlinkListStack() {
    linkListStack *new = malloc(sizeof(linkListStack));
    assert(new);
    new->top = NULL;
    new->size = 0;
    return new;
}

/* 析构函数 */
void dellinkListStack(linkListStack *s) {
    assert(s);
    ListNode *next = s->top;
    while(s->top) {
        next = next->next;
        free(s->top);
        s->top = next;
    }
    free(s);
}

/* 获取栈的长度 */
int size(linkListStack *s) {
    return s->size;
}

/* 判断栈是否为空 */
bool isEmpty(linkListStack *s) {
    return s->size == 0;
}

/* 访问栈顶元素 */
int peek(linkListStack *s) {
    assert(s && s->size);
    return s->top->val;
}

/* 入栈 */
void push(linkListStack *s, int num) {
    assert(s);
    ListNode *new = malloc(sizeof(ListNode));
    assert(new);
    new->next = s->top;
    new->val = num;
    s->top = new;
    s->size++;
}

/* 出栈 */
int pop(linkListStack *s) {
    assert(s && s->size);
    ListNode *top = s->top;
    int val = top->val;
    s->top = top->next;
    s->size--;
    free(top);
    return val;
}

/* Driver Code */
int main() {
    /* 初始化栈 */
    linkListStack *stack = newlinkListStack();

    /* 元素入栈 */
    push(stack, 1);
    push(stack, 3);
    push(stack, 2);
    push(stack, 5);
    push(stack, 4);

    printf("栈 stack = ");
    printLinkedList(stack->top);

    /* 访问栈顶元素 */
    int val = peek(stack);
    printf("栈顶元素 top = %d\r\n", val);

    /* 元素出栈 */
    val = pop(stack);
    printf("出栈元素 pop = %d, 出栈后 stack =  ", val);
    printLinkedList(stack->top);

    /* 获取栈的长度 */
    printf("栈的长度 size = %d\n", size(stack));

    /* 判断是否为空 */
    bool empty = isEmpty(stack);
    printf("栈是否为空 = %s\n", empty ? "true" : "false");

    // 释放内存
    dellinkListStack(stack);

    return 0;
}
