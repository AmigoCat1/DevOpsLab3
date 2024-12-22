#!/bin/bash

# Log file to keep track of activity
OUTPUT_LOG="ActivityScriptB.log"
ENDPOINT_URL="http://localhost:8081/compute" # Load balancer endpoint

while true; do
    # Generate a random wait time between 5 and 10 seconds
    RANDOM_DELAY=$((RANDOM%6+5))
    echo "$(date) Initiating request to $ENDPOINT_URL" | tee -a $OUTPUT_LOG

    # Send a GET request and log the HTTP status code
    curl -s -o /dev/null -w "%{http_code}\n" "$ENDPOINT_URL" | tee -a $OUTPUT_LOG

    # Pause for the specified delay
    sleep "$RANDOM_DELAY" &
    wait
done

