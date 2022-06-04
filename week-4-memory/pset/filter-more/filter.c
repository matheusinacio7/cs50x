#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
    // Define allowable filters
    char *filters = "begr";

    // Get filter flag and check validity
    char filter = getopt(argc, argv, filters);
    if (filter == '?')
    {
        printf("Invalid filter.\n");
        return 1;
    }

    // Ensure only one filter
    if (getopt(argc, argv, filters) != -1)
    {
        printf("Only one filter allowed.\n");
        return 2;
    }

    // Ensure proper usage
    if (argc != optind + 2)
    {
        printf("Usage: ./filter [flag] infile outfile\n");
        return 3;
    }

    // Remember filenames
    char *infile = argv[optind];
    char *outfile = argv[optind + 1];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 5;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 6;
    }

    // Get image's dimensions
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // Allocate memory for image
    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        printf("Not enough memory to store image.\n");
        fclose(outptr);
        fclose(inptr);
        return 7;
    }

    // Determine padding for scanlines
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // Iterate over infile's scanlines
    for (int i = 0; i < height; i++)
    {
        // Read row into pixel array
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);

        // Skip over padding
        fseek(inptr, padding, SEEK_CUR);
    }

    // RGBTRIPLE myimage[3][3];
    // myimage[0][0].rgbtRed = 10;
    // myimage[0][0].rgbtGreen = 20;
    // myimage[0][0].rgbtBlue = 30;

    // myimage[0][1].rgbtRed = 40;
    // myimage[0][1].rgbtGreen = 50;
    // myimage[0][1].rgbtBlue = 60;

    // myimage[0][2].rgbtRed = 70;
    // myimage[0][2].rgbtGreen = 80;
    // myimage[0][2].rgbtBlue = 90;

    // myimage[1][0].rgbtRed = 110;
    // myimage[1][0].rgbtGreen = 130;
    // myimage[1][0].rgbtBlue = 140;

    // myimage[1][1].rgbtRed = 120;
    // myimage[1][1].rgbtGreen = 140;
    // myimage[1][1].rgbtBlue = 150;

    // myimage[1][2].rgbtRed = 130;
    // myimage[1][2].rgbtGreen = 150;
    // myimage[1][2].rgbtBlue = 160;

    // myimage[2][0].rgbtRed = 200;
    // myimage[2][0].rgbtGreen = 210;
    // myimage[2][0].rgbtBlue = 220;

    // myimage[2][1].rgbtRed = 220;
    // myimage[2][1].rgbtGreen = 230;
    // myimage[2][1].rgbtBlue = 240;

    // myimage[2][2].rgbtRed = 240;
    // myimage[2][2].rgbtGreen = 250;
    // myimage[2][2].rgbtBlue = 255;

    // Filter image
    switch (filter)
    {
        // Blur
        case 'b':
            blur(height, width, image);
            // blur(3, 3, myimage);
            break;

        // Edges
        case 'e':
            edges(height, width, image);
            break;

        // Grayscale
        case 'g':
            grayscale(height, width, image);
            break;

        // Reflect
        case 'r':
            reflect(height, width, image);
            break;
    }

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write new pixels to outfile
    for (int i = 0; i < height; i++)
    {
        // Write row to outfile
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

        // Write padding at end of row
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Free memory for image
    free(image);

    // Close files
    fclose(inptr);
    fclose(outptr);
    return 0;
}
