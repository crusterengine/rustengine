#!/bin/zsh

# The following commands tells you which time command is used on your system
#which time
#type -a time

#This creates a 'variable' that contains the path to the file I want to use in my program
input_file="../data/the-champion.txt"

#Go into the directory of the file you want to time
cd ../cengine

#Benchmarks the
gtime -v ./scanner <<< "$input_file"

#To redirect the log
#time -o timing.log ls -l