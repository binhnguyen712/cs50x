#include "helpers.h"
#include <math.h>
// Convert image to grayscale
int calculateSepia(int originalRed, float factor1, int originalGreen, float factor2, int originalBlue, float factor3);
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / (float)3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int sepiaRed = calculateSepia(image[i][j].rgbtRed, .393, image[i][j].rgbtGreen, .769, image[i][j].rgbtBlue, .189);
            int sepiaGreen = calculateSepia(image[i][j].rgbtRed, .349, image[i][j].rgbtGreen, .686, image[i][j].rgbtBlue, .168);
            int sepiaBlue = calculateSepia(image[i][j].rgbtRed, .272, image[i][j].rgbtGreen, .534, image[i][j].rgbtBlue, .131);

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++){
        for(int j = 0; j < width / 2; j++){
            RGBTRIPLE temp;
            temp = image[i][j] ;
            image[i][j] = image[i][width - j - 1];
            image[i][width-j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            copy[i][j] = image[i][j];
        }
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int count = 0;
            int redsum = 0;
            int greensum = 0;
            int bluesum = 0;
            for(int x = -1; x <= 1; x++){
                if(i + x < 0 || i +x > height - 1){
                    continue;
                }
                for(int y = -1; y <= 1; y++){
                    if(j + y < 0 || j + y > width - 1){
                        continue;
                    }
                    count++;
                    redsum += copy[i+x][j+y].rgbtRed;
                    greensum += copy[i+x][j+y].rgbtGreen;
                    bluesum += copy[i+x][j+y].rgbtBlue;
                }
            }
            image[i][j].rgbtRed = round(redsum / (float)(count));
            image[i][j].rgbtGreen = round(greensum / (float)(count));
            image[i][j].rgbtBlue = round(bluesum / (float)(count));
        }
    }
    return;
}

int calculateSepia(int originalRed, float factor1, int originalGreen, float factor2, int originalBlue, float factor3){
    int sepiaColor = round(originalRed*factor1 + originalGreen*factor2 + originalBlue*factor3);
    if (sepiaColor > 255){
        sepiaColor = 255;
    }
    return sepiaColor;
}
