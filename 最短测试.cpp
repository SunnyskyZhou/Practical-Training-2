  	 #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

   #define INFINITY        100000    //最大值
 #define MAX_VERTEX_NUM    30        //最大顶点数
   typedef enum {DG, DN, UDG, UDN} GraphKind; //{有向图，有向网，无向图，无向网}
 typedef struct ArcCell
{
     int weight;    //该弧相关信息的指针
 }ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM], PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM], ShortPathTable[MAX_VERTEX_NUM];
 typedef struct VertexType{
  char data[10];
  }VertexType;
  typedef struct{
     VertexType vexs[MAX_VERTEX_NUM];    //顶点向量
    AdjMatrix arcs;        //邻接矩阵
     int vexnum, arcnum;    //图的当前顶点数和弧数
 	     GraphKind kind;        //图的种类标志
 }MGraph;
 
 /*
  * 根据顶点信息， 返回该顶点在图中的位置， 如果返回-1表示顶点不存在
  */
 static int LocateVex(MGraph *G, char data[])
{
     int i = 0;
     for(i=0; i<G->vexnum; i++){
         if(!strncmp(G->vexs[i].data, data, strlen(G->vexs[i].data))){
             return i;
         }
    }
     return -1;
}
 
 /*
  * 用邻接矩阵作为存储结构，创建有向网
  */
 static int CreateGraphDN(MGraph *G)
 {
     printf("用邻接矩阵创建有向网,输入顶点数，弧数：");
      G->kind = DN;
     scanf("%d,%d", &G->vexnum, &G->arcnum);
     if(G->vexnum > MAX_VERTEX_NUM){
         printf("错误:顶点数不能超过%d!!\n", MAX_VERTEX_NUM);
        return -1;
     }
     int i = 0, j = 0, k = 0;
     char v1[10] = {0}, v2[10]={0}, info[10] = {0};
     char tmp[30] = {0};
     for(i=0; i<G->vexnum; i++){
         printf("输入第%d个顶点: ", i);
         memset(G->vexs[i].data, 0, sizeof(G->vexs[0].data));
         scanf("%s", G->vexs[i].data);
         for(j=0; j<G->vexnum; j++){
             G->arcs[i][j].weight = INFINITY;
         }

     }
     for(k=0; k<G->arcnum; k++){
         printf("输入第%d条弧(顶点1, 顶点2): ", k);
         memset(tmp, 0, sizeof(tmp));
         scanf("%s", tmp);
         sscanf(tmp, "%[^','],%[^','],%s[^\\n]", v1, v2, info);
         i = LocateVex(G, v1);
         j = LocateVex(G, v2);
         if(i<0 || j<0 || (!atoi(info))){
             printf("错误:顶点%s或者%s不存在, 或者权值信息%s不对!\n", v1, v2, info);
            return -1;
         }
         G->arcs[i][j].weight = atoi(info);
     }
     return 0;
 }
 static void printMatrix(int vexnum, VertexType vexs[], int (*arcs)[MAX_VERTEX_NUM])
 {
     int i = 0, j = 0;
     printf("\t");
     for(i=0; i<vexnum; i++){
         printf("%s\t", vexs[i].data);
     }
     printf("\n");
     for(i=0; i<vexnum; i++){
         printf("%s\t", vexs[i].data);
         for(j=0; j<vexnum; j++){
             if(arcs[i][j] == INFINITY){
                 printf("INF\t");
          }else{
                 printf("%d\t", arcs[i][j]);
             }
         }
         printf("\n");
     }
     return ;
 }
 
 static void printArchs(int vexnum, VertexType vexs[], AdjMatrix arcs)
 {
     int i = 0, j = 0;
     printf("\t");
     for(i=0; i<vexnum; i++){
         printf("%s\t", vexs[i].data);
     }
     printf("\n");
     for(i=0; i<vexnum; i++){
         printf("%s\t", vexs[i].data);
         for(j=0; j<vexnum; j++){
             if(arcs[i][j].weight == INFINITY){
                 printf("INF\t");
             }else{
                 printf("%d\t", arcs[i][j].weight);
             }
         }
         printf("\n");
     }
     return ;
 }
 
/*
 * Dijkstra迪杰斯特拉算法
  * 从有向网G的顶点v0出发，求v0到其余顶点v的最短路径P[v]及其带权长度D[v].weight
  * 若P[v][w].weight为TRUE(1)，则w是从v0到v当前求得最短路径上的顶点。
  * final[v]为TRUE(1)，当且仅当v属于S，即已经求得从v0到v的最短路径
 */
 void ShortestPath_DIJ(MGraph *G, int v0)
 {
     int v = 0;
     int w = 0;
 
    int j = 0;
    int final[MAX_VERTEX_NUM] = {0};
     int min = 0;
     int P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    ShortPathTable D;
 
     for(v=0; v<G->vexnum; ++v){
         D[v].weight = G->arcs[v0][v].weight;
        //设为空路径
         for(w=0; w<G->vexnum; ++w){
            P[v][w] = 0;
         }
         if(D[v].weight < INFINITY){
             P[v][v0] = 1;
             P[v][v] = 1;
         }
     }
     //初始化，v0顶点属于S集
     D[v0].weight = 0;
   final[v0] = 1;
    //开始主循环，每次求得v0到某个v顶点的最短路径，并加v到s集
    //其余G->vexnum-1个顶点
    for(j=1; j<G->vexnum; j++){
        //min存放当前离v0顶点最短的距离
         min = INFINITY;
         for(w=0; w<G->vexnum; w++){
           if(!final[w]){
                //顶点w在V-S中
                if(D[w].weight < min){
                     //顶点v0更近
                   min = D[w].weight;
                     v = w;
                }
            }
        }
         if(min == INFINITY)
             break;
       //离v0最短的顶点v加入S集合
        final[v] = 1;
         //更新当前最短路径和距离
        for (w = 0; w < G->vexnum; w++) {
            if (!final[w] && (min + G->arcs[v][w].weight < D[w].weight)) {
               //修改D[w]和P[w]，w属于V-S
                 D[w].weight = min + G->arcs[v][w].weight;
                 for(j=0; j<G->vexnum; j++){
                    P[w][j] = P[v][j];
                }
                P[w][w] = 1;
            }
        }
     }
 
     printf("\n打印最短路径:\n");
     printMatrix(G->vexnum, G->vexs, P);
 
     printf("\n打印%s到其余顶点的带权长度:\n", G->vexs[v0].data);
     for(k=0; i<G->vexnum; i++){
         if(D[i].weight == INFINITY){
             printf("%s,INF\t", G->vexs[i].data);
        }else {
             printf("%s,%d\t", G->vexs[i].data, D[i].weight);
         }
     }
     printf("\n");
     return ;
 }
 
 int main(int argc, char *argv[])
 {
     //以邻接矩阵为存储结构创建有向网
     MGraph G;
     if(CreateGraphDN(&G) < 0){
         return -1;
     }
     printf("\n打印该图中的信息:\n");
    printArchs(G.vexnum, G.vexs, G.arcs);
    //Dijkstra迪杰斯特拉算法求单源最短路径
     ShortestPath_DIJ(&G, 0);
     return 0;
}
//单源最短路径(Dijkstra)

