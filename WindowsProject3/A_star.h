#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <tchar.h>
// ��� ����ü ����
typedef struct Node {
    int x, y;      // ����� ��ǥ
    int cost;      // ���� ���κ����� ���
    int heuristic; // �޸���ƽ ��
    struct Node* parent; // �θ� ��带 �����ϱ� ���� ������
} Node;

// �켱���� ť�� ���� ��� ����ü ����
typedef struct PriorityQueueNode {
    Node* node;
    int priority; // ���� �޸���ƽ ���� ���� �켱����
    struct PriorityQueueNode* next;
} PriorityQueueNode;

// �켱���� ť ����ü ����
typedef struct PriorityQueue {
    PriorityQueueNode* front;
} PriorityQueue;

// �׷������� ����� ��� ����
#define ROW 5
#define COL 5

// ���� ���� ��ǥ ��� ��ǥ ����
#define START_X 0
#define START_Y 0
#define GOAL_X 4
#define GOAL_Y 4

// �׷����� �޸���ƽ �Լ� ����
int graph[ROW][COL] = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}
};

int heuristic(int x, int y) {
    // ����ź �Ÿ��� ����� �޸���ƽ �Լ�
    return abs(x - GOAL_X) + abs(y - GOAL_Y);
}

// �켱���� ť ���� �Լ���
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

// A* �˰��� ����
void Astar(TCHAR* a) {
    // �׷��� �ʱ�ȭ, �켱���� ť ���� �ʱ� �۾� ����
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
            _stprintf(a, _T("���� : �׷����� �׸��� �󿡼� ���� ������ ��ǥ �������� ���� ��θ� ã�� ���� �޸���ƽ �Լ��� ��� �Լ��� �����Ͽ� ����ϴ� Ž�� �˰���\n\n"));
            _stprintf(a + _tcslen(a), _T("�� ���: %d\n"), currentNode->cost);
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


