//created by David Morra
#include "lz77_decoding_function.h"


//main function that reads arg, and calls corresponding functions
int main(int argc, char *argv[]) {
    
    //start timer
    clock_t start, end;
    start = clock();

    //ensure proper input
    if(argc != 2) {
        printf("Error: program must accept one arguments\n");
        return 0;
    }

    //decode file
    Decode_Using_LZ77(argv[1]);

    //end timer
    end = clock();
    printf("\nDecoding time: %.6f sec", ((double)(end - start)) / CLOCKS_PER_SEC);

}