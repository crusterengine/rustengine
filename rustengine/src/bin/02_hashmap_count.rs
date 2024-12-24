use std::collections::HashMap;
use std::fs::File;
use std::io::{self, BufRead, Seek, SeekFrom};
use std::{env, process};

fn print_word_index(word_index: &HashMap<String, i64>) {
    for (word, count) in word_index.iter() {
        println!("{word}: {count}");
    }
}

fn find_most_frequent_word(word_index: &HashMap<String, i64>) {
    let mut currently_highest = 0;
    let mut word_appear: String = String::new();

    for (word, count) in word_index.iter() {
        if count > &currently_highest {
            currently_highest = *count;
            word_appear = word.clone();
        }
    }
    println!("The word appearing the most times is: '{word_appear}', it appeared {currently_highest} times");
}

fn process_word(word: &str, word_count: &mut usize, word_index: &mut HashMap<String, i64>) {
    *word_count += 1;
    let trimmed_word = word.trim_matches(|c: char| !c.is_ascii_alphabetic());
    let count = word_index.get_mut(trimmed_word);
    match count {
        Some(i) => *i += 1,

        None => {
            word_index.insert(trimmed_word.to_string(), 1);
        }
    };
}

// wrong process_word function - requires that the type of the hash map is changed to HashMap<String, i64>
// fn process_word(word: &str, word_count: &mut usize, word_index: &mut HashMap<String, &mut Box<i64>>) {
//     *word_count += 1;
//     let trimmed_word = word.trim_matches(|c: char| !c.is_ascii_alphabetic());
//     //let trimmed_word = word.trim_matches(|c: char| !c.is_alphabetic());
//     println!("{}", trimmed_word);
//     let count = word_index.get_mut(trimmed_word);
//     match count {
//         Some(i) => {
//             ***i += 1;
//         }
//         None => {
//             //let mut i: i64 = 1;
//             let mut first_occurence: Box<i64> = Box::new(1);
//             word_index.insert(trimmed_word.to_string(), &mut first_occurence);
//         }
//     };
// }

fn file_processing(file: &File, word_count: &mut usize, word_index: &mut HashMap<String, i64>) {
    let reader = io::BufReader::new(file);

    for line in reader.lines() {
        for word in line.expect("Expected to find a line").split_whitespace() {
            process_word(word, word_count, word_index);
        }
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 3 {
        eprintln!("Missing argument, check file or counter");
        return;
    }

    let file_path = &args[1];

    let mut file = File::open(file_path).expect("File not found");

    let mut word_count: usize = 0;

    let itr: usize = args[2].parse().expect("Not a valid number of iterations");

    let mut word_index: HashMap<String, i64> = HashMap::new();

    for _ in 0..itr {
        file_processing(&file, &mut word_count, &mut word_index);
        file.seek(SeekFrom::Start(0))
            .expect("Could not rewind file");
    }

    // println!("Rust found the file contains {} words.", word_count);

    // print_word_index(&word_index);

    // find_most_frequent_word(&word_index);
}
