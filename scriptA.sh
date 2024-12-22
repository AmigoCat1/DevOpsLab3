#!/bin/bash

# Log file to store script activities
LOGFILE="MonitorScriptA.log"

# Docker image to use
DOCKER_IMAGE="amigocatandrey/optimaserver1"

# CPU utilization thresholds
CPU_BUSY_THRESHOLD=50
CPU_IDLE_THRESHOLD=5

# Interval and cycle configuration
CHECK_INTERVAL=30
CONSECUTIVE_CYCLES=4

# Server status tracking
declare -A SERVERS=( [srv1]=0 [srv2]=0 [srv3]=0 )
declare -A PORTS=( [srv1]=8081 [srv2]=8082 [srv3]=8083 )
declare -A CPUS=( [srv1]=0 [srv2]=1 [srv3]=2 )

# Initialize counters
BUSY_CYCLES=0
IDLE_CYCLES=0

# Function to start a server
start_server() {
    local server=$1
    echo "$(date) Starting $server on CPU${CPUS[$server]}" | tee -a $LOGFILE
    docker run --name $server --cpuset-cpus=${CPUS[$server]} -d -p ${PORTS[$server]}:8081 $DOCKER_IMAGE
    SERVERS[$server]=1
}

# Function to stop a server
stop_server() {
    local server=$1
    echo "$(date) Stopping $server" | tee -a $LOGFILE
    docker stop $server
    docker rm $server
    SERVERS[$server]=0
}

# Function to restart a server
restart_server() {
    local server=$1
    echo "$(date) Restarting $server" | tee -a $LOGFILE
    stop_server $server
    start_server $server
}

# Function to update all active servers
update_servers() {
    if docker pull $DOCKER_IMAGE | grep -q "Downloaded newer image"; then
        echo "$(date) Detected new image version. Initiating updates..." | tee -a $LOGFILE
        for server in "${!SERVERS[@]}"; do
            if [ ${SERVERS[$server]} -eq 1 ]; then
                restart_server $server
            fi
        done
    fi
}

# Function to get CPU usage for a server
get_cpu_usage() {
    local server=$1
    local usage=$(docker stats --no-stream --format "{{.Name}} {{.CPUPerc}}" | awk -v srv="$server" '$1 == srv {print $2}' | tr -d '%')
    echo ${usage:-0}
}

# Start initial server
start_server srv1

while true; do
    update_servers

    # Get CPU usage for each server
    SRV1_LOAD=$(get_cpu_usage srv1)
    SRV2_LOAD=$(get_cpu_usage srv2)
    SRV3_LOAD=$(get_cpu_usage srv3)

    echo "$(date) CPU Usage: srv1=${SRV1_LOAD}%, srv2=${SRV2_LOAD}%, srv3=${SRV3_LOAD}%" | tee -a $LOGFILE

    # Scale-up logic
    if (( $(echo "$SRV1_LOAD > $CPU_BUSY_THRESHOLD" | bc -l) )); then
        BUSY_CYCLES=$((BUSY_CYCLES + 1))
        if [ $BUSY_CYCLES -ge $CONSECUTIVE_CYCLES ] && [ ${SERVERS[srv2]} -eq 0 ]; then
            start_server srv2
            BUSY_CYCLES=0
        elif [ $BUSY_CYCLES -ge $CONSECUTIVE_CYCLES ] && [ ${SERVERS[srv3]} -eq 0 ] && [ ${SERVERS[srv2]} -eq 1 ]; then
            start_server srv3
            BUSY_CYCLES=0
        fi
    else
        BUSY_CYCLES=0
    fi

    # Scale-down logic
    if [ ${SERVERS[srv3]} -eq 1 ] && (( $(echo "$SRV3_LOAD < $CPU_IDLE_THRESHOLD" | bc -l) )); then
        IDLE_CYCLES=$((IDLE_CYCLES + 1))
        if [ $IDLE_CYCLES -ge $CONSECUTIVE_CYCLES ]; then
            stop_server srv3
            IDLE_CYCLES=0
        fi
    elif [ ${SERVERS[srv2]} -eq 1 ] && [ ${SERVERS[srv3]} -eq 0 ] && (( $(echo "$SRV2_LOAD < $CPU_IDLE_THRESHOLD" | bc -l) )); then
        IDLE_CYCLES=$((IDLE_CYCLES + 1))
        if [ $IDLE_CYCLES -ge $CONSECUTIVE_CYCLES ]; then
            stop_server srv2
            IDLE_CYCLES=0
        fi
    else
        IDLE_CYCLES=0
    fi

    # Wait for the next check
    sleep $CHECK_INTERVAL

done

