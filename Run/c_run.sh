#Costumizable parameters for the script: 
cd ..
cd cengine
gcc cengine01.c -o cengine01

#The program to be benchmarked
compiled_program="./cengine01"

#This creates a 'variable' that contains the path to the file I want to use in my program
input_file="../data/the-champion.txt"

#How many times to read over the same inputfile (to simulate a larger file size)
number_of_iterations="100"

#Query
query="Hat"

#Command line
"$compiled_program" "$input_file" "$number_of_iterations" "$query"