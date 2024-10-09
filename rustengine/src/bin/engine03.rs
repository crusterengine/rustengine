use std::env;
use std::fs::File;
use std::io::{self, BufRead};
use std::collections::{HashMap, LinkedList};

fn insert_word(hash_map: &mut HashMap<String, LinkedList<i32>>, word_key: String, page :i32){
    
    if hash_map.contains_key(&word_key){
       let pages = hash_map.get_mut(&word_key); 
       pages.expect("could not find likedlist").push_back(page);
    } 
    else {
     let mut page_list = LinkedList::new();
     page_list.push_back(page);
     hash_map.insert(word_key, page_list); 
    }
}


fn file_processing(file_path: &str, total_word_count: &mut usize, hash_map: &mut HashMap<String, LinkedList<i32>>){

    let file = File::open(file_path).expect("File not found"); 
    let reader = io::BufReader::new(file); 

    let mut line_no = 1;

    for line in reader.lines() {
        let line = line.expect("Expected to find a line");

        line_no += 1;
        let page = line_no/50 + 1;

        for word in line.split_whitespace(){
            *total_word_count += 1;
            let trimmed_word = word.trim_matches(|c: char| !c.is_alphabetic()).to_string(); //trimmed_word is type &str
            insert_word(hash_map, trimmed_word, page);
        }
    }
}

// fn search_hash_map(hash_map: &HashMap<String, LinkedList<i32>>){
//     for (word, pages) in hash_map.iter() {
//         print!("Word '{word}' on page");
//         for page in pages{
//             print!(", {}", page);
//         }
//         println!();
//     }
// }

fn main() {

    let args: Vec<String> = env::args().collect();

    if args.len() != 3 {
        eprintln!("Usage: {} <file_path>", args[0]);
        return;
    }

    let file_path = &args[1];

    let number_of_iterations: usize = args[2].trim().parse().expect("Not a valid number of iterations");
    let mut total_word_count = 0;
    let mut hash_map: HashMap<String, LinkedList<i32>> = HashMap::new();

    for _ in 0..number_of_iterations{
        file_processing(file_path, &mut total_word_count, &mut hash_map);
    } 
    
    //search_hash_map(&hash_map);
    
    println!("The file contains {} words.", total_word_count);

}

//Files are automatically closed when they go out of scope. 
//Errors detected on closing are ignored by the implementation of Drop. 
//File does not buffer reads and writes. For efficiency, 
//wrapping the file in a BufReader or BufWriter when performing many 
//small read or write calls, unless unbuffered reads and writes are required.
// fn print_type_of<T>(_: &T) {
//     println!("{}", std::any::type_name::<T>());
// }