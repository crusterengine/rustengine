#Costumizable parameters for the script: 
cd ..
cd cengine
gcc 03_hashmap_linked.c -o cengine02 `pkg-config --cflags --libs glib-2.0`

#The program to be benchmarked
compiled_program="./cengine02"

#This creates a 'variable' that contains the path to the file I want to use in my program
input_file="../data/the-champion.txt"

#How many times to read over the same inputfile (to simulate a larger file size)
number_of_iterations="1"

#Query
query="fellow"

#Command line
"$compiled_program" "$input_file" "$number_of_iterations" "fellow"