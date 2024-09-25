#!/bin/zsh

# The following commands tells you which time command is used on your system
#which time
#type -a time

#The following command tells you which system you are running on:
#system_profiler SPHardwareDataType

#This creates a folder for the logs if it does not already exist
mkdir -p "log_folder_rust_file_reader"

#This captures the path to where the log files should be located
log_folder="../../../benchmarking/log_folder_rust_file_reader"

#This creates a 'variable' that contains the path to the file you want to use in the benchmarking 
input_file="../../../data/enwiki-tiny.txt"
number_of_iterations="1"

#Go into the directory of the file you want to time
cd ../rust_with_file/target/release

if [ ! -f $log_folder/results_rust.csv ]; then
    echo "timestamp,elapsed_time,user_time,sys_time,cpu_usage,max_memory,major_faults,minor_faults,voluntary_switches,involuntary_switches,number_of_iterations" >  "$log_folder/results_rust.csv"
fi

gtime -f "$(date +%Y-%m-%d\ %H:%M:%S),%e,%U,%S,%P,%M,%F,%R,%c,%w,"$number_of_iterations"" ./rust_with_file "$input_file" "$number_of_iterations" 2>> "$log_folder/results_rust.csv"

#Benchmarks the rust program based on the input file hardcoded further up
#gtime -v ./rustengine_1point1 "$input_file" "$number_of_iterations" 2> "$log_folder/time_output.txt"

#To redirect the log
#time -o timing.log ls -l