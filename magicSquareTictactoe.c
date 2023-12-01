#include <stdio.h>

int curr_opp_no, curr_self_no;
int board[9];
int magic_board[9];
int userChoice;

void reset()
{
    curr_opp_no = 0;
    curr_self_no = 0;
    board[0] = 0;
    board[1] = 0;
    board[2] = 0;
    board[3] = 0;
    board[4] = 0;
    board[5] = 0;
    board[6] = 0;
    board[7] = 0;
    board[8] = 0;
}

char gridChar(int i)
{

    if (i > 0)
        return userChoice == 1 ? 'X' : 'Y';

    if (i < 0)
        return userChoice == 1 ? 'Y' : 'X';

    return ' ';
}

void draw()
{
    printf(" %c | %c | %c\n", gridChar(board[0]), gridChar(board[1]), gridChar(board[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", gridChar(board[3]), gridChar(board[4]), gridChar(board[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n", gridChar(board[6]), gridChar(board[7]), gridChar(board[8]));
}

int magic_value(int x)
{
    for (int i = 0; i < 9; i++)
        if (board[i] == x)
            return magic_board[i];
}

int check_win(int interation)
{

    int recent_magic_opp;
    int recent_magic_self;

    if (interation > 3)
    {
        for (int i = 0; i < 9; i++)
        {
            if (board[i] == curr_opp_no)
                recent_magic_opp = magic_board[i];

            else if (board[i] == curr_self_no)
                recent_magic_self = magic_board[i];
        }

        // self win checking -1 -2
        int recent_self_move = curr_self_no + 1;
        while (recent_self_move < 0)
        {
            int diff_self = 15 - (recent_magic_self + magic_value(recent_self_move));
            if (interation > 4 && diff_self >= 0 && diff_self <= 9)
                for (int i = 0; i < 9; i++)
                    if (magic_board[i] == diff_self && board[i] == 0)
                    {
                        board[i] = --curr_self_no;
                        return 1;
                    }

            recent_self_move++;
        }

        // opponent win checking
        int recent_opp_move = curr_opp_no - 1;
        while (recent_opp_move > 0)
        {
            int diff_opp = 15 - (recent_magic_opp + magic_value(recent_opp_move));
            if (diff_opp >= 0 && diff_opp <= 9)
                for (int i = 0; i < 9; i++)
                    if (magic_board[i] == diff_opp && board[i] == 0)
                    {
                        board[i] = --curr_self_no;
                        return -1;
                    }

            recent_opp_move--;
        }
    }

    // Center
    if (board[4] == 0)
    {
        board[4] = --curr_self_no;
        // printf("%d --------111--\n", curr_self_no);
        return 0;
    }

    // Corner
    {
        int curr = curr_self_no;
        if (board[0] == 0)
            board[0] = --curr_self_no;
        else if (board[2] == 0)
            board[2] = --curr_self_no;
        else if (board[6] == 0)
            board[6] = --curr_self_no;
        else if (board[8] == 0)
            board[8] = --curr_self_no;

        if (curr != curr_self_no)
            return 0;
    }

    // Middle
    {
        int curr = curr_self_no;
        if (board[1] == 0)
            board[1] = --curr_self_no;
        else if (board[3] == 0)
            board[3] = --curr_self_no;
        else if (board[5] == 0)
            board[5] = --curr_self_no;
        else if (board[7] == 0)
            board[7] = --curr_self_no;

        if (curr != curr_self_no)
            return 0;
    }

    return 0;
}

void game()
{
    while (1)
    {
        printf("Choose your Player 'X' or 'O' Play (1) or (2) ");
        scanf("%d", &userChoice);
        printf("\n");

        if (userChoice == 1 || userChoice == 2)
        {
            for (int i = 0; i < 9; i++)
            {
                int choice;

                if (i % 2 == 1)
                {
                    int result = check_win(i);
                    printf("System Played\n\n");
                    draw();
                    printf("\n\n");
                    if (result == 1)
                    {
                        printf("Machinee Winnn");
                        reset();
                        break;
                    }
                }
                else
                {
                    int row, col;

                    while (1)
                    {
                        printf("Enter location where you want to make move [1 - 9] ");
                        scanf("%d", &choice);
                        printf("\n");

                        if (board[choice - 1] == 0)
                            break;

                        printf("Invalid Move\n");
                    }

                    board[choice - 1] = ++curr_opp_no;

                    draw();
                    printf("\n\n");
                }
            }
        }
        else
            continue;

        printf("Tie reusltt \n\n\n");
        reset();
    }
}

int main()
{
    magic_board[0] = 2;
    magic_board[1] = 7;
    magic_board[2] = 6;
    magic_board[3] = 9;
    magic_board[4] = 5;
    magic_board[5] = 1;
    magic_board[6] = 4;
    magic_board[7] = 3;
    magic_board[8] = 8;
    reset();
    game();
}

