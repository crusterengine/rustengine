use std::fs; 
use std::env;

fn main() {

    let args: Vec<String> = env::args().collect();

    if args.len() < 2 {
        eprintln!("Usage: {} <file_path>", args[0]);
        return;
    }

    let file_path = &args[1];

    let mut word_count = 0; //look at which type, so we can ensure that it is able to hold all the words
    let number_of_iterations: usize = args[2].trim().parse().expect("Not a valid number of iterations");

    let content = fs::read_to_string(file_path) //this turns it into a String and therefore uses heap
    .expect("Should have been able to read the file");

    for _ in 0..number_of_iterations{
        word_count += content.split_whitespace().count();

    } 

    println!("The file contains {} words.", word_count);

}

// cargo run 
// Copy the full path for the file