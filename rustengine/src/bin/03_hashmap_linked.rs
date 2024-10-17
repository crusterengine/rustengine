use std::env;
use std::fs::File;
use std::io::{self, BufRead, Seek, SeekFrom};
use std::collections::{HashMap, LinkedList};

fn search_hash_map(hash_map: &HashMap<String, LinkedList<i32>>){
    for (word, pages) in hash_map.iter() {
        print!("Word '{word}' on page");
        for page in pages{
            print!(", {}", page);
        }
        println!();
    }
}

fn search_hash_map_query(hash_map: &HashMap<String, LinkedList<i32>>, query: &String){
    for (word, pages) in hash_map.iter() {
        if word == query {
            for page in pages{
                print!(", {}", page);
            }
        }
        //println!();
    }
}

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


fn file_processing(file: &File, word_count: &mut usize, hash_map: &mut HashMap<String, LinkedList<i32>>){

    let reader = io::BufReader::new(file); 

    let mut lines: i32 = 1;

    for line in reader.lines() {
        let line = line.expect("Expected to find a line");

        lines += 1;

        let page = lines/50 + 1;

        for word in line.split_whitespace(){
            *word_count += 1;
            let trimmed_word = word.trim_matches(|c: char| !c.is_ascii_alphabetic()).to_string();
            insert_word(hash_map, trimmed_word, page);
        }
    }
}

fn main() {

    let args: Vec<String> = env::args().collect();

    // if args.len() != 4 {
    //     println!("Missing argument, check file or counter");
    //     return;
    // }

    let file_path = &args[1];
    let mut word_count = 0;
    let itr: usize = args[2].trim().parse().expect("Not a valid number of iterations");
    
    let mut file = File::open(file_path).expect("File not found"); 

    let mut hash_map: HashMap<String, LinkedList<i32>> = HashMap::new();

    let query = &args[3];

    for _ in 0..itr{
        file_processing(&file, &mut word_count, &mut hash_map);
        file.seek(SeekFrom::Start(0)).expect("Could not rewind file");
    } 
    
    //search_hash_map(&hash_map);
    //search_hash_map_query(&hash_map, query);
    println!("Total wordcount: {}", word_count);

}
