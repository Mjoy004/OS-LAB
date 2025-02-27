#!/bin/bash

echo "Parent process (PID: $$)"  # $$ gives the current process ID

# Creating a background process (simulating fork)
( 
    echo "Child process (PID: $BASHPID) running..."
    sleep 2
    echo "Child process exiting."
) &

child_pid=$!
echo "Waiting for child process (PID: $child_pid)..."
wait $child_pid  # Simulates wait()
echo "Child process finished."
