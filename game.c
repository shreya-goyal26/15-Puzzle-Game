#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define SIZE 4

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void createMatrix(int arr[SIZE][SIZE])
{
    int nums[16];

    for (int i = 0; i < 15; i++)
        nums[i] = i + 1;

    nums[15] = 0;

    // Fisher-Yates shuffle
    for (int i = 15; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(&nums[i], &nums[j]);
    }

    int k = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            arr[i][j] = nums[k++];
}

void showMatrix(int arr[SIZE][SIZE])
{
    printf("\n---------------------\n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("| ");
        for (int j = 0; j < SIZE; j++)
        {
            if (arr[i][j] != 0)
                printf("%2d | ", arr[i][j]);
            else
                printf("   | ");
        }
        printf("\n");
    }
    printf("---------------------\n");
}

int winner(int arr[SIZE][SIZE])
{
    int count = 1;

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == SIZE - 1 && j == SIZE - 1)
                return 1;

            if (arr[i][j] != count++)
                return 0;
        }
    }
    return 1;
}

void findZero(int arr[SIZE][SIZE], int *r, int *c)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (arr[i][j] == 0)
            {
                *r = i;
                *c = j;
                return;
            }
}

int shiftUp(int arr[SIZE][SIZE])
{
    int r, c;
    findZero(arr, &r, &c);
    if (r == SIZE - 1)
        return 0;
    swap(&arr[r][c], &arr[r + 1][c]);
    return 1;
}

int shiftDown(int arr[SIZE][SIZE])
{
    int r, c;
    findZero(arr, &r, &c);
    if (r == 0)
        return 0;
    swap(&arr[r][c], &arr[r - 1][c]);
    return 1;
}

int shiftLeft(int arr[SIZE][SIZE])
{
    int r, c;
    findZero(arr, &r, &c);
    if (c == SIZE - 1)
        return 0;
    swap(&arr[r][c], &arr[r][c + 1]);
    return 1;
}

int shiftRight(int arr[SIZE][SIZE])
{
    int r, c;
    findZero(arr, &r, &c);
    if (c == 0)
        return 0;
    swap(&arr[r][c], &arr[r][c - 1]);
    return 1;
}

int main()
{
    srand(time(NULL));

    int arr[SIZE][SIZE];
    int maxTry = 100;
    char name[20];

    printf("Enter Player Name: ");
    scanf("%19s", name);

    createMatrix(arr);

    while (!winner(arr) && maxTry > 0)
    {
        system("cls");

        printf("Player: %s | Remaining Moves: %d\n", name, maxTry);
        printf("Use Arrow Keys | Press E to Exit\n");

        showMatrix(arr);

        int moved = 0;
        int key = getch();

        if (key == 224)   // arrow prefix (modern systems)
        {
            key = getch();

            switch (key)
            {
            case 72: moved = shiftUp(arr); break;
            case 80: moved = shiftDown(arr); break;
            case 75: moved = shiftLeft(arr); break;
            case 77: moved = shiftRight(arr); break;
            }
        }
        else if (key == 'e' || key == 'E')
        {
            printf("\nThanks for playing!\n");
            break;
        }

        if (moved)
            maxTry--;
    }

    system("cls");

    if (winner(arr))
        printf("\n🎉 Congratulations %s! You won!\n", name);
    else
        printf("\nGame Over!\n");

    printf("\nPress any key to exit...");
    getch();

    return 0;
}