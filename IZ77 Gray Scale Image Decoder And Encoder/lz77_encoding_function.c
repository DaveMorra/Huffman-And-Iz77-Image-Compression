#include <stdio.h>
#include <string.h>
#include <math.h>
#include "libpnm.h"

//helper function that given a inital values from 0 to img l*w, return gray value at givne x and y value
int findPixel(struct PGM_Image img, int i) {
    int x = i%img.width;
    int y = i/img.width;
    if(y > img.height) {
        printf("ERROR, img out of bounds");
        return -1;
    }
    return img.image[y][x];
}

//encode using LZ77 encoding algorithem
void Encode_Using_LZ77(char *in_PGM_filename_Ptr, unsigned int searching_buffer_size, float *avg_offset_Ptr, float *std_offset_Ptr, float *avg_length_Ptr, float *std_length_Ptr) {

    //inizalized starting variables 
    struct PGM_Image img;
    load_PGM_Image(&img, in_PGM_filename_Ptr);
    int offsetArray[(img.height) * (img.width)];
    int lengthArray[(img.height) * (img.width)];
    int valArray[(img.height) * (img.width)];
    int currentMatchLen;
    int iMax = 0;
    
    //iterate each pixel
    for(int index = 0; index < img.height * img.width; index++) {
        
        //start counters a at zero
        lengthArray[iMax] = 0;
        offsetArray[iMax] = 0;

        //iterate each element inside the accepted buffer array
        for(int n = index - searching_buffer_size; n < index; n++) {
            
            //if value is our of range of buffer array, skip
            if(n < 0) {n = 0;}
            if(index == 0) {break;}
            currentMatchLen = 0;
            
            //iterate all following chars inside the buffer to find longest acceptable length
            for(int i = n; i < index; i++) {
                
                //add longest instance of a match to array
                if(index+(i-n) >= (img.height*img.width)) {break;}
                if(findPixel(img, i) != findPixel(img, index+(i-n))) {
                    if(lengthArray[iMax] > currentMatchLen) { break; }
                    lengthArray[iMax] = currentMatchLen;
                    if(currentMatchLen != 0) {offsetArray[iMax] = index - n;}
                    break;
                }

                //assign max length
                lengthArray[iMax] = currentMatchLen;
                if(currentMatchLen != 0) {offsetArray[iMax] = index - n;}
                currentMatchLen++;

            }
        }

        //add value after a given match
        index += lengthArray[iMax];
        if(index/img.width < img.height) { valArray[iMax] = findPixel(img, index); }
        else { valArray[iMax] = -1; }
        iMax++;

    }

    //modify current file name and open it, else throw error
    char str[40];
    sprintf(str, "%d", searching_buffer_size);
    strcat(in_PGM_filename_Ptr, ".");
    strcat(in_PGM_filename_Ptr, str);
    strcat(in_PGM_filename_Ptr, ".lz");
    FILE *file = fopen(in_PGM_filename_Ptr, "wb");
    if(file == NULL) {printf("Error: could not open file\n");}

    //print main info into file
    fprintf(file, "p2\n%d %d %d\n", img.width, img.height, img.maxGrayValue);
    for(int n = 0; n < iMax; n++) { fprintf(file, "\n%d %d %d", offsetArray[n], lengthArray[n], valArray[n]); }
    fclose(file);

    //make length and offset file
    char strLen[40];
    char strOff[40];
    strcpy(strLen, in_PGM_filename_Ptr);
    strcpy(strOff, in_PGM_filename_Ptr);
    strcat(strLen, ".lengths.csv");
    strcat(strOff, ".offset.csv");
    FILE *fileLen = fopen(strLen, "wb");
    if(fileLen == NULL) {printf("Error: could not open file\n");}
    FILE *fileOff = fopen(strOff, "wb");
    if(fileOff == NULL) {printf("Error: could not open file\n");}

    //write length frequency
    for(int n = 0; n < iMax; n++) {
        int counter = 0;
        for(int i = 0; i < iMax; i++) {
            if(lengthArray[i] == n) {counter++;}
        }
        if(counter != 0) {fprintf(fileLen, "%d, %d\n", n, counter);}
    }

    //write offset frequency
    for(int n = 0; n < iMax; n++) {
        int counter = 0;
        for(int i = 0; i < iMax; i++) {
            if(offsetArray[i] == n) {counter++;}
        }
        if(counter != 0) {fprintf(fileOff, "%d, %d\n", n, counter);}
    }

    fclose(fileLen);
    fclose(fileOff);

    //calculate average offset and length values
    float avg_offset = 0;
    float avg_length = 0;
    for(int n = 0; n < iMax; n++) { avg_offset += offsetArray[n]; }
    for(int n = 0; n < iMax; n++) { avg_length += lengthArray[n]; }
    *avg_offset_Ptr = avg_offset / iMax;
    *avg_length_Ptr = avg_length / iMax;

    //calculate SD offset and length values
    float std_offset = 0;
    float std_length = 0;
    for(int n = 0; n < iMax; n++) { std_offset += pow(offsetArray[n] - (*avg_offset_Ptr), 2); }
    for(int n = 0; n < iMax; n++) { std_length += pow(lengthArray[n] - (*std_length_Ptr), 2); }
    *std_offset_Ptr = sqrt(std_offset / iMax);
    *std_length_Ptr = sqrt(std_length / iMax);
}