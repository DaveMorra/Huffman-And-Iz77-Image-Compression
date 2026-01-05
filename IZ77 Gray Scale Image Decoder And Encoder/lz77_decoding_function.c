#include <stdio.h>
#include "libpnm.h"
#include <string.h>

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

//helper function that given a inital values from 0 to img l*w, return gray value at givne x and y value
void setPixel(struct PGM_Image img, int i, int val) {
    int x = i%img.width;
    int y = i/img.width;
    if(y > img.height) {
        printf("ERROR, img out of bounds");
        return;
    }
    img.image[y][x] = val;
}

void Decode_Using_LZ77(char *in_compressed_filename_Ptr) {

    //open and read file
    FILE *file;
    char fileLine[10];
    int width, height, maxGray;
    int offset, length, value;
    file = fopen(in_compressed_filename_Ptr, "r");
    if(file == NULL) { 
        printf("Error: Cant open file.");
        return;
    }

    //scan file header
    fscanf(file, "%s", fileLine);
    fscanf(file, "%d %d %d\n", &width, &height, &maxGray);

    //create image, else throw error
    struct PGM_Image img;
    strcat(in_compressed_filename_Ptr, ".pgm");
    if (create_PGM_Image(&img, width, height, maxGray) == -1) {
        printf("Error: Could not load image\n");
        return;
    }

    //write information
    int index = 0;
    while (fscanf(file, "%d %d %d", &offset, &length, &value) == 3) {

        for(int i = 0; i < length; i++) {
            setPixel(img, index, findPixel(img, index - offset));
            index++;
        }
        setPixel(img, index, value);
        index++;
        
    }

    //save file
    save_PGM_Image(&img, in_compressed_filename_Ptr, 0);
    free_PGM_Image(&img);
    fclose(file);
}