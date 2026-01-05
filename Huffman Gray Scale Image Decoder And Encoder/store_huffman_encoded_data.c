#include "store_huffman_encoded_data.h"
#include "generate_huffman_nodes.h"
#include <stdio.h>
#include <stdlib.h>

//char *compressed_file_name_ptr, int image_width, int image_height, int max_gray_value, int number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, unsigned char *encoded_image
void store_huffman_encoded_data(char *compressed_file_name_ptr, int image_width, int image_height, int max_gray_value, int number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, unsigned char *encoded_image) {

    FILE *file = fopen(compressed_file_name_ptr, "wb");
    if(file == NULL) {printf("Error: could not open file");}

    fwrite(&image_width, sizeof(int), 1, file);                                             //write img width
    fwrite(&image_height, sizeof(int), 1, file);                                            //write img height
    fwrite(&max_gray_value, sizeof(int), 1, file);                                          //write img max gray value
    fwrite(&number_of_nodes, sizeof(int), 1, file);                                         //write num of nodes
    fwrite(huffman_node, sizeof(struct node), number_of_nodes, file);                       //write nodes
    fwrite(&length_of_encoded_image_array, sizeof(long int), 1, file);                      //write length of char array
    fwrite(encoded_image, sizeof(unsigned char), length_of_encoded_image_array, file);      //write char array (encoded img)
    fclose(file);

    return;
}