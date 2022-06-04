#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

BYTE clamp_color(int target);
RGBTRIPLE get_box_average(int height, int width, int center_h, int center_w, RGBTRIPLE image[height][width],
                          RGBTRIPLE original_image[height][width]);
void copy_image(int height, int width, RGBTRIPLE original[height][width], RGBTRIPLE copy[height][width]);

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half_width = ceil((float) width / 2);
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < half_width; w++)
        {
            RGBTRIPLE swap = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*original_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    copy_image(height, width, image, original_image);

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = get_box_average(height, width, h, w, image, original_image);
        }
    }
    free(original_image);
    return;
}

RGBTRIPLE get_box_average(int height, int width, int center_h, int center_w, RGBTRIPLE image[height][width],
                          RGBTRIPLE original_image[height][width])
{
    int redSum = 0;
    int greenSum = 0;
    int blueSum = 0;
    int count = 0;
    for (int j = -1; j <= 1; j++)
    {
        int h = center_h + j;
        if (h < 0 || h > height - 1)
        {
            continue;
        }
        for (int i = -1; i <= 1; i++)
        {
            int w = center_w + i;
            if (w < 0 || w > width - 1)
            {
                continue;
            }
            count += 1;
            redSum += original_image[h][w].rgbtRed;
            greenSum += original_image[h][w].rgbtGreen;
            blueSum += original_image[h][w].rgbtBlue;
        }
    }

    RGBTRIPLE average;
    average.rgbtRed = round((float) redSum / count);
    average.rgbtGreen = round((float) greenSum / count);
    average.rgbtBlue = round((float) blueSum / count);
    return average;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*original_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    copy_image(height, width, image, original_image);

    return;
}

void copy_image(int height, int width, RGBTRIPLE original[height][width], RGBTRIPLE copy[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w] = original[h][w];
        }
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

