#include "huffman_decode_image.h"

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

//decode huffman code from given image
struct PGM_Image *huffman_decode_image(int image_width, int image_height, int max_gray_value, int number_of_nodes, struct node *huffman_node, long int length_of_encoded_image_array, unsigned char *encoded_image) {

    //create new image
    struct PGM_Image *img;
    create_PGM_Image(img, image_width, image_height, max_gray_value);

    //create huffmen codes given huffmen nodes (note: ignore all leading 1's, it is requierd for an int to have a leading one to maintain following zeros)
    int *huffman_codes;
    huffman_codes = malloc((max_gray_value + 1) * sizeof(int));
    int *copy_huffman_codes;
    copy_huffman_codes = malloc((max_gray_value + 1) * sizeof(int));

    //set all codes to zero (one in this case as leading bit is ignored)
    for (int i = 0; i < max_gray_value+1; i++) {huffman_codes[i] = 1;}

    //iterate each node
    for(int n = 0; n < number_of_nodes; n++) {
       if(huffman_codes[huffman_node[n].first_value] > huffman_codes[huffman_node[n].second_value]) {huffman_codes[huffman_node[n].second_value] = huffman_codes[huffman_node[n].first_value];}
        if(huffman_codes[huffman_node[n].second_value] > huffman_codes[huffman_node[n].first_value]) {huffman_codes[huffman_node[n].first_value] = huffman_codes[huffman_node[n].second_value];}
        huffman_codes[huffman_node[n].first_value] = (huffman_codes[huffman_node[n].first_value] << 1) + 1;
        huffman_codes[huffman_node[n].second_value] = huffman_codes[huffman_node[n].second_value] << 1;
    }

    int combinations_left;
    int char_index = 0;
    int huffmanValue;
    int imgCounter = 0;

    //create copy of huffman codes
    for(int i = 0; i < max_gray_value+1; i++) {copy_huffman_codes[i] = huffman_codes[i];}
    combinations_left = number_of_nodes + 1;

    //iterate entire encoded char until no values are left
    while(encoded_image[char_index] == '0' || encoded_image[char_index] == '1') {
    
        //if one or less combinations are found, store its value in new decoded char
        if(combinations_left <= 1) {

            while(copy_huffman_codes[huffmanValue] > 1) {
                copy_huffman_codes[huffmanValue] = reduce_leading_bit(copy_huffman_codes[huffmanValue]);
                char_index++;
            }

            img->image[imgCounter/image_width][imgCounter%image_width] = huffmanValue;
            imgCounter++;
            for(int i = 0; i < max_gray_value+1; i++) {copy_huffman_codes[i] = huffman_codes[i];}
            combinations_left = number_of_nodes + 1;
        }

        //iterate through each combination to determine if each code is a potential match
        for(int i = 0; i < max_gray_value+1; i++) {

            if(copy_huffman_codes[i] > 1) {

                //if its a match keep code, else remove code as potential match
                if( (( (leading_bit_is_one(copy_huffman_codes[i]) == 1) && encoded_image[char_index] == '1') || (leading_bit_is_one(copy_huffman_codes[i]) == 0 && encoded_image[char_index] == '0'))) {
                    copy_huffman_codes[i] = reduce_leading_bit(copy_huffman_codes[i]);
                    huffmanValue = i;
                }
                else {
                    copy_huffman_codes[i] = 1;
                    combinations_left--;
                }
            }
        }
        char_index++;
    }
    img->image[imgCounter/image_width][imgCounter%image_width] = huffmanValue;


    //free inizalized objects and return new created image
    free(huffman_codes);
    free(copy_huffman_codes);
    return img;
}