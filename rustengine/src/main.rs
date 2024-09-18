use std::fs; 
use std::io;

fn count_words(content: String) -> usize{
    let mut count: usize = 0; 
    let content_splitted = content.split_whitespace();

    while!content_splitted.isEmpty(){
        count += 1;
    }

    count
}

fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>());
}

fn main() {
    let mut file_path = String::new();
    println!("Enter the full filepath to .txt file: ");

    io::stdin()
        .read_line(&mut file_path)
        .expect("Failed to read input");

    let file_path = file_path.trim();

    let content = fs::read_to_string(file_path)
    .expect("Should have been able to read the file");

    let word_count = count_words(content);

    //println!("The type of word_count is {}", type.of(&word_count));

    //print_type_of(&content);
    //print_type_of(&word_count );


    println!("The file holds {} words.", word_count);
}

// cargo run 
// /Users/annesofiedahl-petersen/Desktop/Thesis/Sandbox_Rust/rustengine/rustengine/target/Data/enwiki-tiny.txt
