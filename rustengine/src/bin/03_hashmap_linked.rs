use std::env;
use std::fs::File;
use std::io::{self, BufRead, Seek, SeekFrom};
use std::collections::{HashMap, LinkedList};
use std::process;

fn print_query(word_index: &HashMap<String, LinkedList<i32>>, query: &String){
    for (word, pages) in word_index.iter() {
        if word == query {
            print!("{}: ", word);
            for page in pages{
                print!("{}, ", page);
            }
        }
    }
    println!();
}

fn print_word_index(word_index: &HashMap<String, LinkedList<i32>>){
    for (word, pages) in word_index.iter() {
        print!("{word}: ");
        for page in pages{
            print!("{}, ", page);
        }
        println!();
    }
}


fn update_word_index(word_index: &mut HashMap<String, LinkedList<i32>>, word: &str, page:i32,) {
   
    let page_list = word_index.get_mut(word);
     
     match page_list {
 
         Some(page_list) if page_list.back() != Some(&page) => {
  
                 page_list.push_back(page)
         },

         Some(_) => return,

         None => {
             let mut new_page_list = LinkedList::new();
             new_page_list.push_back(page);
             word_index.insert(word.to_string(), new_page_list);         }
     };
 }



fn file_processing(file: &File, word_count: &mut usize, word_index: &mut HashMap<String, LinkedList<i32>>){

    let reader = io::BufReader::new(file); 

    let mut linecount: i32 = 0;

    for line in reader.lines() {
        let line = line.expect("Expected to find a line");

        linecount += 1;

        for word in line.split_whitespace(){
            *word_count += 1;
            let trimmed_word = word.trim_matches(|c: char| !c.is_ascii_alphabetic());
            let page = linecount/50 + 1;
            update_word_index(word_index, &trimmed_word, page);
        }
    }
}

fn main() {

    let args: Vec<String> = env::args().collect();

    if args.len() != 4 {
        println!("Missing argument, check file or counter");
        return;
    }

    let file_path = &args[1];

    let mut file = File::open(file_path).expect("File not found"); 

    let mut word_count = 0;
    let itr: usize = args[2].trim().parse().expect("Not a valid number of iterations");
    let query = &args[3];    

    let mut word_index: HashMap<String, LinkedList<i32>> = HashMap::new();

    for _ in 0..itr{
        file_processing(&file, &mut word_count, &mut word_index);
        file.seek(SeekFrom::Start(0)).expect("Could not rewind file");
    } 
    
    print_word_index(&word_index);
    print!("The search found, ");
    print_query(&word_index, query);
    println!("Rust found the file contains {} words.", word_count);

    process::exit(0);

}
