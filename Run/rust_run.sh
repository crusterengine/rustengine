
#Costumizable parameters for the script: 
cd ..
cd rustengine
cargo build --bin engine02 --release

cd target/release/

compiled_program="./engine02"

#This creates a 'variable' that contains the path to the file I want to use in my program
input_file="../../../data/enwiki-tiny.txt"

#How many times to read over the same inputfile (to simulate a larger file size)
number_of_iterations="1"

#Query
query="of"

#Command line
"$compiled_program" "$input_file" "$number_of_iterations" "$query"