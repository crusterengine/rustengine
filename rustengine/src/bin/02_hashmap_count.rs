use std::collections::HashMap;
use std::{env, process};
use std::fs::File;
use std::io::{self, BufRead, Seek, SeekFrom};

fn print_word_index(word_index: &HashMap<String, i64>) {
    for (word, count) in word_index.iter() {
        println!("{word}: {count}");
    }
}

fn update_word_index(word_index: &mut HashMap<String, i64>, word: &str, map_word_count: &mut usize) {
    let count = word_index.get_mut(word); //while we have this reference, no one else is allowed to have a reference to it
    *map_word_count += 1;
    match count {
        Some(i) => *i += 1,

        None => {
            word_index.insert(word.to_string(), 1);
        }
    };
}

//anden udgave af ovenstående program
fn update_word_index(word_index: &mut HashMap<String, i64>, word: &str, map_word_count: &mut usize) {
    *map_word_count += 1;
    *word_index.entry(word.to_string()).or_insert(0) += 1;
}


fn file_processing(file: &File, word_count: &mut usize, map_word_count: &mut usize, word_index: &mut HashMap<String, i64>) {
    let reader = io::BufReader::new(file);

    for line in reader.lines() {

        for word in line.expect("Expected to find a line").split_whitespace() {
            *word_count += 1;
            let trimmed_word = word.trim_matches(|c: char| !c.is_ascii_alphabetic());
            update_word_index(word_index, &trimmed_word, map_word_count);
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
    let mut map_word_count:usize = 0;
    let itr: usize = args[2]
        .trim()
        .parse()
        .expect("Not a valid number of iterations");

    let mut word_index: HashMap<String, i64> = HashMap::new();

    for _ in 0..itr {
        file_processing(&file, &mut word_count, &mut map_word_count, &mut word_index);
        file.seek(SeekFrom::Start(0))
            .expect("Could not rewind file");
    }

    //print_word_index(&word_index);

    // let map_size: usize = word_index.len();
    // println!("The size of the map is: {}", map_size);
    // println!("The map contains: {} elements", map_word_count);
    // println!("Rust found the file contains {} words.", word_count);

    process::exit(0);

}
