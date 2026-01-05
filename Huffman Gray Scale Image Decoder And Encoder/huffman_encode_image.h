#ifndef HUFFMAN_ENCODE_IMAGE_H
#define HUFFMAN_ENCODE_IMAGE_H

#include "generate_huffman_nodes.h"
#include "libpnm.h"
#include <stdio.h>
#include <string.h>

unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, int number_of_nodes, long int *length_of_encoded_image_array);

#endif