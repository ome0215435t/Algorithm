#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<tchar.h>
#define V 5  // ������ ����

// �׷��� ǥ���� ���� ����ü
typedef struct {
    int weight;
    int nextVertex;
} Edge;

typedef struct {
    Edge* edges;
    int numEdges;
} Graph;
void dijkstra1(int graph[V][V], int start, TCHAR* a) {
    int distance[V];  // ���� �������κ����� �ִ� �Ÿ��� ������ �迭
    int visited[V];   // �湮 ���θ� ��Ÿ���� �迭

    for (int i = 0; i < V; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    distance[start] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u, minDistance = INT_MAX;

        // �湮���� ���� ���� �߿��� �ִ� �Ÿ��� ���� ������ ã��
        for (int v = 0; v < V; v++) {
            if (!visited[v] && distance[v] < minDistance) {
                u = v;
                minDistance = distance[v];
            }
        }

        visited[u] = 1;

        // u�� ���İ��� ��ΰ� �� ª���� ������Ʈ
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && distance[u] != INT_MAX &&
                distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }


    _stprintf(a, _T("���� : ���� �������κ��� �� ���������� �ִ� ��θ� ã�� �˰����̸�, ������ ����ġ�� ������ �ƴ� ��쿡 ���\n\n���ͽ�Ʈ�� �ִܰ��(0���� ���)\n"));
    for (int j = 0; j < V; j++) {
        _stprintf(a + _tcslen(a), _T("%d���� �ִܰŸ� : %d\n"), j,distance[j]);
    }
    _stprintf(a + _tcslen(a), _T("\n"));
}

void floydWarshall(int graph[V][V], TCHAR* a) {
    int dist[V][V];

    // �ʱ� �Ÿ� ��� ����
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // ���İ��� ���� k�� ���� ��� �� (i, j)�� �ִ� �Ÿ� ���
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

    // ��� ���
    _stprintf(a, _T("���� :  �׷������� ��� ���� �� ���� �ִ� ��θ� ���ϴ� �˰�������, ���� ���α׷����� Ȱ���Ͽ� �� ������ ���İ��� ��츦 ����Ͽ� �ִ� ��θ� ������Ʈ\n\n�÷��̵� �ִܰ��(0���� ���)\n"));
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

    // ��� ���
    _stprintf(a, _T("���� : ���� �׷����� ��� ������ ���⼺�� �Ž����� �����鼭 �����ϴ� �˰�������, ���� ���谡 �ִ� �۾��̳� �Ϸ��� �̺�Ʈ�� ������� �����ϴ� �� ���\n\n���� ���� : "));
    while (stackIndex > 0) {
        stackIndex--;
        _stprintf(a + _tcslen(a), _T("%d "), stack[stackIndex]);
    }
    _stprintf(a + _tcslen(a), _T("\n")); 
}
void prim(int graph[V][V],TCHAR* a) {
    // ���� �˰��� ����
    int parent[V];    // MST�� ���Ե� ������ �θ�
    int key[V];       // ������ Ű ��
    int mstSet[V];    // MST�� ���Ե� ������ ��Ÿ���� �迭

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;       // ���� ������ ����
    parent[0] = -1;   // ���� ������ �θ� ����

    for (int count = 0; count < V - 1; count++) {
        int u, minKey = INT_MAX;

        // MST�� ���Ե��� ���� ���� �߿��� �ּ� Ű ���� ���� ������ ã��
        for (int v = 0; v < V; v++) {
            if (!mstSet[v] && key[v] < minKey) {
                u = v;
                minKey = key[v];
            }
        }

        mstSet[u] = 1;

        // u�� ������ �������� Ű ���� ������Ʈ
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // ��� ���
    _stprintf(a, _T("���� : �ּ� ���� Ʈ���� �����ϱ� ���� �׷������� ���� ���� ����ġ�� ������ �߰��ϴ� ������� �����ϸ�, ũ�罺Į �˰����� ������ ����ġ�� ������������ �����Ͽ� ����Ŭ�� ������ �����鼭 �ּ� ���� Ʈ���� �����ϴ� �˰���\n\n���� �˰���  �ּҽ��� Ʈ��\n"));
    for (int i = 1; i < V; i++) {
        _stprintf(a + _tcslen(a), _T("���� : "));
        _stprintf(a + _tcslen(a), _T("%d - %d\t����ġ : %d"), parent[i], i, graph[i][parent[i]]);
        _stprintf(a + _tcslen(a), _T("\n"));
    }

}

typedef struct {
    int src, dest, weight;
} EdgeKruskal;

// ũ�罺Į �˰��򿡼� ����� �� �Լ�
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
    // ũ�罺Į �˰��� ����
    EdgeKruskal result[V - 1];  // �ּ� ���� Ʈ���� ������ �迭
    int parent[V];              // �� ������ �θ� ��Ÿ���� �迭

    for (int i = 0; i < V; i++) {
        parent[i] = -1;
    }

    int edgeCount = 0;

    // ��� ������ �迭�� ����
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

    // ������ ����ġ ������ ����
    qsort(edges, edgeCount, sizeof(EdgeKruskal), compareEdges);

    // ũ�罺Į �˰��� ����
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

    // ��� ���
    _stprintf(a, _T("���� : �ּ� ���� Ʈ���� ã�� �˰�������, ������ ����ġ�� ������������ �����ϰ� ����Ŭ�� �������� �����鼭 ���� ���� ����ġ�� �������� �߰��ϴ� �˰���\n\nũ�罺Į �˰���  �ּҽ��� Ʈ��\n"));
    for (int i = 0; i < V - 1; i++) {
        _stprintf(a + _tcslen(a), _T("���� : "));
        _stprintf(a + _tcslen(a), _T("%d - %d\t����ġ : %d"), result[i].src, result[i].dest, result[i].weight);
        _stprintf(a + _tcslen(a), _T("\n"));
    }
}