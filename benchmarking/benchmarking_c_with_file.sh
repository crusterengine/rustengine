#!/bin/zsh

# The following commands tells you which time command is used on your system
#which time
#type -a time

#The following command tells you which system you are running on:
#system_profiler SPHardwareDataType

#Overvej hvor mange gange

#This creates a folder for the logs if it does not already exist
mkdir -p "log_folder_c_file_reader_new"

#This captures the path to where the log files should be located
log_folder="../benchmarking/log_folder_c_file_reader_new"

#This creates a 'variable' that contains the path to the file I want to use in my program
input_file="../data/enwiki-large.txt"

number_of_iterations="10"

#Go into the directory of the file you want to time
cd ../cengine_1point1

if [ ! -f $log_folder/results_c.csv ]; then
    echo "timestamp,elapsed_time,user_time,sys_time,cpu_usage,max_memory,major_faults,minor_faults,voluntary_switches,involuntary_switches,number_of_iterations" >  "$log_folder/results_c.csv"
fi

#for i in {0..10}
#do
gtime -f "$(date +%Y-%m-%d\ %H:%M:%S),%e,%U,%S,%P,%M,%F,%R,%c,%w,"$number_of_iterations"" ./cengine "$input_file" "$number_of_iterations" 2>> "$log_folder/results_c.csv"
#done

#Benchmarks the time it takes to run the program and puts the information into a txt file and saves it in a different directory
#gtime -v ./scanner "$input_file" "$number_of_iterations" 2> "$log_folder/time_output.txt"

#gtime -v ./scanner "$input_file" "$number_of_iterations"

#To redirect the log
#time -o timing.log ls -l