#include <stdlib.h>
#include <stdio.h>

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int randomAccess(int arr[], int size) {
    return arr[rand() % size];
}

int *extend(int arr[], int size, int enlarge) {
    int *res = (int *)malloc(sizeof(int) * (size + enlarge));
    int i;
    for (i = 0; i < size; i++) {
        res[i] = arr[i];
    }

    for (; i < size + enlarge; i++) {
        res[i] = 0;
    }
    return res;
}

void insert(int arr[], int size, int index, int val) {
    int i = size;
    if (index < 0 || index >= size) {
        return;
    }

    for (; i > index; i--) {
        arr[i] = arr[i - 1];
    }

    arr[i] = val;
}

void delete(int arr[], int size, int index) {
    int i = index;
    if (index < 0 || index >= size) {
        return;
    }

    for (; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
}

void traverse(int arr[], int size) {
    printf("traverse arr ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int find(int arr[], int size, int val) {
    for (int i = 0; i < size; i ++) {
        if (val == arr[i]) {
            return i;
        }
    }

    return -1;
}

int main() {
    int size = 5;
    int arr[5];
    printf("arr = ");
    printArray(arr, size);

    int nums[5] = {1, 2, 3, 4, 5};
    printf("nums = ");
    printArray(nums, size);

    int rand = randomAccess(nums, size);
    printf("rand = %d\n", rand);

    int enlarge = 3;
    int *res = extend(nums, size, enlarge);
    size += enlarge;
    printf("res = ");
    printArray(nums, size);

    insert(res, size, 6, 3);
    printf("after insert res = ");
    printArray(res, size);

    delete(res, size, 2);
    printf("after delet res = ");
    printArray(res, size);

    traverse(res, size);
    
    int found = find(res, size, 3);
    printf("found = %d", found);

    return 0;
}
