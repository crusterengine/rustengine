use std::fs; 
use std::io;

fn count_words(file: &str) -> usize{
    let mut count: usize = 0; 

    let content = fs::read_to_string(file)
    .expect("Should have been able to read the file");

    let mut content_splitted = content.split_whitespace();

    while content_splitted.next().is_some() {
        count += 1;
    }

    count
}

fn main() {
    let mut file_path = String::new();
    println!("Enter the full filepath to .txt file: ");

    io::stdin()
        .read_line(&mut file_path)
        .expect("file not found");

    let file_path = file_path.trim();

    let word_count = count_words(file_path);

    println!("The file contains {} words.", word_count);

}

// cargo run 
// /Users/annesofiedahl-petersen/Desktop/Thesis/Sandbox_Rust/rustengine/rustengine/target/Data/enwiki-tiny.txt
