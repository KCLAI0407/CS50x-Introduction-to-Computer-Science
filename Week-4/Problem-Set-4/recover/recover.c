#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define JPEG_size 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r"); // Open memory card
    if (infile == NULL)
    {
        printf("Could not open the file");
        return 2;
    }

    BYTE buffer[JPEG_size];

    char out_name[8];
    int file_count = 0;
    FILE *img = NULL;

    while (fread(buffer, 1, JPEG_size, infile) == JPEG_size) // Read 512 bytes into buffer
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // if start of new JPEG
        {
            if (img == NULL) // if first JPEG
            {
                sprintf(out_name, "%03i.jpg", file_count);
                img = fopen(out_name, "w");
                fwrite(buffer, sizeof(buffer), 1, img);
            }
            else if (img != NULL) // if already found a JPEG
            {
                fclose(img);
                file_count++;
                sprintf(out_name, "%03i.jpg", file_count);
                img = fopen(out_name, "w");
                fwrite(buffer, sizeof(buffer), 1, img);
            }
        }
        else if (img != NULL) // Else if already found JPEG
        {
            fwrite(buffer, sizeof(buffer), 1, img);
        }
    }
    fclose(img);
    fclose(infile);

    return 0;
}