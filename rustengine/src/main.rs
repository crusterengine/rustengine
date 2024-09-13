use std::fs; 
use std::io;

fn main() {
    let mut file_path = String::new();
    println!("Enter the full filepath to .txt file: ");

    io::stdin()
        .read_line(&mut file_path)
        .expect("Failed to read input");

    let file_path = file_path.trim();

    let content = fs::read_to_string(file_path)
    .expect("Should have been able to read the file");

    let word_count = content.split_whitespace().count();

    println!("The file holds {} words.", word_count);
}
