#include <conio.h>
#include <stdio.h>
#include <string.h>
int l4;
int values[10];
char letters[10];
int pos(char str[], char x)
{
    int i, l;
    l = strlen(str);
    for (i = 0; i < l; i++)
    {
        if (str[i] == x)
            return i;
    }
}
void add(char str[])
{
    int i, j, l;
    l = strlen(str);
    for (i = 0; i < l; i++)
    {
        for (j = l4 - 1; j >= 0; j--)
        {
            if (letters[j] == str[i])
                break;
        }
        if (j == -1)
        {
            letters[l4] = str[i];
            l4++;
        }
    }
}
void findnext()
{
    int i = l4 - 1;
    values[i]++;
    while (values[i] == 10)
    {
        values[i] = 0;
        i--;
        values[i]++;
    }
}
int fact(int n)
{
    if (n == 0)
        return 1;
    else
        return n * fact(n - 1);
}
int perm(int n, int r)
{
    return fact(n) / fact(n - r);
}
int main()
{
    int i, j, k, n1, n2, n3, l1, l2, l3, p, sol = 0, tries;
    char w1[20], w2[20], w3[20];
    printf("enter the words and their sum\n\n");
    gets(w1);
    printf("+");
    gets(w2);
    printf("=");
    gets(w3);
    l1 = strlen(w1);
    l2 = strlen(w2);
    l3 = strlen(w3);
    l4 = 0;
    add(w1);
    add(w2);
    add(w3);
    if (l4 > 10)
    {
        printf("something is wrong with the input");
        getch();
        return 0;
    }
    printf("\n%s", letters);
    for (i = 0; i < l4; i++)
        values[i] = 0;
    p = 0;

    tries = perm(10, l4);
    for (i = 1; i <= tries; i++)
    {
        if ((int)100.0 * i / tries > p)
        {
            p = (int)100.0 * i / tries;
            // system("cls");
            printf("searching %d possibilites\n", tries);
            printf("%d%% complete", p);
        }
        findnext();
        for (j = 0; j < l4; j++)
        {
            for (k = j + 1; k < l4; k++)
            {
                if (values[j] == values[k])
                {
                    findnext();
                    j = -1;
                    break;
                }
            }
        }
        n1 = 0;
        n2 = 0;
        n3 = 0;
        for (j = 0; j < l1; j++)
            n1 = (n1 * 10) + values[pos(letters, w1[j])];
        for (j = 0; j < l2; j++)
            n2 = (n2 * 10) + values[pos(letters, w2[j])];
        for (j = 0; j < l3; j++)
            n3 = (n3 * 10) + values[pos(letters, w3[j])];
        if (n1 + n2 == n3)
        {
            sol++;
            printf("\n\nSolution %d found in %d tries\n\n", sol, i);
            for (j = 0; j < l4; j++)
            {
                printf("%c=%d\n", letters[j], values[j]);
            }
            getch();
        }
        if (i == tries)
        {
            if (sol == 0)
                printf("\n\nNo solution found");
            else
                printf("\n\n%d solutions found", sol);
        }
    }
    getch();
    return 0;
}