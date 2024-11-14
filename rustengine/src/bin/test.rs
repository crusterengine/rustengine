use std::env;
use std::fs::File;
use std::path::Path;
use std::io::{self, BufRead, BufReader, Seek, SeekFrom};


fn process_word(word: &[u8], word_count: &mut u64) {
    if !word.is_empty() {
        *word_count += 1; // Increment the word count
    }
}

fn file_processing(file: &File, word_count: &mut u64) -> io::Result<()> {
    let mut word_buffer = [0u8; 512]; // Stack-based buffer for each word
    let mut word_index = 0; // Index to track the current word length
    let reader = BufReader::new(file);

    for line in reader.lines() {
        let line = line?; // Read each line from the file
        let mut new_word = false;

        for byte in line.bytes() {
            if byte.is_ascii_whitespace() {
                if new_word {
                    process_word(&word_buffer[..word_index], word_count);
                    // Print the current word as a string
                    //println!("word: {}", String::from_utf8_lossy(&word_buffer[..word_index]));
                    word_index = 0; // Reset for the next word
                    new_word = false;
                    // Clear the word buffer
                    word_buffer = [0u8; 512];
                }
            } else {
                if word_index < 512 {
                    word_buffer[word_index] = byte; // Add the byte to the word buffer
                    word_index += 1; // Increment the index
                    new_word = true; // Indicate that a new word is being formed
                }
            }
        }

        // Process any remaining word in the buffer at the end of the line
        if new_word {
            process_word(&word_buffer[..word_index], word_count);
        }
    }

    Ok(())
}

fn main() -> io::Result<()> {
    let args: Vec<String> = env::args().collect();

    if args.len() != 3 {
        eprintln!("Missing argument, check file path or iteration count");
        return Ok(());
    }

    let file_path = &args[1];
    let file = File::open(&Path::new(file_path))?;

    // Create a BufReader with a specific capacity (stack-based)
    let mut reader = BufReader::with_capacity(8192, file);
    let mut word_count = 0; // Initialize word count
    let itr: usize = args[2].parse().expect("Invalid iteration count");

    for _ in 0..itr {
        // Process the contents of the file
        file_processing(&reader.get_ref(), &mut word_count)?;
        reader.get_mut().seek(std::io::SeekFrom::Start(0))?; // Reset file to the beginning for the next iteration
    }

    println!("The file contains {} words.", word_count);

    Ok(())
}
