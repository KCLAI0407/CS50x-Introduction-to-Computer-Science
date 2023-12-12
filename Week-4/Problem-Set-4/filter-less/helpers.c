#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float gray;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtRed = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRGB[3];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRGB[0] = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            sepiaRGB[1] = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaRGB[2] = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            for (int k = 0; k < 3; k++)
            {
                if (sepiaRGB[k] > 255)
                {
                    sepiaRGB[k] = 255;
                }
            }

            image[i][j].rgbtRed = sepiaRGB[0];
            image[i][j].rgbtGreen = sepiaRGB[1];
            image[i][j].rgbtBlue = sepiaRGB[2];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflectRGB;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            reflectRGB = image[i][j];

            image[i][j] = image[i][width - 1 - j];

            image[i][width - 1 - j] = reflectRGB;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blurRGB[3] = {0};
            int count = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k >= 0 && i + k <= height - 1) && (j + l >= 0 && j + l <= width - 1))
                    {
                        count++;
                        blurRGB[0] += copy[i + k][j + l].rgbtRed;
                        blurRGB[1] += copy[i + k][j + l].rgbtGreen;
                        blurRGB[2] += copy[i + k][j + l].rgbtBlue;
                    }
                }
            }

            image[i][j].rgbtRed = round(blurRGB[0] / count);
            image[i][j].rgbtGreen = round(blurRGB[1] / count);
            image[i][j].rgbtBlue = round(blurRGB[2] / count);
        }
    }

    return;
}
