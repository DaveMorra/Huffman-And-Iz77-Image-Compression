#include "pgm_huffman_decode.h"

int main(int argc, char *argv[]) {

    //make sure the program takes in two additional inputs
    if(argc != 3) {
            printf("Error: program must accept two arguments\n");
            return 0;
    }


    //initialize variables used in each function
    int image_width;
    int image_height;
    int max_gray_value;
    int number_of_nodes;
    struct node *huffman_node;
    long int length_of_encoded_image_array;
    unsigned char *huffman_code;
    struct PGM_Image *img;

    //read the file and extract all data
    huffman_code = read_huffman_encoded_data(argv[1], &image_width, &image_height, &max_gray_value, &number_of_nodes, &huffman_node, &length_of_encoded_image_array);

    //create an image with given huffman data
    img = huffman_decode_image(image_width, image_height, max_gray_value, number_of_nodes, huffman_node, length_of_encoded_image_array, huffman_code);

    //save then free all data
    save_PGM_Image(img, argv[2], 0);
    free(huffman_code);
    free_PGM_Image(img);
}