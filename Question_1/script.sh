#!/bin/bash

# create directories for backups and errors first
mkdir -p unique_backup errors

# setup variables
processed=0
duplicates=0
backed_up=0

# array to track the hashes
declare -A seen_hashes

# loop through all files in the submissions folder
for file in submissions/*; do
    if [ -f "$file" ]; then
        ((processed++))
        
        # get the md5 hash to check for duplicate content
        file_hash=$(md5sum "$file" 2>> errors/error_log.txt | awk '{print $1}')
        
        # check if we already saw this file hash
        if [[ -n "${seen_hashes[$file_hash]}" ]]; then
            ((duplicates++))
        else
            # it's unique, so save the hash and backup the file
            seen_hashes[$file_hash]=1
            cp "$file" unique_backup/ 2>> errors/error_log.txt
            ((backed_up++))
        fi
    fi
done

# Generate the report
echo "Files Processed: $processed" > report.txt
echo "Duplicates Found: $duplicates" >> report.txt
echo "Unique Files Backed Up: $backed_up" >> report.txt

# print report
cat report.txt
