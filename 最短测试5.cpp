#include <stdio.h>  // ��׼���������
#include <stdlib.h>  // ��׼�⣬�����ڴ���亯��
#include <limits.h>  // ���������������Ƶĳ�������
#include <stdbool.h>  // �����������Ͷ��壨����һ��warning�� 

#define NUM_CITIES 26  // �����������
#define INF INT_MAX  // ���������Ϊ���͵����ֵ

//Ԫ�أ�src-�����أ�dest-Ŀ�ĵأ�edge-·��/�ߣ� 

// ����ߵĽṹ��
typedef struct Edge 
{
    int dest;  // Ŀ�ĵ�
    int weight;  // �ߵ�Ȩ��
    struct Edge* next;  // ָ����һ���ߵ�ָ��
} Edge;

// ����ͼ���ڽӱ�
typedef struct Graph 
{
    Edge* adj[NUM_CITIES]; // �ڽӱ�����
} Graph;

// ������е�����
const char* cities[NUM_CITIES] = {"��³ľ��", "����", "����", "���ͺ���", "����","���","����","����","������","����","����","֣��","����","����","�ɶ�","�人","�Ϻ�","����","����","����","�ϲ�","����","����","����","����","����"};
//ֻ�� char*�Ļ���ַ���䣬��ָ�����ֵ���ܸı䣬������const char*��ʾһ���޶����ᱻ�ı��ָ����� 

// ����ڴ������  
Edge* createEdge(int dest, int weight)
 {  
    Edge* edge = (Edge*)malloc(sizeof(Edge));  // Ϊ�߷����ڴ�
    if (!edge)  // ����ڴ�����Ƿ�ɹ�
    {  
        perror("�ڴ�������!");  // ��ӡ������Ϣ
        exit(EXIT_FAILURE);  // �˳�����
    }  
    edge->dest = dest;  // ����Ŀ�ĵ�
    edge->weight = weight;  // ����Ȩ��
    edge->next = NULL;  // ��ʼ����һ����ΪNULL
    return edge;  // ���ش����ı�
}  

// ��ʼ��ͼ
Graph* createGraph() 
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));  // Ϊͼ�����ڴ�
    if (!graph)  // ����ڴ�����Ƿ�ɹ�
    {
        perror("ͼ�������ʧ��");  // ���ʧ�ܣ����������Ϣ
        exit(EXIT_FAILURE);  // �˳�����
    }
    for (int i = 0; i < NUM_CITIES; i++)  // ��ʼ���ڽӱ�
    {
        graph->adj[i] = NULL;  // �������ڽӱ�Ԫ�س�ʼ��ΪNULL
    }
    return graph;  // ���ش�����ͼ
}

// ��ӱߣ�˫��ߣ�
void addEdge(Graph* graph, int src, int dest, int weight) 
{  
    Edge* edge = createEdge(dest, weight);  // �����µı�-ָ��Ŀ�ĵ� 
    edge->next = graph->adj[src];  // ������߲��뵽�ڽӱ��ǰ��
    graph->adj[src] = edge;  // �����ڽӱ�

    // ��ӷ���ߣ�����main()���������㷨��ʹ��˳������򶼿��Լ��㣬���������㣻��������ֱ�����ˣ� 
    edge = createEdge(src, weight);  // ���������-ָ������� 
    edge->next = graph->adj[dest];  // ������߲��뵽�ڽӱ��ǰ��
    graph->adj[dest] = edge;  // �����ڽӱ�
}

// �ͷ�ͼ���ڴ�
void freeGraph(Graph* graph) 
{
    for (int i = 0; i < NUM_CITIES; i++)  // ����ÿ������
    {
        Edge* temp = graph->adj[i];  // ��ȡ�ڽӱ�
        while (temp)  // �����ڽӱ��е����б�
        {
            Edge* toDelete = temp;  // ���浱ǰ��
            temp = temp->next;  // �ƶ�����һ����
            free(toDelete);  // �ͷŵ�ǰ�ߵ��ڴ�
        }
    }
    free(graph);  // �ͷ�ͼ���ڴ�
}

// �ҵ���δ����Ķ����о�����С�Ķ��������
int minDistance(int dist[], bool sptSet[], int V) 
{
    int min = INT_MAX, min_index = -1;  // ��ʼ����Сֵ
    for (int v = 0; v < V; v++) {  // �������ж���
        if (!sptSet[v] && dist[v] <= min)  // �ҵ�δ�����Ҿ�����С�Ķ���
        {
            min = dist[v];  // ������Сֵ
            min_index = v;  // ������Сֵ������
        }
    }
    return min_index;  // ������Сֵ������
}

// ��ӡ��Դ�㵽Ŀ�������·��
void printPath(int parent[], int j)   //����: ��j�ǵ��ڵ�
{

    if (parent[j] == -1)  //��j��Դ�ڵ� 
    {
        return;
    }

    printPath(parent, parent[j]);  // �ݹ��ӡ���ڵ�
    printf(" -> %s", cities[j]);  // ��ӡ��ǰ�ڵ�
}

// ��ӡ�ӳ����㵽Ŀ�������·���������
void printSolution(int dist[], int parent[], int src, int dest) 
{
    printf("�� %s �� %s �����·�������� %d\n", cities[src], cities[dest], dist[dest]);  // ��ӡ���·������
    printf("·��: %s", cities[src]);  // ��ӡ���
    printPath(parent, dest);  // ��ӡ·��
    printf("\n"); 
}  
  
