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

// locateEdge()查找图中是否存在这条边，claimFindOut()是lacate的附属函数
void claimFindOut(EdgeNode *printOut)
{
    printf("the edge exists in Graph: %d | %d\n", printOut->ivex, printOut->jvex);
}

Status locateEdge (GraphAML *G, int vex1, int vex2)                                                            // 会不会一旦传入的指针是的接收参数是const *的情况下，指针已经变成不可修改                              
{
    int flag;
    flag = ERROR;

    // int vex1, vex2;
    // printf("please input the edge you wanna search(1 0):");
    // scanf("%d %d", &vex1, &vex2);
    // getchar();

    EdgeNode *alt = G->amList[vex1].firstedge;
    if ( !(vex1>G->numVertexes || vex1<0 || vex2>G->numVertexes || vex2<0) )                      // 如果输入的顶点有错误，则直接错误
    {
        while (alt)
        {
            //
            if ( (alt->ivex == vex1 && alt->jvex == vex2 ) || (alt->jvex == vex1 && alt->ivex == vex2) )
            {
                flag = OK;
                claimFindOut(alt);
                break;
            } else
            {
                if (alt->ivex == vex1)
                    alt = alt->iLink;
                else
                    alt = alt->jLink;
            }

            // if ( alt->ivex == vex1 )
            // {
            //     if ( alt->jvex == vex2 )
            //     {
            //         flag = OK;
            //         claimFindOut(alt);
            //         break;
            //     } else
            //     {
            //         alt = alt->iLink;
            //     }
            // } else if ( alt->jvex == vex1 )
            // {
            //     if ( alt->ivex == vex2 )
            //     {
            //         flag = OK;
            //         claimFindOut(alt);
            //         break;
            //     } else
            //     {
            //         alt = alt->jLink;
            //     }
            // } else 
            // {
            //     break;
            // }
        }
    }

    if ( !flag )
        printf("the edge has not existed\n");
    return flag;
} 

