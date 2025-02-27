#!/bin/bash

file="test.txt"

if [ -e "$file" ]; then
    stat "$file"
else
    echo "File does not exist."
fi
