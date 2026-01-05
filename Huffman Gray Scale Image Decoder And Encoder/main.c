//created by David Morra
#include "libpnm.h"

//round float into nearest int while rounding appropriately
int roundF(float n) {
        if(n >= (int)n + .5) {return (int) n+1;}
        return (int)n;
}

//return max of two ints
int max(int n1, int n2) {
        if(n1 > n2) {return n1;}
        return n2;
}

//return min of two ints
int min(int n1, int n2) {
        if(n1 < n2) {return n1;}
        return n2;
}

//print corresponding PBM image
void printImagePBM(int width, int height, char* fileName, int isRaw) {
        
        //create picture
        struct PBM_Image img;
        create_PBM_Image(&img, width, height);

        //iterate each pixel
        for(int y = 0; y < height; y++) {
           for(int x = 0; x < width; x++) {

                float fy = y;
                float fx = x;
                float fyScaled = y * width/height;
                float fxScaled = x * height/width;

                //create black boarder
                if(y < height/4 || y+1 > (height/4)*3 || x < width/4 || x+1 > (width/4)*3) {img.image[y][x] = 1;}
                
                //make center diaginal black
                else if(width >= height && ((roundF(fy) == roundF(fxScaled)) || ((height - 1 - roundF(fy) == roundF(fxScaled))))) {img.image[y][x] = 1;}
                else if(width < height && ((roundF(fyScaled) == roundF(fx)) || (roundF(fyScaled) == width - 1 - roundF(fx)))) {img.image[y][x] = 1;}

                //make white otherwise
                else {img.image[y][x] = 0;}
        }}

        //save image and free memory
        save_PBM_Image(&img, fileName, isRaw);
        free_PBM_Image(&img);
}

//print corresponding PGM image
void printImagePGM(int width, int height, char* fileName, int isRaw) {

        //create picture
        struct PGM_Image img;
        create_PGM_Image(&img, width, height, 255);

        //color side triangles by making entire image a gradent accross the width
        for(int x = 0; x < width/4; x++) {
                float greyColor = (((float)x/((float)(width/4)-1)) * 255);
                for(int y = 0; y < height; y++) {
                        img.image[y][x+(int)(width/2)] = roundF(greyColor);
                        img.image[y][x+(int)(width/4)] = 255 - roundF(greyColor);
                }
        }

        //iterate each pixel
        for(int y = 0; y < height; y++) {

                //calculate gradient according to height
                float greyColor = (((float)(y%(height/4))/((float)(height/4)-1)) * 255);
                if(y < (height)/2) {greyColor = 255 - greyColor;}
                int minX = width-1;
                int maxX = 0;

                //fill in the 
                for(int x = 0; x < width; x++) {

                        float fy = y;
                        float fx = x;
                        float fyScaled = y * width/height;
                        float fxScaled = x * height/width;

                        //create black boarder
                        if(y < height/4 || y+1 > (height/4)*3 || x < width/4 || x+1 > (width/4)*3) {img.image[y][x] = 0;}
                        
                        //find left point of triangle (across the width)
                        else if(width >= height && (((int)fy == (int)fxScaled) || ((height - 1 - (int)fy == (int)fxScaled)))) {
                                minX = min(minX, x);
                                maxX = max(maxX, x);
                        }

                        //find right point of triangle (across the width)
                        else if(width < height && (((int)fyScaled == (int)fx) || ((int)fyScaled == width - 1 - (int)fx))) {
                                minX = min(minX, x);
                                maxX = max(maxX, x);
                        }

                }

                //given edge of the triangle (across the width), fill it in
                for(int x = minX; x <= maxX; x++) {
                        if(x == minX || x == maxX) {img.image[y][x] = min(greyColor, (((float)x/((float)(width/4)-1)) * 255));}
                        img.image[y][x] = greyColor;
                }
        }

        //save image and free memory
        save_PGM_Image(&img, fileName, isRaw);
        free_PGM_Image(&img);
}

