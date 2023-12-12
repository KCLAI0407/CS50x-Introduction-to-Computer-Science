#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    // prompt for input between 1 and 8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //
    for (int i = 0; i < height; i++)
    {
        for (int k = i + 1; k < height; k++)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        printf("  ");

        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
