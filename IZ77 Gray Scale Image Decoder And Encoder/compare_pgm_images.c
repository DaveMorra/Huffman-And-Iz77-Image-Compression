#include <stdio.h>
#include "mean_absolute_error.h"

//calcuate mean absolute error of two images
int main(int argc, char *argv[]) { 
    
    //program must take in five arguments
    if(argc != 3) {
            printf("\nError: program must accept two arguments\n");
            return 0;
    }

    //print mean error value
    float mean_error;
    mean_error = mean_absolute_error(argv[1], argv[2]);
    if(mean_error == -1) {printf("\nError: cant calculate mean absolute error, both images have diffrent resolution\n");}
    else {printf("\nMEAN ABSOLUTE ERROR: %f \n", mean_error);}

}