//created by David Morra
#include "lz77_encoding_function.h"

//main function that reads arg, and calls corresponding functions
int main(int argc, char *argv[]) {

    //inizalize pointers and starting variables
    float avg_offset_Ptr;
    float std_offset_Ptr;
    float avg_length_Ptr;
    float std_length_Ptr;

    //program must take in three arguments
    if(argc != 3) {
        printf("Error: program must accept two arguments\n");
        return 0;
    }

    //start timer
    clock_t start, end;
    start = clock();

    //encode using LZ77 algorithem
    Encode_Using_LZ77(argv[1], (unsigned int)strtoul(argv[2], NULL, 10), &avg_offset_Ptr, &std_offset_Ptr, &avg_length_Ptr, &std_length_Ptr);

    //end timer
    end = clock();
    printf("\nEncoding time: %.6f sec", ((double)(end - start)) / CLOCKS_PER_SEC);

    //print additional info
    printf("\nOffset Average: %f", avg_offset_Ptr);
    printf("\nOffset Standard Deviation: %f", std_offset_Ptr);
    printf("\nMatch Length Average: %f", avg_length_Ptr);
    printf("\nMatch Length Standard Deviation: %f\n\n", std_length_Ptr);

}