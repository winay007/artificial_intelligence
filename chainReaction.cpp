#include <iostream>
#include <cstdlib>
#include <ctime> // For random number generation

using namespace std;

char a[10][10][3];
char p1, p2;
int extra;

void board();
char put(int, int, char);
int checkwin(char);
void multiply(char, int, int);
bool isBoardFull();
pair<int, int> findBestMove(char);
int evaluateBoard(char,int);

int main()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            for (int k = 0; k < 3; k++)
                a[i][j][k] = ' ';

    int r, c, counter = 0, i = 0;

    cout << "\t\tPLAYER 1\nChoose a character: ";
    cin >> p1;
    cout << "\n\n\n\t\tAI BOT (PLAYER 2)\n";
    p2 = 'B'; 

    system("cls");

    do
    {
        extra = 1;

        // Player 1
        cout << "\t\t\tPLAYER 1 (" << p1 << ")\n\n";
        board();
        
        while (true)
        {
            cout << "\n\nChoose a spot: ";
            cin >> r >> c;
            if (a[r][c][0] != p2)
                break;
        }

        put(r, c, p1);
        system("cls");
        
        if (i != 0)
        {
            counter = checkwin(p2);
            if (counter == 1)
            {
                cout << "Player 1 Wins!!\n";
                break;
            }
        }

        // AI Bot (Player 2)
        cout << "\t\t\tAI BOT (PLAYER 2)\n\n";
        board();
        pair<int, int> bestMove = findBestMove(p2);
        put(bestMove.first, bestMove.second, p2);
        system("cls");
        if (i != 0)
        {
            if (counter == 1)
            {
                cout << "AI Bot (Player 2) Wins!!\n";
                break;
            }
        }

        i++;
    } while (counter != 1 && !isBoardFull());

    board();

    return 0;
}

void board()
{
    cout << "       0       1       2       3       4       5       6       7       8       9\n";
    for (int i = 0; i < 10; i++)
    {
        cout << " " << i << " ";
        for (int j = 0; j < 10; j++)
        {
            cout << "| ";
            for (int k = 0; k < 3; k++)
            {
                cout << a[i][j][k] << " ";
            }
        }
        cout << "|  " << i << "\n"
             << endl;
    }
    cout << "       0       1       2       3       4       5       6       7       8       9";
}

char put(int r, int c, char player)
{
    char opp;
    (player == p1) ? opp = p2 : opp = p1;

    if ((r == 0 || r == 9) && (c == 0 || c == 9))
    {
        if (a[r][c][0] == opp)
        {
            a[r][c][0] = player;
        }
        else if (a[r][c][0] == ' ')
            a[r][c][0] = player;
        else if (a[r][c][0] == player)
            multiply(player, r, c);
    }
    else if ((r == 0 && (c > 0 && c < 9)) || (r == 9 && (c > 0 && c < 9)) || (c == 0 && (r > 0 && r < 9)) || (c == 9 && (r > 0 && r < 9)))
    {
        if (a[r][c][0] == opp)
        {
            if (a[r][c][1] == opp)
            {
                multiply(player, r, c);
            }
            else if (a[r][c][1] == ' ')
            {
                a[r][c][0] = player;
                a[r][c][1] = player;
                cout << "right\n";
            }
        }
        else if (a[r][c][0] == ' ' && a[r][c][1] == ' ')
            a[r][c][0] = player;
        else if (a[r][c][0] == player && a[r][c][1] == ' ')
            a[r][c][1] = player;
        else if (a[r][c][0] == player && a[r][c][1] == player)
            multiply(player, r, c);
    }
    else
    {
        if (a[r][c][0] == opp)
        {
            if (a[r][c][1] == ' ' && a[r][c][2] == ' ')
            {
                a[r][c][0] = player;
                a[r][c][1] = player;
            }
            else if (a[r][c][1] == opp && a[r][c][2] == ' ')
            {
                a[r][c][0] = player;
                a[r][c][1] = player;
                a[r][c][2] = player;
            }
            else if (a[r][c][1] == opp && a[r][c][2] == opp)
            {
                multiply(player, r, c);
            }
        }
        else if (a[r][c][0] == ' ' && a[r][c][1] == ' ' && a[r][c][2] == ' ')
            a[r][c][0] = player;
        else if (a[r][c][0] == player && a[r][c][1] == ' ' && a[r][c][2] == ' ')
            a[r][c][1] = player;
        else if (a[r][c][0] == player && a[r][c][1] == player && a[r][c][2] == ' ')
            a[r][c][2] = player;
        else if (a[r][c][0] == player && a[r][c][1] == player && a[r][c][2] == player)
            multiply(player, r, c);
    }

    return 'c';
}

int checkwin(char opp)
{
    int g = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (a[i][j][1] == opp || a[i][j][2] == opp || a[i][j][0] == opp) // mark is p2 if we want to check win for player 1
            {
                g++;
                break;
            }
        }
    }
    if (g == 0)
        return 1;
    else
        return 0;
}

void multiply(char player, int row, int col)
{
    extra = 0;
    a[row][col][0] = ' ';
    a[row][col][1] = ' ';
    a[row][col][2] = ' ';

    if (row < 9)
    {
        put(row + 1, col, player);
    }
    if (col < 9)
    {
        put(row, col + 1, player);
    }
    if (row > 0)
    {
        put(row - 1, col, player);
    }
    if (col > 0)
    {
        put(row, col - 1, player);
    }
}

bool isBoardFull()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (a[i][j][0] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

pair<int, int> findBestMove(char player)
{
    pair<int, int> bestMove = make_pair(-1, -1);
    int bestScore = -10000; // Initialize with a very low score

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (a[i][j][0] == ' ')
            {
                a[i][j][0] = player;
                a[i][j][1] = player;
                int moveScore = evaluateBoard(player,3);
                a[i][j][0] = ' ';
                a[i][j][1] = ' ';

                if (moveScore > bestScore)
                {
                    bestScore = moveScore;
                    bestMove = make_pair(i, j);
                }
            }
        }
    }

    return bestMove;
}

int evaluateBoard(char player,int level)
{
    // You can implement a more sophisticated evaluation function here.
    // This simple version just counts the number of squares owned by the player.
    // int score = 0;

    // for (int i = 0; i < 10; i++)
    // {
    //     for (int j = 0; j < 10; j++)
    //     {
    //         if (a[i][j][0] == player)
    //         {
    //             score++;
    //         }
    //     }
    // }

    // return score;

    // more sophisticated evaluation function
    if(level == 0) return 0;

    int playerScore = 0;
    int opponentScore = 0;

    // Evaluate based on owned squares
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (a[i][j][0] == player)
            {
                playerScore++;
            }
            else if (a[i][j][0] != ' ' && a[i][j][0] != player)
            {
                opponentScore++;
            }
        }
    }

    // Evaluate based on possible future moves
    int playerPotentialScore = 0;
    int opponentPotentialScore = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (a[i][j][0] == ' ')
            {
                // Simulate a potential move and evaluate its impact
                a[i][j][0] = player;
                a[i][j][1] = player;

                int playerMoveScore = evaluateBoard(player,level-1);
                int opponentMoveScore = evaluateBoard((player == p1) ? p2 : p1,level-1);

                playerPotentialScore += playerMoveScore;
                opponentPotentialScore += opponentMoveScore;

                // Undo the simulated move
                a[i][j][0] = ' ';
                a[i][j][1] = ' ';
            }
        }
    }

    // Calculate the final score, considering owned squares and potential moves
    int finalScore = playerScore - opponentScore + playerPotentialScore - opponentPotentialScore;

    return finalScore;
}