//print corresponding PPM image
void printImagePPM(int width, int height, char* fileName, int isRaw) {
        
        //create picture
        struct PPM_Image img;
        create_PPM_Image(&img, width, height, 255);

        //iterate top half of image
        for(int y = 0; y < height/2; y++) {

                //calculate gradient according to height
                float color = (((float)y/((float)(height/2)-1)) * 255);

                //iterate width and assign according gradient color
                for(int x = 0; x < width; x++) {

                        //assign all colors to have a gradient
                        img.image[y][x][0] = roundF(color);
                        img.image[y][x][1] = roundF(color);
                        img.image[y][x][2] = roundF(color);

                        //remove gradient to according colors
                        if(x < width/3) {img.image[y][x][0] = 255;}
                        else if(x < (width/3)*2) {img.image[y][x][1] = 255;
                                img.image[y][x][0] = 255 - roundF(color);
                                img.image[y][x][2] = 255 - roundF(color);
                        }
                        else {img.image[y][x][2] = 255;}

                }
        }

        //iterate bottom half of image
        for(int y = (height/2); y < height; y++) {

                //calculate gradient according to height
                float color = (((float)(y-(height/2))/((float)(height/2)-1)) * 255);

                //iterate width and assign according gradient color
                for(int x = 0; x < width; x++) {

                        //all colors have a vertical gradient
                        if(x < width/2) {
                                img.image[y][x][0] = roundF(color);
                                img.image[y][x][1] = roundF(color);
                                img.image[y][x][2] = roundF(color);
                        }

                        //all colors have a vertical gradient (opposite from above)
                        else {
                                img.image[y][x][0] = 255 - roundF(color);
                                img.image[y][x][1] = 255 - roundF(color);
                                img.image[y][x][2] = 255 - roundF(color);
                        }

                }
        }

        //create and convert new image
        char fileR[20];
        char fileG[20];
        char fileB[20];
        sprintf(fileR, "red_%d_%d.pgm", width, height);
        sprintf(fileG, "green_%d_%d.pgm", width, height);
        sprintf(fileB, "blue_%d_%d.pgm", width, height);
        struct PGM_Image imgR;
        struct PGM_Image imgG;
        struct PGM_Image imgB;
        copy_PPM_to_PGM(&img, &imgR, 0);
        copy_PPM_to_PGM(&img, &imgG, 1);
        copy_PPM_to_PGM(&img, &imgB, 2);
        save_PGM_Image(&imgR, fileR, isRaw);
        save_PGM_Image(&imgG, fileG, isRaw);
        save_PGM_Image(&imgB, fileB, isRaw);
        free_PGM_Image(&imgR);
        free_PGM_Image(&imgG);
        free_PGM_Image(&imgB);

        //save image and free memory
        save_PPM_Image(&img, fileName, isRaw);
        free_PPM_Image(&img);
}

//main function that reads arg, and calls corresponding functions
int main(int argc, char *argv[]) { 
        
        //program must take in five arguments
        if(argc != 6) {
                printf("Error: program must accept five arguments\n");
                return 0;
        }

        //program image format code must be (e.g., 0 for ASCII or 1 for raw)
        if(atoi(argv[5]) != 0 && atoi(argv[5]) != 1) {
                printf("Error: program must have image format code (e.g., 0 for ASCII or 1 for raw)\n");
                return 0;
        }

        //program first argument must include image type code (e.g.,1 for pbm, 2 for pgm, or 3 for ppm)
        if(atoi(argv[1]) == 1) {
                
                //image height and width specifications for given format
                if(!(atoi(argv[2]) % 4 == 0 && atoi(argv[2]) >= 4 && atoi(argv[3]) % 4 == 0 && atoi(argv[3]) >= 4)) {
                        printf("Error: program input has not meet height and width specifications for given format\n");
                        return 0;
                }

                //print image according to Program-1
                printImagePBM(atoi(argv[2]), atoi(argv[3]), argv[4], atoi(argv[5]));

        }
        else if(atoi(argv[1]) == 2) {

                //image height and width specifications for given format
                if(!(atoi(argv[2]) % 4 == 0 && atoi(argv[2]) >= 4 && atoi(argv[3]) % 4 == 0 && atoi(argv[3]) >= 4)) {
                        printf("Error: program input has not meet height and width specifications for given format\n");
                        return 0;
                }
                printImagePGM(atoi(argv[2]), atoi(argv[3]), argv[4], atoi(argv[5]));

        }
        else if(atoi(argv[1]) == 3) {

                //image height and width specifications for given format
                if(!(atoi(argv[2]) % 6 == 0 && atoi(argv[2]) >= 6 && atoi(argv[3]) % 4 == 0 && atoi(argv[3]) >= 4)) {
                        printf("Error: program input has not meet height and width specifications for given format\n");
                        return 0;
                }

                //ensure correct program name TODO: ADD LATER
                printImagePPM(atoi(argv[2]), atoi(argv[3]), argv[4], atoi(argv[5]));
        }
        else {
                printf("Error: program must include image type code (e.g.,1 for pbm, 2 for pgm, or 3 for ppm)\n");
                return 0;    
        }
      
        return 0;
}
