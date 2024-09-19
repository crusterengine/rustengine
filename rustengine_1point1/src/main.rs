use std::fs; 
use std::env;


fn count_words(file: &str) -> usize{
    let mut count = 0; 

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

    let mut word_count = 0; //look at which type, so we can ensure that it is able to hold all the words
    let number_of_iterations: usize = args[2].trim().parse().expect("Not a valid number of iterations");

    print_type_of(&word_count);

    for _ in 0..number_of_iterations{
        word_count += count_words(file_path);
    } 

    println!("The file contains {} words.", word_count);

}

//Hjælpe funktion til at se hvilken type ens variabler har
fn print_type_of<T>(_: &T) {
    println!("{}", std::any::type_name::<T>());
}