#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

int default_kernel[3][3] =
{
    { 1, 1, 1 },
    { 1, 1, 1 },
    { 1, 1, 1 },
};
int gx_kernel[3][3] =
{
    { -1, 0, 1 },
    { -2, 0, 2 },
    { -1, 0, 1 },
};
int gy_kernel[3][3] =
{
    { -1, -2, -1 },
    { 0, 0, 0 },
    { 1, 2, 1 },
};

BYTE clamp_color(int target);
RGBTRIPLE get_box_average(int height, int width, int center_h, int center_w, RGBTRIPLE image[height][width],
                          char weight_kernel);
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
            image[h][w] = get_box_average(height, width, h, w, original_image, 'd');
        }
    }
    free(original_image);
    return;
}

// weight_kernel is d for default, x for gx and y for gy
RGBTRIPLE get_box_average(int height, int width, int center_h, int center_w, RGBTRIPLE image[height][width],
                          char weight_kernel)
{
    int redSum = 0;
    int greenSum = 0;
    int blueSum = 0;
    int count = 0;

    int (*kernel)[3][3] = &default_kernel;

    for (int j = 0; j < 3; j++)
    {
        int h = center_h + j - 1;
        if (h < 0 || h > height - 1)
        {
            continue;
        }
        for (int i = 0; i < 3; i++)
        {
            int w = center_w + i - 1;
            if (w < 0 || w > width - 1)
            {
                continue;
            }
            int my_little_kernel_value = (*kernel)[j][i];
            count += 1;
            redSum += image[h][w].rgbtRed * (*kernel)[j][i];
            greenSum += image[h][w].rgbtGreen * (*kernel)[j][i];
            blueSum += image[h][w].rgbtBlue * (*kernel)[j][i];
        }
    }

    RGBTRIPLE average;
    average.rgbtRed = round((float) redSum / count);
    average.rgbtGreen = round((float) greenSum / count);
    average.rgbtBlue = round((float) blueSum / count);
    return average;
}

// void calculate_weighted_box_sum(int sum[3], )

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
