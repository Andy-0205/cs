#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

/* Get a list node with specific value from a linked list */
ListNode *getListNode(ListNode *head, int val) {
    while (head != NULL && head->val != val) {
        head = head->next;
    }
    return head;
}

/* 构造函数，初始化一个新节点 */
ListNode *newListNode(int val) {
    ListNode *new = malloc(sizeof(ListNode));
    assert(new);
    new->next = NULL;
    new->val = val;
    return new;
}

/* Generate a linked list with a vector */
ListNode *arrToLinkedList(const int *arr, size_t size) {
    assert(arr && size);
    ListNode *head = newListNode(arr[0]);
    ListNode *next = head;
    for (int i = 1; i < size; i++) {
        next->next = newListNode(arr[i]);
        next = next->next;
    }

    return head;
}

/* 在链表的节点 n0 之后插入节点 P */
void insert(ListNode *n0, ListNode *P) {
    assert(n0 && P);
    ListNode *next = n0->next;
    n0->next = P;
    P->next = next;
}

/* 删除链表的节点 n0 之后的首个节点 */
// 注意：stdio.h 占用了 remove 关键词
void removeNode(ListNode *n0) {
    assert(n0);
    ListNode *next = n0->next;
    if (next) {
        n0->next = next->next;
        free(next);
    }
}

/* 访问链表中索引为 index 的节点 */
ListNode *access(ListNode *head, int index) {
    assert(head);
    int i = 0;
    while (i < index && head) {
        head = head->next;
        i++;
    }
    return head;
}

/* 在链表中查找值为 target 的首个节点 */
int find(ListNode *head, int target) {
    assert(head);
    int i = 0;
    while (head) {
        if (head->val == target) {
            return i;
        }
        head = head->next;
        i++;
    }
    return -1;
}

/* Driver Code */
int main() {
    /* 初始化链表 */
    // 初始化各个节点
    ListNode *n0 = newListNode(1);
    ListNode *n1 = newListNode(3);
    ListNode *n2 = newListNode(2);
    ListNode *n3 = newListNode(5);
    ListNode *n4 = newListNode(4);
    // 构建引用指向
    n0->next = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    printf("初始化的链表为\r\n");
    printLinkedList(n0);

    /* 插入节点 */
    insert(n0, newListNode(0));
    printf("插入节点后的链表为\r\n");
    printLinkedList(n0);

    /* 删除节点 */
    removeNode(n0);
    printf("删除节点后的链表为\r\n");
    printLinkedList(n0);

    /* 访问节点 */
    ListNode *node = access(n0, 3);
    printf("链表中索引 3 处的节点的值 = %d\r\n", node->val);

    /* 查找节点 */
    int index = find(n0, 2);
    printf("链表中值为 2 的节点的索引 = %d\r\n", index);

    int nums[7] = {0, 1, 2, 3, 4, 5, 6};
    ListNode *new = arrToLinkedList(nums, 7);
    printf("使用nums构造linklist\r\n");
    printLinkedList(new);
    return 0;
}
