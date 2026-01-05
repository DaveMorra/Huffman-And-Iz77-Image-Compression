#!/bin/bash
# Script to build and test all questions

#set -e  # Exit immediately if a command exits with a non-zero status

#echo "Running make Q1..."
#make Q1
#make Q2
#make Q3
#make Q4
#make testCompression

#make Q5
#make Q6
#make testDecompression

#make Q7
#make testComparingImages

make all

make testAll

#make cleanAll

#echo "All targets built and testCompression completed successfully."
