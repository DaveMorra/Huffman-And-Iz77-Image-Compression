#include "huffman_encode_image.h"

//return the leading bit of a binery number stored as a int
int leading_bit_is_one(int n) {
    while(true) {
        if(n <= 3) {return n & 1;}
        n >>= 1;
    }
    return -1;
}

//reduce leading bit for binary number stored as a int
int reduce_leading_bit(int n) {
    int t1 = n;
    int t2 = 1;

    while(t1 > 3) {
        if(t1 & 1) {t2 = (t2 << 1) + 1;}
        else {t2 = (t2 << 1);}
        t1 >>= 1;
    }

    t1 = 1;
    while(t2 > 1) {
        if(t2 & 1) {t1 = (t1 << 1) + 1;}
        else {t1 = (t1 << 1);}
        t2 >>= 1;
    }

    return t1;
}

//create and encode image given huffman nodes
unsigned char *huffman_encode_image(struct PGM_Image *input_pgm_image, struct node *huffman_node, int number_of_nodes, long int *length_of_encoded_image_array) {

    //create huffmen codes given huffmen nodes (note: ignore all leading 1's, it is requierd for an int to have a leading one to maintain following zeros)
    *length_of_encoded_image_array = 0;
    int int_huffman_codes[input_pgm_image->maxGrayValue+1];
    for (int i = 0; i < input_pgm_image->maxGrayValue+1; i++) {int_huffman_codes[i] = 1;}

    //iterate each node
    for(int n = 0; n < number_of_nodes; n++) {
        if(int_huffman_codes[huffman_node[n].first_value] > int_huffman_codes[huffman_node[n].second_value]) {int_huffman_codes[huffman_node[n].second_value] = int_huffman_codes[huffman_node[n].first_value];}
        if(int_huffman_codes[huffman_node[n].second_value] > int_huffman_codes[huffman_node[n].first_value]) {int_huffman_codes[huffman_node[n].first_value] = int_huffman_codes[huffman_node[n].second_value];}
        int_huffman_codes[huffman_node[n].first_value] = (int_huffman_codes[huffman_node[n].first_value] << 1) + 1;
        int_huffman_codes[huffman_node[n].second_value] = int_huffman_codes[huffman_node[n].second_value] << 1;
    }

    //create new huffman codes
    unsigned char *char_huffman_codes;
    char_huffman_codes = malloc(input_pgm_image->width * input_pgm_image->height * 24 * sizeof(unsigned char));
    if(char_huffman_codes == NULL) {printf("Error: could not generate huffman code");}
    int image_length = 0;

    //iterate image and assign each values with a code and append it to encoded char
    for(int y = 0; y < input_pgm_image->height; y++) {
        for(int x = 0; x < input_pgm_image->width; x++) {

            int temp = int_huffman_codes[input_pgm_image->image[y][x]];

            while(temp > 1) {
                if(leading_bit_is_one(temp)) {char_huffman_codes[image_length++] = '1';}
                else {char_huffman_codes[image_length++] = '0';}
                temp = reduce_leading_bit(temp);
            }
        }
    }

    *length_of_encoded_image_array = (long int)image_length;
    return char_huffman_codes;
}