#!/bin/sh
 
file_name=dmg
 
current_time=$(date "+%H-%M-%S_%d-%m-%Y")
echo "Current Time : $current_time"

filetype=txt
new_fileName=${file_name}_${current_time}.${filetype}
echo "New FileName: " "$new_fileName"
 
echo "" > $new_fileName
echo "You should see new file generated with timestamp on it.."