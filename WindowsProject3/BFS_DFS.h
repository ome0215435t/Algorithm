#include <stdio.h>
#include <stdbool.h>
#include <tchar.h>
#define MAX_SIZE 6

// Queue 구현
typedef struct {
    int data[MAX_SIZE];
    int front, rear;
} Queue;

void initializeQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isQueueEmpty(Queue* q) {
    return (q->front == -1 && q->rear == -1);
}

void enqueue(Queue* q, int value) {
    if (isQueueEmpty(q)) {
        q->front = 0;
        q->rear = 0;
    }
    else {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }
    q->data[q->rear] = value;
}

int dequeue(Queue* q) {
    int value = q->data[q->front];
    if (q->front == q->rear) {
        initializeQueue(q);
    }
    else {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    return value;
}

// BFS 구현
void bfs(int graph[][MAX_SIZE], int vertices, int start,TCHAR* a) {
    bool visited[MAX_SIZE] = { false };
    Queue q;
    initializeQueue(&q);
    _stprintf(a, _T("설명 : 그래프나 트리에서 시작 정점으로부터 인접한 모든 정점들을 먼저 탐색하는 알고리즘으로, 큐를 사용하여 구현\n\n BFS 시작점 0 : "));
    _stprintf(a + _tcslen(a), _T("%d "), start);
    visited[start] = true;
    enqueue(&q, start);

    while (!isQueueEmpty(&q)) {
        int current = dequeue(&q);
        for (int i = 0; i < vertices; ++i) {
            if (graph[current][i] == 1 && !visited[i]) {
                _stprintf(a + _tcslen(a), _T("%d "),i);
                visited[i] = true;
                enqueue(&q, i);
            }
        }
    }
}

// DFS 구현
void dfs(int graph[][MAX_SIZE], int vertices, int current, bool visited[], TCHAR* a) {
    _stprintf(a + _tcslen(a), _T("%d "), current);
    visited[current] = true;

    for (int i = 0; i < vertices; ++i) {
        if (graph[current][i] == 1 && !visited[i]) {
            dfs(graph, vertices, i, visited,a);
        }
    }
}
