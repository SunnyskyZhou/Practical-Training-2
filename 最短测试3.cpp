#include <stdio.h>  
#include <stdlib.h>  
#include <limits.h>  
#include <stdbool.h>  
  
#define NUM_CITIES 100  
#define INF INT_MAX  
  
// ����ߵĽṹ��
typedef struct Edge {
    int dest;
    int weight;
    struct Edge* next;
} Edge;

// ����ͼ���ڽӱ�
typedef struct Graph {
    Edge* adj[NUM_CITIES]; // �ڽӱ�����
} Graph;

// ������е�����
const char* cities[NUM_CITIES] = {"��³ľ��", "����", "����", "���ͺ���", "����","���","����","����","������","����","����","֣��","����","����","�ɶ�","�人","�Ϻ�","����","����","����","�ϲ�","����","����","����","����","����"};


// ����ڴ������  
Edge* createEdge(int dest, int weight) {  
    Edge* edge = (Edge*)malloc(sizeof(Edge));  
    if (!edge) {  
        perror("Memory allocation failed for Edge");  
        exit(EXIT_FAILURE);  
    }  
    edge->dest = dest;  
    edge->weight = weight;  
    edge->next = NULL;  
    return edge;  
}  


// ��ʼ��ͼ
Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    for (int i = 0; i < NUM_CITIES; i++) {
        graph->adj[i] = NULL;
    }
    return graph;
}

// ��ӱ�  
void addEdge(Graph* graph, int src, int dest, int weight) {  
    Edge* edge = createEdge(dest, weight);  
    edge->next = graph->adj[src];  
    graph->adj[src] = edge; 
}

// �ͷ�ͼ���ڴ�
void freeGraph(Graph* graph) {
    for (int i = 0; i < NUM_CITIES; i++) {
        Edge* temp = graph->adj[i];
        while (temp) {
            Edge* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(graph);
}

// �ҵ���δ����Ķ����о�����С�Ķ��������
int minDistance(int dist[], bool sptSet[], int V) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// ��ӡ��Դ�㵽Ŀ�������·��
void printPath(int parent[], int j) {
    // ����: ���j��Դ�ڵ�
    if (parent[j] == -1) {
        return;
    }
//
    printf(" -> %s", cities[j]);
}

// ��ӡ��Դ�㵽Ŀ�������·���������
void printSolution(int dist[], int parent[], int src, int dest) {
    printf("�� %s �� %s �����·�������� %d\n", cities[src], cities[dest], dist[dest]);
    printf("·��: %s", cities[src]);
    printPath(parent, dest);
    printf("\n");
}  
  
// ��װDijkstra�㷨  
void dijkstra(Graph* graph, int src, int dest) {  
    int dist[NUM_CITIES];  
    bool sptSet[NUM_CITIES];  
    int parent[NUM_CITIES];  
  
    // ��ʼ��������ѷ��ʼ���  
    for (int i = 0; i < NUM_CITIES; i++) {  
        dist[i] = INF;  
        sptSet[i] = false;  
        parent[i] = -1;  
    }  
  
    // Դ�㵽����ľ���Ϊ0  
    dist[src] = 0;  
  
    // �������·��  
    for (int count = 0; count < NUM_CITIES - 1; count++) {  
        int u = minDistance(dist, sptSet, NUM_CITIES);  
  
        sptSet[u] = true;  
  
        // �����������ڶ���ľ���  
        Edge* temp = graph->adj[u];  
        while (temp) {  
            int v = temp->dest;  
            if (!sptSet[v] && dist[u] != INF && dist[u] + temp->weight < dist[v]) {  
                parent[v] = u;  
                dist[v] = dist[u] + temp->weight;  
            }  
            temp = temp->next;  
        }  
    }  
  
    // ��ӡ���·���;���  
    printSolution(dist, parent, src, dest);  
}  
  
int main() {  
   Graph* graph = createGraph();

    // ��ӱ�
    addEdge(graph, 0, 1, 1892);
    addEdge(graph, 2, 1, 216);
    addEdge(graph, 1, 3, 1145);
    addEdge(graph, 3, 4, 668);
    addEdge(graph, 4, 5, 137);
    addEdge(graph, 5, 6, 704);
    addEdge(graph, 6, 7, 305);
    addEdge(graph, 7, 8, 242);
    addEdge(graph, 6, 9, 397);
    addEdge(graph, 1, 10, 676);
    addEdge(graph, 10, 11, 511);
    addEdge(graph, 4, 11, 695);
    addEdge(graph, 11, 12, 349);
    addEdge(graph, 5, 12, 674);
    addEdge(graph, 10, 14, 842);
    addEdge(graph, 13, 14, 1990);
    addEdge(graph, 11, 15, 534);
    addEdge(graph, 12, 16, 651);
    addEdge(graph, 14, 18, 967);
    addEdge(graph, 14, 17, 1100);
    addEdge(graph, 15, 19, 409);
    addEdge(graph, 16, 20, 825);
    addEdge(graph, 17, 18, 639);
    addEdge(graph, 18, 24, 902);
    addEdge(graph, 19, 20, 367);
    addEdge(graph, 20, 21, 622);
    addEdge(graph, 18, 22, 607);
    addEdge(graph, 19, 22, 672);
    addEdge(graph, 19, 24, 675);
    addEdge(graph, 22, 23, 255);
    addEdge(graph, 24, 25, 140);

    // �û�����Դ���Ŀ���
    int src, dest;
    printf("��������صı��(0-��³ľ��, 1-����,2-����,3-���ͺ���,4-����,5-���,6-����,7-����,8-������,9-����,10-����,11-֣��,12-����,13-����,14-�ɶ�,15-�人,16-�Ϻ�,17-����,18-����,19-����,20-�ϲ�,21-����,22-����,23-����,24-����,25-����): ");
    scanf("%d", &src);
    printf("����Ŀ�ĵصı��(0-��³ľ��, 1-����,2-����,3-���ͺ���,4-����,5-���,6-����,7-����,8-������,9-����,10-����,11-֣��,12-����,13-����,14-�ɶ�,15-�人,16-�Ϻ�,17-����,18-����,19-����,20-�ϲ�,21-����,22-����,23-����,24-����,25-����): ");
    scanf("%d", &dest);

    // ����Dijkstra�㷨
    dijkstra(graph, src, dest);

    // �ͷ�ͼ���ڴ�
    freeGraph(graph);  
    return 0;  
}