Status locateEdge_recur (EdgeNode *e, int *vex1, int *vex2)                             // 递归实现
{
    if ( !e )
    {
        return 0;
    }else if ((e->ivex == *vex1 && e->jvex == *vex2 ) || (e->jvex == *vex1 && e->ivex == *vex2))
    {
        claimFindOut(e);
        return 1;
    } else
    {
        if ( *vex1 == e->ivex)
        {
            locateEdge_recur(e->iLink, vex1, vex2);
        }else
        {
            locateEdge_recur(e->jLink, vex1, vex2);
        }
    }
    
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



// 新建一条边，inserExactNode()、connectEdge()是inserEdge()的附属函数

Status inserExactNode (GraphAML *G, int vex_order)                                   // 在改写数据的时候，用传递参数改成 GraphAML const *G 会报错，这样写的意思是数据不可修改
{
    int flag = OK;
    
    char ch;
    printf("please input data of new vex(char type):");
    scanf("%c", &ch);
    getchar();

    G->amList[vex_order].data = ch;
    G->amList[vex_order].firstedge = NULL;
    G->numVertexes++;

    return flag;

}

Status connectEdge (GraphAML *G, int vex1, int vex2)
{
    EdgeNode *p = (EdgeNode*)malloc(sizeof(EdgeNode));
    p->ivex = vex1;
    p->jvex = vex2;

    // 头插法插入新的边表结点
    p->iLink = G->amList[vex1].firstedge;
    G->amList[vex1].firstedge = p;

    p->jLink = G->amList[vex2].firstedge;
    G->amList[vex2].firstedge = p;
}

Status insertEdge (GraphAML *G)
{
    int flag = ERROR;
    int vex1, vex2;
    printf("please input two vex of new edge(0 1):");
    scanf("%d %d", &vex1, &vex2);
    getchar();

    int flag_retn;
    printf("locating whether the edge existed");
    flag_retn = locateEdge(G, vex1, vex2);
    if (flag_retn)
    {
        printf("this edge has been existing!");
        return flag;
    }

    if ( ((vex1>(MAXVEX-1)) || (vex1<0) || (vex2>(MAXVEX-1)) || (vex2<0) || (vex1 == vex2)) )
    {
        printf("Error!Input vex is out of vex-list boundry.");
    } else if ( vex1 < G->numVertexes && vex2 < G->numVertexes )
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

        {
            // char verify;
        // int cnt = 0;
        // int maxTimes = 1;
        // int mark = OK;                                                                            // 作为继续创建新的边结点的通行证

        // if (vex1 == G->numVertexes || vex2 == G->numVertexes)
        // {
        //     // 这个for循环其实可以不用，为了更直观的操作才加的，不加for循环不通行条件只有1
        //     for (; cnt>maxTimes; cnt++)
        //     {
        //         printf("Tips: input vex has not creat, do you wanna creat it or quit(y or n):");
        //         scanf("%c", &verify);
        //         getchar();

        //         if ( verify == 'n' )
        //         {
        //             printf("quit the inserEdge() function coz' unexisting vex!");
        //             mark = ERROR;                                                                    // 不通行条件1
        //             break;
        //         } else
        //         {
        //             printf("Now creating a new vex in Graph...\n");
        //             inserNode(G);
        //             printf("Finished!");
        //             break;
        //         }
        //     }

        //     // 超过最大输入次数提醒
        //     if (cnt > maxTimes)
        //     {
        //         printf("Wrong input for continuing, now ends the function!");
        //         mark = ERROR;                                                                        // 不通行条件2
        //     }      
        // }

        // // 若通行令为OK，则创建新的边表结点
        // if ( mark == OK )
        // {
        //     EdgeNode *p = (EdgeNode*)malloc(sizeof(EdgeNode));
        //     p->ivex = vex1;
        //     p->jvex = vex2;

        //     // 头插法插入新的边表结点
        //     p->iLink = G->amList[vex1].firstedge;
        //     G->amList[vex1].firstedge = p;

        //     p->jLink = G->amList[vex2].firstedge;
        //     G->amList[vex2].firstedge = p;
        //     flag = OK;
        // }
        }
    } else 
    {                                               // 输入的边顶点至少一个还没新建
        char verify;
        printf("At least one vex has not creat yet, do you wanna creat it or quit(y or n):");
        scanf("%c", &verify);
        getchar();

        if ( verify!='y' )
        {
            return flag;
        }

        if ( vex1>=G->numVertexes && vex2<G->numVertexes)
        {
            inserExactNode(G, vex1);
        } else if (vex2>=G->numVertexes && vex1<G->numVertexes)
        {
            inserExactNode(G, vex2);
        } else
        {
            inserExactNode(G, vex1);
            inserExactNode(G, vex2);
        }
        
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

    return flag;
}

// 删除顶点
Status deletVex (GraphAML *G)
{
    int flag = ERROR;
    


    return flag;
}

// 删除某条边


Status deleteEdge (GraphAML *G, int vex1, int vex2)
{
    int flag = ERROR;
    // int mark_retn;
    // mark_retn = locateEdge(G, vex1, vex2);


    EdgeNode *cur = G->amList[vex1].firstedge;
    EdgeNode *pre = cur;
    int cnt = 0;                                                    // 看循环赋值了几次
    if ( !(vex1>MAXVEX-1|| vex1<0 || vex2>MAXVEX-1 || vex2<0) )                      // 如果输入的顶点有错误，则直接错误
    {
        while (cur)
        {
            //
            if ( (cur->ivex == vex1 && cur->jvex == vex2 ) || (cur->jvex == vex1 && cur->ivex == vex2) )
            {
                claimFindOut(cur);
                if (cnt<1)
                {
                    if ( cur->iLink )
                    {
                        if (cur->iLink->ivex == vex1 || cur->iLink->jvex == vex1)
                        {
                            pre = cur->iLink;
                            free(cur);
                            flag = OK;
                            break;
                        }
                    }
                    else if ( cur->jLink )
                    {
                        if (cur->jLink->ivex == vex1 || cur->jLink->jvex == vex1)
                        {
                            pre = cur->jLink;
                            free(cur);
                            flag = OK;
                            break;
                        }
                    } else
                    {
                        pre = NULL;
                    }
                } else                                                            // 循环超过一次的时候
                {
                    if (pre->iLink == cur)
                    {
                        if ( cur->iLink )
                        {
                            if (cur->iLink->ivex == vex1 || cur->iLink->jvex == vex1)
                            {
                                pre->iLink = cur->iLink;
                                free(cur);
                                flag = OK;
                                break;
                            }
                        }
                        else if ( cur->jLink )
                        {
                            if (cur->jLink->ivex == vex1 || cur->jLink->jvex == vex1)
                            {
                                pre->iLink = cur->jLink;
                                free(cur);
                                flag = OK;
                                break;
                            }
                        } else
                        {
                            pre->iLink = NULL;
                            break;
                        }
                    } else
                    {
                        if ( cur->iLink )
                        {
                            if (cur->iLink->ivex == vex1 || cur->iLink->jvex == vex1)
                            {
                                pre->jLink = cur->iLink;
                                free(cur);
                                flag = OK;
                                break;
                            }
                        }
                        else if ( cur->jLink )
                        {
                            if (cur->jLink->ivex == vex1 || cur->jLink->jvex == vex1)
                            {
                                pre->jLink = cur->jLink;
                                free(cur);
                                flag = OK;
                                break;
                            }
                        } else
                        {
                            pre->jLink = NULL;
                            break;
                        }
                    }
                    
                }
            } else
            {
                if (cur->ivex == vex1)
                {
                    pre = cur;
                    cur = cur->iLink;
                } else
                {
                    pre = cur;
                    cur = cur->jLink;
                }
                    
            }

            cnt++;
        }

    }

    return flag;
}



int main(){
    GraphAML one;
    CreatALGraph(&one);
    printAMGraph(&one);

    // 
    int vex1_m, vex2_m;
    printf("please input the edge you wanna search(1 0):");
    scanf("%d %d", &vex1_m, &vex2_m);
    getchar();
    // locateEdge(&one, vex1_m, vex2_m);
    locateEdge_recur(one.amList[vex1_m].firstedge, &vex1_m, &vex2_m);

    /*
    inserNode(&one);
    printAMGraph(&one);

    insertEdge(&one);
    printAMGraph(&one);
    */

    // 删除边操作
    /*
    printf("please input the edge you wanna delete(1 0):");
    scanf("%d %d", &vex1_m, &vex2_m);
    getchar();
    deleteEdge(&one, vex1_m, vex2_m);
    */

    return 0;
}
