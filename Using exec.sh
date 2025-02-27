#!/bin/bash

echo "Before exec..."
exec ls -l  # Replaces the shell process with `ls -l`
echo "This will never print if exec is successful."
