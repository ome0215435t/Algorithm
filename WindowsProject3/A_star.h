#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <tchar.h>
// 노드 구조체 정의
typedef struct Node {
    int x, y;      // 노드의 좌표
    int cost;      // 시작 노드로부터의 비용
    int heuristic; // 휴리스틱 값
    struct Node* parent; // 부모 노드를 저장하기 위한 포인터
} Node;

// 우선순위 큐를 위한 노드 구조체 정의
typedef struct PriorityQueueNode {
    Node* node;
    int priority; // 비용과 휴리스틱 값을 합한 우선순위
    struct PriorityQueueNode* next;
} PriorityQueueNode;

// 우선순위 큐 구조체 정의
typedef struct PriorityQueue {
    PriorityQueueNode* front;
} PriorityQueue;

// 그래프에서 사용할 상수 정의
#define ROW 5
#define COL 5

// 시작 노드와 목표 노드 좌표 정의
#define START_X 0
#define START_Y 0
#define GOAL_X 4
#define GOAL_Y 4

// 그래프와 휴리스틱 함수 정의
int graph[ROW][COL] = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}
};

int heuristic(int x, int y) {
    // 맨하탄 거리를 사용한 휴리스틱 함수
    return abs(x - GOAL_X) + abs(y - GOAL_Y);
}

// 우선순위 큐 관련 함수들
PriorityQueue* createPriorityQueue() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->front = NULL;
    return pq;
}

void enqueue_a(PriorityQueue* pq, Node* node, int priority) {
    PriorityQueueNode* newNode = (PriorityQueueNode*)malloc(sizeof(PriorityQueueNode));
    newNode->node = node;
    newNode->priority = priority;
    newNode->next = NULL;

    if (pq->front == NULL || priority < pq->front->priority) {
        newNode->next = pq->front;
        pq->front = newNode;
    }
    else {
        PriorityQueueNode* temp = pq->front;
        while (temp->next != NULL && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

Node* dequeue_a(PriorityQueue* pq) {
    if (pq->front == NULL) {
        return NULL;
    }

    Node* node = pq->front->node;
    PriorityQueueNode* temp = pq->front;
    pq->front = pq->front->next;
    free(temp);

    return node;
}

// A* 알고리즘 구현
void Astar(TCHAR* a) {
    // 그래프 초기화, 우선순위 큐 등의 초기 작업 수행
    int visited[ROW][COL] = { 0 };
    int cost[ROW][COL];
    int heuristicValues[ROW][COL];

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cost[i][j] = INT_MAX;
            heuristicValues[i][j] = heuristic(i, j);
        }
    }
    Node* startNode = (Node*)malloc(sizeof(Node));
    startNode->x = START_X;
    startNode->y = START_Y;
    startNode->cost = 0;
    startNode->heuristic = heuristic(START_X, START_Y);
    startNode->parent = NULL;

    PriorityQueue* openList = createPriorityQueue();
    enqueue_a(openList, startNode, startNode->cost + startNode->heuristic);

    while (openList->front != NULL) {
        Node* currentNode = dequeue_a(openList);
        if (currentNode->x == GOAL_X && currentNode->y == GOAL_Y) {
            _stprintf(a, _T("설명 : 그래프나 그리드 상에서 시작 노드부터 목표 노드까지의 최적 경로를 찾기 위해 휴리스틱 함수와 비용 함수를 결합하여 사용하는 탐색 알고리즘\n\n"));
            _stprintf(a + _tcslen(a), _T("총 비용: %d\n"), currentNode->cost);
            while (currentNode != NULL) {
                _stprintf(a + _tcslen(a), _T("(%d, %d) -> "), currentNode->x, currentNode->y);
                currentNode = currentNode->parent;
            }
            _stprintf(a + _tcslen(a), _T("Start\n"));
            break;
        }
        visited[currentNode->x][currentNode->y] = 1;

        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++) {
            int nextX = currentNode->x + dx[i];
            int nextY = currentNode->y + dy[i];

            if (nextX < 0 || nextX >= ROW || nextY < 0 || nextY >= COL) {
                continue;
            }

            if (graph[nextX][nextY] == 1 || visited[nextX][nextY] == 1) {
                continue;
            }

            int newCost = currentNode->cost + 1;

            if (newCost < cost[nextX][nextY]) {
                cost[nextX][nextY] = newCost;
                Node* nextNode = (Node*)malloc(sizeof(Node));
                nextNode->x = nextX;
                nextNode->y = nextY;
                nextNode->cost = newCost;
                nextNode->heuristic = heuristicValues[nextX][nextY];
                nextNode->parent = currentNode;
                enqueue_a(openList, nextNode, newCost + heuristicValues[nextX][nextY]);
            }
        }
    }
}


