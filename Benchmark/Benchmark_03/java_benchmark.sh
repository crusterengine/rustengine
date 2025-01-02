#How many times to read over the same inputfile (to simulate a larger file size)
number_of_iterations="1"

#This creates a 'variable' that contains the path to the file I want to use in my program
input_file="../data/the-champion.txt"

#This creates a folder for the logs if it does not already exist
mkdir -p "log_folder_03"

#This captures the path to where the log files should be located
log_folder="../Benchmark/Benchmark_03/log_folder_03"


#Go into the directory of the file you want to time
cd ../../javaengine

javac javastrem.java

#The program to be benchmarked
compiled_program="javastrem"

# Tag for the log-file
input_filename=$(basename "$input_file")
compile_filename="Java:${compiled_program}"

# Collect system information
machine_info=$(system_profiler SPHardwareDataType | grep "Total Number of Cores")
cpu_info=$(sysctl -n hw.model)

# If  logfolder does not include the logfile. Created with neccesary labels. 
if [ ! -f $log_folder/results_java.csv ]; then
    # Append system information to the log file
    echo "$machine_info,$cpu_info" > "$log_folder/results_java.csv"
    echo "timestamp,elapsed_time,user_time,sys_time,cpu_usage,max_memory,major_faults,minor_faults,voluntary_switches,involuntary_switches,number_of_iterations,program,file" >>  "$log_folder/results_java.csv"
fi

#for i in {0..9}
#do
gtime -f "$(date +%Y-%m-%d\ %H:%M:%S),%e,%U,%S,%P,%M,%F,%R,%c,%w,"$number_of_iterations","$compile_filename","$input_filename"" java -cp . "$compiled_program" "$input_file" "$number_of_iterations" "fellow" 2>> "$log_folder/results_java.csv"
#done