// Dijkstra�㷨 ���Ͻ�˹������ 
void dijkstra(Graph* graph, int src, int dest) 
{  
    int dist[NUM_CITIES];  // �������·���ľ���
    bool sptSet[NUM_CITIES];  // ��¼�����Ƿ񱻴���
    int parent[NUM_CITIES];  // ��¼·���еĸ��ڵ�
  
    // ��ʼ��������ѷ��ʼ���  
    for (int i = 0; i < NUM_CITIES; i++) 
    {  
        dist[i] = INF;  // �����о����ʼ��Ϊ�����
        sptSet[i] = false;  // ��ʼ�����ж���Ϊδ����
        parent[i] = -1;  // ��ʼ�����ڵ�Ϊ-1
    }  
  
    dist[src] = 0;  // Դ�ڵ㵽����ľ���Ϊ0
  
    // �������·��  
    for (int count = 0; count < NUM_CITIES - 1; count++) 
    {  
        int u = minDistance(dist, sptSet, NUM_CITIES);  // �ҵ�������С�Ķ���
        if (u == -1) 
        {
            break; 
        }
  
        sptSet[u] = true;  // ���ҵ��Ķ�����Ϊ�Ѵ���
  
        // �����������ڶ���ľ���  
        Edge* temp = graph->adj[u];  // ��ȡ�ڽӱ�
        while (temp) 
        {  
            int v = temp->dest;  // ��ȡ�ڽӶ���
            if (!sptSet[v] && dist[u] != INF && dist[u] + temp->weight < dist[v]) 
            {  
                parent[v] = u;  // ���¸��ڵ�
                dist[v] = dist[u] + temp->weight;  // ���¾���
            }  
            temp = temp->next;  // �ƶ�����һ����
        }  
    }  
  
    // ��ӡ���·���;���  
    printSolution(dist, parent, src, dest);  
}  
  
int main() 
{  
    Graph* graph = createGraph();  // ����ͼ

    // ��ӳ���֮��ıߵ�Ȩ�� 
    addEdge(graph, 0, 1, 1892);  //��³ľ��-����
    addEdge(graph, 2, 1, 216);  //����-����
    addEdge(graph, 1, 3, 1145);  //����-���ͺ���
    addEdge(graph, 3, 4, 668);  //���ͺ���-����
    addEdge(graph, 4, 5, 137);  //����-���
    addEdge(graph, 5, 6, 704);  //���-����
    addEdge(graph, 6, 7, 305);  //����-����
    addEdge(graph, 7, 8, 242);  //����-������
    addEdge(graph, 6, 9, 397);   //����-����
    addEdge(graph, 1, 10, 676);  //����-����
    addEdge(graph, 10, 11, 511);  //����-֣��
    addEdge(graph, 4, 11, 695);  //����-֣��
    addEdge(graph, 11, 12, 349);  //֣��-����
    addEdge(graph, 5, 12, 674);  //���-����
    addEdge(graph, 10, 14, 842);  //����-�ɶ�
    addEdge(graph, 13, 14, 1990);  //����-�ɶ�
    addEdge(graph, 11, 15, 534);  //֣��-�人
    addEdge(graph, 12, 16, 651);  //����-�Ϻ�
    addEdge(graph, 14, 18, 967);  //�ɶ�-����
    addEdge(graph, 14, 17, 1100);  //�ɶ�-����
    addEdge(graph, 15, 19, 409);  //�人-����
    addEdge(graph, 16, 20, 825);  //�Ϻ�-�ϲ�
    addEdge(graph, 17, 18, 639);  //����-����
    addEdge(graph, 18, 24, 902);  //����-����
    addEdge(graph, 19, 20, 367);  //����-�ϲ�
    addEdge(graph, 20, 21, 622);  //�ϲ�-����
    addEdge(graph, 18, 22, 607);  //����-����
    addEdge(graph, 19, 22, 672);  //����-����
    addEdge(graph, 19, 24, 675);  //����-����
    addEdge(graph, 22, 23, 255);  //����-����
    addEdge(graph, 24, 25, 140);  //����-����

    while (1) 
    {
        // ����Դ���Ŀ���
        int src, dest;

        printf("[��ַ��ű�] \n");
        printf("0-��³ľ��, 1-����,2-����,3-���ͺ���,4-����,5-���,6-����,7-����,8-������,9-����,10-����,11-֣��,12-����\n ");
        printf("13-����,14-�ɶ�,15-�人,16-�Ϻ�,17-����,18-����,19-����,20-�ϲ�,21-����,22-����,23-����,24-����,25-����\n");
        printf("\n");
        printf("����������صı�� (���� -1 �˳�): ");
        
        scanf("%d", &src);  // ��������ر��
        
        if (src == -1) 
		{
            break;  // �������-1�����˳�ѭ��
        }
        
        printf("������Ŀ�ĵصı�� (���� # �˳�): ");
        scanf("%d", &dest);  // ����Ŀ�ĵر��

        if (dest == -1) {
            break;  // �������-1�����˳�ѭ��
        }
        
        printf("\n");

        // ��������Ƿ���Ч
        if (src < 0 || src >= NUM_CITIES || dest < 0 || dest >= NUM_CITIES) 
        {
            printf("����ı����Ч��������0��25֮������֡�\n");  // ������Чʱ�����������Ϣ
            continue;  // ����ѭ��
        }

        // ����Dijkstra�㷨
        dijkstra(graph, src, dest);  // �������·��
    }

    // �ͷ�ͼ���ڴ�
    freeGraph(graph);  
    return 0;  
}

