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
RGBTRIPLE get_box_average(int height, int width, int center_h, int center_w, RGBTRIPLE image[height][width]);
int calculate_weighted_box_sum(int height, int width, int center_h, int center_w, RGBTRIPLE image[height][width],
                               int sum[3], char weight_kernel_code);
int *get_kernel(char kernel_code);
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
            image[h][w] = get_box_average(height, width, h, w, original_image);
        }
    }
    free(original_image);
    return;
}

RGBTRIPLE get_box_average(int height, int width, int center_h, int center_w, RGBTRIPLE image[height][width])
{
    int sum[3] = { 0, 0, 0 };
    int count = calculate_weighted_box_sum(height, width, center_h, center_w, image, sum, 'd');

    RGBTRIPLE average;
    average.rgbtRed = round((float) sum[0] / count);
    average.rgbtGreen = round((float) sum[1] / count);
    average.rgbtBlue = round((float) sum[2] / count);
    return average;
}

// weight_kernel_code is 'd' for default, 'x' for gx and 'y' for gy
int calculate_weighted_box_sum(int height, int width, int center_h, int center_w, RGBTRIPLE image[height][width],
                               int sum[3], char weight_kernel_code)
{
    int count = 0;
    int (*kernel)[3][3] = get_kernel(weight_kernel_code);

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
            count += 1;
            sum[0] += image[h][w].rgbtRed * (*kernel)[j][i];
            sum[1] += image[h][w].rgbtGreen * (*kernel)[j][i];
            sum[2] += image[h][w].rgbtBlue * (*kernel)[j][i];
        }
    }
    return count;
}

int *get_kernel(char kernel_code)
{
    if (kernel_code == 'd')
    {
        return &default_kernel;
    }

    if (kernel_code == 'x')
    {
        return &gx_kernel;
    }

    if (kernel_code == 'y')
    {
        return &gy_kernel;
    }
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
