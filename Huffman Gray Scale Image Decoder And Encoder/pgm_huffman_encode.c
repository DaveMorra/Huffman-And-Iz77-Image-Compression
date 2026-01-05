#include "pgm_huffman_encode.h"

int main(int argc, char *argv[]) { 

    //program must take in five arguments
    if(argc != 3) {
            printf("Error: program must accept two arguments\n");
            return 0;
    }

    //load image, else throw error
    struct PGM_Image img;
    if (load_PGM_Image(&img, argv[1]) == -1) {
        printf("Error: Could not load image\n");
        return 0;
    }

    //initialize encoding variables
    int nonZeroFreq;
    long int lenghtOfEncodedImageArrayBytes;
    long int *valFreqArray;
    struct node *nodes;
    unsigned char *huffman_code;

    //encode given image
    valFreqArray = generate_pixel_frequency(&img, &nonZeroFreq);
    nodes = generate_huffman_nodes(valFreqArray, img.maxGrayValue + 1, nonZeroFreq);
    huffman_code = huffman_encode_image(&img, nodes, nonZeroFreq - 1, &lenghtOfEncodedImageArrayBytes);
    store_huffman_encoded_data(argv[2], img.width, img.height, img.maxGrayValue, nonZeroFreq - 1, nodes, lenghtOfEncodedImageArrayBytes, huffman_code);

    //free all objects
    free(nodes);
    free(valFreqArray);
    free(huffman_code);
    return 0;
}