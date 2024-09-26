**Find type: 
Hjælpe funktion i rust til at se hvilken type ens variabler har
        fn print_type_of<T>(_: &T) {
         println!("{}", std::any::type_name::<T>());
        }   