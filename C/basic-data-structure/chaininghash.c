#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define HASH_DEFAULT_SIZE 20
#define HASH_DEFAULT_RATIO 2
#define HASH_DEFAULT_THRESH 0.666667

/* 键值对 int->string */
struct node {
    int key;
    char *val;
    struct node *next; // 下一个元素
};

typedef struct node Node;

struct pair {
    Node *node; // 键值对节点
};

typedef struct pair Pair;

/* 基于数组简易实现的链式地址哈希表 */
struct hashMapChaining {
    int size;         // 键值对数量
    int capacity;     // 哈希表容量
    double loadThres; // 触发扩容的负载因子阈值
    int extendRatio;  // 扩容倍数
    Pair *buckets;    // 桶数组
};

typedef struct hashMapChaining hashMapChaining;

// 函数声明
void extend(hashMapChaining *hashmap);

/* 初始化桶数组 */
hashMapChaining *newHashMapChaining() {
    hashMapChaining *new = malloc(sizeof(hashMapChaining));
    assert(new);
    new->buckets = malloc(sizeof(Pair) * HASH_DEFAULT_SIZE);
    assert(new->buckets);
    memset(new->buckets, 0, sizeof(Pair) * HASH_DEFAULT_SIZE);
    new->size = 0;
    new->capacity = HASH_DEFAULT_SIZE;
    new->loadThres = HASH_DEFAULT_THRESH;
    new->extendRatio = HASH_DEFAULT_RATIO;
    return new;
}

/* 销毁哈希表 */
void delHashMapChaining(hashMapChaining *hashmap) {
    assert(hashmap);
    Pair *pair;
    Node *next;
    for (int i = 0; i < hashmap->capacity; i++) {
        pair = &hashmap->buckets[i];
        next = pair->node;
        while (pair->node)
        {
            next = next->next;
            free(pair->node->val);
            free(pair->node);
            pair->node = next;
        }
        
    }
    free(hashmap->buckets);
    free(hashmap);
}

/* 哈希函数 */
int hashFunc(hashMapChaining *hashmap, const int key) {
    return key % hashmap->capacity;
}

/* 负载因子 */
double loadFactor(hashMapChaining *hashmap) {
    return (double)hashmap->size / (double)hashmap->capacity;
}

/* 查询操作 */
const char *get(hashMapChaining *hashmap, const int key) {
    assert(hashmap);
    int hashkey = hashFunc(hashmap, key);
    Pair *pair = &hashmap->buckets[hashkey];
    if (pair->node) {
        while(pair->node) {
            if (pair->node->key == key) {
                return pair->node->val;
            }
            pair->node = pair->node->next;
        }
    } 

    return NULL;
}

/* 添加操作 */
void put(hashMapChaining *hashmap, const int key, char *val) {
    assert(hashmap && val);
    if (loadFactor(hashmap) > hashmap->loadThres) {
        extend(hashmap);
    }

    int hashkey = hashFunc(hashmap, key);
    Pair *pair = &hashmap->buckets[hashkey];
    Node *new = malloc(sizeof(Node));
    assert(new);
    new->key = key;
    new->val = malloc(strlen(val) + 1);
    assert(new->val);
    strcpy(new->val, val);
    new->next = NULL;
    Node *prev = NULL;
    Node *current = pair->node;
    if (pair->node) {
        while(current) {
            if (current->key == key) {
                if (prev) {
                    prev->next = new;
                    new->next = current->next;
                } else {
                    pair->node = new;
                }

                free(current->val);
                free(current);
                return;
            }
            prev = current;
            current = current->next;
        }

        if (prev) {
            prev->next = new;
        } else {
            pair->node = new;
        }
    } else {
        pair->node = new;
    }
    hashmap->size++;
}

/* 删除操作 */
void removeItem(hashMapChaining *hashmap, int key) {
    assert(hashmap);
    int hashkey = hashFunc(hashmap, key);
    Pair *pair = &hashmap->buckets[hashkey];
    Node *prev = NULL;
    Node *current = pair->node;
    while(current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                pair->node = current->next;
            }
            free(current->val);
            free(current);
            hashmap->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

/* 扩容哈希表 */
void extend(hashMapChaining *hashmap) {
    assert(hashmap);
    int newsize = hashmap->capacity * hashmap->extendRatio;
    Pair *newbucket = malloc(sizeof(Pair) * newsize);
    assert(newbucket);
    memset(newbucket, 0, sizeof(Pair) * newsize);
    Pair *pair;
    int hashkey;
    int oldsize = hashmap->capacity;
    for (int i = 0; i < oldsize; i++) {
        pair = &hashmap->buckets[i];
        if (pair->node) {
            hashkey = hashFunc(hashmap, pair->node->key);
            newbucket[hashkey].node = pair->node;
        }
    }
    free(hashmap->buckets);
    hashmap->capacity = newsize;
    hashmap->buckets = newbucket;
}

/* 打印哈希表 */
void print(hashMapChaining *hashmap) {
    for (int i = 0; i < hashmap->capacity; i++) {
        printf("[");
        Pair *pair = &hashmap->buckets[i];
        Node *node = pair->node;
        while (node != NULL) {
            if (node->val != NULL) {
                printf("%d->%s, ", node->key, node->val);
            }
            node = node->next;
        }
        printf("]\n");
    }
    return;
}

/* Driver Code */
int main() {
    /* 初始化哈希表 */
    hashMapChaining *map = newHashMapChaining();

    /* 添加操作 */
    // 在哈希表中添加键值对 (key, value)
    put(map, 12836, "小哈");
    put(map, 15937, "小啰");
    put(map, 16750, "小算");
    put(map, 13276, "小法");
    put(map, 10583, "小鸭");
    put(map, 10583, "小鸭1");
    printf("\n添加完成后，哈希表为\nKey -> Value\n");
    print(map);

    /* 查询操作 */
    // 向哈希表输入键 key ，得到值 value
    const char *name = get(map, 13276);
    printf("\n输入学号 13276 ，查询到姓名 %s\n", name);

    /* 删除操作 */
    // 在哈希表中删除键值对 (key, value)
    removeItem(map, 12836);
    printf("\n删除 12836 后，哈希表为\nKey -> Value\n");
    print(map);

    delHashMapChaining(map);
    return 0;
}
