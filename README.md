# rustengine
A Thesis Project exploring memory management for a search engine written with rust. 

To run the cengine-application. 
    gcc cengine01.c -o cengine01
    ./cengine01 <file-path> <num of iterations>

To run the benchmarking of the c-program. Make sure the parameters of the C_bench.sh is correct. Make sure you have the right permissions. 
    ls -l C_bench.sh
    chmod +x C_bench.sh
    ./C_bench.sh

To run the rustengine-application
    Gp to the rustengine directory and compile the program
    cargo build --release
    ./rustengine <file-path> <num of iterations>

To run the benchmarking of the rust-program. Make sure the parameters of the Rust_bench.sh is correct. Make sure you have the right permissions. 
    ls -l Rust_bench.sh
    chmod +x Rust_bench.sh
    ./Rust_bench.sh

To run C code with a hashmap (so 02 and 03) use the following command: gcc "program_name" -o "compiled version name" $(pkg-config --cflags --libs glib-2.0)