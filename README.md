# Huffman-And-IZ77-Image-Compression Algorithms For PGM Images

## Table of Contents
- [Overview](#overview)
- [Requirements](#requirements)
- [Setup](#setup)
- [Usage](#usage)
- [Technical Overview](#technical-overview)

---

## Overview

This project implements **lossless image compression and decompression** for grayscale PGM images using **Huffman** and **IZ77** compression. The system includes **five core algorithms**.
The project is written in **C**, and is built using a provided **Makefile**.  

- **Huffman Encoder** – Compresses a raw PGM image into a custom binary `.comp` format  
- **Huffman Decoder** – Decompresses a `.comp` file back into a valid PGM image
- **Mean Absolute Error** - Comparison tool To evaluate reconstruction accuracy between original and decompressed images.
- **Huffman Decoder** – ADD MORE
- **Huffman Decoder** – ADD MORE

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

Clone or download the repository to your local machine:

```bash
git clone https://github.com/DaveMorra/Huffman-And-Iz77-Image-Compression

Navigate into the project directory and compile all executables using the provided Makefile:

```bash
make
