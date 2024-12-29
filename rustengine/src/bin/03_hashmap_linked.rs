use std::collections::{HashMap, LinkedList};
use std::env;
use std::fs::File;
use std::io::{self, BufRead, Seek, SeekFrom};
use std::process;

fn print_query(word_index: &HashMap<String, LinkedList<i32>>, query: &String) {
    print!("{}: ", query);

    let linked = word_index.get(query);

    match linked {
        Some(page_list) => {
            for page in page_list.iter() {
                print!("{}, ", page);
            }
        }

        None => {
            print!("not found.");
        }
    }

    println!();
}

fn print_word_index(word_index: &HashMap<String, LinkedList<i32>>) {
    for (word, pages) in word_index.iter() {
        print!("{word}: ");
        for page in pages {
            print!("{}, ", page);
        }
        println!();
    }
}

//Testing function
fn find_word_with_max_page_count(word_index: &HashMap<String, LinkedList<i32>>) {
    let mut max_count = 0;
    let mut word_appear = Vec::new();

    for (word, count) in word_index.iter() {
        if count.len() > max_count {
            max_count = count.len();
            word_appear.clear();
            word_appear.push(word);
        } else if count.len() == max_count {
            word_appear.push(word);
        }
    }

    print!("These words appears on the highest number of different pages: ");
    for word in word_appear {
        print!("'{word}', ");
    }
    println!("they appeared {max_count} times ");
}

fn process_word(
    word: &str,
    word_count: &mut usize,
    word_index: &mut HashMap<String, LinkedList<i32>>,
    linecount: i32,
) {
    *word_count += 1;
    let trimmed_word = word.trim_matches(|c: char| !c.is_ascii_alphabetic());
    let page = linecount / 50 + 1;
    let page_list = word_index.get_mut(trimmed_word);

    match page_list {
        Some(page_list) if page_list.back() != Some(&page) => page_list.push_back(page),

        Some(_) => return,

        None => {
            let mut new_page_list = LinkedList::new();
            new_page_list.push_back(page);
            word_index.insert(trimmed_word.to_string(), new_page_list);
        }
    };
}

// Wrong process_word function
// fn process_word(word: &str, word_count: &mut usize, word_index: &mut HashMap<String, LinkedList<i32>>, linecount:i32) {
//     *word_count += 1;
//     let trimmed_word = word.trim_matches(|c: char| !c.is_ascii_alphabetic());
//     let page = linecount/50 + 1;
//     let page_list = word_index.get_mut(trimmed_word);

//      match page_list {

//          Some(page_list) if page_list.back() != Some(&page) => {

//                  page_list.push_back(page)
//          },

//          Some(_) => return,

//          None => {
//              let mut new_page_list = LinkedList::new();
//              new_page_list.push_back(page);
//              word_index.insert(trimmed_word.to_string(), new_page_list);
//              let end_marker = 0;
//              new_page_list.push_back(end_marker);
//         }
//      };
//  }

fn file_processing(
    file: &File,
    word_count: &mut usize,
    word_index: &mut HashMap<String, LinkedList<i32>>,
) {
    let reader = io::BufReader::new(file);

    let mut linecount: i32 = 0;

    for line in reader.lines() {
        linecount += 1;
        for word in line.expect("Expected to find a line").split_whitespace() {
            process_word(word, word_count, word_index, linecount);
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
    let itr: usize = args[2]
        .trim()
        .parse()
        .expect("Not a valid number of iterations");
    let query = &args[3];

    let mut word_index: HashMap<String, LinkedList<i32>> = HashMap::new();

    for _ in 0..itr {
        file_processing(&file, &mut word_count, &mut word_index);
        file.seek(SeekFrom::Start(0))
            .expect("Could not rewind file");
    }

    // println!("Rust found the file contains {} words.", word_count);

    // print_word_index(&word_index);

    // print_query(&word_index, query);

    // find_word_with_max_page_count(&word_index);

    process::exit(0);
}
