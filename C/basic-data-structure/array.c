#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

/* 随机访问元素 */
int randomAccess(int *nums, int size) {
    return nums[rand() % size];
}

/* 扩展数组长度 */
int *extend(int *nums, int size, int enlarge) {
    int newSize = size + enlarge;
    int *new = malloc(sizeof(int) * newSize);
    assert(new);

    int i = 0;
    for (; i < size; i++) {
        new[i] = nums[i];
    }

    for (; i < newSize; i++) {
        new[i] = 0;
    }
    return new;
}

/* 在数组的索引 index 处插入元素 num */
void insert(int *nums, int size, int num, int index) {
    assert(index < size);
    int i = size - 1;
    for (; i > index; i--) {
        nums[i] = nums[i - 1];
    }
    nums[i] = num;
}

/* 删除索引 index 处元素 */
// 注意：stdio.h 占用了 remove 关键词
void removeItem(int *nums, int size, int index) {
    assert(index < size);
    int i = index;
    for (; i < size - 1; i++) {
        nums[i] = nums[i + 1];
    }
    nums[i] = 0;
}

/* 遍历数组 */
void traverse(int *nums, int size) {
    for (int i = 0; i < size; i++) {
        printf("nums[%d] = %d, ", i, nums[i]);
    }
    printf("\n");
}

/* 在数组中查找指定元素 */
int find(int *nums, int size, int target) {
    for (int i = 0; i < size; i++) {
        if (target == nums[i]) {
            return i;
        }
    }
    return -1;
}

/* Driver Code */
int main() {
    /* 初始化数组 */
    int size = 5;
    int arr[5];
    printf("数组 arr = ");
    printArray(arr, size);

    int nums[5] = {1, 3, 2, 5, 4};
    printf("数组 nums = ");
    printArray(nums, size);

    /* 随机访问 */
    int randomNum = randomAccess(nums, size);
    printf("在 nums 中获取随机元素 %d", randomNum);

    /* 长度扩展 */
    int enlarge = 3;
    int *res = extend(nums, size, enlarge);
    size += enlarge;
    printf("将数组长度扩展至 8 ，得到 nums = ");
    printArray(res, size);

    /* 插入元素 */
    insert(res, size, 6, 3);
    printf("在索引 3 处插入数字 6 ，得到 nums = ");
    printArray(res, size);

    /* 删除元素 */
    removeItem(res, size, 2);
    printf("删除索引 2 处的元素，得到 nums = ");
    printArray(res, size);

    /* 遍历数组 */
    traverse(res, size);

    /* 查找元素 */
    int index = find(res, size, 3);
    printf("在 res 中查找元素 3 ，得到索引 = %d\n", index);

    return 0;
}