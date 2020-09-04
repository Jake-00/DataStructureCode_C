// ==============================================================================================  //
// 邻接多重表
// 参考博客：https://blog.csdn.net/bible_reader/article/details/71250117                            //
// 其中输入时遇到回车符会被录入进下一个输入的字符变量，解决办法是在 scanf() 后放一个 getchar() 吸收回车符,
// 参考博客：https://www.cnblogs.com/czysgr/p/11521641.html
// ==============================================================================================  //


#include<stdio.h>
#include<stdlib.h>

#define Status int
#define OK 1
#define ERROR 0

typedef char VertexType;                     /* 顶点类型由用户定义 */
typedef int EdgeType;                        /* 边上的权值类型由用户定义 */
#define MAXVEX 100                           /* 最大顶点数，应由用户定义 */

typedef struct EdgeNode                      /* 边表结点 */
{

    int ivex;                                /* 顶点下标i */
    int jvex;                                /* 顶点下标j */
    EdgeType weight;                         /* 用于存放权值，非网图不需要 */
    struct EdgeNode *iLink;                  /* 链域，指向依附顶点ivex的下条边 */
    struct EdgeNode *jLink;                  /* 链域，指向依附顶点jvex的下条边*/
    int mark;                                /* 判断是否遍历过，无则0，有则1 */
} EdgeNode;

typedef struct VertexNode                    /* 顶点表结点 */
{
    VertexType data;                         /* 顶点域，存储顶点信息 */
    struct EdgeNode *firstedge;                     /* 边表头指针 */
} VertexNode, AMList[MAXVEX];

typedef struct 
{
    AMList amList;
    int numVertexes, numEdges;               /* 图中当前顶点数和边数 */
} GraphAML;


/* 构建无向图的邻接矩阵表示 */
void CreatALGraph (GraphAML *G){
    int i, j, k;
    EdgeNode *e;
    printf("输入顶点数和边数：\n");
    // char ch;                                             /* 接受回车符 */
    scanf("%d %d", &G->numVertexes, &G->numEdges);          /* 输入顶点数和边数 */
    printf("\n");
    getchar();
    for (i = 0; i < G->numVertexes; i++)
    {
        printf("please the each VertexNode's data:");
        scanf("%c", &G->amList[i].data);
        getchar();                                         /* getchar()是为了接收回车换行符 */
        // printf("\n");
        G->amList[i].firstedge = NULL;                     /* 将边表置为空表 */
    }

    // 邻接多重表
    for (k = 0; k < G->numEdges; k++)
    {
        printf("输入边（vi,vj）上的顶点序号:"); 
        scanf("%d %d", &i, &j);                            /* 输入边（vi,vj）上的顶点序号 */
		getchar();                                         /* getchar()是为了接收回车换行符 */
		
        // 建立边结点
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->ivex = i;
        e->jvex = j;

        // 采用头插法链接新结点
        e->iLink = G->amList[i].firstedge;
        G->amList[i].firstedge = e;

        e->jLink = G->amList[j].firstedge;
        G->amList[j].firstedge = e;
    }
}

void printAMGraph (GraphAML *G)
{
    int cnt = 0;
    
    for (; cnt < G->numVertexes; cnt++)
    {
        printf("%d %c:", cnt, G->amList[cnt].data);
        EdgeNode *p = G->amList[cnt].firstedge;
        while (p)
        {
            printf("-->|%d|%d|", p->ivex, p->jvex);

            if (p->ivex == cnt)
            {
                p = p->iLink;
            } else 
            {
                p = p->jLink;
            }
        }
        printf("-->NULL\n");
    }
}

void claimFindOut(EdgeNode *printOut)
{
    printf("the edge exists in Graph: %d | %d\n", printOut->ivex, printOut->jvex);
}

