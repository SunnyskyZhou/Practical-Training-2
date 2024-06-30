#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define NUM_CITIES 10000  // 城市节点数量 
#define INF INT_MAX

// 定义边的结构体
typedef struct Edge {
    int dest;
    int weight;
    struct Edge* next;
} Edge;

// 定义图的邻接表
typedef struct Graph {
    Edge* adj[NUM_CITIES]; // 邻接表数组
} Graph;

// 定义城市的名称
const char* cities[NUM_CITIES] = {
    "乌鲁木齐", "兰州", "西宁", "呼和浩特", "北京", "天津", "沈阳", "长春", "哈尔滨", "大连",
    "西安", "郑州", "徐州", "拉萨", "成都", "武汉", "上海", "昆明", "贵阳", "株洲",
    "南昌", "福州", "柳州", "南宁", "广州", "深圳"
};

// 添加内存分配检查
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

// 初始化图
Graph* createGraph() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    for (int i = 0; i < NUM_CITIES; i++) {
        graph->adj[i] = NULL;
    }
    return graph;
}

// 添加边
void addEdge(Graph* graph, int src, int dest, int weight) {
    Edge* edge = createEdge(dest, weight);
    edge->next = graph->adj[src];
    graph->adj[src] = edge;
}

// 释放图的内存
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

// 找到尚未处理的顶点中距离最小的顶点的索引
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < NUM_CITIES; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// 打印从源点到目标点的最短路径
void printPath(int parent[], int j) {
    // 基例: 如果j是源节点
    if (parent[j] == -1) {
        return;
    }

    printPath(parent, parent[j]);
    printf(" -> %s", cities[j]);
}

// 打印从源点到目标点的最短路径及其距离
void printSolution(int dist[], int parent[], int src, int dest) {
    printf("从 %s 到 %s 的最短路径距离是 %d\n", cities[src], cities[dest], dist[dest]);
    printf("路径: %s", cities[src]);
    printPath(parent, dest);
    printf("\n");
}

