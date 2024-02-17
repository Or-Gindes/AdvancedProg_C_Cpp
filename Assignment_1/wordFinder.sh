#!/bin/bash

input_array=($@)
# Save next to last char which is the first char of words to search
first_char=${@: -2:1}
# Save last num
last_num=${@: -1}
# Set error_flag to indicate if input errors have occured
error_flag=false
erro_message="Usage : wordFinder.sh <valid file name> [More Files] ... <char> <length>"

# Check inputs:
# 1. atleast 3 inputs are required
if [ $# -lt 3 ]
then
    echo "Number of parameters received : $#" 1>&2
    error_flag=true
else 
    # 2. next to last input must be a single valid char ([A-Z] or [a-z] or [0-9])
    if [ ${#first_char} -gt 1 ] || ([[ $first_char != [A-Z] ]] && [[ $first_char != [a-z] ]] && [[ $first_char != [0-9] ]])
    then
        echo "Only one char needed : $first_char" 1>&2
        error_flag=true
    fi
    # 3. last input must be a positive number
    if (! [[ $last_num =~ ^[0-9]+$ ]]) || [ $last_num -le 0 ]
    then 
        echo "Not a positive number : $last_num" 1>&2
        error_flag=true
    fi
fi

# 4. is any errors occured, print the error message and exist
if [ $error_flag = true ]; then
    echo $erro_message
    exit -1
fi

# 5. Check if files are valid - iterate over each element excluding the last two
for read_file in ${input_array[@]::${#input_array[@]}-2}
do
    if ! [ -f $read_file ]; then
        echo "File does not exist : $read_file" 1>&2
        error_flag=true
    fi
done
# if any of the input files were not valid - need to print useage message and exit
if [ $error_flag = true ]; then
    echo $erro_message
    exit -1
fi

let min_length=$last_num-1
let number_of_docs=$#-2
if [ $number_of_docs -gt 1 ]; then
    read_file=${input_array[@]::${#input_array[@]}-2}
    result=`grep -oiE "(\b|\W|_)($first_char[A-Za-z0-9]{$min_length,})" $read_file | grep -oi ':.*' | grep -oi '[^:]*' | sed -E 's/(\b|\W|_)//' | sort -f | uniq -ci | sed 's/^\s*//' | sort -n`
    [ ! -z "$result" ] && echo "$result"
else 
    read_file=${input_array[0]}
    result=`grep -oiE "(\b|\W|_)($first_char[A-Za-z0-9]{$min_length,})" $read_file | sed -E 's/(\b|\W|_)//' | sort -f | uniq -ci | sed 's/^\s*//' | sort -n`
    [ ! -z "$result" ] && echo "$result"
fi