Status locateEdge (GraphAML const *G)                                                            // 会不会一旦传入的指针是的接收参数是const *的情况下，指针已经变成不可修改                              
{
    int vex1, vex2, flag;
    flag = ERROR;
    printf("please input the edge you wanna search(1 0):");
    scanf("%d %d", &vex1, &vex2);
    getchar();

    EdgeNode *alt = G->amList[vex1].firstedge;
    if ( !(vex1>G->numVertexes || vex1<0 || vex2>G->numVertexes || vex2<0) )                      // 如果输入的顶点有错误，则直接错误
    {
        while (alt)
        {
            if ( alt->ivex == vex1 )
            {
                if ( alt->jvex == vex2 )
                {
                    flag = OK;
                    claimFindOut(alt);
                    break;
                } else
                {
                    alt = alt->iLink;
                }
            } else if ( alt->ivex == vex2 )
            {
                if ( alt->jvex == vex1 )
                {
                    flag = OK;
                    claimFindOut(alt);
                    break;
                } else
                {
                    alt = alt->jLink;
                }
            }
        }
    }

    return flag;
} 

// 插入新点
Status inserNode (GraphAML *G)                                   // 在改写数据的时候，用传递参数改成 GraphAML const *G 会报错，这样写的意思是数据不可修改
{
    int flag = OK;
    if (G->numVertexes == MAXVEX - 1 )
    {
        flag = ERROR;
    } else 
    {
        char ch;
        printf("please input data of new vex(char type):");
        scanf("%c", &ch);
        getchar();

        G->amList[G->numVertexes].data = ch;
        G->amList[G->numVertexes].firstedge = NULL;
        G->numVertexes++;
    }

    return flag;

}

// 新建一条边
Status insertEdge (GraphAML *G)
{
    int flag = ERROR;
    int vex1, vex2;
    printf("please input two vex of new edge(0 1):");
    scanf("%d %d", &vex1, &vex2);
    getchar();

    if ( !(vex1>(MAXVEX-1) || vex1<0 || vex2>(MAXVEX-1) || vex2<0 || vex1 == vex2) )
    {
        printf("Error!Input vex is out of vex-list boundry.");
    } else if ( vex1 <= G->numVertexes || vex2 <= G->numVertexes )
    {
        char verify;
        int cnt = 0;
        int maxTimes = 1;
        int mark = OK;                                                                            // 作为继续创建新的边结点的通行证

        if (vex1 == G->numVertexes || vex2 == G->numVertexes)
        {
            // 这个for循环其实可以不用，为了更直观的操作才加的，不加for循环不通行条件只有1
            for (; cnt>maxTimes; cnt++)
            {
                printf("Tips: input vex has not creat, do you wanna creat it or quit(y or n):");
                scanf("%c", &verify);
                getchar();

                if ( verify == 'n' )
                {
                    printf("quit the inserEdge() function coz' unexisting vex!");
                    mark = ERROR;                                                                    // 不通行条件1
                    break;
                } else
                {
                    printf("Now creating a new vex in Graph...\n");
                    inserNode(G);
                    printf("Finished!");
                    break;
                }
            }

            // 超过最大输入次数提醒
            if (cnt > maxTimes)
            {
                printf("Wrong input for continuing, now ends the function!");
                mark = ERROR;                                                                        // 不通行条件2
            }

            // 若通行令为OK，则创建新的边表结点
            if ( mark == OK )
            {
                EdgeNode *p = (EdgeNode*)malloc(sizeof(EdgeNode));
                p->ivex = vex1;
                p->jvex = vex2;

                // 头插法插入新的边表结点
                p->iLink = G->amList[vex1].firstedge;
                G->amList[vex1].firstedge = p;

                p->jLink = G->amList[vex2].firstedge;
                G->amList[vex2].firstedge = p;
                flag = OK;
            }      
        }
    }

    return flag;
}





int main(){
    GraphAML one;
    CreatALGraph(&one);
    printAMGraph(&one);
    locateEdge(&one);
    inserNode(&one);
    printAMGraph(&one);

    return 0;
}