// 封装Dijkstra算法
void dijkstra(Graph* graph, int src, int dest) {
    int dist[NUM_CITIES];
    bool sptSet[NUM_CITIES];
    int parent[NUM_CITIES];

    // 初始化距离和已访问集合
    for (int i = 0; i < NUM_CITIES; i++) {
        dist[i] = INF;
        sptSet[i] = false;
        parent[i] = -1;
    }

    // 源点到自身的距离为0
    dist[src] = 0;

    // 查找最短路径
    for (int count = 0; count < NUM_CITIES - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        // 更新所有相邻顶点的距离
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

    // 打印最短路径和距离
    printSolution(dist, parent, src, dest);
}

int main() {
    Graph* graph = createGraph();

    // 添加边（正方向算的地点） 
    addEdge(graph, 0, 1, 1892);  //乌鲁木齐-兰州
    addEdge(graph, 2, 1, 216);  //西宁-兰州
    addEdge(graph, 1, 3, 1145);  //兰州-呼和浩特
    addEdge(graph, 3, 4, 668);  //呼和浩特-北京
    addEdge(graph, 4, 5, 137);  //北京-天津
    addEdge(graph, 5, 6, 704);  //天津-沈阳
    addEdge(graph, 6, 7, 305);  //沈阳-长春
    addEdge(graph, 7, 8, 242);  //长春-哈尔滨
    addEdge(graph, 6, 9, 397);   //沈阳-大连
    addEdge(graph, 1, 10, 676);  //兰州-西安
    addEdge(graph, 10, 11, 511);  //西安-郑州
    addEdge(graph, 4, 11, 695);  //北京-郑州
    addEdge(graph, 11, 12, 349);  //郑州-徐州
    addEdge(graph, 5, 12, 674);  //天津-徐州
    addEdge(graph, 10, 14, 842);  //西安-成都
    addEdge(graph, 13, 14, 1990);  //拉萨-成都
    addEdge(graph, 11, 15, 534);  //郑州-武汉
    addEdge(graph, 12, 16, 651);  //徐州-上海
    addEdge(graph, 14, 18, 967);  //成都-贵阳
    addEdge(graph, 14, 17, 1100);  //成都-昆明
    addEdge(graph, 15, 19, 409);  //武汉-株洲
    addEdge(graph, 16, 20, 825);  //上海-南昌
    addEdge(graph, 17, 18, 639);  //昆明-贵阳
    addEdge(graph, 18, 24, 902);  //贵阳-株洲
    addEdge(graph, 19, 20, 367);  //株洲-南昌
    addEdge(graph, 20, 21, 622);  //南昌-福州
    addEdge(graph, 18, 22, 607);  //贵阳-柳州
    addEdge(graph, 19, 22, 672);  //株洲-柳州
    addEdge(graph, 19, 24, 675);  //株洲-广州
    addEdge(graph, 22, 23, 255);  //柳州-南宁
    addEdge(graph, 24, 25, 140);  //广州-深圳

    // 添加边（反方向算的地点）    
    addEdge(graph, 1,0 , 1892);  //兰州-乌鲁木齐
    addEdge(graph, 1, 2, 216);  //兰州-西宁
    addEdge(graph, 3,1, 1145);  //呼和浩特-兰州
    addEdge(graph, 4, 3, 668);  //北京-呼和浩特
    addEdge(graph, 5, 4, 137);  //天津-北京
    addEdge(graph, 6, 5, 704);  //沈阳-天津
    addEdge(graph, 7, 6, 305);  //长春-沈阳
    addEdge(graph, 8, 7, 242);  //哈尔滨-长春
    addEdge(graph, 9, 6, 397);   //大连-沈阳
    addEdge(graph, 10, 1, 676);  //西安-兰州
    addEdge(graph, 11, 10, 511);  //郑州-西安
    addEdge(graph, 11, 4, 695);  //郑州-北京
    addEdge(graph, 12, 11, 349);  //徐州-郑州
    addEdge(graph, 12, 5, 674);  //徐州-天津
    addEdge(graph, 14, 10, 842);  //成都-西安
    addEdge(graph, 14, 13, 1990);  //成都-拉萨
    addEdge(graph, 15, 11, 534);  //武汉-郑州
    addEdge(graph, 16, 12, 651);  //上海-徐州
    addEdge(graph, 18, 14, 967);  //贵阳-成都
    addEdge(graph, 17, 14, 1100);  //昆明-成都
    addEdge(graph, 19, 15, 409);  //株洲-武汉
    addEdge(graph, 20, 16, 825);  //南昌-上海
    addEdge(graph, 18, 17, 639);  //贵阳-昆明
    addEdge(graph, 24, 18, 902);  //株洲-贵阳
    addEdge(graph, 20, 19, 367);  //南昌-株洲
    addEdge(graph, 21, 20, 622);  //福州-南昌
    addEdge(graph, 22, 18, 607);  //柳州-贵阳
    addEdge(graph, 22, 19, 672);  //柳州-株洲
    addEdge(graph, 24, 19, 675);  //广州-株洲
    addEdge(graph, 23, 22, 255);  //南宁-柳州
    addEdge(graph, 25, 24, 140);  //深圳-广州

    // 输入源点和目标点
    int src, dest;

    printf("[地址编号表] \n");
    printf("0-乌鲁木齐, 1-兰州,2-西宁,3-呼和浩特,4-北京,5-天津,6-沈阳,7-长春,8-哈尔滨,9-大连,10-西安,11-郑州,12-徐州\n ");
    printf("13-拉萨,14-成都,15-武汉,16-上海,17-昆明,18-贵阳,19-株洲,20-南昌,21-福州,22-柳州,23-南宁,24-广州,25-深圳\n");
    printf("\n");
    printf("请输入出发地的编号: ");
    
    scanf("%d", &src);  // 输入出发地编号
    
    printf("请输入目的地的编号: ");
    scanf("%d", &dest);  // 输入目的地编号
    
    printf("\n");

    // 检查输入是否有效
    if (src < 0 || src >= NUM_CITIES || dest < 0 || dest >= NUM_CITIES) 
    {
        printf("输入的编号无效，请输入0到25之间的数字。\n");  // 输入无效时，输出错误信息
        freeGraph(graph);  // 释放图的内存
        return EXIT_FAILURE;  // 退出程序
    }


    // 调用Dijkstra算法
    dijkstra(graph, src, dest);

    // 释放图的内存
    freeGraph(graph);
    return 0;
}

