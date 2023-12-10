#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<tchar.h>
#define V 5  // 정점의 개수

// 그래프 표현을 위한 구조체
typedef struct {
    int weight;
    int nextVertex;
} Edge;

typedef struct {
    Edge* edges;
    int numEdges;
} Graph;
void dijkstra1(int graph[V][V], int start, TCHAR* a) {
    int distance[V];  // 시작 정점으로부터의 최단 거리를 저장할 배열
    int visited[V];   // 방문 여부를 나타내는 배열

    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    distance[start] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u, minDistance = INT_MAX;

        // 방문하지 않은 정점 중에서 최단 거리를 갖는 정점을 찾음
        for (int v = 0; v < V; v++) {
            if (!visited[v] && distance[v] < minDistance) {
                u = v;
                minDistance = distance[v];
            }
        }

        visited[u] = 1;

        // u를 거쳐가는 경로가 더 짧으면 업데이트
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && distance[u] != INT_MAX &&
                distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }


    _stprintf(a, _T("설명 : 시작 정점으로부터 각 정점까지의 최단 경로를 찾는 알고리즘이며, 간선의 가중치가 음수가 아닌 경우에 사용\n\n다익스트라 최단경로(0에서 출발)\n"));
    for (int j = 0; j < V; j++) {
        _stprintf(a + _tcslen(a), _T("%d까지 최단거리 : %d\n"), j,distance[j]);
    }
    _stprintf(a + _tcslen(a), _T("\n"));
}

void floydWarshall(int graph[V][V], TCHAR* a) {
    int dist[V][V];

    // 초기 거리 행렬 설정
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // 거쳐가는 정점 k에 대해 모든 쌍 (i, j)의 최단 거리 계산
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // 결과 출력
    _stprintf(a, _T("설명 :  그래프에서 모든 정점 쌍 간의 최단 경로를 구하는 알고리즘으로, 동적 프로그래밍을 활용하여 각 정점을 거쳐가는 경우를 고려하여 최단 경로를 업데이트\n\n플로이드 최단경로(0에서 출발)\n"));
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INT_MAX) {
                _stprintf(a + _tcslen(a), _T("INF\t"));
            }
            else {
                _stprintf(a + _tcslen(a), _T("%d\t"), dist[i][j]);
            }
        }
        _stprintf(a + _tcslen(a), _T("\n"));
    }
    _stprintf(a + _tcslen(a), _T("\n"));
}

void topologicalSortUtil(int v, int visited[], int stack[], int* stackIndex, int graph[V][V]) {
    visited[v] = 1;

    for (int i = 0; i < V; i++) {
        if (!visited[i] && graph[v][i]) {
            topologicalSortUtil(i, visited, stack, stackIndex, graph);
        }
    }

    stack[(*stackIndex)++] = v;
}

void topologicalSort(int graph[V][V], TCHAR* a) {
    int visited[V];
    int stack[V];
    int stackIndex = 0;

    for (int i = 0; i < V; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, stack, &stackIndex, graph);
        }
    }

    // 결과 출력
    _stprintf(a, _T("설명 : 방향 그래프의 모든 정점을 방향성을 거스르지 않으면서 나열하는 알고리즘으로, 선후 관계가 있는 작업이나 일련의 이벤트를 순서대로 정렬하는 데 사용\n\n위상 정렬 : "));
    while (stackIndex > 0) {
        stackIndex--;
        _stprintf(a + _tcslen(a), _T("%d "), stack[stackIndex]);
    }
    _stprintf(a + _tcslen(a), _T("\n")); 
}
void prim(int graph[V][V],TCHAR* a) {
    // 프림 알고리즘 구현
    int parent[V];    // MST에 포함된 정점의 부모
    int key[V];       // 정점의 키 값
    int mstSet[V];    // MST에 포함된 정점을 나타내는 배열

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;       // 시작 정점을 선택
    parent[0] = -1;   // 시작 정점은 부모가 없음

    for (int count = 0; count < V - 1; count++) {
        int u, minKey = INT_MAX;

        // MST에 포함되지 않은 정점 중에서 최소 키 값을 갖는 정점을 찾음
        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < minKey) {
                u = v;
                minKey = key[v];
            }
        }

        mstSet[u] = 1;

        // u의 인접한 정점들의 키 값을 업데이트
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // 결과 출력
    _stprintf(a, _T("설명 : 최소 신장 트리를 구성하기 위해 그래프에서 가장 작은 가중치의 간선을 추가하는 방식으로 동작하며, 크루스칼 알고리즘은 간선을 가중치의 오름차순으로 정렬하여 사이클을 만들지 않으면서 최소 신장 트리를 구성하는 알고리즘\n\n프림 알고리즘  최소신장 트리\n"));
    for (int i = 1; i < V; i++) {
        _stprintf(a + _tcslen(a), _T("간선 : "));
        _stprintf(a + _tcslen(a), _T("%d - %d\t가중치 : %d"), parent[i], i, graph[i][parent[i]]);
        _stprintf(a + _tcslen(a), _T("\n"));
    }

}

typedef struct {
    int src, dest, weight;
} EdgeKruskal;

// 크루스칼 알고리즘에서 사용할 비교 함수
int compareEdges(const void* a, const void* b) {
    return ((EdgeKruskal*)a)->weight - ((EdgeKruskal*)b)->weight;
}

int find(int parent[], int i) {
    if (parent[i] == -1) {
        return i;
    }
    return find(parent, parent[i]);
}

void unionSet(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

void kruskal(int graph[V][V],TCHAR* a) {
    // 크루스칼 알고리즘 구현
    EdgeKruskal result[V - 1];  // 최소 신장 트리를 저장할 배열
    int parent[V];              // 각 정점의 부모를 나타내는 배열

    for (int i = 0; i < V; i++) {
        parent[i] = -1;
    }

    int edgeCount = 0;

    // 모든 간선을 배열에 저장
    EdgeKruskal edges[V * V];
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] != 0) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = graph[i][j];
                edgeCount++;
            }
        }
    }

    // 간선을 가중치 순서로 정렬
    qsort(edges, edgeCount, sizeof(EdgeKruskal), compareEdges);

    // 크루스칼 알고리즘 수행
    int i = 0;
    edgeCount = 0;
    while (edgeCount < V - 1) {
        EdgeKruskal nextEdge = edges[i++];

        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);

        if (x != y) {
            result[edgeCount++] = nextEdge;
            unionSet(parent, x, y);
        }
    }

    // 결과 출력
    _stprintf(a, _T("설명 : 최소 신장 트리를 찾는 알고리즘으로, 간선을 가중치의 오름차순으로 정렬하고 사이클을 형성하지 않으면서 가장 작은 가중치의 간선부터 추가하는 알고리즘\n\n크루스칼 알고리즘  최소신장 트리\n"));
    for (int i = 0; i < V - 1; i++) {
        _stprintf(a + _tcslen(a), _T("간선 : "));
        _stprintf(a + _tcslen(a), _T("%d - %d\t가중치 : %d"), result[i].src, result[i].dest, result[i].weight);
        _stprintf(a + _tcslen(a), _T("\n"));
    }
}