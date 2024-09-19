#!/bin/zsh

# The following commands tells you which time command is used on your system
#which time
#type -a time

#This creates a folder for the logs if it does not already exist
mkdir -p "log_folder_rust"

#This captures the path to where the log files should be located
log_folder="/Users/ejer/Desktop/rustengine/benchmarking/log_folder_rust"

#This creates a 'variable' that contains the path to the file you want to use in the benchmarking 
input_file="../../../data/the-champion.txt"

#Go into the directory of the file you want to time
cd ../rustengine_1point1/target/debug

#/usr/bin/time -v ./scanner <<< "$input_file"

#Benchmarks the rust program based on the input file hardcoded further up
gtime -v ./rustengine_1point1 "$input_file" 2> "$log_folder/time_output.txt"

#To redirect the log
#time -o timing.log ls -l