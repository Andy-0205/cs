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

/* 基于环形数组实现的队列 */
struct arrayQueue {
    int *nums;       // 用于存储队列元素的数组
    int front;       // 队首指针，指向队首元素
    int queSize;     // 尾指针，指向队尾 + 1
    int queCapacity; // 队列容量
};

typedef struct arrayQueue arrayQueue;

/* 构造函数 */
arrayQueue *newArrayQueue(int capacity) {
    assert(capacity);
    arrayQueue *new = malloc(sizeof(arrayQueue));
    assert(new);
    new->nums = malloc(sizeof(int) * capacity);
    assert(new->nums);
    new->front = 0;
    new->queSize = 0;
    new->queCapacity = capacity;
    return new;
}

/* 析构函数 */
void delArrayQueue(arrayQueue *queue) {
    assert(queue);
    free(queue->nums);
    free(queue);
}

/* 获取队列的容量 */
int capacity(arrayQueue *queue) {
    assert(queue);
    return queue->queCapacity;
}

/* 获取队列的长度 */
int size(arrayQueue *queue) {
    assert(queue);
    return queue->queSize;
}

/* 判断队列是否为空 */
bool empty(arrayQueue *queue) {
    assert(queue);
    return queue->queSize == 0;
}

/* 访问队首元素 */
int peek(arrayQueue *queue) {
    assert(queue && queue->queSize);
    return queue->nums[queue->front];
}

/* 入队 */
void push(arrayQueue *queue, int num) {
    assert(queue && queue->queSize < queue->queCapacity);
    int rear = (queue->front + queue->queSize) % queue->queCapacity;
    queue->nums[rear] = num;
    queue->queSize++;
}

/* 出队 */
void pop(arrayQueue *queue) {
    assert(queue && queue->queSize);
    queue->front = (queue->front + 1) % queue->queCapacity;
    queue->queSize--;
}

/* 打印队列 */
void printArrayQueue(arrayQueue *queue) {
    assert(queue && queue->queSize);
    int arr[queue->queSize];
    for (int i = 0, j = queue->front; i < queue->queSize; i++, j++) {
        arr[i] = queue->nums[j % queue->queCapacity];
    }
    printArray(arr, queue->queSize);
}

/* Driver Code */
int main() {
    /* 初始化队列 */
    int capacity = 10;
    arrayQueue *queue = newArrayQueue(capacity);

    /* 元素入队 */
    push(queue, 1);
    push(queue, 3);
    push(queue, 2);
    push(queue, 5);
    push(queue, 4);
    printf("队列 queue = ");
    printArrayQueue(queue);

    /* 访问队首元素 */
    int peekNum = peek(queue);
    printf("队首元素 peek = %d\r\n", peekNum);

    /* 元素出队 */
    pop(queue);
    printf("出队元素 pop = %d，出队后 queue = ", peekNum);
    printArrayQueue(queue);

    /* 获取队列的长度 */
    int queueSize = size(queue);
    printf("队列长度 size = %d\r\n", queueSize);

    /* 判断队列是否为空 */
    bool isEmpty = empty(queue);
    printf("队列是否为空 = %s\r\n", isEmpty ? "true" : "false");

    /* 测试环形数组 */
    for (int i = 0; i < 10; i++) {
        push(queue, i);
        pop(queue);
        printf("第 %d 轮入队 + 出队后 queue = ", i);
        printArrayQueue(queue);
    }

    // 释放内存
    delArrayQueue(queue);

    return 0;
}
