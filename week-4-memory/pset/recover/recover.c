#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;
#define BLOCK_SIZE 512

void print_usage_reminder(void);
int write_file(int *countptr, FILE *infile, BYTE chunk[BLOCK_SIZE]);
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        print_usage_reminder();
        return 1;
    }

    char *filename = argv[1];
    FILE *infile = fopen(filename, "r");

    if (infile == NULL)
    {
        printf("Could not open file %s.\n", filename);
        return 3;
    }

    BYTE chunk[BLOCK_SIZE];
    int count = 0;
    char *padding = "000";

    FILE *outfile = NULL;

    while (fread(&chunk, sizeof(BYTE), BLOCK_SIZE, infile) == BLOCK_SIZE)
    {
        if (chunk[0] == 0xff && chunk[1] == 0xd8 && chunk[2] == 0xff & chunk[3] >> 4 == 0x0e)
        {
            if (outfile != NULL)
            {
                fclose(outfile);
            }

            char *padding = "000";
            char strfilecount[4];
            sprintf(strfilecount, "%d", count);
            char outfilename[10];
            sprintf(outfilename, "%.*s%s.jpg", 3 - (int) strlen(strfilecount), padding, strfilecount);

            outfile = fopen(outfilename, "w");
            count += 1;
        }

        if (outfile != NULL)
        {
            fwrite(&chunk, sizeof(BYTE), 512, outfile);
        }
    }
    fclose(infile);
    fclose(outfile);
    return 0;
}

void print_usage_reminder(void)
{
    printf("Usage: recover FILE_PATH\n");
}
