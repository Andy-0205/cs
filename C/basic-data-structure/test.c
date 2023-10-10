#include <stdio.h>
#include <stdlib.h>

int main() {
    int **b = malloc(sizeof(b));
    b[0] = malloc(sizeof(int));
    *b[0]= 1;
    b[1] = malloc(sizeof(int));
    *b[1]= 2;
    printf("%d %d", *b[0], *b[1]);
    return 0;
}