use std::env;
use std::fs::File;
use std::io::{self, BufRead};

//Files are automatically closed when they go out of scope.
//Files are automatically closed when they go out of scope. Errors detected on closing are ignored by the implementation of Drop. 
//File does not buffer reads and writes. For efficiency, consider wrapping the file in a BufReader or BufWriter when performing many small read or write calls, unless unbuffered reads and writes are required.

fn count_words(file_path: &str) -> usize{
    let mut count = 0; 

    let file = File::open(file_path).expect("Should have been able to read the file"); //Type = std::fs::File
    let reader = io::BufReader::new(file); //Type = std::io::buffered::bufreader::BufReader<std::fs::File>

    for line in reader.lines() {
        let line = line.expect("Expected to find a line");
        count += line.split_whitespace().count();
    }

    count
}

fn main() {

    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        eprintln!("Usage: {} <file_path>", args[0]);
        return;
    }

    let file_path = &args[1];

    let mut word_count = 0; //look at which type, so we can ensure that it is able to hold all the words
    let number_of_iterations: usize = args[2].trim().parse().expect("Not a valid number of iterations");

    for _ in 0..number_of_iterations{
        word_count += count_words(file_path);
    } 

    println!("The file contains {} words.", word_count);

}

//Hjælpe funktion til at se hvilken type ens variabler har
// fn print_type_of<T>(_: &T) {
//     println!("{}", std::any::type_name::<T>());
// }