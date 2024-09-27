use std::env;
use std::fs::File;
use std::io::{self, BufRead};

fn count_words(file_path: &str, query: &str, total_word_count: &mut usize, total_appearances: &mut usize){

    let file = File::open(file_path).expect("Should have been able to read the file"); //Type = std::fs::File
    let reader = io::BufReader::new(file); //Type = std::io::buffered::bufreader::BufReader<std::fs::File>

    let mut line_no = 0;

    for line in reader.lines() {
        let line = line.expect("Expected to find a line");
        line_no += 1;

        for word in line.split_whitespace(){
            *total_word_count += 1;
            if word == query {
                *total_appearances += 1; 
                println!("Found query {} in line: {}", query, line_no);
            }
        }

        // let words = line.split_whitespace();

        // for str in 0..size(&words){
        //     *total_word_count += 1;
        //     if str == query {
        //         *total_appearances += 1; 
        //     }
            
        // }
    }
}

fn main() {

    let args: Vec<String> = env::args().collect();

    if args.len() != 4 {
        eprintln!("Usage: {} <file_path>", args[0]);
        return;
    }

    let file_path = &args[1];
    let query = &args[3];

    let number_of_iterations: usize = args[2].trim().parse().expect("Not a valid number of iterations");
    let mut total_word_count = 0;
    let mut total_appearances = 0;

    for _ in 0..number_of_iterations{
        count_words(file_path, query, &mut total_word_count, &mut total_appearances);
    } 

    if total_appearances < 1 {
        println!("The query {} was not found.", query);
    } else{
        println!("The file contains the query {} {} times.", query, total_appearances);
    }
    println!("The file contains {} words.", total_word_count);

}

//Files are automatically closed when they go out of scope. 
//Errors detected on closing are ignored by the implementation of Drop. 
//File does not buffer reads and writes. For efficiency, 
//wrapping the file in a BufReader or BufWriter when performing many 
//small read or write calls, unless unbuffered reads and writes are required.