#include "mean_absolute_error.h"

//calculate abs diffrence between two ints
float abs_dif(int n1, int n2) {
    float n = (float)n1 - (float)n2;
    if (n >= 0) return n;
    return n * -1;
}


//calculate mean absolute error in two images
float mean_absolute_error(char *file_name_1_ptr, char *file_name_2_ptr) {

    //load both images
    struct PGM_Image img1;
    struct PGM_Image img2;
    load_PGM_Image(&img1, file_name_1_ptr);
    load_PGM_Image(&img2, file_name_2_ptr);

    //if img have diffrent width or height, return -1
    if(img1.height != img2.height || img1.width != img2.width) {return -1;}

    //scale image according to diffrent max grey scale values
    if(img1.maxGrayValue > img2.maxGrayValue) {
        float diff = (float)img2.maxGrayValue / (float)img1.maxGrayValue;
        for(int y = 0; y < img1.height; y++) {
            for(int x = 0; x < img1.width; x++) {
                img2.image[y][x] = (int)((float)img2.image[y][x] * (float)diff);
            }
        }
    } else if (img1.maxGrayValue < img2.maxGrayValue) {
        float diff = (float)img1.maxGrayValue / (float)img2.maxGrayValue;
        for(int y = 0; y < img1.height; y++) {
            for(int x = 0; x < img1.width; x++) {
                img1.image[y][x] = (int)((float)img1.image[y][x] * (float)diff);
            }
        }
    }

    //calculate mean abs diffrence
    float sum = 0;
    for(int y = 0; y < img1.height; y++) {
        for(int x = 0; x < img1.width; x++) {
            sum += abs_dif(img1.image[y][x], img2.image[y][x]);
        }
    }
    
    //free images and return mean error
    free_PGM_Image(&img1);
    free_PGM_Image(&img2);
    return (sum / (float)(img1.height*img1.width));
}