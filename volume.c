#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
typedef int16_t SAMPLE;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s INPUT.wav OUTPUT.wav VOLUME\n", argv[0]);
        return 1;
    }

    char *input_file = argv[1];
    char *output_file = argv[2];
    float volume = atof(argv[3]);

    if (volume <= 0.0)
    {
        printf("Volume must be a positive number.\n");
        return 1;
    }

    FILE *input = fopen(input_file, "r");
    if (input == NULL)
    {
        printf("Could not open %s.\n", input_file);
        return 1;
    }

    FILE *output = fopen(output_file, "w");
    if (output == NULL)
    {
        fclose(input);
        printf("Could not create %s.\n", output_file);
        return 1;
    }

    // Read the WAV file header
    BYTE header[44];
    fread(header, sizeof(BYTE), 44, input);
    fwrite(header, sizeof(BYTE), 44, output);

    // Process the audio samples
    while (true)
    {
        SAMPLE buffer;
        fread(&buffer, sizeof(SAMPLE), 1, input);

        if (feof(input))
        {
            break;
        }

        buffer = buffer * volume;
        fwrite(&buffer, sizeof(SAMPLE), 1, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}
