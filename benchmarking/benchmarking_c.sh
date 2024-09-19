#!/bin/zsh

# The following commands tells you which time command is used on your system
#which time
#type -a time

#This creates a folder for the logs if it does not already exist
mkdir -p "log_folder_c"

#This captures the path to where the log files should be located
log_folder="../benchmarking/log_folder_c"

#This creates a 'variable' that contains the path to the file I want to use in my program
input_file="../data/the-champion.txt"

number_of_iterations="1000"

#Go into the directory of the file you want to time
cd ../cengine

if [ ! -f $log_folder/results_c.csv ]; then
    echo "timestamp,elapsed_time,user_time,sys_time,cpu_usage,max_memory,major_faults,minor_faults,voluntary_switches,involuntary_switches,number_of_iterations" >  "$log_folder/results_c.csv"
fi

gtime -f "$(date +%Y-%m-%d\ %H:%M:%S),%e,%U,%S,%P,%M,%F,%R,%c,%w,"$number_of_iterations"" ./scanner "$input_file" "$number_of_iterations" 2>> "$log_folder/results_c.csv"

#Benchmarks the time it takes to run the program and puts the information into a txt file and saves it in a different directory
gtime -v ./scanner "$input_file" "$number_of_iterations" 2> "$log_folder/time_output.txt"


#To redirect the log
#time -o timing.log ls -l