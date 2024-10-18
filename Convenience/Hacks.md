**Find type: 
Hjælpe funktion i rust til at se hvilken type ens variabler har
        fn print_type_of<T>(_: &T) {
         println!("{}", std::any::type_name::<T>());
        }   

Information about Rust's file opener:
- Files are automatically closed when they go out of scope. 
- Errors detected on closing are ignored by the implementation of Drop. 
- File does not buffer reads and writes. For efficiency,wrapping the file in a BufReader or BufWriter when performing many small read or write calls, unless unbuffered reads and writes are required.
