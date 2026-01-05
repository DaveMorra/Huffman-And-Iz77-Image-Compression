#include "read_huffman_encoded_data.h"

//read encoded data from file
unsigned char *read_huffman_encoded_data(char *compressed_file_name_ptr, int *image_width, int *image_height, int *max_gray_value, int *number_of_nodes, struct node **huffman_node, long int *length_of_encoded_image_array) {
    
    //open file, else throw error
    FILE *file = fopen(compressed_file_name_ptr, "rb");
    if (file == NULL) {
        perror("Error opening compressed file for reading");
        return 0;
    }

    //read properties from file
    fread(image_width, sizeof(int), 1, file);
    fread(image_height, sizeof(int), 1, file);
    fread(max_gray_value, sizeof(int), 1, file);
    fread(number_of_nodes, sizeof(int), 1, file);
    *huffman_node = (struct node *)malloc(((int) *number_of_nodes) * sizeof(struct node));
    fread(*huffman_node, sizeof(struct node), *number_of_nodes, file);
    fread(length_of_encoded_image_array, sizeof(long int), 1, file);
    unsigned char *huffman_code;
    huffman_code = malloc(((int) *image_width) * ((int) *image_height) * 24 * sizeof(unsigned char));
    fread(huffman_code, sizeof(unsigned char), ((int) *image_width) * ((int) *image_height) * 24, file);

    //return extracted huffman code
    return huffman_code;
}