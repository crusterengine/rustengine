use std::env;
use std::fs::File;
use std::io::{self, BufRead};

fn count_words(file_path: &str, word_count: usize){

    let file = File::open(file_path).expect("Should have been able to read the file"); //Type = std::fs::File
    let reader = io::BufReader::new(file); //Type = std::io::buffered::bufreader::BufReader<std::fs::File>

    for line in reader.lines() {
        let line = line.expect("Expected to find a line");
        word_count += line.split_whitespace().count();
    }

}

fn main() {

    let args: Vec<String> = env::args().collect();

    if args.len() != 3 {
        eprintln!("Missing argument, check file or counter");
        return;
    }

    let file_path = &args[1]; //&alloc::string::String

    let mut word_count = 0;
    let itr: usize = args[2].trim().parse().expect("Not a valid number of iterations");

    for _ in 0..itr{
        count_words(file_path, word_count);
    } 

    println!("The file contains {} words.", word_count);

}