#include<stdio.h>
#include<stdlib.h>

typedef char VertexType;                     /* 顶点类型由用户定义 */
typedef int EdgeType;                        /* 边上的权值类型由用户定义 */
#define MAXVEX 100                           /* 最大顶点数，应由用户定义 */

typedef struct EdgeNode                      /* 边表结点 */
{
    int adjvex;                              /* 邻接点与域 */
    EdgeType weight;                         /* 用于存放权值，非网图不需要 */
    struct EdgeNode *next;                   /* 链域，指向下一个邻接点 */

} EdgeNode;

typedef struct VertexNode                    /* 顶点表结点 */
{
    VertexType data;                         /* 顶点域，存储顶点信息 */
    EdgeNode *firstedge;                     /* 边表头指针 */
} VertexNode, AdjList[MAXVEX];

typedef struct 
{
    AdjList adjList;
    int numVertexes, numEdges;               /* 图中当前顶点数和边数 */
} GraphAdjList;


/* 构建无向图的邻接矩阵表示 */
void CreatALGraph ( GraphAdjList *G ){
    int i, j, k;
    EdgeNode *e;
    printf("输入顶点数和边数：\n");
    scanf("%d %d", &G->numVertexes, &G->numEdges);          /* 输入顶点数和边数 */
    for (i = 0; i < &G->numVertexes; i++)
    {
        scanf(&G->adjList[i].data);                         /* 输入顶点信息 */
        G->adjList[i].firstedge = NULL;                     /* 将边表置为空表 */
    }

    // 邻接表
    for (k = 0; k < G->numEdges; k++)
    {
        printf("输入边（vi,vj）上的顶点序号");
        scanf("%d %d", &i, &j);                             /* 输入边（vi,vj）上的顶点序号 */
        
        // 运用头插法，用两段差不多的代码的原因是操作对象是***无向图***

        e = (EdgeNode *)malloc(sizeof(EdgeNode));           /* 向内存申请空间 */
        e->adjvex = j;                                      /* 邻接序号为j */
        e->next = G->adjList[i].firstedge;                  /* 将e指针指向当前顶点指向的结点 */
        G->adjList[i].firstedge = e;                        /* 将当前顶点的指针指向e */

        e = (EdgeNode *)malloc(sizeof(EdgeNode));           /* 向内存申请空间, 生成边表 */
        e->adjvex = i;                                      /* 邻接序号为i */
        e->next = G->adjList[j].firstedge;                  /* 将e指针指向当前顶点指向的结点 */
        G->adjList[j].firstedge = e;                        /* 将当前顶点的指针指向e */

    }

    // 逆邻接表
    

}

int main(){
    

    return 0;
}