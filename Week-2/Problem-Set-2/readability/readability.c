#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    // count the number of letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Coleman-Liau index
    double L = ((double) letters / (double) words) * 100;
    double S = ((double) sentences / (double) words) * 100;
    double index = round(0.0588 * L - 0.296 * S - 15.8);

    // print the grade
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}

int count_letters(string text)
{
    int num_letter = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            num_letter++;
        }
    }

    return num_letter;
}

int count_words(string text)
{
    int num_words = 1;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (isspace(text[i]))
        {
            num_words++;
        }
    }

    return num_words;
}

int count_sentences(string text)
{
    int num_sentence = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            num_sentence++;
        }
    }

    return num_sentence;
}
