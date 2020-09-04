#include<stdio.h>
#include<stdlib.h>

// 参考这篇博客
// http://data.biancheng.net/view/38.html
typedef char VertexType;                     /* 顶点类型由用户定义 */
typedef int EdgeType;                        /* 边上的权值类型由用户定义 */
#define MAXVEX 100                           /* 最大顶点数，应由用户定义 */

typedef struct EdgeNode                      /* 边表结点 */
{
    int tailVex;                             /* 弧起点的顶点表下标 */
    int headVex;                             /* 弧终点的顶点表下标 */
    struct EdgeNode *headLink;               /* 边表指针域，指向同头（或终点）*/
    struct EdgeNode *tailLink;               /* 边表指针域，指向同尾（或起点）*/
} EdgeNode;

typedef struct VertexNode                    /* 顶点表结点 */
{
    VertexType data;                         /* 顶点数据 */
    EdgeNode *firstin;                       /* 顶点表指针域，指向入边表的第一个结点 */
    EdgeNode *firstout;                      /* 顶点表指针域，指向出边表的第一个结点 */
} VertexNode, OtList[MAXVEX];

typedef struct
{
    OtList otlist;                           
    int numEdges, numVertexes;                /* 图中当前顶点数和边数 */
} GraphOtho;


// 构造有向图的十字链表
void InitOthoGraph (GraphOtho *G)
{   
    // 输入有向图的边数和顶点数
    EdgeNode *e;
    printf("输入顶点数和边数：\n");
    scanf("%d %d", &(G->numVertexes), &(G->numEdges));          /* 输入顶点数和边数 */
    
    // 使用一维数组存储顶点数据，并初始化首个入边和首个出边指针 
    for (int i = 0; i < G->numVertexes; i++)
    {
        printf("please the each VertexNode's data:\n");
        scanf("%c", &G->otlist[i].data);
        G->otlist[i].firstin = NULL;
        G->otlist[i].firstout = NULL;
    }

    // 构建十字链表
    int i, j;
    for (int k = 0; k < G->numEdges; k++)
    {
        printf("输入边（vi,vj）上的顶点序号");
        scanf("%d %d", &i, &j);                             /* 输入边（vi,vj）上的顶点序号 */

        // 建立弧结点
        e = (VertexNode *)malloc(sizeof(VertexNode));
        e->tailVex = i;
        e->headVex = j;

        // 采用头插法插入新的结点
        e->headLink = G->otlist[j].firstin;
        e->tailLink = G->otlist[i].firstout;
        G->otlist[j].firstin = G->otlist[i].firstout = e;

    }
}

// 计算某顶点的入度
int calVertexOutDegree (GraphOtho *G, int locateNum)
{
    int cnt = 0;
    if (G->otlist[locateNum].firstin)
    {
        cnt++;
        EdgeNode *p = G->otlist[locateNum].firstin;
        for (; p->headLink;)
        {
            cnt++;
            p = p->headLink;
        }
    }
    return cnt;
}

// 计算某顶点的出度
int calVertexInDegreee (GraphOtho *G, int locateNum)
{
    int cnt = 0;
    EdgeNode *p = G->otlist[locateNum].firstout;
    for (; p->tailLink;)
    {
        cnt++;
        p = p->tailLink;
    }
    return cnt;
}

int main (){


    return 0;
}