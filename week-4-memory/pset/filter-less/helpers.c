#include <math.h>
#include <stdio.h>
#include "helpers.h"

BYTE clamp_color(int target);
RGBTRIPLE get_box_average(int height, int width, int h, int w, RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int sum = image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed;
            int average = round(sum / 3.0);
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            BYTE originalRed = image[h][w].rgbtRed;
            BYTE originalGreen = image[h][w].rgbtGreen;
            BYTE originalBlue = image[h][w].rgbtBlue;

            image[h][w].rgbtRed = clamp_color(round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue));
            image[h][w].rgbtGreen = clamp_color(round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue));
            image[h][w].rgbtBlue = clamp_color(round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE myimage[3][3];
    myimage[0][0].rgbtRed = 10;
    myimage[0][0].rgbtGreen = 20;
    myimage[0][0].rgbtBlue = 30;

    myimage[0][1].rgbtRed = 40;
    myimage[0][1].rgbtGreen = 50;
    myimage[0][1].rgbtBlue = 60;

    myimage[0][2].rgbtRed = 70;
    myimage[0][2].rgbtGreen = 80;
    myimage[0][2].rgbtBlue = 90;

    myimage[1][0].rgbtRed = 110;
    myimage[1][0].rgbtGreen = 130;
    myimage[1][0].rgbtBlue = 140;

    myimage[1][1].rgbtRed = 120;
    myimage[1][1].rgbtGreen = 140;
    myimage[1][1].rgbtBlue = 150;

    myimage[1][2].rgbtRed = 130;
    myimage[1][2].rgbtGreen = 150;
    myimage[1][2].rgbtBlue = 160;

    myimage[2][0].rgbtRed = 200;
    myimage[2][0].rgbtGreen = 210;
    myimage[2][0].rgbtBlue = 220;

    myimage[2][1].rgbtRed = 220;
    myimage[2][1].rgbtGreen = 230;
    myimage[2][1].rgbtBlue = 240;

    myimage[2][2].rgbtRed = 240;
    myimage[2][2].rgbtGreen = 250;
    myimage[2][2].rgbtBlue = 255;
    for (int h = 0; h < 3; h++)
    {
        for (int w = 0; w < 3; w++)
        {
            image[h][w] = get_box_average(height, width, h, w, myimage);
        }
    }
    return;
}

RGBTRIPLE get_box_average(int height, int width, int center_h, int center_w, RGBTRIPLE image[height][width])
{
    int redSum = 0;
    int greenSum = 0;
    int blueSum = 0;
    int count = 0;
    if (center_h == 1 && center_w == 1)
    {
        for (int h = center_h - 1; h <= center_h + 1; h++)
        {
            if (h < 0 || h > height - 1)
            {
                continue;
            }
            for (int w = center_w - 1; w <= center_w + 1; w++)
            {
                if (w < 0 || w > width - 1)
                {
                    continue;
                }
                count += 1;
                redSum += image[h][w].rgbtRed;
                greenSum += image[h][w].rgbtGreen;
                blueSum += image[h][w].rgbtBlue;
            }
            printf("row %i = (%i, %i, %i) ", h + 1, image[h][0].rgbtRed, image[h][0].rgbtGreen, image[h][0].rgbtBlue);
            printf("(%i, %i, %i) ", image[h][1].rgbtRed, image[h][1].rgbtGreen, image[h][1].rgbtBlue);
            printf("(%i, %i, %i)\n", image[h][2].rgbtRed, image[h][2].rgbtGreen, image[h][2].rgbtBlue);
        }
        RGBTRIPLE average;
        average.rgbtRed = round((float) redSum / count);
        average.rgbtGreen = round((float) greenSum / count);
        average.rgbtBlue = round((float) blueSum / count);
        printf("sum = (%i, %i, %i)\n", redSum, greenSum, blueSum);
        printf("count = %i\n", count);
        printf("average = (%i, %i, %i)\n", average.rgbtRed, average.rgbtGreen, average.rgbtBlue);
        return average;
    }
    else
    {
        for (int h = center_h - 1; h <= center_h + 1; h++)
        {
            if (h < 0 || h > height - 1)
            {
                continue;
            }
            for (int w = center_w - 1; w <= center_w + 1; w++)
            {
                if (w < 0 || w > width - 1)
                {
                    continue;
                }
                count += 1;
                redSum += image[h][w].rgbtRed;
                greenSum += image[h][w].rgbtGreen;
                blueSum += image[h][w].rgbtBlue;
            }
        }

        RGBTRIPLE average;
        average.rgbtRed = round((float) redSum / count);
        average.rgbtGreen = round((float) greenSum / count);
        average.rgbtBlue = round((float) blueSum / count);
        return average;
    }
}

BYTE clamp_color(int target)
{
    if (target > 255)
    {
        return 255;
    }
    if (target < 0)
    {
        return 0;
    }
    return target;
}
