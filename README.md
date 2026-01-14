# Huffman-And-IZ77-Image-Compression Algorithms For PGM Images

## Table of Contents
- [Overview](#overview)
- [Requirements](#requirements)
- [Setup](#setup)

---

## Overview

This project implements **lossless image compression and decompression** for grayscale PGM images using **Huffman** and **IZ77** compression. The system includes **five core algorithms**.
The project is written in **C**, and is built using a provided **Makefile**.  

- **Huffman Encoder** – Compresses a raw PGM image into a custom binary `.comp` format  
- **Huffman Decoder** – Decompresses a `.comp` file back into a valid PGM image
- **Iz77 Encoder** – Compresses a raw PGM image into a custom binary `.comp` format  
- **Iz77 Decoder** – Decompresses a `.comp` file back into a valid PGM image
- **Mean Absolute Error** - Comparison tool To evaluate reconstruction accuracy between original and decompressed images.

The images, makefile the libpnm library used in this project were provided by Professor **[Mahmoud R. El-Sakka](https://www.csd.uwo.ca/~melsakka/)**.

---

## Requirements

Before building or running this project, ensure that you meet the following requirements:

### Software Dependencies
- **GCC Compiler**
- **GNU Make**
- **Unix-based environment**

### Image Format
- Input images must be **raw grayscale PGM files** (`.raw.pgm`)

---

## Setup

### Step 1: Clone the Repository
First, clone or download this repository to your local machine.
```
git clone https://github.com/DaveMorra/Huffman-And-Iz77-Image-Compression
```
Then, navigate to the source directory of your choice:
```
cd Huffman-And-Iz77-Image-Compression
```
```
cd Huffman-And-Iz77-Image-Compression
```

### Step 2: Compile and Run
Compile the given project:
```
make all
```
```
./pgm_huffman_encode boats.raw.pgm boats.comp
```
```
./pgm_huffman_decode rectangle.comp      rectangle.decomp.pgm
```
```
./lz77_encoding boats.raw.pgm boats.comp
```
```
./lz77_decoding rectangle.comp      rectangle.decomp.pgm
```
```
./compare_pgm_images boats.raw.pgm boats.decomp.pgm
```
