#include<stdio.h>
#include<stdlib.h>

typedef char VertexType;            /* 顶点类型由用户定义 */
typedef int EdgeType;               /* 边上的权值类型由用户定义 */
#define MAXVEX 100                  /* 最大顶点数，应由用户定义 */
#define INFINITY 65535              /* 用65535代表 ∞ */

typedef struct
{
    VertexType vexs[MAXVEX];         /* 顶点表 */
    EdgeType arc[MAXVEX][MAXVEX];   /* 邻接矩阵，可看作边表？？？*/
    int numVertexes, numEdges;      /* 图中当前的顶点数和边数 */
} MGraph;

/* 构建无向图的邻接矩阵表示 */
void CreatMGraph(MGraph *G) {
    int i, j, k, w;
    printf("please input the vertexs' number and edges' number(5 4):\n");        /* 输入顶点数和边数*/
    scanf("%d %d", &G->numVertexes, &G->numEdges);
    for (i = 0; i < G->numVertexes; i++){                                        /* 读入顶点信息，建立顶点表 */
        scanf(&G->vexs[i]);                                                      /* !!!这句话会把数组所有元素都赋值为0 */
        printf("%d\n", G->vexs[i]);
    }
    for (i = 0; i < G->numVertexes; i++){
        for (j = 0; j < G->numVertexes; j++){
            G->arc[i][j] = INFINITY;                                             /* 初始化一个邻接矩阵 */

            // 自己补充的代码
            if (i == j){
                G->arc[i][j] = 0;                                                /* 当i=j时为0 */
            }
        }
    }
    for (k = 0; k < G->numEdges; k++){                                   /* 读入numEdges条边 */
        printf("输入边(vi vj)上的下标i，下标j，和权w:\n");
        scanf("%d %d %d", &i, &j, &w);                                   /* 输入边(vi vj)上的权 */
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];                                     /* 因为是无向图，矩阵对称 */
    }
}

int main(){
    MGraph G;
    CreatMGraph(&G);

    return 0;
}