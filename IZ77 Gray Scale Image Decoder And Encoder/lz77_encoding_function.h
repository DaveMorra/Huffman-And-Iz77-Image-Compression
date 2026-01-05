#ifndef LZ77E_H
#define LZ77E_H

// Include necessary standard libraries if needed
#include <stdio.h>
#include "libpnm.h"
#include <time.h>
#include <stdio.h>

void Encode_Using_LZ77(char *in_PGM_filename_Ptr, unsigned int searching_buffer_size, float *avg_offset_Ptr, float *std_offset_Ptr, float *avg_length_Ptr, float *std_length_Ptr);

#endif