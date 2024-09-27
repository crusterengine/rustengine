
#Costumizable parameters for the script: 

#How many times to read over the same inputfile (to simulate a larger file size)
number_of_iterations="10"

#The program to be benchmarked
compiled_program="./cengine01"

#This creates a 'variable' that contains the path to the file I want to use in my program
input_file="../data/the-champion.txt"

#This creates a folder for the logs if it does not already exist
mkdir -p "log_folder_cmf3"

#This captures the path to where the log files should be located
log_folder="../Benchmark/log_folder_cmf3"

# Tag for the log-file
input_filename=$(basename "$input_file")

#Go into the directory of the file you want to time
cd ../cengine

# Collect system information
machine_info=$(system_profiler SPHardwareDataType | grep "Total Number of Cores")
cpu_info=$(sysctl -n hw.model)

# If  logfolder does not include the logfile. Created with neccesary labels. 
if [ ! -f $log_folder/results_c.csv ]; then
    # Append system information to the log file
    echo "$machine_info,$cpu_info" > "$log_folder/results_c.csv"
    echo "timestamp,elapsed_time,user_time,sys_time,cpu_usage,max_memory,major_faults,minor_faults,voluntary_switches,involuntary_switches,number_of_iterations,program,file" >>  "$log_folder/results_c.csv"
fi

#for i in {0..10}
#do
gtime -f "$(date +%Y-%m-%d\ %H:%M:%S),%e,%U,%S,%P,%M,%F,%R,%c,%w,"$number_of_iterations","$compiled_program","$input_filename"" "$compiled_program" "$input_file" "$number_of_iterations" 2>> "$log_folder/results_c.csv"
#done
