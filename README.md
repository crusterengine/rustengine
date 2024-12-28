# rustengine
This code repository is part of a Master Thesis Project, that exploes memory management in the Rust and C programming languages.  

The code repository contains three programs written in C and Rust: countwords, hashmap_count and hashmap linked. It also contains shell scripts that can be ran to benchmark the programs using the GNU time command. 

# Instructions
Below are the instructions on how to compile and run each program and how to run the benchmarking scripts.

### The C programs
Make sure that you are in the `cengine` directory

To compile and run the 01_countwords.c program:  
   1. `gcc -O3 -o 01_countwords 01_countwords.c`    
   2. `./01_countwords <file-path> <num of iterations>`  

To compile and run the 02_hashmap_count.c program:  
   1. `gcc -O3 -o 02_hashmap_count 02_hashmap_count.c $(pkg-config --cflags --libs glib-2.0)`    
   2. `./02_hashmap_count <file-path> <num of iterations>`  

To compile and run the 03_hashmap_linked.c program:  
   1. `gcc -O3 -o 03_hashmap_linked 03_hashmap_linked.c $(pkg-config --cflags --libs glib-2.0)`    
   2. `./03_hashmap_linked <file-path> <num of iterations> <query word>`  

### The Rust programs
Make sure that you are in the `rustengine` directory

To compile and run 01_countwords.rs
  1.  `cargo build --release --bin 01_countwords`
  2.  `cd target/release`  
  2.  `./01_countwords <file-path> <num of iterations>`

Alternatively the program can be compiled and ran with the following command:  
`cargo run --bin 01_countwords <file-path> <num of iterations>`

To compile and run 02_hashmap_count.rs
  1.  `cargo build --release --bin 02_hashmap_count`
  2.  `cd target/release`  
  2.  `./02_hashmap_count <file-path> <num of iterations>`

Alternatively the program can be compiled and ran with the following command:  
`cargo run --bin 02_hashmap_count <file-path> <num of iterations>`

To compile and run 03_hashmap_linked.rs
  1.  `cargo build --release --bin 03_hashmap_linked`
  2.  `cd target/release`  
  2.  `./03_hashmap_linked <file-path> <num of iterations> <query word>`

Alternatively the program can be compiled and ran with the following command:  
`cargo run --bin 03_hashmap_linked <file-path> <num of iterations> <query word>`

### The benchmarks
Make sure that you are in the `Benchmark` directory. In the `Benchmark` directory, there is three directories, one for each version of the program.  

Once `cd`'et into the wanted directory make sure you have the right permissions.  

    To check the permissions: ls -l <script>.sh
    To give execute permission: chmod +x <script>.sh

Inside the benchmarking scripts the code will be compiled and ran, so there is no need to compile it beforehand.  

Make sure that the parameters are set correctly in the `<script>.sh` file.  

To run the script, execute the following command:  

`./<script>.sh`