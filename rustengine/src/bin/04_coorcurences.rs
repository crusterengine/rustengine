use std::env;
use std::fs::File;
use std::io::{self, BufRead, Seek, SeekFrom};
use std::collections::{HashMap, LinkedList};
use std::process;



// fn print_query(word_index: &HashMap<String, LinkedList<i32>>, query: &String){
//     for (word, pages) in word_index.iter() {
//         if word == query {
//             print!("{}: ", word);
//             for page in pages{
//                 print!("{}, ", page);
//             }
//         }
//     }
//     println!();
// }

// fn print_word_index(word_index: &HashMap<String, LinkedList<i32>>){
//     for (word, pages) in word_index.iter() {
//         print!("{word}: ");
//         for page in pages{
//             print!("{}, ", page);
//         }
//         println!();
//     }
// }


fn print_graph(word_index: &HashMap<String, Node>){
    for (word, node) in word_index.iter(){
       println!("{word}: {0}", node.count);
    }
    println!();
}

struct Node {
    id: usize,
    word: String,
    count: usize,
    edges: Vec<Edge>
}

struct Edge {
    node1_id: usize,
    node2_id: usize,
    cooccurences_count: usize
}

fn update_word_index(word_index: &mut HashMap<String, Node>, word: &str) {
   
    let existing_node = word_index.get_mut(word);
    let mut id_counter: usize = 0;
    id_counter += 1;

     match existing_node {
 
         Some(existing_node) => {
            existing_node.count += 1;
            
         },

         None => {
            let mut node = Node { 
                id: id_counter, 
                word: word.to_string(), 
                count: 1, 
                edges: Vec::new() 
            };

            let edge = Edge {
                node1_id: id_counter,
                node2_id: id_counter+1,
                cooccurences_count: 1
            };

            node.edges.push(edge);

            word_index.insert(word.to_string(), node);         }
     };
 }



fn file_processing(file: &File, word_count: &mut usize, word_index: &mut HashMap<String, Node>){

    let reader = io::BufReader::new(file); 

    for line in reader.lines() {
        let line = line.expect("Expected to find a line");

        for word in line.split_whitespace(){
            *word_count += 1;
            let trimmed_word = word.trim_matches(|c: char| !c.is_ascii_alphabetic());
            update_word_index(word_index, &trimmed_word);
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

    let mut word_index: HashMap<String, Node> = HashMap::new();

    for _ in 0..itr{
        file_processing(&file, &mut word_count, &mut word_index);
        file.seek(SeekFrom::Start(0)).expect("Could not rewind file");
    } 
    
    //print_word_index(&word_index);
    //print!("The search found, ");
    //print_query(&word_index, query);
    // println!("Rust found the file contains {} words.", word_count);
    print_graph(&word_index);
    process::exit(0);

}
