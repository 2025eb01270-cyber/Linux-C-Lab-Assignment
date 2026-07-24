#!/bin/bash

# continuously read the log file in real-time
# send any annoying permission errors into the void (/dev/null)
# pipe it to grep to only grab lines with "ERROR"
# use tee to show it on screen AND save it to a report file
tail -f system.log 2>/dev/null | grep --line-buffered "ERROR" | tee -a error_report.txt
