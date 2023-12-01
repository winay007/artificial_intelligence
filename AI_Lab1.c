#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 3
#define EMPTY ' '
#define USER 'X'
#define AI 'O'

// Function to print the Tic-Tac-Toe board
void printBoard(char board[SIZE][SIZE]) {
    printf("-------------\n");
    for (int i = 0; i < SIZE; i++) {
        printf("| ");
        for (int j = 0; j < SIZE; j++) {
            printf("%c | ", board[i][j]);
        }
        printf("\n-------------\n");
    }
}

// Function to check if the game is over
bool isGameOver(char board[SIZE][SIZE], char player) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    // Check for a draw
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY)
                return false; // The game is not over yet
        }
    }

    return true; // It's a draw
}

// Function to evaluate the board using a simple heuristic
int evaluateBoard(char board[SIZE][SIZE]) {
    int score = 0;

    // Check rows, columns, and diagonals for potential wins and block the opponent
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == AI && board[i][1] == AI && board[i][2] == EMPTY)
            score += 100; // Two AI in a row with an empty cell
        if (board[i][0] == AI && board[i][2] == AI && board[i][1] == EMPTY)
            score += 100;
        if (board[i][1] == AI && board[i][2] == AI && board[i][0] == EMPTY)
            score += 100;

        if (board[0][i] == AI && board[1][i] == AI && board[2][i] == EMPTY)
            score += 100;
        if (board[0][i] == AI && board[2][i] == AI && board[1][i] == EMPTY)
            score += 100;
        if (board[1][i] == AI && board[2][i] == AI && board[0][i] == EMPTY)
            score += 100;
    }

    if (board[0][0] == AI && board[1][1] == AI && board[2][2] == EMPTY)
        score += 100; // Diagonal win possibilities
    if (board[0][0] == AI && board[2][2] == AI && board[1][1] == EMPTY)
        score += 100;
    if (board[1][1] == AI && board[2][2] == AI && board[0][0] == EMPTY)
        score += 100;
    if (board[0][2] == AI && board[1][1] == AI && board[2][0] == EMPTY)
        score += 100;
    if (board[0][2] == AI && board[2][0] == AI && board[1][1] == EMPTY)
        score += 100;
    if (board[1][1] == AI && board[2][0] == AI && board[0][2] == EMPTY)
        score += 100;

    return score;
}

// Function for the user's move
void userMove(char board[SIZE][SIZE]) {
    int row, col;
    printf("Your turn (X):\n");
    while (1) {
        printf("Enter row (0, 1, or 2) and column (0, 1, or 2) separated by space: ");
        scanf("%d %d", &row, &col);
        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == EMPTY) {
            board[row][col] = USER;
            break;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
}

// Min-Max algorithm for AI's move
int minMax(char board[SIZE][SIZE], int depth, bool isMaximizing) {
    // Evaluate the board
    int score = evaluateBoard(board);

    // Base cases
    if (score == 100) // AI wins
        return score - depth;
    if (score == -100) // User wins
        return score + depth;
    if (!isGameOver(board, AI) && !isGameOver(board, USER))
        return 0; // Draw

    // If it's the AI's turn
    if (isMaximizing) {
        int maxEval = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = AI;
                    int eval = minMax(board, depth + 1, !isMaximizing);
                    board[i][j] = EMPTY; // Undo the move
                    if (eval > maxEval)
                        maxEval = eval;
                }
            }
        }
        return maxEval;
    }
    // If it's the user's turn
    else {
        int minEval = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = USER;
                    int eval = minMax(board, depth + 1, !isMaximizing);
                    board[i][j] = EMPTY; // Undo the move
                    if (eval < minEval)
                        minEval = eval;
                }
            }
        }
        return minEval;
    }
}

// Function for the AI's move using Min-Max algorithm
void aiMove(char board[SIZE][SIZE], int ply) {
    int bestMoveRow = -1, bestMoveCol = -1;
    int bestScore = -1000; // Initialize with a very low value

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = AI;
                int score = minMax(board, 0, false);
                board[i][j] = EMPTY; // Undo the move

                if (score > bestScore) {
                    bestScore = score;
                    bestMoveRow = i;
                    bestMoveCol = j;
                }
            }
        }
    }

    // Apply the best move
    board[bestMoveRow][bestMoveCol] = AI;
}

int main() {
    char board[SIZE][SIZE] = {
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY}
    };

    printf("Welcome to Tic-Tac-Toe!\n");

    int currentPlayer;
    printf("Who should play first? (1: User, 2: AI): ");
    scanf("%d", &currentPlayer);

    int ply;
    printf("Choose Min-Max search depth (1-ply or 2-ply): ");
    scanf("%d", &ply);

    int moveCount = 0;
    bool gameOver = false;

    while (!gameOver) {
        printf("\n");

        if (currentPlayer == 1) {
            userMove(board);
        } else {
            aiMove(board, ply);
        }

        moveCount++;
        printBoard(board);

        int score = evaluateBoard(board);
        printf("Heuristic value after move %d: %d\n", moveCount, score);

        if (isGameOver(board, USER)) {
            printf("User wins! Congratulations!\n");
            gameOver = true;
        } else if (isGameOver(board, AI)) {
            printf("AI wins! Better luck next time.\n");
            gameOver = true;
        } else if (moveCount == SIZE * SIZE) {
            printf("It's a draw! Good game!\n");
            gameOver = true;
        }

        currentPlayer = 3 - currentPlayer; // Switch players (1 -> 2, 2 -> 1)
    }

    return 0;
}
