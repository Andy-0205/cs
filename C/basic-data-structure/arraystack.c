#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

static void printArray(int arr[], int size) {
    printf("[");
    if (arr != NULL && size != 0) {
        for (int i = 0; i < size - 1; i++) {
            if (arr[i] != INT_MAX) {
                printf("%d, ", arr[i]);
            } else {
                printf("NULL, ");
            }
        }
        if (arr[size - 1] != INT_MAX) {
            printf("%d]\n", arr[size - 1]);
        } else {
            printf("NULL]\n");
        }
    } else {
        printf("]");
    }
}

#define MAX_SIZE 5000

/* 基于数组实现的栈 */
struct arrayStack {
    int *data;
    int size;
};

typedef struct arrayStack arrayStack;

/* 构造函数 */
arrayStack *newArrayStack() {
    arrayStack *new = malloc(sizeof(arrayStack));
    assert(new);
    new->data = malloc(sizeof(int) * MAX_SIZE);
    assert(new->data);
    new->size = 0;
    return new;
}

/* 获取栈的长度 */
int size(arrayStack *s) {
    assert(s);
    return s->size;
}

/* 判断栈是否为空 */
bool isEmpty(arrayStack *s) {
    assert(s);
    return s->size == 0;
}

/* 入栈 */
void push(arrayStack *s, int num) {
    assert(s && s->size < MAX_SIZE);
    s->data[s->size] = num;
    s->size++;
}

/* 访问栈顶元素 */
int peek(arrayStack *s) {
    assert(s && s->size);
    return s->data[s->size - 1];
}

/* 出栈 */
int pop(arrayStack *s) {
    assert(s && s->size);
    int top = peek(s);
    s->size--;
    return top;
}

/* Driver Code */
int main() {
    /* 初始化栈 */
    arrayStack *stack = newArrayStack();

    /* 元素入栈 */
    push(stack, 1);
    push(stack, 3);
    push(stack, 2);
    push(stack, 5);
    push(stack, 4);
    printf("栈 stack = ");
    printArray(stack->data, stack->size);

    /* 访问栈顶元素 */
    int val = peek(stack);
    printf("栈顶元素 top = %d\n", val);

    /* 元素出栈 */
    val = pop(stack);
    printf("出栈元素 pop = %d，出栈后 stack = ", val);
    printArray(stack->data, stack->size);

    /* 获取栈的长度 */
    int size = stack->size;
    printf("栈的长度 size =  %d\n", size);

    /* 判断是否为空 */
    bool empty = isEmpty(stack);
    printf("栈是否为空 = %s\n", empty ? "true" : "false");

    // 释放内存
    free(stack->data);
    free(stack);

    return 0;
}