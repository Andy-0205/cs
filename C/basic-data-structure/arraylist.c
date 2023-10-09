#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* 列表类简易实现 */
struct myList {
    int *nums;       // 数组（存储列表元素）
    int capacity;    // 列表容量
    int size;        // 列表大小
    int extendRatio; // 列表每次扩容的倍数
};

typedef struct myList myList;

#define LIST_DEFAULT_SIZE 10
#define LIST_DEFAULT_RATIO 2

void extendCapacity(myList *list);

/* 构造函数 */
myList *newMyList() {
    myList *new = malloc(sizeof(myList));
    assert(new);

    new->nums = malloc(sizeof(int) * LIST_DEFAULT_SIZE);
    assert(new->nums);
    for (int i = 0; i < LIST_DEFAULT_SIZE; i++) {
        new->nums[i] = 0;
    }

    new->capacity = LIST_DEFAULT_SIZE;
    new->size = 0;
    new->extendRatio = LIST_DEFAULT_RATIO;
    return new;
}

/* 析构函数 */
void delMyList(myList *list) {
    free(list->nums);
    free(list);
}

/* 获取列表长度 */
int size(myList *list) {
    return list->size;
}

/* 获取列表容量 */
int capacity(myList *list) {
    return list->capacity;
}

/* 访问元素 */
int get(myList *list, int index) {
    assert(index >= 0 && index < list->size);
    return list->nums[index];
}

/* 更新元素 */
void set(myList *list, int index, int num) {
    assert(index >= 0 && index < list->size);
    list->nums[index] = num;
}

/* 尾部添加元素 */
void add(myList *list, int num) {
    if (list->size == list->capacity) {
        extendCapacity(list);
    }

    list->nums[list->size] = num;
    list->size++;
}

/* 中间插入元素 */
void insert(myList *list, int index, int num) {
    assert(index >= 0 && index < list->size);
    if (list->size == list->capacity) {
        extendCapacity(list);
    }

    int i = list->size;
    for (; i > index; i--) {
        list->nums[i] = list->nums[i - 1];
    }
    list->nums[i] = num;
    list->size++;
}

/* 删除元素 */
// 注意：stdio.h 占用了 remove 关键词
int removeNum(myList *list, int index) {
    assert(index >= 0 && index < list->size);
    int i = index;
    int num = list->nums[i];
    for (; i < list->size - 1; i++) {
        list->nums[i] = list->nums[i + 1];
    }
    list->nums[i] = 0;
    list->size--;
    return num;
}

/* 列表扩容 */
void extendCapacity(myList *list) {
    int newSize = list->capacity * list->extendRatio;
    list->nums = realloc(list->nums, sizeof(int) * newSize);
    assert(list->nums);
    for (int i = list->size; i < newSize; i++) {
        list->nums[i] = 0;
    }
    list->capacity = newSize;
}

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

/* 将列表转换为 Array 用于打印 */
int *toArray(myList *list) {
    return list->nums;
}

/* Driver Code */
int main() {
    /* 初始化列表 */
    myList *list = newMyList();
    /* 尾部添加元素 */
    add(list, 1);
    add(list, 3);
    add(list, 2);
    add(list, 5);
    add(list, 4);
    printf("列表 list = ");
    printArray(toArray(list), size(list));
    printf("容量 = %d ，长度 = %d\n", capacity(list), size(list));

    /* 中间插入元素 */
    insert(list, 3, 6);
    printf("在索引 3 处插入数字 6 ，得到 list = ");
    printArray(toArray(list), size(list));

    /* 删除元素 */
    removeNum(list, 3);
    printf("删除索引 3 处的元素，得到 list = ");
    printArray(toArray(list), size(list));

    /* 访问元素 */
    int num = get(list, 1);
    printf("访问索引 1 处的元素，得到 num = %d\n", num);

    /* 更新元素 */
    set(list, 1, 0);
    printf("将索引 1 处的元素更新为 0 ，得到 list = ");
    printArray(toArray(list), size(list));

    /* 测试扩容机制 */
    for (int i = 0; i < 10; i++) {
        // 在 i = 5 时，列表长度将超出列表容量，此时触发扩容机制
        add(list, i);
    }

    printf("扩容后的列表 list = ");
    printArray(toArray(list), size(list));
    printf("容量 = %d ，长度 = %d\n", capacity(list), size(list));

    /* 释放分配内存 */
    delMyList(list);

    return 0;
}