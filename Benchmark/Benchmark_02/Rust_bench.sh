#Costumizable parameters for the script: 

#How many times to read over the same inputfile (to simulate a larger file size)
number_of_iterations="1"

#This creates a 'variable' that contains the path to the file you want to use in the benchmarking 
input_file="../../../Files/the-champion.txt"

#This creates a folder for the logs if it does not already exist
mkdir -p "log_folder_02"

#This captures the path to where the log files should be located
log_folder="../../../Benchmark/Benchmark_02/log_folder_02"

#Compile the program
cd ../../rustengine
cargo build --release --bin 02_hashmap_count

#Go into the directory of the file you want to time
cd ../rustengine/target/release

#The program to be benchmarked
compiled_program="./02_hashmap_count"

# Tag for the log-file
input_filename=$(basename "$input_file")
compile_filename="Rust:${compiled_program}"

# Collect system information
machine_info=$(system_profiler SPHardwareDataType | grep "Total Number of Cores")
cpu_info=$(sysctl -n hw.model)

if [ ! -f $log_folder/results_rust.csv ]; then
    # Append system information to the log file
    echo "$machine_info,$cpu_info" > "$log_folder/results_rust.csv"
    echo "timestamp,elapsed_time,user_time,sys_time,cpu_usage,max_memory,major_faults,minor_faults,voluntary_switches,involuntary_switches,number_of_iterations,program,file" >>  "$log_folder/results_rust.csv"
fi

#for i in {0..9}
#do
gtime -f "$(date +%Y-%m-%d\ %H:%M:%S),%e,%U,%S,%P,%M,%F,%R,%c,%w,"$number_of_iterations","$compile_filename","$input_filename"" "$compiled_program" "$input_file" "$number_of_iterations" 2>> "$log_folder/results_rust.csv"
#done