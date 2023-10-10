#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* 哈希表默认数组大小 */
#define HASH_MAP_DEFAULT_SIZE 100

/* 键值对 int->string */
struct pair {
    int key;
    char *val;
};

typedef struct pair pair;

/* 用于表示键值对、键、值的集合 */
struct mapSet {
    void *set;
    int len;
};

typedef struct mapSet mapSet;

/* 基于数组简易实现的哈希表 */
struct ArrayHashMap {
    pair *buckets[HASH_MAP_DEFAULT_SIZE];
};

typedef struct ArrayHashMap ArrayHashMap;

/* 哈希表初始化函数 */
ArrayHashMap *newArrayHashMap() {
    ArrayHashMap *new = malloc(sizeof(ArrayHashMap));
    assert(new);
    for (int i = 0; i < HASH_MAP_DEFAULT_SIZE; i++) {
        new->buckets[i] = NULL;
    }
    return new;
}

/* 哈希函数 */
int hashFunc(int key) {
    int index = key % HASH_MAP_DEFAULT_SIZE;
    return index;
}

/* 查询操作 */
const char *get(const ArrayHashMap *d, const int key) {
    assert(d);
    int hashkey = hashFunc(key);
    const pair *node = d->buckets[hashkey];
    if (node) {
        return node->val;
    } else {
        return NULL;
    }
}

/* 添加操作 */
void put(ArrayHashMap *d, const int key, const char *val) {
    assert(d);
    int hashkey = hashFunc(key);
    pair *new = malloc(sizeof(pair));
    assert(new);
    new->val = malloc(sizeof(strlen(val) + 1));
    assert(new->val);
    new->key = key;
    strcpy(new->val, val);
    d->buckets[hashkey] = new;
}

/* 删除操作 */
void removeItem(ArrayHashMap *d, const int key) {
    assert(d);
    int hashkey = hashFunc(key);
    pair *node = d->buckets[hashkey];
    if (node) {
        free(node->val);
        free(node);
    }
    d->buckets[hashkey] = NULL;
}

/* 获取所有键值对 */
void pairSet(ArrayHashMap *d, mapSet *set) {
    assert(d && set);
    pair *tmp;
    int count = 0;
    int index = 0;
    int i;
    for (i = 0; i < HASH_MAP_DEFAULT_SIZE; i++) {
        if (d->buckets[i]) {
            count++;
        }
    }

    pair *pairset = malloc(sizeof(pair) * count);
    assert(pairset);

    for (i = 0; i < HASH_MAP_DEFAULT_SIZE; i++) {
        tmp = d->buckets[i];
        if (tmp) {
            pairset[index].key = tmp->key;
            pairset[index].val = malloc(strlen(tmp->val) + 1);
            assert(pairset[index].val);
            strcpy(pairset[index].val, tmp->val);
            index++;
        }
    }
    set->len = count;
    set->set = pairset;
}

/* 获取所有键 */
void keySet(ArrayHashMap *d, mapSet *set) {
    assert(d && set);
    pair *tmp;
    int count = 0;
    int index = 0;
    int i;
    for (i = 0; i < HASH_MAP_DEFAULT_SIZE; i++) {
        if (d->buckets[i]) {
            count++;
        }
    }

    int *keyset = malloc(sizeof(int) * count);
    assert(keyset);

    for (i = 0; i < HASH_MAP_DEFAULT_SIZE; i++) {
        tmp = d->buckets[i];
        if (tmp) {
            keyset[index] = tmp->key;
            index++;
        }
    }
    set->len = count;
    set->set = keyset;
}

/* 获取所有值 */
void valueSet(ArrayHashMap *d, mapSet *set) {
    assert(d && set);
    pair *tmp;
    int count = 0;
    int index = 0;
    int i;
    for (i = 0; i < HASH_MAP_DEFAULT_SIZE; i++) {
        if (d->buckets[i]) {
            count++;
        }
    }

    char **valueset = malloc(sizeof(char *) * count);
    assert(valueset);

    for (i = 0; i < HASH_MAP_DEFAULT_SIZE; i++) {
        tmp = d->buckets[i];
        if (tmp) {
            valueset[index]= tmp->val;
            index++;
        }
    }
    set->len = count;
    set->set = valueset;
}

/* 打印哈希表 */
void print(ArrayHashMap *d) {
    assert(d);
    mapSet set;
    pairSet(d, &set);
    pair *node = (pair *)set.set;
    for (int i = 0; i < set.len; i++) {
        printf("[%d] = %s, ", node[i].key, node[i].val);
        free(node[i].val);
    }
    printf("\n");
    free(set.set);
}

/* Driver Code */
int main() {
    /* 初始化哈希表 */
    ArrayHashMap *map = newArrayHashMap();

    /* 添加操作 */
    // 在哈希表中添加键值对 (key, value)
    put(map, 12836, "小哈");
    put(map, 15937, "小啰");
    put(map, 16750, "小算");
    put(map, 13276, "小法");
    put(map, 10583, "小鸭");
    printf("\n添加完成后，哈希表为\nKey -> Value\n");
    print(map);

    /* 查询操作 */
    // 向哈希表输入键 key ，得到值 value
    const char *name = get(map, 15937);
    printf("\n输入学号 15937 ，查询到姓名 %s\n", name);

    /* 删除操作 */
    // 在哈希表中删除键值对 (key, value)
    removeItem(map, 10583);
    printf("\n删除 10583 后，哈希表为\nKey -> Value\n");
    print(map);

    /* 遍历哈希表 */
    int i;

    printf("\n遍历键值对 Key->Value\n");
    print(map);

    mapSet set;

    keySet(map, &set);
    int *keys = (int *)set.set;
    printf("\n单独遍历键 Key\n");
    for (i = 0; i < set.len; i++) {
        printf("%d\n", keys[i]);
    }
    free(set.set);

    valueSet(map, &set);
    char **vals = (char **)set.set;
    printf("\n单独遍历键 Value\n");
    for (i = 0; i < set.len; i++) {
        printf("%s\n", vals[i]);
    }
    free(set.set);

    return 0;
}
