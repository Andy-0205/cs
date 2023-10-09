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

/* 基于环形数组实现的双向队列,double-ended queue */
struct arrayDeque {
    int *nums;       // 用于存储队列元素的数组
    int front;       // 队首指针，指向队首元素
    int queSize;     // 尾指针，指向队尾 + 1
    int queCapacity; // 队列容量
};

typedef struct arrayDeque arrayDeque;

/* 构造函数 */
arrayDeque *newArrayDeque(int capacity) {
    assert(capacity);
    arrayDeque *new = malloc(sizeof(arrayDeque));
    assert(new);
    new->nums = malloc(sizeof(int) * capacity);
    assert(new->nums);
    new->front = 0;
    new->queSize = 0;
    new->queCapacity = capacity;
    return new;
}

/* 析构函数 */
void delArrayDeque(arrayDeque *deque) {
    assert(deque);
    free(deque->nums);
    free(deque);
}

/* 获取双向队列的容量 */
int capacity(arrayDeque *deque) {
    assert(deque);
    return deque->queCapacity;
}

/* 获取双向队列的长度 */
int size(arrayDeque *deque) {
    assert(deque);
    return deque->queSize;
}

/* 判断双向队列是否为空 */
bool empty(arrayDeque *deque) {
    assert(deque);
    return deque->queSize == 0;
}

/* 队首入队 */
void pushFirst(arrayDeque *deque, int num) {
    assert(deque && deque->queSize < deque->queCapacity);
    deque->front = (deque->front + deque->queCapacity - 1) % deque->queCapacity;
    deque->nums[deque->front] = num;
    deque->queSize++;
}

/* 队尾入队 */
void pushLast(arrayDeque *deque, int num) {
    assert(deque && deque->queSize < deque->queCapacity);
    deque->nums[(deque->front + deque->queSize) % deque->queCapacity] = num;
    deque->queSize++;
}

/* 访问队首元素 */
int peekFirst(arrayDeque *deque) {
    assert(deque && deque->queSize);
    return deque->nums[deque->front];
}

/* 访问队尾元素 */
int peekLast(arrayDeque *deque) {
    assert(deque && deque->queSize);
    return deque->nums[(deque->front + deque->queSize - 1) % deque->queCapacity];
}

/* 队首出队 */
int popFirst(arrayDeque *deque) {
    assert(deque && deque->queSize);
    int top = deque->nums[deque->front];
    deque->front = (deque->front + 1) % deque->queCapacity;
    deque->queSize--;
    return top;
}

/* 队尾出队 */
int popLast(arrayDeque *deque) {
    assert(deque && deque->queSize);
    int rear = deque->nums[(deque->front + deque->queSize - 1) % deque->queCapacity];
    deque->queSize--;
    return rear;
}

/* 打印队列 */
void printArrayDeque(arrayDeque *deque) {
    assert(deque && deque->queSize);
    int arr[deque->queSize];
    for (int i = 0, j = deque->front; i < deque->queSize; i++, j++) {
        arr[i] = deque->nums[j % deque->queCapacity];
    }
    printArray(arr, deque->queSize);
}

/* Driver Code */
int main() {
    /* 初始化队列 */
    int capacity = 10;
    arrayDeque *deque = newArrayDeque(capacity);
    pushLast(deque, 3);
    pushLast(deque, 2);
    pushLast(deque, 5);
    printf("双向队列 deque = ");
    printArrayDeque(deque);

    /* 访问元素 */
    int peekFirstNum = peekFirst(deque);
    printf("队首元素 peekFirst = %d\r\n", peekFirstNum);
    int peekLastNum = peekLast(deque);
    printf("队尾元素 peekLast = %d\r\n", peekLastNum);

    /* 元素入队 */
    pushLast(deque, 4);
    printf("元素 4 队尾入队后 deque = ");
    printArrayDeque(deque);
    pushFirst(deque, 1);
    printf("元素 1 队首入队后 deque = ");
    printArrayDeque(deque);

    /* 元素出队 */
    int popLastNum = popLast(deque);
    printf("队尾出队元素 = %d，队尾出队后 deque= ", popLastNum);
    printArrayDeque(deque);
    int popFirstNum = popFirst(deque);
    printf("队首出队元素 = %d，队首出队后 deque= ", popFirstNum);
    printArrayDeque(deque);

    /* 获取队列的长度 */
    int dequeSize = size(deque);
    printf("双向队列长度 size = %d\r\n", dequeSize);

    /* 判断队列是否为空 */
    bool isEmpty = empty(deque);
    printf("队列是否为空 = %s\r\n", isEmpty ? "true" : "false");

    // 释放内存
    delArrayDeque(deque);

    return 0;
}
