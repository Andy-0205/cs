#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DEFAULT_CAPACITY 8
#define DEFAULT_EXTEND_RATIO 2

struct arrayList
{
    int *nums;
    int capacity;
    int size;
    int extendRatio;
};

typedef struct arrayList arrayList;

arrayList *newArrayList() {
    arrayList *new = (arrayList *)malloc(sizeof(arrayList));
    new->nums = (int *)malloc(sizeof(int) * DEFAULT_CAPACITY);
    new->capacity = DEFAULT_CAPACITY;
    new->size = 0;
    new->extendRatio = DEFAULT_EXTEND_RATIO;
    return new;
}

void deleteArrayList(arrayList *list) {
    free(list->nums);
    free(list);
}

void extendCapacity(arrayList *list) {
    list->nums = (int *)realloc(list->nums, sizeof(int) * list->capacity * list->extendRatio);
    list->capacity = list->capacity * list->extendRatio;
    list->size = list->size;
}

void add(arrayList *list, int val) {
    if (list->size >= list->capacity) {
        extendCapacity(list);
    }

    list->nums[list->size] = val;
    list->size++;
}

void printArrayList(arrayList *list) {
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->nums[i]);
    }
    printf("capacity = %d, size = %d \n", list->capacity, list->size);
}

void insert(arrayList *list, int index, int val) {
    assert(index >= 0 && index < list->size);
    if (list->size >= list->capacity) {
        extendCapacity(list);
    }

    for (int i = list->size; i > index; i--) {
        list->nums[i] = list->nums[i - 1];
    }
    list->nums[index] = val;
    list->size++;
}

void delete(arrayList *list, int index) {
    assert(index >= 0 && index < list->size);
    for (int i = index; i <= list->size - 1; i++) {
        list->nums[i] = list->nums[i + 1];
    }
    list->size--;
}

int get(arrayList *list, int index) {
    assert(index >= 0 && index < list->size);
    return list->nums[index];
}

void set(arrayList *list, int index, int val) {
    if (index > list->size - 1) {
        return;
    }

    list->nums[index] = val;
}

int main() {
    arrayList *list = newArrayList();
    add(list, 1);
    add(list, 2);
    add(list, 3);
    add(list, 4);
    add(list, 5);
    add(list, 6);

    printArrayList(list);
   
    insert(list, 6, 7);
    printArrayList(list);

    insert(list, 0, -1);
    printArrayList(list);

    insert(list, 0, -2);
    printArrayList(list);

    delete(list, 0);
    printArrayList(list);

    set(list, 0, -3);
    printArrayList(list);

    printf("get = %d\n", get(list, 0));

}