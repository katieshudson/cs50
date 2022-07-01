#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    // take an image and turn it into black and white version of same image
    // as long as r g b are the same value for each pixel, you get a different shade of grey
    // take average of the r, g, b by looping through pixels

    // loop through each pixel [i][j]
    for (int i = 0; i < (height); i++)
    {
        for (int j = 0; j < (width); j++)
        {
            // variables for rbg values to make the avg calculation cleaner
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // calculate avg rgb amt and round UP to nearest int
            int avg_rgb = round(((float)(red) + (float)(green) + (float)(blue)) / 3.0); // round up to nearet int

            // convert each rbg pixel value to avg
            image[i][j].rgbtRed = avg_rgb;
            image[i][j].rgbtGreen = avg_rgb;
            image[i][j].rgbtBlue = avg_rgb;

        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // take an image and turn it into a sepia version of the same image

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // variables to store original colour values for each pixel
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // formula to calculate each pixel to sepia equivalent
            int sepiaRed = round((0.393 * originalRed) + (0.769 * originalGreen) + (0.189 * originalBlue));
            int sepiaGreen = round((0.349 * originalRed) + (0.686 * originalGreen) + (0.168 * originalBlue));
            int sepiaBlue = round((0.272 * originalRed) + (0.534 * originalGreen) + (0.131 * originalBlue));

            // convert original values to sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;

            // ensure values do not exceed 255
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtGreen = 255;
            }

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // take an image and reflect it HORIZONTALLY (mirror image)

    // rows stay in the same order, but pixels in row switch places
    // for every row - swap pixels on horizontally opposite sides, then repeat for each row
    // swapping two values with a temporary variable.

    for (int i = 0; i < height; i++) //row
    {
        for (int j = 0; j < (width / 2); j++) // column   (only iterate through first half)
        {
            // store original values in temp file of first half of row
            int temp_red = image[i][j].rgbtRed;
            int temp_green = image[i][j].rgbtGreen;
            int temp_blue = image[i][j].rgbtBlue;

            // swap original value to opposite side of row  (a --> b) - first half of row to second half
            image[i][j].rgbtRed = image[i][width - (j + 1)].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - (j + 1)].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - (j + 1)].rgbtBlue;

            // swap second half of row value to first half of row (b --> a, but use temp)
            image[i][width - (j + 1)].rgbtRed = temp_red;
            image[i][width - (j + 1)].rgbtGreen = temp_green;
            image[i][width - (j + 1)].rgbtBlue = temp_blue;

        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // take an image and turn it into a box blurred version of the same image

    // temp variable to store original values
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // store original values in temp.
            // needs its own loop to not mess with the blur calculations
            temp[i][j] = image[i][j];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // variables to keep track of the rgb totals per pixel
            int total_red = 0;
            int total_green = 0;
            int total_blue = 0;

            // keep track of the # of total pixels
            float total_pixels = 0.0;

            /* CORNERS */
            // top right corner
            if (i >= 0 && j >= 0)
            {
                // add up rgb
                total_red += temp[i][j].rgbtRed;
                total_green += temp[i][j].rgbtGreen;
                total_blue += temp[i][j].rgbtBlue;
                total_pixels++;
            }

            // top left corner
            if (i >= 0 && j - 1 >= 0)
            {
                // add up rgb
                total_red += temp[i][j - 1].rgbtRed;
                total_green += temp[i][j - 1].rgbtGreen;
                total_blue += temp[i][j - 1].rgbtBlue;
                total_pixels++;
            }

            // bottom right corner
            if (i - 1 >= 0 && j >= 0)
            {
                // add up rgb
                total_red += temp[i - 1][j].rgbtRed;
                total_green += temp[i - 1][j].rgbtGreen;
                total_blue += temp[i - 1][j].rgbtBlue;
                total_pixels++;
            }

            // bottom left corner
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                // add up rgb
                total_red += temp[i - 1][j - 1].rgbtRed;
                total_green += temp[i - 1][j - 1].rgbtGreen;
                total_blue += temp[i - 1][j - 1].rgbtBlue;
                total_pixels++;
            }

            /* EDGES */
            // top middle edge
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                // add up rgb
                total_red += temp[i][j + 1].rgbtRed;
                total_green += temp[i][j + 1].rgbtGreen;
                total_blue += temp[i][j + 1].rgbtBlue;
                total_pixels++;
            }

            // bottom middle edge
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                // add up rgb
                total_red += temp[i - 1][j + 1].rgbtRed;
                total_green += temp[i - 1][j + 1].rgbtGreen;
                total_blue += temp[i - 1][j + 1].rgbtBlue;
                total_pixels++;
            }

            // left middle edge
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                // add up rgb
                total_red += temp[i + 1][j].rgbtRed;
                total_green += temp[i + 1][j].rgbtGreen;
                total_blue += temp[i + 1][j].rgbtBlue;
                total_pixels++;
            }

            // right middle edge
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                // add up rgb
                total_red += temp[i + 1][j - 1].rgbtRed;
                total_green += temp[i + 1][j - 1].rgbtGreen;
                total_blue += temp[i + 1][j - 1].rgbtBlue;
                total_pixels++;
            }

            /* MIDDLE */
            // middle pixels
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                // add up rgb
                total_red += temp[i + 1][j + 1].rgbtRed;
                total_green += temp[i + 1][j + 1].rgbtGreen;
                total_blue += temp[i + 1][j + 1].rgbtBlue;
                total_pixels++;
            }

            // calculate avg - ROUND UP
            int boxBlurAvg_Red = round((float)total_red / total_pixels);
            int boxBlurAvg_Green = round((float)total_green / total_pixels);
            int boxBlurAvg_Blue = round((float)total_blue / total_pixels);

            image[i][j].rgbtRed = boxBlurAvg_Red;
            image[i][j].rgbtGreen = boxBlurAvg_Green;
            image[i][j].rgbtBlue = boxBlurAvg_Blue;

        }
    }

    return;
}