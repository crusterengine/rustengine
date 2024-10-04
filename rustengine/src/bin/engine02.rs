use std::env;
use std::fs::File;
use std::io::{self, BufRead};

fn track_query(file_path: &str, query: &str, total_word_count: &mut usize, total_appearances: &mut usize){

    let file = File::open(file_path).expect("File not found"); 
    let reader = io::BufReader::new(file); 

    let mut line_no = 1;
    let mut page = 1;
    //let mut new_page = true; 

    for line in reader.lines() {
        let line = line.expect("Expected to find a line");
        line_no += 1;

        if line_no == 50 {
            page += 1;
            line_no = 1;
            //new_page = true;
        }

        for word in line.split_whitespace(){
            *total_word_count += 1;
            
            let trimmed_word = word.trim_matches(|c: char| !c.is_alphabetic());
            
            //println!("{}", trimmed_word);

            if trimmed_word == query {
                *total_appearances += 1; 

                println!("Rust found query '{}' appears in page: {}", query, page);

                // if new_page {
                //     new_page = false;
                //     println!("Rust found query '{}' appears in page: {}", query, page);
                // }
            }
        }
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
        track_query(file_path, query, &mut total_word_count, &mut total_appearances);
    } 

    if total_appearances < 1 {
        println!("The query {} was not found.", query);
    } else{
        println!("The file contains the query '{}' {} times.", query, total_appearances);
    }
    println!("The file contains {} words.", total_word_count);

}

//Files are automatically closed when they go out of scope. 
//Errors detected on closing are ignored by the implementation of Drop. 
//File does not buffer reads and writes. For efficiency, 
//wrapping the file in a BufReader or BufWriter when performing many 
//small read or write calls, unless unbuffered reads and writes are required.