  	 #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

   #define INFINITY        100000    //���ֵ
 #define MAX_VERTEX_NUM    30        //��󶥵���
   typedef enum {DG, DN, UDG, UDN} GraphKind; //{����ͼ��������������ͼ��������}
 typedef struct ArcCell
{
     int weight;    //�û������Ϣ��ָ��
 }ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM], PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM], ShortPathTable[MAX_VERTEX_NUM];
 typedef struct VertexType{
  char data[10];
  }VertexType;
  typedef struct{
     VertexType vexs[MAX_VERTEX_NUM];    //��������
    AdjMatrix arcs;        //�ڽӾ���
     int vexnum, arcnum;    //ͼ�ĵ�ǰ�������ͻ���
 	     GraphKind kind;        //ͼ�������־
 }MGraph;
 
 /*
  * ���ݶ�����Ϣ�� ���ظö�����ͼ�е�λ�ã� �������-1��ʾ���㲻����
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
  * ���ڽӾ�����Ϊ�洢�ṹ������������
  */
 static int CreateGraphDN(MGraph *G)
 {
     printf("���ڽӾ��󴴽�������,���붥������������");
      G->kind = DN;
     scanf("%d,%d", &G->vexnum, &G->arcnum);
     if(G->vexnum > MAX_VERTEX_NUM){
         printf("����:���������ܳ���%d!!\n", MAX_VERTEX_NUM);
        return -1;
     }
     int i = 0, j = 0, k = 0;
     char v1[10] = {0}, v2[10]={0}, info[10] = {0};
     char tmp[30] = {0};
     for(i=0; i<G->vexnum; i++){
         printf("�����%d������: ", i);
         memset(G->vexs[i].data, 0, sizeof(G->vexs[0].data));
         scanf("%s", G->vexs[i].data);
         for(j=0; j<G->vexnum; j++){
             G->arcs[i][j].weight = INFINITY;
         }

     }
     for(k=0; k<G->arcnum; k++){
         printf("�����%d����(����1, ����2): ", k);
         memset(tmp, 0, sizeof(tmp));
         scanf("%s", tmp);
         sscanf(tmp, "%[^','],%[^','],%s[^\\n]", v1, v2, info);
         i = LocateVex(G, v1);
         j = LocateVex(G, v2);
         if(i<0 || j<0 || (!atoi(info))){
             printf("����:����%s����%s������, ����Ȩֵ��Ϣ%s����!\n", v1, v2, info);
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
 * Dijkstra�Ͻ�˹�����㷨
  * ��������G�Ķ���v0��������v0�����ඥ��v�����·��P[v]�����Ȩ����D[v].weight
  * ��P[v][w].weightΪTRUE(1)����w�Ǵ�v0��v��ǰ������·���ϵĶ��㡣
  * final[v]ΪTRUE(1)�����ҽ���v����S�����Ѿ���ô�v0��v�����·��
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
        //��Ϊ��·��
         for(w=0; w<G->vexnum; ++w){
            P[v][w] = 0;
         }
         if(D[v].weight < INFINITY){
             P[v][v0] = 1;
             P[v][v] = 1;
         }
     }
     //��ʼ����v0��������S��
     D[v0].weight = 0;
   final[v0] = 1;
    //��ʼ��ѭ����ÿ�����v0��ĳ��v��������·��������v��s��
    //����G->vexnum-1������
    for(j=1; j<G->vexnum; j++){
        //min��ŵ�ǰ��v0������̵ľ���
         min = INFINITY;
         for(w=0; w<G->vexnum; w++){
           if(!final[w]){
                //����w��V-S��
                if(D[w].weight < min){
                     //����v0����
                   min = D[w].weight;
                     v = w;
                }
            }
        }
         if(min == INFINITY)
             break;
       //��v0��̵Ķ���v����S����
        final[v] = 1;
         //���µ�ǰ���·���;���
        for (w = 0; w < G->vexnum; w++) {
            if (!final[w] && (min + G->arcs[v][w].weight < D[w].weight)) {
               //�޸�D[w]��P[w]��w����V-S
                 D[w].weight = min + G->arcs[v][w].weight;
                 for(j=0; j<G->vexnum; j++){
                    P[w][j] = P[v][j];
                }
                P[w][w] = 1;
            }
        }
     }
 
     printf("\n��ӡ���·��:\n");
     printMatrix(G->vexnum, G->vexs, P);
 
     printf("\n��ӡ%s�����ඥ��Ĵ�Ȩ����:\n", G->vexs[v0].data);
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
     //���ڽӾ���Ϊ�洢�ṹ����������
     MGraph G;
     if(CreateGraphDN(&G) < 0){
         return -1;
     }
     printf("\n��ӡ��ͼ�е���Ϣ:\n");
    printArchs(G.vexnum, G.vexs, G.arcs);
    //Dijkstra�Ͻ�˹�����㷨��Դ���·��
     ShortestPath_DIJ(&G, 0);
     return 0;
}
//��Դ���·��(Dijkstra)

