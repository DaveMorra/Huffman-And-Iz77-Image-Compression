#include "generate_pixel_frequency.h"

//generate pixel frequency go given gray intensity
long int *generate_pixel_frequency(struct PGM_Image *input_pgm_image, int *number_of_non_zero_values_in_the_frequency_array) {
    
    //inizalize freqency variables
    long int *valFreqArray;
    valFreqArray = (long int *)malloc((input_pgm_image->maxGrayValue + 1) * sizeof(long int));
    for(int n = 0; n < input_pgm_image->maxGrayValue+1; n++) {valFreqArray[n] = 0;}
    *number_of_non_zero_values_in_the_frequency_array = 0;

    //iterate each pixel and count intensity of each gray value
    for(int y = 0; y < input_pgm_image->height; y++) {
        for(int x = 0; x < input_pgm_image->width; x++) {
            valFreqArray[input_pgm_image->image[y][x]]++;
        }
    }

    //count number of non zero values
    for(int n = 0; n < input_pgm_image->maxGrayValue+1; n++) {
        if(valFreqArray[n] != 0) {(*number_of_non_zero_values_in_the_frequency_array)++;}
    }

    return valFreqArray;
}