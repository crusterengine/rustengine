use std::fs; 
use std::env;


fn count_words(file: &str) -> i32{
    let mut count: i32 = 0; 

    let content = fs::read_to_string(file) //this turns it into a String and therefore uses heap
    .expect("Should have been able to read the file");

    let mut content_splitted = content.split_whitespace();

    while content_splitted.next().is_some() {
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

    let file_path = &args[1];

    //sæt loop rundt om denne her så vi kører det x antal gange
    let word_count = count_words(file_path);

    println!("The file contains {} words.", word_count);

}