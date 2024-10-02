use std::env;
use std::fs::File;
//use std::io::{self, BufRead};
use std::io::BufReader;

fn new_word(file: BufReader<File>, word: &str) -> bool {
    
    for line in file.lines() {
        let line = line.expect("Expected to find a line");

        for word_in_line in line.split_whitespace(){
            word = word_in_line;
        }
        return true;
    }
    return false
}

fn count_words(file_path: &str) -> usize{
    let mut count = 0; 

    let mut &(mut str);

    let file = File::open(file_path).expect("Should have been able to read the file"); //Type = std::fs::File
    let reader = io::BufReader::new(file); //Type = std::io::buffered::bufreader::BufReader<std::fs::File>

    while new_word(reader, &str){
        count += 1;
    }
    count
}

fn main() {

    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        eprintln!("Usage: {} <file_path>", args[0]);
        return;
    }

    let file_path = &args[1]; //&alloc::string::String

    let mut word_count = 0;
    let number_of_iterations: usize = args[2].trim().parse().expect("Not a valid number of iterations");

    for _ in 0..number_of_iterations{
        word_count += count_words(file_path);
    } 

    println!("The file contains {} words.", word_count);

}