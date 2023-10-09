#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/* 双向链表节点 */
struct doubleListNode {
    int val;                     // 节点值
    struct doubleListNode *next; // 后继节点
    struct doubleListNode *prev; // 前驱节点
};

typedef struct doubleListNode doubleListNode;

/* Print a linked list */
static void printLinkedList(doubleListNode *node) {
    assert(node);
    int i = 0;
    while(node) {
        printf("node[%d] = %d, ", i, node->val);
        node = node->next;
        i++;
    }
    printf("\n");
}

/* 构造函数 */
doubleListNode *newdoubleListNode(int num) {
    doubleListNode *new = malloc(sizeof(doubleListNode));
    assert(new);
    new->val = num;
    new->next = NULL;
    new->prev = NULL;
    return new;
}

/* 析构函数 */
void deldoubleListNode(doubleListNode *node) {
    assert(node);
    free(node);
}

/* 基于双向链表实现的双向队列 */
struct linkedListDeque {
    doubleListNode *front, *rear; // 头节点 front ，尾节点 rear
    int queSize;                  // 双向队列的长度
};

typedef struct linkedListDeque linkedListDeque;

/* 构造函数 */
linkedListDeque *newLinkedListDeque() {
    linkedListDeque *new = malloc(sizeof(linkedListDeque));
    assert(new);
    new->front = NULL;
    new->rear = NULL;
    new->queSize = 0;
    return new;
}

/* 析构函数 */
void delLinkedListdeque(linkedListDeque *deque) {
    assert(deque);
    doubleListNode *next = deque->front;
    while(deque->front) {
        next = next->next;
        deldoubleListNode(deque->front);
        deque->front = next;
    }
    free(deque);
}

/* 获取队列的长度 */
int size(linkedListDeque *deque) {
    assert(deque);
    return deque->queSize;
}

/* 判断队列是否为空 */
bool empty(linkedListDeque *deque) {
    assert(deque);
    return deque->queSize == 0;
}

/* 入队 */
void push(linkedListDeque *deque, int num, bool isFront) {
    doubleListNode *oldfront = deque->front;
    doubleListNode *new = newdoubleListNode(num);
    assert(new);
    if (!oldfront) {
        deque->front = new;
        deque->rear = new;
        deque->queSize++;
        return;
    }

    if (isFront) {
        new->next = oldfront;
        oldfront->prev = new;
        deque->front = new;
    } else {
        doubleListNode *oldrear = deque->rear;
        oldrear->next = new;
        new->prev = oldrear;
        deque->rear = new;
    }

    deque->queSize++;
}

/* 队首入队 */
void pushFirst(linkedListDeque *deque, int num) {
    assert(deque);
    push(deque, num, true);
}

/* 队尾入队 */
void pushLast(linkedListDeque *deque, int num) {
    assert(deque);
    push(deque, num, false);
}

/* 访问队首元素 */
int peekFirst(linkedListDeque *deque) {
    assert(deque && deque->queSize);
    return deque->front->val;
}

/* 访问队尾元素 */
int peekLast(linkedListDeque *deque) {
    assert(deque && deque->queSize);
    return deque->rear->val;
}

/* 出队 */
int pop(linkedListDeque *deque, bool isFront) {
    int val = 0;
    if (isFront) {
        doubleListNode *oldfront = deque->front;
        val = peekFirst(deque);
        deque->front = oldfront->next;
        if (deque->front) {
            deque->front->prev = NULL;
        }
        deldoubleListNode(oldfront);
    } else {
        doubleListNode *oldrear = deque->rear;
        val = peekLast(deque);
        deque->rear = oldrear->prev;
        if (deque->rear) {
            deque->rear->next = NULL;
        }
        free(oldrear);
    }
    deque->queSize--;
    return val;
}

/* 队首出队 */
int popFirst(linkedListDeque *deque) {
    assert(deque && deque->queSize);
    return pop(deque, true);
}

/* 队尾出队 */
int popLast(linkedListDeque *deque) {
    assert(deque && deque->queSize);
    return pop(deque, false);
}

/* 打印队列 */
void printLinkedListDeque(linkedListDeque *deque) {
    assert(deque && deque->queSize);
    printLinkedList(deque->front);
}

/* Driver Code */
int main() {
    /* 初始化双向队列 */
    linkedListDeque *deque = newLinkedListDeque();
    pushLast(deque, 3);
    pushLast(deque, 2);
    pushLast(deque, 5);
    printf("双向队列 deque = ");
    printLinkedListDeque(deque);

    /* 访问元素 */
    int peekFirstNum = peekFirst(deque);
    printf("队首元素 peekFirst = %d\r\n", peekFirstNum);
    int peekLastNum = peekLast(deque);
    printf("队首元素 peekLast = %d\r\n", peekLastNum);

    /* 元素入队 */
    pushLast(deque, 4);
    printf("元素 4 队尾入队后 deque =");
    printLinkedListDeque(deque);
    pushFirst(deque, 1);
    printf("元素 1 队首入队后 deque =");
    printLinkedListDeque(deque);

    /* 元素出队 */
    int popLastNum = popLast(deque);
    printf("队尾出队元素 popLast = %d，队尾出队后 deque = ", popLastNum);
    printLinkedListDeque(deque);
    int popFirstNum = popFirst(deque);
    printf("队首出队元素 popFirst = %d，队首出队后 deque = ", popFirstNum);
    printLinkedListDeque(deque);

    /* 获取队列的长度 */
    int dequeSize = size(deque);
    printf("双向队列长度 size = %d\r\n", dequeSize);

    /* 判断队列是否为空 */
    bool isEmpty = empty(deque);
    printf("双向队列是否为空 = %s\r\n", isEmpty ? "true" : "false");

    // 释放内存
    delLinkedListdeque(deque);

    return 0;
}
