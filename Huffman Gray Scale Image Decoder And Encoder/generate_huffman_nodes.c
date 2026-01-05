#include "generate_huffman_nodes.h"

//generate nodes for huffman freqency array
struct node *generate_huffman_nodes(long int *pixel_frequency, int max_gray_value, int number_of_non_zero_values_in_the_frequency_array) {
    
    //inizalize node variables
    struct node *nodes;
    nodes = malloc((number_of_non_zero_values_in_the_frequency_array - 1) * sizeof(struct node));
    long int copy_pix_freq[max_gray_value+1];
    for(int n = 0; n < max_gray_value+1; n++) { copy_pix_freq[n] = pixel_frequency[n]; }

    //create smalles value ints
    int smallest_val_1;
    int smallest_val_2;
    int smallest_address_1;
    int smallest_address_2;

    //iterate throught frequency array and merge smallest values in each round
    for(int i = number_of_non_zero_values_in_the_frequency_array - 2; i >= 0; i--) {

        //find smallest values within the pixel frequency array
        smallest_val_1 = 2147483647;
        smallest_val_2 = 2147483647;

        //find two smallest values
        for(int n = 0; n < max_gray_value; n++) {
            if(copy_pix_freq[n] != 0 && copy_pix_freq[n] < smallest_val_1) {
                smallest_val_2 = smallest_val_1;
                smallest_val_1 = copy_pix_freq[n];
                smallest_address_2 = smallest_address_1;
                smallest_address_1 = n;
            }
            else if(copy_pix_freq[n] != 0 && copy_pix_freq[n] < smallest_val_2) {
                smallest_val_2 = copy_pix_freq[n];
                smallest_address_2 = n;
            }
        }

        //merge values
        nodes[i].first_value = smallest_address_1;
        nodes[i].second_value = smallest_address_2;

        copy_pix_freq[smallest_address_1] += copy_pix_freq[smallest_address_2];
        copy_pix_freq[smallest_address_2] = 0;

    }

    return nodes;
}