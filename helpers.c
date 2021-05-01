#include "helpers.h"
#include<stdio.h>
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            float average = (float)(r+g+b)/3;
            int avg = round(average);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i =0;i<height;i++)
    {
        for(int j=0;j<width/2;j++)
        {
            RGBTRIPLE ir = image[i][j];
            image[i][j] = image[i][width-(j+1)];
            image[i][width-(j+1)] = ir;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0;i<height;i++)
    {
        for (int j = 0;j<width;j++)
        {
          copy[i][j] = image[i][j];
        }
    }
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            //top left
            if(i==0&&j==0)
            {
                float avgr = round((float)(copy[1][1].rgbtRed + copy[0][1].rgbtRed + copy[1][0].rgbtRed + copy[0][0].rgbtRed)/4);
                float avgg = round((float)(copy[1][1].rgbtGreen + copy[0][1].rgbtGreen + copy[1][0].rgbtGreen + copy[0][0].rgbtGreen)/4);
                float avgb = round((float)(copy[1][1].rgbtBlue + copy[0][1].rgbtBlue + copy[1][0].rgbtBlue + copy[0][0].rgbtBlue)/4);

                image[0][0].rgbtRed = avgr;
                image[0][0].rgbtGreen = avgg;
                image[0][0].rgbtBlue = avgb;
            }
            //top right
            else if(i==0&&j==width-1)
            {
                float avgr = round((float)(copy[0][width-2].rgbtRed + copy[1][width-2].rgbtRed + copy[1][width-1].rgbtRed + copy[0][width-1].rgbtRed)/4) ;
                float avgg = round((float)(copy[0][width-2].rgbtGreen + copy[1][width-2].rgbtGreen + copy[1][width-1].rgbtGreen + copy[0][width-1].rgbtGreen)/4) ;
                float avgb = round((float)(copy[0][width-2].rgbtBlue + copy[1][width-2].rgbtBlue + copy[1][width-1].rgbtBlue + copy[0][width-1].rgbtBlue)/4) ;

                image[0][width-1].rgbtRed = avgr;
                image[0][width-1].rgbtGreen = avgg;
                image[0][width-1].rgbtBlue = avgb;
            }
            //bottom left
            else if (i==height-1&&j==0)
            {
                float avgr = round((float)(copy[height-2][0].rgbtRed + copy[height-1][0].rgbtRed + copy[height-2][1].rgbtRed + copy[height-1][1].rgbtRed)/4);
                float avgg = round((float)(copy[height-2][0].rgbtGreen + copy[height-1][0].rgbtGreen + copy[height-2][1] .rgbtGreen + copy[height-1][1].rgbtGreen)/4);
                float avgb = round((float)(copy[height-2][0].rgbtBlue + copy[height-1][0].rgbtBlue + copy[height-2][1].rgbtBlue + copy[height-1][1].rgbtBlue)/4);

                image[height-1][0].rgbtRed = avgr;
                image[height-1][0].rgbtGreen = avgg;
                image[height-1][0].rgbtBlue = avgb;
            }
            //bottom right
            else if (i==height-1&&j==width-1)
            {
                float avgr = round((float)(copy[height-1][width-1].rgbtRed + copy[height-2][width-1].rgbtRed + copy[height-2][width-2].rgbtRed + copy[height-1][width-2].rgbtRed)/4);
                float avgg = round((float)(copy[height-1][width-1].rgbtGreen + copy[height-2][width-1].rgbtGreen + copy[height-2][width-2].rgbtGreen + copy[height-1][width-2].rgbtGreen)/4);
                float avgb = round((float)(copy[height-1][width-1].rgbtBlue + copy[height-2][width-1].rgbtBlue + copy[height-2][width-2].rgbtBlue + copy[height-1][width-2].rgbtBlue)/4);

                image[height-1][width-1].rgbtRed = avgr;
                image[height-1][width-1].rgbtGreen = avgg;
                image[height-1][width-1].rgbtBlue = avgb;
            }
            //top edge
            else if (i==0&&j!=0&&j!=width-1)
            {
                float avgr = round((float)(copy[i+1][j-1].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i][j].rgbtRed)/6);
                float avgb = round((float)(copy[i+1][j-1].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i][j].rgbtBlue)/6);
                float avgg = round((float)(copy[i+1][j-1].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i][j].rgbtGreen)/6);

                image[i][j].rgbtRed = avgr;
                image[i][j].rgbtGreen = avgg;
                image[i][j].rgbtBlue = avgb;
            }
            //left edge
            else if (i!=0&&i!=height-1&&j==0)
            {
                float avgr = round((float)(copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j+1].rgbtRed +copy[i+1][j].rgbtRed + copy[i][j].rgbtRed)/6);
                float avgg = round((float)(copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j+1].rgbtGreen +copy[i+1][j].rgbtGreen + copy[i][j].rgbtGreen)/6);
                float avgb = round((float)(copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j+1].rgbtBlue +copy[i+1][j].rgbtBlue + copy[i][j].rgbtBlue)/6);

                image[i][j].rgbtRed = avgr;
                image[i][j].rgbtGreen = avgg;
                image[i][j].rgbtBlue = avgb;
            }
            //right edge
            else if (i!=height-1&&i!=0&&j==width-1)
            {
                float avgr = round((float)(copy[i-1][j].rgbtRed + copy[i-1][j-1].rgbtRed + copy[i][j-1].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i][j].rgbtRed)/6);
                float avgg = round((float)(copy[i-1][j].rgbtGreen + copy[i-1][j-1].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i][j].rgbtGreen)/6);
                float avgb = round((float)(copy[i-1][j].rgbtBlue + copy[i-1][j-1].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i][j].rgbtBlue)/6);

                image[i][j].rgbtRed = avgr;
                image[i][j].rgbtGreen = avgg;
                image[i][j].rgbtBlue = avgb;
            }
            //bottom edge
            else if (i==height-1&&j!=0&&j!=width-1)
            {
                float avgr = round((float)(copy[i][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j].rgbtRed)/6);
                float avgg = round((float)(copy[i][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j].rgbtGreen)/6);
                float avgb = round((float)(copy[i][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j].rgbtBlue)/6);

                image[i][j].rgbtRed = avgr;
                image[i][j].rgbtGreen = avgg;
                image[i][j].rgbtBlue = avgb;
            }
            //everything else
            else
            {
                float avgr = round((float)(copy[i][j].rgbtRed + copy[i-1][j].rgbtRed + copy[i+1][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j+1].rgbtRed + copy[i-1][j-1].rgbtRed + copy[i-1][j+1].rgbtRed
                            + copy[i+1][j-1].rgbtRed + copy[i+1][j+1].rgbtRed)/9);
                float avgg = round((float)(copy[i][j].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i-1][j-1].rgbtGreen
                            + copy[i-1][j+1].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j+1].rgbtGreen)/9);
                float avgb = round((float)(copy[i][j].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i-1][j-1].rgbtBlue
                            + copy[i-1][j+1].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j+1].rgbtBlue)/9);

                image[i][j].rgbtRed = avgr;
                image[i][j].rgbtGreen = avgg;
                image[i][j].rgbtBlue = avgb;
            }
        }
    } 
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            float GredX=0, GgreenX=0, GblueX=0;
            float GredY=0, GgreenY=0, GblueY=0;
            
            if(i>0)
            {
                GredY+= -2 * copy[i-1][j].rgbtRed;
                GgreenY += -2 * copy[i-1][j].rgbtGreen;
                GblueY += -2 * copy[i-1][j].rgbtBlue;
            }
            if(i<height-1)
            {
                GredY += 2 * copy[i+1][j].rgbtRed;
                GgreenY += 2 * copy[i+1][j].rgbtGreen;
                GblueY += 2 * copy[i+1][j].rgbtBlue;
            }
            if(j>0)
            {
                GredX += -2 * copy[i][j-1].rgbtRed;
                GgreenX += -2 * copy[i][j-1].rgbtGreen;
                GblueX += -2 * copy[i][j-1].rgbtBlue;
            }
            if(j<width-1)
            {
               GredX += 2 * copy[i][j+1].rgbtRed;
               GgreenX += 2 * copy[i][j+1].rgbtGreen;
               GblueX += 2 * copy[i][j+1].rgbtBlue; 
            }
            if(i>0&&j>0)
            {
                GredX += -1 * copy[i-1][j-1].rgbtRed;
                GgreenX += -1 * copy[i-1][j-1].rgbtGreen;
                GblueX += -1 * copy[i-1][j-1].rgbtBlue;
                GredY += -1 * copy[i-1][j-1].rgbtRed;
                GgreenY += -1 * copy[i-1][j-1].rgbtGreen;
                GblueY += -1 * copy[i-1][j-1].rgbtBlue;
            }
            if(i>0&&j!=0&&j<width-1)
            {
                GredX += 1 * copy[i-1][j+1].rgbtRed;
                GgreenX += 1 * copy[i-1][j+1].rgbtGreen;
                GblueX += 1 * copy[i-1][j+1].rgbtBlue;
                GredY += -1 * copy[i-1][j+1].rgbtRed;
                GgreenY += -1 * copy[i-1][j+1].rgbtGreen;
                GblueY += -1 * copy[i-1][j+1].rgbtBlue;
            }
            if(i<height-1&&j>0)
            {
                GredX += -1 * copy[i+1][j-1].rgbtRed;
                GgreenX += -1 * copy[i+1][j-1].rgbtGreen;
                GblueX += -1 * copy[i+1][j-1].rgbtBlue;
                GredY += 1 * copy[i+1][j-1].rgbtRed;
                GgreenY += 1 * copy[i+1][j-1].rgbtGreen;
                GblueY += 1 * copy[i+1][j-1].rgbtBlue;
            }
            if(i<height-1&&j<width-1)
            {
                GredX += 1 * copy[i+1][j+1].rgbtRed;
                GgreenX += 1 * copy[i+1][j+1].rgbtGreen;
                GblueX += 1 * copy[i+1][j+1].rgbtBlue;
                GredY += 1 * copy[i+1][j+1].rgbtRed;
                GgreenX += 1 * copy[i+1][j+1].rgbtGreen;
                GblueX += 1 * copy[i+1][j+1].rgbtBlue;
            }
            float r,g,b;
            r = sqrt((float)(GredX*GredX)+(GredY*GredY));
            int Ar = round(r);
            if(Ar>255)
            Ar=255;
            g = sqrt((float)(GgreenX*GgreenX)+(GgreenY*GgreenY));
            int Ag = round(g);
            if(Ag>255)
            Ag=255;
            b = sqrt((float)(GblueX*GblueX)+(GblueY*GblueY));
            int Ab = round(b);
            if(Ab>255)
            Ab=255;
            image[i][j].rgbtRed = Ar;
            image[i][j].rgbtGreen = Ag;
            image[i][j].rgbtBlue = Ab;
        }
    }
}
