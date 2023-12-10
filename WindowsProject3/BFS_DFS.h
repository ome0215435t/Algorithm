#include <stdio.h>
#include <stdbool.h>
#include <tchar.h>
#define MAX_SIZE 6

// Queue ����
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

// BFS ����
void bfs(int graph[][MAX_SIZE], int vertices, int start,TCHAR* a) {
    bool visited[MAX_SIZE] = { false };
    Queue q;
    initializeQueue(&q);
    _stprintf(a, _T("���� : �׷����� Ʈ������ ���� �������κ��� ������ ��� �������� ���� Ž���ϴ� �˰�������, ť�� ����Ͽ� ����\n\n BFS ������ 0 : "));
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

// DFS ����
void dfs(int graph[][MAX_SIZE], int vertices, int current, bool visited[], TCHAR* a) {
    _stprintf(a + _tcslen(a), _T("%d "), current);
    visited[current] = true;

    for (int i = 0; i < vertices; ++i) {
        if (graph[current][i] == 1 && !visited[i]) {
            dfs(graph, vertices, i, visited,a);
        }
    }
}
