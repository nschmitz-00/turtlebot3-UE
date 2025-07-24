#!/bin/bash

export RMW_IMPLEMENTATION=rmw_fastrtps_cpp
export ROS_DISCOVERY_SERVER="127.0.0.1:11811"
export FASTRTPS_DEFAULT_PROFILES_FILE=${PWD}/fastdds_config.xml

# Restart the daemon to setup the super client config
echo "Restarting ROS2 Daemon For New FASTRTPS Settings" 
ros2 daemon stop
ros2 daemon start
