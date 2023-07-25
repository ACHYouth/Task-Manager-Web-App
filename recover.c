#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 512
#define JPEG_SIGNATURE 0xffd8ff

int is_jpeg_start(uint8_t buffer[])
{
    return (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s card.raw\n", argv[0]);
        return 1;
    }

    char *infile = argv[1];
    FILE *file = fopen(infile, "r");

    if (file == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    uint8_t buffer[BLOCK_SIZE];
    int image_count = 0;
    FILE *output = NULL;

    while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (is_jpeg_start(buffer))
        {
            if (output != NULL)
            {
                fclose(output);
            }

            char filename[8];
            sprintf(filename, "%03i.jpg", image_count);
            output = fopen(filename, "w");

            if (output == NULL)
            {
                printf("Could not create %s.\n", filename);
                fclose(file);
                return 1;
            }

            image_count++;
        }

        if (output != NULL)
        {
            fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, output);
        }
    }

    if (output != NULL)
    {
        fclose(output);
    }

    fclose(file);
    return 0;
}
