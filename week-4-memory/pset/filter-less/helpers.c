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
    RGBTRIPLE original_image[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            original_image[height][width] = image[height][width];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;
            int count = 0;
            for (int j = h - 1; j <= h + 1; j++)
            {
                if (j < 0 || j > height - 1)
                {
                    continue;
                }
                for (int i = w - 1; i <= w + 1; i++)
                {
                    if (i < 0 || i > width - 1)
                    {
                        continue;
                    }
                    count += 1;
                    redSum += original_image[j][i].rgbtRed;
                    greenSum += original_image[j][i].rgbtGreen;
                    blueSum += original_image[j][i].rgbtBlue;
                }
            }
            image[h][w].rgbtRed = round((float) redSum / count);
            image[h][w].rgbtGreen = round((float) greenSum / count);
            image[h][w].rgbtBlue = round((float) blueSum / count);
        }
    }
    return;
}

// RGBTRIPLE get_box_average(int height, int width, int center_h, int center_w, RGBTRIPLE image[height][width])
// {
//     int redSum = 0;
//     int greenSum = 0;
//     int blueSum = 0;
//     int count = 0;
//     if (center_h == 1 && center_w == 1)
//     {
//         for (int j = center_h - 1; j <= center_h + 1; j++)
//         {
//             if (j < 0 || j > height - 1)
//             {
//                 continue;
//             }
//             for (int i = center_w - 1; i <= center_w + 1; i++)
//             {
//                 if (i < 0 || i > width - 1)
//                 {
//                     continue;
//                 }
//                 count += 1;
//                 redSum += image[j][i].rgbtRed;
//                 greenSum += image[j][i].rgbtGreen;
//                 blueSum += image[j][i].rgbtBlue;
//             }
//             printf("row %i = (%i, %i, %i) ", j + 1, image[j][0].rgbtRed, image[j][0].rgbtGreen, image[j][0].rgbtBlue);
//             printf("(%i, %i, %i) ", image[j][1].rgbtRed, image[j][1].rgbtGreen, image[j][1].rgbtBlue);
//             printf("(%i, %i, %i)\n", image[j][2].rgbtRed, image[j][2].rgbtGreen, image[j][2].rgbtBlue);
//         }
//         RGBTRIPLE average;
//         average.rgbtRed = round((float) redSum / count);
//         average.rgbtGreen = round((float) greenSum / count);
//         average.rgbtBlue = round((float) blueSum / count);
//         printf("sum = (%i, %i, %i)\n", redSum, greenSum, blueSum);
//         printf("count = %i\n", count);
//         printf("average = (%i, %i, %i)\n", average.rgbtRed, average.rgbtGreen, average.rgbtBlue);
//         return average;
//     }
//     else
//     {
//         for (int h = center_h - 1; h <= center_h + 1; h++)
//         {
//             if (h < 0 || h > height - 1)
//             {
//                 continue;
//             }
//             for (int w = center_w - 1; w <= center_w + 1; w++)
//             {
//                 if (w < 0 || w > width - 1)
//                 {
//                     continue;
//                 }
//                 count += 1;
//                 redSum += image[h][w].rgbtRed;
//                 greenSum += image[h][w].rgbtGreen;
//                 blueSum += image[h][w].rgbtBlue;
//             }
//         }

//         RGBTRIPLE average;
//         average.rgbtRed = round((float) redSum / count);
//         average.rgbtGreen = round((float) greenSum / count);
//         average.rgbtBlue = round((float) blueSum / count);
//         return average;
//     }
// }

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
