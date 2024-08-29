#include "helpers.h"
#include <math.h>
int calculate_final(int gx, int gy);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / (float)3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue= avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width / 2; j++){
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
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
            int counter = 0;
            int redsum =0;
            int greensum = 0;
            int bluesum = 0;
            for(int x = -1; x <= 1; x++){
                if(i+x < 0 || i+x > height - 1){
                    continue;
                }
                for(int y = -1; y <= 1; y++){
                    if(j+y < 0 || j+ y > width - 1){
                        continue;
                    }
                    counter++;
                    redsum += copy[i+x][j+y].rgbtRed;
                    greensum += copy[i+x][j+y].rgbtGreen;
                    bluesum += copy[i+x][j+y].rgbtBlue;
                }
            }
            image[i][j].rgbtRed = round(redsum / (float)counter);
            image[i][j].rgbtGreen = round(greensum / (float)counter);
            image[i][j].rgbtBlue = round(bluesum / (float)counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            copy[i][j] = image[i][j];
        }
    }
    int gx[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
    int gy[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int redgx = 0;
            int greengx =0;
            int bluegx =0;
            int redgy =0;
            int greengy=0;
            int bluegy =0;
            for(int x = -1; x<=1; x++){
                for(int y = -1; y <= 1; y++){
                    if(i + x < 0 || i + x > height -1){
                        continue;
                    }
                    if (j + y < 0 || j + y > width -1){
                        continue;
                    }
                    redgx += copy[i+x][j+y].rgbtRed * gx[x+1][y+1];
                    greengx += copy[i+x][j+y].rgbtGreen * gx[x+1][y+1];
                    bluegx += copy[i+x][j+y].rgbtBlue * gx[x+1][y+1];

                    redgy += copy[i+x][j+y].rgbtRed * gy[x+1][y+1];
                    greengy += copy[i+x][j+y].rgbtGreen * gy[x+1][y+1];
                    bluegy += copy[i+x][j+y].rgbtBlue * gy[x+1][y+1];
                }
            }
            int finalred = calculate_final(redgx, redgy);
            int finalgreen = calculate_final(greengx, greengy);
            int finalblue = calculate_final(bluegx, bluegy);

            image[i][j].rgbtRed = finalred;
            image[i][j].rgbtGreen = finalgreen;
            image[i][j].rgbtBlue = finalblue;
        }
    }
    return;
}
 int calculate_final(int gx, int gy){
    int final = round(sqrt(pow(gx, 2) + pow(gy, 2)));
    if (final > 255){
        final = 255;
    }
    return final;
 }
