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

/* 基于链表实现的队列 */
struct linkedListQueue {
    ListNode *front, *rear;
    int queSize;
};

typedef struct linkedListQueue linkedListQueue;

/* 构造函数 */
linkedListQueue *newLinkedListQueue() {
    linkedListQueue *new = malloc(sizeof(linkedListQueue));
    assert(new);
    new->front = NULL;
    new->rear = NULL;
    new->queSize = 0;
    return new;
}

/* 析构函数 */
void delLinkedListQueue(linkedListQueue *queue) {
    assert(queue);
    ListNode *next = queue->front;
    while(queue->front) {
        next = next->next;
        free(queue->front);
        queue->front = next;
    }
    free(queue);
}

/* 获取队列的长度 */
int size(linkedListQueue *queue) {
    assert(queue);
    return queue->queSize;
}

/* 判断队列是否为空 */
bool empty(linkedListQueue *queue) {
    assert(queue);
    return queue->queSize == 0;
}

/* 入队 */
void push(linkedListQueue *queue, int num) {
    assert(queue);
    ListNode *next = malloc(sizeof(ListNode));
    assert(next);
    next->val = num;
    next->next = NULL;
    if (queue->rear) {
        queue->rear->next = next;
        queue->rear = next;
    } else {
        queue->front = next;
        queue->rear = next;
    }
    queue->queSize++;
}

/* 访问队首元素 */
int peek(linkedListQueue *queue) {
    assert(queue && queue->queSize);
    return queue->front->val;
}

/* 出队 */
void pop(linkedListQueue *queue) {
    assert(queue && queue->queSize);
    ListNode *oldfront = queue->front;
    queue->front = queue->front->next;
    free(oldfront);
    queue->queSize--;
}

/* 打印队列 */
void printLinkedListQueue(linkedListQueue *queue) {
    assert(queue);
    printLinkedList(queue->front);
}

/* Driver Code */
int main() {
    /* 初始化队列 */
    linkedListQueue *queue = newLinkedListQueue();

    /* 元素入队 */
    push(queue, 1);
    push(queue, 3);
    push(queue, 2);
    push(queue, 5);
    push(queue, 4);
    printf("队列 queue = ");
    printLinkedListQueue(queue);

    /* 访问队首元素 */
    int peekNum = peek(queue);
    printf("队首元素 peek = %d\r\n", peekNum);

    /* 元素出队 */
    pop(queue);
    printf("出队元素 pop = %d，出队后 queue = ", peekNum);
    printLinkedListQueue(queue);

    /* 获取队列的长度 */
    int queueSize = size(queue);
    printf("队列长度 size = %d\r\n", queueSize);

    /* 判断队列是否为空 */
    bool isEmpty = empty(queue);
    printf("队列是否为空 = %s\r\n", isEmpty ? "true" : "false");

    // 释放内存
    delLinkedListQueue(queue);

    return 0;
}
