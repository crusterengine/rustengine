use std::collections::HashMap;
use std::env;
use std::fs::File;
use std::io::{self, BufRead, Seek, SeekFrom};

fn print_word_index(word_index: &HashMap<String, i64>) {
    for (word, count) in word_index.iter() {
        println!("{word}: {count}");
    }
}

fn update_word_index(word_index: &mut HashMap<String, i64>, word: String) {
    let count = word_index.get_mut(&word);

    match count {
        Some(i) => *i += 1,

        None => {
            word_index.insert(word, 1);
        }
    };
}

fn file_processing(file: &File, word_count: &mut usize, word_index: &mut HashMap<String, i64>) {
    let reader = io::BufReader::new(file);

    for line in reader.lines() {

        for word in line.expect("Expected to find a line").split_whitespace() {
            *word_count += 1;
            let trimmed_word = word.trim_matches(|c: char| !c.is_alphabetic()).to_string(); //trimmed_word is type &str
            update_word_index(word_index, trimmed_word);
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
    let itr: usize = args[2]
        .trim()
        .parse()
        .expect("Not a valid number of iterations");

    let mut word_index: HashMap<String, i64> = HashMap::new();

    for _ in 0..itr {
        file_processing(&file, &mut word_count, &mut word_index);
        file.seek(SeekFrom::Start(0))
            .expect("Could not rewind file");
    }

    print_word_index(&word_index);
    println!("Rust found the file contains {} words.", word_count);

}
