#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "stack.h"

#define ROWS 5
#define COLS 12
#define OBSTACLE -1
#define START -2
#define END -3

typedef struct Node {
    int row, col;
    int h;
    struct Node* parent;
} Node;

Node* createNode(int row, int col, int h, Node* parent) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->row = row;
    newNode->col = col;
    newNode->h = h;
    newNode->parent = parent;
    return newNode;
}

bool isValid(int row, int col) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS);
}

bool isObstacle(int maze[ROWS][COLS], int row, int col) {
    return maze[row][col] == OBSTACLE;
}

bool isDestination(int maze[ROWS][COLS], int row, int col) {
    return maze[row][col] == END;
}

int heuristic(int row, int col, int endRow, int endCol) {
    return abs(endRow - row) + abs(endCol - col);
}

void bestFirstSearch(int maze[ROWS][COLS], int startRow, int startCol, int endRow, int endCol) {
    Stack s;
    initialize(&s);
    bool closedList[ROWS][COLS];
    memset(closedList, false, sizeof(closedList));

    Node* openList[ROWS * COLS];
    int openListCount = 1; // Start with one node (the starting node)
    openList[0] = createNode(startRow, startCol, heuristic(startRow, startCol, endRow, endCol), NULL);

    while (openListCount > 0) {
        int currentIndex = 0;
        for (int i = 1; i < openListCount; i++) {
            if (openList[i]->h < openList[currentIndex]->h) {
                currentIndex = i;
            }
        }

        Node* currentNode = openList[currentIndex];
        openList[currentIndex] = openList[openListCount - 1];
        openListCount--;

        int row = currentNode->row;
        int col = currentNode->col;
        closedList[row][col] = true;

        if (isDestination(maze, row, col)) {
            printf("Path found!\n");

            // Trace the path
            while (currentNode != NULL) {
                push(&s,currentNode->row,currentNode->col);
                // printf("(%d, %d) -> ", currentNode->row, currentNode->col);
                currentNode = currentNode->parent;
            }
            StackElement se;
            while(!isEmpty(&s)){
                se = pop(&s);
                printf("(%d, %d) -> ", se.data[0], se.data[1]);
            }
            printf("\n");

            return;
        }

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++) {
            int newRow = row + dr[i];
            int newCol = col + dc[i];

            if (isValid(newRow, newCol) && !closedList[newRow][newCol] && !isObstacle(maze, newRow, newCol)) {
                int h = heuristic(newRow, newCol, endRow, endCol);

                bool inOpenList = false;
                for (int j = 0; j < openListCount; j++) {
                    if (openList[j]->row == newRow && openList[j]->col == newCol) {
                        inOpenList = true;
                        break;
                    }
                }

                if (!inOpenList) {
                    openList[openListCount++] = createNode(newRow, newCol, h, currentNode);
                }
            }
        }
    }

    printf("No path found.\n");
}

int main() {
    int maze[ROWS][COLS] = {
        {8, 7, 6, 5, 4, 3, 2, 3, 4, 5, 6},
        {7, OBSTACLE, 5, 4, 3, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, 5},
        {6, OBSTACLE, OBSTACLE, 3, 2, 1, END, 1, 2, OBSTACLE, 4},
        {START, 6, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, 5},
        {8, 7, 6, 5, 4, 3, 2, 3, 4, 5, 6}
    };

    int startRow, startCol, endRow, endCol;

    // Find the positions of START and END in the maze
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == START) {
                startRow = i;
                startCol = j;
            } else if (maze[i][j] == END) {
                endRow = i;
                endCol = j;
            }
        }
    }

    bestFirstSearch(maze, startRow, startCol, endRow, endCol);

    return 0;
}
