#include <stdio.h>
#include <malloc.h>
#include "stack.h"


//first DFS to mark vertexes
int DFS(int **graph, int *visit, int vCnt, int vrt, int mark) {
    *(visit+vrt) = 0;

    for (int i = 0; i < vCnt; i++)
        if (*((*(graph+vrt))+i) == 1 && (*(visit+i) == -1))
            mark = DFS(graph, visit, vCnt, i, mark + 1) + 1;

    //mark - time when exit recursion
    *(visit+vrt) = mark;
}

//second DFS to find strong components
void RevDFS(int **graph, int *visit, int vCnt, int vrt, int mark) {
    //mark - index of component
    *(visit+vrt) = mark;

    for (int i = 0; i < vCnt; i++)
        if (*((*(graph+i))+vrt) == 1 && (*(visit+i) == 0))
            RevDFS(graph, visit, vCnt, i, mark);
}

//algorythm
int* Kosaraju(int **graph, int vCnt, int *mark) {
    STACK **res;
    int *visit;

    visit = (int*)malloc(vCnt*sizeof(int));
    for (int i = 0; i < vCnt; i++)
        *(visit+i) = -1;

    //first DFS
    for (int i = 0; i < vCnt; i++)
        if (*(visit+i) == -1)
            *mark = DFS(graph, visit, vCnt, i, *mark) + 1;

    STACK *stack = Create(0, 0);
    *mark = 0;

    //filling stack in descending order
    for (int i = 0; i < vCnt; i++) {
        Insert(stack, Create(i, *(visit+i)));
        *(visit+i) = 0;
    }

    //second DFS
    while (stack -> next != NULL) {
        int cur = Take(stack);
        if (*(visit+cur) == 0) {
            *mark += 1;
            RevDFS(graph, visit, vCnt, cur, *mark);
        }
    }
    free(stack);

    //creating and filling result array
    res = (STACK**)malloc((*mark)*sizeof(STACK*));
    for (int i = 0; i < (*mark); i++)
        *(res+i) = Create(0, 0);

    for (int i = 0; i < vCnt; i++)
        Add(*(res+(*(visit+i))-1), Create(i, 0));

    free(visit);

    return res;
}

int main()
{
    int vCnt, eCnt;
    int v1, v2;
    int **graph;
    int *mark;
    STACK **res;

    //getting input
    printf("Enter number of vertexes: ");
    scanf("%d", &vCnt);

    printf("Enter number of edges: ");
    scanf("%d", &eCnt);

    //creating adjacency matrix
    graph = (int**)malloc(vCnt*sizeof(int*));
    for (int i = 0; i < vCnt; i++) {
        *(graph+i) = (int*)malloc(vCnt*sizeof(int*));
        for (int j = 0; j < vCnt; j++)
            *((*(graph+i))+j) = 0;
    }

    //getting edges
    printf("Enter edges:\n");
    for (int i = 0; i < eCnt; i++) {
        scanf("%d %d", &v1, &v2);
        *((*(graph+v1))+v2) = 1;
    }

    mark = (int*)malloc(sizeof(int));
    *mark = 1;
    res = Kosaraju(graph, vCnt, mark);

    //output
    for (int i = 0; i < *mark; i++) {
        printf("Component %d: ", i+1);
        while ((*(res+i)) -> next != NULL)
            printf("%d ", Take(*(res+i)));
        printf("\n");
        free(*(res+i));
    }

    //clearing the memory
    free(res);
    for (int i = 0; i < vCnt; i++)
        free(*(graph+i));
    free(graph);

    return 0;
}
