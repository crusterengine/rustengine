#!/bin/bash

# How many times to read over the same input file (to simulate a larger file size)
number_of_iterations="1000"

# The program to be benchmarked
compiled_program="./01_countwords"

# The input file
input_file="../data/the-champion.txt"

# Log folder setup
mkdir -p "log_folder"

#This captures the path to where the log files should be located
log_folder="../Benchmark/log_folder"

# Tag for the log-file
input_filename=$(basename "$input_file")
compile_filename="C:${compiled_program}"

# Go into the directory of the file you want to time
cd ../cengine

# Collect system information
machine_info=$(system_profiler SPHardwareDataType | grep "Total Number of Cores")
cpu_info=$(sysctl -n hw.model)

# Initialize cumulative variables
total_user_time=0
total_max_memory=0

# Create log file with headers if it does not exist
if [ ! -f "$log_folder/results_c.csv" ]; then
    echo "$machine_info,$cpu_info" > "$log_folder/results_c.csv"
    echo "timestamp,elapsed_time,user_time,sys_time,cpu_usage,max_memory,major_faults,minor_faults,voluntary_switches,involuntary_switches,number_of_iterations,program,file" >> "$log_folder/results_c.csv"
fi

# Loop over the specified number of iterations
for i in {0..9}; do
    # Run the program and capture gtime output
    output=$(gtime -o temp_gtime.txt -f "%e %U %S %P %M %F %R %c %w" "$compiled_program" "$input_file" "$number_of_iterations" 2>&1)

    # Read the gtime output from the file
    read elapsed_time user_time sys_time cpu_usage max_memory major_faults minor_faults voluntary_switches involuntary_switches < temp_gtime.txt

    # Accumulate user time and max memory
    total_user_time=$(echo "$total_user_time + $user_time" | bc)
    total_max_memory=$(echo "$total_max_memory + $max_memory" | bc)

    # Log each iteration's output
    echo "$(date +%Y-%m-%d\ %H:%M:%S),$elapsed_time,$user_time,$sys_time,$cpu_usage,$max_memory,$major_faults,$minor_faults,$voluntary_switches,$involuntary_switches,$number_of_iterations,$compile_filename,$input_filename" >> "$log_folder/results_c.csv"
done

# Calculate the average user time and max memory
average_user_time=$(echo "$total_user_time / 10" | bc -l)
average_max_memory=$(echo "$total_max_memory / 10" | bc -l)

# Log the final averages
echo "Average user time: $average_user_time seconds for $number_of_iterations iterations" >> "$log_folder/results_c.csv"
echo "Average max memory: $average_max_memory kilobytes for $number_of_iterations iterations" >> "$log_folder/results_c.csv"

# Clean up temporary file
rm -f temp_gtime.txt

echo "done with benchmarking"