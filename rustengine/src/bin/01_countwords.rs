use std::env;
use std::fs::File;
use std::io::{self, BufRead, Seek, SeekFrom};

fn file_processing(file: &File, word_count: &mut usize) {
    let reader = io::BufReader::new(file); //Type = std::io::buffered::bufreader::BufReader<std::fs::File>

    for line in reader.lines() {
        *word_count += line
            .expect("Expected to find a line")
            .split_whitespace()
            .count();
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

    let mut word_count = 0;
    let itr: usize = args[2]
        .trim()
        .parse()
        .expect("Not a valid number of iterations");

    for _ in 0..itr {
        file_processing(&file, &mut word_count);
        file.seek(SeekFrom::Start(0))
            .expect("Could not rewind file");
    }

    //println!("The file contains {} words.", word_count);
}
