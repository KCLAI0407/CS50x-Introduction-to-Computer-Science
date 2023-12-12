#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_contain_arg(int argc);
void check_number_string(int lengths);
void check_alpha_only(int lengths, string argv[]);
void check_repeated(int lengths, string argv[]);

int main(int argc, string argv[])
{
    check_contain_arg(argc);
    check_number_string(strlen(argv[1]));
    check_alpha_only(strlen(argv[1]), argv);
    check_repeated(strlen(argv[1]), argv);

    string plain = get_string("plaintext: ");
    int lengths = strlen(plain);
    char cipher[lengths];
    strcpy(cipher, plain);
    char keys[strlen(argv[1])];
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        keys[i] = tolower(argv[1][i]);
    }

    for (int i = 0; i < lengths; i++)
    {
        if (tolower(plain[i]) > 96 && tolower(plain[i]) < 123)
        {
            int j = tolower(plain[i]) - 'a';
            cipher[i] = keys[j];
            if (isupper(plain[i]))
            {
                cipher[i] = toupper(cipher[i]);
            }
        }
    }
    printf("ciphertext: %s\n", cipher);
}

void check_contain_arg(int argc)
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key.\n");
        exit(1);
    }
}

void check_number_string(int lengths)
{
    if (lengths != 26)
    {
        printf("Key must contain 26 characters.\n");
        exit(1);
    }
}

void check_alpha_only(int lengths, string argv[])
{
    int alph_count = 0;
    for (int i = 0; i < lengths; i++)
    {
        if (isalpha(argv[1][i]))
        {
            alph_count++;
        }
    }
    if (alph_count != 26)
    {
        printf("Key must only contain alphabetic characters.\n");
        exit(1);
    }
}

void check_repeated(int lengths, string argv[])
{
    int count_char[26] = {0};
    for (int i = 0; i < lengths; i++)
    {
        int j = tolower(argv[1][i]) - 'a';
        count_char[j]++;
        if (count_char[j] > 1)
        {
            printf("Key must not contain repeated characters.\n");
            exit(1);
        }
    }
}