#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
#define BLOCK_SIZE 512

void print_usage_reminder(void);
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        print_usage_reminder();
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        fclose(file);
        printf("Could not open file %s.\n", filename);
        return 3;
    }

    BYTE chunk[BLOCK_SIZE];
    int jpg_count = 0;

    while (fread(&chunk, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (chunk[0] == 0xff && chunk[1] == 0xd8 && chunk[2] == 0xff & chunk[3] >> 4 == 0x0e)
        {
            printf("%x %x %x %x\n", chunk[0], chunk[1], chunk[2], chunk[3]);
            jpg_count += 1;
        }
    }

    printf("%i\n", jpg_count);

    fclose(file);
}

void print_usage_reminder(void)
{
    printf("Usage: recover FILE_PATH\n");
}
