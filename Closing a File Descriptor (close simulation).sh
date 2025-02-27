#!/bin/bash

exec 3>output.txt  # Open file descriptor 3 for writing
echo "Writing to file..." >&3
exec 3>&-  # Close file descriptor 3
echo "File descriptor closed."
