# Hamming Code Project

This repository contains a Hamming Code implementation created on UMB Unix servers and written in C. The project demonstrates the use of error-detecting and error-correcting codes to ensure data integrity during file partitioning and reconstruction.

## Project Overview

The Hamming Code project comprises two main programs:

1. diarBetim: Partitions the input file and performs Hamming code operations to encode the data.

2. raidBetim: Checks and corrects errors in the encoded data and reconstructs the original file.

The program operates on an input text file provided by the user and produces a reconstructed file, ```<input_file.txt>.2``` The output file can then be compared with the original to verify the success of the Hamming code.

## Key Components

1. File Partitioning and Encoding (diarBetim):

    -Reads the input file an input text file.

    -Applies Hamming code to partition and encode the data.

2. Error Detection and Correction (raidBetim):

    -Checks for errors in the encoded data.

    -Corrects errors and reconstructs the original file.

    -Produces a file ```<input_file.txt>.2``` for comparison with the original.

## How to Run

1. Clone the repository:
```
git clone https://github.com/yourusername/hamming-code-project.git
```
2. Navigate to the project directory:
```
cd hamming-code-project
```
3. Compile the programs using the provided Makefile:
```
make
```
4. Run ```diarBetim``` to parition and encode the data. Provide the input file as an argument:
```
./diarBetim <input_file.txt>
```
5. Run the ```raidBetim``` to check and correct errors and reconstruct the file. Output file will be named <input_file.txt>.2
```
./raidBetim <input_file.txt>
```
6. Compare the original file with the reconstructed file to verify the Hamming code's success using the ```cmp``` command:
```
cmp <input_file.txt> <input_file.txt>.2
```

## Files in the Repository

```Makefile```: Automates the compilation process for the project.

```diarBetim```: Program to partition and encode the file using Hamming code.

```raidBetim```: Program to detect and correct errors and reconstruct the original file.

```<input_file.txt>``` Test file used for encoding and decoding.

```<input_file.txt>.2```: Reconstructed file for validation

## Skills and Tools Used
Language: C

Environment: Linux, UMB Unix Servers

Concepts: Hamming code, file I/O, error detection and correction

## Learning Outcomes
Gained hands-on experience with error-detecting and error-correcting codes.

Improved understanding of Hamming code implementation in a real-world scenario.

Enhanced proficiency in file manipulation and system programming in C.
